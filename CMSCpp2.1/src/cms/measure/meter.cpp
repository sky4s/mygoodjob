#include <includeall.h>
#pragma hdrstop
#include "meter.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace measure {
	namespace meter {
	    using namespace std;
	    using namespace boost;
	    using namespace cms::colorformat;
	    using namespace cms::lcd::calibrate;
	    using namespace Indep;
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
		CA210API_->calibrate();
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
		    CA210API_->setAveragingMode(ca210api::Fast);
		    break;
		case Bright:
		    CA210API_->setAveragingMode(ca210api::Slow);
		    break;
		case Auto:
		    CA210API_->setAveragingMode(ca210api::Auto);
		    break;
		}
	    };
	    double_array CA210::triggerMeasurementInXYZ() {
		measureCount++;
		float_array values = CA210API_->triggerMeasurement();
		double_array result(new double[3]);
		result[0] = values[0];
		result[1] = values[1];
		result[2] = values[2];
		return result;
	    };

	    shared_ptr < std::string > CA210::getLastCalibration() {
		return nil_string_ptr;
	    };
	    shared_ptr < std::string > CA210::getCalibrationCount() {
		return nil_string_ptr;
	    };
	    void CA210::setScreenType(ScreenType screenType) {
	    };
	    Instr CA210::getType() {
		return Instr::CA210;
	    };
	    void CA210::close() {
		CA210API_->close();
	    };
	    //ca210api::CA210API CA210::CA210API_;
	    bptr < ca210api::CA210API > CA210::getCA210API() {
		return CA210API_;
	    };
	    bptr < ca210api::CA210API > CA210::CA210API_;
	    void CA210::initCA210API() {
		CA210API_ =
		    bptr < ca210api::CA210API > (new ca210api::CA210API());
	    };
	    CA210::CA210() {
		if (null == CA210API_) {
		    initCA210API();
		}
	    };
	    //==================================================================

	  DGLutFileMeter::DGLutFileMeter(bptr < DGLutFile > dglut):dglut(dglut), vector(dglut->getComponentVector()),
		index(0)
	    {
	    };
	    void DGLutFileMeter::close() {
	    };
	    bool DGLutFileMeter::isConnected() {
		return true;
	    };
	    void DGLutFileMeter::calibrate() {
		index = 0;
	    };
	    string_ptr DGLutFileMeter::getCalibrationDescription() {
		return shared_ptr < string >
		    (new string("Calibration needless."));
	    };
	    void DGLutFileMeter::
		setPatchIntensity(PatchIntensity patchIntensity) {
	    };
	    double_array DGLutFileMeter::triggerMeasurementInXYZ() {
		//int size = vector->size();
		if (index >= vector->size()) {
		    throw java::lang::IndexOutOfBoundsException("index >= vector->size()");
		}

		c = (*vector)[index];
		index++;
		XYZ_ptr XYZ = c->XYZ;
		return XYZ->getValues();
	    };
	    string_ptr DGLutFileMeter::getLastCalibration() {
		return nil_string_ptr;
	    };
	    string_ptr DGLutFileMeter::getCalibrationCount() {
		return nil_string_ptr;
	    };
	    void DGLutFileMeter::setScreenType(ScreenType screenType) {
	    };
	    Instr DGLutFileMeter::getType() {
		return Instr::CA210;
	    };
	    Component_ptr DGLutFileMeter::getComponent() {
		return c;
	    };
	    void DGLutFileMeter::setIndex(int index) {
		this->index = index;
	    };
	    void DGLutFileMeter::reset() {
		this->index = 0;
	    };
	    //==================================================================
	};
    };
};

