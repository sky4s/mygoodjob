#include <includeall.h>
#pragma hdrstop
#include "meter.h"

//C系統文件

//C++系統文件

//其他庫頭文件
#ifndef OD_MEASUREMENT
#include <EyeOneLib/EyeOne.h>
#endif
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
	     Instr::Instr(double width, double length):widthInch(width), lengthInch(length) {
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
	    void Meter::setLogoFileHeader(cms::colorformat::logo::LogoFile & logo) {
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
		    (new string("Set the pointing ring to the 0-CAL position."));
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

	    double CA210::triggerMeasurementInFlickerFMA() {
		measureCount++;
		return (double) CA210API_->triggerFlickerFMA();
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
	    bptr < ca210api::CA210API > CA210::getCA210API() {
		return CA210API_;
	    };
	    bptr < ca210api::CA210API > CA210::CA210API_;
	    void CA210::initCA210API() {
		CA210API_ = bptr < ca210api::CA210API > (new ca210api::CA210API());
	    };
	    CA210::CA210() {
		if (null == CA210API_) {
		    initCA210API();
		}
	    };
	    //==================================================================
#ifndef OD_MEASUREMENT
	    EyeOne::EyeOne() {
		i1 = bptr < TEyeOneCtrl > (new TEyeOneCtrl((TComponent *) null));

	    };
	    void EyeOne::close() {
	    };
	    bool EyeOne::isConnected() {
		long result = i1->IsConnected();
		return eNoError == result;
	    };
	    void EyeOne::calibrate() {
		i1->Calibrate();
	    };
	    string_ptr EyeOne::getCalibrationDescription() {
		return shared_ptr < string >
		    (new string("Set the pointing ring to the 0-CAL position."));
	    };
	    void EyeOne::setPatchIntensity(PatchIntensity patchIntensity) {
	    };
	    double_array EyeOne::triggerMeasurementInXYZ() {
		double_array result(new double[3]);
		return result;
	    };
	    string_ptr EyeOne::getLastCalibration() {
		return nil_string_ptr;
	    };
	    string_ptr EyeOne::getCalibrationCount() {
		return nil_string_ptr;
	    };
	    void EyeOne::setScreenType(ScreenType screenType) {
	    };
	    Instr EyeOne::getType() {
		return Instr::i1Pro;
	    };
#endif
	    //==================================================================
	  DGLutFileMeter::DGLutFileMeter(bptr < DGLutFile > dglut):index(0) {
		Patch_vector_ptr patchVector = dglut->getMeasurePatchVector();
		if (null != patchVector) {
		    measurePatchVector = patchVector;
		} else {
		    vector = dglut->getComponentVector();
		}
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
		return shared_ptr < string > (new string("Calibration needless."));
	    };
	    void DGLutFileMeter::setPatchIntensity(PatchIntensity patchIntensity) {
	    };
	    double_array DGLutFileMeter::triggerMeasurementInXYZ() {

		if (isMeasureFromPatchVector()) {
		    int size = measurePatchVector->size();
		    if (index >= size) {
			throw java::lang::IndexOutOfBoundsException("index >= size");
		    }

		    Patch_ptr p = (*measurePatchVector)[index];
		    index++;
		    XYZ_ptr XYZ = p->getXYZ();
		    return XYZ->getValues();
		} else {
		    int size = vector->size();
		    if (index >= size) {
			throw java::lang::IndexOutOfBoundsException("index >= size");
		    }

		    c = (*vector)[index];
		    index++;
		    XYZ_ptr XYZ = c->XYZ;
		    return XYZ->getValues();
		}

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
	    bool DGLutFileMeter::isMeasureFromPatchVector() {
		return null != measurePatchVector;
	    };
	    FakeMode DGLutFileMeter::getFakeMode() {
		return isMeasureFromPatchVector()? FakeMode::Patch : FakeMode::Component;
	    };
	    //==================================================================
	};
    };
};

