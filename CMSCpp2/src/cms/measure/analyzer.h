#ifndef ANALYZERH
#define ANALYZERH

//C系統文件

//C++系統文件

//其他庫頭文件
#include <vcl.h>

//本項目內頭文件
#include <java/lang.h>

namespace ca210api {
    class CA210API;
};

namespace cms {

    namespace measure {

	class MeterMeasurement;
	class ComponentAnalyzerIF:public jObject {
	  public:
	    virtual RGB_ptr getComponent(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    virtual void enter() = 0;
	};

	class CA210ComponentAnalyzer:public ComponentAnalyzerIF {
	  protected:
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	    XYZ_ptr XYZ;
	     bptr < MeterMeasurement > mm;
	    static const WideString & CalibrationDataFilename;
	    bool dummyMode;
	    void init();
	     cms::measure::meter::DGCodeFileMeter * dgc;
	  public:

	    /*CA210ComponentAnalyzer(bptr < cms::measure::meter::CA210 >
	       ca210); */
	    /*
	       採用CA210為analyze結果的來源
	     */
	     CA210ComponentAnalyzer(bptr < cms::measure::meter::CA210 >
				    ca210, bptr < MeterMeasurement > mm);
	    /*
	       由於缺乏CA210, 因此是以MeterMeasurement中的Meter作為analyze來源,
	       實際上是假設Meter為DGCodeFileMeter, 也就是說讀取檔案中的component作為analyze結果
	     */
	     CA210ComponentAnalyzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getComponent(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id);
	};

	class StocktonComponentAnayzer:public CA210ComponentAnalyzer {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  public:
	    StocktonComponentAnayzer(bptr < cms::measure::meter::CA210 >
				     ca210, bptr < MeterMeasurement > mm);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	};

	class MaxMatrixComponentAnalyzer:public ComponentAnalyzerIF {
	  private:
	    const Dep::RGBColorSpace & rgbColorSpace;
	  public:
	     MaxMatrixComponentAnalyzer(const Dep::RGBColorSpace &
					rgbColorSpace);

	    RGB_ptr getComponent(RGB_ptr rgb) = 0;
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb) = 0;
	    void enter();
	};
    };
};
#endif

