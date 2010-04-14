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
	class RampMeasureFile:public ExcelAccessBase {
	  private:
	    static const std::string & Sheet1;
	  public:
	     RampMeasureFile(const std::string & fileName,
			     const Mode mode);
	    void setMeasureData(Component_vector_ptr wMeasureData,
				Patch_vector_ptr rMeasureData,
				Patch_vector_ptr gMeasureData,
				Patch_vector_ptr bMeasureData);
	};
    };
};


#endif

