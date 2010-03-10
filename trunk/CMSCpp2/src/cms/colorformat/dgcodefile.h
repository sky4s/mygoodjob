#ifndef DGCODEFILEH
#define DGCODEFILEH
//C系統文件

//C++系統文件

//其他庫頭文件
#include <ADODB.hpp>
#include <DB.hpp>
//本項目內頭文件
#include <java/lang.h>
#include "excelfile.h"

namespace cms {
    namespace colorformat {
	class DGCodeProperty;
	class DGCodeFile {
	  private:
	    bptr < ExcelFileDB > db;
	    const Mode mode;
	    void init();
	    void initDefaultData(string_vector_ptr fieldNames,
				 const std::string & tableName, int n,
				 bool reverse);
	    void initDefaultData(string_vector_ptr fieldNames,
				 const std::string & tableName,
				 int_vector_ptr nvector, bool reverse);
	    const int n;
	    const int_vector_ptr nvector;
	    static string_vector_ptr getFieldNames(const std::string *
						   fieldNames, int n);
	    const std::string & filename;
	    bool lazyMode;
	  public:
	    static const std::string GammaHeader[4];
	    static const std::string RawHeader[13];
	    static const std::string PropertiesHeader[2];
	    static const std::string & GammaTable;
	    static const std::string & RawData;
	    static const std::string & Properties;
	    static string_vector_ptr GammaFieldNames;
	    static string_vector_ptr RawFieldNames;
	    static string_vector_ptr PropertiesFieldNames;
	     DGCodeFile(const std::string & filename, int n);
	     DGCodeFile(const std::string & filename,
			int_vector_ptr nvector);
	     DGCodeFile(const std::string & filename);
	    void addProperty(const std::string & key,
			     const std::string & value);
	    void addProperty(const std::string & key, const double value);
	    void setProperty(const DGCodeProperty & property);

	    void setRawData(Composition_vector_ptr compositionVector);
	    void setRawData(Composition_vector_ptr compositionVector,
			    RGBGamma_ptr rgbgamma);
	    void setGammaTable(RGB_vector_ptr dgcode);
	    Composition_vector_ptr getCompositionVector();

	    /*
	       量測的資料不見得是0~255全量, 但是產生的gamma一定是全部
	       該如何整合兩者?兩種作法
	       1. 內插量測值, 使資料為0~255
	       2. 取有量測到的gamma, 但是缺乏的gamma..就缺乏吧...
	       反正產生DG Code的時候還是可以生出來.

	       選擇方案二, 所以不用刻意去縮減rgbgamma, 由setRawData自己去篩
	     */

	  private:
	     string_vector_ptr makeValues(int n, Composition_ptr c);
	    string_vector_ptr makeValues(int n, Composition_ptr c,
					 RGB_ptr rgbGamma,
					 RGB_ptr rgbGammaFix);
	};

	class DGCodeProperty {
	    friend class DGCodeFile;
	  private:
	    static const std::string Start;
	    static const std::string End;
	    static const std::string Step;
	    static const std::string P1P2;
	    static const std::string P1;
	    static const std::string P2;
	    static const std::string RB;
	    static const std::string RBUnder;
	    static const std::string In;
	    static const std::string LUT;
	    static const std::string Out;
	    static const std::string Gamma;
	    static const std::string RGamma;
	    static const std::string GGamma;
	    static const std::string BGamma;
	    static const std::string GammaCurve;
	    static const std::string GByPass;
	    static const std::string BGain;
	    static const std::string BMax;
	    static const std::string Gamma256;
	    static const std::string FRC_NR;
	    const cms::lcd::calibrate::LCDCalibrator & c;
	    void store(DGCodeFile & dgcode) const;
	  public:
	     DGCodeProperty(const cms::lcd::calibrate::LCDCalibrator & c);
	};
    };
};
#endif

