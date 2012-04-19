#ifndef ANALYZERH
#define ANALYZERH

//C�t�Τ��

//C++�t�Τ��
#include <string>
//��L�w�Y���
#include <vcl.h>

//�����ؤ��Y���
#include <cms/colorformat/excelfile.h>
//#include "maxmatrixanalyzer.h"

#define CA210DAT "ca210.dat"
#define INTENSITY_FILE "intensity.xls"

namespace ca210api {
    class CA210API;
};

namespace cms {

    namespace measure {
	using namespace std;

	class MeterMeasurement;
	/*
	   Intensity Analyer����
	   Analyzer���\�δN�O�qXYZ���R�XIntensity
	 */
	class IntensityAnalyzerIF:public jObject {
	  private:
	    string_ptr comment;
	  public:
	    virtual RGB_ptr getIntensity(RGB_ptr rgb) = 0;
	    virtual XYZ_ptr getCIEXYZ() = 0;
	    virtual XYZ_ptr getCIEXYZOnly(RGB_ptr rgb) = 0;
	    virtual void setupComponent(const Dep::Channel & ch, RGB_ptr rgb) = 0;
	    void setReferenceColorComment(const string & comment);
	    string_ptr getReferenceColorComment();
	    virtual void enter() = 0;
	    virtual void beginAnalyze() = 0;
	    virtual void endAnalyze() = 0;
	    virtual void setWaitTimes(int waitTimes) = 0;
	    virtual int getWaitTimes() = 0;
	    virtual xyY_ptr getReferenceColor() = 0;
	    virtual xyY_ptr getPrimaryColor(const Dep::Channel & ch) = 0;
	    virtual RGB_ptr getReferenceRGB() = 0;
	    virtual bptr < MeterMeasurement > getMeterMeasurement() = 0;
	};

	/*
	   �Q��CA-210���ت�Analyzer Mode���R Intensity
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
	       �ĥ�CA210��analyze���G���ӷ�
	     */
	     CA210IntensityAnalyzer(bptr < cms::measure::meter::CA210 >
				    ca210, bptr < MeterMeasurement > mm);
	    /*
	       �ѩ�ʥFCA210, �]���O�HMeterMeasurement����Meter�@��analyze�ӷ�,
	       ��ڤW�O���]Meter��DGLutFileMeter, �]�N�O��Ū���ɮפ���component�@��analyze���G
	     */
	     CA210IntensityAnalyzer(bptr < MeterMeasurement > mm);

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void setChannel(int no, string_ptr id);
	    void setChannel(int no);
	    int getChannelNO();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	     bptr < MeterMeasurement > getMeterMeasurement();
	};

    };
};
#endif

