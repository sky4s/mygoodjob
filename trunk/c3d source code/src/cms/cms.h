#ifndef CMSH
#define CMSH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


namespace cms {
    class Patch;
    class Spectra;
    class ColorMatchingFunction;
    namespace colorformat {
	namespace logo {
	    class LogoFile;
	};

	class ExcelFileDB;
	class ExcelAccessBase;
	class SimpleExcelAccess;

	class DGLutFile;
	class DGLutFile_;
	class DGLutProperty;
	class RampMeasureFile;

	class Parser;
	class ColorMatchingFunctionFile;

    };
//#define COLORSPACE
#ifdef COLORSPACE
    namespace colorspace {
	class ColorSpace;
	namespace depend {
	    class RGBColor;
	    class Channel;
	    class RGBColorSpace;
	    class MaxValue;
	};
	namespace independ {
	    class CIExyY;
	    class CIEXYZ;
	    class CIELab;
	};
    };
#endif
    namespace lcd {
	namespace calibrate {
	    class BitDepthProcessor;
	    class MeasureCondition;
	    class LCDCalibrator;
	    class Component;
	    class ComponentLUT;
	    class ComponentRelationIF;
	    class ComponentLinearRelation;
	    class ComponentPLRelation;

	    class DimDGLutGenerator;
	    class DimTargetGenerator;
	    namespace algo {
		class ChromaticAroundAlgorithm;
		class CIEuv1960NearestAlgorithm;
		class CIEuv1960NearestAlgorithm_;
	    };
	};
    };
    namespace measure {
	class MeterMeasurement;
	class MeasureResult;
	class IntensityAnalyzerIF;

	namespace meter {
	    class Meter;
	    class CA210;
	    class DGLutFileMeter;
	};
    };
    namespace util {
	class Util;
	class RGBVector;
	class RGBGamma;
	class ByteBuffer;
    };

};

//==============================================================================
//²��cms�ϥΤW������
//==============================================================================
#ifdef COLORSPACE
#define Dep cms::colorspace::depend
#define Indep cms::colorspace::independ

typedef bptr < cms::colorspace::ColorSpace > ColorSpace_ptr;
typedef bptr < Dep::RGBColor > RGB_ptr;
#define nil_RGB_ptr RGB_ptr( (Dep::RGBColor*) null)
typedef barray < RGB_ptr > RGB_array;
typedef std::vector < RGB_ptr > RGB_vector;
typedef bptr < RGB_vector > RGB_vector_ptr;

typedef bptr < Indep::CIExyY > xyY_ptr;
typedef std::vector < xyY_ptr > xyY_vector;
typedef bptr < xyY_vector > xyY_vector_ptr;

typedef bptr < Indep::CIEXYZ > XYZ_ptr;
typedef std::vector < XYZ_ptr > XYZ_vector;
typedef bptr < XYZ_vector > XYZ_vector_ptr;

typedef bptr < Indep::CIELab > Lab_ptr;
typedef std::vector < Lab_ptr > Lab_vector;
typedef bptr < XYZ_vector > Lab_vector_ptr;

typedef std::vector < Dep::Channel > Channel_vector;
typedef bptr < Channel_vector > Channel_vector_ptr;
#endif

typedef bptr < cms::Patch > Patch_ptr;
typedef std::vector < Patch_ptr > Patch_vector;
typedef bptr < Patch_vector > Patch_vector_ptr;
#define nil_Patch_vector_ptr Patch_vector_ptr( (Patch_vector*) null)

typedef bptr < cms::Spectra > Spectra_ptr;
typedef std::vector < Spectra_ptr > Spectra_vector;
typedef bptr < Spectra_vector > Spectra_vector_ptr;

typedef bptr < cms::ColorMatchingFunction > CMF_ptr;

typedef bptr < cms::lcd::calibrate::Component > Component_ptr;
typedef std::vector < Component_ptr > Component_vector;
typedef bptr < Component_vector > Component_vector_ptr;
#define nil_Component_vector_ptr Component_vector_ptr( (Component_vector*) null)


typedef bptr < cms::util::RGBGamma > RGBGamma_ptr;
#define nil_RGBGamma RGBGamma_ptr( (RGBGamma*) null)
//==============================================================================

#endif
 