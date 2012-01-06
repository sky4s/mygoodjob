/*-------------------------------------------------------------------------------*/
/* EyeOne	C-Style	API                                                            */
/* This API provides high-level methods to access	the EyeOne device              */
/*                                                                               */
/* Version 2.0                                                                   */
/*                                                                               */
/* Copyright (c) 2003 by GretagMacbeth AG Switzerland.                           */
/*                                                                               */
/* ALL RIGHTS RESERVED.                                                          */
/*                                                                               */
/* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS             */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED             */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE            */
/* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY               */
/* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL            */
/* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE             */
/* GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS                 */
/* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,                  */
/* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                     */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS            */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                  */
/*-------------------------------------------------------------------------------*/
#ifndef	EYEONE_H
#define	EYEONE_H


#ifdef __cplusplus
	extern "C" {
    namespace I1SDK 
    {
      class Exception
      {
        public:
          virtual ~Exception() = 0;
      };

      inline Exception::~Exception() 
      {}
    }
#endif

#include "MeasurementConditions.h"

/* definitions for specific EyeOne key/values used with	GetDeviceInfo()	*/
#define	I1_VERSION                        "Version"
#define I1_SERIAL_NUMBER                  "SerialNumber"
#define	I1_IS_CONNECTED                   "Connection"
#define	I1_IS_KEY_PRESSED                 "IsKeyPressed"
#define	I1_IS_RECOGNITION_ENABLED         "Recognition"
#define	I1_LAST_CALIBRATION_TIME          "LastCalibrationTime"
#define	I1_CALIBRATION_COUNT              "LastCalibrationCounter"
#define	I1_LAST_ERROR                     "LastError"
#define	I1_EXTENDED_ERROR_INFORMATION     "ExtendedErrorInformation"
#define	I1_NUMBER_OF_AVAILABLE_SAMPLES    "AvailableSamples"
#define I1_AVAILABLE_MEASUREMENT_MODES    "AvailableMeasurementModes"
#define I1_IS_BEEP_ENABLED                "Beep"
#define I1_LAST_AUTO_DENSITY_FILTER       "LastAutoDensityFilter"
#define I1_IS_ADAPTIVE_MODE_ENABLED       "AdaptiveMode"
    
#define	I1_PHYSICAL_FILTER                "PhysicalFilter" /*read only*/
#define I1_UNDEFINED_FILTER               "0"    
#define I1_NO_FILTER                      "1"
#define I1_UV_FILTER                      "2"

#define I1_SCREEN_TYPE                    "ScreenType"    /*mandatory for i1-display*/
#define I1_LCD_SCREEN                     "LCD"
#define I1_CRT_SCREEN                     "CRT"

#define I1_PATCH_INTENSITY                "PatchIntensity" /*used with i1-display*/
#define I1_BLEAK                          "Bleak"
#define I1_BRIGHT                         "Bright"
#define I1_AUTO                           "Auto"
    
#define	I1_YES                            "yes"
#define	I1_NO                             "no"

#define I1_DEVICE_TYPE                    "DeviceType"
#define I1_EYEONE                         "EyeOne"
#define I1_DISPLAY                        "EyeOneDisplay"

#define	I1_MEASUREMENT_MODE               "MeasurementMode"
#define	I1_SINGLE_EMISSION                "SingleEmission"
#define	I1_SINGLE_REFLECTANCE             "SingleReflectance"
#define	I1_SINGLE_AMBIENT_LIGHT           "SingleAmbientLight"
#define	I1_SCANNING_REFLECTANCE           "ScanningReflectance"
#define	I1_SCANNING_AMBIENT_LIGHT         "ScanningAmbientLight"

#define	I1_RESET                          "Reset" /*reset command parameters: I1_ALL, DeviceTypes, MeasurementModes*/
#define	I1_ALL                            "All"


typedef enum I1_ErrorType
{
  eNoError,                               /* no error */
  eDeviceNotReady,                        /* device not ready	*/
  eDeviceNotConnected,                    /* device not connected	*/
  eDeviceNotCalibrated,                   /* device not calibrated */
  eKeyNotPressed,                         /* if no button	has been pressed */
  eNoSubstrateWhite,                      /* no substrate	white reference	set */
  eWrongMeasureMode,                      /* wrong measurement mode */
  eStripRecognitionFailed,                /* if the measurement mode is set to scanning and recognition is enabled */
  eNoDataAvailable,                       /* measurement not triggered, index out	of range (scanning) */
  eException,                             /* internal exception, use GetDeviceInfo(I1_LAST_ERROR)	for more details */
  eInvalidArgument,                       /* if a	passed method argument is invalid (i.e. NULL) */
  eUnknownError,                          /* unknown error occurred */
  eWrongDeviceType                        /* operation not supported by this device type */
} I1_ErrorType;


/* -------------- prototypes of	exported functions ----------------------------	*/
/* General remarks:
The FPtr_I1_XXX	typedefs (i.e. FPtr_I1_Calibrate) are declared to simplify the
process	of getting a reference to the desired method(s)	while dynamic loading this library
*/

// void MyErrorHandlerFunction(const char *axContext, I1_ErrorType axCode, const char * axText)
typedef void(*FPtr_I1_ErrorHandler)(const char*, I1_ErrorType, const char*);
FPtr_I1_ErrorHandler I1_RegisterErrorHandler(FPtr_I1_ErrorHandler);

/*------------------------ Information about driver and	API --------------------- */
/*
Deprected method. Use I1_GetOption instead !
I1_GetDeviceInfo is still exported from the dll for binary compatibility
but might be removed within the next release. We suggest to declare a prototype and
implement it for legacy applications the followign way
const char* I1_GetDeviceInfo (const char *axKey)
{
  return I1_GetOption(axKey);
}

*/
//const char* I1_GetDeviceInfo (const char *axKey);
//typedef	const char* (* FPtr_I1_GetDeviceInfo) (const char *);

/*
Test if	the EyeOne is connected
return eNoError	if connected
return eDeviceNotConnected if no EyeOne	is present
*/
I1_ErrorType I1_IsConnected(void);
typedef	I1_ErrorType (*	FPtr_I1_IsConnected)(void);

/*
Test if	the button has been pressed
return eNoError	if button was pressed
return eKeyNotPressed if button	was not	pressed
*/
I1_ErrorType I1_KeyPressed(void);
typedef	I1_ErrorType (*	FPtr_I1_KeyPressed)(void);

/*
returns	amount of currently available samples 
*/
long I1_GetNumberOfAvailableSamples(void);
typedef	long (*	FPtr_I1_GetNumberOfAvailableSamples)(void);

/*-----------------------------	trigger	measurements / calibrations ------------------------*/
/*
Calibrate the EyeOne
*/
I1_ErrorType  I1_Calibrate(void);
typedef	I1_ErrorType (*	FPtr_I1_Calibrate)(void);

/*
Trigger	measurement

Triggers a meausrement  depending on the measurement mode set by I1_SetOption
If the measurement mode is set to I1_SINGLE_EMISSION or I1_SCANNING_REFLECTANCE it is necessary
to calibrate the EyeOne before any measurement can be triggered

use GetSpectrum(index), I1_GetTriStimulus(index) or I1_GetDensity(index) to fetch the result

returns eDeviceNotConnected if no device is available
returns eDeviceNotCalibrated if a (re)calibration is necessary
*/
I1_ErrorType  I1_TriggerMeasurement(void);
typedef	I1_ErrorType (*	FPtr_I1_TriggerMeasurement)(void);


/*----------------------------------- get samples ----------------------------------*/
/*General remarks:
use I1_SINGLE_MEASUREMENT as Index, to fetch the result	of a previously	triggered single measurement 
To fetch a result of a previously triggered scan, specify an index between 0 - (I1_GetNumberOfScannedSamples() - 1)
If no measurement has been triggered or	if the specified index is out of range eNoDataAvailable	is returned
*/

/* 
Get the	spectrum of a previous triggered measurement 
*/
I1_ErrorType  I1_GetSpectrum(float yxSpectrum[SPECTRUM_SIZE], long axIndex);
typedef	I1_ErrorType (*	FPtr_I1_GetSpectrum)(float[SPECTRUM_SIZE], long);

/* 
Get the	color vector of	a previous triggered measurement 
*/
I1_ErrorType  I1_GetTriStimulus(float yxSpectrum[TRISTIMULUS_SIZE], long axIndex);
typedef	I1_ErrorType (*	FPtr_I1_GetTriStimulus)(float[TRISTIMULUS_SIZE], long);

/* 
Get the	all densities (cyan, magenta, yellow, black) of	a previous triggered measurement 
if pxAutoDensity is not	null, *pxAutoDensity will be set accordingly
*/
I1_ErrorType  I1_GetDensities(float yxDensities[DENSITY_SIZE], long *pxAutoDensityIndex, long axIndex);
typedef	I1_ErrorType (*	FPtr_I1_GetDensities)(float[DENSITY_SIZE], long*, long);

I1_ErrorType  I1_GetDensity(float *yxDensity, long axIndex);
typedef	I1_ErrorType (*	FPtr_I1_GetDensity)(float*, long);

/*------------------------------ special functions for Density -----------------------*/
/*
Set the	substrate spectrum for density calculations
This method has	to be called before the	first call to GetDensity()
*/
I1_ErrorType  I1_SetSubstrate(const float yxSpectrum[SPECTRUM_SIZE]);
typedef	I1_ErrorType (*	FPtr_I1_SetSubstrate)(const float[SPECTRUM_SIZE]);


/*---------------------	setting	measurement mode & conditions -------------------------------- */
/*
possible options (see MeasurementConditions.h for possible values)
COLOR_SPACE_KEY
ILLUMINATION_KEY
OBSERVER_KEY
DENSITY_STANDARD_KEY
DENSITY_FILTER_MODE_KEY

I1_MEASUREMENT_MODE, possible values : I1_SINGLE_EMISSION, I1_SINGLE_REFLECTANCE, I1_SCANNING_REFLECTANCEdefault: I1_SCANNING_REFLECTANCE
I1_IS_RECOGNITION_ENABLED, possible values : I1_YES, I1_NO, default : I1_NO
*/
I1_ErrorType  I1_SetOption(const char *axKey, const char *axValue);
typedef	I1_ErrorType (*	FPtr_I1_SetOption)(const char*,	const char*);

const char* I1_GetOption(const char *axKey);
typedef	const char* (* FPtr_I1_GetOption)(const	char*);

#define	I1_SINGLE_MEASUREMENT             0 /*deprecated*/

#ifdef __cplusplus
	}
#endif

#endif /*EYEONE_H*/

