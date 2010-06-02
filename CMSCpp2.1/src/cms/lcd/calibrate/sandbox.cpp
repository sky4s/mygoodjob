#include <includeall.h>
#pragma hdrstop
#include "sandbox.h"


//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::colorformat;
	    using namespace Indep;
	    using namespace Dep;
	    using namespace java::lang;

	    //==================================================================
	    // AdvancedDGLutGenerator
	    //==================================================================
	     AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < IntensityAnalyzerIF >
				       analyzer):DimDGLutGenerator
		(componentVector, analyzer) {
	    };
	    /*RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int turn) {

		//==============================================================
		// 資訊準備
		//==============================================================
		XYZ_ptr blackXYZ =
		    (*componentVector)[componentVector->size() - 1]->XYZ;
		XYZ_ptr nativeXYZ = (*componentVector)[0]->XYZ;

		//求目標值曲線
		double gamma = 1;
		Domain domain = CIEuvPrime;
		XYZ_vector_ptr targetXYZVector = getTarget(blackXYZ,
							   targetWhite,
							   nativeXYZ,
							   luminanceGammaCurve,
							   turn, turn,
							   gamma, gamma,
							   domain);
		 storeXYZVector(targetXYZVector);
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

		    Component_vector_ptr newcomponentVector =
			fetchComponent(analyzer, componentVector);
		     STORE_COMPONENT(_toString(x++) + ".xls",
				     newcomponentVector);
		    DGLutGenerator lutgen(newcomponentVector);
		    //採100嗎?
		    RGB_ptr rgb = lutgen.produce(100, 100, 100);
		     result->push_back(rgb);
		};

		 return result;
	    };*/

	    RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr
			luminanceGammaCurve,
			int dimTurn,
			int brightTurn,
			double dimGamma, double brightGamma) {
		//==============================================================
		// 資訊準備
		//==============================================================
		XYZ_ptr blackXYZ =
		    (*componentVector)[componentVector->size() - 1]->XYZ;
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;

		//求目標值曲線
		XYZ_vector_ptr targetXYZVector = getTarget(blackXYZ,
							   targetWhite,
							   nativeWhite,
							   luminanceGammaCurve,
							   dimTurn,
							   brightTurn,
							   dimGamma,
							   brightGamma,
							   CIEuvPrime);
		storeXYZVector(targetXYZVector);
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

		    Component_vector_ptr newcomponentVector =
			fetchComponent(analyzer, componentVector);
		    STORE_COMPONENT(_toString(x++) + ".xls",
				    newcomponentVector);
		    DGLutGenerator lutgen(newcomponentVector);
		    //採100嗎?
		    RGB_ptr rgb = lutgen.produce(100, 100, 100);
		    result->push_back(rgb);
		};

		return result;
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTarget(XYZ_ptr startXYZ,
			  XYZ_ptr targetXYZ,
			  XYZ_ptr endXYZ,
			  double_vector_ptr
			  luminanceGammaCurve,
			  int dimTurn,
			  int brightTurn,
			  double dimGamma,
			  double brightGamma, Domain domain) {
		int size = luminanceGammaCurve->size();

		double_array dimstartValues;
		double_array dimendValues;
		double_array brightstartValues;
		double_array brightendValues;

		switch (domain) {
		case CIEuv:
		    dimstartValues = startXYZ->getuvValues();
		    dimendValues = targetXYZ->getuvValues();
		    brightstartValues = targetXYZ->getuvValues();
		    brightendValues = endXYZ->getuvValues();
		case CIEuvPrime:
		    dimstartValues = startXYZ->getuvPrimeValues();
		    dimendValues = targetXYZ->getuvPrimeValues();
		    brightstartValues = targetXYZ->getuvPrimeValues();
		    brightendValues = endXYZ->getuvPrimeValues();
		};

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim區段
		//==============================================================
		double dimbase = dimTurn - 1;
		for (int x = 0; x < dimTurn; x++) {
		    double normal = ((double) x) / dimbase;
		    double gamma = Math::pow(normal, dimGamma) * dimbase;
		    //在uv'上線性變化
		    double u = Interpolation::linear(0, dimbase,
						     dimendValues[0],
						     dimstartValues[0],
						     gamma);
		    double v = Interpolation::linear(0, dimbase,
						     dimendValues[1],
						     dimstartValues[1],
						     gamma);
		    int index = dimbase - x;
		    double Y = (*luminanceGammaCurve)[index];

		    (*result)[index] = getTargetXYZ(u, v, Y, domain);
		}

		//==============================================================

		//==============================================================
		// 中間區段
		//==============================================================
		for (int x = dimTurn; x < brightTurn; x++) {
		    //僅Y有變化
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] =
			getTargetXYZ(dimendValues[0], dimendValues[1], Y,
				     domain);
		}
		//==============================================================

		//==============================================================
		// bright區段
		//==============================================================
		double brightbase = size - 1 - brightTurn;
		for (int x = brightTurn; x < size; x++) {
		    double normal = ((double) x - brightTurn) / brightbase;
		    double gamma = Math::pow(normal,
					     brightGamma) * brightbase +
			brightTurn;
		    //在uv'上線性變化
		    double u = Interpolation::linear(brightTurn, size - 1,
						     brightstartValues[0],
						     brightendValues[0],
						     gamma);
		    double v = Interpolation::linear(brightTurn, size - 1,
						     brightstartValues[1],
						     brightendValues[1],
						     gamma);
		    double Y = (*luminanceGammaCurve)[x];

		    (*result)[x] = getTargetXYZ(u, v, Y, domain);
		}
		//==============================================================
		return result;
	    };

	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double u,
							 double v,
							 double Y,
							 Domain domain) {
		double_array targetValues(new double[3]);
		targetValues[0] = u;
		targetValues[1] = v;
		targetValues[2] = Y;
		//xyY_ptr targetxyY(new CIExyY());
		CIExyY targetxyY;
		switch (domain) {
		case CIEuv:
		    targetxyY.setuvYValues(targetValues);
		case CIEuvPrime:
		    targetxyY.setuvPrimeYValues(targetValues);
		};
		return targetxyY.toXYZ();
	    };

	    //==================================================================

	    //==================================================================
	    // DimTargetGenerator
	    //==================================================================
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve) {
		return getLinearTarget(startXYZ, endXYZ,
				       luminanceGammaCurve, CIEuvPrime);
	    };

	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve,
				Domain domain) {
		int size = luminanceGammaCurve->size();

		double_array startuvValues;
		double_array enduvValues;
		switch (domain) {
		case CIEuv:
		    startuvValues = startXYZ->getuvValues();
		    enduvValues = endXYZ->getuvValues();
		case CIEuvPrime:
		    startuvValues = startXYZ->getuvPrimeValues();
		    enduvValues = endXYZ->getuvPrimeValues();
		};

		XYZ_vector_ptr result(new XYZ_vector(size));

		for (int x = 0; x < size; x++) {
		    //在uv'上線性變化
		    double u = Interpolation::linear(0, size - 1,
						     startuvValues[0],
						     enduvValues[0], x);
		    double v = Interpolation::linear(0, size - 1,
						     startuvValues[1],
						     enduvValues[1], x);
		    double Y = (*luminanceGammaCurve)[x];

		    double_array targetValues(new double[3]);
		    targetValues[0] = u;
		    targetValues[1] = v;
		    targetValues[2] = Y;

		    xyY_ptr targetxyY(new CIExyY());
		    switch (domain) {
		    case CIEuv:
			targetxyY->setuvYValues(targetValues);
		    case CIEuvPrime:
			targetxyY->setuvPrimeYValues(targetValues);
		    };

		    (*result)[x] = targetxyY->toXYZ();
		};
		return result;
	    }

	    XYZ_vector_ptr DimTargetGenerator::
		getGammaTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
			       double_vector_ptr luminanceGammaCurve,
			       double gamma) {
	    };
	    //==================================================================
	};
    };
};

