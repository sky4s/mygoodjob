#include <includeall.h>
#pragma hdrstop
#include "lcdcalibrator.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "rgbvectorop.h";

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
	    // Component
	    //==================================================================
	     Component::Component(RGB_ptr rgb, RGB_ptr intensity):rgb(rgb), intensity(intensity) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ):rgb(rgb), intensity(intensity), XYZ(XYZ) {

	    };
	     Component::Component(RGB_ptr rgb,
				  RGB_ptr intensity,
				  XYZ_ptr XYZ, RGB_ptr gamma):rgb(rgb),
		intensity(intensity), XYZ(XYZ), gamma(gamma) {

	    };
	    Component::Component(Component_ptr c) {
		if (null != c->rgb) {
		    this->rgb = c->rgb->clone();
		}
		if (null != c->intensity) {
		    this->intensity = c->intensity->clone();
		}
		if (null != c->XYZ) {
		    this->XYZ = c->XYZ->clone();
		}
		if (null != c->gamma) {
		    this->gamma = c->gamma->clone();
		}
	    };

	    Component::Component(Patch_ptr p) {

		if (null != p->getRGB()) {
		    this->rgb = p->getRGB()->clone();
		}

		if (null != p->getIntensity()) {
		    this->intensity = p->getIntensity()->clone();
		}

		if (null != p->getXYZ()) {
		    this->XYZ = p->getXYZ()->clone();
		}
	    };
	    Component_vector_ptr Component::reverse(Component_vector_ptr componentVector) {
		Component_vector_ptr result(new
					    Component_vector(componentVector->rbegin(),
							     componentVector->rend()));
		return result;
	    };
	    //==================================================================


	    //==================================================================
	    // ComponentFetcher
	    //==================================================================
	    /*ComponentFetcher::ComponentFetcher(bptr < IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):firstAnalyzer
	       (analyzer),
	       //bitDepth(bitDepth),
	       extraMeasureRGB(nil_RGB_ptr) {
	       }; */
	  ComponentFetcher::ComponentFetcher(bptr < IntensityAnalyzerIF > analyzer):firstAnalyzer(analyzer),
		extraMeasureRGB(nil_RGB_ptr)
	    {
	    };
	    Component_vector_ptr ComponentFetcher::fetch(RGB_vector_ptr rgbMeasureCode,
							 bool luminanceMode) {
		Component_vector_ptr result(new Component_vector());

		bptr < cms::measure::IntensityAnalyzerIF > analyzer = getAnalyzer();
		int waitTimes = analyzer->getWaitTimes();
		analyzer->setWaitTimes(10000);
		analyzer->beginAnalyze();



		if (false == luminanceMode && nil_RGB_ptr != extraMeasureRGB) {
		    //量測真實白點
/* TODO : Aging */
		    extraMeasureXYZ = analyzer->getCIEXYZOnly(extraMeasureRGB);
		    //量過就歸零
		    extraMeasureRGB = nil_RGB_ptr;
		}

		bool waitingStable = true;
		stop = false;
		if (inverseMeasure) {
		    rgbMeasureCode = RGBVector::reverse(rgbMeasureCode);
		}
		int count = 0;
		foreach(const RGB_ptr & rgb, *rgbMeasureCode) {
		    if (luminanceMode) {
			XYZ_ptr XYZ = analyzer->getCIEXYZOnly(rgb);
			Component_ptr c(new Component(rgb, nil_RGB_ptr, XYZ));
			result->push_back(c);
		    } else {
			RGB_ptr intensity = analyzer->getIntensity(rgb);
			XYZ_ptr XYZ = analyzer->getCIEXYZ();

			if (null != XYZ && null != intensity) {
			    Component_ptr component(new Component(rgb, intensity, XYZ));
			    result->push_back(component);
			}
		    }

		    if (true == waitingStable) {
			//只有第一次量測的時候發揮作用
			//為了希望量測前面板穩定而設計
			waitingStable = false;
			analyzer->setWaitTimes(waitTimes);
		    }

		    if (true == stop) {
			//為了可以中斷量測
			stop = false;
			analyzer->endAnalyze();
			return nil_Component_vector_ptr;
		    }

		    if (null != feedbackListener) {
			//show出現在量到的灰階
			string msg = _toString(count++) + "=> " + (*rgb->toString());
			if (feedbackMessage.size() != 0) {
			    msg = feedbackMessage + ": " + msg;
			}
			feedbackListener->doFeedback(msg);
		    }
		}
		feedbackMessage = "";
		if (inverseMeasure) {
		    result = Component::reverse(result);
		}
		analyzer->endAnalyze();
		return result;
	    };
	    Component_vector_ptr ComponentFetcher::fetchComponent(RGB_vector_ptr rgbMeasureCode) {
		return fetch(rgbMeasureCode, false);

	    };

	    Component_vector_ptr ComponentFetcher::fetchComponent(bptr <
								  MeasureCondition
								  > measureCondition) {
		return fetchComponent(measureCondition->getRGBMeasureCode());
	    };
	    Component_vector_ptr ComponentFetcher::fetchLuminance(bptr <
								  MeasureCondition
								  > measureCondition) {
		RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
		return fetch(rgbMeasureCode, true);

	    };


	    Component_vector_ptr ComponentFetcher::fetchRGBLuminance(bptr <
								     MeasureCondition
								     > measureCondition) {
		bptr < cms::measure::MeterMeasurement > mm = firstAnalyzer->getMeterMeasurement();
		bptr < MeasureTool > mt(new MeasureTool(mm));
		//bool inverseMeasure = MainForm->CheckBox_InverseMeasure->Checked;
		//mt->InverseMeasure = inverseMeasure;
		MeasureWindow->addWindowListener(mt);
		throw java::lang::UnsupportedOperationException();
	    };
	    void ComponentFetcher::storeToExcel(const string & filename,
						Component_vector_ptr componentVector) {

		Util::deleteExist(filename);
		DGLutFile dglut(filename, Create);
		RGBGamma_ptr rgbp = nil_RGBGamma;


		//如果 gamma有東西, 就寫到檔案裡
		if (null != (*componentVector)[0]->gamma) {
		    double_vector_ptr r(new double_vector());
		    double_vector_ptr g(new double_vector());
		    double_vector_ptr b(new double_vector());
		    foreach(Component_ptr c, *componentVector) {
			RGB_ptr gamma = c->gamma;
			//RGB_ptr gamma = c->rgb;
			r->push_back(gamma->R);
			g->push_back(gamma->G);
			b->push_back(gamma->B);
		    }
		    r = DoubleArray::getReverse(r);
		    g = DoubleArray::getReverse(g);
		    b = DoubleArray::getReverse(b);

		    rgbp = RGBGamma_ptr(new RGBGamma(r, g, b));
		}


		dglut.setRawData(componentVector, rgbp, nil_RGBGamma);

		RGB_vector_ptr rgbVector = getRGBVector(componentVector);
		rgbVector = RGBVector::reverse(rgbVector);
		dglut.setGammaTable(rgbVector);

		dglut.setDeltaData(componentVector);
	    };
	    void ComponentFetcher::windowClosing(TObject * Sender, TCloseAction & Action) {
		stop = true;
	    };
	    bptr < IntensityAnalyzerIF > ComponentFetcher::getAnalyzer() {
		if (null != secondAnalyzer) {
		    return secondAnalyzer;
		} else {

		    return firstAnalyzer;
		}
	    };
	    RGB_vector_ptr ComponentFetcher::getRGBVector(Component_vector_ptr componentVector) {
		int size = componentVector->size();
		RGB_vector_ptr rgbVector(new RGB_vector(size));
		for (int x = 0; x < size; x++) {
		    Component_ptr c = (*componentVector)[x];
		    (*rgbVector)[x] = c->rgb;
		}
		return rgbVector;
	    };
	    //==================================================================

	    //==================================================================
	    // ComponentLinearRelation
	    //==================================================================
	    void ComponentLinearRelation::init(double2D_ptr input, double2D_ptr output) {
		//==============================================================
		// 計算a/c/d
		//==============================================================
		regression = bptr < PolynomialRegression >
		    (new PolynomialRegression(input, output, Polynomial::COEF_3::BY_3C));
		regression->regress();
		const double *coefs = (*regression->getCoefs())[0];
		a1 = coefs[1];
		a2 = coefs[2];
		a3 = coefs[3];
		a0 = coefs[0];
		c = 1 / (a1 + a2 + a3);
		d = -a0 / (a1 + a2 + a3);
		//==============================================================
	    };

	    void ComponentLinearRelation::init(Component_vector_ptr componentVector) {
		//==============================================================
		// 建立回歸資料
		//==============================================================
		int size = componentVector->size();
		double2D_ptr input(new double2D(size, 3));
		double2D_ptr output(new double2D(size, 1));

		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    double Y = component->XYZ->Y;
		    RGB_ptr intensity = component->intensity;

		    (*input)[x][0] = intensity->R;
		    (*input)[x][1] = intensity->G;
		    (*input)[x][2] = intensity->B;
		    (*output)[x][0] = Y;
		}
		//==============================================================

		//==============================================================
		// 計算a/c/d
		//==============================================================
		init(input, output);
		//==============================================================                
	    };

	    /*ComponentLinearRelation::
	       ComponentLinearRelation(double2D_ptr input, double2D_ptr output) {
	       init(input, output);

	       }; */
	  ComponentLinearRelation::ComponentLinearRelation(Component_vector_ptr componentVector):componentVector(componentVector)
	    {
		init(componentVector);
	    };
	    double ComponentLinearRelation::getIntensity(double luminance) {
		return c * luminance + d;
	    };
	    double ComponentLinearRelation::
		getLuminance(double rIntensity, double gIntensity, double bIntensity) {
		return a0 + rIntensity * a1 + gIntensity * a2 + bIntensity * a3;
	    };
	    //==================================================================

	    //==================================================================
	    // ComponentLUT
	    //==================================================================
	    void ComponentLUT::init(Component_vector_ptr componentVector) {
		//==============================================================
		// lut前置作業
		//==============================================================
		int size = componentVector->size();
		double_vector_ptr rKeys(new double_vector());
		double_vector_ptr gKeys(new double_vector());
		double_vector_ptr bKeys(new double_vector());
		double_vector_ptr rValues(new double_vector());
		double_vector_ptr gValues(new double_vector());
		double_vector_ptr bValues(new double_vector());
		double_vector_ptr YValues(new double_vector());
		double_array values(new double[3]);

		for (int x = 0; x != size; x++) {
		    Component_ptr component = (*componentVector)[x];
		    RGB_ptr intensity = component->intensity;

		    RGB_ptr code = component->rgb;
		    code->getValues(values, MaxValue::Double255);

		    rKeys->push_back(values[0]);
		    gKeys->push_back(values[1]);
		    bKeys->push_back(values[2]);
		    double r = intensity->R;
		    double g = intensity->G;
		    double b = intensity->B;
		    rValues->push_back(r);
		    gValues->push_back(g);
		    bValues->push_back(b);
		    double Y = component->XYZ->Y;
		    YValues->push_back(Y);

		    if (-1 == rMax) {
			rMax = values[0];
			gMax = values[1];
			bMax = values[2];
			rIntensityMax = intensity->R;
			gIntensityMax = intensity->G;
			bIntensityMax = intensity->B;
		    }
		}
		//==============================================================

		//==============================================================
		// 產生RGB LUT
		//==============================================================
		//DoubleArray::inspect(rKeys);
		//DoubleArray::inspect(rValues);

		rKeys = DoubleArray::getReverse(rKeys);
		gKeys = DoubleArray::getReverse(gKeys);
		bKeys = DoubleArray::getReverse(bKeys);
		rValues = DoubleArray::getReverse(rValues);
		gValues = DoubleArray::getReverse(gValues);
		bValues = DoubleArray::getReverse(bValues);
		YValues = DoubleArray::getReverse(YValues);

		//DoubleArray::inspect(rKeys);
		//DoubleArray::inspect(rValues);

		rLut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(rKeys, rValues));
		gLut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(gKeys, gValues));
		bLut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(bKeys, bValues, Ripple));
		YLut = bptr < Interpolation1DLUT > (new Interpolation1DLUT(gKeys, YValues));
		//==============================================================                
	    };
	  ComponentLUT::ComponentLUT(Component_vector_ptr componentVector):componentVector(componentVector)
	    {
		rMax = gMax = bMax = rIntensityMax = gIntensityMax = bIntensityMax = -1;
		init(componentVector);
	    };
	    double ComponentLUT::getIntensity(const Dep::Channel & ch, double code) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->getValue(code);
		case ChannelIndex::G:
		    return gLut->getValue(code);
		case ChannelIndex::B:
		    return bLut->getValue(code);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" + *ch.toString());
		}
	    };
	    double ComponentLUT::getCode(const Dep::Channel & ch, double intensity) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->getKey(intensity);
		case ChannelIndex::G:
		    return gLut->getKey(intensity);
		case ChannelIndex::B:
		    return bLut->getKey(intensity);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" + *ch.toString());
		}
	    };
	    RGB_ptr ComponentLUT::getCode(double luminance) {
		luminance = YLut->correctValueInRange(luminance);
		double key = YLut->getKey(luminance);
		RGB_ptr rgb(new RGBColor(key, key, key));
		return rgb;
	    };
	    double ComponentLUT::correctIntensityInRange(const Dep::Channel & ch, double intensity) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->correctValueInRange(intensity);
		case ChannelIndex::G:
		    return gLut->correctValueInRange(intensity);
		case ChannelIndex::B:
		    return bLut->correctValueInRange(intensity);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" + *ch.toString());
		}
	    };
	    double ComponentLUT::correctCodeInRange(const Dep::Channel & ch, double code) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->correctKeyInRange(code);
		case ChannelIndex::G:
		    return gLut->correctKeyInRange(code);
		case ChannelIndex::B:
		    return bLut->correctKeyInRange(code);
		default:
		    throw IllegalArgumentException("Unsupported Channel:" + *ch.toString());
		}
	    };

	    double ComponentLUT::getMaxBIntensity() {
		return bLut->getMaxValue();
	    };
	    int ComponentLUT::getMaxBIntensityRGL() {
		double value = getMaxBIntensity();
		return bLut->getKey(value);
	    }

	    bool ComponentLUT::hasCorrectedInRange(const Dep::Channel & ch) {
		switch (ch.chindex) {
		case ChannelIndex::R:
		    return rLut->hasCorrectedInRange();
		case ChannelIndex::G:
		    return gLut->hasCorrectedInRange();
		case ChannelIndex::B:
		    return bLut->hasCorrectedInRange();
		default:
		    throw IllegalArgumentException("Unsupported Channel:" + *ch.toString());
		}
	    };
	    void ComponentLUT::setInverseSearch(bool inverse) {
		bLut->InverseSearch = inverse;
	    };
	    //==================================================================

	};
    };
};

