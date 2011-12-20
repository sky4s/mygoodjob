#ifndef MEASUREFILEH
#define MEASUREFILEH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


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
    };
};


#endif

