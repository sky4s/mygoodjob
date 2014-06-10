//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件
#include <dir.h>
//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TGammaMeasurementForm.h"
#include "TMainForm.h"
//#include "MeterMeasurement.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
__fastcall TGammaMeasurementForm::TGammaMeasurementForm(TComponent *
                                                        Owner):TForm(Owner),
mm(MainForm->mm), debugMode(MainForm->debugMode)
{
  run = false;

}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_MeasureClick(TObject * Sender)
{
  using namespace std;
  using namespace cms::util;
  using namespace cms::measure;
  using namespace cms::measure::meter;

  MainForm->setMeterMeasurementWaitTimes();

  String_ptr filename = this->TOutputFileFrame1->getOutputFilename();
  string stlfilename = filename->c_str();
  if (!Util::deleteExist(stlfilename))
  {
    ShowMessage("File is locked!");
    return;
  }

  bool imageMeasure = CheckBox_ImageMeasure->Checked;
  try
  {
    Button_Measure->Enabled = false;
    MainForm->showProgress(ProgressBar1);

    if (imageMeasure)           //20140609 skyforce, 可用圖片做pattern的量測功能
    {
      int start = this->Edit_StartLevel->Text.ToInt();
      int end = this->Edit_EndLevel->Text.ToInt();
      int step = this->ComboBox_LevelStep->Text.ToInt();
      AnsiString s;
//      int waitTimes = MainForm->geti
      bptr < MeterMeasurement > mm = MainForm->mm;
      int waitTimes = mm->WaitTimes;
      bptr < Meter > meter = mm->getMeter();
      XYZ_vector_ptr XYZVector(new XYZ_vector());

      MeasureWindow->Visible = true;
      for (int graylevel = start; graylevel >= step; graylevel -= step)
      {
        AnsiString filename = s.sprintf("%03d.", graylevel) + "bmp";
        if (FileExists(filename))
        {
          MeasureWindow->setImageFilename(filename.c_str());
          Application->ProcessMessages();
          Sleep(waitTimes);
          if (MainForm->linkCA210)
          {
            double_array XYZValues = meter->triggerMeasurementInXYZ();
            XYZ_ptr XYZ(new Indep::CIEXYZ(XYZValues));
            XYZVector->push_back(XYZ);
          }
          else
          {
            XYZ_ptr XYZ(new Indep::CIEXYZ(1, 2, 3));
            XYZVector->push_back(XYZ);
          }
        }
        else
        {
          ShowMessage("Image " + filename + " is not exisit! Stop measure.");
          break;
        }
      }

      MeasureWindow->Visible = false;

//      String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
//      string filename = astr->c_str();
      if (XYZVector->size() != 0)
      {
        Util::storeXYZxyVector(stlfilename, XYZVector, "no");
        ShowMessage("Ok!");
        Util::shellExecute(stlfilename);
      }

    }
    else
    {
      bool_vector_ptr rgbw(new bool_vector(4));
      int_vector_ptr background(new int_vector(3));
      bool flicker = this->CheckBox_FlickerFMA->Checked;

      (*rgbw)[0] = this->CheckBox_R->Checked;
      (*rgbw)[1] = this->CheckBox_G->Checked;
      (*rgbw)[2] = this->CheckBox_B->Checked;
      (*rgbw)[3] = this->CheckBox_W->Checked;

      (*background)[0] = Edit_BackgroundR->Text.ToInt();
      (*background)[1] = Edit_BackgroundG->Text.ToInt();
      (*background)[2] = Edit_BackgroundB->Text.ToInt();

      bool customPattern = RadioButton_TCONInputCustomPattern->Checked;
      if (customPattern)
      {
        (*rgbw)[0] = false;
        (*rgbw)[1] = false;
        (*rgbw)[2] = false;
        (*rgbw)[3] = true;
        (*background)[0] = 0;
        (*background)[1] = 0;
        (*background)[2] = 0;
      }

      if (false == (*rgbw)[0] && false == (*rgbw)[1] && false == (*rgbw)[2]
          && false == (*rgbw)[3])
      {
        ShowMessage("Select at least one color.");
        return;
      }

      if (measure
          (rgbw, background, getMeasureCondition(), flicker, stlfilename))
      {
        MainForm->stopProgress(ProgressBar1);
        ShowMessage(" Ok ! ");
        Util::shellExecute(stlfilename);        //Open file
      }
    }
  }
  __finally
  {
    MainForm->stopProgress(ProgressBar1);
    Button_Measure->Enabled = true;
  }

}

