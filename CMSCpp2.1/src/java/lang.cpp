#include "lang.h"

//C系統文件
#include <cmath>
//C++系統文件
#include <limits>

//其他庫頭文件
#include <math.hpp>

//本項目內頭文件

namespace java {
    namespace lang {
	using namespace std;
	using namespace boost;
	//======================================================================
	// Class
	//======================================================================
	 Class::Class(Object & object):object(object), info(typeid(object)) {

	};
	const string_ptr Class::getSimpleName() const {
	    return string_ptr(new string(info.name()));
	};

	const string_ptr Class::getName() const {
	    return string_ptr(new string(info.name()));
	};
	//======================================================================

	//======================================================================
	// Object
	//======================================================================
	int Object::globalID = 0;
	const bool Object::equals(shared_ptr < Object > obj) {
	    return this->objectID == obj->objectID;
	};

	const Class & Object::getClass() const {
	    return c;
	};
	const int Object::hashCode() {
	    return -1;
	};

	const string_ptr Object::toString() const {
	    return getClass().getName();
	};
	const bool Object::isNull() {
	    return null_;
	};
      Object::Object(bool _null_):null_(_null_), c(*this), objectID(globalID++) {
	    //Object::Object(bool _null_):null_(_null_), objectID(globalID++) {
	    name = c.getName();

	};
      Object::Object():null_(false), c(*this), objectID(globalID++) {
	    //Object::Object():null_(false), objectID(globalID++) {
	    name = c.getName();
	};

	const int Object::getObjectID() {
	    return objectID;
	};
	Object_ptr Object::clone() {
	    throw UnsupportedOperationException();
	};
	void Object::finalize() {
	};
	//======================================================================

	//======================================================================
	// Math
	//======================================================================
	double Math::abs(double a) {
	    return std::abs(a);
	};
	double Math::sqrt(double a) {
	    return std::sqrt(a);
	};
	double Math::pow(double a, double b) {
	    return std::pow(a, b);
	};
	double Math::atan2(double y, double x) {
	    return std::atan2(y, x);
	};
	const double Math::PI = 3.141592653589793;
	const double Math::E = 2.718281828459045;
	double Math::cos(double x) {
	    return std::cos(x);
	};
	double Math::acos(double x) {
	    return std::acos(x);
	};
	double Math::sin(double x) {
	    return std::sin(x);
	};
	double Math::sqr(double v) {
	    return v * v;
	}
	double Math::round(double v) {
	    if (v >= 0.0f) {
		return std::floor(v + 0.5f);
	    }
	    return std::ceil(v - 0.5f);
	}
	double Math::floor(double v) {
	    return std::floor(v);
	}
	double Math::roundTo(double v) {
	    return RoundTo(v, 0);
	    //return round(v);
	};
	double Math::log(double v) {
	    return std::log(v);
	};
	double Math::fmod(double x, double y) {
	    return std::fmod(x, y);
	};

	int Math::minIndex(short_array values, int n) {
	    short minValue = std::numeric_limits < short >::max();
	    int minIndex = -1;
	    for (int x = 0; x < n; x++) {
		short v = values[x];
		if (v < minValue) {
		    minValue = v;
		    minIndex = x;
		};
	    };
	    return minIndex;
	};
	SHORT Math::min(short_array values, int n) {
	    int index = minIndex(values, n);
	    return values[index];
	};
	int Math::maxIndex(short_array values, int n) {
	    short maxValue = std::numeric_limits < short >::min();
	    int maxIndex = -1;
	    for (int x = 0; x < n; x++) {
		short v = values[x];
		if (v > maxValue) {
		    maxValue = v;
		    maxIndex = x;
		};
	    };
	    return maxIndex;
	};
	short Math::max(short_array values, int n) {
	    int index = maxIndex(values, n);
	    return values[index];
	};

