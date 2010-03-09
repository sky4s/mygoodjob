#include "rgbArray.h"

//C系統文件

//C++系統文件

//其他庫頭文件
#include <boost/lexical_cast.hpp>
//本項目內頭文件
#include <cms/colorspace/rgb.h>
#include <cms/colorformat/excelfile.h>

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
	void RGBVector::storeToExcel(const string & filename,
				     RGB_vector_ptr rgbVector) {
	    using namespace cms::colorformat;
	    using namespace boost;

	    ExcelFileDB::deleteExist(filename);
	    bptr_ < ExcelFileDB > excel(new ExcelFileDB(filename, Create));

	    string_vector_ptr fieldNames =
		ExcelFileDB::makec(4, "Gray Level", "R", "G",
				   "B");
	    excel->createTable("Sheet1", fieldNames);
	    int size = rgbVector->size();
	    for (int x = 0; x != size; x++) {
		RGB_ptr rgb = (*rgbVector)[x];
		string r = lexical_cast < string > (rgb->R);
		string g = lexical_cast < string > (rgb->G);
		string b = lexical_cast < string > (rgb->B);
		string_vector_ptr values =
		    ExcelFileDB::makes(4, lexical_cast < string > (x), r,
				       g,
				       b);
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
    };
}