bptr < cms::lcd::calibrate::MeasureCondition >
  TGammaMeasurementForm::getMeasureCondition()
{
  using namespace cms::lcd::calibrate;
  using namespace Dep;

  int start = this->Edit_StartLevel->Text.ToInt();
  int end = this->Edit_EndLevel->Text.ToInt();
  int step = this->ComboBox_LevelStep->Text.ToInt();
  //bool is10BitInMeasurement = CheckBox_10BitInMeasurement->Checked;
  bool is10BitInMeasurement = RadioGroup_10BitInMeasurement->ItemIndex;
  int AgingMeasureStep = ComboBox_AgingMeasureStep->Text.ToInt();

  bptr < MeasureCondition > condition;
  if (null == dgcodeTable)
  {
    if (bitDepth->isDirectGamma())
    {
      start = bitDepth->getMeasureStart();
      end = bitDepth->getMeasureEnd();
      step = bitDepth->getMeasureStep();

      condition =
        bptr < MeasureCondition >
        (new
         MeasureCondition(start, end, step, step,
                          bitDepth->getMeasureMaxValue()));
    }
    else if (bitDepth->isAgingMode())
    {
      bool NullDgCodeTable = true;

      condition =
        bptr < MeasureCondition >
        (new
         MeasureCondition(is10BitInMeasurement, AgingMeasureStep,
                          NullDgCodeTable));

    }
    else
    {
      condition =
        bptr < MeasureCondition >
        (new
         MeasureCondition(start, end, step, step,
                          bitDepth->getMeasureMaxValue()));
    }

  }
  else
  {
    int start = this->Edit_StartLevelT->Text.ToInt();
    int end = this->Edit_EndLevelT->Text.ToInt();
    int size = dgcodeTable->size();
    bool isAgingSource = MeasureWindow->isAgingSource();

    if (RadioButton_TCONInputCustomPattern->Checked)
    {
      start = 0;
      end = Edit_CustormPatternCount->Text.ToInt();
    }

    RGB_vector_ptr measureTable(new RGB_vector());

    if (is10BitInMeasurement)
    {
      if (!isAgingSource)
      {

        double_vector_ptr *rgbDoubleVector =
          RGBVector::toRGBDoubleVector(dgcodeTable);
        double_vector_ptr keys(new double_vector());
        const MaxValue & lutBit = dgLutBitDepth->getLutMaxValue();
        //double max = MaxValue::Real12Bit.max;
        for (int x = 0; x < size; x++)
        {
          keys->push_back(x);
          //限制DG的最大值
          /*double r = (*rgbDoubleVector[0])[x];
             (*rgbDoubleVector[0])[x] = r > max ? max : r;
             double g = (*rgbDoubleVector[1])[x];
             (*rgbDoubleVector[1])[x] = g > max ? max : g;
             double b = (*rgbDoubleVector[2])[x];
             (*rgbDoubleVector[1])[x] = b > max ? max : b; */
        }
        Interpolation1DLUT rlut(keys, rgbDoubleVector[0]);
        Interpolation1DLUT glut(keys, rgbDoubleVector[1]);
        Interpolation1DLUT blut(keys, rgbDoubleVector[2]);

        for (int x = start; x <= end; x++)
        {
          double key = x / 4.;
          RGB_ptr rgb(new RGBColor(lutBit));

          rgb->R = rlut.getValue(key);
          rgb->G = glut.getValue(key);
          rgb->B = blut.getValue(key);
          measureTable->push_back(rgb);
        }

        measureTable = RGBVector::reverse(measureTable);
      }
      else
      {
        for (int x = start; x < size; x++)
        {
          RGB_ptr rgb = (*dgcodeTable)[x];
          measureTable->push_back(rgb);
        }
      }


    }
    else
    {
      if (!isAgingSource)
      {
        bool input10Bit =
          MaxValue::Int10Bit == dgLutBitDepth->getInputMaxValue();
        for (int x = start; x <= end; x++)
        {
          RGB_ptr rgb = (*dgcodeTable)[x];

          if (input10Bit && x == end)
          {
            RGB_ptr rgb0 = (*dgcodeTable)[x - 1];

            RGB_ptr rgbMeasure(new RGBColor(rgb0->getMaxValue()));
            rgbMeasure->R = (rgb->R - rgb0->R) / 4. * 3 + rgb0->R;
            rgbMeasure->G = (rgb->G - rgb0->G) / 4. * 3 + rgb0->G;
            rgbMeasure->B = (rgb->B - rgb0->B) / 4. * 3 + rgb0->B;
            measureTable->push_back(rgbMeasure);
          }
          else
          {
            measureTable->push_back(rgb);
          }
        }
        measureTable = RGBVector::reverse(measureTable);
      }
      else
      {
        for (int x = start; x < size; x++)
        {
          RGB_ptr rgb = (*dgcodeTable)[x];
          measureTable->push_back(rgb);
        }
      }
    }

    condition =
      bptr < MeasureCondition >
      (new
       MeasureCondition(measureTable, bitDepth, is10BitInMeasurement,
                        AgingMeasureStep));
  }
  return condition;
};


