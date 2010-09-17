#ifndef DGCODEFILEH
#define DGCODEFILEH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <ADODB.hpp>
#include <DB.hpp>
//�����ؤ��Y���
#include <java/lang.h>
#include "excelfile.h"

namespace cms {
    namespace colorformat {


	class DGLutProperty;
	class DGLutFile:public ExcelAccessBase {
	  private:
	    string_vector_ptr makeValues(int n, Component_ptr c);
	    string_vector_ptr makeValues(int n,
					 Component_ptr c, RGB_ptr rgbGamma, RGB_ptr rgbGammaFix);
	    static const std::string & GammaTable;
	    static const std::string & RawData;
	    static const std::string & Target;
	    const Dep::MaxValue & maxValue;

	  public:
	     DGLutFile(const std::string & filename, Mode mode);
	     DGLutFile(const std::string & filename, Mode mode, const Dep::MaxValue & maxValue);


	    void setProperty(const DGLutProperty & property);
	     bptr < DGLutProperty > getProperty();


	    void setRawData(Component_vector_ptr componentVector,
			    RGBGamma_ptr initialRGBGamma, RGBGamma_ptr finalRGBGamma);
	    void setGammaTable(RGB_vector_ptr dglut);
	    void setTargetXYZVector(XYZ_vector_ptr targetXYZVector);
	    Component_vector_ptr getComponentVector();
	    RGB_vector_ptr getGammaTable();

	    /*
	       �q������Ƥ����o�O0~255���q, ���O���ͪ�gamma�@�w�O����
	       �Ӧp���X���?��ا@�k
	       1. �����q����, �ϸ�Ƭ�0~255
	       2. �����q���쪺gamma, ���O�ʥF��gamma..�N�ʥF�a...
	       �ϥ�����DG Code���ɭ��٬O�i�H�ͥX��.

	       ��ܤ�פG, �ҥH���Ψ�N�h�Y��rgbgamma, ��setRawData�ۤv�h�z */
	};

	class DGLutProperty {
	    friend class DGLutFile;
	  private:

	    static const std::string On;
	    static const std::string Off;
	    static const std::string Native;
	    static const std::string Target;
	    static std::string fileVersion;
	    static std::string productVersion;

	     cms::lcd::calibrate::LCDCalibrator * c;
	     bptr < DGLutFile > d;
	    //DGLutFile *d2;
	    void store(DGLutFile & dglut) const;
	    void DGLutProperty::storeAnalyzer(DGLutFile & dgfile,
					      bptr < cms::measure::IntensityAnalyzerIF >
					      analyzer, const string & prestring) const;
	     std::map < const std::string, string_ptr) propertyMap;
	    void addProperty(const std::string key, string_ptr value);
	    void addProperty(const std::string key, const std::string value);
	    bool initProperty(bptr < DGLutFile > d);
	    bool initProperty(DGLutFile * d);
	    static void fetchVersionInfo();
	  public:
	    //DGLutProperty(bptr < cms::lcd::calibrate::LCDCalibrator > c);
	     DGLutProperty(cms::lcd::calibrate::LCDCalibrator * c);
	     DGLutProperty(bptr < DGLutFile > d);
	     DGLutProperty(DGLutFile * d);
	    string_ptr getProperty(const std::string key);
	    xyY_ptr getReferenceColor(const string & prestring, const Dep::Channel & ch);
	    xyY_ptr getTargetReferenceColor(const Dep::Channel & ch);
	    xyY_ptr getNativeReferenceColor(const Dep::Channel & ch);
	    RGB_ptr getReferenceRGB(const string & prestring);
	    RGB_ptr getTargetReferenceRGB();
	    RGB_ptr getNativeReferenceRGB();
	     bptr < cms::lcd::calibrate::BitDepthProcessor > getBitDepthProcessor();
	};
    };
};
#endif
