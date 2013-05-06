#include <includeall.h>
#pragma hdrstop
#include "MeterMeasurement.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace measure {
	using namespace boost;
	using namespace cms;
	using namespace Dep;
	using namespace cms::measure::meter;
	using namespace cms::measure::cp;
	using namespace std;
	using namespace java::lang;
	using namespace cms::lcd::calibrate;
	using namespace cms::lcd;
	using namespace cms::util;

	void MeterMeasurement::init(bool calibration) {
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
	};
	void MeterMeasurement::resetMeasurePatchVector() {
	    measurePatchVector->clear();
	};
      MeterMeasurement::MeterMeasurement(shared_ptr < Meter > meter, bool calibration):meter(meter), waitTimes(meter->getSuggestedWaitTimes()),
	    measureWindowClosing(false),
	    titleTouched(false),
	    /*fakeMeasure(false), */ averageTimes(1), blankTimes(DefaultBlankTimes),
	    blankRGB(RGBColor::Black), flicker(FlickerMode::JEITA) {
	    init(calibration);
	    measurePatchVector = Patch_vector_ptr(new Patch_vector());
	    DGLutFileMeter *filemeter = dynamic_cast < DGLutFileMeter * >(meter.get());
	    if (null != filemeter) {
		fakeMode = filemeter->getFakeMode();
	    } else {
		fakeMode = FakeMode::None;
	    }
	    measureRequest = RGB_vector_ptr(new RGB_vector());
	};

	void MeterMeasurement::calibrate() {
	    MeasureUtils::meterCalibrate(*this);
	};

	void MeterMeasurement::close() {
	    setMeasureWindowsVisible(false);
	    measureWindow->Close();
	    meterClose();
	};

	void MeterMeasurement::setMeasureWindowsVisible(bool visible) {
	    if (fakeMode == FakeMode::None) {
		if (null == measureWindow) {
		    measureWindow = MeasureWindow;
		}
		measureWindow->setVisible(visible);
		measureWindowClosing = !visible;
	    }
	};

	Patch_ptr MeterMeasurement::measure(const string_ptr patchName) {
	    return measure0(nil_RGB_ptr, patchName, nil_string_ptr, nil_string_ptr, false, true);
	};

	Patch_ptr MeterMeasurement::measure(RGB_ptr rgb, const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr, nil_string_ptr, false, false);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b, const string_ptr patchName) {
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, patchName);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b, const string & patchName) {
	    string_ptr str(new string(patchName));
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, str);
	};

	bptr < cms::measure::meter::Meter > MeterMeasurement::getMeter() {
	    return meter;
	};

	void MeterMeasurement::meterClose() {

	};
	Patch_ptr MeterMeasurement::measureFlicker(RGB_ptr rgb, const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr, nil_string_ptr, true, false);
	};
	Patch_ptr MeterMeasurement::measureFlicker(const string_ptr patchName) {
	    return measure0(nil_RGB_ptr, patchName, nil_string_ptr, nil_string_ptr, true, true);
	};

	void MeterMeasurement::pushMeasureRequest(RGB_ptr rgb) {
	    measureRequest->push_back(rgb);
	}
	void MeterMeasurement::pushMeasureRequest(RGB_vector_ptr measureVector) {
	    foreach(RGB_ptr rgb, *measureVector) {
		measureRequest->push_back(rgb);
	    }
	}
	void MeterMeasurement::clearMeasureRequest() {
	    measureRequest->clear();
	}
	Patch_vector_ptr MeterMeasurement::pullMeasureResult() {

	}

	Patch_ptr
	    MeterMeasurement::measure0(RGB_ptr measureRGB,
				       string_ptr patchName,
				       string_ptr titleNote, string_ptr timeNote,
				       bool flickerMeasure, bool noPattern) {
	    if (!noPattern) {
		setMeasureWindowsVisible(true);
	    }
	    //�q�����C��, �q�����C��i��P�ɨ㪺�C�⤣�P, �ҥH�S�O�W�ߥX���ܼ�

	    if (!titleTouched) {
		//�p�Gtitle�S�Q�]�w�L
		if (titleNote != NULL) {
		    //measureWindow.setTitle("Measure Window " + titleNote);
		    /*measureWindow->Caption =
		       AnsiString("Measure Window " + titleNote); */

		} else {
		    measureWindow->Caption = AnsiString("Measure Window");
		}
	    }

	    if (0 != blankTimes) {
		Application->ProcessMessages();
		measureWindow->setRGB(blankRGB);
		Application->ProcessMessages();
		Util::sleep(blankTimes);
	    }
	    //==========================================================================
	    // �ܴ��������C�⪺�u�Ȱ��d
	    //==========================================================================
	    if (fakeMode == FakeMode::None) {
		Application->ProcessMessages();
		if (!noPattern) {
		    measureWindow->setRGB(measureRGB);
		}
		Application->ProcessMessages();
		Util::sleep(waitTimes);
	    }
	    if (5000 == waitTimes) {
		int x = 1;
	    }
	    //==========================================================================


	    if (true == measureWindowClosing) {
		//�p�G�����Q����, �N�����q��
		return Patch_ptr((Patch *) NULL);
	    }
	    double_array result;
	    if (flickerMeasure) {
		float flickerValue = -1;
		CA210 *ca210 = dynamic_cast < CA210 * >(meter.get());
		if (null != ca210) {
		    bptr < ca210api::CA210API > ca210api = ca210->getCA210API();
		    if (FlickerMode::FMA == flicker) {
			flickerValue = ca210api->triggerFlickerFMA();
		    } else if (FlickerMode::JEITA == flicker) {
			flickerValue = ca210api->triggerFlickerJEITA();
		    }
		}
		result = double_array(new double[3]);
		result[0] = 0;
		result[1] = flickerValue;
		result[2] = 0;
	    } else {
		if (averageTimes == 1) {
		    result = meter->triggerMeasurementInXYZ();
		} else {
		    result = double_array(new double[3]);
		    result[0] = result[1] = result[2] = 0;
		    for (int x = 0; x < averageTimes; x++) {
			double_array thisresult = meter->triggerMeasurementInXYZ();
			result[0] += thisresult[0];
			result[1] += thisresult[1];
			result[2] += thisresult[2];
		    }
		    result[0] /= averageTimes;
		    result[1] /= averageTimes;
		    result[2] /= averageTimes;
		}
	    }

	    XYZ_ptr XYZ(new Indep::CIEXYZ(result));
	    Patch_ptr patch(new Patch(patchName, XYZ, nil_XYZ_ptr, measureRGB));
	    measurePatchVector->push_back(patch);
	    return patch;
	};
	bool MeterMeasurement::doExtraMeasure() {
	    return FakeMode::None == fakeMode || FakeMode::Patch == fakeMode;
	};
	//======================================================================

	//======================================================================
	// MeasureResult
	//======================================================================
	void MeasureUtils::meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate(meter, measureWindow);
	};
	void MeasureUtils::meterCalibrate(shared_ptr < Meter > meter,
					  TMeasureWindow * measureWindow) {
	    if (!meter->isConnected()) {
		throw IllegalStateException("!meter.isConnected()");
	    } else {
		if (measureWindow != NULL) {
		    //show�X�¹�, �קK�v�T�ե�
		    measureWindow->setRGB(0, 0, 0);
		    Application->ProcessMessages();
		    measureWindow->setVisible(true);
		}
		ShowMessage(meter->getCalibrationDescription()->c_str());
		meter->calibrate();
		if (measureWindow != null) {
		    //�����¹�
		    measureWindow->setVisible(false);
		}
		ShowMessage("End of calibration");
	    };
	};

	MeasureResult::MeasureResult(Patch_vector_ptr result,
				     int practicalMeasureCount):result
	    (result), practicalMeasureCount(practicalMeasureCount) {

	};
	//======================================================================

	//======================================================================
	// MeasureTool
	//======================================================================
      MeasureTool::MeasureTool(bptr < cms::measure::MeterMeasurement > mm):mm(mm),
	    stop(false), inverseMeasure(false)
	{

	};
	Patch_vector_ptr MeasureTool::rampMeasure(const Dep::
						  Channel & channel,
						  bptr <
						  cms::lcd::calibrate::
						  MeasureCondition > measureCondition) {
	    return rampMeasure(channel, nil_int_vector_ptr, measureCondition);

	};
	Patch_vector_ptr MeasureTool::rampMeasure(const Dep::
						  Channel & channel, int_vector_ptr background,
						  bptr <
						  cms::lcd::calibrate::
						  MeasureCondition > measureCondition) {

	    RGB_vector_ptr trueMeasureCode(new RGB_vector());
	    foreach(RGB_ptr & c, *measureCondition->getRGBMeasureCode()) {
		RGB_ptr rgb;
		if (channel == Channel::W) {
		    rgb = c;
		} else {
		    rgb = RGB_ptr(new RGBColor(c->getMaxValue()));
		    rgb->setValue(channel, c->getValue(channel));
		    if (null != background) {
			foreach(const Channel & ch, *Channel::RGBChannel) {
			    if (ch != channel) {
				int bgcolor = (*background)[ch.getArrayIndex()];
				rgb->setValue(ch, bgcolor);
			    }
			}
		    }
		}
		trueMeasureCode->push_back(rgb);
	    };
	    bptr < MeasureCondition > newMeasureCondition(new MeasureCondition(trueMeasureCode));
	    return rampMeasure(newMeasureCondition);
	};
	Patch_vector_ptr MeasureTool::rampMeasure(bptr < cms::lcd::calibrate::MeasureCondition >
						  measureCondition) {
	    RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
	    bool is10BitInMeasurement = measureCondition->get10BitInMeasurement();
	    if (inverseMeasure) {
		rgbMeasureCode = RGBVector::reverse(rgbMeasureCode);
	    }

	    Patch_vector_ptr vector(new Patch_vector());

	    //for AgingMode byBS+
	    if (isAgingMode()) {
		if (true) {
		    MeasureWindow->setAgingEnable(rgbMeasureCode);	//TCON�g�JDG LUT�A�ö}��DG
		}

		int step = is10BitInMeasurement ? 1 : 4;
		for (int x = 0; x < 1024; x += step) {	//����?
		    RGB_ptr rgb(new RGBColor(x, x, x));
		    Patch_ptr patch = mm->measure(rgb, rgb->toString());
		    vector->push_back(patch);
		    if (true == stop) {
			stop = false;
			mm->setMeasureWindowsVisible(false);
			return nil_Patch_vector_ptr;
		    }
		}

		/*if (is10BitInMeasurement) {
		   for (int x = 0; x < 1024; x++) {     //����?
		   RGB_ptr rgb(new RGBColor(x, x, x));
		   Patch_ptr patch = mm->measure(rgb, rgb->toString());
		   vector->push_back(patch);
		   if (true == stop) {
		   stop = false;
		   mm->setMeasureWindowsVisible(false);
		   return nil_Patch_vector_ptr;
		   }
		   }
		   } else {
		   for (int x = 0; x < 1024; x += 4) {
		   RGB_ptr rgb(new RGBColor(x, x, x));
		   Patch_ptr patch = mm->measure(rgb, rgb->toString());
		   vector->push_back(patch);
		   if (true == stop) {
		   stop = false;
		   mm->setMeasureWindowsVisible(false);
		   return nil_Patch_vector_ptr;
		   }
		   }
		   } */
	    } else {
		//Patch_vector_ptr vector(new Patch_vector());
		foreach(RGB_ptr rgb, *rgbMeasureCode) {
		    Patch_ptr patch = mm->measure(rgb, rgb->toString());
		    vector->push_back(patch);
		    if (true == stop) {
			stop = false;
			mm->setMeasureWindowsVisible(false);
			return nil_Patch_vector_ptr;
		    }
		};
	    }

	    mm->setMeasureWindowsVisible(false);
	    if (inverseMeasure) {
		vector = Patch::reverse(vector);
	    }
	    return vector;
	};
	Component_vector_ptr MeasureTool::flickerMeasure(bptr < MeasureCondition > measureCondition) {
	    RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
	    Component_vector_ptr vector(new Component_vector());
	    foreach(RGB_ptr rgb, *rgbMeasureCode) {
		Patch_ptr patch = mm->measureFlicker(rgb, rgb->toString());

		Component_ptr component(new Component(rgb, nil_RGB_ptr, patch->getXYZ()));
		vector->push_back(component);
		if (true == stop) {
		    stop = false;
		    mm->setMeasureWindowsVisible(false);
		    return nil_Component_vector_ptr;
		}
	    };
	    mm->setMeasureWindowsVisible(false);
	    return vector;
	};
	bool MeasureTool::isAgingMode() {
	    return MeasureWindow->isAgingSource();
	}
	void MeasureTool::windowClosing(TObject * Sender, TCloseAction & Action) {
	    stop = true;
	}
	int MeasureTool::getMaxZDGCode(bptr < cms::lcd::calibrate::MeasureCondition >
				       measureCondition) {
	    RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
	    Patch_ptr prePatch;
	    XYZ_ptr maxZ;
	    RGB_ptr maxZRGB;
	    mm->setMeasureWindowsVisible(true);

	    foreach(RGB_ptr rgb, *rgbMeasureCode) {
		Patch_ptr patch = mm->measure(rgb, rgb->toString());
		if (true == stop) {
		    stop = false;
		    mm->setMeasureWindowsVisible(false);
		    return -1;
		}
		XYZ_ptr XYZ = patch->getXYZ();
		if (null == maxZ) {
		    maxZ = XYZ;
		    maxZRGB = rgb;
		    continue;
		}
		if (XYZ->Z > maxZ->Z) {
		    maxZ = XYZ;
		    maxZRGB = rgb;
		} else {
		    mm->setMeasureWindowsVisible(false);
		    return (int) maxZRGB->getValue(Channel::W, MaxValue::Int8Bit);
		}
	    };
	    mm->setMeasureWindowsVisible(false);
	    return -1;
	}

	int MeasureTool::getMaxZDGCode(bptr < MeterMeasurement > mm,
				       bptr < BitDepthProcessor > bitDepth) {
	    /*if (mm->FakeMeasure) {
	       throw IllegalStateException("mm->isFakeMeasure(), cannot do real measure.");
	       } */
	    bptr < MeasureTool > mt(new MeasureTool(mm));
	    MeasureWindow->addWindowListener(mt);
	    bptr < MeasureCondition > measureCondition(new MeasureCondition(bitDepth));
	    int maxZDGCode = mt->getMaxZDGCode(measureCondition);
	    return maxZDGCode;
	};
	int MeasureTool::getMaxBIntensityRawGrayLevel(bptr < MeterMeasurement > mm,
						      bptr < BitDepthProcessor > bitDepth) {
	    int max = bitDepth->getInputMaxDigitalCount();
	    using namespace cms::measure;
	    bptr < MaxMatrixIntensityAnalyzer > analyzer =
		MaxMatrixIntensityAnalyzer::getReadyAnalyzer(mm, max, max, max);
	    return getMaxBIntensityRawGrayLevel(mm, bitDepth, analyzer);
	};
	int MeasureTool::getMaxBIntensityRawGrayLevel(bptr < MeterMeasurement > mm,
						      bptr < BitDepthProcessor > bitDepth,
						      bptr < IntensityAnalyzerIF > analyzer) {
	    //int max = bitDepth->getInputMaxDigitalCount();
	    int max = bitDepth->getOutputMaxDigitalCount();	//modified@20130503 by skyforce
	    /*using namespace cms::measure;
	       bptr < MaxMatrixIntensityAnalyzer > analyzer =
	       MaxMatrixIntensityAnalyzer::getReadyAnalyzer(mm, max, max, max); */
	    using namespace Dep;
	    using namespace java::lang;
	    RGB_ptr preIntensity;
	    int maxBRawGrayLevel = max;
	    const int DefinedMaxBRawGrayLevel = 50;

	    //�p�G�B�baging mode, DG����off

	    //�ѩ�x�ξ�ư����N, �̤j�ȶȨ�255, �����10bit out��panel, 255.75�|�Qcut�ѤU255, �L�k���T��X10bit pattern
	    //���O�����I�������b254�H�U, �ҥH�H�W���쪺���~���|�y�����v�T
	    for (int x = max; x > (max - DefinedMaxBRawGrayLevel); x--) {
		RGB_ptr rgb(new RGBColor(x, x, x));
		RGB_ptr intensity = analyzer->getIntensity(rgb);
		if (null != preIntensity) {
		    bool inverseB = intensity->B < preIntensity->B;
		    if (inverseB) {
			maxBRawGrayLevel = x + 1;
			break;
		    }
		}
		preIntensity = intensity;
	    }

	    analyzer->endAnalyze();
	    return maxBRawGrayLevel;

	};
	//======================================================================
    };
};

