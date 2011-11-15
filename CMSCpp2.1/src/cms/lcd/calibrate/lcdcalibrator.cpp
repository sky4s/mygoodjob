#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"
#include <gui/cct/TMainForm.h>
//#include <cms/colorformat/excelfile.h>
//C�t�Τ��

//C++�t�Τ��
#include <algorithm>

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

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double dimGamma, int dimGammaEnd,
						   double brightGamma, int n, int effectiven) {
		double_vector_ptr result(new double_vector(n));

		for (int x = 0; x <= dimGammaEnd; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double v = Math::pow(normal, dimGamma);
		    (*result)[x] = v;
		}
		int brightGammaStart = dimGammaEnd + 1;
		for (int x = brightGammaStart; x < effectiven; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double gamma = Interpolation::linear(dimGammaEnd, effectiven - 1, dimGamma,
							 brightGamma, x);
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

	    void LCDCalibrator::setDefinedDim(int under, double strength) {
		this->correct = Correct::DefinedDim;
		this->under = under;
		this->dimFixEnd = under;
		this->dimStrength = strength;

	    };

	    void LCDCalibrator::setGamma(double gamma) {
		this->gamma = gamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveInputLevel();
		setGammaCurve0(getGammaCurveVector(gamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::setGamma(double dimGamma, int dimGammaEnd, double brightGamma) {
		this->gamma = brightGamma;
		this->dimGamma = dimGamma;
		this->dimGammaEnd = dimGammaEnd;

		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveInputLevel();
		setGammaCurve0(getGammaCurveVector(dimGamma, dimGammaEnd, gamma, n, effectiven));
		useGammaCurve = false;
		rgbIndepGamma = false;
	    };
	    void LCDCalibrator::setGamma(double rgamma, double ggamma, double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveInputLevel();
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
		gamma = rgamma = ggamma = bgamma = dimGamma = -1;
		dimGammaEnd = 50;
		this->fetcher = fetcher;
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
		feedbackFix = false;
		smoothComponent = false;
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

	    double_vector_ptr LCDCalibrator::
		getOriginalGammaCurve(Component_vector_ptr componentVector) {
		double_vector_ptr keys(new double_vector());
		double_vector_ptr values(new double_vector());
		int size = componentVector->size();

		Component_ptr white = (*componentVector)[0];
		Component_ptr black = (*componentVector)[size - 1];
		double maxLuminance = white->XYZ->Y;
		double minLuminance = black->XYZ->Y;
		//double max = white->rgb->getMaxValue().max;
		double max = bitDepth->getOutputMaxDigitalCount();

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
		int effectiven = max + 1;	//bitDepth->getEffectiveLevel();
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

		int max = bitDepth->getOutputMaxDigitalCount();
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

		this->originalComponentVector = fetchComponentVector();
		if (null == originalComponentVector) {
		    return nil_RGB_vector_ptr;
		}
		STORE_COMPONENT("o_fetch.xls", originalComponentVector);

		//�յ�smooth componentVector, �o���smooth ��dg lut
		this->componentVector = Util::copy(originalComponentVector);
		if (smoothComponent) {
		    //smoothComponentVector(componentVector);
		    smoothComponentVector2(componentVector);
		    STORE_COMPONENT("o_fetch_smooth.xls", componentVector);
		}


		this->componentVector = this->originalComponentVector;
		if (doAccurate) {
		    panelRegulator->setEnable(false);
		}
		if (componentVector == null) {
		    //null�N��q���Q���_
		    return RGB_vector_ptr((RGB_vector *) null);
		}

		if (true == originalGamma) {
		    //�Y�n�ĥ�original gamma, �q�q�����G�ԥXgamma, ��@�ؼ�gamma curve
		    double_vector_ptr gammaCurve = getOriginalGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}


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
			    int max = bitDepth->getInputMaxDigitalCount();
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

		    /*bool smoothDim = true;
		       //�յ�smooth componentVector, �o���smooth ��dg lut
		       Component_vector_ptr copy = Util::copy(componentVector);
		       if (smoothDim) {
		       smoothDimComponentVector(copy);
		       STORE_COMPONENT("o_fetch_smooth.xls", copy);
		       } */
		    advgenerator =
			bptr < AdvancedDGLutGenerator >
			(new AdvancedDGLutGenerator(componentVector, fetcher, bitDepth));
		    luminanceGammaCurve = generator.getLuminanceGammaCurve(gammaCurve);
		    //keepMaxLumiOver = bitDepth->getInputMaxDigitalCount();
		    keepMaxLumiOver = bitDepth->getEffectiveInputLevel();

		}
		//=============================================================
		STORE_DOUBLE_VECTOR("1_lumigammacurve.xls", luminanceGammaCurve);


		double dimStrengthParameter = 1;
		int underParameter = 50;

		if (correct == Correct::DefinedDim) {
		    dimStrengthParameter = dimStrength;
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
		if (KeepMaxLuminance::TargetWhite == keepMaxLuminance) {
		    nativeWhite = targetWhite->clone();
		    nativeWhite->normalizeY();
		    double maxLuminance = (*luminanceGammaCurve)[luminanceGammaCurve->size() - 1];
		    nativeWhite->times(maxLuminance);
		}

		for (; overParameter >= minOverParameter; overParameter -= step) {
		    int width = bitDepth->getEffectiveInputLevel() - overParameter;
		    //int width = bitDepth->getLevel() - overParameter;
		    //�p��o��ؼЭ�
		    targetXYZVector =
			advgenerator->getTargetXYZVector(targetWhite, nativeWhite,
							 luminanceGammaCurve,
							 underParameter,
							 overParameter,
							 dimStrengthParameter,
							 brightgammaParameter, width);
		    //�q�ؼЭȺ�XDGLut
		    dglut = advgenerator->produce(targetXYZVector);
		    STORE_RGBVECTOR("3.1_org_dgcode.xls", dglut);
		    if (true == feedbackFix
			&& (true != MainForm->linkCA210 || MainForm->isTCONInput())) {
			//���qDGLut��X�Ƕ���dx dy
			//�A�q�o�˪����G�L�եؼЭ�

			//==============================================================
			RGB_vector_ptr clone = RGBVector::deepClone(dglut);

			RGBVector::changeMaxValue(clone, bitDepth->getLutMaxValue());
			STORE_RGBVECTOR("3.2_lut_dgcode.xls", clone);
			RGBVector::storeToText("3.2_lut_dgcode(beforeFeedback).txt", clone);

			RGBVector::changeMaxValue(clone, bitDepth->getFRCAbilityBit());
			STORE_RGBVECTOR("3.3_frc_dgcode.xls", clone);
			//==============================================================
			RGB_vector_ptr clone2 = RGBVector::deepClone(dglut);

			int frcBit = bitDepth->getFRCAbilityBit().bit;
			int domainBit = frcBit + 2;
			const MaxValue & domainMaxValue = MaxValue::getByIntegerBit(domainBit);
			RGBVector::changeMaxValue(clone2, domainMaxValue);
			STORE_RGBVECTOR("3.4_domain_dgcode.xls", clone2);
			//==============================================================
			RGB_vector_ptr lut = RGBVector::deepClone(clone);
			RGBVector::changeMaxValue(lut, bitDepth->getLutMaxValue());
			bptr < DGLutFile >
			    dgLutFile(new DGLutFile("debug/3.6_lut_dgcode.xls", Create));
			storeDGLutFile(lut, dgLutFile);
			//==============================================================


			fixReverseByFeedback(clone);
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
			    isAscend(checkResult, startCheckPos,
				     bitDepth->getOutputMaxDigitalCount())) {
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


	    /*
	       �qch�ӬD��delta���
	     */
	    double_vector_ptr LCDCalibrator::selectDelta(double_vector_ptr dxofBase,
							 double_vector_ptr dyofBase, Channel & ch) {
		if (ch == Channel::R) {
		    return dxofBase;
		} else if (ch == Channel::G) {
		    return dyofBase;
		}
		return double_vector_ptr((double_vector *) null);
	    }
	    void LCDCalibrator::fixReverseByFeedback(RGB_vector_ptr dglut) {
		FeedbackFixer fixer(dimFixEnd, dimFixThreshold, fetcher->getAnalyzer(), bitDepth);
		fixer.Listener = this->feedbackListener;
		fixer.fixReverseByFeedback(dglut);

		this->feedbackFixCount = fixer.FeedbackFixCount;
		this->maxMeasureError = fixer.getMaxMeasureError();


		/*bptr < MeasureEstimator >
		   chromaticityEstimator(new MeasureEstimator(dglut,
		   fetcher->getAnalyzer(), bitDepth));
		   chromaticityEstimator->MeasureRdxGdy = false;
		   //�q�ndx dy
		   chromaticityEstimator->measure(0, dimFixEnd);
		   double_vector_ptr dxofBase = chromaticityEstimator->dxofBase;
		   double_vector_ptr dyofBase = chromaticityEstimator->dyofBase;
		   STORE_DOUBLE_VECTOR("o_dxofBase.xls", dxofBase);
		   STORE_DOUBLE_VECTOR("o_dyofBase.xls", dyofBase);


		   int checkEnd = dimFixEnd - 1;
		   const int MaxTestCount = 4;
		   //���XmustZone���ηN�O, �ɩw�X���Ǧa�観 reverse, ����u�n�h�q��reverse���a��Y�i, ���Υ������q
		   int_vector_ptr mustZone =
		   getMustMeasureZoneIndexVector(dxofBase, dyofBase, 1, checkEnd);

		   int_vector_ptr reverseIndexes;

		   while (getReverseIndexVector(dxofBase, 1, checkEnd)->size() != 0
		   || getReverseIndexVector(dyofBase, 1, checkEnd)->size() != 0) {
		   //�ץ��ܨS�����ର��


		   //�s���q���覡, �Ʊ�i�H��֮ɶ�
		   for (int x = 1; x <= 2; x++) {
		   //1 for R, 2 for G
		   Channel ch = Channel::getChannel(x);
		   //�qch�ӨM�w�n�B�zdx or dy
		   double_vector_ptr deltaOfBase = selectDelta(dxofBase, dyofBase, ch);
		   reverseIndexes = getReverseIndexVector(deltaOfBase, 1, checkEnd);
		   double_vector_ptr deltaOfBase0;

		   foreach(int index, *reverseIndexes) {

		   int test = 0;
		   do {
		   //�i�J���h�N��J��defect
		   int y = index;
		   //double delta = (*deltaOfBase)[y];
		   double deltaU1 = (*deltaOfBase)[y + 1];
		   double deltaD1 = (*deltaOfBase)[y - 1];

		   RGB_ptr rgb;
		   double value = -1;
		   if (deltaU1 > deltaD1) {
		   //�Y�W�誺delta����j, �N�����j���վ�Ŷ�, �ҥH���W��
		   rgb = (*dglut)[y];
		   value = rgb->getValue(ch) + 1;
		   } else {
		   //�Ϥ�, �N�O���U��
		   rgb = (*dglut)[y - 1];
		   value = rgb->getValue(ch) - 1;
		   }
		   rgb->setValue(ch, value);


		   if (ch == Channel::R) {
		   STORE_RGBVECTOR("3.4_r_reverse_fix_dgcode.xls", dglut);
		   } else if (ch == Channel::G) {
		   STORE_RGBVECTOR("3.5_g_reverse_fix_dgcode.xls", dglut);
		   }
		   //�վ㧹����u�q�����Q�վ㪺���ϰ�(�]�N�O3��GL)
		   //�Y�Ӱϰ쳣ok, ���U�@�Ӥ���
		   int localStart = y - 1;
		   int localEnd = y + 1;

		   chromaticityEstimator->measure(localStart, localEnd);
		   double_vector_ptr dxofBase0 = chromaticityEstimator->dxofBase;
		   double_vector_ptr dyofBase0 = chromaticityEstimator->dyofBase;
		   deltaOfBase0 = selectDelta(dxofBase0, dyofBase0, ch);

		   test++;
		   if (null != feedbackListener) {
		   int feedbackFixCount = chromaticityEstimator->getMeasureCount();
		   int reverseCount = reverseIndexes->size();
		   feedbackListener->doFeedback(reverseCount, feedbackFixCount);
		   }
		   } while (checkReverse(deltaOfBase0, 1, 2) != -1 && test < MaxTestCount);
		   //�]���q�����G�|�h�Ԥ@��0, �ҥHcheckReverse�q1�}�l���ˬd

		   }    //foreach loop

		   }            //for ch loop
		   //�u���b�q�������ɭԤ~�|�Uconstrained
		   chromaticityEstimator->Constrained = mustZone;
		   chromaticityEstimator->measure(0, dimFixEnd);
		   chromaticityEstimator->Constrained = nil_int_vector_ptr;
		   dxofBase = chromaticityEstimator->dxofBase;
		   dyofBase = chromaticityEstimator->dyofBase;
		   STORE_DOUBLE_VECTOR("dxofBase.xls", dxofBase);
		   STORE_DOUBLE_VECTOR("dyofBase.xls", dyofBase);
		   }            //out while
		   STORE_RGBVECTOR("3.5_reverse_fix_dgcode.xls", dglut);
		   this->feedbackFixCount = chromaticityEstimator->getMeasureCount();
		   this->maxMeasureError = chromaticityEstimator->getMaxMeasureError(); */
	    };


	    //const double LCDCalibrator::ReverseDefine = 0.0001;
	    int LCDCalibrator::checkReverse(double_vector_ptr deltaVector) {
		int size = deltaVector->size();
		for (int x = 1; x < size - 1; x++) {
		    double delta = (*deltaVector)[x];
		    if (delta < dimFixThreshold) {
			return x;
		    }
		}
		return -1;
	    }

	    int_vector_ptr LCDCalibrator::getReverseIndexVector(double_vector_ptr deltaVector,
								int start, int end) {
		int_vector_ptr result(new int_vector());
		int preReverseIndex = -1;
		for (int x = start; x < end; x++) {
		    double delta = (*deltaVector)[x];
		    if (delta < dimFixThreshold
			&& ((preReverseIndex != -1) ? (x - preReverseIndex) >= 3 : true)) {
			preReverseIndex = x;
			result->push_back(x);
		    }
		}

		return result;
	    }

	    int_vector_ptr LCDCalibrator::getMustMeasureZoneIndexVector(double_vector_ptr dxofBase,
									double_vector_ptr dyofBase,
									int start, int end) {
		int_vector_ptr result(new int_vector());
		for (int x = start; x < end; x++) {
		    double dx = (*dxofBase)[x];
		    double dy = (*dyofBase)[x];
		    if (dx < dimFixThreshold || dy < dimFixThreshold) {
			pushBackNumber(result, x - 2);
			pushBackNumber(result, x - 1);
			pushBackNumber(result, x);
			pushBackNumber(result, x + 1);
			pushBackNumber(result, x + 2);
			//x = x + 3;
			/*result->push_back(x - 2);
			   result->push_back(x - 1);
			   result->push_back(x);
			   result->push_back(x + 1);
			   result->push_back(x + 2);
			   x = x + 5; */


		    }
		}

		return result;
	    }

	    void LCDCalibrator::pushBackNumber(int_vector_ptr result, int number) {
		bool findIt = find(result->begin(), result->end(), number) != result->end();
		if (!findIt) {
		    result->push_back(number);
		}
	    };

	    int LCDCalibrator::checkReverse(double_vector_ptr deltaVector, int start, int end) {
		//int size = deltaVector->size();
		for (int x = start; x < end; x++) {
		    double delta = (*deltaVector)[x];
		    if (delta < dimFixThreshold) {
			return x;
		    }
		}
		return -1;
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

	    void LCDCalibrator::smoothComponentVector(Component_vector_ptr componentVector) {
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		MaxMatrixIntensityAnalyzer *manalyzer =
		    dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
		int size = componentVector->size();
		if (null != manalyzer) {
		    bool smoothAtXYZ = false;
		    for (int gl = 1; gl < size - 1; gl++) {
			int x = size - 1 - gl;
			Component_ptr c0 = (*componentVector)[x + 1];
			Component_ptr c1 = (*componentVector)[x];
			Component_ptr c2 = (*componentVector)[x - 1];
			XYZ_ptr XYZ0 = c0->XYZ;
			XYZ_ptr XYZ1 = c1->XYZ;
			XYZ_ptr XYZ2 = c2->XYZ;

			XYZ_ptr XYZ;
			if (smoothAtXYZ) {
			    XYZ1->X = Interpolation::linear(0, 1, XYZ0->X, XYZ2->X, 0.5);
			    XYZ1->Y = Interpolation::linear(0, 1, XYZ0->Y, XYZ2->Y, 0.5);
			    XYZ1->Z = Interpolation::linear(0, 1, XYZ0->Z, XYZ2->Z, 0.5);
			    XYZ = XYZ1;
			} else {
			    xyY_ptr xyY0(new CIExyY(XYZ0));
			    xyY_ptr xyY1(new CIExyY(XYZ1));
			    xyY_ptr xyY2(new CIExyY(XYZ2));
			    xyY1->x = Interpolation::linear(0, 1, xyY0->x, xyY2->x, 0.5);
			    xyY1->y = Interpolation::linear(0, 1, xyY0->y, xyY2->y, 0.5);
			    //xyY1->Y = Interpolation::linear(0, 1, xyY0->Y, xyY2->Y, 0.5);
			    XYZ = xyY1->toXYZ();
			}

			c1->XYZ = XYZ;
			RGB_ptr intensity = manalyzer->getIntensity(c1->XYZ);
			c1->intensity = intensity;
		    }
		}
	    };

	    void LCDCalibrator::smoothComponentVector2(Component_vector_ptr componentVector) {
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		MaxMatrixIntensityAnalyzer *manalyzer =
		    dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
		int size = componentVector->size();
		const int smoothTimes = 3;

		if (null != manalyzer) {

		    double_array outputx(new double[size]);
		    double_array outputy(new double[size]);
		    double_array outputY(new double[size]);
		    double_array outputdx(new double[size]);
		    double_array outputdy(new double[size]);
		    double_array outputdY(new double[size]);

		    outputdx[0] = outputdy[0] = outputdY[0] = 0;
		    xyY_ptr prexyY;
		    for (int gl = 0; gl < size; gl++) {
			Component_ptr c = (*componentVector)[gl];
			XYZ_ptr XYZ = c->XYZ;
			xyY_ptr xyY(new CIExyY(XYZ));

			outputx[gl] = xyY->x;
			outputy[gl] = xyY->y;
			outputY[gl] = xyY->Y;
			if (null != prexyY) {
			    outputdx[gl] = xyY->x - prexyY->x;
			    outputdy[gl] = xyY->y - prexyY->y;
			    outputdY[gl] = xyY->Y - prexyY->Y;
			}

			prexyY = xyY;
		    }

		    smooth(outputdx, size, smoothTimes);
		    smooth(outputdy, size, smoothTimes);
		    smooth(outputdY, size, smoothTimes);
		    outputx = getSmoothCurve(outputx, outputdx, size);
		    outputy = getSmoothCurve(outputy, outputdy, size);
		    outputY = getSmoothCurve(outputY, outputdY, size);

		    for (int gl = 0; gl < size; gl++) {
			Component_ptr c = (*componentVector)[gl];
			double x = outputx[gl];
			double y = outputy[gl];
			double Y = outputY[gl];
			xyY_ptr xyY(new CIExyY(x, y, Y));

			c->XYZ = xyY->toXYZ();
			RGB_ptr intensity = manalyzer->getIntensity(c->XYZ);
			c->intensity = intensity;
		    }


		}
	    };

	    void LCDCalibrator::smooth(double_array curve, int size, int times) {
		//int size = curve.length;
		for (int t = 0; t < times; t++) {
		    for (int x = 1; x < size - 1; x++) {
			curve[x] = (curve[x - 1] + curve[x + 1]) / 2;
		    }
		}
	    };

	    double_array LCDCalibrator::getSmoothCurve(double_array originalCurve,
						       double_array deltaCurve, int size) {
		double delta = originalCurve[size - 1] - originalCurve[0];
		double sumOfDelta = DoubleArray::sum(deltaCurve, size);
		double factor = delta / sumOfDelta;

		double_array smoothCurve(new double[size]);
		smoothCurve[0] = originalCurve[0];
		for (int x = 1; x < size; x++) {
		    smoothCurve[x] = smoothCurve[x - 1] + deltaCurve[x] * factor;
		}

		return smoothCurve;
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

	    void LCDCalibrator::setFeedbackListener(bptr < FeedbackListener > listener) {
		this->feedbackListener = listener;
	    }
	    //==================================================================

	};
    };
};

