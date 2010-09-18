#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
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
		} return result;
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
	    };
	    void LCDCalibrator::setGamma(double gamma) {
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
	    void LCDCalibrator::
		setKeepMaxLuminanceNativeWhiteAdvanced(int over, double gamma, bool autoParameter) {
		this->keepMaxLuminance = KeepMaxLuminance::NativeWhiteAdvanced;
		this->keepMaxLumiOver = over;
		this->keepMaxLumiGamma = gamma;
		this->autoKeepMaxLumiParameter = autoParameter;
	    };
	    void LCDCalibrator::setNewMethod(bool enable) {
		this->useNewMethod = enable;
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
		useNewMethod = false;
		bMax = bMax2 = false;
		bTargetIntensity = -1;
		originalGamma = false;
		skipInverseB = false;
		maxZDGCode = -1;
		gByPass = false;
		avoidFRCNoise = false;
		autoKeepMaxLumiParameter = false;
		multiGen = false;
		accurateMode = false;
		remapped = false;
	    };

	    Component_vector_ptr LCDCalibrator::fetchComponentVector() {
		//�q��start->end�o�쪺coponent/Y
		Component_vector_ptr componentVector = fetcher->fetchComponent(measureCondition);
		RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();

		if (componentVector == null || rgbMeasureCode->size() != componentVector->size()) {
		    return Component_vector_ptr((Component_vector *)
						null);
		} else {
		    return componentVector;
		}
	    };

	    double_vector_ptr LCDCalibrator::fetchLuminanceVector() {
		//�q��start->end�o�쪺coponent/Y
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
	       ����smooth CCT��native white�ݨD�ɡA�N�ݭnnative white analyzer
	       �A�D�o��ǽT��DG Lut
	     */
	    void LCDCalibrator::initNativeWhiteAnalyzer() {
		//=====================================================
		// �ͥX�@�շs��analyzer, ��smooth target���ɭԥ�
		// ���o��analyzer, �bsmooth��native white���ɭԥi�H�o���ǽT�����G.
		//=====================================================
		//����max matrix
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
		nativeWhiteAnalyzer =
		    bptr < MaxMatrixIntensityAnayzer > (new MaxMatrixIntensityAnayzer(mm));

		int max = bitDepth->getMaxDigitalCount();
		int blueMax = max;

		if (keepMaxLuminance ==
		    KeepMaxLuminance::NativeWhiteAdvanced && true == skipInverseB) {
		    //�Y�n���Linverse B, �h�n���q����B�b���̤���
		    //�M��]�wb�̤j�u�Ψ�����I
		    blueMax = MeasureTool::getMaxZDGCode(mm, bitDepth);
		    this->maxZDGCode = blueMax;
		}
		//�w��rgb
		RGB_ptr rgb(new RGBColor(max, max, blueMax, MaxValue::Int8Bit));
		RGB_ptr r(new RGBColor(max, 0, 0, MaxValue::Int8Bit));
		RGB_ptr g(new RGBColor(0, max, 0, MaxValue::Int8Bit));
		RGB_ptr b(new RGBColor(0, 0, blueMax, MaxValue::Int8Bit));

		int defaultWaitTimes = nativeWhiteAnalyzer->getWaitTimes();
		nativeWhiteAnalyzer->setWaitTimes(5000);
		nativeWhiteAnalyzer->beginAnalyze();
		nativeWhiteAnalyzer->setupComponent(Channel::R, r);
		nativeWhiteAnalyzer->setupComponent(Channel::G, g);
		nativeWhiteAnalyzer->setupComponent(Channel::B, b);
		nativeWhiteAnalyzer->setupComponent(Channel::W, rgb);
		nativeWhiteAnalyzer->enter();
		nativeWhiteAnalyzer->setWaitTimes(defaultWaitTimes);
		//=====================================================
	    };

	    /*
	       CCT + Gamma
	       ����PanelRegulator�n����, ���O�qLCDCalibrator�q�n���n����T, �A�Ǩ�AdvancedDGLutGenerator�h
	       �]���ݭn�N��ص��G��smooth(target�Mnative), �ҥH�����Nremapping��bAdvancedDGLutGenerator��
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		if (false == originalGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		bool doAccurate = (true == accurateMode) && (null != tconctrl);
		bptr < PanelRegulator > panelRegulator;
		if (doAccurate) {
		    bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    RGB_ptr rgb = analyzer->getReferenceRGB();
		    panelRegulator = bptr < PanelRegulator >
			(new PanelRegulator(bitDepth, tconctrl, (int) rgb->R, (int) rgb->G,
					    (int) rgb->B));
		    panelRegulator->setEnable(true);
		    remapped = true;
		}

		this->componentVector = fetchComponentVector();
		if (doAccurate) {
		    panelRegulator->setEnable(false);
		}
		if (componentVector == null) {
		    //null�N���q���Q���_
		    return RGB_vector_ptr((RGB_vector *) null);
		}

		if (true == originalGamma) {
		    //�Y�n�ĥ�original gamma, �q�q�����G�ԥXgamma, ���@�ؼ�gamma curve
		    double_vector_ptr gammaCurve = getGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}

		STORE_COMPONENT("o_fetch.xls", componentVector);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);

		DGLutGenerator generator(componentVector, keepMaxLuminance);
		const MaxValue & quantizationBit = bitDepth->getLutMaxValue();

		if (true == useNewMethod) {
		    dglut = newMethod(generator, panelRegulator);
		} else {
		    dglut = oldMethod(generator, panelRegulator, quantizationBit);
		}


		//==============================================================
		// DG Code Op block
		//==============================================================
		//�q��
		RGB_vector_ptr result = getDGLutOpResult(dglut, generator);
		//==============================================================

		//==============================================================
		// intensity���v�T�p��
		//==============================================================
		/*double_vector_ptr b1 =
		   generator.getIntensityVector(Channel::B, dglut);
		   double_vector_ptr b2 =
		   generator.getIntensityVector(Channel::B, result);
		   STORE_DOUBLE_VECTOR("b1.xls", b1);
		   STORE_DOUBLE_VECTOR("b2.xls", b2); */
		//==============================================================


		//==============================================================
		//�վ�max value, �վ��LUT�u����max value
		//==============================================================
		STORE_RGBVECTOR("6.9_dgcode_final.xls", result);
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());
		//==============================================================

		STORE_RGBVECTOR("7_dgcode_final.xls", result);
		this->dglut = result;
		return result;
	    };

	    RGB_vector_ptr LCDCalibrator::newMethod(DGLutGenerator & generator,
						    bptr < PanelRegulator > panelRegulator) {
		double brightgammaParameter = 1;
		//==========================================================
		// �s��k
		//==========================================================
		bptr < AdvancedDGLutGenerator > advgenerator;
		double_vector_ptr luminanceGammaCurve;

		if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		    bptr < PanelRegulator > panelRegulator2;
		    Component_vector_ptr componentVector2;
		    bool doAccurate = (true == accurateMode) && (true == skipInverseB)
			&& (null != tconctrl);
		    if (null == nativeWhiteAnalyzer) {
			initNativeWhiteAnalyzer();

			if (doAccurate) {
			    //�Y�nskipInverseB, �N���ӽվ㭱�O�S�ʭ��s�q��
			    int max = bitDepth->getMaxDigitalCount();
			    panelRegulator2 = bptr < PanelRegulator >
				(new PanelRegulator(bitDepth, tconctrl, max, max, maxZDGCode));
			    panelRegulator2->setEnable(true);
			    componentVector2 = fetchComponentVector();
			    STORE_COMPONENT("o_fetch2.xls", componentVector2);
			    panelRegulator2->setEnable(false);
			}
		    }

		    brightgammaParameter = keepMaxLumiGamma;
		    advgenerator = bptr < AdvancedDGLutGenerator >
			(new AdvancedDGLutGenerator(componentVector, fetcher,
						    fetcher->getAnalyzer(),
						    nativeWhiteAnalyzer, bitDepth));
		    if (doAccurate) {
			advgenerator->setComponentVector2(componentVector2, panelRegulator2);
		    }
		    //==============================================================================
		    // luminanceGammaCurve���p��
		    //==============================================================================
		    // max luminance���ĥ��٬O�ܦ���ĳ
		    double maxLuminance =
			(true == skipInverseB) ?
			nativeWhiteAnalyzer->getReferenceColor()->Y : (*componentVector)[0]->XYZ->Y;
		    double minLuminance = (*componentVector)[componentVector->size() - 1]->XYZ->Y;
		    //�ǥѶǲ�generator����luminance gamma curve
		    luminanceGammaCurve =
			generator.getLuminanceGammaCurve(gammaCurve, maxLuminance, minLuminance);
		    //==============================================================================
		} else {
		    advgenerator =
			bptr < AdvancedDGLutGenerator >
			(new AdvancedDGLutGenerator(componentVector, fetcher, bitDepth));
		    luminanceGammaCurve = generator.getLuminanceGammaCurve(gammaCurve);

		}
		STORE_DOUBLE_VECTOR("1_lumigammacurve.xls", luminanceGammaCurve);




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
		//�~���j��w��O�_�|���ӨM�w�_�l��m
		int overParameter = keepMaxLumiOver;
		int startCheckPos = 50;
		int minOverParameter = (useNewMethod
					&& autoKeepMaxLumiParameter) ? startCheckPos :
		    keepMaxLumiOver;
		advgenerator->setPanelRegulator(panelRegulator);
		int step = 4;

		bptr < IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		//analyzer�Y�S���]�w�Ltarget color, �|�Ϧ��B�J����
		XYZ_ptr targetWhite = analyzer->getReferenceColor()->toXYZ();
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		if (null != nativeWhiteAnalyzer) {
		    //nativeWhite = nativeWhiteAnalyzer->getReferenceColor()->toXYZ();
		}

		for (; overParameter >= minOverParameter; overParameter -= step) {
		    int width = bitDepth->getEffectiveLevel() - overParameter;
		    targetXYZVector =
			advgenerator->getTargetXYZVector(targetWhite, nativeWhite,
							 luminanceGammaCurve,
							 underParameter,
							 overParameter,
							 dimgammaParameter,
							 brightgammaParameter, width);
		    dglut = advgenerator->produce(targetXYZVector);

		    if (autoKeepMaxLumiParameter) {
			//�ˬd���ɭ�, �٬O�ݭn�N��Ӭy�{�]���~���ˬd.
			//�ҥH�~�ݭn�I�sgetDGLutOpResult��changeMaxValue
			//���O�^�Ǫ��ɭԭn�^�ǩ|���B�̪����G, ���ӧ��ˬd�Ϊ��^��
			RGB_vector_ptr checkResult = RGBVector::deepClone(dglut);
			checkResult = getDGLutOpResult(checkResult, generator);
			//�n����FRC��bit�U�ˬd�~�O���T��, �ӫDLUT��bit
			RGBVector::changeMaxValue(checkResult, bitDepth->getFRCAbilityBit());
			//�ˬd
			if (RGBVector::
			    isAscend(checkResult, startCheckPos, bitDepth->getMaxDigitalCount())) {
			    //STORE_RGBVECTOR("checkResult.xls", checkResult);
			    break;
			}
		    }
		}
		keepMaxLumiOver = autoKeepMaxLumiParameter ? overParameter + step : keepMaxLumiOver;
		STORE_RGBVECTOR("3_dgcode.xls", dglut);
		return dglut;
		//==========================================================
	    };

	    RGB_vector_ptr LCDCalibrator::
		oldMethod(DGLutGenerator & generator, bptr < PanelRegulator > panelRegulator,
			  const MaxValue & quantizationBit) {
		//==========================================================
		// �Ѥ�k
		//==========================================================
		RGBGamma_ptr rgbgamma = generator.getRGBGamma(gammaCurve);
		initialRGBGamma = rgbgamma->clone();

		STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);


		/* TODO : bIntensityGain�n�T�{ */
		if (bIntensityGain != 1.0) {
		    //���s���ͥؼ�gamma curve
		    bptr < BIntensityGainOp >
			bgain(new BIntensityGainOp(bIntensityGain, 236, bitDepth));

		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(bgain);
		    rgbgamma = gammaop.createInstance();
		    STORE_RGBGAMMA("2_rgbgamma_bGain.xls", rgbgamma);
		}
		//�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		RGB_vector_ptr dglut = generator.getCCTDGLut(rgbgamma);
		STORE_RGBVECTOR("3_dgcode.xls", dglut);
		//==============================================================
		//�Ĥ@���q�ƳB�z
		//==============================================================
		//�q��
		//MaxValue quantizationBit = bitDepth->getLutMaxValue();
		if (null != panelRegulator) {
		    dglut = panelRegulator->remapping(dglut);
		    STORE_RGBVECTOR("3.1_remap.xls", dglut);
		}
		RGBVector::quantization(dglut, quantizationBit);
		//==============================================================

		if (correct == Correct::P1P2) {
		    //==========================================================
		    //p1p2�Ĥ@���q, ��gamma���վ�
		    //==========================================================
		    bptr < P1P2GammaOp > p1p2(new P1P2GammaOp(p1, p2, dglut));
		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(p1p2);

		    //���ͭץ��᪺gamma2(�Y�S��p1p2,�h����ʤ���)
		    rgbgamma = gammaop.createInstance();
		    STORE_RGBGAMMA("4_rgbgamma_p1p2.xls", rgbgamma);

		    //�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    //�q��
		    STORE_RGBVECTOR("4.9_dgcode_p1p2g.xls", dglut);
		    RGBVector::quantization(dglut, quantizationBit);
		    STORE_RGBVECTOR("5_dgcode_p1p2g.xls", dglut);
		    //==========================================================


		    //==========================================================
		    //p1p2�ĤG���q, ��dg code�վ�
		    //==========================================================
		    DGLutOp dgop;
		    dgop.setSource(dglut);
		    bptr < DGLutOp > op(new P1P2DGOp(p1, p2));
		    dgop.addOp(op);
		    dglut = dgop.createInstance();
		    //�q��
		    STORE_RGBVECTOR("6_dgcode_p1p2dg.xls", dglut);
		    //==========================================================
		}
		finalRGBGamma = rgbgamma;
		return dglut;
		//==========================================================
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
		    //�Ȥ�����
		    dglut = RGB_vector_ptr((RGB_vector *) null);
		    return dglut;
		} else {
		    double_vector_ptr luminanceVector = fetchLuminanceVector();
		    STORE_DOUBLE_VECTOR("o_fetch.xls", luminanceVector);

		    if (luminanceVector == null) {
			return RGB_vector_ptr((RGB_vector *) null);
		    }

		    DGLutGenerator generator(luminanceVector);
		    dglut = generator.getGammaDGLut(gammaCurve);

		}
		//�q��
		MaxValue quantizationBit = bitDepth->getLutMaxValue();
		RGBVector::quantization(dglut, quantizationBit);
		//�վ�max value
		RGBVector::changeMaxValue(dglut, bitDepth->getLutMaxValue());

		this->dglut = dglut;
		return dglut;
	    };

	    bptr < DGLutFile >
		LCDCalibrator::storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut) {
		//�屼�w�s�b��
		Util::deleteExist(filename);
		//���ͷs��
		bptr < DGLutFile > file(new DGLutFile(filename, Create));
		storeDGLutFile(dglut, file);
		return file;
	    };

	    void LCDCalibrator::storeDGLutFile(RGB_vector_ptr dglut,
					       bptr < cms::colorformat::DGLutFile > dglutFile) {
		DGLutProperty property(this);
		//�g�Jproperty
		dglutFile->setProperty(property);
		//�g�Jdgcode
		dglutFile->setGammaTable(dglut);
		if (null != componentVector) {
		    //�g�Jraw data
		    dglutFile->setRawData(componentVector, initialRGBGamma, finalRGBGamma);
		}
		if (null != targetXYZVector) {
		    dglutFile->setTargetXYZVector(targetXYZVector);
		}
	    };

	    RGB_vector_ptr LCDCalibrator::getDGLutOpResult(RGB_vector_ptr dglut,
							   DGLutGenerator & generator) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		RGB_vector_ptr source = RGBVector::deepClone(dglut);
		DGLutOp dgop;
		dgop.setSource(source);

		//==============================================================
		// dim�ץ�
		//==============================================================
		if (correct == Correct::RBInterpolation) {
		    bptr < DGLutOp > op(new RBInterpolationOp(under));
		    dgop.addOp(op);
		}
		//==============================================================


		if (gByPass) {
		    //g bypass���վ�
		    bptr < DGLutOp > gbypass(new GByPassOp(bitDepth));
		    dgop.addOp(gbypass);
		}
		if (avoidFRCNoise) {
		    //frc noise���վ�
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
			//�̫��٬O�n��DG���@��smooth
			bptr < DGLutOp >
			    nativeWhiteAdv(new
					   KeepNativeWhiteAdvancedOp(bitDepth, keepMaxLumiOver,
								     false));
			dgop.addOp(nativeWhiteAdv);
		    }
		    break;
		}

		if (bMax) {
		    //bmax���վ�
		    bptr < DGLutOp > bmax(new BMaxOp(bitDepth));
		    dgop.addOp(bmax);
		} else if (bMax2) {
		    //bmax2���վ�
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
						       cms::measure::
						       MaxMatrixIntensityAnayzer > analyzer) {
		this->nativeWhiteAnalyzer = analyzer;
	    };
	    void LCDCalibrator::setTCONControl(bptr < i2c::TCONControl > tconctrl) {
		this->tconctrl = tconctrl;
	    };
	    void LCDCalibrator::setAccurateMode(bool enable) {
		this->accurateMode = enable;
	    };
	};
    };
};
