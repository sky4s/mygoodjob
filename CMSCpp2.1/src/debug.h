#ifndef DEBUGH
#define DEBUGH

#define DEBUG_FILE "debug.txt"
#define METER_FILE "debug.xls"
#define DEBUG_DIR  "debug/"

//==============================================================================
// debug¥Î¥¨¶°
//==============================================================================
#ifdef _DEBUG
#include <cms/util/rgbarray.h>
#define _ std::string
#define debug_dir _(DEBUG_DIR)

#define MAKE_DEBUG_DIR() \
if (!DirectoryExists(DEBUG_DIR)) { \
    CreateDir(DEBUG_DIR); \
}
#define STORE_COMPONENT( filename , result ) \
MAKE_DEBUG_DIR(); \
ComponentFetcher::storeToExcel(debug_dir + _(filename), result);

#define STORE_RGBGAMMA( filename , result ) \
MAKE_DEBUG_DIR(); \
cms::lcd::calibrate::RGBGamma::storeToExcel(debug_dir + _(filename), result);

#define STORE_RGBVECTOR( filename , result ) \
MAKE_DEBUG_DIR(); \
RGBVector::storeToExcel(debug_dir + _(filename), result);

#define STORE_DOUBLE_VECTOR( filename , result ) \
MAKE_DEBUG_DIR(); \
DoubleArray::storeToExcel(debug_dir + _(filename), result);

#else
#define STORE_COMPONENT( filename , result )
#define STORE_RGBGAMMA( filename , result )
#define STORE_RGBVECTOR( filename , result )
#define STORE_DOUBLE_VECTOR( filename , result )
#endif
//==============================================================================

#endif
 