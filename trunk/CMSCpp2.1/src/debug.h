#ifndef DEBUGH
#define DEBUGH

#define DEBUG_FILE "debug.txt"
#define METER_FILE "debug.xls"
#define DEBUG_DIR  "debug/"

#define DEBUG_NEWFUNC_FILE "new.txt"

#define DEBUG_CCTLUT		//CCT功能的debug功能開啟
//#define DEBUG_CCTLUT_NEWMETHOD	//新方法的過程debug功能開啟

//#define DEBUG_FINDWHITE //find white過程的紀錄
//#define DEBUG_TARGETWHITE //Target White測試功能的開啟

//是否支援在tcon input狀況下, 能中止量測;
//若能中止意味著會跳出量測視窗來阻擋, 因為中止功能要靠視窗去攔截按鍵
//#define DEBUG_STOP_TCONINPUT

//==============================================================================
// CCT巨集
//==============================================================================
#ifdef DEBUG_CCTLUT
#define _s std::string
#define debug_dir _s(DEBUG_DIR)

#define MAKE_DEBUG_DIR() \
if (!DirectoryExists(DEBUG_DIR)) { \
    CreateDir(DEBUG_DIR); \
}

#define STORE_COMPONENT( filename , result ) \
MAKE_DEBUG_DIR(); \
ComponentFetcher::storeToExcel(debug_dir + _s(filename), result);

#define STORE_RGBGAMMA( filename , result ) \
MAKE_DEBUG_DIR(); \
cms::lcd::calibrate::RGBGamma::storeToExcel(debug_dir + _s(filename), result);

#define STORE_RGBVECTOR( filename , result ) \
MAKE_DEBUG_DIR(); \
RGBVector::storeToExcel(debug_dir + _s(filename), result);

#define STORE_DOUBLE_VECTOR( filename , result ) \
MAKE_DEBUG_DIR(); \
DoubleArray::storeToExcel(debug_dir + _s(filename), result);

#define STORE_XYZXY_VECTOE( filename, result ) \
MAKE_DEBUG_DIR(); \
Util::storeXYZxyVector(debug_dir + _s(filename), result);

#else
#define STORE_COMPONENT( filename , result )
#define STORE_RGBGAMMA( filename , result )
#define STORE_RGBVECTOR( filename , result )
#define STORE_DOUBLE_VECTOR( filename , result )
#define STORE_XYZXY_VECTOE( filename, result )
#endif
//==============================================================================

//==============================================================================
// white finder巨集
//==============================================================================
#ifdef DEBUG_FINDWHITE
#define BEGIN_STORE( filename ) \
		Util::deleteExist(filename);\
		string_vector_ptr fieldNames =\
		    StringVector::fromCString(5, "R", "G", "B", "x", "y");\
		bptr < SimpleExcelAccess >\
		    access(new SimpleExcelAccess(filename, Create,\
					     fieldNames));
#define STORE_RGBXY( rgb , xyY )\
		    access->insert(StringVector::\
				   fromString(5, _toString(rgb->R),\
                                              _toString(rgb->G),\
                                              _toString(rgb->B),\
					      _toString(xyY->x),\
					      _toString(xyY->y)));

#else
#define BEGIN_STORE( filename )
#define STORE_RGBXY( rgb , xyY )
#endif
//==============================================================================

#endif

