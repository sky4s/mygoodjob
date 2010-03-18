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

#define MAKE_DEBUG_DIR() \
if (!DirectoryExists(DEBUG_DIR)) { \
    CreateDir(DEBUG_DIR); \
}
#define STORE_COMPONENT( filename , result ) \
MAKE_DEBUG_DIR(); \
ComponentFetcher::storeToExcel(debug_dir + _(filename), result);

#define STORE_RGBGAMMA( filename , result ) \
MAKE_DEBUG_DIR(); \
cms::lcd::calibrate::RGBGamma::storeToExcel(debug_dir + _(filename), result);

#define STORE_RGBVECTOR( filename , result ) \
MAKE_DEBUG_DIR(); \
RGBVector::storeToExcel(debug_dir + _(filename), result);

#define STORE_DOUBLE_ARRAY( filename , result ) \
MAKE_DEBUG_DIR(); \
DoubleArray::storeToExcel(debug_dir + _(filename), result);

#else
#define STORE_COMPONENT( filename , result )
#define STORE_RGBGAMMA( filename , result )
#define STORE_RGBVECTOR( filename , result )
#define STORE_DOUBLE_ARRAY( filename , result )
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
	    // Component
	    //==================================================================
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity):rgb(rgb),
		intensity(intensity) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ):rgb(rgb),
		intensity(intensity), XYZ(XYZ) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ, RGB_ptr gamma):rgb(rgb),
		intensity(intensity), XYZ(XYZ), gamma(gamma) {

	    };
	    //==================================================================


	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	  ComponentFetcher::ComponentFetcher(bptr < IntensityAnalyzerIF > analyzer):analyzer
		(analyzer)
	    {

	    };

	    Component_vector_ptr ComponentFetcher::
		fetchComponent(int start, int end, int step) {

		Component_vector_ptr result(new Component_vector());
		for (int x = start; x >= end; x -= step) {
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    RGB_ptr intensity = analyzer->getIntensity(rgb);
		    XYZ_ptr XYZ = analyzer->getCIEXYZ();
		    Component_ptr component(new Component(rgb, intensity,
							  XYZ));
		    result->push_back(component);
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
						Component_vector_ptr
						componentVector) {

		int n = componentVector->size();
		ExcelFileDB::deleteExist(filename);
		DGLutFile dglut(filename, n);
		dglut.setRawData(componentVector, nil_RGBGamma,
				 nil_RGBGamma);
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
		int size = componentVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));
		double_vector_ptr keys(new double_vector(size));
		double_vector_ptr rValues(new double_vector(size));
		double_vector_ptr gValues(new double_vector(size));
		double_vector_ptr bValues(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    double Y = component->XYZ->Y;
		    RGB_ptr intensity = component->intensity;

		    (*input)[x][0] = intensity->R;
		    (*input)[x][1] = intensity->G;
		    (*input)[x][2] = intensity->B;
		    (*output)[x][0] = Y;

		    (*keys)[x] = component->rgb->getValue(Channel::W);
		    (*rValues)[x] = intensity->R;
		    (*gValues)[x] = intensity->G;
		    (*bValues)[x] = intensity->B;
		}
		//==============================================================

		//==============================================================
		// 計算c/d
		//==============================================================
		regression.reset(new PolynomialRegression(input, output,
							  Polynomial::
							  COEF_3::BY_3C));
		regression->regress();
		const double *coefs = (*regression->getCoefs())[0];
		a1 = coefs[1];
		a2 = coefs[2];
		a3 = coefs[3];
		a0 = coefs[0];
		c = 1 / (a1 + a2 + a3);
		d = -a0 / (a1 + a2 + a3);
		//==============================================================
		double maxintensity =
		    Math::floor(getMaximumIntensity()) + 1;

		maxLuminance =
		    getLuminance(maxintensity, maxintensity, maxintensity);
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
	    double DGLutGenerator::getIntensity(double luminance) {
		return c * luminance + d;
	    };
	    double DGLutGenerator::getLuminance(double rIntensity,
						double gIntensity,
						double bIntensity) {
		return a0 + rIntensity * a1 + gIntensity * a2 +
		    bIntensity * a3;
	    };
	    /*
	       將正規化的gamma curve, 轉換為絕對的亮度curve
	     */
	    double_vector_ptr DGLutGenerator::
		getLuminanceGammaCurve(double_vector_ptr normalGammaCurve)
	    {
		int size = normalGammaCurve->size();
		double_vector_ptr luminanceGammaCurve(new
						      double_vector(size));
		double differ = maxLuminance - minLuminance;
		for (int x = 0; x != size; x++) {
		    (*luminanceGammaCurve)[x] =
			differ * (*normalGammaCurve)[x] + minLuminance;
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
	    double DGLutGenerator::getMaximumIntensity() {
		//int maxindex = (out == Dep::MaxValue::Int6Bit) ? 3 : 0;
                int maxindex = 0;
		Component_ptr maxcomponent = (*componentVector)[maxindex];
		RGB_ptr maxintensity = maxcomponent->intensity;
		const Channel & minchannel = maxintensity->getMinChannel();
		double maxvalue = maxintensity->getValue(minchannel);
		return maxvalue;
	    };
	  DGLutGenerator::DGLutGenerator(Component_vector_ptr componentVector, const MaxValue & in, const MaxValue & out):componentVector
		(componentVector), in(in), out(out)
	    {
		init();
	    };

	    RGB_vector_ptr DGLutGenerator::
		produce(RGBGamma_ptr rgbIntensityCurve) {
		double_vector_ptr rIntensityCurve = rgbIntensityCurve->r;
		double_vector_ptr gIntensityCurve = rgbIntensityCurve->g;
		double_vector_ptr bIntensityCurve = rgbIntensityCurve->b;

		int size = rIntensityCurve->size();
		RGB_vector_ptr dglut(new RGB_vector(size));
		double intensity[3];
		//將code 0強制設定為0
		(*dglut)[0] = RGB_ptr(new RGBColor(0, 0, 0));

		for (int x = 1; x != size; x++) {
		    intensity[0] = (*rIntensityCurve)[x];
		    intensity[1] = (*gIntensityCurve)[x];
		    intensity[2] = (*bIntensityCurve)[x];

		    intensity[0] = rLut->correctValueInRange(intensity[0]);
		    intensity[1] = gLut->correctValueInRange(intensity[1]);
		    intensity[2] = bLut->correctValueInRange(intensity[2]);

		    double r = rLut->getKey(intensity[0]);
		    double g = gLut->getKey(intensity[1]);
		    double b = bLut->getKey(intensity[2]);

		    RGB_ptr rgb(new RGBColor(r, g, b));
		    (*dglut)[x] = rgb;
		}
		return dglut;
	    };

	    RGBGamma_ptr DGLutGenerator::
		getRGBGamma(double_vector_ptr normalGammaCurve) {
		double_vector_ptr luminanceGammaCurve =
		    getLuminanceGammaCurve(normalGammaCurve);
		int size = luminanceGammaCurve->size();
		double_vector_ptr rIntenisty(new double_vector(size));
		double_vector_ptr gIntenisty(new double_vector(size));
		double_vector_ptr bIntenisty(new double_vector(size));

		for (int x = 0; x != size; x++) {
		    double luminance = (*luminanceGammaCurve)[x];
		    double intensity = getIntensity(luminance);
		    (*rIntenisty)[x] = intensity;
		    (*gIntenisty)[x] = intensity;
		    (*bIntenisty)[x] = intensity;
		}

		RGBGamma_ptr rgbgamma(new
				      RGBGamma(rIntenisty, gIntenisty,
					       bIntenisty, 100,
					       Intensity));

		return rgbgamma;
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
		return (out == MaxValue::Int12Bit) ? 257 : 256;
	    };

	    int LCDCalibrator::getEffectiven() {
		return (in == MaxValue::Int6Bit
			&& out == MaxValue::Int6Bit) ? 253 :
		    (in == MaxValue::Int8Bit) ? 256 : 257;
	    };

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
		//this->p1p2 = true;
		this->correct = P1P2;
	    };
	    void LCDCalibrator::setRBInterpolation(int under) {
		//this->p1p2 = false;
		this->correct = RBInterpolation;
		this->rbInterpUnder = under;
	    };
	    void LCDCalibrator::setNoneDimCorrect() {
		this->correct = None;
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
	    /*void LCDCalibrator::setBitDepth(const Dep::MaxValue & in,
	       const Dep::MaxValue & lut,
	       const Dep::MaxValue & out) {
	       this->in = in;
	       this->lut = lut;
	       this->out = out;
	       }; */

	    LCDCalibrator::LCDCalibrator(bptr < IntensityAnalyzerIF >
					 analyzer,
					 const Dep::MaxValue & in,
					 const Dep::MaxValue & lut,
					 const Dep::
					 MaxValue &
					 out):analyzer(analyzer), in(in),
		lut(lut), out(out) {
		rgbgamma = false;
		bIntensityGain = 1;
		rbInterpUnder = 0;
		p1 = p2 = 0;
		gamma = rgamma = ggamma = bgamma = -1;
		fetcher.reset(new ComponentFetcher(analyzer));
		//in = lut = out = Unknow;
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
		//量測start->end得到的coponent/Y
		componentVector =
		    fetcher->fetchComponent(start, end, step);
		STORE_COMPONENT("0_fetch.xls", componentVector);

		//產生generator
		generator.
		    reset(new DGLutGenerator(componentVector, in, out));
		RGBGamma_ptr rgbgamma = generator->getRGBGamma(gammaCurve);
                STORE_DOUBLE_ARRAY("0_gammacurve.xls",gammaCurve);
		STORE_RGBGAMMA("1_rgbgamma_org.xls", rgbgamma);

		/* TODO : 要確認 */
		if (bIntensityGain != 1.0) {
		    //重新產生目標gamma curve
		    bptr < BIntensityGainOp >
			bgain(new BIntensityGainOp(bIntensityGain));
		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(bgain);
		    rgbgamma = gammaop.createInstance();
		};
		initialRGBGamma = rgbgamma->clone();
		STORE_RGBGAMMA("2_rgbgamma_init.xls", rgbgamma);

		//從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		RGB_vector_ptr dglut = generator->produce(rgbgamma);
		STORE_RGBVECTOR("3_dgcode.xls", dglut);
		//==============================================================
		//第一次量化處理
		//==============================================================
		//量化
		RGBVector::quantization(dglut, lut);
		//==============================================================

		if (correct == P1P2) {
		    //==========================================================
		    //p1p2第一階段, 對gamma做調整
		    //==========================================================
		    bptr < P1P2GammaOp >
			p1p2(new P1P2GammaOp(p1, p2, dglut));
		    RGBGammaOp gammaop;
		    gammaop.setSource(rgbgamma);
		    gammaop.addOp(p1p2);

		    //產生修正後的gamma2(若沒有p1p2,則為原封不動)
		    rgbgamma = gammaop.createInstance();
		    STORE_RGBGAMMA("4_rgbgamma_p1p2.xls", rgbgamma);

		    //產生generator
		    //generator.reset(new DGLutGenerator(compositionVector));
		    //從目標gamma curve產生dg code, 此處是傳入normal gammaCurve
		    dglut = generator->produce(rgbgamma);
		    //量化
		    RGBVector::quantization(dglut, lut);
		    STORE_RGBVECTOR("5_dgcode_p1p2g.xls", dglut);
		    //==========================================================


		    //==========================================================
		    //p1p2第二階段, 對dg code調整
		    //==========================================================
		    DGLutOp dgop;
		    dgop.setSource(dglut);
		    bptr < DGLutOp > op(new P1P2DGOp(p1, p2, lut));
		    dgop.addOp(op);
		    dglut = dgop.createInstance();
		    //量化
		    RGBVector::quantization(dglut, lut);
		    STORE_RGBVECTOR("6_dgcode_p1p2dg.xls", dglut);
		    //==========================================================
		};
		//RGB_vector_ptr dgcode2 = dglut;
		finalRGBGamma = rgbgamma;

		//==============================================================
		// DG Code Op block
		//==============================================================
		//量化
		//RGBVector::quantization(dglut, maxValue);
		RGB_vector_ptr result = getDGLutOpResult(dglut);
		//==============================================================

		STORE_RGBVECTOR("7_dgcode_final.xls", result);
		//調整max value
		RGBVector::changeMaxValue(result, lut);

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
		file.setRawData(componentVector, initialRGBGamma,
				finalRGBGamma);

	    };

	    /*BitDepth LCDCalibrator::getBitDepth(int bit) {
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
	       }; */

	    RGB_vector_ptr LCDCalibrator::
		getDGLutOpResult(RGB_vector_ptr dglut) {
		//==============================================================
		// DG Code Op block
		//==============================================================
		DGLutOp dgop;
		dgop.setSource(dglut);


		if (correct == RBInterpolation) {
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
		    bptr < DGLutOp > avoidNoise(new FrcNROp());
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

