//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件
#include <FileCtrl.hpp>
//本項目內頭文件
#include "TCCTLUTForm.h"
#include "TMainForm.h"
#include "TTargetWhiteForm2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
__fastcall TCCTLUTForm::TCCTLUTForm(TComponent * Owner)
:TForm(Owner), serialid(0), run(false), debugMode(MainForm->debugMode)
{
}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------


void TCCTLUTForm::setMeasureInfo()
{
    using namespace cms::util;
    int start = bitDepth->getMeasureStart();
    int step = bitDepth->getMeasureStep();
    this->Edit_StartLevel->Text = Util::toString(start).c_str();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};


//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::RadioButton_P1P2Click(TObject * Sender)
{
    this->CheckBox_NewMethod->Checked = false;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_MeaRunClick(TObject * Sender)
{
    using namespace std;
    using namespace Dep;
    using namespace cms::lcd::calibrate;
    using namespace cms::colorformat;
    using namespace cms::measure;
    using namespace i2c;
    using namespace java::lang;


    if (Button_Run->Enabled) {
	MainForm->initCA210Meter();
	MainForm->setAnalyzerNull();
    }

    bptr < DGLutFile > dgLutFile;
    try {			//為了對應__finally使用的try
	run = true;
	if (this->TOutputFileFrame1->Warning) {
	    ShowMessage("Output file is locked! Try release file lock and retry!");
	    return;
	}
	Button_MeaRun->Enabled = false;
	MainForm->showProgress(ProgressBar1);
	String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
	string filename = astr->c_str();

	MainForm->initAnalyzer();
	MainForm->setMeterMeasurementWaitTimes();
	bptr < ComponentFetcher > fetcher = MainForm->getComponentFetcher();
	bptr < MeterMeasurement > mm = fetcher->FirstAnalyzer->getMeterMeasurement();
	mm->resetMeasurePatchVector();

	cms::lcd::calibrate::debugMode = debugMode;
	cms::lcd::calibrate::linkCA210 = MainForm->linkCA210;
	cms::lcd::calibrate::pcWithTCONInput = MainForm->isPCwithTCONInput();
	LCDCalibrator calibrator(fetcher, bitDepth);

	//以下都是選項的設定

	//==========================================================================
	// P1P2和RBInterp的選擇
	//==========================================================================
	if (this->RadioButton_P1P2->Checked) {
	    //選了P1P2
	    int p1 = this->Edit_P1->Text.ToInt();
	    int p2 = this->Edit_P2->Text.ToInt();
	    calibrator.setP1P2(p1, p2);
	} else if (this->RadioButton_RBInterp->Checked) {
	    //選了RBInterp
	    int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	    calibrator.setRBInterpolation(rbunder);
	} else if (this->RadioButton_DefinedDim->Checked) {
	    //新低灰階修正方法
	    int under = this->Edit_DefinedDimUnder->Text.ToInt();	// + 1;
	    double gamma = this->ComboBox_DefinedDimGamma->Text.ToDouble();

	    calibrator.setDefinedDim(under, gamma);
	    calibrator.FeedbackFix = CheckBox_Feedback->Checked;
	} else if (this->RadioButton_NoneLowLevelCorrect->Checked) {
	    calibrator.setNonDimCorrect();
	}
	//==========================================================================

	//==========================================================================
	// gamma的處理
	//==========================================================================

	if (true == CheckBox_AbsoluteGamma->Checked) {
	    bool absGamma = CheckBox_AbsoluteGamma->Checked;
	    int start = Edit_AbsGammaStart->Text.ToInt();
	    double aboveGamma = ComboBox_AbsGammaStartAboveGamma->Text.ToDouble();
	    calibrator.setAbsoluteGamma(absGamma, start, aboveGamma);
	}

	if (this->RadioButton_Gamma->Checked) {
	    double gamma = this->ComboBox_Gamma->Text.ToDouble();
	    calibrator.setGamma(gamma);
	} else if (this->RadioButton_GammaCurve->Checked || this->RadioButton_GammaValue->Checked) {
	    double_vector_ptr gammaCurve = rgbGamma->w;
	    calibrator.setGammaCurve(gammaCurve);
	    calibrator.GByPass = this->CheckBox_GByPass->Checked;
	} else if (this->RadioButton_OriginalGamma->Checked) {
	    calibrator.setOriginalGamma();
	    calibrator.GByPass = true;
	} else if (this->RadioButton_3Gamma->Checked) {
	    double gammaDim = this->ComboBox_DimGamma->Text.ToDouble();
	    double gammaBright = this->ComboBox_BrightGamma->Text.ToDouble();
	    int dimGammaEnd = Edit_DimGammaEnd->Text.ToInt();
	    int middleGammaEnd = Edit_MiddleGammaEnd->Text.ToInt();
	    calibrator.setGamma(gammaDim, dimGammaEnd, middleGammaEnd, gammaBright);
	}
	//==========================================================================

	//==========================================================================
	// blue correction
	//==========================================================================
	if (this->CheckBox_BGain->Checked) {
	    double gain = this->Edit_BGain->Text.ToDouble();
	    calibrator.BIntensityGain = gain;
	}
	calibrator.BMax = this->CheckBox_BMax->Checked;
	//==========================================================================

	//==========================================================================
	// others
	//==========================================================================
	calibrator.AvoidFRCNoise = this->CheckBox_AvoidNoise->Checked;

	//新方法
	calibrator.NewMethod = this->CheckBox_NewMethod->Checked;
	calibrator.setMultiGen(this->CheckBox_MultiGen->Checked,
			       this->Edit_MultiGenTimes->Text.ToInt());
	calibrator.KeepMaxYInMultiGen = this->CheckBox_KeepMaxYInMultiGen->Checked;
	if (CheckBox_RTargetIntensity->Checked) {
	    double rTargetIntensity = Edit_RTargetIntensity->Text.ToDouble();
	    calibrator.RTargetIntensity = rTargetIntensity;
	}
	if (CheckBox_BTargetIntensity->Checked) {
	    double bTargetIntensity = Edit_BTargetIntensity->Text.ToDouble();
	    calibrator.BTargetIntensity = bTargetIntensity;
	}
	//==========================================================================

	//==========================================================================
	// Keep Max Luminance
	//==========================================================================
	//keep跟dehook融合在一起, 簡化ui
	if (true == RadioButton_MaxYNone->Checked) {
	    calibrator.setKeepMaxLuminance(KeepMaxLuminance::TargetLuminance);
	    calibrator.DeHookMode = None;
	} else if (true == RadioButton_MaxYNative->Checked) {
	    calibrator.setKeepMaxLuminance(KeepMaxLuminance::NativeWhite);

	    if (RadioButton_DeHookNone->Checked) {
		calibrator.DeHookMode = None;
	    } else if (RadioButton_DeHookKeepCCT->Checked) {
		calibrator.DeHookMode = KeepCCT;
	    } else if (RadioButton_NewDeHook->Checked) {
		int index = RadioGroup_NewDeHookPriority->ItemIndex;
		switch (index) {
		case 0:	//B Gap first
		    calibrator.DeHookMode = SecondWithBGap1st;
		    break;
		case 1:	//Gamma first
		    calibrator.DeHookMode = SecondWithGamma1st;
		    break;
		};
		calibrator.AlterGammaCurveAtDeHook2 = CheckBox_AlterGammaCurveAtDeHook2->Checked;
	    }


	} else if (true == RadioButton_MaxYNativeAdv->Checked) {
	    int over = Edit_MaxYAdvOver->Text.ToInt();
	    bool autoOver = CheckBox_MaxYAdvAuto->Checked;
	    calibrator.setKeepMaxLuminanceSmooth2NativeWhite(over, autoOver);

	} else if (true == RadioButton_MaxYTargetWhite->Checked) {
	    calibrator.setKeepMaxLuminance(KeepMaxLuminance::TargetWhite);

	    if (true == this->CheckBox_SmoothIntensity->Checked) {
		int start = Edit_SmoothIntensityStart->Text.ToInt();
		int end = Edit_SmoothIntensityEnd->Text.ToInt();
		calibrator.setSmoothIntensity(start, end);
	    }
	    calibrator.DeHookMode = None;
	}
	//==========================================================================
	//以上都是選項的設定
	//=================================================================
	// 設定結束, 進入主流程開始處理
	//=================================================================

	try {
	    if (this->TOutputFileFrame1->createDir() == false) {
		ShowMessage("Cannot create directory!! Stop!");
		MainForm->stopProgress(ProgressBar1);
		return;
	    }
	    Util::deleteExist(filename);
	    dgLutFile = bptr < DGLutFile > (new DGLutFile(filename, Create));

	    bptr < TCONControl > tconctrl = MainForm->getTCONControl();
	    calibrator.TCONControl = tconctrl;
	    calibrator.SecondWhiteAnalyzer = secondWhiteAnalyzer;
	    calibrator.setFeedbackListener(this);


	    //開始量測及計算
	    RGB_vector_ptr dglut = calibrator.getCCTDGLut(getMeasureCondition(), dgLutFile);
	    if (dglut == null) {
		MainForm->stopProgress(ProgressBar1);
		if (run) {
		    //被中斷就直接return
		    ShowMessage("Internal abnormal stop!");
		} else {
		    ShowMessage("Interrupt!");

		}
		return;
	    };
	    secondWhiteAnalyzer = calibrator.SecondWhiteAnalyzer;

	    //=================================================================
	    // 存檔
	    //=================================================================
	    calibrator.storeDGLut2DGLutFile(dgLutFile, dglut);

	    if (true == CheckBox_MemoryMeasure->Checked
		&& FakeMode::None != MainForm->mm->FakeMeasureMode) {
		//提供memory功能
		MainForm->setDummyMeterFile(dgLutFile);
		this->Button_Run->Enabled = true;
		this->Button_MeaRun->Enabled = false;
	    }
	    //要release掉, 才可以讀取該檔;但是要在set dummy後release, 要不然dummy沒東西可設
	    //dgLutFile.reset();
	    //寫到文字檔
	    RGBVector::storeToText(ChangeFileExt(filename.c_str(), ".txt").c_str(), dglut);
	    //=================================================================
	    RGB_vector_ptr checkResult = RGBVector::deepClone(dglut);
	    RGBVector::changeMaxValue(checkResult, bitDepth->getFRCAbilityBit());
	    MainForm->stopProgress(ProgressBar1);
	    if (RGBVector::isAscend(checkResult, 0, bitDepth->getOutputMaxDigitalCount())) {
		//檢查是否遞增且無疊階
		ShowMessage("Ok!");
	    } else {
		ShowMessage("Warning: It's not ascend!(inverse)");
	    }
	    dgLutFile.reset();
	    Util::shellExecute(filename);
	}
	catch(java::lang::IllegalStateException & ex) {
	    MainForm->stopProgress(ProgressBar1);
	    ShowMessage(ex.toString().c_str());
	}
	catch(...) {
	    ShowMessage("Abnormal stop!");
	}
	//=================================================================
    }
    __finally {
	MainForm->stopProgress(ProgressBar1);
	run = false;
	Button_MeaRun->Enabled = true;
	if (null != dgLutFile) {
	    dgLutFile.reset();
	}
    }
}

//---------------------------------------------------------------------------






void __fastcall TCCTLUTForm::Button_DebugClick(TObject * Sender)
{
    using namespace std;
    OpenDialog1->Filter = "DGCode Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	MainForm->setDummyMeterFilename(string(filename.c_str()));
	ShowMessage("Dummy meter setting Ok!");
	secondWhiteAnalyzer = MainForm->getSecondAnalyzerFromProperty();

    };

}

