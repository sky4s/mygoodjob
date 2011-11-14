#include <includeall.h>
#pragma hdrstop
#include "dg.h"


//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::colorformat;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::util;
	    using namespace cms::lcd::calibrate;
	    //==================================================================
	    // DGLutGenerator
	    //==================================================================
	    /*
	       將正規化的gamma curve, 轉換為絕對的亮度curve
	     */
	    double_vector_ptr DGLutGenerator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve) {
		return getLuminanceGammaCurve(normalGammaCurve, maxLuminance, minLuminance);
	    };
	    double_vector_ptr DGLutGenerator::
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
	       計算可用的最大intensity
	     */
	    double DGLutGenerator::getMaximumIntensity() {
		int maxindex = 0;
		//找到最亮量測點
		Component_ptr maxcomponent = (*componentVector)[maxindex];
		RGB_ptr maxintensity = maxcomponent->intensity;
		//最小值的channel
		const Channel & minchannel = maxintensity->getMinChannel();
		//以最小值得channel的intensity為最大的intensity
		double maxvalue = maxintensity->getValue(minchannel);
		return maxvalue;
	    };
	    /*
	       DGLutGenerator擔任產出DG Code的重責大任
	       1. 首先接手ComponentFetcher產出的rgb,對應的componet,亮度
	       2. 藉由regression找出componet與亮度的關係
	       1/2由init產出

	       3. 由目標gamma curve經步驟二找到對應的component
	       4. 由compomenet對應出DG Code, DG Code產出
	       3/4由produce產出
	     */
	    void DGLutGenerator::
		initComponent(Component_vector_ptr componentVector,
			      bool keepTargetWhiteMaxLuminance) {
		//==============================================================
		// 計算a/c/d
		//==============================================================
		componentRelation =
		    bptr < ComponentRelationIF > (new ComponentLinearRelation(componentVector));
		//==============================================================

		//==============================================================
		// 產生RGB LUT
		//==============================================================
		lut = bptr < ComponentLUT > (new ComponentLUT(componentVector));
		//==============================================================

		double maxintensity = Math::roundTo(getMaximumIntensity());
		if (!keepTargetWhiteMaxLuminance) {
		    maxintensity = (maxintensity > 100) ? 100 : maxintensity;
		}

		maxLuminance =
		    componentRelation->getLuminance(maxintensity, maxintensity, maxintensity);
		int size = componentVector->size();
		minLuminance = (*componentVector)[size - 1]->XYZ->Y;
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector):componentVector
		(componentVector), mode(Component),
		keepMaxLuminance(KeepMaxLuminance::TargetWhite) {
		initComponent(componentVector, keepMaxLuminance == KeepMaxLuminance::TargetWhite);
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, KeepMaxLuminance keepMaxLuminance):componentVector
		(componentVector),
		mode(Component), keepMaxLuminance(keepMaxLuminance) {
		initComponent(componentVector, keepMaxLuminance == KeepMaxLuminance::TargetWhite);
	    };
	  DGLutGenerator::DGLutGenerator(double_vector_ptr luminanceVector):luminanceVector(luminanceVector), mode(WLumi)
	    {
		maxLuminance = (*luminanceVector)[0];
		int size = luminanceVector->size();
		minLuminance = (*luminanceVector)[size - 1];
		double_vector_ptr key(new double_vector(size));
		for (int x = 0; x != size; x++) {
		    (*key)[x] = size - x - 1;
		}
		key = DoubleArray::getReverse(key);
		double_vector_ptr value = DoubleArray::getReverse(luminanceVector);

		wlut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(key, value));
	    };

	    RGB_ptr DGLutGenerator::getDGCode(double rIntensity,
					      double gIntensity,
					      double bIntensity, bool correctInRange) {
		if (true == correctInRange) {
		    rIntensity = lut->correctIntensityInRange(Channel::R, rIntensity);
		    gIntensity = lut->correctIntensityInRange(Channel::G, gIntensity);
		    bIntensity = lut->correctIntensityInRange(Channel::B, bIntensity);
		}

		double r = lut->getCode(Channel::R, rIntensity);
		double g = lut->getCode(Channel::G, gIntensity);
		double b = lut->getCode(Channel::B, bIntensity);

		RGB_ptr rgb(new RGBColor(r, g, b));
		return rgb;
	    };

	    RGB_ptr DGLutGenerator::
		getDGCode(double rIntensity, double gIntensity, double bIntensity) {
		return getDGCode(rIntensity, gIntensity, bIntensity, true);
	    }

	    RGB_vector_ptr DGLutGenerator::getCCTDGLut(RGBGamma_ptr rgbIntensityCurve) {
		if (mode == WLumi || mode == RGBLumi) {
		    throw UnsupportedOperationException("DGLutGenerator is in luminanceMode.");
		}

		using namespace Dep;
		double_vector_ptr rIntensityCurve = rgbIntensityCurve->r;
		double_vector_ptr gIntensityCurve = rgbIntensityCurve->g;
		double_vector_ptr bIntensityCurve = rgbIntensityCurve->b;

		int size = rIntensityCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));
		//將code 0強制設定為0
		(*dglut)[0] = RGB_ptr(new RGBColor(0, 0, 0));

		for (int x = size - 1; x != 0; x--) {
		    RGB_ptr rgb = getDGCode((*rIntensityCurve)[x],
					    (*gIntensityCurve)[x],
					    (*bIntensityCurve)[x]);
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };

	    RGB_vector_ptr DGLutGenerator::getGammaDGLut(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve = getLuminanceGammaCurve(normalGammaCurve);
		int size = luminanceGammaCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));

		//for (int x = 0; x != size; x++) {
		for (int x = size - 1; x != -1; x--) {
		    double luminance = (*luminanceGammaCurve)[x];
		    RGB_ptr rgb;
		    switch (mode) {
		    case RGBLumi:
			throw java::lang::UnsupportedOperationException();
		    case Component:
			rgb = lut->getCode(luminance);
			break;
		    case WLumi:
			luminance = wlut->correctValueInRange(luminance);
			double key = wlut->getKey(luminance);
			rgb = RGB_ptr(new RGBColor(key, key, key));
			break;

		    }
		    (*dglut)[x] = rgb;
		}

		return dglut;
	    };

	    /*
	       normalGammaCurve轉LuminanceGammaCurve再轉intensity
	     */
	    RGBGamma_ptr DGLutGenerator::getRGBGamma(double_vector_ptr normalGammaCurve) {
		//gamma curve轉luminance curve
		double_vector_ptr luminanceGammaCurve = getLuminanceGammaCurve(normalGammaCurve);
		STORE_DOUBLE_VECTOR("0_lumicurve.xls", luminanceGammaCurve);
		int size = luminanceGammaCurve->size();
		double_vector_ptr rIntenisty(new double_vector(size));
		double_vector_ptr gIntenisty(new double_vector(size));
		double_vector_ptr bIntenisty(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    double luminance = (*luminanceGammaCurve)[x];
		    //luminance curve轉intensity
		    double intensity = componentRelation->getIntensity(luminance);
		    (*rIntenisty)[x] = intensity;
		    (*gIntenisty)[x] = intensity;
		    (*bIntenisty)[x] = intensity;
		}

		RGBGamma_ptr rgbgamma(new
				      RGBGamma(rIntenisty, gIntenisty, bIntenisty, 100, Intensity));

		return rgbgamma;
	    };
	    double DGLutGenerator::getMaxBIntensity() {
		return lut->getMaxBIntensity();
	    };

	    /*
	       取出 rgbVector中, 所有ch channel下對應的intensity
	     */
	    double_vector_ptr DGLutGenerator::
		getIntensityVector(const Dep::Channel & ch, RGB_vector_ptr rgbVector) {
		double_vector_ptr vector(new double_vector());
		foreach(RGB_ptr rgb, *rgbVector) {
		    double v = rgb->getValue(ch);
		    double intensity = lut->getIntensity(ch, v);
		    vector->push_back(intensity);
		}
		return vector;
	    };

	    RGB_ptr DGLutGenerator::getIntensity(RGB_ptr dgcode) {
		using namespace Dep;
		//double_array intensity(new double[3]);
		RGB_ptr intensity(new RGBColor());
		intensity->R = lut->getIntensity(Channel::R, dgcode->R);
		intensity->G = lut->getIntensity(Channel::G, dgcode->G);
		intensity->B = lut->getIntensity(Channel::B, dgcode->B);
		return intensity;
	    };
	    //==================================================================
	};
    };
};

