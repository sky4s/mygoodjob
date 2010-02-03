#ifndef ALGOH
#define ALGOH
//C系統文件

//C++系統文件
//#include <list>;
#include <vector>;

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		enum Mode {
		    White, Green, Normal
		};
		class Algorithm {
		  private:
		    Mode mode;
		  protected:
		    bool isWhiteMode();
		    bool isGreenMode();
		  public:
		    void setMode(Mode mode);
		};

		class AroundAlgorithm:public Algorithm {
		  public:
		    virtual RGB_vector_ptr getAroundRGB(RGB_ptr centerRGB, double
							step) = 0;

		    virtual RGB_vector_ptr
			getAroundRGB(RGB_ptr centerRGB, double_array delta,
				     double step) = 0;
		};

		class AlgoResult:public jObject {

		};

		class NearestAlgorithm:public Algorithm {
		  private:
		    bptr < cms::measure::cp::MeasureInterface > mi;

		  protected:
		    XYZ_ptr white;

		    virtual double_array getDelta(XYZ_ptr center,
						  XYZ_ptr XYZ) = 0;
		     bptr < cms::measure::MeasureResult >
			getMeasureResult(RGB_vector_ptr aroundRGB);
		    virtual double getIndex(XYZ_ptr center,
					    XYZ_ptr around) = 0;
		  public:
		     bptr < AlgoResult > getNearestRGB(XYZ_ptr center,
						       RGB_vector_ptr
						       rgbVec,
						       int lastCount);
		    double_array getDelta(XYZ_ptr XYZ, RGB_ptr rgb);
		     NearestAlgorithm(XYZ_ptr white,
				      bptr < cms::measure::cp::
				      MeasureInterface > mi);
		     bptr < AlgoResult > getNearestRGB(XYZ_ptr center,
						       RGB_vector_ptr
						       aroundRGB);
		};

		class MeasuredUtils {
		  public:
		    static double_array getDeltauvPrime(XYZ_ptr center,
							XYZ_ptr XYZ);
		};
	    };
	};
    };
};
#endif

