#include <includeall.h>
#pragma hdrstop
#include "core.h"

#define CIE_1931_2DEG "ciexyz31_1.txt"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    using namespace boost;
    using namespace Indep;
    using namespace java::lang;
    using namespace cms::colorformat;

    //==========================================================================
    const CMF_ptr ColorMatchingFunction::
	//CIE_1931_2DEG_XYZ = getColorMatchingFunction("ciexyz31_1.txt");
	/*CIE_1931_2DEG_XYZ =
	   (true == FileExists(CIE_1931_2DEG)) ?
	   getColorMatchingFunction(CIE_1931_2DEG) : CMF_ptr(new ColorMatchingFunction()); */
     CIE_1931_2DEG_XYZ = CMF_ptr(new ColorMatchingFunction());

     ColorMatchingFunction::
	ColorMatchingFunction(Spectra_vector_ptr
			      spectraVector):spectraVector(spectraVector), index(0) {
    };
  ColorMatchingFunction::ColorMatchingFunction():index(0) {
    };
#ifdef TNT_LIB
    double1D_ptr ColorMatchingFunction::getData() {
	return (*spectraVector)[index]->data;
    };

    double1D_ptr ColorMatchingFunction::getData(int index) {
	return (*spectraVector)[index]->data;
    };
#endif
    int ColorMatchingFunction::getEnd() const {
	return (*spectraVector)[index]->end;
    };
    int ColorMatchingFunction::getInterval() const {
	return (*spectraVector)[index]->interval;
    };
    int ColorMatchingFunction::getStart() const {
	return (*spectraVector)[index]->start;
    };
    Spectra_ptr ColorMatchingFunction::getSpectra(int index) const {
	return (*spectraVector)[index];
    };
    CMF_ptr ColorMatchingFunction::getColorMatchingFunction(const string & filename) {
	if (!FileExists(filename.c_str())) {
	    throw IllegalStateException("!FileExists(" + filename + ")");
	}
	ColorMatchingFunctionFile file(filename);
	return file.getColorMatchingFunction();
    };
    //==========================================================================
    // CorrelatedColorTemperature
    //==========================================================================
    bptr < CIExyY > CorrelatedColorTemperature::CCT2DIlluminantxyY(double tempK) {
	//using namespace std;
	double x = 0.0, y;
	double T, T2, T3;

	// No optimization provided.
	T = tempK;
	T2 = T * T;		// Square
	T3 = T2 * T;		// Cube

	// For correlated color temperature (T) between 4000K and 7000K:

	if (T >= 4000. && T <= 7000.) {
	    x = -4.6070 * (1E9 / T3) + 2.9678 * (1E6 / T2) + 0.09911 * (1E3 / T) + 0.244063;
	} else
	    // or for correlated color temperature (T) between 7000K and 25000K:

	if (T > 7000.0 && T <= 25000.0) {
	    x = -2.0064 * (1E9 / T3) + 1.9018 * (1E6 / T2) + 0.24748 * (1E3 / T) + 0.237040;
	} else {
	    //string msg = "invalid temp: " + tempK +
	    //    ", tempK must in 4000~25000K";
	    //throw IllegalArgumentException();
	    return bptr < CIExyY > (new CIExyY(0, 0, 1.0));
	}

	// Obtain y(x)
	y = -3.000 * (x * x) + 2.870 * x - 0.275;

	// wave factors (not used, but here for futures extensions)
	// M1 = (-1.3515 - 1.7703*x + 5.9114 *y)/(0.0241 + 0.2562*x - 0.7341*y);
	// M2 = (0.0300 - 31.4424*x + 30.0717*y)/(0.0241 + 0.2562*x - 0.7341*y);

	// Fill WhitePoint struct
	bptr < CIExyY > xyY(new CIExyY(x, y, 1.0));
	return xyY;
    };

    xyY_ptr CorrelatedColorTemperature::CCT2BlackbodyxyY(double tempK) {
	Spectra_ptr blackbody = getSpectraOfBlackbodyRadiator(tempK);
	XYZ_ptr XYZ = blackbody->getXYZ();
	XYZ->normalizeY();
	xyY_ptr xyY(new CIExyY(XYZ));
	return xyY;
    };

    double CorrelatedColorTemperature::xy2CCTByMcCamyFloat(bptr < CIExyY > xyY) {
	double n = (xyY->x - 0.332) / (xyY->y - 0.1858);
	double sqr = Math::sqr(n);
	double cct = -449 * sqr * n + 3525 * sqr - 6823.3 * n + 5520.33;
	return cct;
    }

    double_array CorrelatedColorTemperature::getdudvWithDIlluminant(XYZ_ptr XYZ) {
	xyY_ptr xyY(new CIExyY(XYZ));
	double cct = xy2CCTByMcCamyFloat(xyY);
	xyY_ptr dxyY = CCT2DIlluminantxyY(cct);
	return dxyY->getDeltauv(xyY);
    };

    double CorrelatedColorTemperature::getduvWithDIlluminant(XYZ_ptr XYZ) {
	double_array duv = getdudvWithDIlluminant(XYZ);
	double d = Math::sqrt(Math::sqr(duv[0]) + Math::sqr(duv[1]));
	if (duv[0] < 0 || duv[1] > 0) {
	    d = -d;
	}
	return d;
    }
    Spectra_ptr CorrelatedColorTemperature::
	getSpectraOfBlackbodyRadiator(double tempK, int start, int end, int interval) {
	int size = (end - start) / interval + 1;
	double1D_ptr data(new double1D(size, new double[size]));
	for (int x = 0; x < size; x++) {
	    double lambda = (start + x * interval) * 1E-9;
	    (*data)[x] = c1 /
		(Math::pow(lambda, 5) * (Math::pow(Math::E, c2 / (tempK * lambda)) - 1));
	}
	Spectra_ptr spectra(new Spectra(_toString(tempK) + "K", start, end, interval, data));
	spectra->normalizeDataToMax();
	return spectra;
    };
    Spectra_ptr CorrelatedColorTemperature::getSpectraOfBlackbodyRadiator(double tempK) {
	return getSpectraOfBlackbodyRadiator(tempK, 360, 830, 1);
    };
    const double CorrelatedColorTemperature::c = 2.99792458E8;
    const double CorrelatedColorTemperature::h = 6.626176E-34;
    const double CorrelatedColorTemperature::k = 1.380662E-23;
    const double CorrelatedColorTemperature::c1 = 2 * Math::PI * h * Math::sqr(c);
    const double CorrelatedColorTemperature::c2 = h * c / k;
    bool CorrelatedColorTemperature::isCCTMeaningful(xyY_ptr xyY) {
	XYZ_ptr XYZ = xyY->toXYZ();
	double duv = getduvWithBlackbody(XYZ);
	return duv <= 5e-2;
    };
    double CorrelatedColorTemperature::getduvWithBlackbody(XYZ_ptr XYZ) {
	double_array duv = getdudvWithBlackbody(XYZ);
	double d = Math::sqrt(Math::sqr(duv[0]) + Math::sqr(duv[1]));
	if (duv[0] < 0 || duv[1] > 0) {
	    d = -d;
	}
	return d;
    }
    double_array CorrelatedColorTemperature::getdudvWithBlackbody(XYZ_ptr XYZ) {
	double cct = xy2CCTByMcCamyFloat(xyY_ptr(new CIExyY(XYZ)));
	//getSpectraOfBlackbodyRadiator(cct, 380, 730, 1);

	Spectra_ptr spectra = getSpectraOfBlackbodyRadiator(cct, 380, 780, 1);
	XYZ_ptr blackbodyXYZ = spectra->getXYZ();
	//xyY_ptr bbxyY = CIExyY::fromXYZ(blackbodyXYZ);
	xyY_ptr bbxyY(new CIExyY(blackbodyXYZ));
	//xyY_ptr xyY = CIExyY::fromXYZ(XYZ);
	xyY_ptr xyY(new CIExyY(XYZ));
	double_array duv = bbxyY->getDeltauv(xyY);
	return duv;
    }
    //==========================================================================
    // Illuminant
    //==========================================================================
