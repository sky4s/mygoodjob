#include "excelfile.h"

//C系統文件

//C++系統文件
#include <iostream>

//其他庫頭文件
#include <vcl.h>
#include <boost/lexical_cast.hpp>
//本項目內頭文件
#include <cms/lcd/calibrate/lcdcalibrator.h>
#include <cms/lcd/calibrate/rgbgamma.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	using namespace lcd::calibrate;
	using namespace Indep;
	using namespace Dep;

	//======================================================================
	// ExcelFileDB
	//======================================================================
	 bptr < WideString >
	    ExcelFileDB::toWideString(const std::string & sql) {
	    bptr < WideString > wstring(new WideString(sql.c_str()));
	    return wstring;
	};

	string ExcelFileDB::getTableName() {
	    if (tableName.size() == 0) {
		throw IllegalStateException("Set tableName first!");
	    };
	    return tableName;
	};
	string ExcelFileDB::getKeyField() {
	    if (keyField.size() == 0) {
		throw IllegalStateException("Set keyField first!");
	    };
	    return keyField;
	};
	string_vector_ptr ExcelFileDB::getFieldNames(string_ptr tableName) {
	    if (null == fieldNames || true == tableChanged) {
		bptr_ < TStringList > stringList(new TStringList());
		connection->GetFieldNames(tableName->c_str(),
					  stringList.get());
		fieldNames.reset(new string_vector());
		for (int x = 0; x != stringList->Count; x++) {
		    AnsiString as = (*stringList)[x];
		    string s(as.c_str());
		    fieldNames->push_back(s);
		};
	    }
	    //return result;
	    return fieldNames;
	};
	bool ExcelFileDB::isAlterable() {
	    return mode == Create || mode == Update;
	};

      ExcelFileDB::ExcelFileDB(const string & fileName, const Mode mode):fileName(fileName),
	    mode(mode), tableChanged(true)
	{

	    WideString connectstr;
	    connectstr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	    connectstr += fileName.c_str();
	    connectstr +=
		";Mode=ReadWrite;Extended Properties=Excel 8.0;Persist Security Info=False";

	    CoInitialize(null);
	    connection.reset(new TADOConnection(null));
	    connection->ConnectionString = connectstr;
	    connection->Provider = "Microsoft.Jet.OLEDB.4.0";
	    connection->Open();
	};
	ExcelFileDB::~ExcelFileDB() {
	    close();
	};

	void ExcelFileDB::createTable(const std::string & tableName,
				      string_vector_ptr fieldNames) {
	    int size = fieldNames->size();
	    string_vector_ptr fieldTypes(new string_vector(size));
	    foreach(string & s, *fieldTypes) {
		s = "Real";
	    };
	    createTable(tableName, fieldNames, fieldTypes);
	};

	void ExcelFileDB::createTable(const std::string & tableName,
				      string_vector_ptr fieldNames,
				      string_vector_ptr fieldTypes) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }
	    if (fieldNames->size() != fieldTypes->size()) {
		throw
		    IllegalArgumentException
		    ("fieldNames->size() != fieldTypes->size()");
	    }

	    this->setTableName(tableName);
	    string sql = "CREATE TABLE [" + tableName + "] (";

	    int size = fieldNames->size();
	    for (int x = 0; x != size; x++) {
		string & name = (*fieldNames)[x];
		string & type = (*fieldTypes)[x];
		sql += "[" + name + "] " + type + ",";
	    };

	    sql.erase(sql.size() - 1, 1);
	    sql += ")";
	    execute(sql);
	};

	void ExcelFileDB::setTableName(const std::string & tableName) {
	    this->tableName = tableName;
	}

	void ExcelFileDB::insert(string_vector_ptr fieldNames,
				 string_vector_ptr values) {

	    insert(fieldNames, values, false);
	};

	void ExcelFileDB::insert(string_vector_ptr fieldNames,
				 string_vector_ptr values, bool text) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }

	    string sql = "INSERT INTO [" + getTableName() + "] (";

	    foreach(string s, *fieldNames) {
		sql += "[" + s + "],";
	    };
	    sql.erase(sql.size() - 1, 1);
	    sql += ") VALUES (";
	    foreach(string s, *values) {
		//sql += "\"" + s + "\",";
		sql += text ? ("\"" + s + "\",") : (s + ",");
	    };
	    sql.erase(sql.size() - 1, 1);
	    sql += ")";
	    //cout << sql << endl;
	    execute(sql);
	};
	void ExcelFileDB::execute(const std::string & sql) {
	    //std::cout << sql << std::endl;
	    connection->Execute(*toWideString(sql), TCommandType(),
				TExecuteOptions());
	};
	void ExcelFileDB::update0(const std::string & keyField,
				  const int keyValue,
				  string_vector_ptr fieldNames,
				  string_vector_ptr values,
				  bool textValues) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }
	    string sql = "UPDATE [" + getTableName() + "$] SET";
	    //string sql = "UPDATE [Raw_Data$] SET";
	    int size = fieldNames->size();
	    for (int x = 0; x < size; x++) {
		string key = (*fieldNames)[x];
		string val = (*values)[x];
		//sql += textValues ? " \"" + key + "\" = \"" + val + "\"," :
		//    " " + key + " = " + val + ",";
		sql += " [" + key + "] = ";
		sql += textValues ? ("\"" + val + "\",") : (val + ",");
		//sql += textValues ? "[" + key + "] = \"" + val + "\"," : " [" + key + "] = " + val + ",";
	    }
	    sql.erase(sql.size() - 1, 1);
	    sql +=
		" WHERE [" + keyField + "] = " + lexical_cast < string >
		(keyValue);
	    //cout << sql << endl;
	    execute(sql);

	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 string_vector_ptr fieldNames,
				 string_vector_ptr values) {
	    update0(keyField, keyValue, fieldNames, values, true);
	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 string_vector_ptr fieldNames,
				 string_vector_ptr values,
				 bool textValues) {
	    update0(keyField, keyValue, fieldNames, values, textValues);
	};

	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 const std::string & fieldName,
				 const std::string & value) {
	    string_vector_ptr fieldNames(new string_vector());
	    fieldNames->push_back(fieldName);
	    string_vector_ptr values(new string_vector());
	    values->push_back(value);

	    update0(keyField, keyValue, fieldNames, values, true);

	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 const std::string & fieldName,
				 const int value) {
	    string_vector_ptr fieldNames(new string_vector());
	    fieldNames->push_back(fieldName);
	    string_vector_ptr values(new string_vector());
	    values->push_back(lexical_cast < string > (value));

	    update0(keyField, keyValue, fieldNames, values, false);
	};

	string_vector_ptr ExcelFileDB::select0(const std::
					       string & keyField,
					       const std::
					       string & keyValue,
					       bool textValues) {
	    string select =
		"SELECT * FROM " + getTableName() + " Where " + keyField +
		" = ";
	    select += textValues ? "\"" + keyValue + "\"" : keyValue;
	    bptr < TADODataSet > dataSet = selectDataSet(select);
	    return getResult(dataSet);
	};

	bptr < TADODataSet >
	    ExcelFileDB::selectDataSet(const std::string & sql) {
	    bptr < TADODataSet >
		dataSet(new TADODataSet((TComponent *) null));
	    dataSet->Connection = connection.get();
	    dataSet->CommandText = *toWideString(sql);
	    dataSet->Open();
	    dataSet->First();
	    return dataSet;
	};

	string_vector_ptr ExcelFileDB::getResult(bptr < TADODataSet >
						 dataSet) {
	    string_vector_ptr result(new string_vector());
	    int fields = dataSet->FieldCount;

	    for (int x = 0; x != fields; x++) {
		AnsiString astr = dataSet->Fields->Fields[x]->AsString;
		string str(astr.c_str());
		result->push_back(str);
	    }
	    return result;
	};

	string_vector_ptr ExcelFileDB::select(const std::string & keyField,
					      const int keyValue) {
	    return select0(keyField, lexical_cast < string > (keyValue),
			   false);
	};

	string_vector_ptr ExcelFileDB::select(const int keyValue) {
	    return select0(getKeyField(),
			   lexical_cast < string > (keyValue), false);
	};
	string_vector_ptr ExcelFileDB::select(const std::string & keyField,
					      const std::
					      string & keyValue) {
	    return select0(keyField, keyValue, true);
	};
	string_vector_ptr ExcelFileDB::select(const std::string & keyValue) {
	    return select0(getKeyField(), keyValue, true);
	};

	bptr < DBQuery > ExcelFileDB::selectAll() {
	    string select = "SELECT * FROM " + getTableName();
	    bptr < TADODataSet > dataSet = selectDataSet(select);
	    bptr < DBQuery > query(new DBQuery(dataSet));
	    return query;
	};

	void ExcelFileDB::close() {
	    if (null != connection && true == connection->Connected) {
		connection->Close();
		//connection.reset((TADOConnection *) null);
		CoUninitialize();
		//cout << "close" << endl;
	    }
	};

	string_vector_ptr ExcelFileDB::make(int count, ...) {
	    string_vector_ptr result(new string_vector());
	    va_list num_list;
	    va_start(num_list, count);

	    for (int i = 0; i < count; i++) {
		const char *c = va_arg(num_list, const char *);
		string str(c);
		result->push_back(str);
	    } va_end(num_list);
	    return result;
	};

	void ExcelFileDB::setKeyField(const std::string & keyField) {
	    this->keyField = keyField;
	}
	//======================================================================

	//======================================================================
	//
	//======================================================================
      DBQuery::DBQuery(bptr < TADODataSet > dataSet):dataSet(dataSet)
	{
	};

	string_vector_ptr DBQuery::nextResult() {
	    if (!hasNext()) {
		throw IllegalStateException("!hasNext()");
	    }
	    string_vector_ptr result = ExcelFileDB::getResult(dataSet);
	    dataSet->Next();
	    return result;
	};
	bool DBQuery::hasNext() {
	    return !dataSet->Eof;
	};

	const string_ptr DBQuery::get(int row, int column) {
	    dataSet->First();
	    for (int x = 0; x < row; x++) {
		dataSet->Next();
	    };
	    string_vector_ptr result = nextResult();
	    string_ptr str(new string((*result)[column]));
	    //dataSet->UpdateRecord();
	    return str;
	};
	/*void DBQuery::set(int row, int column, const std::string & value) {
	   throw UnsupportedOperationException();
	   dataSet->First();
	   for (int x = 0; x < row; x++) {
	   dataSet->Next();
	   };
	   AnsiString astr(value.c_str());
	   dataSet->Fields->Fields[column]->Text = astr;
	   };

	   void DBQuery::refresh() {
	   throw UnsupportedOperationException();
	   dataSet->Refresh();
	   }; */

	//======================================================================

	//======================================================================
	// DGCodeFile
	//======================================================================
	const std::string DGCodeFile::GammaHeader[4] =
	    { "Gray Level", "Gamma R", "Gamma G", "Gamma B" };
	const std::string DGCodeFile::RawHeader[13] =
	    { "Gray Level", "W_x", "W_y", "W_Y (nit)", "W_R", "W_G", "W_B",
	    "RP", "GP", "BP", "RP_Intensity_Fix", "GP_Intensity_Fix",
	    "BP_Intensity_Fix"
	};
	const std::string DGCodeFile::PropertiesHeader[2] =
	    { "Key", "Value" };
	//const string & DGCodeFile::GammaTable = "Gamma Table";
	//const string & DGCodeFile::RawData = "Raw Data";
	const string & DGCodeFile::GammaTable = "Gamma_Table";
	const string & DGCodeFile::RawData = "Raw_Data";
	const string & DGCodeFile::Properties = "Properties";

	string_vector_ptr DGCodeFile::getFieldNames(const string *
						    fieldNames, int n) {
	    string_vector_ptr result(new string_vector(n));
	    for (int x = 0; x < n; x++) {
		(*result)[x] = fieldNames[x];
	    }
	    return result;
	};

	void DGCodeFile::initDefaultData(string_vector_ptr fieldNames,
					 const string & tableName,
					 bool reverse) {
	    db->createTable(tableName, fieldNames);
	    int start = !reverse ? 0 : n - 1;
	    int end = !reverse ? n : -1;
	    int step = !reverse ? 1 : -1;

	    for (int x = start; x != end; x += step) {
		string_vector_ptr value =
		    ExcelFileDB::make(1, lexical_cast < string > (x));
		string_vector_ptr fieldName =
		    ExcelFileDB::make(1, (*fieldNames)[0]);

		db->insert(fieldName, value);
	    };
	};

	void DGCodeFile::initDefaultData(string_vector_ptr fieldNames,
					 const std::string & tableName,
					 int_vector_ptr nvector,
					 bool reverse) {
	    db->createTable(tableName, fieldNames);
	    int size = nvector->size();

	    int start = !reverse ? 0 : size - 1;
	    int end = !reverse ? size : -1;
	    int step = !reverse ? 1 : -1;


	    for (int x = start; x != end; x += step) {
		int n = (*nvector)[x];
		string_vector_ptr value
		    = ExcelFileDB::make(1, lexical_cast < string > (n));
		string_vector_ptr fieldName =
		    ExcelFileDB::make(1, (*fieldNames)
				      [0]);
		db->insert(fieldName, value);
	    }
	};
	void
	 DGCodeFile::init() {
	    if (null == GammaFieldNames) {
		GammaFieldNames = getFieldNames(GammaHeader, 4);
	    }
	    if (null == RawFieldNames) {
		RawFieldNames = getFieldNames(RawHeader, 13);
	    }
	    if (null == PropertiesFieldNames) {
		PropertiesFieldNames = getFieldNames(PropertiesHeader, 2);
	    }
	    if (Create == mode) {
		if (FileExists(filename.c_str())) {
		    throw IllegalStateException("File " + filename +
						" exists.");
		}

		db.reset(new ExcelFileDB(filename, Create));

		if (n != -1) {
		    initDefaultData(GammaFieldNames, GammaTable, false);
		    initDefaultData(RawFieldNames, RawData, true);
		} else {
		    initDefaultData(GammaFieldNames, GammaTable, nvector,
				    false);
		    initDefaultData(RawFieldNames, RawData, nvector, true);
		};

		string_vector_ptr fieldType(new string_vector(2));
		(*fieldType)[0]
		    = "Text";
		(*fieldType)[1]
		    = "Text";
		db->createTable
		    (Properties, PropertiesFieldNames, fieldType);
	    };
	};
	DGCodeFile::DGCodeFile(const string & filename, int
			       n):filename(filename), n(n), mode(Create) {
	    init();
	};
	DGCodeFile::DGCodeFile(const std::string & filename,
			       int_vector_ptr nvector):filename(filename),
	    nvector(nvector), n(-1), mode(Create) {

	};
	DGCodeFile::
	    DGCodeFile(const string & filename, int n,
		       const Mode mode):filename(filename), n(n),
	    mode(mode) {
	    init();
	};
	DGCodeFile::
	    DGCodeFile
	    (const string & filename, int_vector_ptr nvector,
	     const Mode mode):filename(filename), nvector(nvector), n(-1),
	    mode(mode) {
	    init();
	};
	void
	 DGCodeFile::addProperty(const string & key, const string & value) {
	    db->setTableName(Properties);
	    string_vector_ptr values(new string_vector(2));
	    (*values)[0] = key;
	    (*values)[1] = value;
	    db->insert(PropertiesFieldNames, values, true);
	};
	void
	 DGCodeFile::setRawData(Composition_vector_ptr compositionVector) {
	    db->setTableName(RawData);
	    int size = compositionVector->size();
	    string_vector_ptr values(new string_vector(13));

	    //for (int x = size - 1; x != -1; x--) {
	    for (int x = 0; x != size; x++) {
		Composition_ptr c = (*compositionVector)[x];
		int w = static_cast < int >(c->rgb->getValue(Channel::W));

		(*values)[0] = lexical_cast < string > (w);
		xyY_ptr xyY(new CIExyY(c->XYZ));
		(*values)[1] = lexical_cast < string > (xyY->x);
		(*values)[2] = lexical_cast < string > (xyY->y);
		(*values)[3] = lexical_cast < string > (xyY->Y);
		RGB_ptr component = c->component;
		(*values)[4] = lexical_cast < string > (component->R);
		(*values)[5] = lexical_cast < string > (component->G);
		(*values)[6] = lexical_cast < string > (component->B);
		//gamma 0~100
		(*values)[7] = "0";
		(*values)[8] = "0";
		(*values)[9] = "0";
		(*values)[10] = "0";
		(*values)[11] = "0";
		(*values)[12] = "0";
		db->update(RawHeader[0], w, RawFieldNames, values, false);
	    }
	};


	void
	 DGCodeFile::
	    setRawData
	    (Composition_vector_ptr
	     compositionVector, RGBGamma_ptr rgbgamma) {

	};

	Composition_vector_ptr DGCodeFile::getCompositionVector() {
	    Composition_vector_ptr vector(new Composition_vector());
	    bptr < DBQuery > query = db->selectAll();
	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		int gray = lexical_cast < int >((*result)[0]);
		double x = lexical_cast < double >((*result)[1]);
		double y = lexical_cast < double >((*result)[2]);
		double Y = lexical_cast < double >((*result)[3]);
		double R = lexical_cast < double >((*result)[4]);
		double G = lexical_cast < double >((*result)[5]);
		double B = lexical_cast < double >((*result)[6]);
		double r = lexical_cast < double >((*result)[7]);
		double g = lexical_cast < double >((*result)[8]);
		double b = lexical_cast < double >((*result)[9]);

		RGB_ptr rgb(new RGBColor(gray, gray, gray));
		RGB_ptr component(new RGBColor(R, G, B));
		xyY_ptr xyY(new CIExyY(x, y, Y));
		XYZ_ptr XYZ(xyY->toXYZ());
		RGB_ptr gamma(new RGBColor(r, g, b));

		bptr < Composition >
		    composition(new
				Composition(rgb, component, XYZ, gamma));
		vector->push_back(composition);
	    };
	    return vector;
	};

	void
	 DGCodeFile::deleteExist(const std::string & filename) {
	    const char
	    *cstr = filename.c_str();
	    if (FileExists(cstr)) {
		DeleteFile(cstr);
	    }
	};
	string_vector_ptr DGCodeFile::makeValues(int
						 n, Composition_ptr c) {
	    return
		makeValues(n, c, RGB_ptr((RGBColor *) null),
			   RGB_ptr((RGBColor *) null));
	};
	string_vector_ptr DGCodeFile::makeValues(int n, Composition_ptr c,
						 RGB_ptr rgbGamma,
						 RGB_ptr rgbGammaFix) {
	    //tring_vector_ptr fieldNames = getFieldNames(RawHeader, 13);
	    string_vector_ptr values(new string_vector(13));
	    (*values)[0] = lexical_cast < string > (n);
	    xyY_ptr xyY(new CIExyY(c->XYZ));
	    (*values)[1] = lexical_cast < string > (xyY->x);
	    (*values)[2] = lexical_cast < string > (xyY->y);
	    (*values)[3] = lexical_cast < string > (xyY->Y);
	    RGB_ptr component = c->component;
	    (*values)[4] = lexical_cast < string > (component->R);
	    (*values)[5] = lexical_cast < string > (component->G);
	    (*values)[6] = lexical_cast < string > (component->B);
	    //gamma 0~100
	    if (null != rgbGamma) {
		(*values)[7] = lexical_cast < string > (rgbGamma->R);
		(*values)[8] = lexical_cast < string > (rgbGamma->G);
		(*values)[9] = lexical_cast < string > (rgbGamma->B);
	    }

	    if (null != rgbGammaFix) {
		(*values)[10] = lexical_cast < string > (rgbGammaFix->R);
		(*values)[11] = lexical_cast < string > (rgbGammaFix->G);
		(*values)[12] = lexical_cast < string > (rgbGammaFix->B);
	    }
	    return values;
	};
	string_vector_ptr DGCodeFile::GammaFieldNames;
	string_vector_ptr DGCodeFile::RawFieldNames;
	string_vector_ptr DGCodeFile::PropertiesFieldNames;
	//======================================================================
    };
};

