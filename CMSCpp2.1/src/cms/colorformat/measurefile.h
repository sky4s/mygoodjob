#ifndef MEASUREFILEH
#define MEASUREFILEH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace colorformat {
	class SimpleExcelReader {
	  private:
	    bptr < ExcelFileDB > excel;
	  public:
	    SimpleExcelReader(const std::string & filename);
	};
	class MeasureFile {
	};
	class RampMeasureFile {
	};
    };
};


#endif

