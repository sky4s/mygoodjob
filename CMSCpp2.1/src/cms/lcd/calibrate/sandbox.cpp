#include <includeall.h>
#pragma hdrstop
#include "sandbox.h"
#include <debug.h>


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
		(componentVector, analyzer),
		useMaxTargetBIntensity(false), bTargetIntensity(-1),
		multiPrimayColor(false), multiPrimayColorInterval(17),
		stopMeasure(false), multiGenerate(false) {
	    };

	    RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int dimTurn,
			int brightTurn, double dimGamma,
			double brightGamma) {
		return produce(targetWhite, luminanceGammaCurve, dimTurn,
			       brightTurn, dimGamma, brightGamma, false);
	    };

	    /*
	       更進階的產生方式
	       1.先產生一組DG Lut
	       2.把該組DG做量測當作Raw Data
	       3.再拿該組偽Raw Data產生DG Lut
	       4.若精準度要更高,就重複做到滿意為止
	     */
	    RGB_vector_ptr AdvancedDGLutGenerator::
		produce(XYZ_ptr targetWhite,
			double_vector_ptr luminanceGammaCurve, int dimTurn,
			int brightTurn, double dimGamma,
			double brightGamma, bool avoidHook) {
		//==============================================================
		// 資訊準備
		//==============================================================
		XYZ_ptr blackXYZ =
		    (*componentVector)[componentVector->size() - 1]->XYZ;
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;

		//求目標值曲線
		XYZ_vector_ptr targetXYZVector;

		if (avoidHook) {
		    targetXYZVector = getAvoidHookTarget(blackXYZ,
							 nativeWhite,
							 luminanceGammaCurve,
							 dimTurn,
							 brightTurn,
							 dimGamma);
		} else {
		    targetXYZVector = getTarget(blackXYZ,
						targetWhite,
						nativeWhite,
						luminanceGammaCurve,
						dimTurn, brightTurn,
						dimGamma, brightGamma);
		}
		STORE_XYZXY_VECTOE("target.xls", targetXYZVector);
		//==============================================================
		int size = targetXYZVector->size();
		RGB_vector_ptr result(new RGB_vector(size));

		//primary color只能用target white~
		XYZ_ptr rXYZ = analyzer->getPrimaryColor(Channel::R)->toXYZ();
		XYZ_ptr gXYZ = analyzer->getPrimaryColor(Channel::G)->toXYZ();
		XYZ_ptr bXYZ = analyzer->getPrimaryColor(Channel::B)->toXYZ();
		//解crosstalk用
		XYZ_ptr wXYZ = (*targetXYZVector)[size - 1];
		//double2D_ptr targetRatio;
		bptr < MeterMeasurement > mm;

		if (multiPrimayColor) {
		    mm = analyzer->getMeterMeasurement();
		}

		for (int x = size - 1; x != -1; x--) {
		    XYZ_ptr targetXYZ = (*targetXYZVector)[x];

		    bool doMultiPrimayColorMeasure =
			multiPrimayColor
			&& (x % multiPrimayColorInterval == 0)
			&& (x != size - 1)
			&& x <= multiPrimayColorStart
			&& x >= multiPrimayColorEnd;

		    if (doMultiPrimayColorMeasure) {
			RGB_ptr preRGB = (*result)[x + 1];
			rXYZ =
			    mm->measure((int) preRGB->R, 0, 0,
					"")->getXYZ();
			gXYZ =
			    mm->measure(0, (int) preRGB->G, 0,
					"")->getXYZ();
			bXYZ =
			    mm->measure(0, 0, (int) preRGB->B,
					"")->getXYZ();
			wXYZ =
			    mm->measure(preRGB, nil_string_ptr)->getXYZ();
			if (true == stopMeasure) {
			    stopMeasure = false;
			    return RGB_vector_ptr((RGB_vector *)
						  null);
			}
		    }

		    Component_vector_ptr newcomponentVector;
		    if (multiPrimayColor) {
			bptr < AdvancedMaxMatrixIntensityAnayzer >
			    ma(new AdvancedMaxMatrixIntensityAnayzer());
			ma->setupComponent(Channel::R, rXYZ);
			ma->setupComponent(Channel::G, gXYZ);
			ma->setupComponent(Channel::B, bXYZ);
			ma->setupComponent(Channel::W, wXYZ);
			ma->setupTarget(targetXYZ);
			ma->enter();

			newcomponentVector =
			    fetchComponent(ma, componentVector);
		    } else {
			bptr < MaxMatrixIntensityAnayzer >
			    ma(new MaxMatrixIntensityAnayzer());
			ma->setupComponent(Channel::R, rXYZ);
			ma->setupComponent(Channel::G, gXYZ);
			ma->setupComponent(Channel::B, bXYZ);
			ma->setupComponent(Channel::W, targetXYZ);
			ma->enter();

			newcomponentVector =
			    fetchComponent(ma, componentVector);
		    }

#ifdef DEBUG_CCTLUT_NEWMETHOD
		    STORE_COMPONENT(_toString(x) + ".xls",
				    newcomponentVector);
#endif
		    DGLutGenerator lutgen(newcomponentVector);
		    //B採100嗎?
		    if (bTargetIntensity == -1) {
			bTargetIntensity =
			    useMaxTargetBIntensity ? lutgen.
			    getMaxBIntensity() : 100;
		    };
		    RGB_ptr rgb = lutgen.getDGCode(100, 100,
						   bTargetIntensity);
		    (*result)[x] = rgb;
		}

		if (multiPrimayColor) {
		    mm->setMeasureWindowsVisible(false);
		}
		return result;
	    };
	    bool AdvancedDGLutGenerator::
		isAvoidHook(XYZ_ptr targetXYZ, double offsetK) {
		XYZ_ptr XYZOffset = getXYZ(targetXYZ, offsetK);
		return isDuplicateBlue100(XYZOffset);
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getXYZ(XYZ_ptr XYZ,
						   double offsetK) {
		//==============================================================
		// 材料準備
		//==============================================================
		xyY_ptr xyY(new CIExyY(XYZ));
		double cct =
		    CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		xyY_ptr xyYOriginal =
		    CorrelatedColorTemperature::CCT2DIlluminantxyY(cct);
		double cctOffset = cct + offsetK;
		xyY_ptr xyYOffset =
		    CorrelatedColorTemperature::
		    CCT2DIlluminantxyY(cctOffset);
		//==============================================================

		//==============================================================
		// shift
		//==============================================================
		double_array dxy = xyY->getDeltaxy(xyYOriginal);
		xyYOffset->x += dxy[0];
		xyYOffset->y += dxy[1];
		//==============================================================

		xyYOffset->Y = XYZ->Y;
		XYZ_ptr XYZOffset = xyYOffset->toXYZ();
		return XYZOffset;
	    };
	    bool AdvancedDGLutGenerator::
		isDuplicateBlue100(XYZ_ptr targetXYZ) {
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		bptr < MaxMatrixIntensityAnayzer >
		    mmia(new MaxMatrixIntensityAnayzer());
		mmia->setupComponent(Channel::R, rxyY->toXYZ());
		mmia->setupComponent(Channel::G, gxyY->toXYZ());
		mmia->setupComponent(Channel::B, bxyY->toXYZ());
		mmia->setupComponent(Channel::W, targetXYZ);
		mmia->enter();

		Component_vector_ptr newcomponentVector =
		    fetchComponent(mmia, componentVector);

		return isDuplicateBlue100(newcomponentVector);
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getAvoidHookTarget(XYZ_ptr startXYZ,
				   XYZ_ptr targetXYZ,
				   double_vector_ptr
				   luminanceGammaCurve,
				   int dimTurn, int brightTurn,
				   double dimGamma) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim區段
		//==============================================================
		XYZ_vector_ptr dimResult =
		    getDimGammaTarget(luminanceGammaCurve,
				      startXYZ,
				      targetXYZ, dimGamma,
				      dimTurn);
		int dimSize = dimResult->size();
		for (int x = 0; x < dimSize; x++) {
		    (*result)[x] = (*dimResult)[x];
		}
		//==============================================================

		//==============================================================
		// 中間區段+bright區段
		//==============================================================
		for (int x = dimTurn; x < size; x++) {
		    //僅Y有變化
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] =
			getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright區段
		//==============================================================
		for (int x = size - 1; x >= brightTurn; x--) {
		    XYZ_ptr XYZ = (*result)[x];
		    if (!isDuplicateBlue100(XYZ)) {
			int offsetK = 0;
			for (int x = 10; x < 3000; x += 10) {
			    if (isAvoidHook(XYZ, x)) {
				//若可以避免就跳開
				offsetK = x;
				break;
			    }
			}
			(*result)[x] = getXYZ(XYZ, offsetK);
		    }
		}
		//==============================================================
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
			  double dimGamma, double brightGamma) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim區段
		//==============================================================
		XYZ_vector_ptr dimResult =
		    getDimGammaTarget(luminanceGammaCurve,
				      startXYZ,
				      targetXYZ, dimGamma,
				      dimTurn);
		int dimSize = dimResult->size();
		for (int x = 0; x < dimSize; x++) {
		    (*result)[x] = (*dimResult)[x];
		}
		//==============================================================

		//==============================================================
		// 中間區段
		//==============================================================
		for (int x = dimTurn; x < brightTurn; x++) {
		    //僅Y有變化
		    double Y = (*luminanceGammaCurve)[x];
		    (*result)[x] =
			getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright區段
		//==============================================================
		XYZ_vector_ptr brightResult =
		    getBrightGammaTarget(luminanceGammaCurve,
					 targetXYZ,
					 endXYZ, brightGamma,
					 brightTurn);
		int brightSize = brightResult->size();
		for (int x = 0; x < brightSize; x++) {
		    (*result)[x + brightTurn] = (*brightResult)[x];
		}
		//==============================================================
		return result;
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getDimGammaTarget(double_vector_ptr
				  luminanceGammaCurve,
				  XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				  double dimGamma, int dimTurn) {
		//==============================================================
		// dim區段
		//==============================================================
		XYZ_vector_ptr result(new XYZ_vector(dimTurn));
		double_array dimstartValues = startXYZ->getxyValues();
		double_array dimendValues = endXYZ->getxyValues();
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

		    (*result)[index] = getTargetXYZ(u, v, Y);
		}
		//==============================================================
		return result;
	    };
	    XYZ_vector_ptr
		AdvancedDGLutGenerator::
		getBrightGammaTarget(double_vector_ptr
				     luminanceGammaCurve,
				     XYZ_ptr startXYZ,
				     XYZ_ptr endXYZ,
				     double brightGamma, int brightTurn) {
		//==============================================================
		// bright區段
		//==============================================================
		int size = luminanceGammaCurve->size();
		int resultSize = size - brightTurn;
		XYZ_vector_ptr result(new XYZ_vector(resultSize));
		double_array brightstartValues = startXYZ->getxyValues();
		double_array brightendValues = endXYZ->getxyValues();
		double brightbase = size - 1 - brightTurn;

		for (int x = brightTurn; x < size; x++) {
		    double normal = ((double) x - brightTurn) / brightbase;
		    double gamma = Math::pow(normal,
					     brightGamma) *
			brightbase + brightTurn;
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

		    //(*result)[x] = getTargetXYZ(u, v, Y);
		    (*result)[x - brightTurn] = getTargetXYZ(u, v, Y);
		}
		return result;
		//==============================================================
	    };

	    void AdvancedDGLutGenerator::
		setUseMaxTargetBIntensity(bool useMaxTargetBIntensity) {
		this->useMaxTargetBIntensity = useMaxTargetBIntensity;
	    };
	    void AdvancedDGLutGenerator::
		setBTargetIntensity(double bTargetIntensity) {
		this->bTargetIntensity = bTargetIntensity;
	    }
	    void AdvancedDGLutGenerator::
		setMultiPrimayColor(bool enable, int start,
				    int end, int interval) {
		this->multiPrimayColor = enable;
		this->multiPrimayColorStart = start;
		this->multiPrimayColorEnd = end;
		this->multiPrimayColorInterval = interval;
	    };
	    void AdvancedDGLutGenerator::windowClosing() {
		stopMeasure = true;
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1,
							 double v2,
							 double v3,
							 Domain domain) {
		double_array targetValues(new double[3]);
		targetValues[0] = v1;
		targetValues[1] = v2;
		targetValues[2] = v3;

		CIExyY targetxyY;
		switch (domain) {
		case CIExy:
		    targetxyY.setValues(targetValues);
		case CIEuv:
		    targetxyY.setuvYValues(targetValues);
		case CIEuvPrime:
		    targetxyY.setuvPrimeYValues(targetValues);
		};
		return targetxyY.toXYZ();
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1,
							 double v2,
							 double v3) {
		CIExyY targetxyY;
		targetxyY.x = v1;
		targetxyY.y = v2;
		targetxyY.Y = v3;
		return targetxyY.toXYZ();
	    };
	    bool AdvancedDGLutGenerator::
		isDuplicateBlue100(Component_vector_ptr componentVector) {
		int size = componentVector->size();
		int timesOfB100 = 0;
		for (int x = size - 1; x > 0; x--) {
		    Component_ptr c0 = (*componentVector)[x];
		    Component_ptr c1 = (*componentVector)[x - 1];
		    if (c0->intensity->B > 100
			&& c1->intensity->B < 100
			|| c0->intensity->B < 100
			&& c1->intensity->B > 100 ||
			//剛好等於100, 應該很難
			c0->intensity->B == 100 ||
			//最後一個逼近100, 也視為100
			(c0->intensity->B > 99.0 && x == size - 1)) {
			timesOfB100++;
		    }
		}
		return timesOfB100 == 2;
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
				double_vector_ptr
				luminanceGammaCurve, Domain domain) {
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
						     enduvValues[0],
						     x);
		    double v = Interpolation::linear(0, size - 1,
						     startuvValues[1],
						     enduvValues[1],
						     x);
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
			       double_vector_ptr
			       luminanceGammaCurve, double gamma) {
	    };
	    //==================================================================
	};
    };
};

