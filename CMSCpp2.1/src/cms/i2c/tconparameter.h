#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TConParameter {
	  private:
	    const cms::colorformat::ExcelFileDB & excel;
	    string_ptr tcon;
	  public:
	     TConParameter(const cms::colorformat::ExcelFileDB & excel);
	};
    };
};

#endif

