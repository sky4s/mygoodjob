#include <includeall.h>
#pragma hdrstop
#include "searcher.h"

//C系統文件

//C++系統文件

//其他庫頭文件
#include <math.hpp>
//本項目內頭文件

namespace math {

    int Searcher::sequentialSearch(double_vector_ptr a, double key) {
	double prev = NaN;
	for (unsigned int x = 0; x != a->size(); x++) {
	    double v = (*a)[x];
	    if (v == key) {
		return x;
	    } else if (!IsNan(prev) && key > prev && key < v) {
		return -(static_cast < int >(x) + 1);
	    };
	    prev = v;
	}
	return -1;

    };
    int Searcher::inverseSequentialSearch(double_vector_ptr a, double key) {
	double prev = NaN;
	for (unsigned int x = a->size() - 1; x != -1; x--) {
	    double v = (*a)[x];
	    if (v == key) {
		return x;
	    } else if (!IsNan(prev) && key < prev && key < v) {
		return -(static_cast < int >(x) + 1);
	    };
	    prev = v;
	}
	return -1;

    };
    int Searcher::sequentialSearch(int_vector_ptr a, int key) {
	int prev = NaN;
	for (unsigned int x = 0; x != a->size(); x++) {
	    int v = (*a)[x];
	    if (v == key) {
		return x;
	    } else if (!IsNan(prev) && key > prev && key < v) {
		return -(static_cast < int >(x) + 1);
	    };
	    prev = v;
	}
	return -1;
    };

    int_vector_ptr Searcher::leftNearSequentialSearchAll(double_vector_ptr a, double key) {
	int_vector_ptr result(new int_vector(2));
	int search = sequentialSearch(a, key);
	(*result)[0] = leftNearSequentialSearch0(a->size(), search);
	(*result)[1] = search;

	return result;
    };
    int Searcher::leftNearSequentialSearch0(int arrayLength, int binarySearchResult) {
	int result = binarySearchResult;
	if (result < -1) {
	    //interstion的場合
	    result = -result;
	    if (result > arrayLength) {
		return -1;
	    } else {
		return result - 2;
	    }
	} else if (result != 0 && result != -1) {
	    //一般的場合
	    return result - 1;
	} else {
	    //為0 or -1的場合
	    return result;
	}
    };
    int Searcher::leftNearSequentialSearch(double_vector_ptr a, double key) {
	int result = sequentialSearch(a, key);
	return Searcher::leftNearSequentialSearch0(a->size(), result);
    };
    int Searcher::leftNearInverseSequentialSearch(double_vector_ptr a, double key) {
	int result = inverseSequentialSearch(a, key);
	return Searcher::leftNearSequentialSearch0(a->size(), result);
    };

};

