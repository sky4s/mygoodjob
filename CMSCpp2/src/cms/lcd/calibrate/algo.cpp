#include <includeall.h>
#pragma hdrstop
#include "algo.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		using namespace std;
		using namespace Dep;
		using namespace Indep;
		using namespace cms::measure::cp;
		using namespace cms::measure;
		using namespace cms;
		using namespace java::lang;

		//==============================================================
		// Algorithm
		//==============================================================
		bool Algorithm::isWhiteMode() {
		    return mode == White;
		};
		bool Algorithm::isGreenMode() {
		    return mode == Green;
		};

		void Algorithm::setMode(Mode mode) {
		    this->mode = mode;
		};
		 Algorithm::Algorithm():mode(Normal) {

		};
		//==============================================================
		// AlgoResult
		//==============================================================
		AlgoResult::AlgoResult(RGB_ptr nearestRGB,
				       double_vector_ptr indexes,
				       RGB_vector_ptr aroundRGB,
				       XYZ_vector_ptr aroundXYZ, int
				       indexInArray):nearestRGB
		    (nearestRGB), indexes(indexes), aroundRGB(aroundRGB),
		    aroundXYZ(aroundXYZ), indexInArray(indexInArray) {

		};
		//==============================================================

		//==============================================================

		//==============================================================
		// NearestAlgorithm
		//==============================================================
	      NearestAlgorithm::NearestAlgorithm(XYZ_ptr white, bptr < MeasureInterface > mi):white(white),
		    mi(mi)
		{
		};
		double_array NearestAlgorithm::getDelta(XYZ_ptr XYZ,
							RGB_ptr rgb) {
		    Patch_ptr p = mi->measure(rgb, false, false);
		    return getDelta(XYZ, p->getXYZ());
		}

		bptr < cms::measure::MeasureResult >
		    NearestAlgorithm::
		    getMeasureResult(RGB_vector_ptr aroundRGB) {
		    bptr < cms::measure::MeasureResult > measureResult =
			mi->measureResult(aroundRGB, false, false);
		    /*MeasureResult measureResult =
		       mi.measureResult(aroundRGB,
		       this.isForceTrigger(),
		       AutoCPOptions.get("CPM_MeasureRequestThanTrigger")); */
		    return measureResult;
		};

		bptr < AlgoResult >
		    NearestAlgorithm::getNearestRGB(XYZ_ptr center,
						    RGB_vector_ptr
						    aroundRGB) {
		    bptr < MeasureResult > measureResult =
			getMeasureResult(aroundRGB);
		    Patch_vector_ptr patchVec = measureResult->result;
		    int size = patchVec->size();
		    double_vector_ptr dist(new double_vector());

		    XYZ_vector_ptr aroundXYZ(new XYZ_vector());


		    for (int x = 0; x < size; x++) {
			Patch_ptr patch = (*patchVec)[x];
			XYZ_ptr XYZ = patch->getXYZ();
			aroundXYZ->push_back(XYZ);
			dist->push_back(getIndex(center, XYZ));

		    }
		    int index = Math::minIndex(dist);
		    RGB_ptr rgb = (*patchVec)[index]->getRGB();
		    bptr < AlgoResult >
			result(new AlgoResult(rgb, dist,
					      aroundRGB,
					      aroundXYZ, index));
		    return result;
		};

		//==============================================================

		//==============================================================
		// MeasuredUtils
		//==============================================================
		double_array MeasuredUtils::getDeltauvPrime(XYZ_ptr center,
							    XYZ_ptr XYZ) {
		    xyY_ptr centerxyY(new CIExyY(center));
		    xyY_ptr xyY(new CIExyY(XYZ));
		    return xyY->getDeltauvPrime(centerxyY);
		};
		bool MeasuredUtils::isFirstNearestXYZInuvPrime(XYZ_ptr
							       targetXYZ,
							       XYZ_vector_ptr
							       aroundXYZ) {
		    int size = aroundXYZ->size();
		    double_vector_ptr dists(new double_vector());
		    //double[] dists = new double[size];
		    for (int x = 0; x < size; x++) {
			double_array delta =
			    getDeltauvPrime(targetXYZ, (*aroundXYZ)[x]);
			double dist =
			    Math::sqrt(Math::sqr(delta[0]) +
				       Math::sqr(delta[1]));
			dists->push_back(dist);
		    }
		    return Math::minIndex(dists) == 0;
		};
		//==============================================================
	    };
	};
    };
};

