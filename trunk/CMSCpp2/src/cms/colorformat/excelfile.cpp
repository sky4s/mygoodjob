#include "excelfile.h"

//C系統文件

//C++系統文件
#include <iostream>

//其他庫頭文件
#include <vcl.h>
#include <boost/lexical_cast.hpp>
//本項目內頭文件

namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;

	//======================================================================
	// ExcelFileDB
	//======================================================================
	 bptr < WideString >
	    ExcelFileDB::toWideString(const std::string & sql) {
	    bptr < WideString > wstring(new WideString(sql.c_str()));
	    return wstring;
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
	    /*ADOConnection1 = new TADOConnection(null);
	       ADOConnection1->ConnectionString = connectstr;
	       ADOConnection1->Provider = "Microsoft.Jet.OLEDB.4.0";
	       ADOConnection1->Open(); */
	};
	ExcelFileDB::~ExcelFileDB() {
	    close();
	};
	/*void ExcelFileDB::createTable(string_ptr tableName,
	   string_vector_ptr fieldNames) {
	   if (!isAlterable()) {
	   throw IllegalStateException("!isAlterable()");
	   }

	   this->setTableName(tableName);

	   string sql = "CREATE TABLE [";
	   sql += tableName->c_str();
	   sql += "] (";

	   foreach(string s, *fieldNames) {
	   sql += "[";
	   sql += s.c_str();
	   //sql += "] TEXT(100),";
	   sql += "] REAL,";

	   }
	   sql.erase(sql.size() - 1, 1);
	   sql += ")";
	   cout << sql << endl;
	   execute(sql);
	   }; */
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
	    //cout<<this->tableName<<" "<<tableName<<endl;
	    string sql = "CREATE TABLE [" + tableName + "] (";

	    int size = fieldNames->size();
	    for (int x = 0; x != size; x++) {
		string & name = (*fieldNames)[x];
		string & type = (*fieldTypes)[x];
		sql += "[" + name + "] " + type + ",";
	    };

	    sql.erase(sql.size() - 1, 1);
	    sql += ")";
	    //cout << sql << endl;
	    execute(sql);
	};
	/*void ExcelFileDB::setTableName(string_ptr tableName) {
	   this->tableName = tableName;
	   tableChanged = true;
	   }; */
	void ExcelFileDB::setTableName(const std::string & tableName) {
	    this->tableName = tableName;
	}

	void ExcelFileDB::insert(string_vector_ptr fieldNames,
				 string_vector_ptr values) {
	    /*if (!isAlterable()) {
	       throw IllegalStateException("!isAlterable()");
	       }

	       string sql = "INSERT INTO [" + tableName + "] (";

	       foreach(string s, *fieldNames) {
	       sql += "[" + s + "],";
	       };
	       sql.erase(sql.size() - 1, 1);
	       sql += ") VALUES (";
	       foreach(string s, *values) {
	       //sql += "\"" + s + "\",";
	       sql += s + ",";
	       };
	       sql.erase(sql.size() - 1, 1);
	       sql += ")";
	       cout << sql << endl;
	       execute(sql); */
	    insert(fieldNames, values, false);
	};

	void ExcelFileDB::insert(string_vector_ptr fieldNames,
				 string_vector_ptr values, bool text) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }

	    string sql = "INSERT INTO [" + tableName + "] (";

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
	    cout << sql << endl;
	    execute(sql);
	};
	void ExcelFileDB::execute(const std::string & sql) {
	    connection->Execute(*toWideString(sql), TCommandType(),
				TExecuteOptions());
	};
	void ExcelFileDB::update0(const std::string & keyField,
				  const int &keyValue,
				  string_vector_ptr fieldNames,
				  string_vector_ptr values,
				  bool textValues) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }

	    string sql = "UPDATE [" + tableName + "$] SET";
	    int size = fieldNames->size();
	    for (int x = 0; x < size; x++) {
		string key = (*fieldNames)[x];
		string val = (*values)[x];
		sql +=
		    textValues ? " " + key + " = \"" + val + "\"," :
		    " " + key + " = " + val + ",";
	    } sql.erase(sql.size() - 1, 1);
	    sql +=
		" WHERE " + keyField + " = " + lexical_cast < string >
		(keyValue);
	    //cout << sql << endl;
	    execute(sql);

	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int &keyValue,
				 string_vector_ptr fieldNames,
				 string_vector_ptr values) {
	    update0(keyField, keyValue, fieldNames, values, true);
	};

	void ExcelFileDB::update(const std::string & keyField,
				 const int &keyValue,
				 const std::string & fieldName,
				 const std::string & value) {
	    string_vector_ptr fieldNames(new string_vector());
	    fieldNames->push_back(fieldName);
	    string_vector_ptr values(new string_vector());
	    values->push_back(value);

	    update0(keyField, keyValue, fieldNames, values, true);

	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int &keyValue,
				 const std::string & fieldName,
				 const int &value) {
	    string_vector_ptr fieldNames(new string_vector());
	    fieldNames->push_back(fieldName);
	    string_vector_ptr values(new string_vector());
	    values->push_back(lexical_cast < string > (value));

	    update0(keyField, keyValue, fieldNames, values, false);
	};

	/*void ExcelFileDB::update(const int &keyValue,
	   string_vector_ptr values) {

	   if ("" == keyField || null == tableName) {
	   throw IllegalStateException
	   ("\"\" == keyField || null == tableName");
	   }
	   string_vector_ptr fieldNames = getFieldNames(tableName);
	   update(keyField, keyValue, fieldNames, fieldNames);
	   }; */

	string_vector_ptr ExcelFileDB::select(const std::string & keyField,
					      const int &keyValue) {
	    bptr_ < TADODataSet >
		dataSet(new TADODataSet((TComponent *) null));
	    dataSet->Connection = connection.get();
	    string select = "SELECT * FROM " + tableName;;
	    dataSet->CommandText = *toWideString(select);
	    dataSet->Open();
	    cout << dataSet->FieldCount << endl;
	    //cout << dataSet.Fields[0]->Value << endl;
	    Variant v = dataSet->Fields->Fields[0]->Value;

	    string_vector_ptr result(new string_vector());
	    return result;
	};

	void ExcelFileDB::close() {
	    if (null != connection && true == connection->Connected) {
		connection->Close();
		//connection.reset((TADOConnection *) null);
		CoUninitialize();
		cout << "close" << endl;
	    }
	};

	void ExcelFileDB::setKeyField(const std::string & keyField) {
	    this->keyField = keyField;
	}
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
	const string & DGCodeFile::GammaTable = "Gamma Table";
	const string & DGCodeFile::RawData = "Raw Data";
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
		string_vector_ptr value(new string_vector(1));
		(*value)[0] = lexical_cast < string > (x);
		string_vector_ptr fieldName(new string_vector(1));
		(*fieldName)[0] = (*fieldNames)[0];

		db->insert(fieldName, value);
	    };
	};

	void DGCodeFile::init() {
	    if (Create == mode) {
		string_vector_ptr fieldNames =
		    getFieldNames(GammaHeader, 4);
		initDefaultData(fieldNames, GammaTable, false);
		fieldNames = getFieldNames(RawHeader, 13);
		initDefaultData(fieldNames, RawData, true);

		fieldNames = getFieldNames(PropertiesHeader, 2);
		string_vector_ptr fieldType(new string_vector(2));
		(*fieldType)[0] = "Text";
		(*fieldType)[1] = "Text";
		db->createTable(Properties, fieldNames, fieldType);
	    };
	};
	DGCodeFile::
	    DGCodeFile(const string & filename,
		       int n):db(new ExcelFileDB(filename, Create)), n(n),
	    mode(Create) {
	    init();
	};
	DGCodeFile::
	    DGCodeFile(const string & filename, int n,
		       const Mode mode):db(new ExcelFileDB(filename,
							   mode)), n(n),
	    mode(mode) {
	    init();
	};
	void DGCodeFile::setProperty(const string & key,
				     const string & value) {
	    db->setTableName(Properties);
	    string_vector_ptr fieldNames =
		getFieldNames(PropertiesHeader, 2);
	    string_vector_ptr values(new string_vector(2));
	    (*values)[0] = key;
	    (*values)[1] = value;
	    db->insert(fieldNames, values, tru7e);
	};
	//======================================================================
    };
};

