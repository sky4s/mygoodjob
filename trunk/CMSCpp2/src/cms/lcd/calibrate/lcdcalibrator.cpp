#include "lcdcalibrator.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/measure/MeterMeasurement.h>
#include <cms/measure/analyzer.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <math/doublearray.h>
#include <math/interpolation.h>
#include "rgbvectorop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace java::lang;
	    //==================================================================
	    // Composition
	    //==================================================================
	     Composition::Composition(RGB_ptr rgb,
				      RGB_ptr component):rgb(rgb),
		component(component) {

	    };
	     Composition::Composition(RGB_ptr rgb,
				      RGB_ptr component,
				      XYZ_ptr XYZ):rgb(rgb),
		component(component), XYZ(XYZ) {

	    };
	    //==================================================================


	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	    /*ComponentFetcher::ComponentFetcher(bptr < MeterMeasurement >
	       mm,
	       bptr <
	       ComponentAnalyzerIF >
	       analyzer):mm(mm),
	       analyzer(analyzer) {

	       }; */
	     ComponentFetcher::ComponentFetcher(bptr <
						ComponentAnalyzerIF >
						analyzer):analyzer
		(analyzer) {

	    };

	    Composition_vector_ptr ComponentFetcher::
		fetchComposition(int start, int end, int step) {

		Composition_vector_ptr result(new Composition_vector());
		for (int x = start; x >= end; x -= step) {
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    RGB_ptr component = analyzer->getComponent(rgb);
		    XYZ_ptr XYZ = analyzer->getCIEXYZ();
		    Composition_ptr composition(new
						Composition(rgb,
							    component,
							    XYZ));
		    result->push_back(composition);
		};
		return result;
	    };
	    //==================================================================

	    //==================================================================
	    // DGCodeProducer
	    //==================================================================
	    /*
	       DGCodeProducer擔任產出DG Code的重責大任
	       1. 首先接手ComponentFetcher產出的rgb,對應的componet,亮度
	       2. 藉由regression找出componet與亮度的關係
	       1/2由init產出

	       3. 由目標gamma curve經步驟二找到對應的component
	       4. 由compomenet對應出DG Code, DG Code產出
	       3/4由produce產出

	     */
	    void DGCodeProducer::init() {
		//==============================================================
		// 建立回歸資料
		//==============================================================
		int size = compositionVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));
		double_vector_ptr key(new double_vector(size));
		double_vector_ptr rValue(new double_vector(size));
		double_vector_ptr gValue(new double_vector(size));
		double_vector_ptr bValue(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    Composition_ptr composition = (*compositionVector)[x];
		    double Y = composition->XYZ->Y;
		    RGB_ptr component = composition->component;

		    (*input)[x][0] = component->R;
		    (*input)[x][1] = component->G;
		    (*input)[x][2] = component->B;
		    (*output)[x][0] = Y;

		    (*key)[x] = composition->rgb->getValue(Channel::W);
		    (*rValue)[x] = component->R;
		    (*gValue)[x] = component->G;
		    (*bValue)[x] = component->B;
		}
		//==============================================================

		//==============================================================
		// 計算c/d
		//==============================================================
		regression.reset(new PolynomialRegression(input, output,
							  Polynomial::
							  COEF_3::BY_3C));
		regression->regress();
		coefs = regression->getCoefs();
		c = 1 / ((*coefs)[0][1] + (*coefs)[0][2] + (*coefs)[0][3]);
		d = -(*coefs)[0][0] / ((*coefs)[0][1] + (*coefs)[0][2] +
				       (*coefs)[0][3]);
		//==============================================================

		minLuminance = (*output)[0][0];
		maxLuminance = (*output)[size - 1][0];

		//==============================================================
		// 產生RGB LUT
		//==============================================================
		rLut.reset(new Interpolation1DLUT(key, rValue));
		gLut.reset(new Interpolation1DLUT(key, gValue));
		bLut.reset(new Interpolation1DLUT(key, bValue));
		//==============================================================
	    };
	    double DGCodeProducer::getComponent(double luminance) {
		return c * luminance + d;
	    };
	    double_vector_ptr DGCodeProducer::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve)
	    {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new
						      double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    double lumi =
			differ * (*normalGammaCurve)[x] + minLuminance;
		    (*luminanceGammaCurve)[x] = lumi;
		}
		return luminanceGammaCurve;
	    };
	  DGCodeProducer::DGCodeProducer(Composition_vector_ptr compositionVector):compositionVector
		(compositionVector)
	    {
		init();
	    };
	    RGB_vector_ptr DGCodeProducer::
		produce(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		int size = luminanceGammaCurve->size();
		RGB_vector_ptr dgcode(new RGB_vector(size));

		for (int x = 0; x != size; x++) {
		    double lumi = (*luminanceGammaCurve)[x];
		    double component = getComponent(lumi);
		    double r = rLut->getKey(component);
		    double g = gLut->getKey(component);
		    double b = bLut->getKey(component);
		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dgcode)[x] = rgb;
		}
		return dgcode;
	    };
	    //==================================================================



	    //==================================================================
	    // LCDCalibrator
	    //==================================================================
	    double_array LCDCalibrator::getGammaCurve(double gamma, int n) {
		double_array result(new double[n]);
		for (int x = 0; x < n; x++) {
		    double normal = static_cast < double >(x) / (n - 1);
		    double v = java::lang::Math::pow(normal, gamma);
		    result[x] = v;
		}
		return result;
	    };
	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < n; x++) {
		    double normal = static_cast < double >(x) / (n - 1);
		    double v = java::lang::Math::pow(normal, gamma);
		    (*result)[x] = v;
		}
		return result;
	    };
	    void LCDCalibrator::setP1P2(double p1, double p2) {
		this->p1 = p1;
		this->p2 = p2;
		this->p1p2 = true;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		this->p1p2 = false;
		this->rbInterpUnder = under;
	    };
	    void LCDCalibrator::setGamma(double
					 gamma, int n) {
		setGammaCurve(getGammaCurveVector(gamma, n));
	    };
	    void LCDCalibrator::
		setGammaCurve(double_array gammaCurve, int n) {
		/* TODO : setGammaCurve */
		//this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::setGByPass(bool byPass) {
		this->gByPass = byPass;
	    };
	    void LCDCalibrator::setBIntensityGain(double gain) {
		this->bIntensityGain = gain;
	    };
	    void LCDCalibrator::setBMax(bool bMax) {
		this->bMax = bMax;
	    };
	    void LCDCalibrator::setGamma256(bool gamma256) {
		this->gamma256 = gamma256;
	    };
	    void LCDCalibrator::setAvoidFRCNoise(bool avoid) {
		this->avoidFRCNoise = avoid;
	    };
	    void LCDCalibrator::setBitDepth(const
					    BitDepth & in, const
					    BitDepth & lut, const
					    BitDepth & out) {
		this->in = in;
		this->lut = lut;
		this->out = out;
	    };
	    RGB_vector_ptr LCDCalibrator::
		getDGCode(int start, int end, int step) {
		if (null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}

		if (bIntensityGain != 1.0) {
		    //重新產生目標gamma curve

		};

		if (p1p2) {
		    //op.reset(new P1P2Op(p1, p2));
		};

		//量測start->end得到的coponent/Y
		Composition_vector_ptr compositionVector =
		    fetcher->fetchComposition(start, end, step);
		//產生producer
		producer.reset(new DGCodeProducer(compositionVector));
		//從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		RGB_vector_ptr dgcode = producer->produce(gammaCurve);

		bptr_ < DGCodeOp > op;
		if (!p1p2) {
		    op.reset(new RBInterpolationOp(rbInterpUnder));
		}
		op->setSource(dgcode);

		if (bMax) {
		    bptr < DGCodeOp > bmax(new BMaxOp());
		    op->addOp(bmax);
		}
		if (gByPass) {
		    bptr < DGCodeOp > gbypass(new GByPassOp());
		    op->addOp(gbypass);
		}
		if (avoidFRCNoise) {

		}
		if (gamma256) {

		}
		RGB_vector_ptr result = op->createInstance();
		return result;
	    };
	  LCDCalibrator::LCDCalibrator(bptr < ComponentAnalyzerIF > analyzer):analyzer(analyzer)
	    {
		fetcher.reset(new ComponentFetcher(analyzer));
	    };
	    //==================================================================
	};
    };
};