#ifdef TNT_LIB
    double1D_ptr Illuminant::getData() {
	return data;
    };
#endif
    Illuminant::Illuminant() {
    };
    int Illuminant::getEnd() const {
	return end;
    };
    int Illuminant::getInterval() const {
	return interval;
    };
    int Illuminant::getStart() const {
	return start;
    };
    const Illuminant Illuminant::D50;	// = Illuminant();
    const Illuminant Illuminant::D65;	// = Illuminant();
    const Illuminant Illuminant::C;	// = Illuminant();
    XYZ_ptr Illuminant::getXYZ() const {
	XYZ_ptr XYZ = getXYZ(*this);
	 return XYZ;
    };

    const XYZ_ptr Illuminant::getXYZ(const Illuminant & illuminant) {
	using namespace Indep;
	//D50();                        // Illuminant();
	XYZ_ptr XYZ;
	if (&illuminant == null) {
	    throw new IllegalArgumentException("illuminant == null");
	} else if (&illuminant == &Illuminant::D50) {
	    XYZ = XYZ_ptr(new CIEXYZ(0.964221, 1, 0.825210, Normal1));
	} else if (&illuminant == &Illuminant::D65) {
	    XYZ = XYZ_ptr(new CIEXYZ(0.950471, 1, 1.088830, Normal1));
	} else if (&illuminant == &Illuminant::C) {
	    XYZ = XYZ_ptr(new CIEXYZ(0.980741, 1, 1.182320, Normal1));
	}
	return XYZ;
    };
    //==========================================================================