	int Math::minIndex(double_array values, int n) {
	    double minValue = std::numeric_limits < double >::max();
	    int minIndex = -1;
	    for (int x = 0; x < n; x++) {
		double v = values[x];
		if (v < minValue) {
		    minValue = v;
		    minIndex = x;
		};
	    };
	    return minIndex;
	};
	double Math::min(double_array values, int n) {
	    int index = minIndex(values, n);
	    return values[index];
	};
	int Math::maxIndex(double_array values, int n) {
	    double maxValue = std::numeric_limits < double >::min();
	    int maxIndex = -1;
	    for (int x = 0; x < n; x++) {
		double v = values[x];
		if (v > maxValue) {
		    maxValue = v;
		    maxIndex = x;
		};
	    };
	    return maxIndex;
	};
	double Math::max(double_array values, int n) {
	    int index = maxIndex(values, n);
	    return values[index];
	};
	double Math::min(double a, double b) {
	    return std::min(a, b);
	};
	double Math::max(double a, double b) {
	    return std::max(a, b);
	};
#ifdef TNT_LIB
	double Math::max(double1D_ptr values) {
	    double max = std::numeric_limits < double >::min();
	    for (int x = 0; x < values->dim1(); x++) {
		double d = (*values)[x];
		max = Math::max(max, d);
	    }
	    return max;
	};
#endif
	int Math::maxIndex(double_vector_ptr values) {
	    double maxValue = std::numeric_limits < double >::min();
	    int maxIndex = -1;
	    int size = values->size();
	    for (int x = 0; x != size; x++) {
		double v = (*values)[x];
		if (v > maxValue) {
		    maxValue = v;
		    maxIndex = x;
		};
	    };
	    return maxIndex;
	};
	int Math::minIndex(double_vector_ptr values) {
	    double minValue = std::numeric_limits < double >::max();
	    int minIndex = -1;
	    int size = values->size();
	    for (int x = 0; x != size; x++) {
		double v = (*values)[x];
		if (v < minValue) {
		    minValue = v;
		    minIndex = x;
		};
	    };
	    return minIndex;
	};
	double Math::max(double_vector_ptr values) {
	    int index = maxIndex(values);
	    return (*values)[index];
	};
	double Math::min(double_vector_ptr values) {
	    int index = minIndex(values);
	    return (*values)[index];
	};
	double_vector_ptr Math::normalize(double_vector_ptr original, double normal) {
	    for (unsigned int x = 0; x < original->size(); x++) {
		(*original)[x] /= normal;
	    }
	    return original;
	};

	double Math::cubeRoot(double x) {

	    double fr, r;
	    int ex, shx;

	    // Argument reduction
	    fr = frexp(x, &ex);	// separate into mantissa and exponent
	    //fr = (Double) p.get(0);
	    //ex = (Integer) p.get(1);
	    shx = ex % 3;

	    if (shx > 0) {
		shx -= 3;	// compute shx such that (ex - shx) is divisible by 3
	    }

	    ex = (ex - shx) / 3;	// exponent of cube root
	    fr = ldexp(fr, shx);

	    // 0.125 <= fr < 1.0

	    // Use quartic rational polynomial with error < 2^(-24)

	    fr = (((((45.2548339756803022511987494 * fr +
		      192.2798368355061050458134625) * fr +
		     119.1654824285581628956914143) * fr +
		    13.43250139086239872172837314) * fr + 0.1636161226585754240958355063)
		  /
		  ((((14.80884093219134573786480845 * fr +
		      151.9714051044435648658557668) * fr +
		     168.5254414101568283957668343) * fr +
		    33.9905941350215598754191872) * fr + 1.0));
	    r = ldexp(fr, ex);	// 24 bits of precision
	    return r;
	}
	double Math::exp(double x) {
	    return std::exp(x);
	}
	double Math::atan2deg(double b, double a) {
	    double h;

	    if (a == 0 && b == 0) {
		h = 0;
	    } else {
		h = Math::atan2(a, b);
	    }
	    h *= (180. / Math::PI);

	    while (h > 360.) {
		h -= 360.;
	    }

	    while (h < 0) {
		h += 360.;
	    }

	    return h;

	}
	//======================================================================

	//======================================================================
	// Exception
	//======================================================================
	Exception::Exception() {
	};
      Exception::Exception(string message):message(message) {
	};
	string & Exception::toString() {
	    return message;
	};


	RuntimeException::RuntimeException() {
	};
      RuntimeException::RuntimeException(string message):Exception(message) {

	};

	IllegalStateException::IllegalStateException() {
	};
      IllegalStateException::IllegalStateException(string message):RuntimeException(message)
	{

	};

	IllegalArgumentException::IllegalArgumentException() {
	};
      IllegalArgumentException::IllegalArgumentException(string message):RuntimeException(message)
	{

	};

	UnsupportedOperationException::UnsupportedOperationException() {
	};
      UnsupportedOperationException::UnsupportedOperationException(string message):RuntimeException(message)
	{

	};
	IndexOutOfBoundsException::IndexOutOfBoundsException() {
	};
      IndexOutOfBoundsException::IndexOutOfBoundsException(string message):RuntimeException(message)
	{

	};
	//======================================================================


    };
};