//---------------------------------------------------------------------------





void __fastcall TCCTLUTForm::FormShow(TObject * Sender)
{
    using namespace Dep;
    using namespace cms::lcd::calibrate;
    using namespace i2c;
    using namespace cms::measure;
    using namespace cms::lcd::calibrate;

    if (true == MainForm->newFunction) {
	//=========================================================================
	this->Button_Debug->Visible = true;
	this->Button_Reset->Visible = true;
	//=========================================================================

	this->Button_Run->Visible = true;

	CheckBox_MemoryMeasure->Visible = true;
	RadioGroup_NormalCase->Visible = true;

	//smooth intensity
	CheckBox_SmoothIntensity->Visible = true;
	Edit_SmoothIntensityStart->Visible = true;
	Edit_SmoothIntensityEnd->Visible = true;

	//native white smooth
	Label20->Visible = true;
	Edit_MaxYAdvOver->Visible = true;
	CheckBox_MaxYAdvAuto->Visible = true;

	CheckBox_KeepMaxYInMultiGen->Visible = true;

	RadioButton_NewDeHook->Visible = true;
	RadioGroup_NewDeHookPriority->Visible = true;
	CheckBox_AlterGammaCurveAtDeHook2->Visible = true;
    }
    //=========================================================================
    // function on/off relative
    //=========================================================================
    this->CheckBox_NewMethod->Checked = true;

    const MaxValue & input = bitDepth->getInputMaxValue();
    bool avoidNoise = (input == MaxValue::Int6Bit || input == MaxValue::Int8Bit);
    this->CheckBox_AvoidNoise->Enabled = avoidNoise;

    bool tconInput = bitDepth->isTCONInput();
    this->CheckBox_Expand->Visible = !tconInput;



    //=========================================================================
    // tcon relative
    //=========================================================================
    bool useTConInput = (true == tconInput || MainForm->isInTCONSetup());	// || debugMode;
    RadioButton_DeHookKeepCCT->Enabled = useTConInput;
    RadioButton_NewDeHook->Enabled = useTConInput;
    CheckBox_Feedback->Enabled = useTConInput;
    Edit_DimFixThreshold->Enabled = useTConInput;
    //=========================================================================
    //=========================================================================
    // target white relative
    //=========================================================================
    RGB_ptr refRGB = MainForm->initAnalyzer()->getReferenceRGB();
    bool useNativeWhite = refRGB->isWhite();
    if (useNativeWhite) {
	RadioButton_MaxYNative->Checked = true;
    } else {
	RadioButton_MaxYTargetWhite->Checked = true;
    }
    //=========================================================================
    setMeasureInfo();
    secondWhiteAnalyzer = MainForm->getSecondAnalyzerFromProperty();


}

