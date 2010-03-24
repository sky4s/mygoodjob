#ifndef EXCELFILETESTERH
#define EXCELFILETESTERH
//C系統文件

//C++系統文件

//其他庫頭文件
#include <ADODB.hpp>
#include <DB.hpp>
//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace colorformat {
	class ExcelFileTester {
	  private:
	    TADOConnection * ADOConnection1;
	  public:
	    ExcelFileTester(string_ptr filename);
	};
    };
};

#endif

