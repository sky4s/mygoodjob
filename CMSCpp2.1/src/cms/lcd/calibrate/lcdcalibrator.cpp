#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"
#include <gui/cct/TMainForm.h>
//#include <cms/colorformat/excelfile.h>
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
	    using namespace Indep;
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
		this->dimFixEnd = under;
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

	    void LCDCalibrator::setBMax2(bool bMax2, int begin, double gamma) {
		this->bMax2 = bMax2;
		bMax2Begin = begin;
		bMax2Gamma = gamma;
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

	  LCDCalibrator::LCDCalibrator(bptr < ComponentFetcher > fetcher, bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {
		rgbIndepGamma = false;
		useGammaCurve = false;
		bIntensityGain = 1;
		under = 50;
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
		manualAccurateMode = false;
		middleCCTRatio = -1;
		dimFixEnd = 50;
		dimFix = false;
		dimFixThreshold = 0.0000;
		modifiedTarget = false;
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
	       ��smooth CCT��native white�ݨD�ɡA�N�ݭnnative white analyzer
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
		    bptr < MaxMatrixIntensityAnalyzer > (new MaxMatrixIntensityAnalyzer(mm));

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
		    //���: �Htarget white��rgb���̤j��, �վ㭱�O�í��s�q��
		    //��}: �Hdirect gamma(gamma test)�������ܥ��X��pattern, �F��ۦP�ĪG

		    bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    RGB_ptr rgb = analyzer->getReferenceRGB();
		    panelRegulator = bptr < PanelRegulator >
			(new
			 GammaTestPanelRegulator(bitDepth, tconctrl, (int) rgb->R, (int) rgb->G,
						 (int) rgb->B, measureCondition));
		    if (false == this->manualAccurateMode) {
			panelRegulator->setEnable(true);
		    }
		    remapped = true;
		}

		this->componentVector = fetchComponentVector();
		if (doAccurate) {
		    panelRegulator->setEnable(false);
		}
		if (componentVector == null) {
		    //null�N��q���Q���_
		    return RGB_vector_ptr((RGB_vector *) null);
		}

		if (true == originalGamma) {
		    //�Y�n�ĥ�original gamma, �q�q�����G�ԥXgamma, ��@�ؼ�gamma curve
		    double_vector_ptr gammaCurve = getGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}

		STORE_COMPONENT("o_fetch.xls", componentVector);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);

		DGLutGenerator generator(componentVector, keepMaxLuminance);
		const MaxValue & quantizationBit = bitDepth->getLutMaxValue();

		if (true == useNewMethod) {
		    //�s��k��������פW���B�z
		    dglut = newMethod(generator, panelRegulator);
		} else {
		    //�¤�k�ĦX��ץH��DG Code���B�z
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
		STORE_RGBVECTOR("7.9_dgcode_final.xls", result);
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());
		//==============================================================
		//�w���ͥXDG, �i�b���B�q��
		/*if (dimFix) {
		   //STORE_RGBVECTOR("7.1_before_dimFix.xls", result);
		   result = dimDGLutFix(result);
		   //STORE_RGBVECTOR("7.2_after_dimFix.xls", result);
		   } */


		STORE_RGBVECTOR("8_dgcode_final.xls", result);
		this->dglut = result;
		return result;
	    };

	    /*
	       generator�b�����ηN�u�O���Ӳ���gamma curve
	     */
	    RGB_vector_ptr LCDCalibrator::newMethod(DGLutGenerator & generator,
						    bptr < PanelRegulator > panelRegulator) {
		double brightgammaParameter = 1;
		//==========================================================
		// �s��k
		//==========================================================
		bptr < AdvancedDGLutGenerator > advgenerator;
		double_vector_ptr luminanceGammaCurve;

		//=============================================================
		// ���� luminance gamma curve
		//=============================================================
		if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		    //NativeWhiteAdvanced�O���F���UHook�M�̤j�G�ת���J����
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
				(new
				 GammaTestPanelRegulator(bitDepth, tconctrl, max, max,
							 maxZDGCode, measureCondition));
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
		    //�H�̤j�G�׬�Target White���i�J�I
		    //componentVector�O�ƥ��q�n��(�I�s��function���e)

		    bool smoothDim = true;
		    //�յ�smooth componentVector, �o���smooth ��dg lut
		    Component_vector_ptr copy = componentVector;
		    if (smoothDim) {
			Component_vector_ptr copy = Util::copy(componentVector);
			smoothDimComponentVector(copy);
			STORE_COMPONENT("o_fetch_smooth.xls", copy);
		    }
		    advgenerator =
			bptr < AdvancedDGLutGenerator >
			(new AdvancedDGLutGenerator(copy, fetcher, bitDepth));
		    luminanceGammaCurve = generator.getLuminanceGammaCurve(gammaCurve);
		    keepMaxLumiOver = bitDepth->getEffectiveLevel();

		}
		//=============================================================
		STORE_DOUBLE_VECTOR("1_lumigammacurve.xls", luminanceGammaCurve);


		double dimgammaParameter = 1;
		int underParameter = 50;

		if (correct == Correct::DefinedDim) {
		    dimgammaParameter = dimGamma;
		    underParameter = under;
		}
		//=================================================================================
		// advgenerator options
		//=================================================================================
		if (this->bTargetIntensity != -1) {
		    advgenerator->setBTargetIntensity(bTargetIntensity);
		}
		if (multiGen) {
		    advgenerator->setMultiGen(multiGen, multiGenTimes);
		}
		if (middleCCTRatio != -1) {
		    advgenerator->setMiddleCCTRatio(middleCCTRatio);
		}
		//=================================================================================

		//�~���j��w��O�_�|���ӨM�w�_�l��m
		//�o�䪺����O: �p�G����I�]�w����(�Ӥp�ӱ���0), �N�i��y���|��
		//�ҥH�v���վ�����I�����|������
		int overParameter = keepMaxLumiOver;
		int startCheckPos = 50;
		int minOverParameter = (useNewMethod && autoKeepMaxLumiParameter) ?
		    startCheckPos : keepMaxLumiOver;
		//int minOverParameter = startCheckPos;
		advgenerator->setPanelRegulator(panelRegulator);
		const int step = 4;

		bptr < IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		//analyzer�Y�S���]�w�Ltarget color, �|�Ϧ��B�J����
		//�]��analyzer->getReferenceColor()�|�Onull
		XYZ_ptr targetWhite = analyzer->getReferenceColor()->toXYZ();
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		if (null != nativeWhiteAnalyzer) {
		    //nativeWhite = nativeWhiteAnalyzer->getReferenceColor()->toXYZ();
		}

		for (; overParameter >= minOverParameter; overParameter -= step) {
		    int width = bitDepth->getEffectiveLevel() - overParameter;
		    //�p��o��ؼЭ�
		    targetXYZVector =
			advgenerator->getTargetXYZVector(targetWhite, nativeWhite,
							 luminanceGammaCurve,
							 underParameter,
							 overParameter,
							 dimgammaParameter,
							 brightgammaParameter, width);
		    //�q�ؼЭȺ�XDGLut
		    dglut = advgenerator->produce(targetXYZVector);
		    STORE_RGBVECTOR("3.1_org_dgcode.xls", dglut);
		    if (true == modifiedTarget
			&& (true != MainForm->linkCA210 || MainForm->isTCONInput())) {
			//���qDGLut��X�Ƕ���dx dy
			//�A�q�o�˪����G�L�եؼЭ�
			//Component_vector_ptr dimComponentVector = getDimComponentVector(dglut);
			RGB_vector_ptr measureCode = RGBVector::copyRange(dglut, 0, dimFixEnd);

			bool debug = !MainForm->linkCA210;
			double_vector_ptr dxofBase, dyofBase, dxofR, dyofG;
			if (!debug) {
			    bptr < MeasureEstimator >
				chromaticityEstimator(new MeasureEstimator(measureCode,
									   fetcher->getAnalyzer(),
									   bitDepth));
			    chromaticityEstimator->measure(0, dimFixEnd);

			    /*double_vector_ptr dxofBase = chromaticityEstimator->dxofBase;
			       double_vector_ptr dyofBase = chromaticityEstimator->dyofBase;
			       double_vector_ptr dxofR = chromaticityEstimator->dxofRVector;
			       double_vector_ptr dyofG = chromaticityEstimator->dyofGVector; */
			    dxofR = chromaticityEstimator->dxofRVector;
			    dyofG = chromaticityEstimator->dyofGVector;
			    dxofBase = chromaticityEstimator->dxofBase;
			    dyofBase = chromaticityEstimator->dyofBase;

			    STORE_DOUBLE_VECTOR("dxofR.xls", dxofR);
			    STORE_DOUBLE_VECTOR("dyofG.xls", dyofG);
			    STORE_DOUBLE_VECTOR("dxofBase.xls", dxofBase);
			    STORE_DOUBLE_VECTOR("dyofBase.xls", dyofBase);
			} else {
			    dxofR = DoubleArray::loadFromExcel(DEBUG_DIR + _s("dxofR.xls"));
			    dyofG = DoubleArray::loadFromExcel(DEBUG_DIR + _s("dyofG.xls"));
			    dxofBase = DoubleArray::loadFromExcel(DEBUG_DIR + _s("dxofBase.xls"));
			    dyofBase = DoubleArray::loadFromExcel(DEBUG_DIR + _s("dyofBase.xls"));

			}

			double_vector_ptr dxofBaseCopy = DoubleArray::copy(dxofBase);
			double_vector_ptr dyofBaseCopy = DoubleArray::copy(dyofBase);

			RGB_vector_ptr clone = RGBVector::deepClone(dglut);
			RGBVector::changeMaxValue(clone, bitDepth->getLutMaxValue());
			STORE_RGBVECTOR("3.2_lut_dgcode.xls", clone);
			RGBVector::storeToText("3.2_lut_dgcode.txt", clone);

			RGBVector::changeMaxValue(clone, bitDepth->getFRCAbilityBit());
			STORE_RGBVECTOR("3.3_frc_dgcode.xls", clone);
			fixReverse(dxofBaseCopy, dxofR, clone, Channel::R);
			STORE_RGBVECTOR("3.4_r_reverse_fix_dgcode.xls", clone);
			fixReverse(dyofBaseCopy, dyofG, clone, Channel::G);
			STORE_RGBVECTOR("3.5_g_reverse_fix_dgcode.xls", clone);
			dglut = clone;
		    }

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
		RGBVector::changeMaxValue(dglut, MaxValue::Double255);
		STORE_RGBVECTOR("3.9_dgcode.xls", dglut);
		return dglut;
		//==========================================================
	    };
	    void LCDCalibrator::fixReverse(double_vector_ptr deltaVector,
					   double_vector_ptr deltaOfChVector,
					   RGB_vector_ptr dglut, Dep::Channel ch) {
		int size = deltaVector->size();
		for (int x = 1; x < size - 1; x++) {
		    double delta = (*deltaVector)[x];
		    if (delta < 0) {
			//������, �N�����B���e(�]�t����)����-1
			//int a = 1;
			for (int y = x; y <= x; y++) {
			    double delta = (*deltaVector)[y];
			    double deltaOfCh = (*deltaOfChVector)[y];
			    if ((delta - deltaOfCh) >= 0) {
				RGB_ptr rgb = (*dglut)[y];
				double value = rgb->getValue(ch);
				value--;
				rgb->setValue(ch, value);

				delta -= deltaOfCh;	//����i���ܭt��! �n�קK!
				(*deltaVector)[y] = delta;

				double nextdelta = (*deltaVector)[y + 1];
				nextdelta += deltaOfCh;
				(*deltaVector)[y + 1] = nextdelta;
			    }
			}
			fixReverse(deltaVector, deltaOfChVector, dglut, ch);
			return;
		    }
		}
	    }



	    RGB_vector_ptr LCDCalibrator::
		oldMethod(DGLutGenerator & generator,
			  bptr < PanelRegulator > panelRegulator,
			  const MaxValue & quantizationBit) {
		//==========================================================
		// �Ѥ�k
		//==========================================================
		RGBGamma_ptr rgbgamma = generator.getRGBGamma(gammaCurve);
		initialRGBGamma = rgbgamma->clone();
		STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);
		/* TODO : bIntensityGain�n�T�{ */
		//�ѹ�����intensity��ı�o�O���ꪺ�@�k
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
		    STORE_RGBGAMMA("4.0_rgbgamma_p1p2.xls", rgbgamma);
		    //�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    //�q��
		    STORE_RGBVECTOR("4.1_dgcode_p1p2g.xls", dglut);
		    RGBVector::quantization(dglut, quantizationBit);
		    STORE_RGBVECTOR("4.2_dgcode_p1p2g.xls", dglut);
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
		    STORE_RGBVECTOR("4.3_dgcode_p1p2dg.xls", dglut);
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
		} else
		    if (true == rgbIndepGamma
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
	    Component_vector_ptr LCDCalibrator::getDimComponentVector(RGB_vector_ptr dglut) {
		RGB_vector_ptr measureCode = RGBVector::copyRange(dglut, 0, dimFixEnd);
		//50�q��0
		measureCode = RGBVector::reverse(measureCode);
		RGBVector::quantization(measureCode, bitDepth->getFRCAbilityBit());
		bptr < MeasureCondition > measureCondition(new MeasureCondition(measureCode));
		Component_vector_ptr componentVector;	// = fetcher->fetchComponent(measureCondition);
		if (true == MainForm->linkCA210) {
		    //���s�Wca210�N�q�����o
		    componentVector = fetcher->fetchComponent(measureCondition);
		} else {
		    //�_�h�N�����e���ɮרӷ�q���ƾ�
		    DGLutFile dglut("5.0_dimComponent.xls", ReadOnly);
		    componentVector = dglut.getComponentVector();
		}
		STORE_COMPONENT("5.0_dimComponent.xls", componentVector);
		return componentVector;
	    };
	    void LCDCalibrator::smoothDimComponentVector(Component_vector_ptr componentVector) {
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		/*bptr < cms::measure::MaxMatrixIntensityAnalyzer > mmanalyzer =
		   bptr < cms::measure::MaxMatrixIntensityAnalyzer >
		   (dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get())); */
		MaxMatrixIntensityAnalyzer *manalyzer =
		    dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
		int size = componentVector->size();
		if (null != manalyzer) {
		    for (int gl = 1; gl < dimFixEnd; gl++) {
			int x = size - 1 - gl;
			//for (int x = 1; x < dimFixEnd - 1; x++) {
			Component_ptr c0 = (*componentVector)[x + 1];
			Component_ptr c1 = (*componentVector)[x];
			Component_ptr c2 = (*componentVector)[x - 1];
			XYZ_ptr XYZ0 = c0->XYZ;
			XYZ_ptr XYZ1 = c1->XYZ;
			XYZ_ptr XYZ2 = c2->XYZ;
			xyY_ptr xyY0(new CIExyY(XYZ0));
			xyY_ptr xyY1(new CIExyY(XYZ1));
			xyY_ptr xyY2(new CIExyY(XYZ2));
			xyY1->x = Interpolation::linear(0, 1, xyY0->x, xyY2->x, 0.5);
			xyY1->y = Interpolation::linear(0, 1, xyY0->y, xyY2->y, 0.5);
			c1->XYZ = xyY1->toXYZ();
			RGB_ptr intensity = manalyzer->getIntensity(c1->XYZ);
			c1->intensity = intensity;
		    }
		}
	    };
	    RGB_vector_ptr LCDCalibrator::
		getDGLutOpResult(RGB_vector_ptr dglut, DGLutGenerator & generator) {
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
					   KeepNativeWhiteAdvancedOp(bitDepth,
								     keepMaxLumiOver, false));
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
		//==============================================================
		// dim�ץ�, �bxy domain�W�i��
		//==============================================================

		if (dimFix) {
		    //50�q��0
		    Component_vector_ptr componentVector = getDimComponentVector(dglut);
		    bptr < ChromaticityAdjustEstimatorIF >
			chromaticityEstimator(new
					      MeasureEstimator(componentVector,
							       fetcher->getAnalyzer(), bitDepth));
		    bptr < DGLutOp >
			dimfix(new
			       DimDGLutFixOp(bitDepth, dimFixThreshold, componentVector,
					     chromaticityEstimator));
		    dgop.addOp(dimfix);
		}
		//==============================================================

		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };
	    /*void LCDCalibrator::setBTargetIntensity(double bTargetIntensity) {
	       this->bTargetIntensity = bTargetIntensity;
	       }; */
	    void LCDCalibrator::setMultiGen(bool enable, int times) {
		this->multiGen = enable;
		this->multiGenTimes = times;
	    };
	    //==================================================================
	    xyY_ptr IntensityEstimator::getxyY(RGB_ptr intensity) {
		XYZ_ptr rXYZ2 = rXYZ->clone();
		XYZ_ptr gXYZ2 = gXYZ->clone();
		XYZ_ptr bXYZ2 = bXYZ->clone();
		rXYZ2->times(intensity->R / 100.);
		gXYZ2->times(intensity->G / 100.);
		bXYZ2->times(intensity->B / 100.);
		XYZ_ptr rgXYZ = CIEXYZ::plus(rXYZ2, gXYZ2);
		XYZ_ptr XYZ = CIEXYZ::plus(rgXYZ, bXYZ2);
		xyY_ptr xyY(new CIExyY(XYZ));
		return xyY;
	    };
	  IntensityEstimator::IntensityEstimator(Component_vector_ptr componentVector, bptr < cms::measure::IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):componentVector(componentVector), analyzer(analyzer),
		bitDepth(bitDepth),
		dgLutGenerator(bptr < DGLutGenerator > (new DGLutGenerator(componentVector))) {
		xyY_ptr xyYR = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr xyYG = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr xyYB = analyzer->getPrimaryColor(Channel::B);
		rXYZ = xyYR->toXYZ();
		gXYZ = xyYG->toXYZ();
		bXYZ = xyYB->toXYZ();
		//dgLutGenerator = DGLutGenerator(componentVector);
	    };
	    double_array IntensityEstimator::getdxdy(const Dep::Channel & ch, int grayLevel) {
		int size = componentVector->size();
		int index = size - grayLevel - 1;
		Component_ptr c = (*componentVector)[index];
		//RGB_ptr orgrgb = c->rgb;
		const Dep::MaxValue & lutMaxValue = bitDepth->getLutMaxValue();
		RGB_ptr rgb = c->rgb->clone();
		RGB_ptr intensity = dgLutGenerator->getIntensity(rgb);
		rgb->changeMaxValue(lutMaxValue);
		rgb->addValue(ch, 1);
		rgb->changeMaxValue(MaxValue::Double255);
		RGB_ptr intensity2 = dgLutGenerator->getIntensity(rgb);
		xyY_ptr xyY = getxyY(intensity);
		xyY_ptr xyY2 = getxyY(intensity2);
		double_array dxdy = DoubleArray::minus(xyY->getxyValues(), xyY2->getxyValues(), 2);
		return dxdy;
	    };
	    double_array IntensityEstimator::getRdxGdy(int componentIndex) {
	    }
	    //=================================================================
	    // MeasureEstimator
	    //=================================================================
	    void MeasureEstimator::init() {
		if (true == MainForm->linkCA210) {
		    storeComponentVector = Component_vector_ptr(new Component_vector());
		} else {
		    DGLutFile dglut(DEBUG_DIR + _s("MeasureEstimator.xls"), ReadOnly);
		    storeComponentVector = dglut.getComponentVector();
		    storeIndex = 0;
		}
	    };
	  MeasureEstimator::MeasureEstimator(Component_vector_ptr componentVector, bptr < cms::measure::MeterMeasurement > mm, bptr < BitDepthProcessor > bitDepth):componentVector(componentVector), mm(mm),
		bitDepth(bitDepth), size(componentVector->size()),
		useComponentVector(true) {
		init();
	    };
	  MeasureEstimator::MeasureEstimator(Component_vector_ptr componentVector, bptr < cms::measure::IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):componentVector(componentVector),
		mm(analyzer->getMeterMeasurement()), bitDepth(bitDepth),
		size(componentVector->size()), useComponentVector(true) {
		init();
	    };
	  MeasureEstimator::MeasureEstimator(RGB_vector_ptr dglut, bptr < cms::measure::IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):dglut(dglut), mm(analyzer->getMeterMeasurement()),
		bitDepth(bitDepth), size(dglut->size()),
		useComponentVector(false) {
		init();
	    };
	    double_array MeasureEstimator::getdxdy(const Dep::Channel & ch, int componentIndex) {
		if (true == MainForm->linkCA210) {
		    RGB_ptr dg0 = getMeasureBaseRGB(componentIndex);
		    dg0->changeMaxValue(bitDepth->getFRCAbilityBit());
		    XYZ_ptr XYZ0 = measure(dg0);
		    RGB_ptr dg1 = dg0->clone();
		    dg1->addValue(ch, 1);
		    XYZ_ptr XYZ1 = measure(dg1);
		    double_array delta = getdxdy(XYZ0, XYZ1);
		    /*Component_ptr c0(new Component(dg0, nil_RGB_ptr, XYZ0));
		       Component_ptr c1(new Component(dg1, nil_RGB_ptr, XYZ1));
		       storeComponentVector->push_back(c0);
		       storeComponentVector->push_back(c1); */
		    return delta;
		} else {
		    Component_ptr c0 = (*storeComponentVector)[storeIndex++];
		    Component_ptr c1 = (*storeComponentVector)[storeIndex++];
		    XYZ_ptr XYZ0 = c0->XYZ;
		    XYZ_ptr XYZ1 = c1->XYZ;
		    double_array delta = getdxdy(XYZ0, XYZ1);
		    return delta;
		}
	    };
	    double_array MeasureEstimator::getRdxGdy(int componentIndex) {
		if (true == MainForm->linkCA210) {
		    RGB_ptr dg0 = getMeasureBaseRGB(componentIndex);
		    dg0->changeMaxValue(bitDepth->getFRCAbilityBit());
		    RGB_ptr dg1 = dg0->clone();
		    dg1->addValue(Channel::R, 1);
		    RGB_ptr dg2 = dg0->clone();
		    dg2->addValue(Channel::G, 1);

		    XYZ_ptr XYZ2 = measure(dg2);
		    XYZ_ptr XYZ1 = measure(dg1);
		    XYZ_ptr XYZ0 = measure(dg0);


		    baseXYZ = XYZ0;
		    double_array delta1 = getdxdy(XYZ0, XYZ1);
		    double_array delta2 = getdxdy(XYZ0, XYZ2);
		    double_array delta(new double[2]);
		    delta[0] = delta1[0];
		    delta[1] = delta2[1];
		    /*Component_ptr c0(new Component(dg0, nil_RGB_ptr, XYZ0));
		       Component_ptr c1(new Component(dg1, nil_RGB_ptr, XYZ1));
		       Component_ptr c2(new Component(dg2, nil_RGB_ptr, XYZ2));
		       storeComponentVector->push_back(c0);
		       storeComponentVector->push_back(c1);
		       storeComponentVector->push_back(c2); */
		    return delta;
		} else {
		    Component_ptr c0 = (*storeComponentVector)[storeIndex++];
		    Component_ptr c1 = (*storeComponentVector)[storeIndex++];
		    Component_ptr c2 = (*storeComponentVector)[storeIndex++];
		    XYZ_ptr XYZ0 = c0->XYZ;
		    XYZ_ptr XYZ1 = c1->XYZ;
		    XYZ_ptr XYZ2 = c2->XYZ;
		    double_array delta1 = getdxdy(XYZ0, XYZ1);
		    double_array delta2 = getdxdy(XYZ0, XYZ2);
		    double_array delta(new double[2]);
		    delta[0] = delta1[0];
		    delta[1] = delta2[1];
		    return delta;
		}
	    };
	    RGB_ptr MeasureEstimator::getMeasureBaseRGB(int index) {
		if (useComponentVector) {
		    Component_ptr c = (*componentVector)[index];
		    RGB_ptr dg = c->rgb->clone();
		    return dg;
		} else {
		    RGB_ptr dg = (*dglut)[index]->clone();
		    return dg;
		}
	    };
	    double_array MeasureEstimator::getdxdy(XYZ_ptr XYZ0, XYZ_ptr XYZ1) {
		double_array xy0Values = XYZ0->getxyValues();
		double_array xy1Values = XYZ1->getxyValues();
		double_array delta = DoubleArray::minus(xy1Values, xy0Values, 2);
		return delta;
	    };
	    MeasureEstimator::~MeasureEstimator() {
		STORE_COMPONENT("MeasureEstimator.xls", storeComponentVector);
		mm->close();
	    };
	    void MeasureEstimator::measure(int startIndex, int endIndex) {
		if (true) {
		    measure0(startIndex, endIndex);
		    return;
		}
		resetMeasure();
		RGB_ptr dg0 = getMeasureBaseRGB(startIndex);
		if (true == MainForm->linkCA210) {
		    baseXYZ = measure(dg0);
		    //Component_ptr c0(new Component(dg0, nil_RGB_ptr, baseXYZ));
		    //storeComponentVector->push_back(c0);
		} else {
		    Component_ptr c0 = (*storeComponentVector)[storeIndex++];
		    baseXYZ = c0->XYZ;
		}


		for (int x = startIndex; x <= endIndex; x++) {
		    XYZ_ptr lastXYZ = baseXYZ;
		    double_array RdxGdy = getRdxGdy(x);
		    XYZ_ptr thisXYZ = baseXYZ;
		    xyY_ptr lastxyY(new CIExyY(lastXYZ));
		    xyY_ptr thisxyY(new CIExyY(thisXYZ));
		    double_array dxdy = thisxyY->getDeltaxy(lastxyY);
		    dxofBase->push_back(dxdy[0]);
		    dyofBase->push_back(dxdy[1]);
		    dxofRVector->push_back(RdxGdy[0]);
		    dyofGVector->push_back(RdxGdy[1]);
		}
	    };
	    void MeasureEstimator::measure0(int startIndex, int endIndex) {
		resetMeasure();
		const Dep::MaxValue & frcBit = bitDepth->getFRCAbilityBit();
		XYZ_vector_ptr baseXYZVec(new XYZ_vector());

		//���qbase
		for (int x = endIndex; x >= startIndex; x--) {
		    RGB_ptr rgb = getMeasureBaseRGB(x);
		    XYZ_ptr XYZ = measure(rgb);
		    baseXYZVec->push_back(XYZ);
		}
		//�q���A�Ӱ��B��
		int size = baseXYZVec->size();
		//���F��base�Mr/g�i�H���, �ҥH�h��@��0
		dxofBase->push_back(0);
		dyofBase->push_back(0);
		for (int x = size - 2; x >= 0; x--) {
		    XYZ_ptr XYZ0 = (*baseXYZVec)[x + 1];
		    XYZ_ptr XYZ1 = (*baseXYZVec)[x];
		    double_array dxy = getdxdy(XYZ0, XYZ1);
		    dxofBase->push_back(dxy[0]);
		    dyofBase->push_back(dxy[1]);
		};


		/*for (int x = startIndex; x <= endIndex; x++) {
		   double_array RdxGdy = getRdxGdy(x);
		   dxofRVector->push_back(RdxGdy[0]);
		   dyofGVector->push_back(RdxGdy[1]);
		   } */
		for (int x = endIndex; x >= startIndex; x--) {
		    double_array RdxGdy = getRdxGdy(x);
		    dxofRVector->push_back(RdxGdy[0]);
		    dyofGVector->push_back(RdxGdy[1]);
		}
		dxofRVector = DoubleArray::getReverse(dxofRVector);
		dyofGVector = DoubleArray::getReverse(dyofGVector);

	    }

	    XYZ_ptr MeasureEstimator::measure(RGB_ptr rgb) {
		Patch_ptr p = mm->measure(rgb, nil_string_ptr);
		XYZ_ptr XYZ = p->getXYZ();
		Component_ptr c(new Component(rgb, nil_RGB_ptr, XYZ));
		storeComponentVector->push_back(c);
		return XYZ;
	    };
	    void MeasureEstimator::resetMeasure() {
		dxofRVector = double_vector_ptr(new double_vector());
		dyofGVector = double_vector_ptr(new double_vector());
		dxofBase = double_vector_ptr(new double_vector());
		dyofBase = double_vector_ptr(new double_vector());
	    };
	    //=================================================================
	};
    };
};

