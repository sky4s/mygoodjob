#include <includeall.h>
#pragma hdrstop
#include "rgbArray.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace util {
	using namespace std;
	using Dep::RGBColor;
	using Dep::MaxValue;
	using namespace cms::colorformat;
	using namespace boost;

	//==================================================================
	// RGBVector
	//==================================================================
	string_ptr RGBVector::toString(RGB_vector_ptr rgbVector) {

	    string_ptr result(new string());
	     foreach(RGB_ptr rgb, *rgbVector) {
		(*result) += *rgb->toString() + "\n";

	    };
	     return result;
	};
	RGB_vector_ptr RGBVector::getLinearRGBVector(int n) {
	    RGB_vector_ptr result(new RGB_vector());
	    for (int x = 0; x < n; x++) {
		RGB_ptr rgb(new RGBColor(x, x, x));
		result->push_back(rgb);
	    };
	    return result;
	};
	RGB_vector_ptr RGBVector::getLinearRGBVector(bptr < cms::lcd::calibrate::BitDepthProcessor >
						     bitDepth, double bgain) {
	    return getLinearRGBVector(bitDepth, 1, 1, bgain);
	};
	RGB_vector_ptr RGBVector::getLinearRGBVector(bptr < cms::lcd::calibrate::BitDepthProcessor >
						     bitDepth, double rgain, double ggain,
						     double bgain) {
	    int n = bitDepth->getEffectiveLevel();
	    double maxdc = bitDepth->getMaxDigitalCount();	//�o��8bit�U�̤j��
	    const MaxValue & maxValue = bitDepth->getLutMaxValue();	//lut��maxvalue
	    double factor = maxValue.max / 255.;
	    RGB_vector_ptr result(new RGB_vector());
	    for (int x = 0; x < n; x++) {
		double v = maxdc * factor / (n - 1) * x;
		double r = v * rgain;
		double g = v * ggain;
		double b = v * bgain;
		RGB_ptr rgb(new RGBColor(r, g, b, maxValue));
		result->push_back(rgb);
	    }
	    int remainn = bitDepth->getLevel() - n;
	    RGB_ptr last = (*result)[result->size() - 1];
	    for (int x = 0; x < remainn; x++) {
		RGB_ptr rgb(new RGBColor(last->R, last->G, last->B, maxValue));
		result->push_back(rgb);
	    }
	    return result;
	};
	void RGBVector::storeToExcel(const string & filename, RGB_vector_ptr rgbVector) {


	    Util::deleteExist(filename);
	    SimpleExcelAccess excel(filename, Create,
				    StringVector::fromCString(4, "Gray Level", "R", "G", "B"));
	    int size = rgbVector->size();
	    for (int x = 0; x != size; x++) {
		RGB_ptr rgb = (*rgbVector)[x];
		string_vector_ptr values =
		    StringVector::fromDouble(4, static_cast < double >(x), rgb->R, rgb->G,
					     rgb->B);
		excel.insert(values);
	    };
	};
	void RGBVector::storeToText(const std::string & filename, RGB_vector_ptr rgbVector) {

	    bptr_ < TStringList > list(new TStringList);
	    foreach(RGB_ptr rgb, *rgbVector) {
		list->Add((_toString(rgb->R) + "\t" + _toString(rgb->G) +
			   "\t" + _toString(rgb->B)).c_str());
	    }
	    //list->Add("");
	    list->SaveToFile(filename.c_str());
	    //Save the list

	};

	RGB_vector_ptr RGBVector::deepClone(RGB_vector_ptr vector) {
	    int size = vector->size();
	    RGB_vector_ptr result(new RGB_vector(size));
	    for (int x = 0; x != size; x++) {
		(*result)[x] = (*vector)[x]->clone();
	    }
	    return result;
	};
	void RGBVector::changeMaxValue(RGB_vector_ptr vector, const MaxValue & type) {
	    foreach(RGB_ptr rgb, *vector) {
		rgb->changeMaxValue(type);
	}};
	void RGBVector::quantization(RGB_vector_ptr vector, const MaxValue & maxValue) {
	    foreach(RGB_ptr rgb, *vector) {
		rgb->quantization(maxValue);
	}};
	RGB_vector_ptr RGBVector::reverse(RGB_vector_ptr rgbVector) {
	    RGB_vector_ptr result(new RGB_vector(rgbVector->rbegin(), rgbVector->rend()));
	    return result;
	};
	bool RGBVector::isAscend(RGB_vector_ptr rgbVector) {
	    return isAscend(rgbVector, 0, rgbVector->size() - 1);
	};
	bool RGBVector::isAscend(RGB_vector_ptr rgbVector, int start, int end) {
	    RGB_ptr preRGB;
	    for (int x = start; x <= end; x++) {
		RGB_ptr rgb = (*rgbVector)[x];
		if (null == preRGB) {
		    preRGB = rgb;
		    continue;
		} else if (rgb->R <= preRGB->R || rgb->G <= preRGB->G || rgb->B <= preRGB->B) {
		    return false;
		}
		preRGB = rgb;
	    }
	    return true;
	}
	//==================================================================

	//==================================================================
	// RGBGamma
	//==================================================================
      RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g, double_vector_ptr b):r(r), g(g), b(b),
	    max(1),
	    type(Gamma) {
	};
      RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g, double_vector_ptr b, double_vector_ptr w):r(r), g(g), b(b),
	    w(w), max(1),
	    type(Gamma) {
	};
      RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g, double_vector_ptr b, const double max, const RGBType type):r(r), g(g), b(b), max(max),
	    type(type)
	{
	};
	RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g,
			   double_vector_ptr b, double_vector_ptr w,
			   const double max, const RGBType type):r(r),
	    g(g), b(b), w(w), max(max), type(type) {
	};
	void RGBGamma::storeToExcel(const std::string & filename, RGBGamma_ptr rgbgamma) {


	    Util::deleteExist(filename);
	    SimpleExcelAccess excel(filename, Create,
				    StringVector::
				    fromCString(4, "Gray Level", "R gamma", "G gamma", "B gamma"));

	    int size = rgbgamma->r->size();

	    for (int x = 0; x != size; x++) {
		(*rgbgamma->r)[x];
		string_vector_ptr values =
		    StringVector::fromDouble(4, static_cast < double >(x), (*rgbgamma->r)[x],
					     (*rgbgamma->g)[x], (*rgbgamma->b)[x]);
		excel.insert(values);
	    };
	};

	void RGBGamma::storeToDesiredGamma(const std::string & filename, RGBGamma_ptr rgbgamma) {
	    /* TODO : storeToDesiredGamma */
	};

	RGBGamma_ptr RGBGamma::loadFromDesiredGamma(const std::string & filename) {
	    return loadFromDesiredGamma(filename, false);
	};

	RGBGamma_ptr RGBGamma::loadFromDesiredGammaValue(const std::string & filename) {
	    return loadFromDesiredGamma(filename, true);
	};

	RGBGamma_ptr RGBGamma::loadFromDesiredGamma(const std::string & filename, bool isGammaValue) {
	    using namespace java::lang;

	    SimpleExcelAccess excel(filename);
	    double_vector_ptr r(new double_vector()),
		g(new double_vector()), b(new double_vector()), w(new double_vector());
	    try {
		bptr < DBQuery > query = excel.retrieve();
		double maxLevel = -1;
		while (query->hasNext()) {
		    string_vector_ptr result = query->nextResult();
		    double level = _toDouble((*result)[0]);
		    if (maxLevel == -1) {
			maxLevel = level;
		    }

		    double wg = _toDouble((*result)[1]);
		    double rg = _toDouble((*result)[2]);
		    double gg = _toDouble((*result)[3]);
		    double bg = _toDouble((*result)[4]);
		    if (isGammaValue) {
			double normal = level / maxLevel;
			wg = Math::pow(normal, wg);
			rg = Math::pow(normal, rg);
			gg = Math::pow(normal, gg);
			bg = Math::pow(normal, bg);
		    }

		    w->push_back(wg);
		    r->push_back(rg);
		    g->push_back(gg);
		    b->push_back(bg);

		};
		//==============================================================
		// ����B�z
		//==============================================================
		w = double_vector_ptr(new double_vector(w->rbegin(), w->rend()));
		r = double_vector_ptr(new double_vector(r->rbegin(), r->rend()));
		g = double_vector_ptr(new double_vector(g->rbegin(), g->rend()));
		b = double_vector_ptr(new double_vector(b->rbegin(), b->rend()));
		//==============================================================
		RGBGamma_ptr rgbgamma(new RGBGamma(r, g, b, w));
		return rgbgamma;
	    }
	    catch(EOleException & ex) {
		//ShowMessage("Desired Gamma File Format is wrong!");
		return RGBGamma_ptr((RGBGamma *) null);
	    }
	};


	RGBGamma_ptr RGBGamma::clone() {
	    double_vector_ptr rclone(new double_vector(*r));
	    double_vector_ptr gclone(new double_vector(*g));
	    double_vector_ptr bclone(new double_vector(*b));
	    if (null != w) {
		double_vector_ptr wclone(new double_vector(*w));
		return RGBGamma_ptr(new RGBGamma(rclone, gclone, bclone, wclone, max, type));
	    } else {
		return RGBGamma_ptr(new RGBGamma(rclone, gclone, bclone, max, type));
	    };

	};
	//==================================================================

    };
};

