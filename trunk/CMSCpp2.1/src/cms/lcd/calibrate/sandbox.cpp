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
	    using namespace cms::lcd::calibrate;

	    //==================================================================
	    // AdvancedDGLutGenerator
	    //==================================================================
	     AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < cms::lcd::calibrate::ComponentFetcher > fetcher,
				       bptr < IntensityAnalyzerIF > analyzer1,
				       bptr < IntensityAnalyzerIF > analyzer2,
				       bptr < BitDepthProcessor >
				       bitDepth):DimDGLutGenerator(componentVector, analyzer1),
		fetcher(fetcher), useMaxTargetBIntensity(false), bTargetIntensity(-1),
		stopMeasure(false), multiGen(false), analyzer2(analyzer2), bitDepth(bitDepth),
		smoothMode(true) {
	    };

	     AdvancedDGLutGenerator::
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr < ComponentFetcher >
				       fetcher,
				       bptr < BitDepthProcessor >
				       bitDepth):DimDGLutGenerator
		(componentVector, fetcher->getAnalyzer()),
		fetcher(fetcher), useMaxTargetBIntensity(false),
		bTargetIntensity(-1), stopMeasure(false), multiGen(false),
		bitDepth(bitDepth), smoothMode(false) {
	    };

	    XYZ_vector_ptr AdvancedDGLutGenerator::getTargetXYZVector(XYZ_ptr targetWhite,
								      double_vector_ptr
								      luminanceGammaCurve,
								      int dimTurn, int brightTurn,
								      double dimGamma,
								      double brightGamma,
								      int brightWidth) {
		//==============================================================
		// 資訊準備
		//==============================================================
		XYZ_ptr blackXYZ = (*componentVector)[componentVector->size() - 1]->XYZ;
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		XYZ_vector_ptr targetXYZVector;
		 this->brightTurn = brightTurn;

		//求目標值曲線
		if (true == autoParameter) {
		    int turn = brightTurn;
		    int width = -1;
		    for (; turn >= 100; turn--) {
			width = bitDepth->getEffectiveLevel() - turn;
			targetXYZVector =
			    getTarget0(blackXYZ, targetWhite, nativeWhite, luminanceGammaCurve,
				       dimTurn, turn, dimGamma, brightGamma, width);

			if (true == checkTargetXYZVector(targetXYZVector, turn, turn + width, 3)) {
			    //檢查若最大的dab小於threshold, 就跳出
			    break;
			}
		    };
		    this->autoBrightTurn = turn;
		    this->autoBrightWidth = width;
		} else {
		    targetXYZVector =
			getTarget0(blackXYZ, targetWhite, nativeWhite, luminanceGammaCurve, dimTurn,
				   brightTurn, dimGamma, brightGamma, brightWidth);
		}
		return targetXYZVector;
	    }
	    /*
	       更進階的產生方式
	       1.先產生一組DG Lut
	       2.把該組DG做量測當作Raw Data
	       3.再拿該組偽Raw Data產生DG Lut
	       4.若精準度要更高,就重複做到滿意為止
	     */
	    RGB_vector_ptr AdvancedDGLutGenerator::produce(XYZ_vector_ptr targetXYZVector) {
		STORE_XYZXY_VECTOE("target.xls", targetXYZVector);
		//==============================================================
		/*
		   若做了smooth target(基本上adv dg lut也只有smooth target的功能)
		   但是analyzer裡的primary color並不是native white的primary color,
		   所以做出來的native target無法如預期會是(255,255,255)
		   為了解決這個問題, 必須要有兩組primary color;
		   第一組給target white用, 第二組給native white用.
		   問題在於如何混用這兩組primary color?

		   方法1. 以兩組analyer都產生一組DG, 然後再bright turn到end這段, 以gain值做內插處理.
		 */
		if (multiGen) {
		    return produceDGLutMulti(targetXYZVector, componentVector);
		} else {
		    if (smoothMode) {
			//target white產生的結果
			RGB_vector_ptr result1 = produceDGLut(targetXYZVector, componentVector,
							      analyzer);
			//native white產生的結果
			RGB_vector_ptr result2;
			if (componentVector2 != null) {
			    result2 = produceDGLut(targetXYZVector, componentVector2, analyzer2);
			    result2 = panelRegulator->remapping(result2);
			} else {
			    result2 = produceDGLut(targetXYZVector, componentVector, analyzer2);
			}
			//將兩個結果銜接起來
			return smooth(result1, result2, bitDepth, brightTurn);
		    } else {
			return produceDGLut(targetXYZVector, componentVector, analyzer);
		    }

		}
	    }
	    RGB_vector_ptr AdvancedDGLutGenerator::
		smooth(RGB_vector_ptr result1, RGB_vector_ptr result2,
		       bptr < BitDepthProcessor > bitDepth, int brightTurn) {
		RGB_vector_ptr result = RGBVector::deepClone(result1);

		int level = bitDepth->getLevel();
		int part = level - brightTurn;
		int part13 = part / 3;
		int part13Start = level - part13;
		int size = result1->size();
		for (int x = brightTurn; x < part13Start; x++) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr rgb1 = (*result1)[x];
		    RGB_ptr rgb2 = (*result2)[x];
		    double gain2 = (((double) x) - brightTurn) / (part13Start - brightTurn);
		    double gain = 1. - gain2;
		    rgb->R = gain * rgb1->R + gain2 * rgb2->R;
		    rgb->G = gain * rgb1->G + gain2 * rgb2->G;
		    rgb->B = gain * rgb1->B + gain2 * rgb2->B;
		}
		for (int x = part13Start; x < level; x++) {
		    (*result)[x] = (*result2)[x]->clone();
		}
		STORE_RGBVECTOR("sm-result1.xls", result1);
		STORE_RGBVECTOR("sm-result2.xls", result2);
		STORE_RGBVECTOR("sm-result.xls", result);

		return result;
	    };
	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLutMulti(XYZ_vector_ptr targetXYZVector,
				  Component_vector_ptr componentVector) {
		RGB_vector_ptr initRGBVector = produceDGLut(targetXYZVector, componentVector,
							    analyzer);

		/*
		   1. RGB不用換, 恆定255
		   2. RGB都採用上一次的DG Code
		   若是如此, 一定要求出該GL的DG才可以繼續下一個
		 */
		//int size = targetXYZVector->size();
		RGB_vector_ptr result = initRGBVector;
		if (null == fetcher) {
		    throw new IllegalStateException("null == fetcher");
		}
		STORE_RGBVECTOR("MultiGen_0.xls", result);

		for (int t = 0; t < multiGenTimes; t++) {
		    bptr < MeasureCondition >
			measureCondition(new MeasureCondition(RGBVector::reverse(result)));
		    Component_vector_ptr componentVectorPrime =
			fetcher->fetchComponent(measureCondition);

		    result = produceDGLut0(targetXYZVector, analyzer, componentVectorPrime);
		    STORE_RGBVECTOR("MultiGen_" + _toString(t + 1) + ".xls", result);
		}

		return result;
	    };

	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLut0(XYZ_vector_ptr targetXYZVector,
			      bptr < cms::measure::IntensityAnalyzerIF > analyzer,
			      Component_vector_ptr componentVector) {
		int size = targetXYZVector->size();
		RGB_vector_ptr result(new RGB_vector(size));
		//==============================================================
		//primary color只能用target white~
		XYZ_ptr rXYZ = analyzer->getPrimaryColor(Channel::R)->toXYZ();
		XYZ_ptr gXYZ = analyzer->getPrimaryColor(Channel::G)->toXYZ();
		XYZ_ptr bXYZ = analyzer->getPrimaryColor(Channel::B)->toXYZ();

#ifdef DEBUG_CCTLUT_NEWMETHOD
		Component_vector_ptr maxComponentVector(new Component_vector());
#endif
		for (int x = size - 1; x != -1; x--) {
		    XYZ_ptr targetXYZ = (*targetXYZVector)[x];

		    bptr < MaxMatrixIntensityAnayzer > ma(new MaxMatrixIntensityAnayzer());
		    ma->setupComponent(Channel::R, rXYZ);
		    ma->setupComponent(Channel::G, gXYZ);
		    ma->setupComponent(Channel::B, bXYZ);
		    ma->setupComponent(Channel::W, targetXYZ);
		    ma->enter();

		    Component_vector_ptr newcomponentVector =
			fetchNewComponent(ma, componentVector);

#ifdef DEBUG_CCTLUT_NEWMETHOD
#ifdef DEBUG_CCTLUT_NEWMETHOD_STEP
		    STORE_COMPONENT(_toString(x) + ".xls", newcomponentVector);
#endif
		    //把第一個存起來, 第一個往往是最大的
		    RGB_ptr grayLevel(new RGBColor(x, x, x));
		    Component_ptr c(new Component(grayLevel,
						  (*newcomponentVector)[0]->intensity, targetXYZ));
		    maxComponentVector->push_back(c);
#endif
		    DGLutGenerator lutgen(newcomponentVector);
		    //B採100嗎?
		    if (bTargetIntensity == -1) {
			bTargetIntensity = useMaxTargetBIntensity ? lutgen.getMaxBIntensity() : 100;
		    };
		    RGB_ptr rgb = lutgen.getDGCode(100, 100,
						   bTargetIntensity);
		    (*result)[x] = rgb;
		}
#ifdef DEBUG_CCTLUT_NEWMETHOD
		STORE_COMPONENT("maxIntensity.xls", maxComponentVector);
#endif
		return result;
	    }

	    RGB_vector_ptr AdvancedDGLutGenerator::
		produceDGLut(XYZ_vector_ptr targetXYZVector,
			     Component_vector_ptr componentVector,
			     bptr < cms::measure::IntensityAnalyzerIF > analyzer) {

		return produceDGLut0(targetXYZVector, analyzer, componentVector);
	    };
	    bool AdvancedDGLutGenerator::isAvoidHook(XYZ_ptr targetXYZ, double offsetK) {
		XYZ_ptr XYZOffset = getXYZ(targetXYZ, offsetK);
		return isDuplicateBlue100(XYZOffset);
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getXYZ(XYZ_ptr XYZ, double offsetK) {
		//==============================================================
		// 材料準備
		//==============================================================
		xyY_ptr xyY(new CIExyY(XYZ));
		double cct = CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY);
		xyY_ptr xyYOriginal = CorrelatedColorTemperature::CCT2DIlluminantxyY(cct);
		double cctOffset = cct + offsetK;
		xyY_ptr xyYOffset = CorrelatedColorTemperature::CCT2DIlluminantxyY(cctOffset);
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
	    bool AdvancedDGLutGenerator::isDuplicateBlue100(XYZ_ptr targetXYZ) {
		xyY_ptr rxyY = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr gxyY = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr bxyY = analyzer->getPrimaryColor(Channel::B);

		bptr < MaxMatrixIntensityAnayzer > mmia(new MaxMatrixIntensityAnayzer());
		mmia->setupComponent(Channel::R, rxyY->toXYZ());
		mmia->setupComponent(Channel::G, gxyY->toXYZ());
		mmia->setupComponent(Channel::B, bxyY->toXYZ());
		mmia->setupComponent(Channel::W, targetXYZ);
		mmia->enter();

		Component_vector_ptr newcomponentVector = fetchNewComponent(mmia, componentVector);

		return isDuplicateBlue100(newcomponentVector);
	    };

	    /*
	       產生smooth target還是有個問題, 就是luminance.
	       現在的作法是用原本的Target White的亮度來產生Luminance(也就是最大亮度),
	       但實際上高灰階的Target White已經被改變, 所以最大亮度也不同了.
	       若直接以高灰階的Target White為最大亮度, 部份高灰階卻又無法產生相同亮度及相同色度座標的DG
	     */
	    XYZ_vector_ptr AdvancedDGLutGenerator::
		getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ, XYZ_ptr endXYZ,
			   double_vector_ptr luminanceGammaCurve, int dimTurn, int brightTurn,
			   double dimGamma, double brightGamma, int brightWidth) {
		int size = luminanceGammaCurve->size();
		double_array dimendValues = targetXYZ->getxyValues();

		XYZ_vector_ptr result(new XYZ_vector(size));

		//==============================================================
		// dim區段
		//==============================================================
		XYZ_vector_ptr dimResult = getDimGammaTarget(luminanceGammaCurve,
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
		    (*result)[x] = getTargetXYZ(dimendValues[0], dimendValues[1], Y);
		}
		//==============================================================

		//==============================================================
		// bright區段
		//==============================================================
		XYZ_vector_ptr brightResult = getBrightGammaTarget(luminanceGammaCurve,
								   targetXYZ,
								   endXYZ, brightGamma,
								   brightTurn, brightWidth,
								   bitDepth);
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
				  XYZ_ptr startXYZ, XYZ_ptr endXYZ, double dimGamma, int dimTurn) {
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
				     XYZ_ptr endXYZ, double brightGamma,
				     int brightTurn, int brightWidth,
				     bptr < BitDepthProcessor > bitDepth) {
		//==============================================================
		// bright區段
		//==============================================================
		int size = luminanceGammaCurve->size();
		int brightEnd = brightTurn + brightWidth;
		int resultSize = size - brightTurn;
		XYZ_vector_ptr result(new XYZ_vector(resultSize));
		double_array brightstartValues = startXYZ->getxyValues();
		double_array brightendValues = endXYZ->getxyValues();
		double brightbase = brightEnd - 1 - brightTurn;

		for (int x = brightTurn; x < brightEnd; x++) {
		    double normal = ((double) x - brightTurn) / brightbase;
		    double gamma = Math::pow(normal, brightGamma) * brightbase + brightTurn;
		    //在uv'上線性變化
		    double u = Interpolation::linear(brightTurn, brightEnd - 1,
						     brightstartValues[0],
						     brightendValues[0],
						     gamma);
		    double v = Interpolation::linear(brightTurn, brightEnd - 1,
						     brightstartValues[1],
						     brightendValues[1],
						     gamma);
		    double Y = (*luminanceGammaCurve)[x];

		    (*result)[x - brightTurn] = getTargetXYZ(u, v, Y);
		}
		XYZ_ptr XYZ = (*result)[brightEnd - 1 - brightTurn];
		for (int x = brightEnd; x < size; x++) {
		    (*result)[x - brightTurn] = XYZ;
		}
		return result;
		//==============================================================
	    };

	    void AdvancedDGLutGenerator::setUseMaxTargetBIntensity(bool useMaxTargetBIntensity) {
		this->useMaxTargetBIntensity = useMaxTargetBIntensity;
	    };
	    void AdvancedDGLutGenerator::setBTargetIntensity(double bTargetIntensity) {
		this->bTargetIntensity = bTargetIntensity;
	    }
	    void AdvancedDGLutGenerator::windowClosing() {
		stopMeasure = true;
	    };
	    void AdvancedDGLutGenerator::setMultiGen(bool enable, int times) {
		if (null == fetcher) {
		    throw IllegalStateException("null == fetcher");
		}
		this->multiGen = enable;
		this->multiGenTimes = times;
	    };
	    XYZ_vector_ptr AdvancedDGLutGenerator::getTargetXYZVector() {
		return targetXYZVector;
	    };
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1,
							 double v2, double v3, Domain domain) {
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
	    XYZ_ptr AdvancedDGLutGenerator::getTargetXYZ(double v1, double v2, double v3) {
		CIExyY targetxyY;
		targetxyY.x = v1;
		targetxyY.y = v2;
		targetxyY.Y = v3;
		return targetxyY.toXYZ();
	    };
	    bool AdvancedDGLutGenerator::isDuplicateBlue100(Component_vector_ptr componentVector) {
		int size = componentVector->size();
		int timesOfB100 = 0;
		for (int x = size - 1; x > 0; x--) {
		    Component_ptr c0 = (*componentVector)[x];
		    Component_ptr c1 = (*componentVector)[x - 1];
		    if (c0->intensity->B > 100
			&& c1->intensity->B < 100
			|| c0->intensity->B < 100 && c1->intensity->B > 100 ||
			//剛好等於100, 應該很難
			c0->intensity->B == 100 ||
			//最後一個逼近100, 也視為100
			(c0->intensity->B > 99.0 && x == size - 1)) {
			timesOfB100++;
		    }
		}
		return timesOfB100 == 2;
	    };
	    void AdvancedDGLutGenerator::setAutoParameter(bool autoParameter) {
		this->autoParameter = autoParameter;
	    };
	    bool AdvancedDGLutGenerator::checkTargetXYZVector(XYZ_vector_ptr targetXYZVector,
							      int start, int end,
							      double deltaabThreshold) {
		int size = targetXYZVector->size();
		XYZ_ptr white = (*targetXYZVector)[size - 1];
		int checkSize = end - start;
		double_vector_ptr checkResult(new double_vector(checkSize));

		for (int x = start + 1; x < end; x++) {
		    XYZ_ptr x0 = (*targetXYZVector)[x - 1];
		    XYZ_ptr x1 = (*targetXYZVector)[x];
		    Lab_ptr lab0(new CIELab(x0, white));
		    Lab_ptr lab1(new CIELab(x1, white));
		    DeltaE de(lab0, lab1);
		    double dab = de.getCIE2000Deltaab();
		    (*checkResult)[x - (start + 1)] = dab;
		}
		double max = Math::max(checkResult);
		return max < deltaabThreshold;
	    };
	    int AdvancedDGLutGenerator::getAutoBrightTurn() {
		return autoBrightTurn;
	    };
	    int AdvancedDGLutGenerator::getAutoBrightWidth() {
		return autoBrightWidth;
	    };
	    void AdvancedDGLutGenerator::setComponentVector2(Component_vector_ptr componentVector2,
							     bptr < PanelRegulator >
							     panelRegulator) {
		this->componentVector2 = componentVector2;
		this->panelRegulator = panelRegulator;
	    };
	    //==================================================================

	    //==================================================================
	    // DimTargetGenerator
	    //==================================================================
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve) {
		return getLinearTarget(startXYZ, endXYZ, luminanceGammaCurve, CIEuvPrime);
	    };
	    XYZ_vector_ptr DimTargetGenerator::
		getLinearTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
				double_vector_ptr luminanceGammaCurve, Domain domain) {
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
						     startuvValues[0], enduvValues[0], x);
		    double v = Interpolation::linear(0, size - 1,
						     startuvValues[1], enduvValues[1], x);
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
			       double_vector_ptr luminanceGammaCurve, double gamma) {
		/* TODO : getGammaTarget */
	    };
	    //==================================================================
	};
    };
};

