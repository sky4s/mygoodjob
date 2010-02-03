#ifndef NEARALGOH
#define NEARALGOH
//C系統文件

//C++系統文件
//#include <list>;
//#include <vector>;

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "algo.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		class CIEuv1960NearestAlgorithm:public NearestAlgorithm {
		  public:
		    CIEuv1960NearestAlgorithm(XYZ_ptr white,
					      cms::measure::cp::
					      MeasureInterface & mi);
		    double_array getDelta(XYZ_ptr center, XYZ_ptr XYZ);
		  protected:
		    double getIndex(XYZ_ptr center, XYZ_ptr around);
		};
	    };
	};
    };
};
#endif

