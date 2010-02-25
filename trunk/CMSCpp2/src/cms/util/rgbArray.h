#ifndef RGBARRAYH
#define RGBARRAYH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>


namespace cms {
    namespace util {
	class RGBArray {

	};
	class RGBVector {
	  public:
	    static string_ptr toString(RGB_vector_ptr rgbVector);
	    static RGB_vector_ptr getLinearRGBVector(int n);
	    static void storeToExcel(string_ptr filename,
				     string_vector_ptr header,
				     RGB_vector_ptr rgbVector);
	    static void storeToExcelDB(bptr <
				       cms::colorformat::ExcelFileDB > db,
				       string_ptr tableName,
				       string_vector_ptr header,
				       RGB_vector_ptr rgbVector);
	};

    };
}
#endif

