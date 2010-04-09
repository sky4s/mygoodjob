#ifndef AROUNDALGOH
#define AROUNDALGOH
//C系統文件

//C++系統文件
//#include <list>;
#include <vector>;

//其他庫頭文件

//本項目內頭文件
#include "algo.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {

		class StepAroundAlgorithm:public AroundAlgorithm {
		  private:
		    RGB_vector_ptr
			rgbAdjust(channel_vector_ptr channels,
				  Dep::Channel & maxChannel,
				  RGB_ptr centerRGB, double adjustStep,
				  double_array delta);

		     RGB_vector_ptr
			whiteAdjust(Dep::Channel & maxChannel,
				    RGB_ptr centerRGB, double adjustStep);
		  protected:
		     virtual bool checkAdjustable(RGB_ptr rgb, double step,
						  const Dep::
						  Channel & maxChannel,
						  const Dep::
						  Channel & adjustChannel,
						  double_array delta);
		     RGB_vector_ptr
			getChromaticExpandAround(RGB_ptr centerRGB,
						 double_array delta, double
						 step);
		    bool whiteCheckAdjustable(RGB_ptr rgb, double step,
					      Dep::Channel & maxChannel);
		    static bool ChromaticSkipByDelta;
		    double maxCode;
		  public:
		     virtual RGB_vector_ptr getAroundRGB(RGB_ptr centerRGB,
							 double_array
							 delta,
							 double step) = 0;
		    virtual RGB_vector_ptr getAroundRGB(RGB_ptr centerRGB,
							double step) = 0;
		     StepAroundAlgorithm();
		};

		class ChromaticAroundAlgorithm:public StepAroundAlgorithm {
		  protected:
		    virtual bool checkAdjustable(RGB_ptr rgb, double step,
						 const Dep::
						 Channel & maxChannel,
						 const Dep::
						 Channel & adjustChannel,
						 double_array delta);
		  public:
		     RGB_vector_ptr getAroundRGB(RGB_ptr centerRGB,
						 double_array delta,
						 double step);
		    RGB_vector_ptr getAroundRGB(RGB_ptr centerRGB,
						double step);
		};
	    };
	};
    };
};
#endif

