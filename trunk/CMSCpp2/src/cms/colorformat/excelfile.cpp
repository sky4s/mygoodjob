#include <includeall.h>
#pragma hdrstop
#include "excelfile.h"

//C系統文件

//C++系統文件
#include <iostream>

//其他庫頭文件

//本項目內頭文件

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
	    mode(mode), tableChanged(true),
	    caching(false) {

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

#ifdef USE_QUERY
	    query = bptr < TADOQuery > (new TADOQuery(null));
#endif
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
		sql +=
		    "[" + name + "] " + type +
		    ((x == size - 1) ? ")" : ",");
	    };

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
	    string sql;
	    if (caching && cachesql.size() != 0) {
		sql = "(";
	    } else {
		sql = "INSERT INTO [" + getTableName() + "$] (";

		foreach(string s, *fieldNames) {
		    sql += "[" + s + "],";
		};
		sql.replace(sql.size() - 1, 1, ") VALUES (");
	    }

	    foreach(string s, *values) {
		sql += text ? ("\"" + s + "\",") : (s + ",");
	    };
	    sql.replace(sql.size() - 1, 1, ")");

	    if (caching) {
		cachesql += sql + ",";
	    } else {
		execute(sql);
	    };
	};
	void ExcelFileDB::execute(const std::string & sql) {
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
	    int size = fieldNames->size();
	    for (int x = 0; x < size; x++) {
		string key = (*fieldNames)[x];
		string val = (*values)[x];
		sql += " [" + key + "] = ";
		sql += textValues ? ("\"" + val + "\"") : val;
		sql += (x == size - 1) ? "" : ",";
	    }

	    sql +=
		" WHERE [" + keyField + "] = " + lexical_cast < string >
		(keyValue);

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
		"SELECT * FROM [" + getTableName() + "$] Where " +
		keyField + " = ";
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
	    //string select = "SELECT * FROM " + getTableName();
	    string select = "SELECT * FROM [" + getTableName() + "$]";
	    bptr < TADODataSet > dataSet = selectDataSet(select);
	    bptr < DBQuery > query(new DBQuery(dataSet));
	    return query;
	};

	void ExcelFileDB::close() {
	    if (null != connection && true == connection->Connected) {
		connection->Close();
		CoUninitialize();
	    }
	};

	string_vector_ptr ExcelFileDB::makec(int count, ...) {
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

	string_vector_ptr ExcelFileDB::makes(int count, ...) {
	    string_vector_ptr result(new string_vector());
	    va_list num_list;
	    va_start(num_list, count);

	    for (int i = 0; i < count; i++) {
		const string str = va_arg(num_list, const string);
		//string str(c);
		result->push_back(str);
	    } va_end(num_list);
	    return result;
	};

	void
	 ExcelFileDB::deleteExist(const std::string & filename) {
	    const char
	    *cstr = filename.c_str();
	    if (FileExists(cstr)) {
		DeleteFile(cstr);
	    }
	};

	void ExcelFileDB::setKeyField(const std::string & keyField) {
	    this->keyField = keyField;
	};
	void ExcelFileDB::setCacheMode(bool caching) {
	    this->caching = caching;
	};
	void ExcelFileDB::excuteCache() {
	    int size = cachesql.size();
	    if (size != 0) {
		cachesql.erase(size - 1, size);
		//cachesql += ";";
		execute(cachesql);
		cachesql.clear();
	    }
	    /*
	       String   strSQL;  
	       strSQL   =   "";  
	       for   (   int   i   =   0;   i   <   1500;   ++i   )  
	       {  
	       strSQL   =   strSQL   +   "insert   into   test   valuse   ("   +   IntToStr(i)   +   ")";  
	       }  
	       ADOQuery1->Close();  
	       ADOQuery1->SQL->Clear();  
	       ADOQuery1->SQL->Add(strSQL);  
	       ADOQuery1->Execute();  
	       ADOQuery1->Close();
	     */
	};
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
	double_vector_ptr DBQuery::toDoubleVector(string_vector_ptr result) {
	    int size = result->size();
	    double_vector_ptr doublevec(new double_vector(size));
	    for (int x = 0; x != size; x++) {
		(*doublevec)[x] = lexical_cast < double >((*result)[x]);
	    }

	    return doublevec;
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
    };
};

