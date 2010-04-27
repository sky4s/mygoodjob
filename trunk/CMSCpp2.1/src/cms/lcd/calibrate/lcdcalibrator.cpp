#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "rgbvectorop.h";
#include <debug.h>

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::colorformat;
	    using namespace cms::util;
	    using namespace cms::lcd::calibrate;
	    //==================================================================
	    // Component
	    //==================================================================
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity):rgb(rgb),
		intensity(intensity) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ):rgb(rgb),
		intensity(intensity), XYZ(XYZ) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ, RGB_ptr gamma):rgb(rgb),
		intensity(intensity), XYZ(XYZ), gamma(gamma) {

	    };
	    //==================================================================


	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	  ComponentFetcher::ComponentFetcher(bptr < IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):analyzer
		(analyzer), bitDepth(bitDepth)
	    {
	    };

	    Component_vector_ptr ComponentFetcher::
		fetchComponent(int start, int end, int firstStep,
			       int step) {
		MeasureCondition measureCondition(start, end, firstStep,
						  step);
		int_vector_ptr measurecode =
		    measureCondition.getMeasureCode();
		return fetchComponent(measurecode);
	    };

	    Component_vector_ptr ComponentFetcher::
		fetchComponent(int_vector_ptr measureCode) {
		bool tconInput = bitDepth->isTCONInput();
		bool real10Bit = bitDepth->is10in10Out();
		Component_vector_ptr result(new Component_vector());

		bool waitingStable = true;
		int waitTimes = analyzer->getWaitTimes();
		analyzer->setWaitTimes(10000);

		analyzer->beginAnalyze();
		foreach(const int &x, *measureCode) {
		    RGB_ptr rgb(tconInput ?
				(real10Bit ?
				 new RGBColor(x, x, x,
					      MaxValue::RealInt10Bit) :
				 new RGBColor(x, x, x, MaxValue::Int10Bit))
				: new RGBColor(x, x, x));
		    RGB_ptr intensity = analyzer->getIntensity(rgb);
		    XYZ_ptr XYZ = analyzer->getCIEXYZ();
		    Component_ptr component(new Component(rgb, intensity,
							  XYZ));
		    result->push_back(component);

		    if (true == waitingStable) {
			waitingStable = false;
			analyzer->setWaitTimes(waitTimes);
		    }

		    if (true == stop) {
			stop = false;
			break;
		    }
		}
		analyzer->endAnalyze();
		return result;
	    };

	    void ComponentFetcher::setStop(bool stop) {
		this->stop = stop;
	    };

	    void ComponentFetcher::storeToExcel(const string & filename,
						Component_vector_ptr
						componentVector) {

		int n = componentVector->size();
		Util::deleteExist(filename);
		DGLutFile dglut(filename, Create);
		dglut.setRawData(componentVector, nil_RGBGamma,
				 nil_RGBGamma);
	    };
	    void ComponentFetcher::windowClosing() {
		this->setStop(true);
	    };
	    //==================================================================

	    //==================================================================
	    // DGLutGenerator
	    //==================================================================
	    /*
	       DGLutGenerator擔任產出DG Code的重責大任
	       1. 首先接手ComponentFetcher產出的rgb,對應的componet,亮度
	       2. 藉由regression找出componet與亮度的關係
	       1/2由init產出

	       3. 由目標gamma curve經步驟二找到對應的component
	       4. 由compomenet對應出DG Code, DG Code產出
	       3/4由produce產出

	     */
	    void DGLutGenerator::init() {
		//==============================================================
		// 建立回歸資料
		//==============================================================
		int size = componentVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));
		double_vector_ptr keys(new double_vector(size));
		double_vector_ptr rValues(new double_vector(size));
		double_vector_ptr gValues(new double_vector(size));
		double_vector_ptr bValues(new double_vector(size));
		double_array values(new double[3]);


		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    double Y = component->XYZ->Y;
		    RGB_ptr intensity = component->intensity;

		    (*input)[x][0] = intensity->R;
		    (*input)[x][1] = intensity->G;
		    (*input)[x][2] = intensity->B;
		    (*output)[x][0] = Y;

		    RGB_ptr code = component->rgb;
		    code->getValues(values, MaxValue::Double255);
		    //(*keys)[x] = code->getValue(Channel::W);
		    (*keys)[x] = values[0];

		    (*rValues)[x] = intensity->R;
		    (*gValues)[x] = intensity->G;
		    (*bValues)[x] = intensity->B;
		}
		//==============================================================

		//==============================================================
		// 計算c/d
		//==============================================================
		regression.reset(new PolynomialRegression(input, output,
							  Polynomial::
							  COEF_3::BY_3C));
		regression->regress();
		const double *coefs = (*regression->getCoefs())[0];
		a1 = coefs[1];
		a2 = coefs[2];
		a3 = coefs[3];
		a0 = coefs[0];
		c = 1 / (a1 + a2 + a3);
		d = -a0 / (a1 + a2 + a3);
		//==============================================================
		double maxintensity = Math::roundTo(getMaximumIntensity());

		maxLuminance =
		    getLuminance(maxintensity, maxintensity, maxintensity);
		minLuminance = (*output)[size - 1][0];

		//==============================================================
		// 產生RGB LUT
		//==============================================================
		keys = getReverse(keys);
		rValues = getReverse(rValues);
		gValues = getReverse(gValues);
		bValues = getReverse(bValues);
		rLut.reset(new Interpolation1DLUT(keys, rValues));
		gLut.reset(new Interpolation1DLUT(keys, gValues));
		bLut.reset(new Interpolation1DLUT(keys, bValues));
		//==============================================================
	    };
	    double DGLutGenerator::getIntensity(double luminance) {
		return c * luminance + d;
	    };
	    double DGLutGenerator::getLuminance(double rIntensity,
						double gIntensity,
						double bIntensity) {
		return a0 + rIntensity * a1 + gIntensity * a2 +
		    bIntensity * a3;
	    };
	    /*
	       將正規化的gamma curve, 轉換為絕對的亮度curve
	     */
	    double_vector_ptr DGLutGenerator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve)
	    {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new
						      double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    (*luminanceGammaCurve)[x] =
			differ * (*normalGammaCurve)[x] + minLuminance;
		}
		return luminanceGammaCurve;
	    };
	    double_vector_ptr DGLutGenerator::
		getReverse(double_vector_ptr vec) {
		int size = vec->size();
		double_vector_ptr result(new double_vector(size));
		for (int x = 0; x != size; x++) {
		    (*result)[x] = (*vec)[size - 1 - x];
		}
		return result;
	    };
	    double DGLutGenerator::getMaximumIntensity() {
		//int maxindex = (out == Dep::MaxValue::Int6Bit) ? 3 : 0;
		int maxindex = 0;
		Component_ptr maxcomponent = (*componentVector)[maxindex];
		RGB_ptr maxintensity = maxcomponent->intensity;
		const Channel & minchannel = maxintensity->getMinChannel();
		double maxvalue = maxintensity->getValue(minchannel);
		return maxvalue;
	    };
	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, bptr < BitDepthProcessor > bitDepth):componentVector
		(componentVector), bitDepth(bitDepth)
	    {
		init();
	    };

	    RGB_vector_ptr DGLutGenerator::
		produce(RGBGamma_ptr rgbIntensityCurve) {
		double_vector_ptr rIntensityCurve = rgbIntensityCurve->r;
		double_vector_ptr gIntensityCurve = rgbIntensityCurve->g;
		double_vector_ptr bIntensityCurve = rgbIntensityCurve->b;

		int size = rIntensityCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));
		//double intensity[3];
		double rIntensity, gIntensity, bIntensity;
		//將code 0強制設定為0
		(*dglut)[0] = RGB_ptr(new RGBColor(0, 0, 0));

		for (int x = size - 1; x != 0; x--) {
		    rIntensity = (*rIntensityCurve)[x];
		    gIntensity = (*gIntensityCurve)[x];
		    bIntensity = (*bIntensityCurve)[x];

		    rIntensity = rLut->correctValueInRange(rIntensity);
		    gIntensity = gLut->correctValueInRange(gIntensity);
		    bIntensity = bLut->correctValueInRange(bIntensity);

		    double r = rLut->getKey(rIntensity);
		    double g = gLut->getKey(gIntensity);
		    double b = bLut->getKey(bIntensity);

		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };

	    RGBGamma_ptr DGLutGenerator::
		getRGBGamma(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		STORE_DOUBLE_VECTOR("0_lumicurve.xls",
				    luminanceGammaCurve);
		int size = luminanceGammaCurve->size();
		double_vector_ptr rIntenisty(new double_vector(size));
		double_vector_ptr gIntenisty(new double_vector(size));
		double_vector_ptr bIntenisty(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    double luminance = (*luminanceGammaCurve)[x];
		    double intensity = getIntensity(luminance);
		    (*rIntenisty)[x] = intensity;
		    (*gIntenisty)[x] = intensity;
		    (*bIntenisty)[x] = intensity;
		}

		RGBGamma_ptr rgbgamma(new
				      RGBGamma(rIntenisty, gIntenisty,
					       bIntenisty, 100,
					       Intensity));

		return rgbgamma;
	    };

	    //==================================================================

	    //==================================================================
	  MeasureCondition::MeasureCondition(const int start, const int end, const int firstStep, const int step):start(start), end(end),
		firstStep(firstStep), step(step), lowStart(0), lowEnd(0),
		lowStep(0), highStart(0), highEnd(0), highStep(0),
		normalCondition(true) {

	    };
	    MeasureCondition::MeasureCondition(const int lowStart,
					       const int lowEnd,
					       const int lowStep,
					       const int highStart,
					       const int highEnd, const int
					       highStep):start(0), end(0),
		firstStep(0), step(0), lowStart(lowStart), lowEnd(lowEnd),
		lowStep(lowStep), highStart(highStart), highEnd(highEnd),
		highStep(highStep), normalCondition(false) {
	    };
	    int_vector_ptr MeasureCondition::getMeasureCode() {
		if (normalCondition) {
		    return getMeasureCode(start, end, firstStep, step);
		} else {
		    return getMeasureCode(lowStart, lowEnd, lowStep,
					  highStart, highEnd, highStep);
		}
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int start, const int end,
			       const int firstStep, const int step) {
		int_vector_ptr measureCode(new int_vector());
		int measureStep = firstStep;
		bool first = true;

		for (int x = start; x >= end; x -= measureStep) {
		    if (x != start && true == first) {
			first = false;
			measureStep = step;
		    }
		    measureCode->push_back(x);
		}

		return measureCode;
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int lowStart, const int lowEnd,
			       const int lowStep, const int highStart,
			       const int highEnd, const int highStep) {
		int_vector_ptr measureCode(new int_vector());

		int start = isNoRemainder(highStart, highEnd, highStep) ?
		    highStart : highStart + 1;

		for (int x = start; x >= highEnd; x -= highStep) {
		    int code = x > 255 ? 255 : x;
		    measureCode->push_back(code);
		}
		start =
		    (lowStart == highEnd) ? (lowStart - lowStep) : highEnd;
		for (int x = start; x >= lowEnd; x -= lowStep) {
		    measureCode->push_back(x);
		}

		return measureCode;
	    };

	    bool MeasureCondition::isNoRemainder(int start, int end,
						 int step) {
		double dividend = ((double) start - end) / step;
		bool noremainder =
		    dividend == static_cast < int >(dividend);
		return noremainder;
	    }
	    //==================================================================


	    //==================================================================
	    // LCDCalibrator
	    //==================================================================

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n,
						   int effectiven) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < effectiven; x++) {
		    double normal =
			static_cast < double >(x) / (effectiven - 1);
		    double v = java::lang::Math::pow(normal, gamma);
		    (*result)[x] = v;
		} for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
		}
		return result;
	    };
	    void LCDCalibrator::setP1P2(double p1, double p2) {
		this->p1 = p1;
		this->p2 = p2;
		//this->p1p2 = true;
		this->correct = P1P2;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		//this->p1p2 = false;
		this->correct = RBInterpolation;
		this->rbInterpUnder = under;
	    };
	    void LCDCalibrator::setNoneDimCorrect() {
		this->correct = None;
	    };
	    void LCDCalibrator::setGamma(double gamma) {
		this->gamma = gamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		int measureLevel = bitDepth->getMeasureLevel();
		setGammaCurve0(getGammaCurveVector(gamma, n, effectiven));
		useGammaCurve = false;
	    };
	    void LCDCalibrator::setGamma(double rgamma, double ggamma,
					 double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		setGammaCurve0(getGammaCurveVector(rgamma, n, effectiven),
			       getGammaCurveVector(ggamma, n, effectiven),
			       getGammaCurveVector(bgamma, n, effectiven));
		useGammaCurve = false;
	    };
	    void LCDCalibrator::
		setGammaCurve0(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve0(double_vector_ptr rgammaCurve,
			       double_vector_ptr ggammaCurve,
			       double_vector_ptr bgammaCurve) {
		this->rgammaCurve = rgammaCurve;
		this->ggammaCurve = ggammaCurve;
		this->bgammaCurve = bgammaCurve;
	    };
	    void LCDCalibrator::setGammaCurve(double_vector_ptr gammaCurve) {
		setGammaCurve0(gammaCurve);
		useGammaCurve = true;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr rgammaCurve,
			      double_vector_ptr ggammaCurve,
			      double_vector_ptr bgammaCurve) {
		setGammaCurve0(rgammaCurve, ggammaCurve, bgammaCurve);
		useGammaCurve = true;
	    };
	    void LCDCalibrator::setGByPass(bool byPass) {
		this->gByPass = byPass;
	    };
	    void LCDCalibrator::setBIntensityGain(double gain) {
		this->bIntensityGain = gain;
	    };
	    void LCDCalibrator::setBMax(bool bMax) {
		this->bMax = bMax;
	    };
	    void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
		this->avoidFRCNoise = avoid;
	    };
	    void LCDCalibrator::setKeepMaxLuminance(bool keepMaxLuminance) {
		this->keepMaxLuminance = keepMaxLuminance;
	    };

	    /*LCDCalibrator::LCDCalibrator(bptr < cms::measure::IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth): 
	       bitDepth(bitDepth) {
	       rgbgamma = false;
	       useGammaCurve = false;
	       bIntensityGain = 1;
	       rbInterpUnder = 0;
	       p1 = p2 = 0;
	       gamma = rgamma = ggamma = bgamma = -1;
	       this->fetcher.
	       reset(new ComponentFetcher(analyzer, bitDepth));
	       stop = false;
	       }; */

	  LCDCalibrator::LCDCalibrator(bptr < ComponentFetcher > fetcher, bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {
		rgbgamma = false;
		useGammaCurve = false;
		bIntensityGain = 1;
		rbInterpUnder = 0;
		p1 = p2 = 0;
		gamma = rgamma = ggamma = bgamma = -1;
		this->fetcher = fetcher;
		stop = false;
	    };

	    /*
	       CCT + Gamma
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr <
						      MeasureCondition >
						      measureCondition) {
		this->measureCondition = measureCondition;

		if (null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}
		//量測start->end得到的coponent/Y
		int_vector_ptr measurecode =
		    measureCondition->getMeasureCode();
		componentVector = fetcher->fetchComponent(measurecode);
		if (measurecode->size() != componentVector->size()) {
		    return RGB_vector_ptr((RGB_vector *) null);
		}
		STORE_COMPONENT("o_fetch.xls", componentVector);
		if (true == stop) {
		    stop = false;
		    return RGB_vector_ptr((RGB_vector *) null);
		}
		//產生generator
		generator.
		    reset(new DGLutGenerator(componentVector, bitDepth));
		RGBGamma_ptr rgbgamma = generator->getRGBGamma(gammaCurve);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);
		STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);

		/* TODO : bIntensityGain要確認 */
		if (bIntensityGain != 1.0) {
		    //重新產生目標gamma curve
		    bptr < BIntensityGainOp >
			bgain(new BIntensityGainOp(bIntensityGain, 236,
						   bitDepth));
		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(bgain);
		    rgbgamma = gammaop.createInstance();
		};
		initialRGBGamma = rgbgamma->clone();
		STORE_RGBGAMMA("2_rgbgamma_init.xls", rgbgamma);

		//從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		RGB_vector_ptr dglut = generator->produce(rgbgamma);
		STORE_RGBVECTOR("3_dgcode.xls", dglut);
		//==============================================================
		//第一次量化處理
		//==============================================================
		//量化
		MaxValue quantizationBit = bitDepth->getLutMaxValue();
		RGBVector::quantization(dglut, quantizationBit);
		//==============================================================

		if (correct == P1P2) {
		    //==========================================================
		    //p1p2第一階段, 對gamma做調整
		    //==========================================================
		    bptr < P1P2GammaOp >
			p1p2(new P1P2GammaOp(p1, p2, dglut));
		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(p1p2);

		    //產生修正後的gamma2(若沒有p1p2,則為原封不動)
		    rgbgamma = gammaop.createInstance();
		    STORE_RGBGAMMA("4_rgbgamma_p1p2.xls", rgbgamma);

		    //從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		    dglut = generator->produce(rgbgamma);
		    //量化
		    STORE_RGBVECTOR("4.9_dgcode_p1p2g.xls", dglut);
		    RGBVector::quantization(dglut, quantizationBit);
		    STORE_RGBVECTOR("5_dgcode_p1p2g.xls", dglut);
		    //==========================================================


		    //==========================================================
		    //p1p2第二階段, 對dg code調整
		    //==========================================================
		    DGLutOp dgop;
		    dgop.setSource(dglut);
		    bptr < DGLutOp >
			op(new P1P2DGOp(p1, p2, quantizationBit));
		    dgop.addOp(op);
		    dglut = dgop.createInstance();
		    //量化
		    STORE_RGBVECTOR("6_dgcode_p1p2dg.xls", dglut);
		    //==========================================================
		};
		//RGB_vector_ptr dgcode2 = dglut;
		finalRGBGamma = rgbgamma;

		//==============================================================
		// DG Code Op block
		//==============================================================
		//量化
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		//==============================================================

		STORE_RGBVECTOR("7_dgcode_final.xls", result);
		//調整max value
		RGBVector::changeMaxValue(result,
					  bitDepth->getLutMaxValue());

		this->dglut = result;
		return result;
	    };

	    RGB_vector_ptr LCDCalibrator::getGammaDGLut(int step) {

	    };

	    void LCDCalibrator::storeDGLut(const std::
					   string & filename,
					   RGB_vector_ptr dglut) {
		int n = bitDepth->getLevel();
		//int n = true == gamma256 ? 257 : 256;
		//砍掉已存在的
		Util::deleteExist(filename);
		//產生新檔
		DGLutFile file(filename, Create);
		//產生property物件
		DGLutProperty property(*this);
		//寫入property
		file.setProperty(property);
		//寫入dgcode
		file.setGammaTable(dglut);
		//寫入raw data
		file.setRawData(componentVector, initialRGBGamma,
				finalRGBGamma);

	    };

	    void LCDCalibrator::setStop(bool stop) {
		fetcher->setStop(stop);
	    };

	    RGB_vector_ptr LCDCalibrator::
		getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		DGLutOp dgop;
		dgop.setSource(dglut);


		if (correct == RBInterpolation) {
		    bptr < DGLutOp >
			op(new RBInterpolationOp(rbInterpUnder));
		    dgop.addOp(op);
		}

		if (bMax) {
		    //bmax的調整
		    bptr < DGLutOp > bmax(new BMaxOp(bitDepth));
		    dgop.addOp(bmax);
		}
		if (gByPass) {
		    //g bypass的調整
		    bptr < DGLutOp > gbypass(new GByPassOp(bitDepth));
		    dgop.addOp(gbypass);
		}
		if (avoidFRCNoise) {
		    //frc noise的調整
		    bptr < DGLutOp > avoidNoise(new FrcNROp(bitDepth));
		    dgop.addOp(avoidNoise);
		}

		/*if (gamma256) {

		   } */
		if (keepMaxLuminance) {
		    //keep最大亮度
		    bptr < DGLutOp >
			KeepMax(new KeepMaxLuminanceOp(bitDepth));
		    dgop.addOp(KeepMax);
		}
		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };


	    //==================================================================

	};
    };
};

