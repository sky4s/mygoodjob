#ifndef EXCELFILEH
#define EXCELFILEH


//#if   !defined(_DEBUG)
#pragma   link   "dbrtl.lib"
#pragma   link   "adortl.lib"
//#endif

//C系統文件

//C++系統文件

#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif

#include <map>

#ifdef __BORLANDC__
# pragma pack(pop)
#endif

//其他庫頭文件
#include <vcl.h>
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
			 string_vector_ptr fieldNames, string_vector_ptr values, bool textValues);
	    string_vector_ptr select0(const std::string & keyField,
				      const std::string & keyValue, bool textValues);
	     bptr < TADODataSet > selectDataSet(const std::string & sql);
	    static string_vector_ptr getResult(bptr < TADODataSet > dataSet);

	  public:
	     bool isTableExist(const std::string & tableName);
	    void execute(const std::string & sql);
	     ExcelFileDB(const std::string & fileName, const Mode mode);
	    ~ExcelFileDB();
	    void createTable(const std::string & tableName, string_vector_ptr fieldNames);
	    void createTable(const std::string & tableName,
			     string_vector_ptr fieldNames, string_vector_ptr fieldTypes);

	    void setTableName(const std::string & tableName);
	    void insert(string_vector_ptr fieldNames, string_vector_ptr values);
	    void insert(string_vector_ptr fieldNames, string_vector_ptr values, bool text);



	    void update(const std::string & keyField,
			const int keyValue, string_vector_ptr fieldNames, string_vector_ptr values);
	    void update(const std::string & keyField,
			const int keyValue,
			string_vector_ptr fieldNames, string_vector_ptr values, bool textValues);
	    void update(const std::string & keyField,
			const int keyValue,
			const std::string & fieldName, const std::string & value);

	    void update(const std::string & keyField,
			const int keyValue, const std::string & fieldName, const int value);

	    string_vector_ptr select(const std::string & keyField, const int keyValue);
	    string_vector_ptr select(const int keyValue);
	    string_vector_ptr select(const std::string & keyField, const std::string & keyValue);
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
	    static double_vector_ptr toDoubleVector(string_vector_ptr result);
	    bool hasNext();
	    const string_ptr get(int row, int column);
	};

	class ExcelAccessBase {
	  private:
	    const std::string & filename;
	    const Mode mode;
	     std::map < const std::string, string_vector_ptr) headerNamesMap;
	    static const std::string & DeltaData;
	    static const std::string & OldGammaTable;
	  protected:
	    static const std::string & GammaTable;
	     bptr < ExcelFileDB > db;
	    string_vector_ptr getHeaderNames(const std::string & sheetname);
	    const int getHeaderCount(const std::string & sheetname);

	    void initPropertySheet();
	    void initBegin();
	    const static std::string & Sheet1;
	    //virtual void init() = 0;
	  public:
	    void initSheet(const std::string & sheetname, int headerCount, ...);
	    void initSheet(const std::string & sheetname, string_vector_ptr headerNames);
	    void initSheet(const std::string & sheetname,
			   string_vector_ptr headerNames, string_vector_ptr fieldTypes);
	    void insertData(const std::string & sheetname, string_vector_ptr values, bool text);

	     ExcelAccessBase(const std::string & filename, Mode mode);
	    void
	     addProperty(const std::string & key, const std::string & value);
	    void
	     addProperty(const std::string & key, const double value);
	    static const std::string & Properties;
	     bptr < DBQuery > retrieve(const std::string & sheetname);
	    void setDeltaData(Component_vector_ptr componentVector);
	    void setDeltaData(Patch_vector_ptr patchVector);
	    void setGammaTable(RGB_vector_ptr dglut);
	    RGB_vector_ptr getGammaTable(const Dep::MaxValue & maxValue);

	};
	class SimpleExcelAccess:protected ExcelAccessBase {
	  private:

	  protected:
	    //string_vector_ptr headerNames;
	    //void init();
	  public:
	    SimpleExcelAccess(const std::string & filename, Mode mode);
	     SimpleExcelAccess(const std::string & filename, Mode mode,
			       string_vector_ptr headerNames);
	     SimpleExcelAccess(const std::string & filename, Mode mode,
			       string_vector_ptr headerNames, string_vector_ptr fieldTypes);
	     SimpleExcelAccess(const std::string & filename);
	     bptr < DBQuery > retrieve();
	    void insert(string_vector_ptr values);
	    /*void insert(const std::string & sheetname,
	       string_vector_ptr values); */

	    /*
	       提供可用來儲存value的預先定義格式
	     */
	    static bptr < SimpleExcelAccess > getValueStoreInstance(const std::string & filename);
	};
    };
};
#endif

