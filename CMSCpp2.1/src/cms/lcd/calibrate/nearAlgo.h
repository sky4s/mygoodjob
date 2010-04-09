#ifndef NEARALGOH
#define NEARALGOH
//C系統文件

//C++系統文件
//#include <list>;
//#include <vector>;

//其他庫頭文件

//本項目內頭文件
#include "algo.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		class CIEuv1960NearestAlgorithm:public NearestAlgorithm {
		  public:
		    CIEuv1960NearestAlgorithm(XYZ_ptr white,
					      bptr <
					      cms::measure::
					      MeterMeasurement > mm);

		  protected:
		     double getIndex(XYZ_ptr center, XYZ_ptr around);
                        double_array getDelta(XYZ_ptr center, XYZ_ptr XYZ);
		};


		class CIEuv1960NearestAlgorithm_:public Algorithm {
		  private:
		    bptr < cms::measure::MeterMeasurement > mm;

		  protected:
		    XYZ_ptr white;

		     double_array getDelta(XYZ_ptr center,
						  XYZ_ptr XYZ);
		     bptr < cms::measure::MeasureResult >
			getMeasureResult(RGB_vector_ptr aroundRGB);
		     double getIndex(XYZ_ptr center,
					    XYZ_ptr around) ;
		  public:

		     double_array getDelta(XYZ_ptr XYZ, RGB_ptr rgb);
		     CIEuv1960NearestAlgorithm_(XYZ_ptr white,
				      bptr <
				      cms::measure::MeterMeasurement > mm);
		     bptr < AlgoResult > getNearestRGB(XYZ_ptr center,
						       RGB_vector_ptr
						       aroundRGB);
		};

	    };
	};
    };
};
#endif

