#ifndef EXCELFILEH
#define EXCELFILEH
//C系統文件

//C++系統文件

//其他庫頭文件
#include <ADODB.hpp>
#include <DB.hpp>
//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace colorformat {
	enum Mode {
	    Create, Update, ReadOnly
	};


	class ExcelFile {
	};
	class DBQuery;
	class ExcelFileDB {


	  private:

	    friend class DBQuery;
	    bptr < TADOConnection > connection;
	    const Mode mode;
	     std::string fileName;
	     std::string tableName;
	     bptr < WideString > toWideString(const std::string & sql);
	    string_vector_ptr fieldNames;
	     std::string keyField;
	    bool tableChanged;
	     std::string getTableName();
	     std::string getKeyField();
	    //bptr < TADODataSet > selectAllDataSet;

	  public:
	     string_vector_ptr getFieldNames(string_ptr tableName);
	  protected:
	     bool isAlterable();
	    void execute(const std::string & sql);
	    void update0(const std::string & keyField,
			 const int keyValue,
			 string_vector_ptr fieldNames,
			 string_vector_ptr values, bool textValues);
	    string_vector_ptr select0(const std::string & keyField,
				      const std::string & keyValue,
				      bool textValues);
	     bptr < TADODataSet > selectDataSet(const std::string & sql);
	    static string_vector_ptr getResult(bptr < TADODataSet >
					       dataSet);
	  public:
	     ExcelFileDB(const std::string & fileName, const Mode mode);
	    ~ExcelFileDB();
	    void createTable(const std::string & tableName,
			     string_vector_ptr fieldNames);
	    void createTable(const std::string & tableName,
			     string_vector_ptr fieldNames,
			     string_vector_ptr fieldTypes);

	    void setTableName(const std::string & tableName);
	    void insert(string_vector_ptr fieldNames,
			string_vector_ptr values);
	    void insert(string_vector_ptr fieldNames,
			string_vector_ptr values, bool text);



	    void update(const std::string & keyField,
			const int keyValue,
			string_vector_ptr fieldNames,
			string_vector_ptr values);
	    void update(const std::string & keyField,
			const int keyValue,
			const std::string & fieldName,
			const std::string & value);

	    void update(const std::string & keyField,
			const int keyValue,
			const std::string & fieldName, const int value);

	    string_vector_ptr select(const std::string & keyField,
				     const int keyValue);
	    string_vector_ptr select(const int keyValue);
	    string_vector_ptr select(const std::string & keyField,
				     const std::string & keyValue);
	    string_vector_ptr select(const std::string & keyValue);

	     bptr < DBQuery > selectAll();
	    /*string_vector_ptr nextResult();
	       bool hasNext(); */

	    static string_vector_ptr makeStringVector(int count, ...);

	    void setKeyField(const std::string & keyField);
	  private:
	    void close();

	};
	class DBQuery {
	  private:
	    friend class ExcelFileDB;
	    bptr < TADODataSet > dataSet;
	    DBQuery(bptr < TADODataSet > dataSet);
	  public:
	    string_vector_ptr nextResult();
	    bool hasNext();
	    const string_ptr get(int row, int column);
	    void set(int row, int column, const std::string & value);
	    void refresh();
	};
	class DGCodeFile {
	  private:
	    bptr < ExcelFileDB > db;
	    const Mode mode;
	    void init();
	    void initDefaultData(string_vector_ptr fieldNames,
				 const std::string & tableName,
				 bool reverse);
	    const int n;
	    static string_vector_ptr getFieldNames(const std::string *
						   fieldNames, int n);
	  public:
	    static const std::string GammaHeader[4];
	    static const std::string RawHeader[13];
	    static const std::string PropertiesHeader[2];
	    static const std::string & GammaTable;
	    static const std::string & RawData;
	    static const std::string & Properties;
	     DGCodeFile(const std::string & filename, int n);
	     DGCodeFile(const std::string & filename, int n,
			const Mode mode);
	    void setProperty(const std::string & key,
			     const std::string & value);
	};
    };
};
#endif

