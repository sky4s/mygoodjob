#ifndef MAXMATRIXANALYZERH
#define MAXMATRIXANALYZERH

//C�t�Τ��

//C++�t�Τ��
#include <string>
//��L�w�Y���
#include <vcl.h>

//�����ؤ��Y���
#include <cms/colorformat/excelfile.h>
#include <cms/measure/analyzer.h>

namespace ca210api {
    class CA210API;
};

namespace cms {

    namespace measure {
	using namespace std;

#ifdef TNT_LIB
	/*
	   �Q�ίx�}�B�����XIntensity
	 */
	class MaxMatrixIntensityAnalyzer:public IntensityAnalyzerIF {
	    friend class IntensityAnayzer;
	  protected:
	     double2D_ptr inverseMatrix;
	    double2D_ptr targetRatio;
	    double2D_ptr rgbValues;
	     bptr < MeterMeasurement > mm;
	    XYZ_ptr XYZ;
	    XYZ_ptr rXYZ, gXYZ, bXYZ, wXYZ;
	    RGB_ptr referenceRGB;

	  public:
	     MaxMatrixIntensityAnalyzer(bptr < MeterMeasurement > mm);
	     MaxMatrixIntensityAnalyzer();

	    RGB_ptr getIntensity(RGB_ptr rgb);
	    RGB_ptr getIntensity(XYZ_ptr XYZ);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, XYZ_ptr measureXYZ);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	    void setReferenceRGB(RGB_ptr rgb);
	    bool isInverseMatrixNull();
	     bptr < MeterMeasurement > getMeterMeasurement();
	    double2D_ptr getTargetRatio();
	    static bptr < MaxMatrixIntensityAnalyzer > getReadyAnalyzer(bptr <
									MeterMeasurement > mm,
									int rMax, int gMax,
									int bMax);
	    static bptr < MaxMatrixIntensityAnalyzer > getReadyAnalyzer(XYZ_ptr rXYZ, XYZ_ptr gXYZ,
									XYZ_ptr bXYZ, XYZ_ptr wXYZ);
	    static bptr < MaxMatrixIntensityAnalyzer > getReadyAnalyzer(bptr <
									MeterMeasurement > mm,
									XYZ_ptr rXYZ, XYZ_ptr gXYZ,
									XYZ_ptr bXYZ, XYZ_ptr wXYZ);
	};

	/*
	   �ΨӦX��CA-210�PMaxMatrix��ؤ�k�Ӥ��RIntensity
	   ��ڤW��X���Ȭ�CA-210��, MaxMatrix����X�ȷ|�t�~�s�b�ɮ�
	 */
	class IntensityAnayzer:public IntensityAnalyzerIF {
	  private:
	    bptr < MaxMatrixIntensityAnalyzer > matrix;
	    bptr < CA210IntensityAnalyzer > ca210;
	    bptr < cms::colorformat::SimpleExcelAccess > excel;
	    string_vector_ptr fieldNames;
	    int no;
	    XYZ_ptr XYZ;
	  public:
	     IntensityAnayzer(bptr < MaxMatrixIntensityAnalyzer >
			      matrix, bptr < CA210IntensityAnalyzer > ca210);
	    RGB_ptr getIntensity(RGB_ptr rgb);
	    XYZ_ptr getCIEXYZ();
	    XYZ_ptr getCIEXYZOnly(RGB_ptr rgb);
	    void setupComponent(const Dep::Channel & ch, RGB_ptr rgb);
	    void enter();
	    void beginAnalyze();
	    void endAnalyze();
	    void setWaitTimes(int waitTimes);
	    int getWaitTimes();
	    xyY_ptr getReferenceColor();
	    xyY_ptr getPrimaryColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB();
	     bptr < MeterMeasurement > getMeterMeasurement();
	};
#endif
    };
};

#endif

