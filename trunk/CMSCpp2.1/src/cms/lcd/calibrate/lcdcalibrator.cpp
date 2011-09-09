#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"
#include <gui/cct/TMainForm.h>
//#include <cms/colorformat/excelfile.h>
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
	    /*void LCDCalibrator::setDimFixEnd(int fixEnd) {
	       this->dimFixEnd = fixEnd;
	       };
	       void LCDCalibrator::setDimFix(bool dimFix) {
	       this->dimFix = dimFix;
	       };
	       void LCDCalibrator::setDimFixThreshold(double threshold) {
	       this->dimFixThreshold = threshold;
	       } */
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
	    /*void LCDCalibrator::setGByPass(bool byPass) {
	       this->gByPass = byPass;
	       };
	       void LCDCalibrator::setBIntensityGain(double gain) {
	       this->bIntensityGain = gain;
	       };
	       void LCDCalibrator::setBMax(bool bMax) {
	       this->bMax = bMax;
	       }; */
	    void LCDCalibrator::setBMax2(bool bMax2, int begin, double gamma) {
		this->bMax2 = bMax2;
		bMax2Begin = begin;
		bMax2Gamma = gamma;
	    };
	    /*void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
	       this->avoidFRCNoise = avoid;
	       }; */
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
	    /*void LCDCalibrator::setNewMethod(bool enable) {
	       this->useNewMethod = enable;
	       };
	       void LCDCalibrator::setSkipInverseB(bool skip) {
	       this->skipInverseB = skip;
	       }; */
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
		manualAccurateMode = false;
		middleCCTRatio = -1;
		dimFixEnd = 50;
		dimFix = false;
		dimFixThreshold = 0.0000;
	    };

	    Component_vector_ptr LCDCalibrator::fetchComponentVector() {
		//量測start->end得到的coponent/Y
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
	       當有smooth CCT到native white需求時，就需要native white analyzer
	       ，求得更準確的DG Lut
	     */
	    void LCDCalibrator::initNativeWhiteAnalyzer() {
		//=====================================================
		// 生出一組新的analyzer, 給smooth target的時候用
		// 有這組analyzer, 在smooth到native white的時候可以得到更準確的結果.
		//=====================================================
		//產生max matrix
		bptr < cms::measure::IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
		nativeWhiteAnalyzer =
		    bptr < MaxMatrixIntensityAnalyzer > (new MaxMatrixIntensityAnalyzer(mm));

		int max = bitDepth->getMaxDigitalCount();
		int blueMax = max;

		if (keepMaxLuminance ==
		    KeepMaxLuminance::NativeWhiteAdvanced && true == skipInverseB) {
		    //若要略過inverse B, 則要先量測到B在哪裡反轉
		    //然後設定b最大只用到反轉點
		    blueMax = MeasureTool::getMaxZDGCode(mm, bitDepth);
		    this->maxZDGCode = blueMax;
		}
		//已知rgb
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
	       不管PanelRegulator要怎麼用, 都是從LCDCalibrator量好必要的資訊, 再傳到AdvancedDGLutGenerator去
	       因為需要將兩種結果做smooth(target和native), 所以必須將remapping放在AdvancedDGLutGenerator內
	     */
	    RGB_vector_ptr LCDCalibrator::getCCTDGLut(bptr < MeasureCondition > measureCondition) {
		this->measureCondition = measureCondition;
		if (false == originalGamma && null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		bool doAccurate = (true == accurateMode) && (null != tconctrl);
		bptr < PanelRegulator > panelRegulator;
		if (doAccurate) {
		    //原先: 以target white的rgb為最大值, 調整面板並重新量測
		    //改良: 以direct gamma(gamma test)直接改變打出的pattern, 達到相同效果

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
		    //null代表量測被中斷
		    return RGB_vector_ptr((RGB_vector *) null);
		}

		if (true == originalGamma) {
		    //若要採用original gamma, 從量測結果拉出gamma, 當作目標gamma curve
		    double_vector_ptr gammaCurve = getGammaCurve(componentVector);
		    setGammaCurve(gammaCurve);
		}

		STORE_COMPONENT("o_fetch.xls", componentVector);
		STORE_DOUBLE_VECTOR("0_gammacurve.xls", gammaCurve);

		DGLutGenerator generator(componentVector, keepMaxLuminance);
		const MaxValue & quantizationBit = bitDepth->getLutMaxValue();

		if (true == useNewMethod) {
		    //新方法完全基於色度上的處理
		    dglut = newMethod(generator, panelRegulator);
		} else {
		    //舊方法融合色度以及DG Code的處理
		    dglut = oldMethod(generator, panelRegulator, quantizationBit);
		}



		//==============================================================
		// DG Code Op block
		//==============================================================
		//量化
		RGB_vector_ptr result = getDGLutOpResult(dglut, generator);
		//==============================================================



		//==============================================================
		// intensity的影響計算
		//==============================================================
		/*double_vector_ptr b1 =
		   generator.getIntensityVector(Channel::B, dglut);
		   double_vector_ptr b2 =
		   generator.getIntensityVector(Channel::B, result);
		   STORE_DOUBLE_VECTOR("b1.xls", b1);
		   STORE_DOUBLE_VECTOR("b2.xls", b2); */
		//==============================================================


		//==============================================================
		//調整max value, 調整到LUT真正的max value
		//==============================================================
		STORE_RGBVECTOR("7.9_dgcode_final.xls", result);
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());
		//==============================================================
		//已產生出DG, 可在此處量測
		/*if (dimFix) {
		   //STORE_RGBVECTOR("7.1_before_dimFix.xls", result);
		   result = dimDGLutFix(result);
		   //STORE_RGBVECTOR("7.2_after_dimFix.xls", result);
		   } */


		STORE_RGBVECTOR("8_dgcode_final.xls", result);
		this->dglut = result;
		return result;
	    };



	    /*bool_array LCDCalibrator::getDefectArray(double2D_ptr deltaxyValues, double threshold) {
		int size = deltaxyValues->dim1();
		bool_array defectArray(new bool[size]);
		for (int x = 0; x < size; x++) {
		    defectArray[x] = false;
		}

		for (int x = 1; x < size; x++) {
		    double dx = (*deltaxyValues)[x][0];
		    double dy = (*deltaxyValues)[x][1];
		    if (dx < threshold || dy < threshold) {
			defectArray[x] = true;
		    }
		}
		return defectArray;
	    }
	    int getDefectType(bool dxdefect, bool dydefect) {
		if (dxdefect && dydefect) {
		    return 3;
		} else if (dxdefect) {
		    return 1;
		} else if (dydefect) {
		    return 2;
		} else {
		    return -1;
		}
	    };
	    bool_array LCDCalibrator::getContinueDefectArray(double2D_ptr deltaxyValues,
							     double threshold) {
		int size = deltaxyValues->dim1();
		bool_array defectArray(new bool[size]);
		for (int x = 0; x < size; x++) {
		    defectArray[x] = false;
		}
		// dx = 1
		// dy = 2
		// dx + dy =3
		int defectType = -1;

		for (int x = 1; x < size - 1; x++) {
		    bool dx = (*deltaxyValues)[x][0] < threshold;
		    bool dy = (*deltaxyValues)[x][1] < threshold;
		    bool nextdx = (*deltaxyValues)[x + 1][0] < threshold;
		    bool nextdy = (*deltaxyValues)[x + 1][1] < threshold;
		    int thisDefectType = getDefectType(dx, dy);
		    int nextDefectType = getDefectType(nextdx, nextdy);

		    if (defectType == -1 && thisDefectType != -1) {
			if (thisDefectType == nextDefectType) {
			    defectArray[x] = true;
			    defectArray[x + 1] = true;
			}
		    }
		}
		return defectArray;
	    }*/

	    /*RGB_vector_ptr LCDCalibrator::dimDGLutFix(RGB_vector_ptr original) {
		RGB_vector_ptr measureCode = RGBVector::copyRange(original, 0, 50);
		//50量到0
		measureCode = RGBVector::reverse(measureCode);
		bptr < MeasureCondition > measureCondition(new MeasureCondition(measureCode));


		Component_vector_ptr componentVector;	// = fetcher->fetchComponent(measureCondition);
		if (true == MainForm->linkCA210) {
		    componentVector = fetcher->fetchComponent(measureCondition);
		} else {
		    DGLutFile dglut("7.4_dimComponent.xls", ReadOnly);
		    componentVector = dglut.getComponentVector();
		}


		STORE_RGBVECTOR("7.1_before_fix.xls", original);
		RGB_vector_ptr result = RGBVector::deepClone(original);
		RGBVector::quantization(result, bitDepth->getFRCAbilityBit(), true);
		STORE_RGBVECTOR("7.2_quant2FRC.xls", result);
		RGBVector::changeMaxValue(result, bitDepth->getFRCAbilityBit());
		STORE_RGBVECTOR("7.3_change2FRC.xls", result);




		STORE_COMPONENT("7.4_dimComponent.xls", componentVector);
		double2D_ptr deltaxyValues = getDeltaxyValues(componentVector);
		int size = deltaxyValues->dim1();

		//const double Normal = 0.0000;
		//const double Tiny = 0.0001;
		double threshold = dimFixThreshold;

		const double SuitGap = 0.0009;
		bool_array defectArray = getDefectArray(deltaxyValues, threshold);
		bool_array continueDefectArray = getContinueDefectArray(deltaxyValues, threshold);


		for (int x = 1; x < size; x++) {
		    bool defect = defectArray[x];
		    bool predefect = defectArray[x - 1];
		    bool nextdefect = defectArray[x + 1];
		    //目前要是相鄰有defect就先不動, 因為太複雜!
		    bool doDefectErase = defect && !predefect && !nextdefect;


		    if (doDefectErase) {
			//確定要消除defect
			int grayLevel = 50 - x;
			double dx = (*deltaxyValues)[x][0];
			double dy = (*deltaxyValues)[x][1];

			double predx = (*deltaxyValues)[x - 1][0];
			double pre2dx = dx + predx;
			double predy = (*deltaxyValues)[x - 1][1];
			double pre2dy = dy + predy;

			//三種defect, 從delta確認是哪一種
			if (dx < threshold && dy < threshold) {
			    if (pre2dx < SuitGap) {
				//太擠
				(*result)[grayLevel - 1]->B += 1;
			    } else {
				(*result)[grayLevel]->B -= 1;
			    }

			} else if (dx < threshold) {
			    //dx <0
			    //double predx = (*deltaxyValues)[x - 1][0];
			    //double pre2dx = dx + predx;
			    if (pre2dx < SuitGap) {
				//太擠
				(*result)[grayLevel - 1]->R -= 1;
			    } else {
				(*result)[grayLevel]->R += 1;
			    }
			} else if (dy < threshold) {
			    //dy <0
			    //double predy = (*deltaxyValues)[x - 1][1];
			    //double pre2dy = dy + predy;
			    if (pre2dy < SuitGap) {
				//太擠
				(*result)[grayLevel - 1]->G -= 1;
			    } else {
				(*result)[grayLevel]->G += 1;
			    }

			}
		    }
		}
		STORE_RGBVECTOR("7.5_afterFix.xls", result);
		RGBVector::changeMaxValue(result, bitDepth->getLutMaxValue());
		STORE_RGBVECTOR("7.6_change2LUT.xls", result);
		return result;
	    };*/

	    RGB_vector_ptr LCDCalibrator::newMethod(DGLutGenerator & generator,
						    bptr < PanelRegulator > panelRegulator) {
		double brightgammaParameter = 1;
		//==========================================================
		// 新方法
		//==========================================================
		bptr < AdvancedDGLutGenerator > advgenerator;
		double_vector_ptr luminanceGammaCurve;

		//=============================================================
		// 產生 luminance gamma curve
		//=============================================================
		if (keepMaxLuminance == KeepMaxLuminance::NativeWhiteAdvanced) {
		    //NativeWhiteAdvanced是為了兼顧Hook和最大亮度的折衷產物
		    bptr < PanelRegulator > panelRegulator2;
		    Component_vector_ptr componentVector2;
		    bool doAccurate = (true == accurateMode) && (true == skipInverseB)
			&& (null != tconctrl);
		    if (null == nativeWhiteAnalyzer) {
			initNativeWhiteAnalyzer();

			if (doAccurate) {
			    //若要skipInverseB, 就應該調整面板特性重新量測
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
		    // luminanceGammaCurve的計算
		    //==============================================================================
		    // max luminance的採用還是很有爭議
		    double maxLuminance =
			(true == skipInverseB) ?
			nativeWhiteAnalyzer->getReferenceColor()->Y : (*componentVector)[0]->XYZ->Y;
		    double minLuminance = (*componentVector)[componentVector->size() - 1]->XYZ->Y;
		    //藉由傳統generator產生luminance gamma curve
		    luminanceGammaCurve =
			generator.getLuminanceGammaCurve(gammaCurve, maxLuminance, minLuminance);
		    //==============================================================================
		} else {
		    advgenerator =
			bptr < AdvancedDGLutGenerator >
			(new AdvancedDGLutGenerator(componentVector, fetcher, bitDepth));
		    luminanceGammaCurve = generator.getLuminanceGammaCurve(gammaCurve);
		    keepMaxLumiOver = bitDepth->getEffectiveLevel();

		}
		//=============================================================
		STORE_DOUBLE_VECTOR("1_lumigammacurve.xls", luminanceGammaCurve);


		double dimgammaParameter = 3.5;
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

		//外部迴圈針對是否疊階來決定起始位置
		//這邊的思維是: 如果轉折點設定不當(太小太接近0), 就可能造成疊階
		//所以逐漸調整轉折點來讓疊階消失
		int overParameter = keepMaxLumiOver;
		int startCheckPos = 50;
		int minOverParameter = (useNewMethod && autoKeepMaxLumiParameter) ?
		    startCheckPos : keepMaxLumiOver;
		//int minOverParameter = startCheckPos;
		advgenerator->setPanelRegulator(panelRegulator);
		int step = 4;

		bptr < IntensityAnalyzerIF > analyzer = fetcher->getAnalyzer();
		//analyzer若沒有設定過target color, 會使此步驟失效
		//因為analyzer->getReferenceColor()會是null
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
			//檢查的時候, 還是需要將整個流程跑完才做檢查.
			//所以才需要呼叫getDGLutOpResult跟changeMaxValue
			//但是回傳的時候要回傳尚未處裡的結果, 不該把檢查用的回傳
			RGB_vector_ptr checkResult = RGBVector::deepClone(dglut);
			checkResult = getDGLutOpResult(checkResult, generator);
			//要切到FRC的bit下檢查才是正確的, 而非LUT的bit
			RGBVector::changeMaxValue(checkResult, bitDepth->getFRCAbilityBit());
			//檢查
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
		    STORE_RGBGAMMA("4.0_rgbgamma_p1p2.xls", rgbgamma);

		    //從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		    dglut = generator.getCCTDGLut(rgbgamma);
		    //量化
		    STORE_RGBVECTOR("4.1_dgcode_p1p2g.xls", dglut);
		    RGBVector::quantization(dglut, quantizationBit);
		    STORE_RGBVECTOR("4.2_dgcode_p1p2g.xls", dglut);
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
		storeDGLutFile(dglut, file);
		return file;
	    };

	    void LCDCalibrator::storeDGLutFile(RGB_vector_ptr dglut,
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
					   KeepNativeWhiteAdvancedOp(bitDepth, keepMaxLumiOver,
								     false));
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
		    //STORE_RGBVECTOR("7.1_before_dimFix.xls", result);
		    //result = dimDGLutFix(result);
		    //STORE_RGBVECTOR("7.2_after_dimFix.xls", result);
		    RGB_vector_ptr measureCode = RGBVector::copyRange(dglut, 0, dimFixEnd);
		    //50量到0
		    measureCode = RGBVector::reverse(measureCode);
		    bptr < MeasureCondition > measureCondition(new MeasureCondition(measureCode));


		    Component_vector_ptr componentVector;	// = fetcher->fetchComponent(measureCondition);
		    if (true == MainForm->linkCA210) {
			//有連上ca210就量測取得
			componentVector = fetcher->fetchComponent(measureCondition);
		    } else {
			//否則就挖之前的檔案來當量測數據
			DGLutFile dglut("5.0_dimComponent.xls", ReadOnly);
			componentVector = dglut.getComponentVector();
		    }
		    STORE_COMPONENT("5.0_dimComponent.xls", componentVector);

		    const double SuitGap = 0.0009;
		    bptr < DGLutOp > dimfix(new DimDGLutFixOp(bitDepth, dimFixThreshold, SuitGap,
							      componentVector));
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
	    /*bptr < cms::measure::MaxMatrixIntensityAnalyzer >
	       LCDCalibrator::getNativeWhiteAnalyzer() {
	       return nativeWhiteAnalyzer;
	       }
	       void LCDCalibrator::setNativeWhiteAnalyzer(bptr <
	       cms::measure::
	       MaxMatrixIntensityAnalyzer > analyzer) {
	       this->nativeWhiteAnalyzer = analyzer;
	       }; */
	    /*void LCDCalibrator::setTCONControl(bptr < i2c::TCONControl > tconctrl) {
	       this->tconctrl = tconctrl;
	       }; */
	    /*void LCDCalibrator::setAccurateMode(bool enable) {
	       this->accurateMode = enable;
	       };
	       void LCDCalibrator::setManualAccurateMode(bool enable) {
	       this->manualAccurateMode = enable;
	       };
	       void LCDCalibrator::setMiddleCCTRatio(double ratio) {
	       this->middleCCTRatio = ratio;
	       }; */
	};
    };
};

