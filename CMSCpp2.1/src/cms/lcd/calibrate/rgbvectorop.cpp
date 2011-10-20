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
	    // RBInterpolation
	    //==================================================================
	    RGB_vector_ptr RBInterpolationOp::getRendering(RGB_vector_ptr source) {

		double rInterval = (*source)[under]->R / under;
		double gInterval = (*source)[under]->G / under;
		double bInterval = (*source)[under]->B / under;
		RGB_vector_ptr result = RGBVector::deepClone(source);


		for (int x = 0; x != under; x++) {
		    //做RB interpolation
		    RGB_ptr rgb = (*result)[x];

		    rgb->R = rInterval * x;
		    rgb->G = gInterval * x;
		    rgb->B = bInterval * x;
		}
		return result;
	    };
	  RBInterpolationOp::RBInterpolationOp(double under):under(under) {
	    };
	    //==================================================================

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
		int effectiven = (bitDepth->getEffectiveLevel() - 1);
		for (int x = n; x >= effectiven; x--) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getMaxDigitalCount();
		}
		//==============================================================

		for (int x = effectiven; x != -1; x--) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr nextrgb = (*result)[x - 1];
		    //設定差異
		    double diff = x > 252 ? 10 / 4. : (x > 232 ? 8 / 4. : 6 / 4.);
		    double thisB = rgb->B;
		    double nextB = nextrgb->B;
		    if (thisB > nextB) {
			nextrgb->B = thisB - diff;
		    } else {
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
		int effectiven = bitDepth->getEffectiveLevel();
		for (int x = effectiven; x != bitDepth->getLevel(); x++) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getMaxDigitalCount();
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
		/*if (bitDepth->is10in8Out() || bitDepth->is8in8Out()) {

		   int effectiveLevel = bitDepth->getEffectiveLevel();
		   int level = bitDepth->getLevel();
		   for (int x = 0; x != effectiveLevel; x++) {
		   (*result)[x]->G = x;
		   }
		   for (int x = effectiveLevel; x != level; x++) {
		   (*result)[x]->G = bitDepth->getMaxDigitalCount();
		   }
		   } else */
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
		    int effectiveLevel = bitDepth->getEffectiveLevel();
		    int level = bitDepth->getLevel();
		    for (int x = 0; x != effectiveLevel; x++) {
			(*result)[x]->G = x;
		    }
		    for (int x = effectiveLevel; x != level; x++) {
			(*result)[x]->G = bitDepth->getMaxDigitalCount();
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
	    RGB_vector_ptr KeepNativeWhiteOp::getRendering(RGB_vector_ptr source) {
		//int size = source->size();
		RGB_vector_ptr result = RGBVector::deepClone(source);
		double max = bitDepth->getMaxDigitalCount();
		int effectiven = bitDepth->getEffectiveLevel();

		for (int x = effectiven; x != bitDepth->getLevel(); x++) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->setValues(max, max, max);
		}

		return result;
	    };
	  KeepNativeWhiteOp::KeepNativeWhiteOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {

	    };
	    //==================================================================
	    RGB_vector_ptr KeepNativeWhiteAdvancedOp::getRendering(RGB_vector_ptr source) {
		//STORE_RGBVECTOR("op-source.xls", source);
		RGB_vector_ptr result = RGBVector::deepClone(source);
		int size = result->size();
		RGB_ptr lastRGB = (*result)[size - 1];
		RGB_ptr beginRGB = (*result)[over];
		double max = bitDepth->getMaxDigitalCount();
		int effectiven = bitDepth->getEffectiveLevel();
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
	  KeepNativeWhiteAdvancedOp::KeepNativeWhiteAdvancedOp(bptr < BitDepthProcessor > bitDepth, int over, bool compensationR):bitDepth(bitDepth),
		over(over), compensationR(compensationR)
	    {

	    };
	    //==================================================================

	    int DimDGLutFixOp::getDefectType(bool dxdefect, bool dydefect) {
		if (dxdefect && dydefect) {
		    return Type2;
		} else if (dxdefect) {
		    return Type1x;
		} else if (dydefect) {
		    return Type1y;
		} else {
		    return None;
		}
	    };
	    int_array DimDGLutFixOp::getDefectTypeArray(double2D_ptr deltaxyValues,
							double thresholdx, double thresholdy) {
		int size = deltaxyValues->dim1();
		int_array defectTypeArray(new int[size]);
		for (int x = 0; x < size; x++) {
		    defectTypeArray[x] = None;
		}
		// dx = 1
		// dy = 2
		// dx + dy =3
		for (int x = 1; x < size - 1; x++) {
		    //辨識Type 1x/1y/2
		    bool dx = (*deltaxyValues)[x][0] < thresholdx;
		    bool dy = (*deltaxyValues)[x][1] < thresholdy;
		    defectTypeArray[x] = getDefectType(dx, dy);
		}

		for (int x = 1; x < size - 3; x++) {
		    //辨識Type 12/21/3/4
		    int thisType = defectTypeArray[x];
		    int nextType = defectTypeArray[x + 1];
		    int next2Type = defectTypeArray[x + 2];
		    if ((Type1x == thisType || Type1y == thisType) && Type2 == nextType
			&& None == next2Type) {
			//12
			defectTypeArray[x] = Type12;
			defectTypeArray[x + 1] = None;
		    } else if (Type2 == thisType && (Type1x == nextType || Type1y == nextType)
			       && None == next2Type) {
			//21
			defectTypeArray[x] = Type21;
			defectTypeArray[x + 1] = None;
		    } else if ((thisType == nextType) && (Type1x == thisType || Type1y == thisType)) {
			//3
			defectTypeArray[x] = Type3;
			defectTypeArray[x + 1] = None;
		    } else if (Type2 == thisType && Type2 == nextType && None == next2Type) {
			//4
			defectTypeArray[x] = Type4;
			defectTypeArray[x + 1] = None;
		    }
		}
		return defectTypeArray;
	    };
 
	    double2D_ptr DimDGLutFixOp::getDeltaxyValues(Component_vector_ptr componentVector) {
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

	    RGB_vector_ptr DimDGLutFixOp::getRendering(RGB_vector_ptr source) {
		//source是0~255, 要先轉成frc
		STORE_RGBVECTOR("5.1_before_fix.xls", source);
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGBVector::changeMaxValue(result, bitDepth->getFRCAbilityBit());
		STORE_RGBVECTOR("5.2_change2FRC.xls", result);

		double2D_ptr deltaxyValues = getDeltaxyValues(componentVector);
		int size = componentVector->size();

		double threshold = dimFixThreshold;

		//bool_array defectArray = getDefectArray(deltaxyValues, threshold);
		//bool_array continueDefectArray = getContinueDefectArray(deltaxyValues, threshold);
		int_array defectTypeArray = getDefectTypeArray(deltaxyValues, threshold, threshold);

		for (int x = 1; x < size; x++) {
		    int defect = defectTypeArray[x];
		    int predefect = defectTypeArray[x - 1];
		    int nextdefect = defectTypeArray[x + 1];

		    bool doDefectErase = false;
		    if (Type1x == defect || Type1y == defect) {
			//若是x或y的defect, 相鄰不同type就進行處理
			doDefectErase = defect != predefect && defect != nextdefect;
		    } else if (Type2 == defect) {
			//若是x y皆須進行處理的type, 相鄰必須無defect
			doDefectErase = (None == predefect) && (None == nextdefect);
		    }


		    if (doDefectErase) {
			//確定要消除defect
			int grayLevel = size - x - 1;

			double dx = (*deltaxyValues)[x][0];
			double dy = (*deltaxyValues)[x][1];

			double predx = (*deltaxyValues)[x - 1][0];
			double pre2dx = dx + predx;
			double predy = (*deltaxyValues)[x - 1][1];
			double pre2dy = dy + predy;


			switch (defect) {
			case Type2:{
				//type II
				double_array dxdyofB = adjustEstimator->getdxdy(Channel::B, x);
				double dxofB = -dxdyofB[0];
				double dyofB = -dxdyofB[1];
				double_array xCoordinatorArray =
				    getCoordinatorArray(grayLevel, true);
				double_array yCoordinatorArray =
				    getCoordinatorArray(grayLevel, false);

				int suitAdjustGrayLevel_1 = getSuitAdjustGrayLevel(grayLevel, dxofB,
										   xCoordinatorArray);
				int suitAdjustGrayLevel_2 = getSuitAdjustGrayLevel(grayLevel, dyofB,
										   yCoordinatorArray);


				if (suitAdjustGrayLevel_1 == suitAdjustGrayLevel_2
				    && -1 != suitAdjustGrayLevel_1) {
				    //調整方向相同的case, B就可以解決
				    if (suitAdjustGrayLevel_1 == grayLevel) {
					(*result)[grayLevel]->B -= 1;	//1
				    } else if (suitAdjustGrayLevel_1 == (grayLevel - 1)) {
					(*result)[grayLevel - 1]->B += 1;	//3
				    }
				} else {
				    double_array dxdyR = adjustEstimator->getdxdy(Channel::R, x);
				    double_array dxdyG = adjustEstimator->getdxdy(Channel::G, x);

				    int suitAdjustGrayLevel_3R =
					getSuitAdjustGrayLevel(grayLevel, dxdyR[0],
							       xCoordinatorArray);
				    int suitAdjustGrayLevel_3G =
					getSuitAdjustGrayLevel(grayLevel, dxdyG[1],
							       yCoordinatorArray);

				    if (suitAdjustGrayLevel_3R == grayLevel) {
					(*result)[grayLevel]->R += 1;	//4
				    } else if (suitAdjustGrayLevel_3R == (grayLevel - 1)) {
					(*result)[grayLevel - 1]->R -= 1;	//2
				    }

				    if (suitAdjustGrayLevel_3G == grayLevel) {
					(*result)[grayLevel]->G += 1;	//2
				    } else if (suitAdjustGrayLevel_3G == (grayLevel - 1)) {
					(*result)[grayLevel - 1]->G -= 1;	//4
				    }
				}

				//double xdividey = dy / dx;
				/*bool adjustB = true;  //xdividey > 1.71 && xdividey < 2.28;
				   // dx + dy
				   if (pre2dx < suitGapx) {
				   //太擠
				   if (adjustB) {
				   (*result)[grayLevel - 1]->B += 1;
				   }
				   } else {
				   if (adjustB) {
				   (*result)[grayLevel]->B -= 1;
				   }
				   } */
				break;
			    }
			case Type1x:{
				//type I, dx
				double_array dxdy = adjustEstimator->getdxdy(Channel::R, x);
				double dxOfR = dxdy[0];
				double_array coordinatorArray =
				    getCoordinatorArray(grayLevel, true);
				int suitAdjustGrayLevel =
				    getSuitAdjustGrayLevel(grayLevel, dxOfR, coordinatorArray);

				if (suitAdjustGrayLevel == grayLevel) {
				    (*result)[grayLevel]->R += 1;
				} else if (suitAdjustGrayLevel == (grayLevel - 1)) {
				    (*result)[grayLevel - 1]->R -= 1;
				} else if (-1 == suitAdjustGrayLevel) {
				    //沒輒=.=
				}
				break;
			    }
			case Type1y:{
				//type I, dy
				double_array dxdy = adjustEstimator->getdxdy(Channel::G, x);
				double dyOfG = dxdy[1];
				double_array coordinatorArray =
				    getCoordinatorArray(grayLevel, false);
				int suitAdjustGrayLevel =
				    getSuitAdjustGrayLevel(grayLevel, dyOfG, coordinatorArray);

				if (suitAdjustGrayLevel == grayLevel) {
				    (*result)[grayLevel]->G += 1;
				} else if (suitAdjustGrayLevel == (grayLevel - 1)) {
				    (*result)[grayLevel - 1]->G -= 1;
				} else if (-1 == suitAdjustGrayLevel) {
				    //沒輒=.=
				}
				break;
			    }
			}



		    }
		}
		STORE_RGBVECTOR("5.3_afterFix.xls", result);
		return result;
	    };

	    int DimDGLutFixOp::getSuitAdjustGrayLevel(int middleGrayLevel, double delta,
						      double_array coordinatorArray) {
		double_array case1 = DoubleArray::arraycopy(coordinatorArray, 3);
		case1[1] += delta;

		double_array case2 = DoubleArray::arraycopy(coordinatorArray, 3);
		case2[2] -= delta;

		double c10 = case1[0];
		double c11 = case1[1];
		double c12 = case1[2];
		double c20 = case2[0];
		double c21 = case2[1];
		double c22 = case2[2];

		if (isSuitGap(case1)) {
		    return middleGrayLevel;
		} else if (isSuitGap(case2)) {
		    return middleGrayLevel - 1;
		} else {
		    return -1;
		}
	    };

	    /*
	       coordinatorArray為遞減的 N -> N-1 -> N-2
	     */
	    bool DimDGLutFixOp::isSuitGap(double_array coordinatorArray) {
		double x0 = coordinatorArray[0];
		double x1 = coordinatorArray[1];
		double x2 = coordinatorArray[2];
		bool increase = x0 > x1 && x1 > x2;
		//儘管可以符合suit gap很令人開心..但這卻很難
		/*bool x01gapOk = (x0 - x1) > suitGapx;
		   bool x12gapOk = (x1 - x2) > suitGapy; */
		return increase;
	    };
	    double_array DimDGLutFixOp::getCoordinatorArray(int grayLevel, bool getCoordinatorX) {
		int size = componentVector->size();
		int x = size - grayLevel - 1;
		Component_ptr p0 = (*componentVector)[x - 1];	//亮的
		Component_ptr p1 = (*componentVector)[x];
		Component_ptr p2 = (*componentVector)[x + 1];
		double_array p0xyValues = p0->XYZ->getxyValues();
		double_array p1xyValues = p1->XYZ->getxyValues();
		double_array p2xyValues = p2->XYZ->getxyValues();
		double_array coordinatorArray(new double[3]);

		int xyindex = getCoordinatorX ? 0 : 1;
		coordinatorArray[0] = p0xyValues[xyindex];
		coordinatorArray[1] = p1xyValues[xyindex];
		coordinatorArray[2] = p2xyValues[xyindex];
		return coordinatorArray;
	    };
 
	  DimDGLutFixOp::DimDGLutFixOp(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold, Component_vector_ptr componentVector, bptr < ChromaticityAdjustEstimatorIF > adjustEstimator):bitDepth
		(bitDepth), dimFixThreshold(dimFixThreshold),
		componentVector(componentVector), adjustEstimator(adjustEstimator) {
	    };
	    //==================================================================
	    DimDGLutFixOp2::DimDGLutFixOp2(bptr < BitDepthProcessor > bitDepth,
					   double dimFixThreshold,
					   Component_vector_ptr componentVector,
					   bptr < ChromaticityAdjustEstimatorIF >
					   adjustEstimator):DimDGLutFixOp(bitDepth, dimFixThreshold,
									  componentVector,
									  adjustEstimator) {
	    };


	    RGB_vector_ptr DimDGLutFixOp2::getRendering(RGB_vector_ptr source) {
		//source是0~255, 要先轉成frc
		STORE_RGBVECTOR("5.1_before_fix.xls", source);
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGBVector::changeMaxValue(result, bitDepth->getFRCAbilityBit());
		STORE_RGBVECTOR("5.2_change2FRC.xls", result);

		double2D_ptr deltaxyValues = getDeltaxyValues(componentVector);
		int size = componentVector->size();

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
	};
    };
};

