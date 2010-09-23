#ifndef COREH
#define COREH

//C系統文件

//C++系統文件
#include <vcl.h>
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <vector>
#ifdef __BORLANDC__
# pragma pack(pop)
#endif
//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <cms/cms.h>

namespace cms {
    class SpectraIF {
      public:
#ifdef TNT_LIB
	virtual double1D_ptr getData() = 0;
#endif
	virtual int getEnd() const = 0;
	virtual int getInterval() const = 0;
	virtual int getStart() const = 0;
    };

    class ColorMatchingFunction:public jObject, SpectraIF {
      private:
	int index;
	Spectra_vector_ptr spectraVector;
	 ColorMatchingFunction();
      public:
	static const CMF_ptr CIE_1931_2DEG_XYZ;
	 ColorMatchingFunction(Spectra_vector_ptr spectraVector);

#ifdef TNT_LIB
	double1D_ptr getData(int index);
	double1D_ptr getData();
#endif
	void setIndex(int index);
	int getEnd() const;
	int getInterval() const;
	int getStart() const;
	Spectra_ptr getSpectra(int index) const;
      private:
	static CMF_ptr getColorMatchingFunction(const std::string & filename);
    };

    enum CCTMethod {
	McCamyInt, McCamyFloat, Exp, ExpCCTOver50k, Robertson
    };

    class CorrelatedColorTemperature:public jObject {
      public:
	static xyY_ptr CCT2DIlluminantxyY(double tempK);
	static xyY_ptr CCT2BlackbodyxyY(double tempK);
	static double xy2CCTByMcCamyFloat(xyY_ptr xyY);
	static double_array getdudvWithDIlluminant(XYZ_ptr XYZ);
	static double getduvWithDIlluminant(XYZ_ptr XYZ);
	static Spectra_ptr getSpectraOfBlackbodyRadiator(double tempK,
							 int start, int end, int interval);
	static Spectra_ptr getSpectraOfBlackbodyRadiator(double tempK);
	static bool isCCTMeaningful(xyY_ptr xyY);
	static double getduvWithBlackbody(XYZ_ptr XYZ);
	static double_array getdudvWithBlackbody(XYZ_ptr XYZ);
      private:
	static const double c;
	static const double h;
	static const double k;
	static const double c1;
	static const double c2;
    };
    class Illuminant:public jObject, SpectraIF {
      private:
	int start, end, interval;
#ifdef TNT_LIB
	double1D_ptr data;
#endif
      public:
#ifdef TNT_LIB
	 double1D_ptr getData();
#endif
	int getEnd() const;
	int getInterval() const;
	int getStart() const;

	static const Illuminant & D50;
	static const Illuminant & D65;
	static const Illuminant & C;
    };
#ifdef TNT_LIB
    class Spectra:public jObject, SpectraIF /*, util::NameIF */  {
	friend class ColorMatchingFunction;
      protected:
	const std::string & name;
	int start, end, interval;

	double1D_ptr data;
	XYZ_ptr CIE1931XYZ;
      public:
	 Spectra(const std::string & name, int start, int end, int interval, double1D_ptr data);
	XYZ_ptr getXYZ();
	XYZ_ptr getXYZ(const ColorMatchingFunction & cmf);
	double1D_ptr getData();
	int getEnd() const;
	int getInterval() const;
	int getStart() const;
	void normalizeDataToMax();
	void normalizeData(double normal);
      private:
	 XYZ_ptr getXYZFill(const ColorMatchingFunction & cmf);
	Spectra_ptr doFillPurlieus(int start, int end);
	static double1D_ptr fillPurlieusData(const double1D_ptr data,
					     int leftBorder, int rightBorder);
	static bool fillZero;
	static double sigma(int start, int end,
			    double1D_ptr data1, int interval1, double1D_ptr data2, int interval2);
    };
#endif


    class Target:public jObject {
    };

    class ValuePropertyIF {
      public:
	virtual double_array getValues() = 0;
	virtual void setValues(double_array values) = 0;
	virtual double_array getValues(double_array values) = 0;
    };
};
#endif

