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
	/*
	   Intensity Analyer的皮
	   Analyzer的功用就是從XYZ分析出Intensity
	 */
	class IntensityAnalyzerIF:public jObject {
	  public:
	    virtual RGB_ptr getIntensity(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual XYZ_ptr getCIEXYZOnly(RGB_ptr rgb) = 0;
	    virtual void setupComponent(const Dep::Channel & ch,
					RGB_ptr rgb) = 0;
	    virtual void enter() = 0;
	    virtual void beginAnalyze() = 0;
	    virtual void endAnalyze() = 0;
	    virtual void setWaitTimes(int waitTimes) = 0;
	    virtual int getWaitTimes() = 0;
	    virtual xyY_ptr getReferenceColor() = 0;
	    virtual xyY_ptr getPrimaryColor(const Dep::Channel & ch) = 0;
	    virtual RGB_ptr getReferenceRGB() = 0;
	};

	/*
	   利用CA-210內建的Analyzer Mode分析 Intensity
	 */
	class CA210IntensityAnalyzer:public IntensityAnalyzerIF {
	  private:
	    Patch_ptr rp, gp, bp, wp;
	  protected:
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	    XYZ_ptr XYZ;
	     bptr < MeterMeasurement > mm;
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
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id);
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	};

	/*
	   利用矩陣運算推算出Intensity
	 */
	class MaxMatrixIntensityAnayzer:public IntensityAnalyzerIF {
	    friend class IntensityAnayzer;
	  private:
	     double2D_ptr inverseMatrix;
	    double2D_ptr targetRatio;
	    double2D_ptr rgbValues;
	  protected:
	     bptr < MeterMeasurement > mm;
	    XYZ_ptr XYZ;
	    XYZ_ptr rXYZ, gXYZ, bXYZ, wXYZ;
	    RGB_ptr referenceRGB;

	  public:
	     MaxMatrixIntensityAnayzer(bptr < MeterMeasurement > mm);
	     MaxMatrixIntensityAnayzer();

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    RGB_ptr getIntensity(XYZ_ptr XYZ);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch,
				XYZ_ptr measureXYZ);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	};

	/*
	   用來合併CA-210與MaxMatrix兩種方法來分析Intensity
	   實際上輸出的值為CA-210的, MaxMatrix的輸出值會另外存在檔案
	 */
	class IntensityAnayzer:public IntensityAnalyzerIF {
	  private:
	    bptr < MaxMatrixIntensityAnayzer > matrix;
	    bptr < CA210IntensityAnalyzer > ca210;
	    bptr < cms::colorformat::SimpleExcelAccess > excel;
	    string_vector_ptr fieldNames;
	    int no;
	    XYZ_ptr XYZ;
	  public:
	     IntensityAnayzer(bptr < MaxMatrixIntensityAnayzer > matrix,
			      bptr < CA210IntensityAnalyzer > ca210);
	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	};

	/*
	   以float進行矩陣運算, 問題多多不能使用
	 */
	/*class MaxMatrixIntensityAnayzer2:public MaxMatrixIntensityAnayzer {
	   friend class IntensityAnayzer;
	   protected:
	   float2D_ptr inverseMatrix2;
	   float2D_ptr targetRatio2;
	   float2D_ptr rgbValues2;
	   public:
	   MaxMatrixIntensityAnayzer2(bptr < MeterMeasurement > mm);
	   void enter();
	   RGB_ptr getIntensity(XYZ_ptr XYZ);
	   RGB_ptr getIntensity(RGB_ptr rgb);
	   }; */
    };
};
#endif

