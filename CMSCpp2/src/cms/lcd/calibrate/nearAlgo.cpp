#include "nearAlgo.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/colorspace/rgb.h>
#include <cms/measure/cp.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		using namespace cms::measure::cp;
		using namespace java::lang;
		 CIEuv1960NearestAlgorithm::
		    CIEuv1960NearestAlgorithm(XYZ_ptr white,
					      MeasureInterface &
					      mi):NearestAlgorithm(white,
								   mi) {
		};
		double_array CIEuv1960NearestAlgorithm::
		    getDelta(XYZ_ptr center, XYZ_ptr XYZ) {
		    return MeasuredUtils::getDeltauvPrime(center, XYZ);
		};
		double CIEuv1960NearestAlgorithm::getIndex(XYZ_ptr center,
							   XYZ_ptr around)
		{
		    double_array duvp = getDelta(center, around);
		    double de =
			Math::sqrt(Math::sqr(duvp[0]) +
				   Math::sqr(duvp[1]));
		     return de;
		};

	    };
	};
    };
};

