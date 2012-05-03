#ifndef DGCODEFILEH
#define DGCODEFILEH
//C系統文件

//C++系統文件
#include <string>
//其他庫頭文件
#include <ADODB.hpp>
#include <DB.hpp>
//本項目內頭文件
#include <java/lang.h>
#include "excelfile.h"

namespace cms {
    namespace colorformat {
	using namespace std;

	class DGLutProperty;
	class DGLutFile:public ExcelAccessBase {
	  private:
	    string_vector_ptr makeValues(int n, Component_ptr c);
	    string_vector_ptr makeValues(int n,
					 Component_ptr c, RGB_ptr rgbGamma,
					 RGB_ptr rgbGammaFix);
	    static const std::string & RawData;
	    static const std::string & Target;
	    static const std::string & LCDTarget;
	    const Dep::MaxValue & maxValue;
	    void init();
	    Component_vector_ptr getComponentVector(bool rgbFromGammaTable,
						    int max);
	  public:
	     DGLutFile(const std::string & filename, Mode mode);
	     DGLutFile(const std::string & filename, Mode mode,
		       const Dep::MaxValue & maxValue);


	    void setProperty(const DGLutProperty & property);
	     bptr < DGLutProperty > getProperty();


	    void setRawData(Component_vector_ptr componentVector,
			    RGBGamma_ptr initialRGBGamma,
			    RGBGamma_ptr finalRGBGamma);

	    void setTargetXYZVector(XYZ_vector_ptr targetXYZVector);
	    void setTargetXYZVector(XYZ_vector_ptr targetXYZVector,
				    RGB_vector_ptr dglut,
				    bptr < cms::lcd::BitDepthProcessor >
				    bitDepth);
	    void setLCDTarget(LCDTarget_ptr lcdTarget);
	    LCDTarget_ptr getLCDTarget();
	    Component_vector_ptr getComponentVector();
	    RGB_vector_ptr getGammaTable();
	    /*
	       量測的資料不見得是0~255全量, 但是產生的gamma一定是全部
	       該如何整合兩者?兩種作法
	       1. 內插量測值, 使資料為0~255
	       2. 取有量測到的gamma, 但是缺乏的gamma..就缺乏吧...
	       反正產生DG Code的時候還是可以生出來.

	       選擇方案二, 所以不用刻意去縮減rgbgamma, 由setRawData自己去篩 */
	};

	class DGLutProperty {
	    friend class DGLutFile;
	    friend class RampMeasureFile;
	  private:

	    static const std::string On;
	    static const std::string Off;

	    static const std::string TargetWhiteRatio;
	    static const std::string WhiteRatio;
	    static std::string fileVersion;
	    static std::string productVersion;

	     cms::lcd::calibrate::LCDCalibrator * c;
	     bptr < DGLutFile > d;
	    void store(ExcelAccessBase & dglut) const;
	    void DGLutProperty::storeAnalyzer(ExcelAccessBase & dgfile,
					      bptr <
					      cms::measure::
					      IntensityAnalyzerIF >
					      analyzer,
					      const string & prestring)
		const;
	     std::map < const std::string, string_ptr) propertyMap;
	    void addProperty(const std::string key, string_ptr value);
	    void addProperty(const std::string key,
			     const std::string value);
	    bool initProperty(bptr < DGLutFile > d);
	    bool initProperty(DGLutFile * d);
	    xyY_ptr getReferenceColor(const string & prestring,
				      const Dep::Channel & ch);
	  public:
	    static const std::string Native;
	    static const std::string Target;
	    static const std::string Second;
	     DGLutProperty(cms::lcd::calibrate::LCDCalibrator * c);
	     DGLutProperty(bptr < DGLutFile > d);
	     DGLutProperty(DGLutFile * d);
	    string_ptr getProperty(const std::string key);

	    xyY_ptr getTargetReferenceColor(const Dep::Channel & ch);
	    xyY_ptr getNativeReferenceColor(const Dep::Channel & ch);
	    xyY_ptr getSecondReferenceColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB(const string & prestring);
	    RGB_ptr getTargetReferenceRGB();
	    RGB_ptr getNativeReferenceRGB();
	    RGB_ptr getSecondReferenceRGB();
	     bptr < cms::lcd::BitDepthProcessor > getBitDepthProcessor();
	    double_array getTargetWhiteRatio();
	};
    };
};
#endif

