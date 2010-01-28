#include "meter.h"

//#include <java/lang.h>
//#include <cms/colorformat/logo.h>
//#include <string>

namespace cms {
    namespace measure {
	namespace meter {
	    using namespace std;
	    using namespace boost;
	    //==================================================================
	    // Instr
	    //==================================================================
	     Instr::Instr(double width, double length):widthInch(width),
		lengthInch(length) {
	    };

	    const Instr Instr::i1Display2(2.5, 3.3);
	    const Instr Instr::i1Pro(2.6, 6);
	    const Instr Instr::Spyder2(4.25, 4.7);
	    const Instr Instr::Spyder3(3.5, 4);
	    const Instr Instr::CA210(1.9, 1.9);
	    const Instr Instr::Dummy(2.5, 3.3);
	    const Instr Instr::Argyll(4.25, 4.7);
	    const Instr Instr::Platform(0, 0);
	    //==================================================================

	    //==================================================================
	    // Meter
	    //==================================================================
	    void Meter::setLogoFileHeader(cms::colorformat::logo::
					  LogoFile & logo) {
		/*logo.setHeader(LogoFile.Reserved.Created,
		   new Date().toString());
		   logo.setHeader(LogoFile.Reserved.Instrumentation,
		   getType().name());
		   logo.setHeader(LogoFile.Reserved.MeasurementSource,
		   "Illumination=Unknown    ObserverAngle=Unknown   WhiteBase=Abs   Filter=Unknown");
		   logo.setNumberOfFields(8);
		   logo.addKeyword("SampleID");
		   logo.addKeyword("SAMPLE_NAME");
		   logo.
		   setDataFormat
		   ("SampleID       SAMPLE_NAME     RGB_R   RGB_G   RGB_B   XYZ_X   XYZ_Y   XYZ_Z"); */
	    };
	    int Meter::getSuggestedWaitTimes() {
		return 300;
	    };
	    //==================================================================

	    //==================================================================
	    // CA210
	    //==================================================================
	    bool CA210::isConnected() {
		return true;
	    };

	    void CA210::calibrate() {
		_CA210API->calibrate();
		//calibrateTime = new Date();
		measureCount = 0;
	    };


	    shared_ptr < string > CA210::getCalibrationDescription() {
		return shared_ptr < string >
		    (new
		     string
		     ("Set the pointing ring to the 0-CAL position."));
	    };

	    void CA210::setPatchIntensity(PatchIntensity patchIntensity) {
		//using namespace ca210api;
		switch (patchIntensity) {
		case Bleak:
		    _CA210API->setAveragingMode(ca210api::Fast);
		    break;
		case Bright:
		    _CA210API->setAveragingMode(ca210api::Slow);
		    break;
		case Auto:
		    _CA210API->setAveragingMode(ca210api::Auto);
		    break;
		}
	    };
	    shared_array < double >CA210::triggerMeasurementInXYZ() {
		measureCount++;
		shared_array < float >values =
		    _CA210API->triggerMeasurement();
		shared_array < double >result(new double[3]);
		result[0] = values[0];
		result[1] = values[1];
		result[2] = values[2];
		return result;
	    };

	    shared_ptr < std::string > CA210::getLastCalibration() {
		//return nil_string_ptr;
	    };
	    shared_ptr < std::string > CA210::getCalibrationCount() {
		//return nil_string_ptr;
	    };
	    void CA210::setScreenType(ScreenType screenType) {
	    };
	    Instr CA210::getType() {
		return Instr::CA210;
	    };
	    void CA210::close() {
		_CA210API->close();
	    };
	    //ca210api::CA210API CA210::_CA210API;
	    bptr < ca210api::CA210API > CA210::getCA210API() {
		return _CA210API;
	    };
	    bptr < ca210api::CA210API > CA210::_CA210API;
	    void CA210::initCA210API() {
		_CA210API =
		    bptr < ca210api::CA210API > (new ca210api::CA210API());
	    };
	    CA210::CA210() {
		if (NULL == _CA210API) {
		    initCA210API();
		}
	    };
	    //==================================================================
	};
    };
};

