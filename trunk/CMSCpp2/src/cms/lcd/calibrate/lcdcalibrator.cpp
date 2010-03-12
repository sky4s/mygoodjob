#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

#include <math/doublearray.h>
#include <math/interpolation.h>
#include "rgbvectorop.h"
#include "rgbgamma.h"
#include <gui/UIConfig.h>



#ifdef _DEBUG
#include <cms/util/rgbarray.h>
#define _ std::string
#define debug_dir _(DEBUG_DIR)

#define STORE_COMPOSITION( filename , result ) \
ComponentFetcher::storeToExcel(debug_dir + _(filename), result);
#define STORE_RGBGAMMA( filename , result ) \
cms::lcd::calibrate::RGBGamma::storeToExcel(debug_dir + _(filename), result);
#define STORE_RGBVECTOR( filename , result ) \
RGBVector::storeToExcel(debug_dir + _(filename), result);

#else
#define STORE_COMPOSITION( filename , result )
#define STORE_RGBGAMMA( filename , result )
#define STORE_RGBVECTOR( filename , result )
#endif

namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::colorformat;
	    using namespace cms::util;
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
	     Composition::Composition(RGB_ptr rgb,
				      RGB_ptr component,
				      XYZ_ptr XYZ, RGB_ptr gamma):rgb(rgb),
		component(component), XYZ(XYZ), gamma(gamma) {

	    };
	    //==================================================================


	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	  ComponentFetcher::ComponentFetcher(bptr < ComponentAnalyzerIF > analyzer):analyzer
		(analyzer)
	    {

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
		    if (true == stop) {
			break;
		    }
		};
		return result;
	    };
	    void ComponentFetcher::setStop(bool stop) {
		this->stop = stop;
	    };
	    void ComponentFetcher::storeToExcel(const string & filename,
						Composition_vector_ptr
						compositionVector) {

		int n = compositionVector->size();
		ExcelFileDB::deleteExist(filename);
		DGLutFile dglut(filename, n);
		dglut.setRawData(compositionVector);
	    };
	    //==================================================================

	    //==================================================================
	    // DGLutGenerator
	    //==================================================================
	    /*
	       DGLutGenerator擔任產出DG Code的重責大任
	       1. 首先接手ComponentFetcher產出的rgb,對應的componet,亮度
	       2. 藉由regression找出componet與亮度的關係
	       1/2由init產出

	       3. 由目標gamma curve經步驟二找到對應的component
	       4. 由compomenet對應出DG Code, DG Code產出
	       3/4由produce產出

	     */
	    void DGLutGenerator::init() {
		//==============================================================
		// 建立回歸資料
		//==============================================================
		int size = compositionVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));
		double_vector_ptr keys(new double_vector(size));
		double_vector_ptr rValues(new double_vector(size));
		double_vector_ptr gValues(new double_vector(size));
		double_vector_ptr bValues(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    Composition_ptr composition = (*compositionVector)[x];
		    double Y = composition->XYZ->Y;
		    RGB_ptr component = composition->component;

		    (*input)[x][0] = component->R;
		    (*input)[x][1] = component->G;
		    (*input)[x][2] = component->B;
		    (*output)[x][0] = Y;

		    (*keys)[x] = composition->rgb->getValue(Channel::W);
		    (*rValues)[x] = component->R;
		    (*gValues)[x] = component->G;
		    (*bValues)[x] = component->B;
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

		maxLuminance = (*output)[0][0];
		minLuminance = (*output)[size - 1][0];

		//==============================================================
		// 產生RGB LUT
		//==============================================================
		keys = getReverse(keys);
		rValues = getReverse(rValues);
		gValues = getReverse(gValues);
		bValues = getReverse(bValues);
		rLut.reset(new Interpolation1DLUT(keys, rValues));
		gLut.reset(new Interpolation1DLUT(keys, gValues));
		bLut.reset(new Interpolation1DLUT(keys, bValues));
		//==============================================================
	    };
	    double DGLutGenerator::getComponent(double luminance) {
		return c * luminance + d;
	    };
	    double_vector_ptr DGLutGenerator::
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
	    double_vector_ptr DGLutGenerator::
		getReverse(double_vector_ptr vec) {
		int size = vec->size();
		double_vector_ptr result(new double_vector(size));
		for (int x = 0; x != size; x++) {
		    (*result)[x] = (*vec)[size - 1 - x];
		}
		return result;
	    };
	  DGLutGenerator::DGLutGenerator(Composition_vector_ptr compositionVector):compositionVector
		(compositionVector)
	    {
		init();
	    };
	    RGB_vector_ptr DGLutGenerator::
		produce(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		int size = luminanceGammaCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));

		for (int x = 0; x != size; x++) {
		    double lumi = (*luminanceGammaCurve)[x];
		    double component = getComponent(lumi);
		    double r = rLut->getKey(component);
		    double g = gLut->getKey(component);
		    double b = bLut->getKey(component);
		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };

	    RGB_vector_ptr DGLutGenerator::
		produce(RGBGamma_ptr normalRGBGammaCurve) {
		double_vector_ptr rluminanceGammaCurve =
		    getLuminanceGammaCurve(normalRGBGammaCurve->r);
		double_vector_ptr gluminanceGammaCurve =
		    getLuminanceGammaCurve(normalRGBGammaCurve->g);
		double_vector_ptr bluminanceGammaCurve =
		    getLuminanceGammaCurve(normalRGBGammaCurve->b);

		int size = rluminanceGammaCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));
		double luminance[3], component[3];

		for (int x = 0; x != size; x++) {
		    luminance[0] = (*rluminanceGammaCurve)[x];
		    luminance[1] = (*gluminanceGammaCurve)[x];
		    luminance[2] = (*bluminanceGammaCurve)[x];

		    component[0] = getComponent(luminance[0]);
		    component[1] = getComponent(luminance[1]);
		    component[2] = getComponent(luminance[2]);

		    double r =
			(rLut->isValueInRange(component[0])) ? rLut->
			getKey(component[0]) : 0;
		    double g =
			(gLut->isValueInRange(component[1])) ? gLut->
			getKey(component[1]) : 0;
		    double b =
			(bLut->isValueInRange(component[2])) ? bLut->
			getKey(component[2]) : 0;

		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };
	    //==================================================================

	    //==================================================================
	    // LCDCalibrator
	    //==================================================================
	    void LCDCalibrator::set(int start, int end, int step) {
		this->start = start;
		this->end = end;
		this->step = step;
	    };

	    int LCDCalibrator::getn() {
		return (out == 12) ? 257 : 256;
	    };

	    int LCDCalibrator::getEffectiven() {
		return (in == 6 && out == 6) ? 253 : (in == 8) ? 256 : 257;
	    };

	    /*RGBGamma_ptr LCDCalibrator::
	       getRGBGamma(double_vector_ptr gammaCurve) {
	       double_vector_ptr r(new double_vector(*gammaCurve));
	       double_vector_ptr g(new double_vector(*gammaCurve));
	       double_vector_ptr b(new double_vector(*gammaCurve));
	       RGBGamma_ptr rgbGamma(new RGBGamma(r, g, b));
	       return rgbGamma;
	       }; */
	    /*double_array LCDCalibrator::getGammaCurve(double gamma, int n) {
	       double_array result(new double[n]);
	       for (int x = 0; x < n; x++) {
	       double normal = static_cast < double >(x) / (n - 1);
	       double v = java::lang::Math::pow(normal, gamma);
	       result[x] = v;
	       }
	       return result;
	       }; */
	    double_vector_ptr
		LCDCalibrator::getGammaCurveVector(double gamma, int n,
						   int effectiven) {
		double_vector_ptr result(new double_vector(n));
		for (int x = 0; x < effectiven; x++) {
		    double normal =
			static_cast < double >(x) / (effectiven - 1);
		    double v = java::lang::Math::pow(normal, gamma);
		    (*result)[x] = v;
		}
		for (int x = effectiven; x < n; x++) {
		    (*result)[x] = 1;
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
	    void LCDCalibrator::setGamma(double gamma) {
		this->gamma = gamma;
		setGammaCurve(getGammaCurveVector
			      (gamma, getn(), getEffectiven()));
	    };
	    void LCDCalibrator::setGamma(double rgamma, double ggamma,
					 double bgamma) {
		this->rgamma = rgamma;
		this->ggamma = ggamma;
		this->bgamma = bgamma;
		int n = getn();
		int effectiven = getEffectiven();
		setGammaCurve(getGammaCurveVector(rgamma, n, effectiven),
			      getGammaCurveVector(ggamma, n, effectiven),
			      getGammaCurveVector(bgamma, n, effectiven));
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr gammaCurve) {
		this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::
		setGammaCurve(double_vector_ptr rgammaCurve,
			      double_vector_ptr ggammaCurve,
			      double_vector_ptr bgammaCurve) {
		this->rgammaCurve = rgammaCurve;
		this->ggammaCurve = ggammaCurve;
		this->bgammaCurve = bgammaCurve;
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

	  LCDCalibrator::LCDCalibrator(bptr < ComponentAnalyzerIF > analyzer):analyzer(analyzer)
	    {
		rgbgamma = false;
		bIntensityGain = 1;
		rbInterpUnder = 0;
		gamma = rgamma = ggamma = bgamma = -1;
		fetcher.reset(new ComponentFetcher(analyzer));
		in = lut = out = Unknow;
	    };

	    /*
	       CCT + Gamma
	     */
	    RGB_vector_ptr LCDCalibrator::
		getDGLut(int start, int end, int step) {
		set(start, end, step);
		if (null == gammaCurve) {
		    throw new IllegalStateException("null == gammaCurve");
		}
#ifdef _DEBUG
		if (!DirectoryExists(DEBUG_DIR)) {
		    CreateDir(DEBUG_DIR);
		}
#endif

		//量測start->end得到的coponent/Y
		compositionVector =
		    fetcher->fetchComposition(start, end, step);

		STORE_COMPOSITION("0_fetch.xls", compositionVector);

		//產生generator
		generator.reset(new DGLutGenerator(compositionVector));
		//RGBGamma_ptr rgbgamma = getRGBGamma(gammaCurve);
		RGBGamma_ptr rgbgamma =
		    RGBGammaOp::getRGBGamma(gammaCurve);
		STORE_RGBGAMMA("1_rgbgamma1.xls", rgbgamma);

		RGBGammaOp gammaop;
		gammaop.setSource(rgbgamma);

		/* TODO : 要確認 */
		if (bIntensityGain != 1.0) {
		    //重新產生目標gamma curve
		    bptr < BIntensityGainOp >
			bgain(new BIntensityGainOp(bIntensityGain));
		    gammaop.addOp(bgain);
		    rgbgamma = gammaop.createInstance();
		};
		STORE_RGBGAMMA("2_rgbgamma2.xls", rgbgamma);

		//從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		RGB_vector_ptr dglut = generator->produce(rgbgamma);
		STORE_RGBVECTOR("3_dgcode1.xls", dglut);

		if (p1p2) {
		    //==========================================================
		    //p1p2第一階段, 對gamma做調整
		    //==========================================================
		    bptr < P1P2GammaOp >
			p1p2(new P1P2GammaOp(p1, p2, dglut));
		    gammaop.addOp(p1p2);

		    //產生修正後的gamma2(若沒有p1p2,則為原封不動)
		    rgbgamma = gammaop.createInstance();
		    STORE_RGBGAMMA("4_rgbgamma2.xls", rgbgamma);

		    //產生generator
		    //generator.reset(new DGLutGenerator(compositionVector));
		    //從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		    dglut = generator->produce(rgbgamma);
		    STORE_RGBVECTOR("5_dgcode2.xls", dglut);
		    //==========================================================


		    //==========================================================
		    //p1p2第二階段, 對dg code調整
		    //==========================================================
		    DGLutOp dgop;
		    dgop.setSource(dglut);
		    bptr < DGLutOp > op(new P1P2DGOp(p1, p2, in == Bit6));
		    dgop.addOp(op);
		    dglut = dgop.createInstance();
		    //==========================================================
		};
		//RGB_vector_ptr dgcode2 = dglut;
		finalRGBGamma = rgbgamma;

		//==============================================================
		// DG Code Op block
		//==============================================================
		const MaxValue & maxValue = (lut == 10) ?
		    MaxValue::Int10Bit : MaxValue::Int12Bit;
		//量化
		RGBVector::quantization(dglut, maxValue);
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		//==============================================================
		STORE_RGBVECTOR("6_dgcode.xls", result);
		//調整max value
		RGBVector::changeMaxValue(result, maxValue);

		this->dglut = result;
		return result;
	    };

	    /*
	       Gamma Only
	     */
	    RGB_vector_ptr LCDCalibrator::getDGLut(int step) {
		set(255, 0, step);
	    };

	    void LCDCalibrator::storeDGLut(const std::string & filename,
					   RGB_vector_ptr dglut) {

		int n = true == gamma256 ? 257 : 256;
		//砍掉已存在的
		ExcelFileDB::deleteExist(filename);
		//產生新檔
		DGLutFile file(filename, n);
		//產生property物件
		DGLutProperty property(*this);
		//寫入property
		file.setProperty(property);
		//寫入dgcode
		file.setGammaTable(dglut);
		//寫入raw data
		file.setRawData(compositionVector, finalRGBGamma);

	    };

	    BitDepth LCDCalibrator::getBitDepth(int bit) {
		switch (bit) {
		case 6:
		    return Bit6;
		case 8:
		    return Bit8;
		case 10:
		    return Bit10;
		case 12:
		    return Bit12;
		};
	    };

	    RGB_vector_ptr LCDCalibrator::
		getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		DGLutOp dgop;
		dgop.setSource(dglut);

		/*if (p1p2) {
		   //p1p2第二階段, 對dg code調整
		   bptr < DGLutOp > op(new P1P2DGOp(p1, p2, in == Bit6));
		   dgop.addOp(op);
		   } else { */
		if (!p1p2) {
		    //若不是p1p2就是RBInterp(至少目前是如此)
		    bptr < DGLutOp >
			op(new RBInterpolationOp(rbInterpUnder));
		    dgop.addOp(op);
		}

		if (bMax) {
		    //bmax的調整
		    bptr < DGLutOp > bmax(new BMaxOp(out));
		    dgop.addOp(bmax);
		}
		if (gByPass) {
		    //g bypass的調整
		    bptr < DGLutOp > gbypass(new GByPassOp(in, out));
		    dgop.addOp(gbypass);
		}
		if (avoidFRCNoise) {
		    //frc noise的調整
		    bptr < DGLutOp > avoidNoise(new AvoidFRCNoiseOp());
		    dgop.addOp(avoidNoise);
		}
		if (gamma256) {

		}
		RGB_vector_ptr result = dgop.createInstance();
		return result;
		//==============================================================
	    };


	    //==================================================================

	};
    };
};

