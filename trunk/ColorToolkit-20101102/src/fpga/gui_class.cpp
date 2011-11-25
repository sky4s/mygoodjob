#include "gui_class.h"
#include <fpga/gui/Unit1.h>

#include <iostream>
#include <fstream>
StringMap_ptr AbstractBase::map = nil_StringMap_ptr;

int_vector_ptr AbstractBase::getValuesFromFile(std::string tag)
{
    if (nil_StringMap_ptr == map) {
	map = getStringMap(TMainForm::AddressFile);
    }
    if (tag.length() == 0 || tag == "_NULL") {
	return nil_int_vector;
    }
    const std::string text = (*map)[tag];
    if (text.size() == 0) {
	return nil_int_vector_ptr;
    }
    using namespace cms::util;
    string_vector_ptr tokens = StringVector::tokenize(text, ",");
    int size = tokens->size();
    int_vector_ptr values(new int_vector(size - 1));
    for (int x = 1; x < size; x++) {
	string token = (*tokens)[x];
	(*values)[x - 1] = _toInt(token);
    }
    return values;
};

bool AbstractBase::setAddress(AbstractAddressType * address,
			      std::string text)
{
    if (text.length() == 0 || text == "_NULL") {
	return false;
    }
    using namespace cms::util;
    string_vector_ptr tokens = StringVector::tokenize(text, ",");
    int size = tokens->size();
    int_vector_ptr values(new int_vector(size - 1));
    for (int x = 1; x < size; x++) {
	string token = (*tokens)[x];
	(*values)[x - 1] = _toInt(token);
    }
    address->set(values, (*tokens)[0]);
    return true;
};

bool AbstractBase::setAddressFromFile(AbstractAddressType * address,
				      std::string tag)
{
    if (nil_StringMap_ptr == map) {
	map = getStringMap(TMainForm::AddressFile);
    }
    if (tag.length() == 0 || tag == "_NULL") {
	return false;
    }
    const std::string text = (*map)[tag];
    setAddress(address, text);
    return true;
};

StringMap_ptr AbstractBase::getStringMap(std::string filename)
{
    using namespace std;
    using namespace cms::util;

    initAliasNameMap();
    if (Util::isFileExist(filename)) {
	ifstream infile(filename.c_str());

	if (infile.is_open()) {
	    string line;
	    StringMap_ptr map(new StringMap());
	    while (infile.good()) {
		getline(infile, line);
		if (line.length() != 0) {
		    string_vector_ptr stringvector =
			StringVector::tokenize(line, ",");
		    string key = (*stringvector)[0];
		    const std::string aliasName = (*aliasNameMap)[key];
		    if (aliasName.length() != 0) {

			//line = line.replace(key, aliasName);
			line = line.replace(0, key.size(), aliasName);
			key = aliasName;
		    }
		    map->insert(make_pair(key, line));
		}
	    }
	    infile.close();
	    return map;
	}
    }
    return nil_StringMap_ptr;
}

StringMap_ptr AbstractBase::getStringMap(AnsiString filename)
{
    return getStringMap(std::string(filename.c_str()));
}



void AbstractBase::resetAddressMap()
{
    map = nil_StringMap_ptr;
}


void AbstractBase::initAliasNameMap()
{
    if (nil_StringMap_ptr == aliasNameMap) {
	using namespace std;
	aliasNameMap = StringMap_ptr(new StringMap());

	string ALIAS_NAMES[] = {
	    "CM_DEMO_EN", "CM_DEMO",
	    "CM_DEMO_SIDE", "CM_DEMO_LEFT",
	    "SP_DEMO_EN", "SP_DEMO",
	    "SP_DEMO_SIDE", "SP_DEMO_LEFT",
	    "HUE_DEMO_EN", "HUE_DEMO",
	    "OFS1", "ofs1",
	    "OFS2", "ofs2",
	    "OFS3", "ofs3",
	    "SP_GLB_STR", "GLB_STR",
	    "SP_DEB_EN", "DEB_EN",
	    "EDGE_THR", "SP_EDGE_THRESHOLD",
	    "HORZ_THR", "SP_HORZ_THRESHOLD",
	    "VERT_THR", "SP_VERT_THRESHOLD",
	    "CM_DEMO_EN", "CM_DEMO",
	    "HSV_EN", "HUE_EN",
	    "HUE_DEMO_EN", "HUE_DEMO",
	};
	//string *ALIAS_NAMES = getAliasNameArray();
	int size = (sizeof(ALIAS_NAMES) / sizeof(ALIAS_NAMES[0])) / 2;

	for (int x = 0; x < size; x++) {
	    string key = ALIAS_NAMES[x * 2];
	    string value = ALIAS_NAMES[x * 2 + 1];

	    aliasNameMap->insert(make_pair(key, value));
	}
    }
}


StringMap_ptr AbstractBase::aliasNameMap = nil_StringMap_ptr;

