#include <includeall.h>
#pragma hdrstop
#include "dimdg.h"


//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::colorformat;
	    Component_vector_ptr DimDGLutGenerator::fetchComponent(bptr <
								   MaxMatrixIntensityAnayzer
								   >
								   analyzer,
								   Component_vector_ptr
								   componentVector)
	    {
		Component_vector_ptr result(new Component_vector());

		 foreach(const Component_ptr c, *componentVector) {
		    RGB_ptr intensity = analyzer->getIntensity(c->XYZ);
		    Component_ptr component(new
					    Component(c->rgb, intensity,
						      c->XYZ));
		     result->push_back(component);
		};
		 return result;
	    };
	    XYZ_vector_ptr DimDGLutGenerator::getTarget(XYZ_ptr startXYZ,
							XYZ_ptr endXYZ,
							double_vector_ptr
							luminanceGammaCurve)
	    {
		XYZ_vector_ptr targetXYZVector =
		    DimTargetGenerator::
		    getLinearTarget(startXYZ, endXYZ, luminanceGammaCurve);
		 return targetXYZVector;
	    };
	    /*void DimDGLutGenerator::
	       storeXYZxyVector(XYZ_vector_ptr XYZVector) {

	       Util::deleteExist("target.xls");
	       SimpleExcelAccess excel("target.xls", Create,
	       StringVector::
	       fromCString(6, "Gray Level",
	       "X", "Y", "Z",
	       "_x", "_y"));
	       int size = XYZVector->size();
	       for (int x = 0; x != size; x++) {
	       XYZ_ptr XYZ = (*XYZVector)[x];
	       Indep::CIExyY xyY(XYZ);
	       string_vector_ptr values = StringVector::fromDouble
	       (6, static_cast < double >(x), XYZ->X, XYZ->Y,
	       XYZ->Z, xyY.x, xyY.y);
	       excel.insert(values);
	       }
	       }; */
	  DimDGLutGenerator::DimDGLutGenerator(Component_vector_ptr componentVector, bptr < IntensityAnalyzerIF > analyzer):componentVector(componentVector),
		analyzer(analyzer)
	    {
	    };
	    RGB_vector_ptr DimDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int under) {
		using namespace Dep;
		//==============================================================
		// 資訊準備
		//==============================================================
		XYZ_ptr blackXYZ = (*componentVector)
		    [componentVector->size() - 1]->XYZ;
		int size = under - 1;
		double_vector_ptr partGammaCurve =
		    DoubleArray::getRangeCopy(luminanceGammaCurve,
					      0, size);
		//求目標值曲線
		XYZ_vector_ptr targetXYZVector =
		    getTarget(blackXYZ, targetWhite,
			      partGammaCurve);
		STORE_XYZXY_VECTOE("target.xls", targetXYZVector);
		//==============================================================
		RGB_vector_ptr result(new RGB_vector());
		//primary color只能用target white~
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);
		int x = 0;
		x;
		foreach(const XYZ_ptr targetXYZ, *targetXYZVector) {
		    bptr < MaxMatrixIntensityAnayzer >
			analyzer(new MaxMatrixIntensityAnayzer());
		    analyzer->setupComponent(Channel::R, rxyY->toXYZ());
		    analyzer->setupComponent(Channel::G, gxyY->toXYZ());
		    analyzer->setupComponent(Channel::B, bxyY->toXYZ());
		    analyzer->setupComponent(Channel::W, targetXYZ);
		    analyzer->enter();
		    Component_vector_ptr
			newcomponentVector =
			fetchComponent(analyzer, componentVector);
		    //STORE_COMPONENT(_toString(x++) + ".xls",
		    //newcomponentVector);
		    DGLutGenerator lutgen(newcomponentVector);
		    //採100嗎?
		    RGB_ptr rgb = lutgen.getDGCode(100, 100, 100);
		    result->push_back(rgb);
		};
		return result;
	    };
	};
    };
};

