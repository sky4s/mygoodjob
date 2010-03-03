#include "rgbArray.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace util {
	using namespace std;
	using Dep::RGBColor;
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
    };
}

