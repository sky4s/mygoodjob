#include "lcdcalibrator.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/measure/MeterMeasurement.h>
#include <cms/measure/analyzer.h>
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    //==================================================================
	    // Composition
	    //==================================================================
	     Composition::Composition(RGB_ptr rgb,
				      RGB_ptr component):rgb(rgb),
		component(component) {

	    };
	    //==================================================================

	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	     ComponentFetcher::ComponentFetcher(bptr < MeterMeasurement >
						mm,
						bptr <
						ComponentAnalyzerIF >
						analyzer):mm(mm),
		analyzer(analyzer) {

	    };
	     ComponentFetcher::ComponentFetcher(bptr <
						ComponentAnalyzerIF >
						analyzer):analyzer
		(analyzer) {

	    };

	    Composition_vector_ptr ComponentFetcher::
		fetchComposition(int start, int end, int step) {
		using namespace Dep;
		Composition_vector_ptr result(new Composition_vector());
		for (int x = start; x >= end; x -= end) {
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    RGB_ptr component = analyzer->getComponent(rgb);
		    Composition_ptr composition(new
						Composition(rgb,
							    component));
		    result->push_back(composition);
		};
		return result;
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
	    double_vector_ptr LCDCalibrator::
		getGammaCurveVector(double gamma, int n) {
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
	    void LCDCalibrator::setGamma(double gamma, int n) {
		setGammaCurve(getGammaCurveVector(gamma, n));
	    };
	    void LCDCalibrator::setGammaCurve(double_array gammaCurve,
					      int n) {
		//this->gammaCurve = gammaCurve;
	    };
	    void LCDCalibrator::setGammaCurve(double_vector_ptr gammaCurve) {
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
	    void LCDCalibrator::setBitDepth(const BitDepth & in,
					    const BitDepth & lut,
					    const BitDepth & out) {
		this->in = in;
		this->lut = lut;
		this->out = out;
	    };
	    //==================================================================
	};
    };
};

;

