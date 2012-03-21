#ifndef MEASUREFILEH
#define MEASUREFILEH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace colorformat {

	class MeasureFile {
	};
	class RampMeasureFile:public ExcelAccessBase {
	  private:
	    static const std::string & Sheet1;
	    static const std::string & Sheet2;
	    int getMaximumSize(Component_vector_ptr wMeasureData,
			       Patch_vector_ptr rMeasureData,
			       Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData);
	    int getMaximumSize(Patch_vector_ptr wMeasureData,
			       Patch_vector_ptr rMeasureData,
			       Patch_vector_ptr gMeasureData, Patch_vector_ptr bMeasureData);
	    double_array getValues(XYZ_ptr XYZ, bool XYZMode);
	    void setMeasureData(Component_vector_ptr wMeasureData, Patch_vector_ptr wMeasureData2,
				Patch_vector_ptr rMeasureData, Patch_vector_ptr gMeasureData,
				Patch_vector_ptr bMeasureData, bool XYZMode);
	  public:
	     RampMeasureFile(const std::string & fileName, const Mode mode);
	     RampMeasureFile(const string_ptr fileName, const Mode mode);
	    void setMeasureData(Component_vector_ptr wMeasureData,
				Patch_vector_ptr rMeasureData, Patch_vector_ptr gMeasureData,
				Patch_vector_ptr bMeasureData);
	    void setMeasureData(Component_vector_ptr wMeasureData,
				Patch_vector_ptr rMeasureData, Patch_vector_ptr gMeasureData,
				Patch_vector_ptr bMeasureData, bool XYZMode);
	    void setMeasureData(Patch_vector_ptr wMeasureData,
				Patch_vector_ptr rMeasureData, Patch_vector_ptr gMeasureData,
				Patch_vector_ptr bMeasureData, bool XYZMode);

	};

	class IntensityMatrixFile:public ExcelAccessBase {
	  private:
	    void initSheet();
	    static const std::string & RSheet;
	    static const std::string & GSheet;
	    static const std::string & BSheet;
	  public:
	     IntensityMatrixFile(const std::string & filename);
	    void addIntensityVector(Component_vector_ptr intensityVector);
	};
    };
};


#endif

