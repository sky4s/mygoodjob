#include "doublearray.h"

namespace math {
    string_ptr DoubleArray::toString(double_array m, int n) {
	using namespace std;
	string_ptr str(new string());
	for (int x = 0; x != n; x++) {
	    //str->insert(m[x]);
	};
	return str;
    };

    double_array DoubleArray::plus(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] + v;
	}
	return array;
    };

    double_array DoubleArray::minus(double_array v1, double_array v2,
				    int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] - v2[i];
	}
	return array;
    };

    double_array DoubleArray::times(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] * v;
	}
	return array;
    }
};

