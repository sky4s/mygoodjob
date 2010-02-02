#ifndef ALGOH
#define ALGOH
//C系統文件

//C++系統文件
#include <list>;
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
		    virtual barray < Dep::RGBColor > getAroundRGB(bptr <
								  Dep::
								  RGBColor
								  >
								  centerRGB,
								  double
								  step) =
			0;

		    virtual barray < Dep::RGBColor > getAroundRGB(bptr <
								  Dep::
								  RGBColor
								  >
								  centerRGB,
								  double_array
								  delta,
								  double
								  step) =
			0;

		};

		class StepAroundAlgorithm:public AroundAlgorithm {
		  private:
		    std::list < Dep::RGBColor >
			rgbAdjust(channel_vector_ptr channels,
				  Dep::Channel & maxChannel,
				  bptr < Dep::RGBColor > centerRGB, double
				  adjustStep, double_array delta);

		     std::list < Dep::RGBColor > whiteAdjust(Dep::
							     Channel &
							     maxChannel,
							     bptr <
							     Dep::
							     RGBColor >
							     centerRGB,
							     double
							     adjustStep);
		  protected:
		     bool checkAdjustable(bptr <
					  Dep::RGBColor > rgb, double step,
					  Dep::
					  Channel & maxChannel,
					  Dep::
					  Channel & adjustChannel,
					  double_array delta);
		     std::list < Dep::RGBColor >
			getChromaticExpandAround(bptr < Dep::RGBColor >
						 centerRGB,
						 double_array delta, double
						 step);
		    bool whiteCheckAdjustable(bptr <
					      Dep::
					      RGBColor
					      > rgb, double step,
					      Dep::Channel & maxChannel);
		  public:
		     barray < Dep::RGBColor > getAroundRGB(bptr <
							   Dep::RGBColor >
							   centerRGB,
							   double_array
							   delta,
							   double step,
							   bool
							   involveWhite);
		     barray < Dep::RGBColor > getAroundRGB(bptr <
							   Dep::RGBColor >
							   centerRGB,
							   double_array
							   delta,
							   double step);
		     barray < Dep::RGBColor > getAroundRGB(bptr <
							   Dep::RGBColor >
							   centerRGB,
							   double step,
							   bool
							   involeWhite);
		     barray < Dep::RGBColor > getAroundRGB(bptr <
							   Dep::RGBColor >
							   centerRGB,
							   double step);
		    void setChromaticExpandMode(bool chromaticExpandMode);
		};

		class ChromaticAroundAlgorithm:public StepAroundAlgorithm {
		  protected:
		    bool checkAdjustable(bptr <
					 Dep::RGBColor > rgb, double step,
					 Dep::Channel & maxChannel,
					 Dep::Channel & adjustChannel,
					 double_array delta);
		     barray < Dep::RGBColor > getAroundRGB(bptr <
							   Dep::RGBColor >
							   centerRGB,
							   double_array
							   delta,
							   double step);
		     barray < Dep::RGBColor > getAroundRGB(bptr <
							   Dep::RGBColor >
							   centerRGB,
							   double step);
		};
	    };
	};
    };
};
#endif

