#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"
//#include <gui/cct/TMainForm.h>
//C系統文件
#include   <limits.h>
//C++系統文件
#include <algorithm>

//其他庫頭文件

//本項目內頭文件
//#include "rgbvectorop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    bool debugMode = false;
	    bool linkCA210 = false;
	    bool pcWithTCONInput = false;

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

	     LCDCalibrator::LCDCalibrator(bptr < ComponentFetcher >
					  fetcher,
					  bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth) {
		rgbIndepGamma = false;
		useGammaCurve = false;
		bIntensityGain = 1;
		under = 50;
		p1 = p2 = 0;
		correct = DimCorrect::None;
		gamma = rgamma = ggamma = bgamma = dimGamma = -1;
		dimGammaEnd = 50;
		this->fetcher = fetcher;
		useNewMethod = false;
		bMax = bMax2 = false;
		rTargetIntensity = -1;
		gTargetIntensity = -1;
		bTargetIntensity = -1;
		originalGamma = false;
		maxBRawGrayLevel = -1;
		maxBDGGrayLevel = -1;
		gByPass = false;
		avoidFRCNoise = false;
		autoKeepMaxLumiParameter = false;
		multiGen = false;
		remapped = false;
		dimFixEnd = 50;
		dimFix = false;
		dimFixThreshold = 0.0000;
		keepDarkLevel = true;
		feedbackFix = false;

		colorimetricQuanti = true;
		quantiType = NearOriginal;

		autoIntensity = false;
		smoothIntensity = false;
		smoothIntensityStart = 40;
		smoothIntensityEnd = 60;

		excuteStatus = "N/A";
		debugMode = false;

		dehook = None;
		gammaDWLimit = 1.5;
		gammaUPLimit = 3.0;
		bGap1stGammaBoundGrayLevel = 250;
		bestGammaAtGammaBoundGrayLevel = -1;
		reasonableDeltaChromaticity = 0.003;
		AlterGammaCurveAtDeHook2 = false;
	    };

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

		    double gamma = Interpolation::linear(0, dimGammaEnd, dimGamma,
							 brightGamma, x);
		    double v = Math::pow(normal, gamma);
		    (*result)[x] = v;
		}
		int brightGammaStart = dimGammaEnd + 1;
		for (int x = brightGammaStart; x < effectiven; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double v = Math::pow(normal, brightGamma);
		    (*result)[x] = v;
		}
		for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
		} return result;
	    };

	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double dimGamma,
						   int dimGammaEnd,
						   int middleGammaEnd,
						   double brightGamma, int n, int effectiven) {
		double_vector_ptr result(new double_vector(n));

		for (int x = 0; x <= dimGammaEnd; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double v = Math::pow(normal, dimGamma);
		    (*result)[x] = v;
		}
		int middleGammaStart = dimGammaEnd + 1;
		for (int x = middleGammaStart; x <= middleGammaEnd; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double gamma = Interpolation::linear(middleGammaStart,
							 middleGammaEnd,
							 dimGamma,
							 brightGamma, x);
		    double v = Math::pow(normal, gamma);
		    (*result)[x] = v;
		}
		int brightGammaStart = middleGammaEnd + 1;
		for (int x = brightGammaStart; x < effectiven; x++) {
		    double normal = static_cast < double >(x) / (effectiven - 1);
		    double v = Math::pow(normal, brightGamma);
		    (*result)[x] = v;
		}
		for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
		} return result;
	    };

	    void LCDCalibrator::setP1P2(int p1, int p2) {
		this->p1 = p1;
		this->p2 = p2;
		this->correct = DimCorrect::P1P2;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		this->correct = DimCorrect::RBInterpolation;
		this->under = under;
	    };
	    void LCDCalibrator::setNonDimCorrect() {
		this->correct = DimCorrect::None;
	    };

	    void LCDCalibrator::setDefinedDim(int under, double strength) {
		this->correct = DimCorrect::DefinedDim;
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
	    /*
	       2-Gamma
	     */
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
	    /*
	       3-Gamma
	     */
	    void LCDCalibrator::setGamma(double dimGamma, int dimGammaEnd,
					 int middleGammaEnd, double brightGamma) {
		this->gamma = brightGamma;
		this->dimGamma = dimGamma;
		this->dimGammaEnd = dimGammaEnd;

		int n = bitDepth->getLevel();
		int effectiven = bitDepth->getEffectiveInputLevel();
		setGammaCurve0(getGammaCurveVector
			       (dimGamma, dimGammaEnd, middleGammaEnd, gamma, n, effectiven));
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

	    void LCDCalibrator::setAbsoluteGamma(bool absoluteGamma, int startGrayLevel, double
						 startGrayLevelAboveGamma) {
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
		if (keepMaxLuminance == KeepMaxLuminance::Smooth2NativeWhite) {
		    throw
			UnsupportedOperationException
			("Please call setKeepMaxLuminanceSmooth2NativeWhite().");
		}
		this->keepMaxLuminance = keepMaxLuminance;
		if (KeepMaxLuminance::TargetWhite == keepMaxLuminance) {
		    this->autoIntensity = true;
		}
	    };

	    /*
	       over: 哪一個灰階之後開始smooth
	       gamma: smooth線段的gamma指數
	       autoParameter: 是否自動找尋適當的over參數, 使DG不會有疊階的情形
	     */
	    void LCDCalibrator::setKeepMaxLuminanceSmooth2NativeWhite(int over, bool autoParameter) {
		this->keepMaxLuminance = KeepMaxLuminance::Smooth2NativeWhite;
		this->keepMaxLumiOver = over;
		this->autoKeepMaxLumiParameter = autoParameter;
		this->autoIntensity = true;
	    };


	    Component_vector_ptr LCDCalibrator::fetchComponentVector() {
		//量測start->end得到的coponent/Y
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->FirstAnalyzer;
		RGB_ptr refRGB = analyzer->getReferenceRGB();
		bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
		bool nativeTagetWhite = refRGB->isWhite();
		if (!nativeTagetWhite && !mm->FakeMeasure) {
		    //額外量測target white, 使的每次的作業中, 都確保白點的亮度可以穩定!
		    //而不會限制白點的亮度只能是設定target white當下的亮度
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

		return componentVector;
	    };

	    double_vector_ptr LCDCalibrator::fetchLuminanceVector() {
		//量測start->end得到的coponent/Y
		luminanceVector = fetcher->fetchLuminance(measureCondition);

		if (luminanceVector == null) {
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
		double_vector_ptr result(new double_vector());

		for (int x = 0; x != effectiven; x++) {
		    double normal = ((double) x) / (effectiven - 1);
		    double value = lut.getValue(normal);
		    result->push_back(value);
		}
		for (int x = effectiven; x != n; x++) {
		    result->push_back(1);
		}

		return result;
	    };
            bptr < cms::measure::IntensityAnalyzerIF > LCDCalibrator::getFirstAnalzyer(){
            bptr < IntensityAnalyzerIF > firstAnalyzer = fetcher->FirstAnalyzer;
            return firstAnalyzer;
            };
	    /*
	       當有smooth CCT到native white需求時，就需要native white analyzer
	       ，求得更準確的DG Lut
	     */
	    void LCDCalibrator::
		init2ndWhiteAnalyzer(KeepMaxLuminance keepMaxLuminance, DeHook deHook) {
		SecondWhite secondWhite = DeHookProcessor::getSecondWhite(keepMaxLuminance,
									  deHook);
		//=====================================================
		// 生出一組新的analyzer, 給smooth target的時候用
		// 有這組analyzer, 在smooth到native white的時候可以得到更準確的結果.
		//=====================================================
		//產生max matrix
		bptr < MeterMeasurement > mm = getMeterMeasurement();	//analyzer->getMeterMeasurement();
		int max = bitDepth->getOutputMaxDigitalCount();
		double bluemax = max;
		double redmax = max;
		double greenmax = max;
		DeHookProcessor processor(*this);

		switch (secondWhite) {
		case SecondWhite::MaxRGB:
		    break;
		case SecondWhite::DeHook:
		    if (mm->FakeMeasure) {
			//如果是FakeMeasure, secondWhiteAnalyzer應該是從excel讀出來,
			//所以不用(也不能,因為mm是fake不能量東西)重新產生secondWhiteAnalyzer
			//而且應該也不會進到這邊
			throw new IllegalStateException();
		    } else {
			bluemax = processor.getMaxBIntensityRawGrayLevel();
			this->maxBRawGrayLevel = bluemax;
		    }
		    break;
		case SecondWhite::DeHook2:
		    /*
		       dehook2, 要找的2nd white也會跟過去不同
		     */
		    //*must measure
		    this->maxBRawGrayLevel = processor.getMaxBIntensityRawGrayLevel();
		    if (-1 == maxBRawGrayLevel) {
			ShowMessage("-1 == maxBRawGrayLevel");
		    }
		    lcdmodel4DeHook = processor.getLCDModelForDeHook(this->maxBRawGrayLevel);

		    /*
		       DeHook2+Gamma1st/BGap1st:會影響到搭配的R/G
		       湊出所有R/G組合
		       過濾出dxdy reasonableDeltaChromaticity(0.003)內
		     */
		    Patch_vector_ptr patchVector = processor.
			getReasonableChromaticityPatchVector
			(lcdmodel4DeHook, this->maxBRawGrayLevel, reasonableDeltaChromaticity);
                    if( 0 == patchVector->size()) {
                      throw new IllegalStateException("");
                    }

		    if (SecondWithBGap1st == deHook) {
			//會盡量找到最低的gray level
			this->maxBDGGrayLevel =
			    processor.
			    getReasonableGammaGrayLevel(patchVector, gammaDWLimit, gammaUPLimit);
			if (-1 == this->maxBDGGrayLevel) {
			    this->maxBDGGrayLevel = max - 1;
			}
			if (this->maxBDGGrayLevel <= bGap1stGammaBoundGrayLevel) {
			    this->maxBDGGrayLevel = bGap1stGammaBoundGrayLevel + 1;
			}

			double normalOutput = (*gammaCurve)[this->maxBDGGrayLevel];
			int maxcount = bitDepth->getInputMaxDigitalCount();
			double normalInput = ((double) this->maxBDGGrayLevel) / maxcount;
			double gamma = GammaFinder::getGammaExponential(normalInput,
									normalOutput);
			//再從這裡面撈出最接近target gamma的
			bestGammaPatch1 = processor.getBestGammaPatch(patchVector, gamma,
								      this->maxBDGGrayLevel);
			if (nil_Patch_ptr == bestGammaPatch1) {
			    throw new IllegalStateException("");
			}
			bestGammaPatch2 =
			    processor.getBestGammaPatchByMeasure(bestGammaPatch1, gamma,
								 this->maxBDGGrayLevel,
								 reasonableDeltaChromaticity);
			Patch_ptr bestPatch = bestGammaPatch2;
			double bestGamma = processor.bestGamma;
			this->bestGammaAtGammaBoundGrayLevel = bestGamma;
			/*
			   gamma算出來了, 所以要去更動gamma curve, 讓做出來的結果真的有碰到bestPatch
			 */
			if (alterGammaCurveAtDeHook2) {
			    this->gammaCurve =
				processor.alterGammaCurve(this->gammaCurve,
							  bGap1stGammaBoundGrayLevel,
							  this->maxBDGGrayLevel, maxcount,
							  bestGamma);
			}

			RGB_ptr rgb = bestPatch->getRGB();
			redmax = rgb->R;
			greenmax = rgb->G;
			bluemax = rgb->B;
		    } else if (SecondWithGamma1st == deHook) {
			//找到最貼近target gamma的patch及gray level
		    }

		    break;
		};


		secondWhiteAnalyzer =
		    MaxMatrixIntensityAnalyzer::getReadyAnalyzer(mm, redmax, greenmax, bluemax);
	    };

	    /*
	       CCT + Gamma
	       不管PanelRegulator要怎麼用, 都是從LCDCalibrator量好必要的資訊, 再傳到AdvancedDGLutGenerator去
	       因為需要將兩種結果做smooth(target和native), 所以必須將remapping放在AdvancedDGLutGenerator內
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr <
						      MeasureCondition >
						      measureCondition,
						      bptr < DGLutFile > dgLutFile) {
		excuteStatus = "CCTDGLut";
		this->measureCondition = measureCondition;
		if (false == originalGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		bptr < PanelRegulator > panelRegulator;
		bool needPanelRegular = isDoDeHook();
		if (needPanelRegular) {
		    //原先: 以target white的rgb為最大值, 調整面板並重新量測
		    //改良: 以direct gamma(gamma test)直接改變打出的pattern, 達到相同效果
		    /*
		       dehook選項從target white拉到 cctlut去, 所以這邊重新產生新的analyzer
		       當dehook在target white的時候, 1st analyzer就是當作target white,
		       因為設定target white同時就考慮的hook

		       當dehook放到cctlut時, 因為1st analyzer沒考慮hook, 所以要產生2nd analyzer
		       去對應hook, 因此才要這邊的步驟
		     */

		    //if (null == secondWhiteAnalyzer) {
		    //此時找的是255 255 250(B Max IntensitY)
		    init2ndWhiteAnalyzer(keepMaxLuminance, dehook);
		    fetcher->SecondAnalyzer = secondWhiteAnalyzer;
		    //}

		    RGB_ptr rgb = secondWhiteAnalyzer->getReferenceRGB();
		    double_array values(new double[3]);
		    rgb->getValues(values, MaxValue::Double255);
		    bool regulatorFix = true;
		    if (!regulatorFix) {
			values[0] = (int) values[0];
			values[1] = (int) values[1];
			values[2] = (int) values[2];
		    }
		    panelRegulator = bptr < PanelRegulator >
			(new
			 GammaTestPanelRegulator(bitDepth, tconctrl,
						 values[0], values[1], values[2],
						 measureCondition));
		    //若是在direct gamma下, setEnable會無效
		    //因為setEnable是變更DG LUT, 但是direct gamma無視DG LUT的內容!
		    panelRegulator->setEnable(true);
		    remapped = true;
		}
		//原始特性量測
		this->originalComponentVector = fetchComponentVector();
		if (needPanelRegular && null != panelRegulator) {
		    panelRegulator->setEnable(false);
		}
		if (null == originalComponentVector) {
		    return nil_RGB_vector_ptr;
		}
		if (null != dgLutFile) {
		    //把一些設定訊息先存起來
		    storeInfo2DGLutFile(dgLutFile);
		}

		STORE_COMPONENT("0.0_o_fetch.xls", originalComponentVector);

		this->originalComponentVector = Util::copy(originalComponentVector);

		//=============================================================
		// gamma curve setting zone
		// 因為要量過才知道原始的 gamma, 所以這個原始gamma的設定位置異於其他選項
		//=============================================================
		if (true == originalGamma) {
		    //若要採用original gamma, 從量測結果拉出gamma, 當作目標gamma curve
		    double_vector_ptr originalGammaCurve =
			getOriginalGammaCurve(originalComponentVector);
		    setGammaCurve(originalGammaCurve);
		}

		STORE_DOUBLE_VECTOR("0.1_gammacurve.xls", gammaCurve);
		//=============================================================

		const MaxValue & quantizationBit = bitDepth->getLutMaxValue();

		if (true == useNewMethod) {
		    //新方法完全基於色度上的處理
		    dglut = newMethod(panelRegulator);
		} else {
		    //舊方法融合色度以及DG Code的處理
		    DGLutGenerator generator(originalComponentVector, keepMaxLuminance);
		    dglut = oldMethod(generator, panelRegulator, quantizationBit);
		}

		if (nil_RGB_vector_ptr == dglut) {
		    return nil_RGB_vector_ptr;
		}
		//==============================================================
		// DG Code Op block
		//==============================================================
		//量化
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		//==============================================================

		//==============================================================
		//調整max value, 調整到LUT真正的max value
		//==============================================================
		STORE_RGBVECTOR("7.9_dgcode_final.xls", result);
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());
		//==============================================================

		STORE_RGBVECTOR("8_dgcode_final.xls", result);
		this->dglut = result;
		return result;
	    };

	    bool LCDCalibrator::isDoDeHook() {
		return KeepCCT == dehook || SecondWithBGap1st == dehook
		    || SecondWithGamma1st == dehook;
	    };



	    /*
	       generator在此的用意只是拿來產生gamma curve
	     */
	    RGB_vector_ptr LCDCalibrator::newMethod(bptr < PanelRegulator > panelRegulator) {
		double brightgammaParameter = 1;
		//==========================================================
		// 新方法
		//==========================================================
		bptr < AdvancedDGLutGenerator > advgenerator;
		double_vector_ptr luminanceGammaCurve;
		double minLuminance =
		    (*originalComponentVector)[originalComponentVector->size() - 1]->XYZ->Y;


		//=============================================================
		// 產生 luminance gamma curve
		//=============================================================
		/*
		   KeepMaxLuminance::Smooth2NativeWhite
		   1. de-hook org
		   兩個white analyzer, 算出兩組component;
		   一組是native white, 一組是以b max intensity為基準的white
		   兩組結果做smooth

		   2. de-hook evo
		   直接對b intensity做smooth
		   將target B Intensity由100->Max B Intensity->100做smooth
		 */
		if (keepMaxLuminance == KeepMaxLuminance::Smooth2NativeWhite) {
		    //native white smooth
		    //Smooth2NativeWhite是為了兼顧Hook和最大亮度的折衷產物
		    //較適合NB使用
		    bptr < PanelRegulator > panelRegulator2;
		    Component_vector_ptr componentVector2;


		    //Smooth2NativeWhite + dehook org
		    int max = bitDepth->getInputMaxDigitalCount();
		    panelRegulator2 = bptr < PanelRegulator >
			(new
			 GammaTestPanelRegulator(bitDepth,
						 tconctrl, max,
						 max, maxBRawGrayLevel, measureCondition));
		    panelRegulator2->setEnable(true);
		    componentVector2 = fetchComponentVector();
		    STORE_COMPONENT("o_fetch2.xls", componentVector2);
		    panelRegulator2->setEnable(false);

		    //if (null == secondWhiteAnalyzer) {
		    //初始化255/255/255的white analyzer
		    init2ndWhiteAnalyzer(keepMaxLuminance, dehook);
		    //}

		    advgenerator = bptr < AdvancedDGLutGenerator >
			(new
			 AdvancedDGLutGenerator(originalComponentVector,
						fetcher,
						fetcher->getAnalyzer(),
						secondWhiteAnalyzer, bitDepth, *this));

		    advgenerator->setComponentVector2(componentVector2, panelRegulator2);

		    //==============================================================================
		    // luminanceGammaCurve的計算
		    //==============================================================================
		    // max luminance的採用還是很有爭議
		    double maxLuminance = (*originalComponentVector)[0]->XYZ->Y;
		    //藉由傳統generator產生luminance gamma curve
		    luminanceGammaCurve =
			getLuminanceGammaCurve(gammaCurve, maxLuminance, minLuminance);
		    //==============================================================================

		    //end of Smooth2NativeWhite
		} else {
		    //一般的case, 不用兼顧Hook和最大亮度
		    //NativeWhite(可搭配de-hook) & TargetWhite
		    //componentVector是事先量好的(呼叫此function之前)
		    if (isDoDeHook() && null == secondWhiteAnalyzer) {
			throw new
			    IllegalStateException("isDoDeHook() && null == secondWhiteAnalyzer");
		    }
		    //==========================================================
		    // 產生gamma curve用
		    //==========================================================
		    //max luminance
		    advgenerator =
			bptr < AdvancedDGLutGenerator >
			(new
			 AdvancedDGLutGenerator(originalComponentVector, fetcher, bitDepth, *this));


		    bptr < IntensityAnalyzerIF > firstAnalyzer = getFirstAnalzyer();
		    double targetLuminance = firstAnalyzer->getReferenceColor()->Y;
		    double maxLuminance = targetLuminance;
		    //藉由傳統generator產生luminance gamma curve
		    if (true == absoluteGamma) {
			int effectiven = bitDepth->getEffectiveInputLevel();	//256
			luminanceGammaCurve =
			    getLuminanceGammaCurve(gammaCurve,
						   maxLuminance,
						   minLuminance,
						   absoluteGamma,
						   absoluteGammaStart,
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

		if (correct == DimCorrect::DefinedDim) {
		    dimStrengthParameter = dimStrength;
		    underParameter = under;
		} else if (correct == DimCorrect::None) {
		    underParameter = 0;
		}

		int startCheckReversePos = 50;
		int minOverParameter = (useNewMethod
					&& autoKeepMaxLumiParameter) ?
		    startCheckReversePos : keepMaxLumiOver;
		advgenerator->setPanelRegulator(panelRegulator);


		//==================================================================================
		// init maxWhiteXYZ
		//==================================================================================
		XYZ_ptr maxWhiteXYZ = targetWhiteXYZ;
		double maxLuminance = (*luminanceGammaCurve)[luminanceGammaCurve->size() - 1];

		switch (keepMaxLuminance) {
		case KeepMaxLuminance::TargetLuminance:{
			//利用luminanceGammaCurve, 把native的亮度設定成luminanceGammaCurve的最大亮度
			maxWhiteXYZ = targetWhiteXYZ->clone();
			maxWhiteXYZ->normalizeY();
			maxWhiteXYZ->times(maxLuminance);
		    };
		    break;
		case KeepMaxLuminance::TargetWhite:
		    break;
		case KeepMaxLuminance::NativeWhite:
		    if (isDoDeHook()) {
			xyY_ptr secondWhite = secondWhiteAnalyzer->getReferenceColor()->clone();
			secondWhite->Y = maxLuminance;
			maxWhiteXYZ = secondWhite->toXYZ();
		    }
		};
		//==================================================================================

		//外部迴圈針對是否疊階來決定起始位置
		//這邊的思維是: 如果轉折點設定不當(太小太接近0), 就可能造成疊階
		//所以逐漸調整轉折點來讓疊階消失
		int overParameter = keepMaxLumiOver;
		const int step = 4;

		//開啟native white smooth(advanced)時, 會依照結果自動調整smooth區間的參數
		for (; overParameter >= minOverParameter; overParameter -= step) {
		    //設定目標參數: target end
		    advgenerator->setTarget(targetWhiteXYZ, maxWhiteXYZ,
					    luminanceGammaCurve,
					    underParameter, overParameter,
					    dimStrengthParameter,
					    brightgammaParameter,
					    bitDepth->getEffectiveInputLevel());
		    //得到目標值
		    targetXYZVector = advgenerator->TargetXYZVector;
		    if (null == targetXYZVector) {
			return nil_RGB_vector_ptr;
		    }
		    //從目標值算出DGLut
		    dglut = advgenerator->produce();
		    STORE_RGBVECTOR("3.1_org_dgcode.xls", dglut);
		    initialRGBGamma = advgenerator->RGBGenerateResult;
		    idealIntensity = advgenerator->IdealIntensity;

		    //=========================================================
		    // feedback
		    //=========================================================
		    if (true == feedbackFix && (true == debugMode || bitDepth->isTCONInput()
						|| pcWithTCONInput)) {
			//先從DGLut算出灰階的dx dy
			//再從這樣的結果微調目標值
			const MaxValue & lutMaxValue = bitDepth->getLutMaxValue();
			RGB_vector_ptr clone = RGBVector::deepClone(dglut);

			int frcBit = bitDepth->getFRCAbilityBit().bit;

			if (true == colorimetricQuanti && 11 == frcBit) {
			    //11bit下才可以使用colorimetricQuanti, 10bit下使用沒啥效果
			    int domainBit = frcBit + 2;
			    const MaxValue & domainMaxValue = MaxValue::getByIntegerBit(domainBit);
			    //先降到domain bit, 為FRC bit+2 bit
			    RGBVector::changeMaxValue(clone, domainMaxValue);
			    STORE_RGBVECTOR("3.2_domain_dgcode.xls", clone);

			    //進行smart quanti
			    clone = colorimetricQuantization(clone, 0);	//11bit
			    //用frc bit(11bit)去跑 feedback才是對的
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
			//檢查的時候, 還是需要將整個流程跑完才做檢查.
			//所以才需要呼叫getDGLutOpResult跟changeMaxValue
			//但是回傳的時候要回傳尚未處裡的結果, 不該把檢查用的回傳
			RGB_vector_ptr checkResult = RGBVector::deepClone(dglut);
			checkResult = getDGLutOpResult(checkResult);
			//要切到FRC的bit下檢查才是正確的, 而非LUT的bit
			RGBVector::changeMaxValue(checkResult, bitDepth->getFRCAbilityBit());
			//檢查
			if (RGBVector::
			    isAscend(checkResult, startCheckReversePos,
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
	       從ch來挑選delta資料
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
		    bptr < FeedbackFixer >
		    (new
		     FeedbackFixer(dimFixEnd, dimFixThreshold, fetcher->getAnalyzer(), bitDepth));
		feedbackFixer->Listener = this->feedbackListener;
		feedbackFixer->fixReverseByFeedback(dglut);
		this->feedbackFixCount = feedbackFixer->FeedbackFixCount;
		this->maxMeasureError = feedbackFixer->getMaxMeasureError();
		this->initDefectCount = feedbackFixer->InitDefectCount;
	    };


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
		// 老方法
		//==========================================================
		RGBGamma_ptr rgbgamma = generator.getRGBGamma(gammaCurve);
		initialRGBGamma = rgbgamma->clone();
		STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);
		/* TODO : bIntensityGain要確認 */
		//老實講調intensity我覺得是很爛的作法
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
		RGB_vector_ptr dglut = generator.getCCTDGLut(rgbgamma);
		STORE_RGBVECTOR("3_dgcode.xls", dglut);
		//==============================================================
		//第一次量化處理
		//==============================================================
		//量化
		//MaxValue quantizationBit = bitDepth->getLutMaxValue();
		if (null != panelRegulator) {
		    dglut = panelRegulator->remapping(dglut);
		    STORE_RGBVECTOR("3.1_remap.xls", dglut);
		}
		RGBVector::quantization(dglut, quantizationBit);
		//==============================================================
		if (correct == DimCorrect::P1P2) {
		    //==========================================================
		    //p1p2第一階段, 對gamma做調整
		    //==========================================================
		    bptr < P1P2GammaOp > p1p2(new P1P2GammaOp(p1, p2, dglut));
		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(p1p2);
		    //產生修正後的gamma2(若沒有p1p2,則為原封不動)
		    rgbgamma = gammaop.createInstance();
		    if (null == rgbgamma) {
			return nil_RGB_vector_ptr;
		    }
		    STORE_RGBGAMMA("5.0_rgbgamma_p1p2.xls", rgbgamma);
		    //從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    //量化
		    STORE_RGBVECTOR("5.1_dgcode_p1p2g.xls", dglut);
		    RGBVector::quantization(dglut, quantizationBit);
		    STORE_RGBVECTOR("5.2_dgcode_p1p2g.xls", dglut);
		    //==========================================================
		    //==========================================================
		    //p1p2第二階段, 對dg code調整
		    //==========================================================
		    DGLutOp dgop;
		    dgop.setSource(dglut);
		    bptr < DGLutOp > op(new P1P2DGOp(p1, p2));
		    dgop.addOp(op);
		    dglut = dgop.createInstance();
		    //量化
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
		    //暫不提供
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
		//砍掉已存在的
		Util::deleteExist(filename);
		//產生新檔
		bptr < DGLutFile > file(new DGLutFile(filename, Create));
		storeInfo2DGLutFile(file);
		storeDGLut2DGLutFile(file, dglut);

		return file;
	    };



	    void LCDCalibrator::storeInfo2DGLutFile(bptr < cms::colorformat::DGLutFile > dglutFile) {
		DGLutProperty property(this);
		//寫入property
		dglutFile->setProperty(property);

		if (null != originalComponentVector) {
		    //寫入raw data
		    dglutFile->setRawData(originalComponentVector, initialRGBGamma, finalRGBGamma);
		}
		if (null != lcdmodel4DeHook) {
		    dglutFile->setLCDTarget(lcdmodel4DeHook->LCDTarget);
		    if (null != bestGammaPatch1) {
			dglutFile->addToLCDTarget(bestGammaPatch1);
			dglutFile->addToLCDTarget(bestGammaPatch2);
		    }
		}


	    };

	    void LCDCalibrator::storeDGLut2DGLutFile(bptr <
						     cms::colorformat::
						     DGLutFile > dglutFile, RGB_vector_ptr dglut) {
		dglutFile->setGammaTable(dglut);
		if (null != targetXYZVector) {
		    dglutFile->setTargetXYZVector(targetXYZVector, dglut, bitDepth);
		}

		bptr < cms::measure::MeterMeasurement > mm = getMeterMeasurement();
		if (null != mm && !mm->FakeMeasure) {
		    Patch_vector_ptr measurePatchVector = mm->MeasurePatchVector;
		    if (measurePatchVector->size() != 0) {
			dglutFile->setMeasure(measurePatchVector);
		    }
		}
	    }

	    Component_vector_ptr LCDCalibrator::getDimComponentVector(RGB_vector_ptr dglut) {
		RGB_vector_ptr measureCode = RGBVector::copyRange(dglut, 0, dimFixEnd);
		//50量到0
		measureCode = RGBVector::reverse(measureCode);
		RGBVector::quantization(measureCode, bitDepth->getFRCAbilityBit());
		bptr < MeasureCondition > measureCondition(new MeasureCondition(measureCode));
		Component_vector_ptr componentVector;	// = fetcher->fetchComponent(measureCondition);
		if (true == linkCA210) {
		    //有連上ca210就量測取得
		    componentVector = fetcher->fetchComponent(measureCondition);
		} else {
		    //否則就挖之前的檔案來當量測數據
		    DGLutFile dglut("6.0_dimComponent.xls", ReadOnly);
		    componentVector = dglut.getComponentVector();
		}
		STORE_COMPONENT("6.0_dimComponent.xls", componentVector);
		return componentVector;
	    };


	    RGB_vector_ptr LCDCalibrator::getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		RGB_vector_ptr source = RGBVector::deepClone(dglut);
		DGLutOp dgop;
		dgop.setSource(source);
		//==============================================================
		// dim修正
		//==============================================================
		if (correct == DimCorrect::RBInterpolation) {
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
		    //如果用上dehook2, maxBDGGrayLevel到白點需要內插, 使色度漸進到白點
		    if (SecondWithBGap1st == dehook || SecondWithBGap1st == dehook) {
			RGB_ptr rgb = secondWhiteAnalyzer->getReferenceRGB();
			if (-1 == maxBDGGrayLevel) {
			    ShowMessage("-1 == maxBDGGrayLevel");
			}
			bptr < DGLutOp > deHook2(new DeHook2Op(bitDepth, rgb, maxBDGGrayLevel));
			dgop.addOp(deHook2);
		    }
		    break;
		case KeepMaxLuminance::Smooth2NativeWhite:{
			//最後還是要對DG做一次smooth
			bptr < DGLutOp >
			    nativeWhiteAdv(new
					   KeepNativeWhiteSmoothOp
					   (bitDepth, keepMaxLumiOver, false));
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
		//==============================================================
		// dim修正, 在xy domain上進行
		//==============================================================

		if (dimFix) {
		    //50量到0
		    Component_vector_ptr dimComponentVector = getDimComponentVector(dglut);
		    bptr < ChromaticityAdjustEstimatorIF >
			chromaticityEstimator(new
					      MeasureEstimator
					      (dimComponentVector,
					       fetcher->getAnalyzer(), bitDepth));
		    bptr < DGLutOp >
			dimfix(new
			       DimDGLutFixOp(bitDepth, dimFixThreshold,
					     dimComponentVector, chromaticityEstimator));
		    dgop.addOp(dimfix);
		}
		//==============================================================

		RGB_vector_ptr result = dgop.createInstance();
		//==============================================================
		// keep dark level
		//==============================================================
		if (keepDarkLevel) {
		    RGB_ptr rgb0 = (*result)[0];
		    rgb0->R = 0;
		    rgb0->G = 0;
		    rgb0->B = 0;
		}
		//==============================================================
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

	    bptr < MeterMeasurement > LCDCalibrator::getMeterMeasurement() {
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = getFirstAnalzyer();
		bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
		return mm;
	    };
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
	       gamma curve又分絕對和相對的
	       相對的較簡單, 絕對的會遇到無法整條線都meet的問題
	       samsung是規定8灰階的gamma要達到2.1以上; 為求保險, 直接把灰階8設在gamma 2.2,
	       然後推算絕對gamma 2.2的相對gamma是多少, 以該gamma 接回原點(灰階0)

	       effectiven有錯?
	     */
	    double_vector_ptr LCDCalibrator::getLuminanceGammaCurve(double_vector_ptr normalGammaCurve, double maxLuminance, double minLuminance, bool absGamma,	//
								    int absGammaStartGL,	//8
								    double startGLAboveGamma,	//2.2
								    int effectiven) {	//256
		if (true == absGamma) {
		    int size = normalGammaCurve->size();
		    //=========================================================
		    // 1
		    //=========================================================

		    //計算abs gamma起點的normal input
		    double startNormalInput =
			static_cast < double >(absGammaStartGL) / (effectiven - 1);
		    double startAbsoluteNormalOutput = GammaFinder::gamma(startNormalInput,
									  startGLAboveGamma);
		    double startAbsoluteLuminance = maxLuminance * startAbsoluteNormalOutput;
		    //=========================================================
		    // 2
		    //=========================================================
		    if (startAbsoluteLuminance < minLuminance) {
			//若灰階設定太低就會落到此case
			//回傳nul代表找不到
			return nil_double_vector_ptr;
		    }
		    //換算相對應的rel gamma
		    double relativeNormalOutput =
			(startAbsoluteLuminance - minLuminance) / (maxLuminance - minLuminance);
		    double relativeGamma = GammaFinder::getGammaExponential(startNormalInput,
									    relativeNormalOutput);
		    int turnGrayLevel = -1;


		    //=========================================================
		    // 4 找到turnGrayLevel
		    //=========================================================
		    for (int x = absGammaStartGL; x < 255; x++) {
			double normalInput = static_cast < double >(x) / (effectiven - 1);

			double absoluteNormalOutput = (*normalGammaCurve)[x];
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

		    //相對gamma區間
		    for (int x = 0; x < turnGrayLevel; x++) {
			//此區段設定順勢修正到abs gamma
			double normalInput = static_cast < double >(x) / (effectiven - 1);
			double relativeNomralOutput =
			    GammaFinder::gamma(normalInput, relativeGamma);
			newNormalGammaCurve->push_back(relativeNomralOutput);
		    }
		    //絕對gamma區間
		    for (int x = turnGrayLevel; x < effectiven; x++) {
			//此區段符合abs gamma
			//double normalInput = ((double) x) / effectiven;
			//原始是abs, 要轉成rel
			double absoluteNormalOutput = (*normalGammaCurve)[x];
			double absoluteGammaLuminance = absoluteNormalOutput * maxLuminance;
			double relativeNormalOutput =
			    (absoluteGammaLuminance - minLuminance) / (maxLuminance - minLuminance);

			if (relativeNormalOutput < 0) {
			    return nil_double_vector_ptr;
			}
			//double absGamma = GammaFinder::getGamma(normalInput, absoluteNormalOutput);


			newNormalGammaCurve->push_back(relativeNormalOutput);

		    }
		    for (int x = effectiven; x < size; x++) {
			double absoluteNormalOutput = (*normalGammaCurve)[x];
			newNormalGammaCurve->push_back(absoluteNormalOutput);
		    }
		    return getLuminanceGammaCurve(newNormalGammaCurve, maxLuminance, minLuminance);
		} else {
		    return getLuminanceGammaCurve(normalGammaCurve, maxLuminance, minLuminance);
		}
		//==================================================================
	    };



	};
    };
};

