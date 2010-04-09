#include <includeall.h>
#pragma hdrstop
#include "rgbArray.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

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
		RGB_ptr rgb(new RGBColor());
		rgb->setValues(x, x, x);
		result->push_back(rgb);
	    };
	    return result;
	};
	void RGBVector::storeToExcel(const string & filename,
				     RGB_vector_ptr rgbVector) {


	    Util::deleteExist(filename);
	    bptr_ < ExcelFileDB > excel(new ExcelFileDB(filename, Create));

	    string_vector_ptr fieldNames =
		StringVector::fromCString(4, "Gray Level", "R", "G", "B");
	    excel->createTable("Sheet1", fieldNames);
	    int size = rgbVector->size();
	    for (int x = 0; x != size; x++) {
		RGB_ptr rgb = (*rgbVector)[x];
		string r = _toString(rgb->R);
		string g = _toString(rgb->G);
		string b = _toString(rgb->B);
		string xstring = _toString(x);
		string_vector_ptr values =
		    StringVector::fromString(4, xstring, r, g, b);
		excel->insert(fieldNames, values);
	    }

	};
	RGB_vector_ptr RGBVector::clone(RGB_vector_ptr vector) {
	    RGB_vector_ptr result(new RGB_vector(*vector));
	    return result;
	};
	RGB_vector_ptr RGBVector::deepClone(RGB_vector_ptr vector) {
	    int size = vector->size();
	    RGB_vector_ptr result(new RGB_vector(size));
	    for (int x = 0; x != size; x++) {
		(*result)[x] = (*vector)[x]->clone();
	    }
	    return result;
	};
	void RGBVector::changeMaxValue(RGB_vector_ptr vector,
				       const MaxValue & type) {
	    foreach(RGB_ptr rgb, *vector) {
		rgb->changeMaxValue(type);
	    }
	};
	void RGBVector::quantization(RGB_vector_ptr vector,
				     const MaxValue & maxValue) {
	    foreach(RGB_ptr rgb, *vector) {
		rgb->quantization(maxValue);
	    }
	};
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
	RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g,
			   double_vector_ptr b, const double max,
			   const Type type):r(r), g(g), b(b),
	    max(max), type(type) {
	};
	RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g,
			   double_vector_ptr b, double_vector_ptr w,
			   const double max, const Type type):r(r),
	    g(g), b(b), w(w), max(max), type(type) {
	};
	void RGBGamma::storeToExcel(const std::string & filename,
				    RGBGamma_ptr rgbgamma) {


	    Util::deleteExist(filename);
	    bptr_ < ExcelFileDB > excel(new ExcelFileDB(filename, Create));

	    string_vector_ptr fieldNames =
		StringVector::fromCString(4, "Gray Level", "R gamma",
					  "G gamma", "B gamma");
	    excel->createTable("Sheet1", fieldNames);
	    int size = rgbgamma->r->size();

	    for (int x = 0; x != size; x++) {
		(*rgbgamma->r)[x];
		string r = _toString((*rgbgamma->r)[x]);
		string g = _toString((*rgbgamma->g)[x]);
		string b = _toString((*rgbgamma->b)[x]);
		string xstring = _toString(x);
		string_vector_ptr values =
		    StringVector::fromString(4, xstring, r, g, b);
		excel->insert(fieldNames, values);
	    };
	};

	void RGBGamma::storeToDesiredGamma(const std::
					   string & filename,
					   RGBGamma_ptr rgbgamma) {
	    /* TODO : storeToDesiredGamma */
	};

	RGBGamma_ptr RGBGamma::loadFromDesiredGamma(const std::
						    string & filename) {
	    bptr_ < ExcelFileDB >
		excel(new ExcelFileDB(filename, ReadOnly));
	    double_vector_ptr r(new double_vector()),
		g(new double_vector()), b(new double_vector()),
		w(new double_vector());
	    excel->setTableName("Sheet1");
	    try {
		bptr < DBQuery > query = excel->selectAll();
		while (query->hasNext()) {
		    string_vector_ptr result = query->nextResult();
		    w->push_back(_toDouble((*result)[1]));
		    r->push_back(_toDouble((*result)[2]));
		    g->push_back(_toDouble((*result)[3]));
		    b->push_back(_toDouble((*result)[4]));

		};
		//==============================================================
		// 反轉處理
		//==============================================================
		w.reset(new double_vector(w->rbegin(), w->rend()));
		r.reset(new double_vector(r->rbegin(), r->rend()));
		g.reset(new double_vector(g->rbegin(), g->rend()));
		b.reset(new double_vector(b->rbegin(), b->rend()));
		//==============================================================
		RGBGamma_ptr rgbgamma(new RGBGamma(r, g, b, w));
		return rgbgamma;
	    }
	    catch(EOleException & ex) {
		//ShowMessage("Desired Gamma File Format is wrong!");
		return RGBGamma_ptr((RGBGamma*)null);
	    }
	};

	RGBGamma_ptr RGBGamma::clone() {
	    double_vector_ptr rclone(new double_vector(*r));
	    double_vector_ptr gclone(new double_vector(*g));
	    double_vector_ptr bclone(new double_vector(*b));
	    if (null != w) {
		double_vector_ptr wclone(new double_vector(*w));
		return RGBGamma_ptr(new
				    RGBGamma(rclone, gclone, bclone,
					     wclone, max, type));
	    } else {
		return RGBGamma_ptr(new
				    RGBGamma(rclone, gclone, bclone,
					     max, type));
	    };

	};
	//==================================================================

    };
};