void __fastcall TCCTLUTForm::RadioButton_GammaCurveClick(TObject * Sender)
{
    using namespace cms::util;
    OpenDialog1->Filter = "Desired Gamma Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	rgbGamma = RGBGamma::loadFromDesiredGamma(filename.c_str());
	unsigned int n = bitDepth->getLevel();
	if (rgbGamma != null) {
	    if (n == rgbGamma->w->size()) {
		this->CheckBox_GByPass->Enabled = true;
		return;
	    } else {
		String msg = "Desired Gamma File count is not match to the DG LUT count(need ";
		msg += n;
		msg += " records)";
		ShowMessage(msg);
	    }
	} else {
	    ShowMessage("Desired Gamma File Format is wrong! (need W/R/G/B gamma in File)");
	}
    }
    RadioButton_Gamma->Checked = true;
}


//---------------------------------------------------------------------------
void TCCTLUTForm::setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
}

void __fastcall TCCTLUTForm::TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
    TOutputFileFrame1->Button_BrowseDirClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (27 == Key) {
	//for tcon inpuse時, 關閉會跳到這邊
	if (true == run) {
	    ShowMessage("Interrupt!");
	    if (false == MeasureWindow->Visible) {
		//觸發fetcher的window closing, 可以停止量測
		TCloseAction action = caNone;
		MainForm->getComponentFetcher()->windowClosing(Sender, action);
		MainForm->mm->setMeasureWindowsVisible(false);
	    }
	    Button_MeaRun->Enabled = true;
	    run = false;
	} else {
	    this->Close();
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_GammaClick(TObject * Sender)
{
    this->CheckBox_GByPass->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::ComboBox_GammaChange(TObject * Sender)
{
    RadioButton_GammaClick(Sender);
    ComboBox_AbsGammaStartAboveGamma->Text = ComboBox_Gamma->Text;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_ExpandClick(TObject * Sender)
{
    bool checked = this->CheckBox_Expand->Checked;
    this->Panel_Expand->Visible = checked;
}

//---------------------------------------------------------------------------
bptr < cms::lcd::calibrate::MeasureCondition > TCCTLUTForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    using namespace Dep;
    bool expand = this->CheckBox_Expand->Checked;
    bptr < MeasureCondition > condition;
    const MaxValue & maxValue = bitDepth->getMeasureMaxValue();
    if (expand) {
	int lowstart = this->Edit_LowStartLevel->Text.ToInt();
	int lowend = this->Edit_LowEndLevel->Text.ToInt();
	int lowstep = this->ComboBox_LowStep->Text.ToInt();
	int highstart = this->Edit_HighStartLevel->Text.ToInt();
	int highend = this->Edit_HighEndLevel->Text.ToInt();
	int highstep = this->ComboBox_HighStep->Text.ToInt();
	condition =
	    bptr < MeasureCondition >
	    (new
	     MeasureCondition(lowstart, lowend, lowstep, highstart, highend, highstep, maxValue));
    } else {
	int start = this->Edit_StartLevel->Text.ToInt();
	int end = this->Edit_EndLevel->Text.ToInt();
	int step = this->ComboBox_LevelStep->Text.ToInt();
	//預設的第一階
	int firstStep = bitDepth->getMeasureFirstStep();
	if (bitDepth->getMeasureStart() != start
	    || bitDepth->getMeasureEnd() != end || bitDepth->getMeasureStep() != step) {
	    //如果量測條件被改變, 則不要採用原本的第一階
	    firstStep = step;
	}

	condition =
	    bptr < MeasureCondition > (new MeasureCondition(start, end, firstStep, step, maxValue));
    }
    return condition;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_ResetClick(TObject * Sender)
{
    MainForm->resetDummyMeter();
}

//---------------------------------------------------------------------------






void __fastcall TCCTLUTForm::CheckBox_NewMethodClick(TObject * Sender)
{
    bool newMethod = CheckBox_NewMethod->Checked;
    RadioButton_P1P2->Enabled = !newMethod;
    RadioButton_DefinedDim->Enabled = newMethod;
    RadioButton_MaxYNativeAdv->Enabled = newMethod;
    CheckBox_BTargetIntensity->Enabled = newMethod;
    CheckBox_MultiGen->Enabled = newMethod;
    Edit_MultiGenTimes->Enabled = newMethod;

    if (newMethod) {
	if (RadioButton_P1P2->Checked) {
	    this->RadioButton_DefinedDim->Checked = true;
	}

    } else {
	if (RadioButton_DefinedDim->Checked) {
	    this->RadioButton_P1P2->Checked = true;
	}

    }

    //RadioButton_MaxYNative->Checked = newMethod;
    //RadioButton_MaxYNone->Checked = !newMethod;
    //RadioButton_MaxYNone->Checked = true;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    if (true == Button_Run->Enabled) {
	MainForm->initCA210Meter();
	MainForm->setAnalyzerNull();
	Button_MeaRun->Enabled = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_RunClick(TObject * Sender)
{
    Button_ResetClick(Sender);
    Button_Run->Enabled = false;
    Button_MeaRunClick(Sender);
    Button_Run->Enabled = true;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_BTargetIntensityClick(TObject * Sender)
{
    bool check = this->CheckBox_BTargetIntensity->Checked;
    this->Edit_BTargetIntensity->Enabled = check;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_GammaValueClick(TObject * Sender)
{
    using namespace cms::util;
    OpenDialog1->Filter = "Desired Gamma Values Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	rgbGamma = RGBGamma::loadFromDesiredGammaValue(filename.c_str());
	unsigned int n = bitDepth->getLevel();
	if (rgbGamma != null && rgbGamma->w->size() == n) {
	    return;
	} else {
	    ShowMessage("Desired Gamma File Format is wrong!");
	}
    }
    this->RadioButton_Gamma->Checked = true;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::CheckBox_BMax2Click(TObject * Sender)
{
    bool checked = this->CheckBox_BMax2->Checked;
    Edit_BMax2Begin->Enabled = checked;
    Edit_BMax2Gamma->Enabled = checked;
}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::Edit_MaxYAdvOverChange(TObject * Sender)
{
    int over = Edit_MaxYAdvOver->Text.ToInt();
    if (over >= bitDepth->getOutputMaxDigitalCount()) {
	ShowMessage(("Must < " + _toString(bitDepth->getOutputMaxDigitalCount())).c_str());
	Edit_MaxYAdvOver->Text = bitDepth->getOutputMaxDigitalCount() - 1;
    } else {
	Edit_BMax2Begin->Text = Edit_MaxYAdvOver->Text;
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_MaxYAdvAutoClick(TObject * Sender)
{
    bool checked = CheckBox_MaxYAdvAuto->Checked;
    Edit_MaxYAdvOver->Enabled = !checked;
}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::Edit_DimGammaEndChange(TObject * Sender)
{
    int dimEnd = Edit_DimGammaEnd->Text.ToInt();
    int middleStart = dimEnd + 1;
    string text = _toString(middleStart) + "-";
    Label_MiddleZone->Caption = text.c_str();
}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::RadioGroup_NormalCaseClick(TObject * Sender)
{
    switch (RadioGroup_NormalCase->ItemIndex) {
    case 0:			//NB
	RadioButton_OriginalGamma->Checked = true;
	CheckBox_AvoidNoise->Checked = true;
	RadioButton_RBInterp->Checked = true;
	RadioButton_MaxYNative->Checked = true;
	CheckBox_BMax->Checked = true;
	break;
    case 1:
	RadioButton_3Gamma->Checked = true;
	CheckBox_AvoidNoise->Checked = false;
	RadioButton_DefinedDim->Checked = true;
	CheckBox_Feedback->Checked = true;
	RadioButton_MaxYNative->Checked = true;
	CheckBox_BMax->Checked = false;
	break;

    }
}

void TCCTLUTForm::doFeedback(int defectCount, int feedbackCount)
{
    String msg = "Defect/Total FeedBack: ";
    msg = msg + defectCount + "/" + feedbackCount;
    StatusBar1->Panels->Items[0]->Text = msg;
};

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_RTargetIntensityClick(TObject * Sender)
{
    bool check = this->CheckBox_RTargetIntensity->Checked;
    this->Edit_RTargetIntensity->Enabled = check;
}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::FormMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    TOutputFileFrame1->updateWarning();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_SmoothIntensityClick(TObject * Sender)
{
    bool checked = CheckBox_SmoothIntensity->Checked;
    Edit_SmoothIntensityStart->Enabled = checked;
    Edit_SmoothIntensityEnd->Enabled = checked;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Edit_DefinedDimUnderChange(TObject * Sender)
{
    Edit_SmoothIntensityStart->Text = Edit_DefinedDimUnder->Text;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_AbsoluteGammaClick(TObject * Sender)
{
    Edit_AbsGammaStart->Enabled = CheckBox_AbsoluteGamma->Checked;
    ComboBox_AbsGammaStartAboveGamma->Enabled = CheckBox_AbsoluteGamma->Checked;
}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::Edit_MiddleGammaEndChange(TObject * Sender)
{
    int middleEnd = Edit_MiddleGammaEnd->Text.ToInt();
    int brightStart = middleEnd + 1;
    string text = _toString(brightStart) + "-255";
    Label_BrightZone->Caption = text.c_str();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_DeHookOrgClick(TObject * Sender)
{
    RadioButton_MaxYNative->Checked = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_DeHookEvoClick(TObject * Sender)
{
    RadioButton_MaxYNative->Checked = true;
}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::FormCreate(TObject * Sender)
{
    //int x = 1;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_MaxYNativeClick(TObject * Sender)
{
    if (RadioButton_MaxYNative->Checked && RadioButton_DeHookKeepCCT->Enabled) {
	RadioButton_DeHookKeepCCT->Checked = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_3GammaClick(TObject * Sender)
{
    this->CheckBox_GByPass->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_OriginalGammaClick(TObject * Sender)
{
    this->CheckBox_GByPass->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_NewDeHookClick(TObject * Sender)
{
    RadioGroup_NewDeHookPriority->Enabled = true;
    CheckBox_AlterGammaCurveAtDeHook2->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_DeHookKeepCCTClick(TObject * Sender)
{
    RadioGroup_NewDeHookPriority->Enabled = false;
    CheckBox_AlterGammaCurveAtDeHook2->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_DeHookNoneClick(TObject * Sender)
{
    RadioGroup_NewDeHookPriority->Enabled = false;
    CheckBox_AlterGammaCurveAtDeHook2->Enabled = false;
}

//---------------------------------------------------------------------------