//---------------------------------------------------------------------------
void TGammaMeasurementForm::setBitDepthProcessor(bptr <
                                                 cms::lcd::BitDepthProcessor >
                                                 bitDepth)
{
  this->bitDepth = bitDepth;
}

//---------------------------------------------------------------------------


void TGammaMeasurementForm::setMeasureInfo()
{
  using namespace cms::util;
  int start = bitDepth->getMeasureStart();
  int step = bitDepth->getMeasureStep();
  this->Edit_StartLevel->Text = Util::toString(start).c_str();
  this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};

//---------------------------------------------------------------------------
bool TGammaMeasurementForm::measure(bool_vector_ptr rgbw,
                                    int_vector_ptr background,
                                    bptr <
                                    cms::lcd::calibrate::MeasureCondition >
                                    measureCondition, bool flicker,
                                    const std::string & filename)
{
  using namespace Dep;
  using namespace std;
  using namespace cms::colorformat;
  using namespace cms::measure;
  using namespace cms::util;

  mm->resetMeasurePatchVector();        //先清空，避免程式沒關，量測愈來愈多資料問題  byBS+ 20140509

  Patch_vector_ptr vectors[4];
  mt = bptr < MeasureTool > (new MeasureTool(mm));
  bool inverseMeasure = MainForm->CheckBox_InverseMeasure->Checked;
  mt->InverseMeasure = inverseMeasure;
  MeasureWindow->addWindowListener(mt);
  RampMeasureFile measureFile(filename, Create);
  //debugMode = false;
  if (!debugMode)
  {
    run = true;
    try
    {

      foreach(const Channel & ch, *Channel::RGBWChannel)
      {
        int index = ch.getArrayIndex();
        index = (Channel::W == ch) ? 3 : index;
        if (true == (*rgbw)[index])
        {
          vectors[index] = mt->rampMeasure(ch, background, measureCondition);
          if (null == vectors[index])
          {
            return false;
          }
        }
        else
        {
          vectors[index] = nil_Patch_vector_ptr;
        }
      }
    }
    __finally
    {
      run = false;
    }
    measureFile.setMeasureData(vectors[3], vectors[0], vectors[1], vectors[2],
                               false);
    measureFile.setMeasureData(vectors[3], vectors[0], vectors[1], vectors[2],
                               true);
    if (null != vectors[3])
    {
      measureFile.setDeltaData(vectors[3]);
    }

    Patch_vector_ptr measurePatchVector = mm->MeasurePatchVector;
    if (null != measurePatchVector && measurePatchVector->size() != 0)
    {
      measureFile.setMeasure(measurePatchVector);
    }
  }
  if (null != property)
  {
    //property->store(measureFile);
    measureFile.addProperty(property);
  }
  return true;
};

//---------------------------------------------------------------------------
void TGammaMeasurementForm::tconMeasure(bool_vector_ptr rgbw, int start,
                                        int end, int step,
                                        const std::string & filename)
{
  using namespace Dep;
  Channel_vector_ptr channels = Channel::RGBWChannel;
  //int size = channels->size();
};

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormShow(TObject * Sender)
{
  bool PanelPGInputShow = bitDepth->isDirectGamma() || bitDepth->isAgingMode()
    || MainForm->isInTCONSetup();

  if (PanelPGInputShow)
  {
    this->Panel_PGInput->Visible = true;
    this->Panel_PCInput->Visible = false;
    this->CheckBox_ImageMeasure->Visible = false;
  }
  else
  {
    this->Panel_PGInput->Visible = false;
    this->Panel_PCInput->Visible = true;
    this->CheckBox_ImageMeasure->Visible = true;
  }

  if (bitDepth->isAgingMode())
  {
    this->GroupBox5->Caption = " Aging Pattern Measurement(Aging / PG Mode) ";
    this->Label5->Visible = false;      // 以下Aging mode沒作用，隱藏起來
    this->Label6->Visible = false;      // 因量測數以CheckBox_10BitInMeasurement決定
    this->Edit_StartLevelT->Visible = false;
    this->Edit_EndLevelT->Visible = false;
    this->RadioButton_TCONInputCustomPattern->Visible = false;
  }
  else
  {
    this->GroupBox5->Caption = " Direct Pattern Measurement(Direct Gamma) ";
    this->Label10->Visible = false;
    this->ComboBox_AgingMeasureStep->Visible = false;
  }

  setMeasureInfo();
  fetcher = MainForm->getComponentFetcher();

  this->CheckBox_DGLoaded->Checked = false;
  this->CheckBox_DGLoaded->Enabled = false;
  Edit_GrayScaleCount->Text = " 0 ";
  Edit_StartLevelT->Text = " 0 ";
  Edit_EndLevelT->Text = " 0 ";
  dgcodeTable = (RGB_vector_ptr) ((RGB_vector *) null);

  if (true == PanelPGInputShow)
  {
    //Button_Measure->Enabled = false;
  }
#ifdef EXPERIMENT_FUNC
  CheckBox_FlickerFMA->Visible = true;
#endif
}

