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
		return LCDCalibrator::getLuminanceGammaCurve(normalGammaCurve,
							     maxLuminance, minLuminance);
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
		initComponent(Component_vector_ptr componentVector, bool keepTargetMaxLuminance) {
		//==============================================================
		// 計算a/c/d
		//==============================================================
		componentRelation =
		    bptr < ComponentLinearRelation > (new ComponentLinearRelation(componentVector));
		//==============================================================

		//==============================================================
		// 產生RGB LUT
		//==============================================================
		lut = bptr < ComponentLUT > (new ComponentLUT(componentVector));
		//==============================================================
		//找到最大的intensity, 然後去推算對應的luminance;
		//基於舊方法中, 建立intensity和luminance的關係所得
		double maxintensity = Math::roundTo(getMaximumIntensity());
		if (!keepTargetMaxLuminance) {
		    maxintensity = (maxintensity > 100) ? 100 : maxintensity;
		}
		//此處的作法比較適合target white = native white的case//若遇到target white不是 native white....須從外部指定maxLuminance//內部可能無法推算max luminace....
		    maxLuminance =
		 componentRelation->getLuminance(maxintensity, maxintensity, maxintensity);
		int size = componentVector->size();
		minLuminance = (*componentVector)[size - 1]->XYZ->Y;
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector):componentVector
		(componentVector), mode(Component),
		keepMaxLuminance(KeepMaxLuminance::TargetLuminance) {

		init(componentVector, false);
	    };

	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, KeepMaxLuminance keepMaxLuminance):componentVector
		(componentVector),
		mode(Component), keepMaxLuminance(keepMaxLuminance) {
		initComponent(componentVector,
			      keepMaxLuminance == KeepMaxLuminance::TargetLuminance);
	    };
	    void DGLutGenerator::init(Component_vector_ptr componentVector, bool luminanceMode) {
		if (luminanceMode) {
		    initLuminance(componentVector);
		} else {
		    keepMaxLuminance = KeepMaxLuminance::TargetLuminance;
		    initComponent(componentVector,
				  keepMaxLuminance == KeepMaxLuminance::TargetLuminance);
		}
	    };
	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, bool luminanceMode):componentVector
		(componentVector),
		mode(luminanceMode ? WLumi : Component) {
		init(componentVector, luminanceMode);

	    };

	    void DGLutGenerator::initLuminance(Component_vector_ptr componentVector) {
		maxLuminance = (*componentVector)[0]->XYZ->Y;
		int size = componentVector->size();
		minLuminance = (*componentVector)[size - 1]->XYZ->Y;
		double_vector_ptr keys(new double_vector());
		double_vector_ptr wvalues(new double_vector());
		double_vector_ptr rvalues(new double_vector());
		double_vector_ptr gvalues(new double_vector());
		double_vector_ptr bvalues(new double_vector());

		for (int x = 0; x != size; x++) {
		    Component_ptr c = (*componentVector)[x];
		    RGB_ptr rgb = c->rgb;
		    XYZ_ptr XYZ = c->XYZ;
		    double w = rgb->getValue(Dep::Channel::W);
		    keys->push_back(w);
		    wvalues->push_back(XYZ->Y);

		    RGB_ptr intensity = c->intensity;
		    rvalues->push_back(intensity->R);
		    gvalues->push_back(intensity->R);
		    bvalues->push_back(intensity->R);
		}
		keys = DoubleArray::getReverse(keys);
		wvalues = DoubleArray::getReverse(wvalues);
		rvalues = DoubleArray::getReverse(rvalues);
		gvalues = DoubleArray::getReverse(gvalues);
		bvalues = DoubleArray::getReverse(bvalues);

		wlut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(keys, wvalues));
		rlut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(keys, rvalues));
		glut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(keys, gvalues));
		blut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(keys, bvalues));
	    };

	    RGB_ptr DGLutGenerator::getIntensity(RGB_ptr dg) {
		return getIntensity(dg, true);
	    }
	    RGB_ptr DGLutGenerator::getIntensity(RGB_ptr dg, bool correctInRange) {
		double r = dg->R;
		double g = dg->G;
		double b = dg->B;
		if (true == correctInRange) {
		    r = lut->correctCodeInRange(Channel::R, r);
		    rCorrect = lut->hasCorrectedInRange(Channel::R);
		    g = lut->correctCodeInRange(Channel::G, g);
		    gCorrect = lut->hasCorrectedInRange(Channel::G);
		    b = lut->correctCodeInRange(Channel::B, b);
		    bCorrect = lut->hasCorrectedInRange(Channel::B);
		}

		double rIntensity = lut->getIntensity(Channel::R, r);
		double gIntensity = lut->getIntensity(Channel::G, g);
		double bIntensity = lut->getIntensity(Channel::B, b);
		RGB_ptr intensity(new RGBColor(rIntensity, gIntensity, bIntensity));
		return intensity;
	    };

	    RGB_ptr DGLutGenerator::getDGCode(double rIntensity,
					      double gIntensity,
					      double bIntensity, bool correctInRange) {

		if (true == correctInRange) {
		    rIntensity = lut->correctIntensityInRange(Channel::R, rIntensity);
		    rCorrect = lut->hasCorrectedInRange(Channel::R);
		    gIntensity = lut->correctIntensityInRange(Channel::G, gIntensity);
		    gCorrect = lut->hasCorrectedInRange(Channel::G);
		    bIntensity = lut->correctIntensityInRange(Channel::B, bIntensity);
		    bCorrect = lut->hasCorrectedInRange(Channel::B);
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

	    bool_array DGLutGenerator::isCorrectIntensityInRange() {
		bool_array result(new bool[3]);
		result[0] = rCorrect;
		result[1] = gCorrect;
		result[2] = bCorrect;
		return result;
	    };



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
		RGB_ptr rgb0 = (*componentVector)[0]->rgb;

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
			rgb = RGB_ptr(new RGBColor(key, key, key, rgb0->getMaxValue()));
			break;

		    }
		    (*dglut)[x] = rgb;
		}

		return dglut;
	    };

	    RGB_vector_ptr DGLutGenerator::getGammaDGLut(RGBGamma_ptr rgbNormalGammaCurve) {

		LCDCalibrator::getLuminanceGammaCurve(rgbNormalGammaCurve->r,
						      maxLuminance, minLuminance);
                                                               throw java::lang::UnsupportedOperationException();
	    };

	    RGB_vector_ptr getFineGammaDGLut(RGB_vector_ptr rgbVector,
					     double_vector_ptr normalGammaCurve) {
		//double_vector_ptr luminanceGammaCurve = getLuminanceGammaCurve(normalGammaCurve);
                            throw java::lang::UnsupportedOperationException();
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

	    void DGLutGenerator::setInverseSearch(bool inverse) {
		lut->setInverseSearch(inverse);
	    };
	    //==================================================================
	};
    };
};

