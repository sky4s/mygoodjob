#include <includeall.h>
#pragma hdrstop
#include "gamma.h"

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件

namespace math {
    using namespace java::lang;
    double GammaFinder::findingGamma(double_vector_ptr normalizeInput,
				     double_vector_ptr normalizeOutput) {
	if (normalizeInput->size() != normalizeOutput->size()) {
	    throw IllegalArgumentException("normalizeInput->size()!= normalizeOutput->size()");
	}

	double denominator = 0;
	for (unsigned int x = 0; x < normalizeInput->size(); x++) {
	    if ((*normalizeInput)[x] == 0) {
		continue;
	    }
	    denominator += Math::sqr(Math::log((*normalizeInput)[x]));
	}
	double numerator = 0;
	for (unsigned int x = 0; x < normalizeInput->size(); x++) {
	    if ((*normalizeInput)[x] == 0 || (*normalizeOutput)[x] == 0) {
		continue;
	    }
	    numerator += Math::log((*normalizeInput)[x]) * Math::log((*normalizeOutput)[x]);
	}
	return numerator / denominator;
    };
    double GammaFinder::findingGamma(double_vector_ptr input,
				     double_vector_ptr output,
				     double inputMinValue,
				     double outputMinValue,
				     double inputMaxValue, double outputMaxValue) {
	if (input->size() != output->size()) {
	    throw IllegalArgumentException("input->size() != output->size()");
	}

	barray < double_vector_ptr > normalize =
	    GammaFinder::normalize(input, output, inputMinValue,
				   outputMinValue, inputMaxValue, outputMaxValue);
	return findingGamma(normalize[0], normalize[1]);
    };

    double_vector_ptr GammaFinder::normalize(double_vector_ptr valueArray,
					     double minValue, double maxValue) {
	double_vector_ptr normal = DoubleArray::minus(valueArray, minValue);
	normal = Math::normalize(normal, maxValue - minValue);
	return normal;
    };

    barray < double_vector_ptr >
	GammaFinder::normalize(double_vector_ptr input,
			       double_vector_ptr output,
			       double inputMinValue, double outputMinValue,
			       double inputMaxValue, double outputMaxValue) {


	if (input->size() != output->size()) {
	    throw IllegalArgumentException("input->size() != output->size()");
	}
	double_vector_ptr normalInput = normalize(input, inputMinValue, inputMaxValue);
	double_vector_ptr normalOutput = normalize(output, outputMinValue, outputMaxValue);

	barray < double_vector_ptr > normalize(new double_vector_ptr[2]);
	normalize[0] = normalInput;
	normalize[1] = normalOutput;
	return normalize;
    };

    double GammaFinder::gamma(double input, double gamma) {
	return Math::pow(input, gamma);
    };
    double_vector_ptr GammaFinder::gamma(double_vector_ptr input, double gamma) {
	int size = input->size();
	double_vector_ptr correcInput(new double_vector(size));
	for (int x = 0; x < size; x++) {
	    (*correcInput)[x] = GammaFinder::gamma((*input)[x], gamma);
	}
	return correcInput;
    };
    double GammaFinder::getGammaExponential(double normalInput, double normalOutput) {
	double gamma = Math::log(normalOutput) / Math::log(normalInput);
	return gamma;
    };
};