#ifdef TNT_LIB
  Spectra::Spectra(const std::string & name, int start, int end, int interval, double1D_ptr data):name(name), start(start), end(end), interval(interval),
	data(data)
    {

    }
    XYZ_ptr Spectra::getXYZ() {
	if (null == CIE1931XYZ) {
	    CIE1931XYZ = getXYZ(*ColorMatchingFunction::CIE_1931_2DEG_XYZ);
	}
	return CIE1931XYZ;
    }
    XYZ_ptr Spectra::getXYZ(const ColorMatchingFunction & cmf) {
	return getXYZFill(cmf);
    };
    double1D_ptr Spectra::getData() {
	return data;
    };
    int Spectra::getEnd() const {
	return end;
    };
    int Spectra::getInterval() const {
	return interval;
    };
    int Spectra::getStart() const {
	return start;
    };
    void Spectra::normalizeDataToMax() {
	//checkReadOnly();
	double max = Math::max(data);
	normalizeData(max);
    };
    void Spectra::normalizeData(double normal) {
	for (int x = 0; x < data->dim1(); x++) {
	    (*data)[x] = ((*data)[x] / normal);
	}
    };
    XYZ_ptr Spectra::getXYZFill(const
				ColorMatchingFunction & cmf) {
	double1D_ptr modifyData = doFillPurlieus(cmf.getStart(),
						 cmf.getEnd())->getData();
	double_array XYZValues(new double[3]);
	for (int x = 0; x < 3; x++) {
	    Spectra_ptr cmfSpectra = cmf.getSpectra(x);
	    XYZValues[x] =
		.683002 * sigma(cmfSpectra->start,
				cmfSpectra->end,
				modifyData,
				interval, cmfSpectra->data, cmfSpectra->interval) * interval;
	}
	XYZ_ptr result(new CIEXYZ(XYZValues));
	return result;
    };
    Spectra_ptr Spectra::doFillPurlieus(int start, int end) {
	int leftFill = (this->start - start) / interval;
	int rightFill = (end - this->end) / interval;
	double1D_ptr modifyData = fillPurlieusData(data, leftFill,
						   rightFill);
	Spectra_ptr spectra(new Spectra(this->name, start, end, this->interval, modifyData));
	return spectra;
    };
    double1D_ptr Spectra::fillPurlieusData(const double1D_ptr data, int leftBorder, int rightBorder) {
	using namespace math;
	int dataSize = data->dim1();
	int resultSize = dataSize + leftBorder + rightBorder;
	double1D_ptr result(new double1D(resultSize, new double
					 [resultSize]));
	double first = fillZero ? 0 : (*data)[0];
	double last = fillZero ? 0 : (*data)[dataSize - 1];
	for (int x = 0; x < leftBorder; x++) {
	    (*result)[x] = first;
	}

	int srcPos = leftBorder < 0 ? -leftBorder : 0;
	int destPos = leftBorder < 0 ? 0 : leftBorder;
	int length = leftBorder < 0 ? leftBorder + dataSize : dataSize;
	length = rightBorder < 0 ? length + rightBorder : length;
	//System.arraycopy(data, srcPos, result, destPos, length);
	DoubleArray::arraycopy(data, srcPos, result, destPos, length);
	for (int x = leftBorder + dataSize; x < resultSize; x++) {
	    (*result)[x] = last;
	}
	return result;
    };
    bool Spectra::fillZero = false;
    double Spectra::sigma(int start, int end, double1D_ptr data1, int
			  interval1, double1D_ptr data2, int
			  interval2) {
	//double[] a = null, b = null;
	double1D_ptr a, b;
	int step = 0, size = 0;
	if (data1->dim1() > data2->dim1()) {
	    a = data2;
	    b = data1;
	    step = interval2 / interval1;
	    size = ((end - start) / interval2) + 1;
	} else {
	    a = data1;
	    b = data2;
	    step = interval1 / interval2;
	    size = ((end - start) / interval1) + 1;
	}

	double total = 0.0;
	for (int x = 0; x < size; x++) {
	    total += (*a)[x] * (*b)[x * step];
	}
	return total;
    };
#endif
    //==========================================================================
    RGBPatchMap Target::processPatchMap(Patch_vector_ptr patchList) {
	RGBPatchMap patchMap;
	foreach(Patch_ptr p, *patchList) {
	    RGB_ptr rgb = p->getRGB();
	    patchMap.insert(make_pair(rgb, p));
	}
	return patchMap;
    };
  Target::Target(Patch_vector_ptr patchList):patchList(patchList) {

    };
    string_ptr Target::getFilename() {
	return filename;
    };
    Patch_vector_ptr Target::getPatchList() {
	return patchList;
    };

    Patch_ptr Target::getPatch(double r, double g, double b) {
	if (keyRGB == null) {
	    keyRGB = getKeyRGB();
	}
	keyRGB->setValues(r, g, b);
	return getPatch(keyRGB);
    };
    Patch_ptr Target::getPatch(int index) {
	return (*patchList)[index];
    };
    Patch_ptr Target::getPatch(RGB_ptr rgb) {
	return patchMap[rgb];
    };
    RGB_ptr Target::getKeyRGB() {
	RGB_ptr clone = (*patchList)[0]->getRGB()->clone();
	return clone;
    };
    int Target::size() {
	return patchList->size();
    };
};

