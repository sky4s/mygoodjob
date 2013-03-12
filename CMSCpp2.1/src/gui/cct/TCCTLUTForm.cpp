//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <FileCtrl.hpp>
//�����ؤ��Y���
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
    try {			//���F����__finally�ϥΪ�try
	run = true;
	if (this->TOutputFileFrame1->Warning) {
	    ShowMessage("Output file is locked! Try release file lock and retry!");
	    return;
	}
	Button_MeaRun->Enabled = false;
	MainForm->showProgress(ProgressBar1);
	//String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
	string filename = this->TOutputFileFrame1->getOutputFilename()->c_str();

	MainForm->initAnalyzer();
	MainForm->setMeterMeasurementWaitTimes();
	bptr < ComponentFetcher > fetcher = MainForm->getComponentFetcher();
	fetcher->Listener = this;
	bptr < MeterMeasurement > mm = fetcher->FirstAnalyzer->getMeterMeasurement();

	int defaultWaitTimes = mm->WaitTimes;
	mm->resetMeasurePatchVector();

	cms::lcd::calibrate::debugMode = debugMode;
	cms::lcd::calibrate::linkCA210 = MainForm->linkCA210;
	cms::lcd::calibrate::pcWithDirectGamma = MainForm->isPCwithDirectGamma();
	LCDCalibrator calibrator(fetcher, bitDepth);

	//�H�U���O�ﶵ���]�w

	//==========================================================================
	// P1P2�MRBInterp�����
	//==========================================================================
	/*if (this->RadioButton_P1P2->Checked) {
	   //��FP1P2
	   int p1 = this->Edit_P1->Text.ToInt();
	   int p2 = this->Edit_P2->Text.ToInt();
	   calibrator.setP1P2(p1, p2);
	   } else
	   if (this->RadioButton_RBInterp->Checked) {
	   //��FRBInterp
	   int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	   calibrator.setRBInterpolation(rbunder);
	   } else */
	if (this->RadioButton_DefinedDim->Checked) {
	    //�s�C�Ƕ��ץ���k
	    int under = this->Edit_DefinedDimUnder->Text.ToInt();	// + 1;
	    double gamma = this->ComboBox_DefinedDimGamma->Text.ToDouble();

	    calibrator.setDefinedDim(under, gamma);
	    calibrator.FeedbackFix = CheckBox_Feedback->Checked;

	    bool dimRBFix = CheckBox_DimRBFix->Checked;
	    int rbFixUnder = Edit_DimRBFixUnder->Text.ToInt();
	    bool autoUnder = CheckBox_RBFixAuto->Checked;
	    calibrator.setDefinedDimRBFix(rbFixUnder, dimRBFix, autoUnder);

	} else if (this->RadioButton_NoneLowLevelCorrect->Checked) {
	    calibrator.setNonDimCorrect();
	}
	//==========================================================================

	//==========================================================================
	// gamma���B�z
	//==========================================================================
	calibrator.FixInverseCIEZ = CheckBox_FixInverseCIEZ->Checked;
	if (true == CheckBox_AbsoluteGamma->Checked) {
	    bool absGamma = CheckBox_AbsoluteGamma->Checked;
	    int start = Edit_AbsGammaStart->Text.ToInt();
	    double aboveGamma = ComboBox_AbsGammaStartAboveGamma->Text.ToDouble();
	    //KeepL keepL = (0 == RadioGroup_KeepLBy->ItemIndex) ? ByGamma : ByLuminance;
	    KeepL keepL = ByGamma;
	    calibrator.setAbsoluteGamma(absGamma, start, aboveGamma, keepL);
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

	//�s��k
	calibrator.NewMethod = true;
	bool multiGen = this->CheckBox_MultiGen->Checked;
	calibrator.setMultiGen(multiGen, this->Edit_MultiGenTimes->Text.ToInt());
	calibrator.KeepMaxYInMultiGen = this->CheckBox_KeepMaxYInMultiGen->Checked;
	calibrator.LuminanceCalibration = this->CheckBox_LuminanceCalInMultiGen->Checked;
	calibrator.LuminanceCalibrationOnly = this->CheckBox_YOnly->Checked;
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
	//keep��dehook�ĦX�b�@�_, ²��ui
	if (true == RadioButton_MaxYNative->Checked) {
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

	    calibrator.DeHookMode = None;
	    bool autoIntensityInMultiGen = RadioButton_IntensityShift->Checked;
	    calibrator.AutoIntensityInMultiGen = autoIntensityInMultiGen;
	    bool targetWhiteShift = RadioButton_WhiteShift->Checked;
	    calibrator.TargetWhiteShift = targetWhiteShift;
	    bool forceAssignWhite = RadioButton_ForceAssignWhite->Checked;
	    calibrator.ForceAssignTargetWhite = forceAssignWhite;
	}
	//==========================================================================
	//�H�W���O�ﶵ���]�w
	//=================================================================
	// �]�w����, �i�J�D�y�{�}�l�B�z
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

	    //multigen�����p�U, �ˬdFRC�O�_�����}
	    if (multiGen && !tconctrl->isFRC()) {
		ShowMessage
		    ("Set FRC_EN Enable is needed in Multi-Gen, program will force to set Enable");
		tconctrl->setFRC(true);
	    }
	    //throw IllegalStateException("NULL == inverseMatrix");
	    //�}�l�q���έp��
	    RGB_vector_ptr dglut = calibrator.getCCTDGLut(getMeasureCondition(), dgLutFile);
	    if (!calibrator.componentVectorLuminanceCheckResult) {
		ShowMessage("Raw luminance of Panel is inverse!");
	    }
	    if (!calibrator.increaseZOfTarget) {
		ShowMessage("Target CIE Z is inverse!");
	    }
	    if (0 != calibrator.dgLutOpErrorMessage.Length()) {
		ShowMessage(calibrator.dgLutOpErrorMessage);
	    }
	    if (dglut == null) {

		MainForm->stopProgress(ProgressBar1);
		if (run) {
		    //�Q�������_(�޿�)

		    if (0 != calibrator.errorMessage.Length()) {
			ShowMessage("Internal abnormal stop: " + calibrator.errorMessage);
		    } else {
			ShowMessage("Internal abnormal stop!");
		    }


		} else {
		    //�Q�~�����_(�H��)
		    //ShowMessage("Interrupt!");

		}
		return;
	    };
	    secondWhiteAnalyzer = calibrator.SecondWhiteAnalyzer;

	    //=================================================================
	    // �s��
	    //=================================================================
	    calibrator.storeDGLut2DGLutFile(dgLutFile, dglut);

	    if (true == CheckBox_MemoryMeasure->Checked
		&& FakeMode::None != MainForm->mm->FakeMeasureMode) {
		//����memory�\��
		MainForm->setDummyMeterFile(dgLutFile);
		this->Button_Run->Enabled = true;
		this->Button_MeaRun->Enabled = false;
	    }
	    //�nrelease��, �~�i�HŪ������;���O�n�bset dummy��release, �n���Mdummy�S�F��i�]
	    //dgLutFile.reset();
	    //�g���r��
	    RGBVector::storeToText(ChangeFileExt(filename.c_str(), ".txt").c_str(), dglut);
	    //=================================================================
	    RGB_vector_ptr checkResult = RGBVector::deepClone(dglut);
	    RGBVector::changeMaxValue(checkResult, bitDepth->getFRCAbilityBit());
	    MainForm->stopProgress(ProgressBar1);


	    if (RGBVector::isAscend(checkResult, 0, bitDepth->getOutputMaxDigitalCount())) {
		//�ˬd�O�_���W�B�L�|��
		ShowMessage("Ok!");
	    } else {
		ShowMessage("Warning: It's not ascend!(inverse)");
	    }
	    dgLutFile.reset();

	    /*int button = MessageDlg("Do verify measurement? ", mtConfirmation,
	       TMsgDlgButtons() << mbYes << mbNo,
	       0);
	       if (button == mrYes) {
	       bool_vector_ptr rgbw(new bool_vector(4));
	       (*rgbw)[0] = false;
	       (*rgbw)[1] = false;
	       (*rgbw)[2] = false;
	       (*rgbw)[3] = true;

	       int_vector_ptr background(new int_vector(3));
	       (*background)[0] = 0;
	       (*background)[1] = 0;
	       (*background)[2] = 0;

	       bptr < MeasureCondition > condition(new MeasureCondition(dglut, bitDepth));

	       gammaMeasureForm = MainForm->getGammaMeasurementForm();
	       string verifyFilename = filename + "-verify.xls";
	       Util::deleteExist(verifyFilename);
	       gammaMeasureForm->measure(rgbw, background, condition, false, verifyFilename);
	       } */

	    Util::shellExecute(filename);
	}
	catch(java::lang::IllegalStateException & ex) {
	    //MainForm->stopProgress(ProgressBar1);
	    ShowMessage(ex.toString().c_str());
	}
	catch(java::lang::Exception & ex) {
	    //const char *exstr = ex.what();
	    ShowMessage(ex.toString().c_str());
	}

	catch(std::exception & ex) {
	    const char *exstr = ex.what();
	    ShowMessage(exstr);
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

	using namespace cms::colorformat;
	bptr < DGLutFile > dglutFile(new DGLutFile(filename.c_str(), ReadOnly));
	MainForm->setDummyMeterFile(dglutFile);
	RGB_vector_ptr gammaTableFromDGFile = dglutFile->getGammaTable();
	gammaTableFromDebugFile = RGB_vector_ptr(new RGB_vector());

	for (int x = 255; x >= 0; x--) {
	    RGB_ptr rgb = (*gammaTableFromDGFile)[x];
	    gammaTableFromDebugFile->push_back(rgb);
	}

	//MainForm->setDummyMeterFilename(string(filename.c_str()));
	ShowMessage("Dummy meter setting Ok!");
	secondWhiteAnalyzer = MainForm->getSecondAnalyzerFromProperty();
	CheckBox_MeasureRGBFromDebugFile->Visible = true;
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
    /*if (debugMode) {
       CheckBox_MeasureRGBFromDebugFile->Visible = true;
       } */

    if (true == MainForm->newFunction) {
	//=========================================================================
	this->Button_Debug->Visible = true;
	this->Button_Reset->Visible = true;
	//=========================================================================

	this->Button_Run->Visible = true;

	//CheckBox_MemoryMeasure->Visible = true;

	RadioGroup_NormalCase->Visible = true;


	//native white smooth
	Label20->Visible = true;
	Edit_MaxYAdvOver->Visible = true;
	CheckBox_MaxYAdvAuto->Visible = true;

	CheckBox_KeepMaxYInMultiGen->Visible = true;
	CheckBox_LuminanceCalInMultiGen->Visible = true;
	CheckBox_YOnly->Visible = true;

	RadioButton_NewDeHook->Visible = true;
	RadioGroup_NewDeHookPriority->Visible = true;
	CheckBox_AlterGammaCurveAtDeHook2->Visible = true;
	GroupBox_DeIntensityError->Visible = true;
    }
    //=========================================================================
    // function on/off relative
    //=========================================================================

    const MaxValue & input = bitDepth->getInputMaxValue();
    bool avoidNoise = (input == MaxValue::Int6Bit || input == MaxValue::Int8Bit);
    this->CheckBox_AvoidNoise->Enabled = avoidNoise;

    bool directGamma = bitDepth->isDirectGamma();
    this->CheckBox_Expand->Visible = !directGamma;



    //=========================================================================
    // tcon relative
    //=========================================================================
    bool useDirectGamma = (true == directGamma || MainForm->isInTCONSetup());	// || debugMode;
    RadioButton_DeHookKeepCCT->Enabled = useDirectGamma;
    RadioButton_NewDeHook->Enabled = useDirectGamma;
    CheckBox_Feedback->Enabled = useDirectGamma;
    Edit_DimFixThreshold->Enabled = useDirectGamma;
    CheckBox_MultiGen->Enabled = useDirectGamma;
    Edit_MultiGenTimes->Enabled = useDirectGamma;
    CheckBox_KeepMaxYInMultiGen->Enabled = useDirectGamma;
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
	//for direct gamma��, �����|����o��
	if (true == run) {
	    ShowMessage("Interrupt!");
	    if (false == MeasureWindow->Visible) {
		//Ĳ�ofetcher��window closing, �i�H����q��
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
    if (CheckBox_MeasureRGBFromDebugFile->Checked && null != gammaTableFromDebugFile) {
	condition =
	    bptr < MeasureCondition > (new MeasureCondition(gammaTableFromDebugFile, bitDepth));
    } else if (expand) {
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
	//�w�]���Ĥ@��
	int firstStep = bitDepth->getMeasureFirstStep();
	if (bitDepth->getMeasureStart() != start
	    || bitDepth->getMeasureEnd() != end || bitDepth->getMeasureStep() != step) {
	    //�p�G�q������Q����, �h���n�ĥέ쥻���Ĥ@��
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
	//RadioButton_RBInterp->Checked = true;
	RadioButton_MaxYNative->Checked = true;
	CheckBox_BMax->Checked = true;
	break;
    case 1:
	RadioButton_Gamma->Checked = true;
	CheckBox_AbsoluteGamma->Checked = true;
	CheckBox_AvoidNoise->Checked = false;
	RadioButton_DefinedDim->Checked = true;
	Edit_DefinedDimUnder->Text = "20";
	//CheckBox_Feedback->Checked = true;
	RadioButton_MaxYNative->Checked = true;
	RadioButton_DeHookNone->Checked = true;
	CheckBox_BMax->Checked = false;
	CheckBox_MultiGen->Checked = true;
	Edit_MultiGenTimes->Text = "1";
	break;

    }
}

void TCCTLUTForm::doFeedback(int defectCount, int feedbackCount)
{
    String msg = "Defect/Total FeedBack: ";
    msg = msg + defectCount + "/" + feedbackCount;
    StatusBar1->Panels->Items[0]->Text = msg;
};
void TCCTLUTForm::doFeedback(string msg)
{
    StatusBar1->Panels->Items[0]->Text = msg.c_str();
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
void __fastcall TCCTLUTForm::CheckBox_AbsoluteGammaClick(TObject * Sender)
{
    bool absGamma = CheckBox_AbsoluteGamma->Checked;;
    Edit_AbsGammaStart->Enabled = absGamma;
    ComboBox_AbsGammaStartAboveGamma->Enabled = absGamma;
    RadioGroup_KeepLBy->Enabled = absGamma;
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
	//RadioButton_DeHookKeepCCT->Checked = true;
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

void __fastcall TCCTLUTForm::Button1Click(TObject * Sender)
{
    /*int button =
       MessageDlg("Do verify measurement? ", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,
       0); */

}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_MultiGenClick(TObject * Sender)
{
    RadioButton_IntensityShift->Enabled = CheckBox_MultiGen->Checked;

    if (true == CheckBox_MultiGen->Checked) {
	if (true == RadioButton_MaxYTargetWhite->Checked) {
	    RadioButton_IntensityShift->Checked = true;
	}
    } else {
	//����multigen�N��IntensityShift�@�_����
	RadioButton_ForceAssignWhite->Checked = true;
    }

}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_DimRBFixClick(TObject * Sender)
{
    //CheckBox_RBFixAuto->Enabled = CheckBox_DimRBFix->Checked;
    /*if (!CheckBox_DimRBFix->Checked) {
       Edit_DimRBFixUnder->Enabled = false;
       } */
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_RBFixAutoClick(TObject * Sender)
{
    Edit_DimRBFixUnder->Enabled = !CheckBox_RBFixAuto->Checked;
}

//---------------------------------------------------------------------------

