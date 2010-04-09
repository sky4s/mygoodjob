#ifndef EXCELFILEH
#define EXCELFILEH
//C系統文件

//C++系統文件

//其他庫頭文件
#include <ADODB.hpp>
#include <DB.hpp>
//本項目內頭文件

//#define USE_QUERY

namespace cms {
    namespace colorformat {
	enum Mode {
	    Create, Update, ReadOnly
	};

	class DBQuery;
	class ExcelFileDB {
	  private:

	    friend class DBQuery;
	    bptr < TADOConnection > connection;
	    bptr < TADOQuery > query;
	    const Mode mode;
	     std::string fileName;
	     std::string tableName;
	    string_vector_ptr fieldNames;
	     std::string keyField;
	    bool tableChanged;
	     std::string getTableName();
	     std::string getKeyField();
	     std::string cachesql;

	  public:
	     string_vector_ptr getFieldNames(string_ptr tableName);
	  protected:
	     bool isAlterable();

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
	    void execute(const std::string & sql);
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
			string_vector_ptr fieldNames,
			string_vector_ptr values, bool textValues);
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


	    void setKeyField(const std::string & keyField);
	    void setCacheMode(bool caching);
	    void excuteCache();
	  private:
	    void close();
	    bool caching;

	};
	class DBQuery {
	  private:
	    friend class ExcelFileDB;
	    bptr < TADODataSet > dataSet;
	    DBQuery(bptr < TADODataSet > dataSet);
	  public:
	    string_vector_ptr nextResult();
	    static double_vector_ptr toDoubleVector(string_vector_ptr
						    result);
	    bool hasNext();
	    const string_ptr get(int row, int column);
	};
    };
};
#endif

