#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
//#include "rgbvectorop.h"

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
	     MeasureCondition::MeasureCondition(bptr < cms::lcd::calibrate::BitDepthProcessor >
						bitDepth):start(bitDepth->getMeasureStart()),
		end(bitDepth->getMeasureEnd()), firstStep(bitDepth->getMeasureFirstStep()),
		step(bitDepth->getMeasureStep()), type(Normal) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      bitDepth->getMeasureMaxValue());
	    };
	     MeasureCondition::MeasureCondition(const int start, const int end, const int firstStep,
						const int step,
						const Dep::MaxValue & maxValue):start(start),
		end(end), firstStep(firstStep), step(step), type(Normal) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      maxValue);
	    };
	     MeasureCondition::MeasureCondition(const int lowStart,
						const int lowEnd,
						const int lowStep,
						const int highStart, const int highEnd, const int
						highStep,
						const Dep::
						MaxValue &
						maxValue):lowStart
		(lowStart), lowEnd(lowEnd), lowStep(lowStep),
		highStart(highStart), highEnd(highEnd), highStep(highStep), type(Extend) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode
				      (lowStart, lowEnd, lowStep,
				       highStart, highEnd, highStep), Channel::W, maxValue);
	    };

	  MeasureCondition::MeasureCondition(RGB_vector_ptr rgbMeasureCode):type(Normal)
	    {
		this->rgbMeasureCode = rgbMeasureCode;
	    };

	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode() {
		return rgbMeasureCode;
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
		if ((*measureCode)[measureCode->size() - 1] != end) {
		    measureCode->push_back(end);
		}

		return measureCode;
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int lowStart, const int lowEnd,
			       const int lowStep, const int highStart,
			       const int highEnd, const int highStep) {
		int_vector_ptr measureCode(new int_vector());

		int start = isNoRemainder(highStart, highEnd,
					  highStep) ? highStart : highStart + 1;

		for (int x = start; x >= highEnd; x -= highStep) {
		    int code = x > 255 ? 255 : x;
		    measureCode->push_back(code);
		}
		start = (lowStart == highEnd) ? (lowStart - lowStep) : highEnd;
		for (int x = start; x >= lowEnd; x -= lowStep) {
		    measureCode->push_back(x);
		}

		return measureCode;
	    };

	    bool MeasureCondition::isNoRemainder(int start, int end, int step) {
		double dividend = ((double) start - end) / step;
		bool noremainder = dividend == static_cast < int >(dividend);
		return noremainder;
	    }
	    RGB_vector_ptr MeasureCondition::
		getRGBMeasureCode(int_vector_ptr measureCode, const Dep::Channel & channel) {
		return getRGBMeasureCode(measureCode, channel, MaxValue::Int8Bit);
	    }
	    RGB_vector_ptr MeasureCondition::
		getRGBMeasureCode(int_vector_ptr measureCode,
				  const Dep::Channel & channel, const MaxValue & maxValue) {
		RGB_vector_ptr rgbMeasureCode(new RGB_vector());
		foreach(int c, *measureCode) {
		    RGB_ptr rgb(new RGBColor(maxValue));
		    rgb->setValue(channel, c);
		    rgbMeasureCode->push_back(rgb);
		}
		return rgbMeasureCode;
	    };
	    //==================================================================


	    //==================================================================
	    // LCDCalibrator
	    //==================================================================

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n, int effectiven) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < effectiven; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double v = Math::pow(normal, gamma);
		    (*result)[x] = v;
		};
		for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
		}
		return result;
	    };
	    void LCDCalibrator::setP1P2(int p1, int p2) {
		this->p1 = p1;
		this->p2 = p2;
		this->correct = Correct::P1P2;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		this->correct = Correct::RBInterpolation;
		this->under = under;
	    };
	    void LCDCalibrator::setNonDimCorrect() {
		this->correct = Correct::None;
	    };

	    void LCDCalibrator::setDefinedDim(int under, double gamma, bool averageDimDG) {
		this->correct = Correct::DefinedDim;
		this->under = under;
		this->dimGamma = gamma;
		this->averageDimDG = averageDimDG;
	    } void LCDCalibrator::setGamma(double gamma) {
		this->gamma = gamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		setGammaCurve0(getGammaCurveVector(gamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::setGamma(double rgamma, double ggamma, double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		setGammaCurve0(getGammaCurveVector(rgamma, n, effectiven),
			       getGammaCurveVector(ggamma, n, effectiven),
			       getGammaCurveVector(bgamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = true;
	    };
	    void LCDCalibrator::setGammaCurve0(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve0(double_vector_ptr rgammaCurve,
			       double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve) {
		this->rgammaCurve = rgammaCurve;
		this->ggammaCurve = ggammaCurve;
		this->bgammaCurve = bgammaCurve;
	    };
	    void LCDCalibrator::setGammaCurve(double_vector_ptr gammaCurve) {
		setGammaCurve0(gammaCurve);
		useGammaCurve = true;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr rgammaCurve,
			      double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve) {
		setGammaCurve0(rgammaCurve, ggammaCurve, bgammaCurve);
		useGammaCurve = true;
		rgbIndepGamma = true;
	    };
	    void LCDCalibrator::setOriginalGamma() {
		this->originalGamma = true;
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
	    void LCDCalibrator::setBMax2(bool bMax2, int begin, double gamma) {
		this->bMax2 = bMax2;
		bMax2Begin = begin;
		bMax2Gamma = gamma;
	    };
	    void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
		this->avoidFRCNoise = avoid;
	    };
	    void LCDCalibrator::setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance) {
		if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		    throw
			UnsupportedOperationException
			("Please call setKeepMaxLuminanceNativeWhiteAdvanced().");
		}
		this->keepMaxLuminance = keepMaxLuminance;
	    };
	    void LCDCalibrator::setKeepMaxLuminanceNativeWhiteAdvanced(int over, double gamma) {
		this->keepMaxLuminance = KeepMaxLuminance::NativeWhiteAdvanced;
		this->keepMaxLumiOver = over;
		this->keepMaxLumiGamma = gamma;
	    };
	    void LCDCalibrator::setNewMethod(bool enable) {
		this->newMethod = enable;
	    };
	    void LCDCalibrator::setSkipInverseB(bool skip) {
		this->skipInverseB = skip;
	    };
	  LCDCalibrator::LCDCalibrator(bptr < ComponentFetcher > fetcher, bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {
		rgbIndepGamma = false;
		useGammaCurve = false;
		bIntensityGain = 1;
		under = 0;
		p1 = p2 = 0;
		gamma = rgamma = ggamma = bgamma = -1;
		this->fetcher = fetcher;
		averageDimDG = false;
		newMethod = false;
		bMax = bMax2 = false;
		bTargetIntensity = -1;
		originalGamma = false;
		skipInverseB = false;
	    };

	    Component_vector_ptr LCDCalibrator::
		fetchComponentVector(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		//量測start->end得到的coponent/Y
		componentVector = fetcher->fetchComponent(measureCondition);
		RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();

		if (componentVector == null || rgbMeasureCode->size() != componentVector->size()) {
		    return Component_vector_ptr((Component_vector *)
						null);
		} else {
		    return componentVector;
		}
	    };

	    double_vector_ptr LCDCalibrator::
		fetchLuminanceVector(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		//量測start->end得到的coponent/Y
		luminanceVector = fetcher->fetchLuminance(measureCondition);

		if (luminanceVector == null
		    /*|| measurecode->size() != luminanceVector->size() */
		    ) {
		    return double_vector_ptr((double_vector *)
					     null);
		} else {
		    return luminanceVector;
		}
	    };

	    double_vector_ptr LCDCalibrator::getGammaCurve(Component_vector_ptr componentVector) {
		double_vector_ptr keys(new double_vector());
		double_vector_ptr values(new double_vector());
		int size = componentVector->size();

		Component_ptr white = (*componentVector)[0];
		Component_ptr black = (*componentVector)[size - 1];
		double maxLuminance = white->XYZ->Y;
		double minLuminance = black->XYZ->Y;
		//double max = white->rgb->getMaxValue().max;
		double max = bitDepth->getMaxDigitalCount();

		for (int x = size - 1; x != -1; x--) {
		    Component_ptr c = (*componentVector)[x];
		    double gray = c->rgb->getValue(Channel::W);
		    double normal = gray / max;
		    double luminance = c->XYZ->Y;
		    double normalLuminance =
			(luminance - minLuminance) / (maxLuminance - minLuminance);
		    keys->push_back(normal);
		    values->push_back(normalLuminance);
		}

		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveLevel();
		Interpolation1DLUT lut(keys, values);
		double_vector_ptr gammaCurve(new double_vector());

		for (int x = 0; x != effectiven; x++) {
		    double normal = ((double) x) / (effectiven - 1);
		    double value = lut.getValue(normal);
		    gammaCurve->push_back(value);
		}
		for (int x = effectiven; x != n; x++) {
		    gammaCurve->push_back(1);
		}

		return gammaCurve;
	    };

	    /*
	       CCT + Gamma
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		if (false == originalGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		if (true == newMethod && keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced
		    && nativeWhiteAnalyzer == null) {
		    //=====================================================
		    // 生出一組新的analyzer, 給smooth target的時候用
		    // 有這組analyzer, 在smooth到native white的時候可以得到更準確的結果.
		    //=====================================================
		    //產生max matrix
		    bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
		    nativeWhiteAnalyzer =
			bptr < MaxMatrixIntensityAnayzer > (new MaxMatrixIntensityAnayzer(mm));

		    int max = bitDepth->getMaxDigitalCount();
		    int bmax = max;
		    if (true == skipInverseB) {
			bptr < MeasureTool > mt(new MeasureTool(mm));
			MeasureWindow->addWindowListener(mt);
			bptr < MeasureCondition > measureCondition(new MeasureCondition(bitDepth));
			bmax = mt->getMaxZDGCode(measureCondition);
		    }
		    //已知rgb
		    RGB_ptr rgb(new RGBColor(max, max, bmax, MaxValue::Int8Bit));
		    RGB_ptr r(new RGBColor(max, 0, 0, MaxValue::Int8Bit));
		    RGB_ptr g(new RGBColor(0, max, 0, MaxValue::Int8Bit));
		    RGB_ptr b(new RGBColor(0, 0, bmax, MaxValue::Int8Bit));

		    int defaultWaitTimes = analyzer->getWaitTimes();
		    analyzer->setWaitTimes(5000);
		    nativeWhiteAnalyzer->beginAnalyze();
		    nativeWhiteAnalyzer->setupComponent(Channel::R, r);
		    nativeWhiteAnalyzer->setupComponent(Channel::G, g);
		    nativeWhiteAnalyzer->setupComponent(Channel::B, b);
		    nativeWhiteAnalyzer->setupComponent(Channel::W, rgb);
		    nativeWhiteAnalyzer->enter();
		    analyzer->setWaitTimes(defaultWaitTimes);

		    //=====================================================
		}

		Component_vector_ptr componentVector = fetchComponentVector(measureCondition);
		if (componentVector == null) {
		    return RGB_vector_ptr((RGB_vector *) null);
		}

		if (true == originalGamma) {
		    //若要採用original gamma, 從量測結果拉出gamma, 當作目標gamma curve
		    double_vector_ptr gammaCurve = getGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}

		STORE_COMPONENT("o_fetch.xls", componentVector);
		DGLutGenerator generator(componentVector, keepMaxLuminance);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);
		MaxValue quantizationBit = bitDepth->getLutMaxValue();

		if (true == newMethod) {
		    //==========================================================
		    // 新方法
		    //==========================================================
		    double brightgammaParameter = 1;
		    int overParameter = 200;
		    bptr < AdvancedDGLutGenerator > advgenerator;

		    //藉由傳統generator產生luminance gamma curve
		    double_vector_ptr luminanceGammaCurve;

		    if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
			brightgammaParameter = keepMaxLumiGamma;
			overParameter = keepMaxLumiOver;

			advgenerator = bptr < AdvancedDGLutGenerator >
			    (new
			     AdvancedDGLutGenerator(componentVector, fetcher->getAnalyzer(),
						    nativeWhiteAnalyzer, bitDepth));

			double maxLuminance =
			    (true == skipInverseB) ?
			    nativeWhiteAnalyzer->getReferenceColor()->Y : (*componentVector)[0]->
			    XYZ->Y;
			double minLuminance =
			    (*componentVector)[componentVector->size() - 1]->XYZ->Y;
			luminanceGammaCurve =
			    generator.getLuminanceGammaCurve(gammaCurve, maxLuminance,
							     minLuminance);
		    } else {
			advgenerator =
			    bptr < AdvancedDGLutGenerator >
			    (new AdvancedDGLutGenerator(componentVector, fetcher, bitDepth));
			luminanceGammaCurve = generator.getLuminanceGammaCurve(gammaCurve);

		    }
		    STORE_DOUBLE_VECTOR("1_lumigammacurve.xls", luminanceGammaCurve);

		    //AdvancedDGLutGenerator advgenerator(componentVector, fetcher, bitDepth);
		    bptr < IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    //analyzer若沒有設定過target color, 會使此步驟失效
		    XYZ_ptr targetWhite = analyzer->getReferenceColor()->toXYZ();


		    double dimgammaParameter = 3.5;
		    int underParameter = 50;

		    if (correct == Correct::DefinedDim) {
			dimgammaParameter = dimGamma;
			underParameter = under;
		    }

		    if (this->bTargetIntensity != -1) {
			advgenerator->setBTargetIntensity(bTargetIntensity);
		    }

		    if (multiGen) {
			advgenerator->setMultiGen(multiGen, multiGenTimes);
		    }

		    dglut =
			advgenerator->produce(targetWhite, luminanceGammaCurve, underParameter,
					      overParameter, dimgammaParameter,
					      brightgammaParameter);
		    STORE_RGBVECTOR("3_dgcode.xls", dglut);
		    //==========================================================
		} else {
		    //==========================================================
		    // 老方法
		    //==========================================================
		    RGBGamma_ptr rgbgamma = generator.getRGBGamma(gammaCurve);
		    initialRGBGamma = rgbgamma->clone();

		    STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);


		    /* TODO : bIntensityGain要確認 */
		    if (bIntensityGain != 1.0) {
			//重新產生目標gamma curve
			bptr < BIntensityGainOp >
			    bgain(new BIntensityGainOp(bIntensityGain, 236, bitDepth));

			RGBGammaOp gammaop;
			gammaop.setSource(rgbgamma);
			gammaop.addOp(bgain);
			rgbgamma = gammaop.createInstance();
			STORE_RGBGAMMA("2_rgbgamma_bGain.xls", rgbgamma);
		    }
		    //從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    STORE_RGBVECTOR("3_dgcode.xls", dglut);
		    //==============================================================
		    //第一次量化處理
		    //==============================================================
		    //量化
		    //MaxValue quantizationBit = bitDepth->getLutMaxValue();
		    RGBVector::quantization(dglut, quantizationBit);
		    //==============================================================

		    if (correct == Correct::P1P2) {
			//==========================================================
			//p1p2第一階段, 對gamma做調整
			//==========================================================
			bptr < P1P2GammaOp > p1p2(new P1P2GammaOp(p1, p2, dglut));
			RGBGammaOp gammaop;
			gammaop.setSource(rgbgamma);
			gammaop.addOp(p1p2);

			//產生修正後的gamma2(若沒有p1p2,則為原封不動)
			rgbgamma = gammaop.createInstance();
			STORE_RGBGAMMA("4_rgbgamma_p1p2.xls", rgbgamma);

			//從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
			dglut = generator.getCCTDGLut(rgbgamma);
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
			//bptr < DGLutOp > op(new P1P2DGOp(p1, p2, quantizationBit));
			bptr < DGLutOp > op(new P1P2DGOp(p1, p2));
			dgop.addOp(op);
			dglut = dgop.createInstance();
			//量化
			STORE_RGBVECTOR("6_dgcode_p1p2dg.xls", dglut);
			//==========================================================
		    }
		    finalRGBGamma = rgbgamma;
		    //==========================================================
		}

		//==============================================================
		// DG Code Op block
		//==============================================================
		//量化
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		RGBVector::quantization(result, quantizationBit);
		//==============================================================

		STORE_RGBVECTOR("7_dgcode_final.xls", result);
		//調整max value, 調整到LUT真正的max value
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());

		this->dglut = result;
		return result;
	    };

	    RGB_vector_ptr LCDCalibrator::getGammaDGLut(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;

		if (false == rgbIndepGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		} else if (true == rgbIndepGamma
			   && (null == rgammaCurve || null == ggammaCurve || null == bgammaCurve)) {
		    throw new
			IllegalStateException
			("null == rgammaCurve || null == ggammaCurve || null == bgammaCurve");
		}


		RGB_vector_ptr dglut;
		if (true == rgbIndepGamma) {
		    //暫不提供
		    dglut = RGB_vector_ptr((RGB_vector *) null);
		    return dglut;
		} else {
		    double_vector_ptr luminanceVector = fetchLuminanceVector(measureCondition);
		    STORE_DOUBLE_VECTOR("o_fetch.xls", luminanceVector);

		    if (luminanceVector == null) {
			return RGB_vector_ptr((RGB_vector *) null);
		    }

		    DGLutGenerator generator(luminanceVector);
		    dglut = generator.getGammaDGLut(gammaCurve);

		}
		//量化
		MaxValue quantizationBit = bitDepth->getLutMaxValue();
		RGBVector::quantization(dglut, quantizationBit);
		//調整max value
		RGBVector::changeMaxValue(dglut, bitDepth->getLutMaxValue());

		this->dglut = dglut;
		return dglut;
	    };

	    bptr < DGLutFile >
		LCDCalibrator::storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut) {
		//int n = bitDepth->getLevel();
		//int n = true == gamma256 ? 257 : 256;
		//砍掉已存在的
		Util::deleteExist(filename);
		//產生新檔
		bptr < DGLutFile > file(new DGLutFile(filename, Create));
		//DGLutFile file(filename, Create);
		//產生property物件
		//bptr < LCDCalibrator > thisbptr(this);
		DGLutProperty property(this);
		//寫入property
		file->setProperty(property);
		//寫入dgcode
		file->setGammaTable(dglut);
		if (null != componentVector) {
		    //寫入raw data
		    file->setRawData(componentVector, initialRGBGamma, finalRGBGamma);
		}
		return file;
	    };

	    void LCDCalibrator::storeDGLutFile(const std::
					       string & filename,
					       RGB_vector_ptr dglut,
					       bptr < cms::colorformat::DGLutFile > dglutFile) {
		DGLutProperty property(this);
		//寫入property
		dglutFile->setProperty(property);
		//寫入dgcode
		dglutFile->setGammaTable(dglut);
		if (null != componentVector) {
		    //寫入raw data
		    dglutFile->setRawData(componentVector, initialRGBGamma, finalRGBGamma);
		}
		//return file;
	    };

	    RGB_vector_ptr LCDCalibrator::getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		DGLutOp dgop;
		dgop.setSource(dglut);

		//==============================================================
		// dim修正
		//==============================================================
		if (correct == Correct::RBInterpolation) {
		    bptr < DGLutOp > op(new RBInterpolationOp(under));
		    dgop.addOp(op);
		}
		//==============================================================


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
		switch (keepMaxLuminance) {
		case KeepMaxLuminance::NativeWhite:{
			bptr < DGLutOp > nativeWhite(new KeepNativeWhiteOp(bitDepth));
			dgop.addOp(nativeWhite);
		    }
		    break;
		case KeepMaxLuminance::NativeWhiteAdvanced:{
			//最後還是要對DG做一次smooth
			bptr < DGLutOp >
			    nativeWhiteAdv(new
					   KeepNativeWhiteAdvancedOp(bitDepth, keepMaxLumiOver));
			dgop.addOp(nativeWhiteAdv);
		    }
		    break;
		}

		if (bMax) {
		    //bmax的調整
		    bptr < DGLutOp > bmax(new BMaxOp(bitDepth));
		    dgop.addOp(bmax);
		} else if (bMax2) {
		    //bmax2的調整
		    bptr < DGLutOp > bmax2(new BMax2Op(bitDepth, bMax2Begin, bMax2Gamma));
		    dgop.addOp(bmax2);
		}

		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };

	    void LCDCalibrator::setBTargetIntensity(double bTargetIntensity) {
		this->bTargetIntensity = bTargetIntensity;
	    };

	    void LCDCalibrator::setMultiGen(bool enable, int times) {
		this->multiGen = enable;
		this->multiGenTimes = times;
	    };
	    //==================================================================
	    bptr < cms::measure::MaxMatrixIntensityAnayzer > LCDCalibrator::getNativeWhiteAnalyzer() {
		return nativeWhiteAnalyzer;
	    }
	    void LCDCalibrator::setNativeWhiteAnalyzer(bptr <
						       cms::measure::MaxMatrixIntensityAnayzer >
						       analyzer) {
		this->nativeWhiteAnalyzer = analyzer;
	    }
	};
    };
};

