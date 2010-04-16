#ifndef EXCELFILEH
#define EXCELFILEH
//C系統文件

//C++系統文件
#include <vcl.h>
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <map>
#ifdef __BORLANDC__
# pragma pack(pop)
#endif

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

	class ExcelAccessBase {
	  private:
	    const std::string & filename;
	    const Mode mode;
	     std::map < const std::string,
		string_vector_ptr) headerNamesMap;
	  protected:
	     bptr < ExcelFileDB > db;
	    string_vector_ptr getHeaderNames(const std::
					     string & sheetname);
	    const int getHeaderCount(const std::string & sheetname);
	    void initSheet(const std::string & sheetname, int headerCount,
			   ...);
	    void initSheet(const std::string & sheetname,
			   string_vector_ptr headerNames);
	    void initPropertySheet();
	    void initBegin();
	    void insertData(const std::string & sheetname,
			    string_vector_ptr values, bool text);
	    //virtual void init() = 0;
	  public:

	     ExcelAccessBase(const std::string & filename, Mode mode);
	    void
	     addProperty(const std::string & key,
			 const std::string & value);
	    void
	     addProperty(const std::string & key, const double value);
	    static const std::string & Properties;
	     bptr < DBQuery > retrieve(const std::string & sheetname);

	};
	class SimpleExcelAccess:public ExcelAccessBase {
	  private:
	    const static std::string & Sheet1;
	  protected:
	     string_vector_ptr headerNames;
	    //void init();
	  public:
	     SimpleExcelAccess(const std::string & filename, Mode mode,
			       string_vector_ptr headerNames);
	     SimpleExcelAccess(const std::string & filename);
	     bptr < DBQuery > retrieve();
	    void insert(string_vector_ptr values);
	    static bptr < SimpleExcelAccess >
		getValueStoreInstance(const std::string & filename);
	};
    };
};
#endif

