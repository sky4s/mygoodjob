//---------------------------------------------------------------------------
#ifndef CA210APIH
#define CA210APIH
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//其他庫頭文件
#include <CA200SRVRLib/CA200SRVRLib_TLB.h>
//#include <vcl.h>
//本項目內頭文件

//---------------------------------------------------------------------------

namespace ca210api {
    class CAMeasureResult:public jObject {
      public:

	float x, y, Lv;
	float X, Y, Z;
	long cct;
	float duv;
	float R, G, B;
	 CAMeasureResult();
	 CAMeasureResult(float R, float G, float B);
	 CAMeasureResult(float x, float y, float Lv, float X, float Y,
			 float Z, long cct, float duv);
	 CAMeasureResult(float x, float y, float Lv, float X, float Y,
			 float Z, long cct, float duv, float R, float G,
			 float B);
	float_array getxyYValues();
	float_array getXYZValues();
    };

    enum SyncMode { NTSC = 0, PAL, EXT, UNIV
    };
    enum AveragingMode { Slow = 0, Fast, Auto
    };
    enum BrightnessUnit { fL = 0, nits
    };
    enum DisplayMode { Lvxy =
	    0, Tdudv, Analyzer_nodisplay, AnalyzerG, AnalyzerR, uv,
	FMAflicker, XYZ, JEITAflicker
    };
    enum DisplayDigits { Display3digit = 0, Display4digit
    };
    enum CalStandard { D6500k = 0, D9300k
    };
    enum RemoteMode { Off = 0, On, Locked
    };
    enum lClr { Red = 0, Green, Blue, White
    };


    class CA210API:public jObject {
      private:
	ICa200Disp ca200;
	ICaDisp ca;
	IProbeDisp probe;
	IMemoryDisp memory;
	 bptr < CAMeasureResult > measureResult;
      public:

	 bptr < CAMeasureResult > getMeasureResult();
	 CA210API();
	~CA210API();
	void calibrate();

	void close();
	float_array triggerMeasurement();
	float_array triggerIntensityAnalyze();
	 bptr < CAMeasureResult > triggerMeasureResult();

	// Options
	void setSyncMode(SyncMode mode);
	void setAveragingMode(AveragingMode mode);

	void setBrightnessUnit(BrightnessUnit unit);
	void setDisplayMode(DisplayMode mode);

	void setDisplayDigits(DisplayDigits digits);
	void setCalStandard(CalStandard standard);
	void setRemoteMode(RemoteMode mode);
	// Analyzer Mode
	void setAnalyzerCalMode();
	void resetAnalyzerCalMode();

	void setAnalyzerCalData(lClr lclr);
	void setLvxyCalMode();
	void resetLvxyCalMode();
	void setLvxyCalData(lClr lclr, float xValue, float yValue,
			    float YValue);

	void setLvxyCalData(lClr lclr, float_array xyYValue);
	void setLvxyCalData(lClr lclr, double_array xyYValue);

	long enter();

	// Channel NO
	void setChannelNO(int no);

	long getChannelNO();
	// channel ID
	void setChannelID(wchar_t * id);
	void setChannelID(const WideString & id);
	//void setChannelID(const std::string & id);

	wchar_t *getChannelID();
	//void copyToFile(const std::string & filename);
	//void copyFromFile(const std::string & filename);
	void copyToFile(const WideString & filename);
	void copyFromFile(const WideString & filename);
    };
};
#endif

