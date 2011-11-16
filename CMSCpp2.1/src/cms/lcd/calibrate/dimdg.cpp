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
	    /*
	       將componentVector以analyzer重新計算Component
	     */
	    Component_vector_ptr DimDGLutGenerator::fetchNewComponent(bptr <
								      MaxMatrixIntensityAnalyzer
								      >
								      analyzer,
								      Component_vector_ptr
								      componentVector) {
		Component_vector_ptr result(new Component_vector());
		//不限長度
		 foreach(const Component_ptr c, *componentVector) {
		    RGB_ptr intensity = analyzer->getIntensity(c->XYZ);
		    Component_ptr component(new Component(c->rgb, intensity, c->XYZ));
		     result->push_back(component);
		};
		 return result;
	    };

	     DimDGLutGenerator::DimDGLutGenerator(Component_vector_ptr componentVector,
						  bptr < IntensityAnalyzerIF >
						  analyzer):componentVector(componentVector),
		analyzer(analyzer) {
	    };

	    RGB_vector_ptr DimDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int under, double gamma) {
		using namespace Dep;
		//==============================================================
		// 資訊準備
		//==============================================================
		XYZ_ptr blackXYZ = (*componentVector)
		    [componentVector->size() - 1]->XYZ;
		int size = under - 1;
		double_vector_ptr partGammaCurve = DoubleArray::getRangeCopy(luminanceGammaCurve,
									     0, size);
		//求目標值曲線, 僅有dim部分
		XYZ_vector_ptr targetXYZVector = (gamma != -1) ?
		    DimTargetGenerator::getTarget(blackXYZ, targetWhite, partGammaCurve, gamma)
		    : DimTargetGenerator::getLinearTarget(blackXYZ, targetWhite, partGammaCurve);
		STORE_XYZXY_VECTOE("1.2_target.xls", targetXYZVector);
		//==============================================================
		RGB_vector_ptr result(new RGB_vector());
		//primary color只能用target white~
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		foreach(const XYZ_ptr targetXYZ, *targetXYZVector) {
		    bptr < MaxMatrixIntensityAnalyzer > analyzer(new MaxMatrixIntensityAnalyzer());
		    analyzer->setupComponent(Channel::R, rxyY->toXYZ());
		    analyzer->setupComponent(Channel::G, gxyY->toXYZ());
		    analyzer->setupComponent(Channel::B, bxyY->toXYZ());
		    analyzer->setupComponent(Channel::W, targetXYZ);
		    analyzer->enter();
		    Component_vector_ptr
			newcomponentVector = fetchNewComponent(analyzer, componentVector);
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

