#include <includeall.h>
#pragma hdrstop
#include "rgbArray.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "util.h"

namespace cms {
    namespace util {
	using namespace std;
	using Dep::RGBColor;
	using Dep::MaxValue;
	using namespace cms::colorformat;
	using namespace boost;
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
    };
}

