#include <includeall.h>
#pragma hdrstop
#include "rgbvectorop.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
//#include "rgbvectorop.h";

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace Dep;
	    using namespace cms::util;
	    using namespace math;
	    using namespace java::lang;

	    //==================================================================
	    RGB_vector_ptr LinearOp::getRendering(RGB_vector_ptr source) {

		int size = source->size();
		RGB_vector_ptr result(new RGB_vector());
		for (int x = 0; x < size; x++) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb2->G = rgb2->B = x;
		     result->push_back(rgb2);
		};
		 return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr MinusOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result(new RGB_vector());
		 foreach(RGB_ptr rgb, *source) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb->R - minusValue;
		     rgb2->G = rgb->G - minusValue;
		     rgb2->B = rgb->B - minusValue;
		     result->push_back(rgb2);
		};
		return result;
	    };
	  MinusOp::MinusOp(double minusValue):minusValue(minusValue) {
	    };
	    //==================================================================
	    // P1P2DGOp
	    //==================================================================
	    RGB_vector_ptr P1P2DGOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGB_ptr rgbp1 = (*result)[p1];


		for (int x = 0; x != p1; x++) {
		    double v = x * rgbp1->G / p1;
		    //double d = java::lang::Math::roundTo(v * 4);
		    RGB_ptr rgb = (*result)[x];
		    rgb->setValues(v, v, v);
		    //rgb->quantization(maxValue);
		}

		RGB_ptr rgbp0 = (*result)[p1 - 1];
		RGB_ptr rgbp2 = (*result)[p1 + 1];
		rgbp1->R = (rgbp0->R + rgbp2->R) / 2;
		rgbp1->G = (rgbp0->G + rgbp2->G) / 2;
		rgbp1->B = (rgbp0->B + rgbp2->B) / 2;
		//rgbp1->quantization(maxValue);

		return result;
	    };
	    /*P1P2DGOp::P1P2DGOp(double p1, double p2, const MaxValue & maxValue):p1(p1), p2(p2), maxValue(maxValue)
	       {
	       }; */
	  P1P2DGOp::P1P2DGOp(double p1, double p2):p1(p1), p2(p2) {
	    };
	    //==================================================================

	    //==================================================================
	    // RGBInterpolation
	    //==================================================================
	    RGB_vector_ptr RGBInterpolationOp::getRendering(RGB_vector_ptr source) {

		double rInterval = (*source)[under]->R / under;
		double gInterval = (*source)[under]->G / under;
		double bInterval = (*source)[under]->B / under;
		RGB_vector_ptr result = RGBVector::deepClone(source);


		for (int x = 0; x != under; x++) {
		    //做RGB interpolation
		    RGB_ptr rgb = (*result)[x];

		    rgb->R = rInterval * x;
		    rgb->G = gInterval * x;
		    rgb->B = bInterval * x;
		}
		return result;
	    };
	  RGBInterpolationOp::RGBInterpolationOp(int under):under(under) {
	    };

	    //==================================================================
	    int RBInterpolationOp::calculateAutoUnder() {
		return -1;
	    };
	    RGB_vector_ptr RBInterpolationOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		int realunder = under;
		if (autoUnder) {
		    realunder = calculateAutoUnder();
		}
		for (int x = 1; x != realunder; x++) {
		    double gratio = (realunder - x + 1) / realunder;
		    //做RB interpolation
		    RGB_ptr rgb = (*result)[x];

		    //double r_ = rgb->R * (1 - gratio) + rgb->G * gratio;
		    //double b_ = rgb->B * (1 - gratio) + rgb->G * gratio;
		    double r = Interpolation::linear(0, 1, rgb->R, rgb->G, gratio);
		    double b = Interpolation::linear(0, 1, rgb->B, rgb->G, gratio);

		    rgb->R = r;
		    rgb->B = b;

		}
		RGB_ptr rgb0 = (*result)[0];
		rgb0->R = rgb0->G = rgb0->B = 0;
		return result;
	    };
	  RBInterpolationOp::RBInterpolationOp(int under):under(under),
		autoUnder(false) {
	    };
	    RBInterpolationOp::RBInterpolationOp(int under, bool autoUnder):under(under),
		autoUnder(autoUnder) {
	    };

	    //==================================================================
	    // BMaxOp
	    //==================================================================
	  BMaxOp::BMaxOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth) {

	    };
	    RGB_vector_ptr BMaxOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		//==============================================================
		//把未用到的區域全部處理成最大值
		int n = bitDepth->getLevel() - 1;
		int effectiven = (bitDepth->getEffectiveInputLevel() - 1);
		for (int x = n; x >= effectiven; x--) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getOutputMaxDigitalCount();
		}
		//==============================================================

		for (int x = effectiven; x != -1; x--) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr nextrgb = (*result)[x - 1];
		    //設定差異
		    // 253~   : 2.5
		    // 233~252: 2
		    //    ~232: 1.5
		    double diff = x > 252 ? 10 / 4. : (x > 232 ? 8 / 4. : 6 / 4.);
		    double thisB = rgb->B;
		    double nextB = nextrgb->B;
		    if (thisB > nextB) {
			nextrgb->B = thisB - diff;
		    } else {
			//代表有反轉
			double preB = (*result)[x + 1]->B;
			rgb->B = (preB + nextB) / 2.;
			break;
		    }
		}

		return result;
	    };
	    //==================================================================

	    //==================================================================
	    // BMax2Op
	    //==================================================================
	  BMax2Op::BMax2Op(bptr < BitDepthProcessor > bitDepth, int begin, double gamma):bitDepth(bitDepth), begin(begin), gamma(gamma)
	    {

	    };
	    RGB_vector_ptr BMax2Op::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		//==============================================================
		//把未用到的區域全部處理成最大值
		int effectiven = bitDepth->getEffectiveInputLevel();
		for (int x = effectiven; x != bitDepth->getLevel(); x++) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getOutputMaxDigitalCount();
		}
		//==============================================================
		RGB_ptr rgb0 = (*result)[begin];
		RGB_ptr rgb1 = (*result)[effectiven];
		int base = effectiven - 1;

		//==============================================================
		// smooth的處理
		//==============================================================
		bool useSCurve = true;
		if (useSCurve) {
		    SCurve scurve(-3, 3);
		    for (int x = begin + 1; x != effectiven; x++) {
			RGB_ptr rgb = (*result)[x];
			double normal = ((double) x - begin) / (base - begin);
			double v = scurve.getValue(normal);
			double b = Interpolation::linear(0, 1, rgb0->B, rgb1->B, v);
			rgb->B = b;
		    }
		} else {
		    for (int x = begin + 1; x != effectiven; x++) {
			RGB_ptr rgb = (*result)[x];
			double normal = ((double) x - begin) / (base - begin);
			double v = Math::pow(normal, gamma);
			double b = Interpolation::linear(0, 1, rgb0->B, rgb1->B, v);
			rgb->B = b;
		    }
		}
		//==============================================================


		return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr GByPassOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		//8/6 0~244,245~250,251~255
		//6/6 0~251,252~255

		if (bitDepth->is8in6Out()) {
		    for (int x = 0; x != 245; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 245; x != 251; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 0.5;
		    };
		    for (int x = 251; x != 256; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 1;
		    };
		} else {
		    int effectiveLevel = bitDepth->getEffectiveInputLevel();
		    int level = bitDepth->getLevel();
		    for (int x = 0; x != effectiveLevel; x++) {
			(*result)[x]->G = x;
		    }
		    for (int x = effectiveLevel; x != level; x++) {
			(*result)[x]->G = bitDepth->getOutputMaxDigitalCount();
		    }
		}
		/*else if (bitDepth->is6in6Out()) {
		   for (int x = 0; x != 252; x++) {
		   (*result)[x]->G = x;
		   };
		   for (int x = 252; x != 256; x++) {
		   (*result)[x]->G = 252;
		   };
		   } */
		return result;
	    };
	  GByPassOp::GByPassOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth) {

	    };
	    //==================================================================
	    RGB_vector_ptr FrcNROp::getRendering(RGB_vector_ptr source) {
		//int size = source->size();
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGB_ptr rgb255 = (*result)[255];
		STORE_RGBVECTOR("frcNR_0.xls", result);
		if (!bitDepth->is6in6Out()) {
		    //6in6out才啟動以下修正(nb panel即是)
		    foreach(const Channel & ch, *Channel::RGBChannel) {
			//亮位的修正
			if (rgb255->getValue(ch) >= 248.5) {
			    //若使用到248.5以上, 修正讓254才使用到FRC
			    (*result)[255]->setValue(ch, 252);
			    (*result)[254]->setValue(ch, 250);
			    (*result)[253]->setValue(ch, 248);
			    for (int x = 252; x != -1; x--) {
				RGB_ptr thisRGB = (*result)[x];
				RGB_ptr nextRGB = (*result)[x + 1];
				double thisv = thisRGB->getValue(ch);
				double nextv = nextRGB->getValue(ch);
				if (thisv >= nextv) {
				    //若有反轉, 則強制設定差異為0.5
				    thisRGB->setValue(ch, nextv - 2 / 4.);
				} else {
				    break;
				}
			    }
			}
		    }
		    STORE_RGBVECTOR("frcNR_1.xls", result);
		}
		//以下修正則不限定是nb panel
		foreach(const Channel & ch, *Channel::RGBChannel) {
		    //暗位的修正1~30
		    for (int x = 1; x != 31; x++) {
			RGB_ptr rgb = (*result)[x];
			double v = rgb->getValue(ch);
			//只有在v為3 or 1才做修正
			if (v == 12 / 4. || v == 4 / 4.) {
			    double setvalue = (v == 12 / 4.) ? 10 / 4. : 2 / 4.;
			    rgb->setValue(ch, setvalue);
			    RGB_ptr prergb = (*result)[x - 1];
			    double prev = prergb->getValue(ch);
			    if (prev == rgb->getValue(ch)) {
				prergb->setValue(ch, prev - 2 / 4.);
			    }
			    if (prergb->getValue(ch) < 0) {
				prergb->setValue(ch, 0);
			    }
			}

		    }
		}
		STORE_RGBVECTOR("frcNR_2.xls", result);
		return result;
	    };
	  FrcNROp::FrcNROp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth) {
	    };
	    //==================================================================


	    //==================================================================

	    RGB_vector_ptr SetWhiteOp::getRendering(RGB_vector_ptr source) {

		RGB_vector_ptr result = RGBVector::deepClone(source);
		int level = bitDepth->getLevelInTCon();

		if (input10Bit) {
		    double_array rgb255Values(new double[3]);
		    double_array rgb256Values(new double[3]);
		    double_array setrgbValues(new double[3]);

		    RGB_ptr rgb255 = (*result)[level - 2];
		    rgb255->getValues(rgb255Values, MaxValue::Int12Bit);
		    setRGB->getValues(setrgbValues, MaxValue::Int12Bit);
		    double r255 = rgb255Values[0];
		    double g255 = rgb255Values[1];
		    double b255 = rgb255Values[2];
		    double setr255 = setrgbValues[0];
		    double setg255 = setrgbValues[1];
		    double setb255 = setrgbValues[2];
		    rgb256Values[0] =
			Interpolation::linear(255, 255.75, rgb255Values[0], setrgbValues[0], 256);
		    rgb256Values[1] =
			Interpolation::linear(255, 255.75, rgb255Values[1], setrgbValues[1], 256);
		    rgb256Values[2] =
			Interpolation::linear(255, 255.75, rgb255Values[2], setrgbValues[2], 256);
		    rgb256Values[0] = Math::ceil(rgb256Values[0]);
		    rgb256Values[1] = Math::ceil(rgb256Values[1]);
		    rgb256Values[2] = Math::ceil(rgb256Values[2]);

		    if (rgb256Values[0] > 4095 || rgb256Values[1] > 4095 || rgb256Values[2] > 4095) {
 			errorMessage = "10Bit輸入時, 計算出的DG255與DG256, 無法滿足10Bit輸入1023時, DG255.75內插出4080的需求";
			//return nil_RGB_vector_ptr;
		    }

		    RGB_ptr rgb256 = (*result)[level - 1];
		    rgb256->setProcessOverflow(false);
		    rgb256->setValues(rgb256Values, MaxValue::Int12Bit);

		} else {
		    double_array rgbValues(new double[3]);
		    setRGB->getValues(rgbValues, MaxValue::Int12Bit);
		    for (int x = level - 1; x != bitDepth->getLevel(); x++) {
			RGB_ptr rgb = (*result)[x];
			//因為下一行的setValues..會改變到rgbValues裡面的值
			//所以改成每次都要讀出來到rgbValues, 就不會受到影響
			setRGB->getValues(rgbValues, MaxValue::Int12Bit);
			rgb->setValues(rgbValues, MaxValue::Int12Bit);
		    }
		}

		return result;
	    };

	  SetWhiteOp::SetWhiteOp(bptr < BitDepthProcessor > bitDepth, RGB_ptr setRGB):bitDepth(bitDepth),
		setRGB(setRGB), input10Bit(bitDepth->is10BitInput())
	    {

	    };

	    //==================================================================
	    RGB_vector_ptr KeepNativeWhiteSmoothOp::getRendering(RGB_vector_ptr source) {
		//STORE_RGBVECTOR("op-source.xls", source);
		RGB_vector_ptr result = RGBVector::deepClone(source);
		int size = result->size();
		RGB_ptr lastRGB = (*result)[size - 1];
		RGB_ptr beginRGB = (*result)[over];
		double max = bitDepth->getOutputMaxDigitalCount();
		int effectiven = bitDepth->getEffectiveInputLevel();
		//把rgb都推到最大值
		double rGain = max / lastRGB->R;
		double gGain = max / lastRGB->G;
		double bGain = max / lastRGB->B;

		for (int x = over; x != effectiven; x++) {
		    double realrgain = Interpolation::linear(over, effectiven - 1, 1,
							     rGain, x);
		    double realggain = Interpolation::linear(over, effectiven - 1, 1,
							     gGain, x);
		    double realbgain = Interpolation::linear(over, effectiven - 1, 1,
							     bGain, x);
		    RGB_ptr rgb = (*result)[x];
		    rgb->R *= realrgain;
		    rgb->G *= realggain;
		    rgb->B *= realbgain;
		}
		for (int x = effectiven; x != bitDepth->getLevel(); x++) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->setValues(max, max, max);
		}

		//STORE_RGBVECTOR("op-result.xls", result);
		return result;

	    };
	  KeepNativeWhiteSmoothOp::KeepNativeWhiteSmoothOp(bptr < BitDepthProcessor > bitDepth, int over, bool compensationR):bitDepth(bitDepth),
		over(over), compensationR(compensationR)
	    {

	    };


	    //==================================================================



	    double2D_ptr DimDGLutFixOp2::getDeltaxyValues(Component_vector_ptr componentVector) {
		using namespace Indep;
		int size = componentVector->size();
		xyY_vector_ptr xyYVector(new xyY_vector());

		for (int x = 0; x < size; x++) {
		    Component_ptr c = (*componentVector)[x];
		    XYZ_ptr XYZ = c->XYZ;
		    xyY_ptr xyY(new CIExyY(XYZ));
		    xyYVector->push_back(xyY);
		}

		double2D_ptr deltaxyValues(new double2D(size - 1, 2));

		for (int x = 0; x < (size - 1); x++) {
		    xyY_ptr xyY0 = (*xyYVector)[x];
		    xyY_ptr xyY1 = (*xyYVector)[x + 1];
		    double_array xy0Values = xyY0->getxyValues();
		    double_array xy1Values = xyY1->getxyValues();
		    double_array delta = DoubleArray::minus(xy0Values, xy1Values, 2);
		    (*deltaxyValues)[x][0] = delta[0];
		    (*deltaxyValues)[x][1] = delta[1];
		}
		return deltaxyValues;
	    };


	  DimDGLutFixOp2::DimDGLutFixOp2(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold, Component_vector_ptr componentVector, bptr < ChromaticityAdjustEstimatorIF > adjustEstimator):bitDepth(bitDepth),
		dimFixThreshold(dimFixThreshold), componentVector(componentVector),
		adjustEstimator(adjustEstimator) {
	    };



	    RGB_vector_ptr DimDGLutFixOp2::getRendering(RGB_vector_ptr source) {
		//source是0~255, 要先轉成frc
		STORE_RGBVECTOR("6.1_before_fix.xls", source);
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGBVector::changeMaxValue(result, bitDepth->getFRCAbilityBit());
		STORE_RGBVECTOR("6.2_change2FRC.xls", result);

		double2D_ptr deltaxyValues = getDeltaxyValues(componentVector);
		//int size = componentVector->size();

		double threshold = dimFixThreshold;
		bool_array xDefectArray = getDefectArray(deltaxyValues, threshold, 0);
		bool_array yDefectArray = getDefectArray(deltaxyValues, threshold, 1);

		return result;
	    };

	    bool_array DimDGLutFixOp2::getDefectArray(double2D_ptr deltaxyValues, double threshold,
						      int index) {
		int size = deltaxyValues->dim1();
		bool_array defectArray(new bool[size]);
		for (int x = 0; x < size; x++) {
		    defectArray[x] = false;
		}

		for (int x = 0; x < size; x++) {
		    defectArray[x] = (*deltaxyValues)[x][index] < threshold;
		}

		return defectArray;
	    };
	    //==================================================================

	  DeHook2Op::DeHook2Op(bptr < BitDepthProcessor > bitDepth, RGB_ptr _maxBDG, int _maxBDGGrayLevel):bitDepth(bitDepth),
		maxBDG(_maxBDG)
	    {
		this->maxBDGGrayLevel = _maxBDGGrayLevel;
	    };

	    RGB_vector_ptr DeHook2Op::getRendering(RGB_vector_ptr source) {
		int maxCount = bitDepth->getOutputMaxDigitalCount();
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGB_ptr rgb0 = (*result)[this->maxBDGGrayLevel];
		rgb0->R = maxBDG->R;
		rgb0->G = maxBDG->G;
		rgb0->B = maxBDG->B;
		RGB_ptr rgb1 = (*result)[maxCount];

		/*
		   這邊不應該用DG作內插就好, 應該考量亮度是否meet target gamma
		 */
		for (int x = this->maxBDGGrayLevel + 1; x < maxCount; x++) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->R =
			Interpolation::linear(this->maxBDGGrayLevel, maxCount, rgb0->R, rgb1->R, x);
		    rgb->G =
			Interpolation::linear(this->maxBDGGrayLevel, maxCount, rgb0->G, rgb1->G, x);
		    rgb->B =
			Interpolation::linear(this->maxBDGGrayLevel, maxCount, rgb0->B, rgb1->B, x);
		}

		return result;
	    };
	};
    };
};

