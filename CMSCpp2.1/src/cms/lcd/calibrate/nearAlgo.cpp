#include <includeall.h>
#pragma hdrstop
#include "nearAlgo.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {

		using namespace cms::measure;
		using namespace java::lang;
		 CIEuv1960NearestAlgorithm::
		    CIEuv1960NearestAlgorithm(XYZ_ptr white,
					      bptr < MeterMeasurement >
					      mm):NearestAlgorithm(white,
								   mm) {
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


		//==============================================================
		// CIEuv1960NearestAlgorithm_
		//==============================================================
		/*double_array CIEuv1960NearestAlgorithm_::
		   getDelta(XYZ_ptr center, XYZ_ptr XYZ) {
		   return MeasuredUtils::getDeltauvPrime(center, XYZ);
		   };
		   double CIEuv1960NearestAlgorithm_::getIndex(XYZ_ptr center,
		   XYZ_ptr around)
		   {
		   double_array duvp = getDelta(center, around);
		   double de =
		   Math::sqrt(Math::sqr(duvp[0]) +
		   Math::sqr(duvp[1]));
		   return de;
		   };

		   //==============================================================
		   // CIEuv1960NearestAlgorithm_
		   //==============================================================
		   CIEuv1960NearestAlgorithm_::CIEuv1960NearestAlgorithm_(XYZ_ptr white, bptr < cms::measure::MeterMeasurement > mm):white(white),
		   mm(mm)
		   {
		   };
		   double_array CIEuv1960NearestAlgorithm_::
		   getDelta(XYZ_ptr XYZ, RGB_ptr rgb) {
		   //Patch_ptr p = mi->measure(rgb, false, false);
		   Patch_ptr p = mm->measure(rgb, rgb->toString());
		   return getDelta(XYZ, p->getXYZ());
		   }

		   bptr < cms::measure::MeasureResult >
		   CIEuv1960NearestAlgorithm_::
		   getMeasureResult(RGB_vector_ptr aroundRGB) {
		   //this->mm;

		   int size = aroundRGB->size();
		   Patch_vector_ptr result(new Patch_vector());

		   foreach(RGB_ptr rgb, *aroundRGB) {
		   Patch_ptr p = mm->measure(rgb, rgb->toString());
		   result->push_back(p);
		   };

		   bptr < MeasureResult >
		   measureResult(new MeasureResult(result, size));
		   return measureResult;

		   };

		   bptr < AlgoResult >
		   CIEuv1960NearestAlgorithm_::
		   getNearestRGB(XYZ_ptr center,
		   RGB_vector_ptr aroundRGB) {
		   this->mm;
		   bptr < MeasureResult > measureResult =
		   getMeasureResult(aroundRGB);
		   Patch_vector_ptr patchVec = measureResult->result;
		   int size = patchVec->size();
		   double_vector_ptr dist(new double_vector());

		   XYZ_vector_ptr aroundXYZ(new XYZ_vector());

		   foreach(Patch_ptr patch, *patchVec) {
		   XYZ_ptr XYZ = patch->getXYZ();
		   aroundXYZ->push_back(XYZ);
		   double index = this->getIndex(center, XYZ);
		   dist->push_back(index);
		   }
		   int minIndex = Math::minIndex(dist);
		   RGB_ptr rgb = (*patchVec)[minIndex]->getRGB();
		   bptr < AlgoResult >
		   result(new AlgoResult(rgb, dist,
		   aroundRGB,
		   aroundXYZ, minIndex));
		   return result;
		   }; */

		//==============================================================


	    };
	};
    };
};