//---------------------------------------------------------------------------
bool TGammaMeasurementForm::checkMeasureable()
{
  bptr < cms::measure::IntensityAnalyzerIF > analyzer =
    MainForm->initAnalyzer();
  if (null != analyzer)
  {
    if (MainForm->isCA210Analyzer())
    {
      //MainForm->setAnalyzerToTargetChannel();
      return true;
    }
    else
    {
      if (null == analyzer->getReferenceColor())
      {
        ShowMessage
          ("Set \"Target White\" first or use CA-210 Intensity Analyzer");
        return false;
      }
      else
      {
        return true;
      }
    }
  }

  else
  {
    return false;
  }
}

//---------------------------------------------------------------------------


void __fastcall TGammaMeasurementForm::
TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
  TOutputFileFrame1->Button_BrowseDirClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::Button_LoadDGTableClick(TObject *
                                                               Sender)
{
  using namespace cms::colorformat;
  using namespace cms::util;
  using namespace Dep;
  OpenDialog1->Filter = "Gamma Table Files(*.xls)|*.xls";
  string currDir = Util::getCurrentDirectory();

  //OpenDialog1->InitialDir = currDir;
  if (OpenDialog1->Execute())
  {
    const AnsiString & filename = OpenDialog1->FileName;
    /*const MaxValue & maxValue =
       RadioButton_GrayScale12Bit->Checked ? MaxValue::Int12Bit : MaxValue::Int10Bit; */
    DGLutFile dgcode(filename.c_str(), ReadOnly);

    grayScaleTable = dgcode.getGammaTable();
    property = dgcode.getProperty();
    dgLutBitDepth = property->getBitDepthProcessor();
    bool lut12Bit = MaxValue::Int12Bit == dgLutBitDepth->getLutMaxValue();
    bool input10Bit = MaxValue::Int10Bit == dgLutBitDepth->getInputMaxValue();
    //RadioButton_GrayScale12Bit->Checked = lut12Bit;
    //RadioButton_GrayScale10Bit->Checked = !lut12Bit;
    RadioGroup_GrayScaleBit->ItemIndex = lut12Bit;

    this->CheckBox_DGLoaded->Checked = true;
    this->CheckBox_DGLoaded->Enabled = true;

    int size = grayScaleTable->size();
    Edit_GrayScaleCount->Text = size;
    Edit_EndLevelT->Text = size - 1;
    //此checkbox點選會決定量測的end level, 所以要擺在這個地方
    //CheckBox_10BitInMeasurement->Checked = false;
    //CheckBox_10BitInMeasurement->Checked = input10Bit;
    //RadioButton_10BitInMeasurement->Checked = false;
    //RadioButton_10BitInMeasurement->Checked = input10Bit;
    RadioGroup_10BitInMeasurement->ItemIndex = 0;
    RadioGroup_10BitInMeasurement->ItemIndex = input10Bit;

    chdir(currDir.c_str());
    Button_Measure->Enabled = true;
    dgcodeTable = grayScaleTable;

  }

}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormKeyPress(TObject * Sender,
                                                    char &Key)
{
  if (27 == Key)
  {
    if (true == run)
    {
      stopMeasure(Sender);
    }
    else
    {
      this->Close();
    }
  }
}

