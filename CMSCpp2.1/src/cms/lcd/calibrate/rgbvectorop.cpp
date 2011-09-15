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
	    bool_array DimDGLutFixOp::getDefectArray(double2D_ptr deltaxyValues, double threshold) {
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
	    int DimDGLutFixOp::getDefectType(bool dxdefect, bool dydefect) {
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
	    int_array DimDGLutFixOp::getDefectTypeArray(double2D_ptr deltaxyValues,
							double thresholdx, double thresholdy) {
		int size = deltaxyValues->dim1();
		int_array defectTypeArray(new int[size]);
		for (int x = 0; x < size; x++) {
		    defectTypeArray[x] = -1;
		}
		// dx = 1
		// dy = 2
		// dx + dy =3
		for (int x = 1; x < size - 1; x++) {
		    bool dx = (*deltaxyValues)[x][0] < thresholdx;
		    bool dy = (*deltaxyValues)[x][1] < thresholdy;
		    defectTypeArray[x] = getDefectType(dx, dy);
		}

		return defectTypeArray;
	    };
	    bool_array DimDGLutFixOp::getContinueDefectArray(double2D_ptr deltaxyValues,
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
	    }

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
		int size = deltaxyValues->dim1();

		double threshold = dimFixThreshold;

		//bool_array defectArray = getDefectArray(deltaxyValues, threshold);
		//bool_array continueDefectArray = getContinueDefectArray(deltaxyValues, threshold);
		int_array defectTypeArray = getDefectTypeArray(deltaxyValues, threshold, threshold);

		for (int x = 1; x < size; x++) {
		    int defect = defectTypeArray[x];
		    int predefect = defectTypeArray[x - 1];
		    int nextdefect = defectTypeArray[x + 1];

		    bool doDefectErase = false;
		    if (1 == defect || 2 == defect) {
			//若是x或y的defect, 相鄰不同type就進行處理
			doDefectErase = defect != predefect && defect != nextdefect;
		    } else if (3 == defect) {
			//若是x y皆須進行處理的type, 相鄰必須無defect
			doDefectErase = (-1 == predefect) && (-1 == nextdefect);
		    }


		    if (doDefectErase) {
			//確定要消除defect
			int grayLevel = size - x;
			double dx = (*deltaxyValues)[x][0];
			double dy = (*deltaxyValues)[x][1];

			double predx = (*deltaxyValues)[x - 1][0];
			double pre2dx = dx + predx;
			double predy = (*deltaxyValues)[x - 1][1];
			double pre2dy = dy + predy;


			switch (defect) {
			case 3:{
				double_array dxdy = adjustEstimator->getdxdy(Channel::B, grayLevel);
				double xdividey = dy / dx;
				bool adjustB = true;	//xdividey > 1.71 && xdividey < 2.28;
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
				}
				break;
			    }
			case 1:{
				double_array dxdy = adjustEstimator->getdxdy(Channel::R, grayLevel);
				//dx <0
				if (pre2dx < suitGapx /*|| pre2dx < dxdy[0] */ ) {
				    //太擠
				    (*result)[grayLevel - 1]->R -= 1;
				} else {
				    (*result)[grayLevel]->R += 1;
				}
				break;
			    }
			case 2:{
				double_array dxdy = adjustEstimator->getdxdy(Channel::G, grayLevel);
				//dy <0
				if (pre2dy < suitGapy /*|| pre2dy < dxdy[1] */ ) {
				    //太擠
				    (*result)[grayLevel - 1]->G -= 1;
				} else {
				    (*result)[grayLevel]->G += 1;
				}
				break;
			    }
			}



		    }
		}
		STORE_RGBVECTOR("5.3_afterFix.xls", result);
		return result;


	    };
	    /*DimDGLutFixOp::DimDGLutFixOp(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold, double suitGap, Component_vector_ptr componentVector):bitDepth(bitDepth), dimFixThreshold(dimFixThreshold), suitGap(suitGap),
	       componentVector(componentVector)
	       {
	       }; */
	  DimDGLutFixOp::DimDGLutFixOp(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold, Component_vector_ptr componentVector, bptr < ChromaticityAdjustEstimator > adjustEstimator):bitDepth(bitDepth), dimFixThreshold(dimFixThreshold), componentVector(componentVector),
		suitGapx(0.0004), suitGapy(0.0008),
		adjustEstimator(adjustEstimator) {
	    };
	    //==================================================================
	};
    };
};

