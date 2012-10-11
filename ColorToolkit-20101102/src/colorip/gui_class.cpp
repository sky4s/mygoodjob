#include "gui_class.h"
#include <colorip/gui/TMainForm.h>

#include <iostream>
#include <fstream>


//C系統文件

//C++系統文件

//vcl庫頭文件
#include "inifiles.hpp"

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件

StringMap_ptr AbstractBase::map = nil_StringMap_ptr;

 
int_vector_ptr AbstractBase::getValuesFromFile(std::string tag)
{
    if (nil_StringMap_ptr == map) {
	map = getStringMap(TMainForm::AddressFile);
    }
    if (null == map || tag.length() == 0 || tag == "_NULL") {
	return nil_int_vector_ptr;
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

int AbstractBase::getValueFromFile(std::string tag)
{
    int_vector_ptr values = getValuesFromFile(tag);
    if (nil_int_vector_ptr == values) {
	return -1;
    } else if (1 == values->size()) {
	return (*values)[0];
    } else {
	throw java::lang::IllegalStateException("");
    }
};

bool AbstractBase::hasValueInFile(std::string tag)
{

    int_vector_ptr values = getValuesFromFile(tag);
    if (null != values) {
	int result = (*values)[0];
	return 0 != result;
    } else {
	return false;
    }

};
int_vector_ptr AbstractBase::getRegisterIntVector(string_vector_ptr registerTokens)
{
    using namespace std;
    int size = registerTokens->size();
    int_vector_ptr values(new int_vector(size - 1));
    for (int x = 1; x < size; x++) {
	string token = (*registerTokens)[x];
	(*values)[x - 1] = _toInt(token);
    }
    return values;
};
bool AbstractBase::setAddress(AbstractAddressType * address, std::string text)
{
    if (text.length() == 0 || text == "_NULL") {
	return false;
    }
    using namespace cms::util;
    string_vector_ptr tokens = StringVector::tokenize(text, ",");
    int_vector_ptr values = getRegisterIntVector(tokens);
    address->set(values, (*tokens)[0]);
    return true;
};

bool AbstractBase::setAddressFromFile(AbstractAddressType * address, std::string tag)
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


AbstractAddress_ptr AbstractBase::getAddress(std::string tag)
{
    if (nil_StringMap_ptr == map) {
	map = getStringMap(TMainForm::AddressFile);
    }
    if (null == map || tag.length() == 0 || tag == "_NULL") {
	return nil_AbstractAddress_ptr;
    }
    const std::string text = (*map)[tag];
    using namespace cms::util;
    string_vector_ptr tokens = StringVector::tokenize(text, ",");
    int_vector_ptr values = getRegisterIntVector(tokens);
    //return null;
    int size = values->size();
    bptr < AbstractAddressType > result;
    switch (size) {
    case 3:			//TBit1
	result = bptr < TBit > (new TBit());
	break;
    case 6:			//TBit2
	result = bptr < TBit2 > (new TBit2());
	break;
    case 9:			//TBit3
	result = bptr < TBit3 > (new TBit3());
	break;
    case 12:			//TBit4
	result = bptr < TBit4 > (new TBit4());
	break;
    case 4:			//TLUT
	result = bptr < TLUT > (new TLUT());
	break;
    };
    result->set(values, tag);
    return result;
};

AbstractAddressType *AbstractBase::getAddress2(std::string tag)
{
    if (nil_StringMap_ptr == map) {
	map = getStringMap(TMainForm::AddressFile);
    }
    if (tag.length() == 0 || tag == "_NULL") {
	return null;
    }
    const std::string text = (*map)[tag];
    using namespace cms::util;
    string_vector_ptr tokens = StringVector::tokenize(text, ",");
    int_vector_ptr values = getRegisterIntVector(tokens);
    //return null;
    int size = values->size();
    AbstractAddressType *result;
    switch (size) {
    case 3:{			//TBit1
	    result = new TBit();
	    break;
	}
    case 6:{			//TBit1
	    result = new TBit2();
	    break;
	}
    case 9:{			//TBit1
	    result = new TBit3();
	    break;
	}
    case 12:{			//TBit1
	    result = new TBit4();
	    break;
	}
    case 4:{			//TBit1
	    result = new TLUT();
	    break;
	}
    };
    result->set(values, tag);
    return result;
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
		    string_vector_ptr stringvector = StringVector::tokenize(line, ",");
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

AbstractBase::~AbstractBase()
{
    int x = 1;
};
StringMap_ptr AbstractBase::aliasNameMap = nil_StringMap_ptr;
//const std::string AbstractBase::AliasFilename = "alias.txt";
//const String AbstractBase::Alias = "alias";
void AbstractBase::initAliasNameMap()
{
    const std::string AliasFilename = "./alias.txt";
    const String Alias = "alias";


    if (NULL == aliasNameMap) {
	using namespace std;
	using namespace cms::util;
	aliasNameMap = StringMap_ptr(new StringMap());

	if (!Util::isFileExist(AliasFilename)) {

	    string ALIAS_NAMES[] = {
		//alias(nick), real name

		//sharpness
		"SP_DEMO_EN", "SP_DEMO",
		"SP_DEMO_SIDE", "SP_DEMO_LEFT",
		"SP_DEB_EN", "DEB_EN",
		"GLT_STR", "SP_GLB_STR",
		"GLB_STR", "SP_GLB_STR",
		"EDGE_THR", "SP_EDGE_THRESHOLD",
		"EDGE_TH", "SP_EDGE_THRESHOLD",
		"HORZ_THR", "SP_HORZ_THRESHOLD",
		"VERT_THR", "SP_VERT_THRESHOLD",

		//CM
		"CM_DEMO_EN", "CM_DEMO",
		"CM_DEMO_SIDE", "CM_DEMO_LEFT",
		"OFS1", "ofs1",
		"OFS2", "ofs2",
		"OFS3", "ofs3",

		//HSV
		"HUE_DEMO_EN", "HUE_DEMO",
		"HSV_EN", "HUE_EN",
		"HUE_DEMO_EN", "HUE_DEMO",
		"VALUE_MODE", "V_OFS_EN"
	    };
	    int size = (sizeof(ALIAS_NAMES) / sizeof(ALIAS_NAMES[0])) / 2;

	    bptr_ < TIniFile > ini(new TIniFile(AliasFilename.c_str()));
	    for (int x = 0; x < size; x++) {
		string key = ALIAS_NAMES[x * 2];
		string value = ALIAS_NAMES[x * 2 + 1];
		ini->WriteString(Alias, key.c_str(), value.c_str());
	    }
	    ini->UpdateFile();
	}

	if (Util::isFileExist(AliasFilename)) {
	    bptr_ < TIniFile > ini(new TIniFile(AliasFilename.c_str()));
	    TStrings *strings = new TStringList();
	    ini->ReadSection(Alias, strings);
	    int size = strings->Count;
	    for (int x = 0; x < size; x++) {
		String key = strings->Strings[x];
		String value = ini->ReadString(Alias, key, "");
		aliasNameMap->insert(make_pair(key.c_str(), value.c_str()));
	    }
	    delete strings;

	}


    }
}

