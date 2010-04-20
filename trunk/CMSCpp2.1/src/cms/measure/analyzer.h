#ifndef ANALYZERH
#define ANALYZERH

//C系統文件

//C++系統文件

//其他庫頭文件
#include <vcl.h>

//本項目內頭文件
#include <cms/colorformat/excelfile.h>

namespace cms {

    namespace measure {

	class MeterMeasurement;
	class IntensityAnalyzerIF:public jObject {
	  public:
	    virtual RGB_ptr getIntensity(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    virtual void enter() = 0;
	    virtual void beginAnalyze() = 0;
	    virtual void endAnalyze() = 0;
	    virtual void setWaitTimes(int waitTimes) = 0;
	    virtual void setDefaultWaitTimes() = 0;
	};

	class CA210IntensityAnalyzer:public IntensityAnalyzerIF {
	  protected:
	    int defaultWaitTimes;
	     bptr < cms::measure::meter::CA210 > ca210;
	     bptr < ca210api::CA210API > ca210api;
	    XYZ_ptr XYZ;
	     bptr < MeterMeasurement > mm;
	    //static const WideString & CalibrationDataFilename;
	    bool dummyMode;
	    void init();
	     cms::measure::meter::DGLutFileMeter * dgc;
	  public:

	    /*
	       採用CA210為analyze結果的來源
	     */
	     CA210IntensityAnalyzer(bptr < cms::measure::meter::CA210 >
				    ca210, bptr < MeterMeasurement > mm);
	    /*
	       由於缺乏CA210, 因此是以MeterMeasurement中的Meter作為analyze來源,
	       實際上是假設Meter為DGLutFileMeter, 也就是說讀取檔案中的component作為analyze結果
	     */
	     CA210IntensityAnalyzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id, bool reset);
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    void setDefaultWaitTimes();
	};

	class StocktonIntensityAnayzer:public CA210IntensityAnalyzer {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  public:
	    StocktonIntensityAnayzer(bptr < cms::measure::meter::CA210 >
				     ca210, bptr < MeterMeasurement > mm);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	};

	class MaxMatrixIntensityAnayzer:public IntensityAnalyzerIF {
	    friend class IntensityAnayzer;
	  private:
	    static const std::string & CoefficientFilename;
	  protected:
	     bptr < MeterMeasurement > mm;
	    double2D_ptr inverseMatrix;
	    double2D_ptr targetRatio;
	    Patch_ptr rPatch;
	    Patch_ptr gPatch;
	    Patch_ptr bPatch;
	    Patch_ptr wPatch;
	    XYZ_ptr XYZ;
	    XYZ_ptr rXYZ, gXYZ, bXYZ, wXYZ;
	    int defaultWaitTimes;
	    double2D_ptr rgbValues;
	  public:
	     MaxMatrixIntensityAnayzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    RGB_ptr getIntensity(XYZ_ptr XYZ);
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch,
				XYZ_ptr measureXYZ);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    void setDefaultWaitTimes();
	};


	class IntensityAnayzer:public IntensityAnalyzerIF {
	  private:
	    bptr < MaxMatrixIntensityAnayzer > matrix;
	    bptr < CA210IntensityAnalyzer > ca210;
	    bptr < cms::colorformat::SimpleExcelAccess > excel;
	    string_vector_ptr fieldNames;
	    int no;
	  public:
	     IntensityAnayzer(bptr < MaxMatrixIntensityAnayzer > matrix,
			      bptr < CA210IntensityAnalyzer > ca210);
	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    void setDefaultWaitTimes();
	};


	class MaxMatrixIntensityAnayzer2:public MaxMatrixIntensityAnayzer {
	  protected:
	    float2D_ptr inverseMatrix;
	    float2D_ptr targetRatio;
	    float2D_ptr rgbValues;
	  public:
	     MaxMatrixIntensityAnayzer2(bptr < MeterMeasurement > mm);
	    void enter();
	    RGB_ptr getIntensity(XYZ_ptr XYZ);
	};
    };
};
#endif