void TGammaMeasurementForm::stopMeasure(TObject * Sender)
{
  ShowMessage("Interrupt!");
  //const TCloseAction &None = caNone;
  if (false == MeasureWindow->Visible)
  {
    MainForm->getComponentFetcher()->windowClosing(Sender, caNone);
  }
  if (null != mt)
  {
    mt->windowClosing(Sender, caNone);
  }
  run = false;
};

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::CheckBox_DGLoadedClick(TObject *
                                                              Sender)
{
  if (false == CheckBox_DGLoaded->Checked)
  {
    this->CheckBox_DGLoaded->Enabled = false;
    grayScaleTable.reset();
    Button_Measure->Enabled = false;
    Edit_GrayScaleCount->Text = "";
  }
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormMouseMove(TObject * Sender,
                                                     TShiftState Shift, int X,
                                                     int Y)
{
  TOutputFileFrame1->updateWarning();
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::
RadioButton_TCONInputGrayScaleClick(TObject * Sender)
{
  bool grayScale = RadioButton_TCONInputGrayScale->Checked;
  //GroupBox_GrayScale->Enabled = grayScale;
  GroupBox_GrayScale->Visible = grayScale;
  GroupBox_Color->Visible = grayScale;
  bool customPattern = RadioButton_TCONInputCustomPattern->Checked;
  //GroupBox_CustomPattern->Enabled = customPattern;
  GroupBox_CustomPattern->Visible = customPattern;
  if (grayScale)
  {
    dgcodeTable = grayScaleTable;
  }
  else
  {
    dgcodeTable = customTable;
  }

}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::Button_LoadPatternClick(TObject *
                                                               Sender)
{
  using namespace cms::colorformat;
  using namespace cms::util;
  using namespace java::lang;
  using namespace Dep;
  OpenDialog1->Filter = "Pattern Files(*.xls)|*.xls";
  string currDir = Util::getCurrentDirectory();

  //OpenDialog1->InitialDir = currDir;
  if (OpenDialog1->Execute())
  {
    const AnsiString & filename = OpenDialog1->FileName;
//    const MaxValue & maxValue =
//      RadioButton_Custom12Bit->
//      Checked ? MaxValue::Int12Bit : RadioButton_Custom12Bit->
//      Checked ? MaxValue::Int10Bit : MaxValue::Int8Bit;

    bptr < SimpleExcelAccess > excel(new SimpleExcelAccess(filename.c_str()));
    bptr < DBQuery > dbquery = excel->retrieve();
    customTable = RGB_vector_ptr(new RGB_vector());

    int directGammaBit = bitDepth->is10BitDirectGamma()? 10 : 12;
    int patterhBit =
      RadioButton_Custom8Bit->Checked ? 8 : RadioButton_Custom10Bit->
      Checked ? 10 : 12;
    double gain = Math::pow(2, directGammaBit - patterhBit);
    int count = 0;

    while (dbquery->hasNext())
    {
      string_vector_ptr result = dbquery->nextResult();
      double_vector_ptr doubleResult = DBQuery::toDoubleVector(result);
      double r = (*doubleResult)[1] * gain;
      double g = (*doubleResult)[2] * gain;
      double b = (*doubleResult)[3] * gain;
      RGB_ptr rgb(new RGBColor(r, g, b));
      customTable->push_back(rgb);
      count++;
    }
    Edit_CustormPatternCount->Text = count;

    this->CheckBox_CustomLoaded->Checked = true;
    this->CheckBox_CustomLoaded->Enabled = true;

    chdir(currDir.c_str());
    Button_Measure->Enabled = true;
    dgcodeTable = customTable;
  }

}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::CheckBox_CustomLoadedClick(TObject *
                                                                  Sender)
{
  if (false == CheckBox_CustomLoaded->Checked)
  {
    this->CheckBox_CustomLoaded->Enabled = false;
    customTable.reset();
    Button_Measure->Enabled = false;
    Edit_CustormPatternCount->Text = "";
  }
}

//---------------------------------------------------------------------------




void __fastcall TGammaMeasurementForm::Button1Click(TObject * Sender)
{
  MeasureWindow->Button3Click(this);
}

//---------------------------------------------------------------------------



void __fastcall TGammaMeasurementForm::
RadioGroup_10BitInMeasurementClick(TObject * Sender)
{
  bool measureIn10Bit = RadioGroup_10BitInMeasurement->ItemIndex;
  if (measureIn10Bit)
  {
    Edit_StartLevelT->Text = 0;
    Edit_EndLevelT->Text = 1023;
  }
  else
  {
    int size = Edit_GrayScaleCount->Text.ToInt();
    Edit_StartLevelT->Text = 0;
    Edit_EndLevelT->Text = size - 1;
  }
}

//---------------------------------------------------------------------------




void __fastcall TGammaMeasurementForm::Button3Click(TObject * Sender)
{
  MeasureWindow->Button5Click(this);
}

//---------------------------------------------------------------------------

