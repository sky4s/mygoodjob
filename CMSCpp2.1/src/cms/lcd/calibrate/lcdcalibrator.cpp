#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"
#include <gui/cct/TMainForm.h>
//#include <cms/colorformat/excelfile.h>
//C�t�Τ��
#include    <limits.h>
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
		LCDCalibrator::getGammaCurveVector(double dimGamma,
						   int dimGammaEnd,
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
		    double gamma = Interpolation::linear(dimGammaEnd, effectiven - 1,
							 dimGamma,
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
 
	    void LCDCalibrator::setAbsoluteGamma(bool absoluteGamma, int startGrayLevel,
						 double startGrayLevelAboveGamma) {
		this->absoluteGamma = absoluteGamma;
		this->absoluteGammaStart = startGrayLevel;
		this->absGammaStartGLAboveGamma = startGrayLevelAboveGamma;
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
		if (KeepMaxLuminance::TargetWhite == keepMaxLuminance) {
		    autoIntensity = true;
		}
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
		correct = Correct::None;
		gamma = rgamma = ggamma = bgamma = dimGamma = -1;
		dimGammaEnd = 50;
		this->fetcher = fetcher;
		useNewMethod = false;
		bMax = bMax2 = false;
		rTargetIntensity = -1;
		gTargetIntensity = -1;
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

		colorimetricQuanti = true;
		quantiType = NearOriginal;

		autoIntensity = false;
		smoothIntensity = false;
		smoothIntensityStart = 40;
		smoothIntensityEnd = 60;

		excuteStatus = "N/A";
	    };

	    Component_vector_ptr LCDCalibrator::fetchComponentVector() {
		//�q��start->end�o�쪺coponent/Y
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
		bool nativeTagetWhite = refRGB->isWhite();
		if (!nativeTagetWhite && !mm->FakeMeasure) {
		    //�B�~�q��target white, �Ϫ��C�����@�~��, ���T�O���I���G�ץi�Hí�w!
		    //�Ӥ��|������I���G�ץu��O�]�wtarget white��U���G��
		    fetcher->ExtraMeasureRGB = refRGB;
		}
		Component_vector_ptr componentVector = fetcher->fetchComponent(measureCondition);
		RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();

		if (componentVector == null || rgbMeasureCode->size() != componentVector->size()) {
		    return Component_vector_ptr((Component_vector *)
						null);
		}

		if (nativeTagetWhite) {
		    targetWhiteXYZ = (*componentVector)[0]->XYZ;
		} else {
		    if (!mm->FakeMeasure) {
			targetWhiteXYZ = fetcher->ExtraMeasureXYZ;
		    } else {
			xyY_ptr refColor = analyzer->getReferenceColor();
			XYZ_ptr refColorXYZ = refColor->toXYZ();
			targetWhiteXYZ = refColorXYZ;
		    }
		}

		/*xyY_ptr refColor=analyzer->getReferenceColor();
		   targetWhiteXYZ =
		   nativeTagetWhite ? (*componentVector)[0]->XYZ :
		   (!mm->FakeMeasure ? fetcher->ExtraMeasureXYZ :
		   refColor->toXYZ()); */
		/*RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();

		   if (rgbMeasureCode->size() != componentVector->size()) {
		   return Component_vector_ptr((Component_vector *)
		   null);
		   } else { */
		return componentVector;
		//}
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
		int max = bitDepth->getOutputMaxDigitalCount();
		int blueMax = max;

		if (keepMaxLuminance ==
		    KeepMaxLuminance::NativeWhiteAdvanced && true == skipInverseB) {

		    if (mm->FakeMeasure) {
			this->maxZDGCode = blueMax;
			return;
		    } else {
			//�Y�n���Linverse B, �h�n���q����B�b���̤���
			//�M��]�wb�̤j�u�Ψ�����I
			blueMax = MeasureTool::getMaxZDGCode(mm, bitDepth);
			this->maxZDGCode = blueMax;
		    }
		}

		nativeWhiteAnalyzer =
		    MaxMatrixIntensityAnalyzer::getReadyAnalyzer(mm, max, max, blueMax);
	    };

	    /*
	       CCT + Gamma
	       ����PanelRegulator�n����, ���O�qLCDCalibrator�q�n���n����T, �A�Ǩ�AdvancedDGLutGenerator�h
	       �]���ݭn�N��ص��G��smooth(target�Mnative), �ҥH�����Nremapping��bAdvancedDGLutGenerator��
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr < MeasureCondition > measureCondition) {
		excuteStatus = "CCTDGLut";
		this->measureCondition = measureCondition;
		if (false == originalGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		bool doAccurate = isDoAccurate();
		//�I�sdoAccurate�`�@����B, ���B�O�ΨӲ���panel regulator
		bptr < PanelRegulator > panelRegulator;
		//doAccurate = true;
		if (doAccurate) {
		    //���: �Htarget white��rgb���̤j��, �վ㭱�O�í��s�q��
		    //��}: �Hdirect gamma(gamma test)�������ܥ��X��pattern, �F��ۦP�ĪG

		    bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    RGB_ptr rgb = analyzer->getReferenceRGB();
		    panelRegulator = bptr < PanelRegulator >
			(new GammaTestPanelRegulator(bitDepth, tconctrl, (int) rgb->R, (int) rgb->G,
						     (int) rgb->B, measureCondition));
		    if (false == this->manualAccurateMode) {
			//�Y�O�bdirect gamma�U, setEnable�|�L��, �]��setEnable�O�ܧ�DG LUT
			//���Odirect gamma�L��DG LUT�����e!
			panelRegulator->setEnable(true);
		    }
		    remapped = true;
		}

		this->originalComponentVector = fetchComponentVector();
		if (null == originalComponentVector) {
		    return nil_RGB_vector_ptr;
		}
		STORE_COMPONENT("0.0_o_fetch.xls", originalComponentVector);

		//�յ�smooth componentVector, �o���smooth ��dg lut
		this->componentVector = Util::copy(originalComponentVector);
		if (smoothComponent) {
		    //smoothComponentVector(componentVector);
		    smoothComponentVector2(componentVector);
		    STORE_COMPONENT("o_fetch_smooth.xls", componentVector);
		}
		//this->componentVector = this->originalComponentVector;
		if (doAccurate) {
		    panelRegulator->setEnable(false);
		}
		if (componentVector == null) {
		    //null�N��q���Q���_
		    return RGB_vector_ptr((RGB_vector *) null);
		}
		//=============================================================
		// gamma curve setting zone
		//=============================================================
		if (true == originalGamma) {
		    //�Y�n�ĥ�original gamma, �q�q�����G�ԥXgamma, ��@�ؼ�gamma curve
		    double_vector_ptr gammaCurve = getOriginalGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}

		STORE_DOUBLE_VECTOR("0.1_gammacurve.xls", gammaCurve);
		//=============================================================


		const MaxValue & quantizationBit = bitDepth->getLutMaxValue();

		if (true == useNewMethod) {
		    //�s��k��������פW���B�z
		    dglut = newMethod(panelRegulator);
		} else {
		    //�¤�k�ĦX��ץH��DG Code���B�z
		    DGLutGenerator generator(componentVector, keepMaxLuminance);
		    dglut = oldMethod(generator, panelRegulator, quantizationBit);
		}

		if (nil_RGB_vector_ptr == dglut) {
		    return nil_RGB_vector_ptr;
		}
		//==============================================================
		// DG Code Op block
		//==============================================================
		//�q��
		RGB_vector_ptr result = getDGLutOpResult(dglut);
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
	    bool LCDCalibrator::isDoAccurate() {
		return (true == accurateMode) && (null != tconctrl);
	    };


	    /*
	       generator�b�����ηN�u�O���Ӳ���gamma curve
	     */
	    RGB_vector_ptr LCDCalibrator::newMethod(bptr < PanelRegulator > panelRegulator) {
		double brightgammaParameter = 1;
		//==========================================================
		// �s��k
		//==========================================================
		bptr < AdvancedDGLutGenerator > advgenerator;
		double_vector_ptr luminanceGammaCurve;
		double minLuminance = (*componentVector)[componentVector->size() - 1]->XYZ->Y;

		//=============================================================
		// ���� luminance gamma curve
		//=============================================================
		if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		    //NativeWhiteAdvanced�O���F���UHook�M�̤j�G�ת���J����
		    bptr < PanelRegulator > panelRegulator2;
		    Component_vector_ptr componentVector2;
		    bool doAccurate = (true == skipInverseB) && isDoAccurate();
		    if (null == nativeWhiteAnalyzer) {
			initNativeWhiteAnalyzer();

			if (doAccurate) {
			    //�Y�nskipInverseB, �N���ӽվ㭱�O�S�ʭ��s�q��
			    int max = bitDepth->getInputMaxDigitalCount();
			    panelRegulator2 = bptr < PanelRegulator >
				(new
				 GammaTestPanelRegulator(bitDepth,
							 tconctrl, max,
							 max, maxZDGCode, measureCondition));
			    panelRegulator2->setEnable(true);
			    componentVector2 = fetchComponentVector();
			    STORE_COMPONENT("o_fetch2.xls", componentVector2);
			    panelRegulator2->setEnable(false);
			}
		    }

		    brightgammaParameter = keepMaxLumiGamma;
		    advgenerator = bptr < AdvancedDGLutGenerator >
			(new
			 AdvancedDGLutGenerator(componentVector, fetcher,
						fetcher->getAnalyzer(),
						nativeWhiteAnalyzer, bitDepth, *this));
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
		    //�ǥѶǲ�generator����luminance gamma curve
		    luminanceGammaCurve =
			getLuminanceGammaCurve(gammaCurve, maxLuminance, minLuminance);
		    //==============================================================================
		    //end of native white
		} else {
		    //�@�몺case, ���έ��UHook�M�̤j�G��
		    //componentVector�O�ƥ��q�n��(�I�s��function���e)

		    advgenerator =
			bptr < AdvancedDGLutGenerator >
			(new AdvancedDGLutGenerator(componentVector, fetcher, bitDepth, *this));

		    //==========================================================
		    // ����gamma curve��
		    //==========================================================
		    //max luminance
		    //bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		    //double maxLuminance = isDoAccurate()? targetWhiteXYZ->Y : targetWhiteXYZ->Y;
		    bool doAccurate = isDoAccurate();
		    if (doAccurate && null == nativeWhiteAnalyzer) {
			initNativeWhiteAnalyzer();
		    }
		    double maxLuminance =
			doAccurate ? nativeWhiteAnalyzer->getReferenceColor()->Y :
			targetWhiteXYZ->Y;
		    //�ǥѶǲ�generator����luminance gamma curve
		    if (true == absoluteGamma) {
			int effectiven = bitDepth->getEffectiveInputLevel();
			luminanceGammaCurve =
			    getLuminanceGammaCurve(gammaCurve, maxLuminance, minLuminance,
						   absoluteGamma, absoluteGammaStart,
						   absGammaStartGLAboveGamma, effectiven);
			if (nil_double_vector_ptr == luminanceGammaCurve) {
			    return nil_RGB_vector_ptr;
			}
		    } else {
			luminanceGammaCurve =
			    getLuminanceGammaCurve(gammaCurve, maxLuminance, minLuminance);
		    }
		    //==========================================================

		    keepMaxLumiOver = bitDepth->getEffectiveInputLevel();

		}		// end of gamma curve
		//=============================================================
		STORE_DOUBLE_VECTOR("1.0_lumigammacurve.xls", luminanceGammaCurve);


		double dimStrengthParameter = 1;
		int underParameter = 50;

		if (correct == Correct::DefinedDim) {
		    dimStrengthParameter = dimStrength;
		    underParameter = under;
		} else if (correct == Correct::None) {
		    underParameter = 0;

		}

		int startCheckPos = 50;
		int minOverParameter = (useNewMethod
					&& autoKeepMaxLumiParameter) ?
		    startCheckPos : keepMaxLumiOver;
		advgenerator->setPanelRegulator(panelRegulator);


		bptr < IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		//analyzer�Y�S���]�w�Ltarget color, �|�Ϧ��B�J����
		//�]��analyzer->getReferenceColor()�|�Onull
		XYZ_ptr targetWhite = analyzer->getReferenceColor()->toXYZ();
		XYZ_ptr nativeWhite = (*componentVector)[0]->XYZ;
		if (null != nativeWhiteAnalyzer) {
		    //nativeWhite = nativeWhiteAnalyzer->getReferenceColor()->toXYZ();
		}
		if (KeepMaxLuminance::TargetLuminance == keepMaxLuminance) {
		    //�Q��luminanceGammaCurve, ��native���G�׳]�w��luminanceGammaCurve���̤j�G��
		    nativeWhite = targetWhite->clone();
		    nativeWhite->normalizeY();
		    double maxLuminance = (*luminanceGammaCurve)[luminanceGammaCurve->size() - 1];
		    nativeWhite->times(maxLuminance);
		}
		//�~���j��w��O�_�|���ӨM�w�_�l��m
		//�o�䪺����O: �p�G����I�]�w����(�Ӥp�ӱ���0), �N�i��y���|��
		//�ҥH�v���վ�����I�����|������
		int overParameter = keepMaxLumiOver;
		const int step = 4;

		//�}��native white smooth(advanced)��, �|�̷ӵ��G�۰ʽվ�smooth�϶����Ѽ�
		for (; overParameter >= minOverParameter; overParameter -= step) {
		    int width = bitDepth->getEffectiveInputLevel() - overParameter;
		    //int width = bitDepth->getLevel() - overParameter;
		    //�p��o��ؼЭ�
		    targetXYZVector =
			advgenerator->getTargetXYZVector(targetWhite,
							 nativeWhite,
							 luminanceGammaCurve,
							 underParameter,
							 overParameter,
							 dimStrengthParameter,
							 brightgammaParameter, width);


		    //�q�ؼЭȺ�XDGLut
		    dglut = advgenerator->produce(targetXYZVector);
		    STORE_RGBVECTOR("3.1_org_dgcode.xls", dglut);
		    initialRGBGamma = advgenerator->RGBGenerateResult;
		    idealIntensity = advgenerator->IdealIntensity;



		    //=========================================================
		    // feedback
		    //=========================================================
		    if (true == feedbackFix
			&& (true == MainForm->debugMode || MainForm->isTCONInput()
			    || MainForm->isPCwithTCONInput())) {
			//���qDGLut��X�Ƕ���dx dy
			//�A�q�o�˪����G�L�եؼЭ�
			const MaxValue & lutMaxValue = bitDepth->getLutMaxValue();
			RGB_vector_ptr clone = RGBVector::deepClone(dglut);

			//colorimetricQuanti = true;
			int frcBit = bitDepth->getFRCAbilityBit().bit;

			if (true == colorimetricQuanti && 11 == frcBit) {
			    //11bit�U�~�i�H�ϥ�colorimetricQuanti, 10bit�U�ϥΨSԣ�ĪG
			    int domainBit = frcBit + 2;
			    const MaxValue & domainMaxValue = MaxValue::getByIntegerBit(domainBit);
			    //������domain bit, ��FRC bit+2 bit
			    RGBVector::changeMaxValue(clone, domainMaxValue);
			    STORE_RGBVECTOR("3.2_domain_dgcode.xls", clone);

			    //�i��smart quanti
			    clone = colorimetricQuantization(clone, 0);	//11bit
			    //��frc bit(11bit)�h�] feedback�~�O�諸
			    STORE_RGBVECTOR("3.3_smart0_dgcode.xls", clone);

			    RGB_vector_ptr lut = RGBVector::deepClone(clone);
			    RGBVector::changeMaxValue(lut, lutMaxValue);	//12bit
			    STORE_RGBVECTOR("3.4_lut_dgcode(afterQuanti).xls", lut);
			} else {
			    //==============================================================

			    RGBVector::changeMaxValue(clone, bitDepth->getLutMaxValue());
			    STORE_RGBVECTOR("3.2_lut_dgcode(beforeQuanti).xls", clone);
			    RGBVector::storeToText("3.2_lut_dgcode(beforeFeedback).txt", clone);

			    RGBVector::changeMaxValue(clone, bitDepth->getFRCAbilityBit());
			    STORE_RGBVECTOR("3.3_frc_dgcode.xls", clone);

			    RGB_vector_ptr lut = RGBVector::deepClone(clone);
			    RGBVector::changeMaxValue(lut, bitDepth->getLutMaxValue());
			    STORE_RGBVECTOR("3.4_lut_dgcode(afterQuanti).xls", lut);

			    //==============================================================
			}
			//==============================================================

			fixChromaticityReverseByFeedback(clone);
			dglut = clone;
		    }		//end of feedbackFix
		    //=========================================================

		    if (autoKeepMaxLumiParameter) {
			//�ˬd���ɭ�, �٬O�ݭn�N��Ӭy�{�]���~���ˬd.
			//�ҥH�~�ݭn�I�sgetDGLutOpResult��changeMaxValue
			//���O�^�Ǫ��ɭԭn�^�ǩ|���B�̪����G, ���ӧ��ˬd�Ϊ��^��
			RGB_vector_ptr checkResult = RGBVector::deepClone(dglut);
			checkResult = getDGLutOpResult(checkResult);
			//�n����FRC��bit�U�ˬd�~�O���T��, �ӫDLUT��bit
			RGBVector::changeMaxValue(checkResult, bitDepth->getFRCAbilityBit());
			//�ˬd
			if (RGBVector::
			    isAscend(checkResult, startCheckPos,
				     bitDepth->getOutputMaxDigitalCount())) {
			    //STORE_RGBVECTOR("checkResult.xls", checkResult);
			    break;
			}
		    }		// end of autoKeepMaxLumiParameter
		}		//end of overParameter loop

		keepMaxLumiOver = autoKeepMaxLumiParameter ? overParameter + step : keepMaxLumiOver;
		RGBVector::changeMaxValue(dglut, MaxValue::Double255);
		STORE_RGBVECTOR("3.9_dgcode.xls", dglut);
		return dglut;
		//==========================================================
	    };			// end of newMethod

	    //=================================================================
	    // colorimetric quantization
	    //=================================================================
	    RGB_vector_ptr LCDCalibrator::
		colorimetricQuantization(RGB_vector_ptr dglut, int quadrant) {
		return ColorimetricQuantizer::colorimetricQuantization(dglut, quadrant);
	    };

	    //=================================================================

	    /*
	       �qch�ӬD��delta���
	     */
	    double_vector_ptr LCDCalibrator::
		selectDelta(double_vector_ptr dxofBase, double_vector_ptr dyofBase, Channel & ch) {
		if (ch == Channel::R) {
		    return dxofBase;
		} else if (ch == Channel::G) {
		    return dyofBase;
		}
		return double_vector_ptr((double_vector *) null);
	    }
	    void LCDCalibrator::fixChromaticityReverseByFeedback(RGB_vector_ptr dglut) {
		feedbackFixer =
		    bptr < FeedbackFixer > (new
					    FeedbackFixer(dimFixEnd,
							  dimFixThreshold,
							  fetcher->getAnalyzer(), bitDepth));
		feedbackFixer->Listener = this->feedbackListener;
		feedbackFixer->fixReverseByFeedback(dglut);
		this->feedbackFixCount = feedbackFixer->FeedbackFixCount;
		this->maxMeasureError = feedbackFixer->getMaxMeasureError();
		this->initDefectCount = feedbackFixer->InitDefectCount;
	    };
	    //const double LCDCalibrator::ReverseDefine = 0.0001;
	    /*int LCDCalibrator::checkReverse(double_vector_ptr deltaVector) {
	       int size = deltaVector->size();
	       for (int x = 1; x < size - 1; x++) {
	       double delta = (*deltaVector)[x];
	       if (delta < dimFixThreshold) {
	       return x;
	       }
	       }
	       return -1;
	       } */

	    int_vector_ptr LCDCalibrator::
		getReverseIndexVector(double_vector_ptr deltaVector, int start, int end) {
		int_vector_ptr result(new int_vector());
		int preReverseIndex = -1;
		for (int x = start; x < end; x++) {
		    double delta = (*deltaVector)[x];
		    if (delta < dimFixThreshold && ((preReverseIndex != -1) ? (x - preReverseIndex)
						    >= 3 : true)) {
			preReverseIndex = x;
			result->push_back(x);
		    }
		}

		return result;
	    }

	    int_vector_ptr LCDCalibrator::
		getMustMeasureZoneIndexVector(double_vector_ptr dxofBase,
					      double_vector_ptr dyofBase, int start, int end) {
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
		bool findIt = find(result->begin(), result->end(),
				   number) != result->end();
		if (!findIt) {
		    result->push_back(number);
		}
	    };

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
		    if (null == rgbgamma) {
			return nil_RGB_vector_ptr;
		    }
		    STORE_RGBGAMMA("5.0_rgbgamma_p1p2.xls", rgbgamma);
		    //�q�ؼ�gamma curve����dg code, ���B�O�ǤJnormal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    //�q��
		    STORE_RGBVECTOR("5.1_dgcode_p1p2g.xls", dglut);
		    RGBVector::quantization(dglut, quantizationBit);
		    STORE_RGBVECTOR("5.2_dgcode_p1p2g.xls", dglut);
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
		    STORE_RGBVECTOR("5.3_dgcode_p1p2dg.xls", dglut);
		    //==========================================================
		}
		finalRGBGamma = rgbgamma;
		return dglut;
		//==========================================================
	    };
	    RGB_vector_ptr LCDCalibrator::getGammaDGLut(bptr < MeasureCondition > measureCondition) {
		excuteStatus = "GammaDGLut";
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
		    dglutFile->setTargetXYZVector(targetXYZVector, dglut, bitDepth);
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
		    DGLutFile dglut("6.0_dimComponent.xls", ReadOnly);
		    componentVector = dglut.getComponentVector();
		}
		STORE_COMPONENT("6.0_dimComponent.xls", componentVector);
		return componentVector;
	    };

	    /*
	       �����N�ȧ@�����F��smooth
	     */
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

	    /*
	       �Q�ήt��dx dy dY�Ӱ�smooth, �|�󬰥����۵M
	     */
	    void LCDCalibrator::smoothComponentVector2(Component_vector_ptr componentVector) {
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		MaxMatrixIntensityAnalyzer *manalyzer =
		    dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
		int size = componentVector->size();
		//smooth�T��
		const int smoothTimes = 3;
		//manalyzer�Ψӧ�smooth����XYZ, ���s�p��intensity
		if (null != manalyzer) {

		    double_array outputx(new double[size]);
		    double_array outputy(new double[size]);
		    double_array outputY(new double[size]);
		    double_array outputdx(new double[size]);
		    double_array outputdy(new double[size]);
		    double_array outputdY(new double[size]);
		    outputdx[0] = outputdy[0] = outputdY[0] = 0;
		    xyY_ptr prexyY;
		    //�˦�dx dy dY curve, �Asmooth
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
		    //�Q�έ쥻��outputx�Msmooth����outputdx, �٭�^�s���g�Lsmooth��outputx curve
		    outputx = getSmoothCurve(outputx, outputdx, size);
		    outputy = getSmoothCurve(outputy, outputdy, size);
		    outputY = getSmoothCurve(outputY, outputdY, size);
		    for (int gl = 0; gl < size; gl++) {
			Component_ptr c = (*componentVector)[gl];
			double x = outputx[gl];
			double y = outputy[gl];
			double Y = outputY[gl];
			xyY_ptr xyY(new CIExyY(x, y, Y));
			//��xyY���XYZ
			c->XYZ = xyY->toXYZ();
			//���s��Xintensity
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
	    double_array LCDCalibrator::
		getSmoothCurve(double_array originalCurve, double_array deltaCurve, int size) {
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
	    RGB_vector_ptr LCDCalibrator::getDGLutOpResult(RGB_vector_ptr dglut) {
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
					   KeepNativeWhiteAdvancedOp
					   (bitDepth, keepMaxLumiOver, false));
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
					      MeasureEstimator
					      (componentVector, fetcher->getAnalyzer(), bitDepth));
		    bptr < DGLutOp >
			dimfix(new
			       DimDGLutFixOp(bitDepth, dimFixThreshold,
					     componentVector, chromaticityEstimator));
		    dgop.addOp(dimfix);
		}
		//==============================================================

		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };

	    void LCDCalibrator::setMultiGen(bool enable, int times) {
		this->multiGen = enable;
		this->multiGenTimes = times;
	    };
	    void LCDCalibrator::setSmoothIntensity(int start, int end) {
		this->smoothIntensity = true;
		smoothIntensityStart = start;
		smoothIntensityEnd = end;
	    };
	    void LCDCalibrator::setFeedbackListener(FeedbackListener * listener) {
		this->feedbackListener = listener;
	    }


	    double_vector_ptr LCDCalibrator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve,
				       double maxLuminance, double minLuminance) {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    double v = differ * (*normalGammaCurve)[x] + minLuminance;
		    (*luminanceGammaCurve)[x] = v;
		};
		return luminanceGammaCurve;
	    };

	    /*
	       gamma curve�S������M�۹諸
	       �۹諸��²��, ���諸�|�J��L�k����u��meet�����D
	       samsung�O�W�w8�Ƕ���gamma�n�F��2.1�H�W; ���D�O�I, ������Ƕ�8�]�bgamma 2.2,
	       �M����⵴��gamma 2.2���۹�gamma�O�h��, �H��gamma ���^���I(�Ƕ�0)
	     */
	    double_vector_ptr
		LCDCalibrator::getLuminanceGammaCurve(double_vector_ptr normalGammaCurve,
						      double maxLuminance, double minLuminance,
						      bool absGamma, int absGammaStartGL,
						      double startGLAboveGamma, int effectiven) {
		if (true == absGamma) {
		    int size = normalGammaCurve->size();
		    //=========================================================
		    // 1
		    //=========================================================

		    double startNormalInput = ((double) absGammaStartGL) / effectiven;
		    double startAbsoluteNormalOutput =
			GammaFinder::gamma(startNormalInput, startGLAboveGamma);
		    double startAbsoluteLuminance = maxLuminance * startAbsoluteNormalOutput;
		    //=========================================================
		    // 2
		    //=========================================================
		    if (startAbsoluteLuminance < minLuminance) {
			//�Y�Ƕ��]�w�ӧC�N�|���즹case
			return nil_double_vector_ptr;
		    }
		    double relativeNormalOutput =
			(startAbsoluteLuminance - minLuminance) / (maxLuminance - minLuminance);
		    double relativeGamma =
			GammaFinder::getGamma(startNormalInput, relativeNormalOutput);
		    int turnGrayLevel = -1;


		    //=========================================================
		    // 4
		    //=========================================================
		    for (int x = absGammaStartGL; x < 255; x++) {
			double normalInput = ((double) x) / effectiven;

			double absoluteNormalOutput = (*normalGammaCurve)[x];

			/*double absoluteNormalOutput =
			   GammaFinder::gamma(normalInput, startGLAboveGamma); */
			double absoluteGammaLuminance = maxLuminance * absoluteNormalOutput;

			double relativeNormalOutput =
			    GammaFinder::gamma(normalInput, relativeGamma);
			double relativeGammaLuminance =
			    (maxLuminance - minLuminance) * relativeNormalOutput + minLuminance;
			if (absoluteGammaLuminance > relativeGammaLuminance) {
			    turnGrayLevel = x;
			    break;
			}
		    }
		    if (-1 == turnGrayLevel) {
			return nil_double_vector_ptr;
		    }
		    //=========================================================
		    double_vector_ptr newNormalGammaCurve(new double_vector());

		    for (int x = 0; x <= turnGrayLevel; x++) {
			//���Ϭq�]�w���խץ���abs gamma
			double normalInput = ((double) x) / effectiven;
			double relativeNomralOutput =
			    GammaFinder::gamma(normalInput, relativeGamma);
			newNormalGammaCurve->push_back(relativeNomralOutput);
		    }
		    for (int x = turnGrayLevel + 1; x < effectiven; x++) {
			//���Ϭq�ŦXabs gamma
			double normalInput = ((double) x) / effectiven;
			double absoluteNormalOutput = (*normalGammaCurve)[x];
			double relativeNomralOutput =
			    (absoluteNormalOutput * maxLuminance - minLuminance) / (maxLuminance -
										    minLuminance);
			if (relativeNomralOutput < 0) {
			    return nil_double_vector_ptr;
			}
			newNormalGammaCurve->push_back(relativeNomralOutput);
		    }
		    for (int x = effectiven; x < size; x++) {
			double absoluteNormalOutput = (*normalGammaCurve)[x];
			newNormalGammaCurve->push_back(absoluteNormalOutput);
		    }
		    return getLuminanceGammaCurve(newNormalGammaCurve, maxLuminance, minLuminance);
		}

		/*if (true == absGamma) {
		   double normalInput = ((double) absGammaStartGL) / normalGammaCurve->size();
		   double absoluteNormalOutput =
		   GammaFinder::gamma(normalInput, startGLAboveGamma);
		   double relativeNomralOutput =
		   (absoluteNormalOutput * maxLuminance - minLuminance) / (maxLuminance -
		   minLuminance);
		   if (relativeNomralOutput < 0) {
		   return nil_double_vector_ptr;
		   }
		   double relativeGamma = GammaFinder::getGamma(normalInput, relativeNomralOutput);



		   //�Y�ĥ�abs gamma, gamma�N������q
		   //abs gamma start���e, �O rel gamma���Ŷ�, ����h�Oabs gamma���Ŷ�
		   //�ҥH���B�ݭn�N�쥻��normalGammaCurve���q

		   int size = normalGammaCurve->size();
		   double_vector_ptr newNormalGammaCurve(new double_vector());

		   for (int x = 0; x < absGammaStartGL; x++) {
		   //���Ϭq�]�w���խץ���abs gamma
		   double normalInput = ((double) x) / size;
		   double relativeNomralOutput =
		   GammaFinder::gamma(normalInput, relativeGamma);
		   newNormalGammaCurve->push_back(relativeNomralOutput);
		   }

		   for (int x = absGammaStartGL; x < size; x++) {
		   //���Ϭq�ŦXabs gamma
		   double normalInput = ((double) x) / size;
		   double absoluteNormalOutput = (*normalGammaCurve)[x];
		   double relativeNomralOutput =
		   (absoluteNormalOutput * maxLuminance - minLuminance) / (maxLuminance -
		   minLuminance);
		   if (relativeNomralOutput < 0) {
		   return nil_double_vector_ptr;
		   }
		   newNormalGammaCurve->push_back(relativeNomralOutput);
		   }
		   //newNormalGammaCurve�˸��F�������abs gamma��rel gamma
		   return getLuminanceGammaCurve(newNormalGammaCurve, maxLuminance, minLuminance);
		   } */
		else {
		    return getLuminanceGammaCurve(normalGammaCurve, maxLuminance, minLuminance);
		}
		//==================================================================
	    };

	    /*
	       gamma curve�S������M�۹諸
	       �۹諸��²��, ���諸�|�J��L�k����u��meet�����D
	       samsung�O�W�w8�Ƕ���gamma�n�F��2.1�H�W; ���D�O�I, ������Ƕ�8�]�bgamma 2.2,
	       �M����⵴��gamma 2.2���۹�gamma�O�h��, �H��gamma ���^���I(�Ƕ�0)
	     */
	    /*double_vector_ptr LCDCalibrator::
	       getLuminanceGammaCurve(double_vector_ptr normalGammaCurve,
	       double maxLuminance, double minLuminance,
	       bool absoluteGamma, int absoluteGammaStart) {
	       if (true == absoluteGamma) {
	       double normalInput = ((double) absoluteGammaStart) / normalGammaCurve->size();
	       double absoluteNormalOutput = (*normalGammaCurve)[absoluteGammaStart];
	       double absoluteGamma = GammaFinder::getGamma(normalInput, absoluteNormalOutput);
	       return getLuminanceGammaCurve(normalGammaCurve, maxLuminance, minLuminance,
	       absoluteGamma, absoluteGammaStart, absoluteGamma);
	       } else {
	       return getLuminanceGammaCurve(normalGammaCurve, maxLuminance, minLuminance);
	       }

	       //==================================================================
	       }; */
	};
    };
};

