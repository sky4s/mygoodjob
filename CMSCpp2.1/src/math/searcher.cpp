#include <includeall.h>
#pragma hdrstop
#include "searcher.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <math.hpp>
//�����ؤ��Y���

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
	    //interstion�����X
	    result = -result;
	    if (result > arrayLength) {
		return -1;
	    } else {
		return result - 2;
	    }
	} else if (result != 0 && result != -1) {
	    //�@�몺���X
	    return result - 1;
	} else {
	    //��0 or -1�����X
	    return result;
	}
    };
    int Searcher::leftNearSequentialSearch(double_vector_ptr a, double key) {
	int result = sequentialSearch(a, key);
	return Searcher::leftNearSequentialSearch0(a->size(), result);
    };

};

