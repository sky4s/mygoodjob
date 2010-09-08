inherited HSVForm2: THSVForm2
  Left = 301
  Top = 106
  Width = 952
  Height = 841
  OldCreateOrder = True
  PixelsPerInch = 120
  TextHeight = 16
  inherited GroupBox1: TGroupBox
    inherited Hue_Img: TImage
      Left = 454
      Top = 639
      Visible = False
    end
    inherited rg_HSV_Mode: TRadioGroup
      OnClick = nil
    end
    inherited GroupBox29: TGroupBox
      Left = 114
      Top = 632
      Visible = False
    end
    inherited btn_Hue_Img_load: TButton
      Left = 670
      Top = 636
      Visible = False
    end
    inherited GroupBox28: TGroupBox
      Height = 258
      inherited Label136: TLabel
        Visible = False
      end
      inherited lb_dif_n: TLabel
        Visible = False
      end
      inherited lb_dif_p: TLabel
        Visible = False
      end
      inherited Label192: TLabel
        Visible = False
      end
      inherited Label193: TLabel
        Visible = False
      end
      inherited sb_Hue_gain: TScrollBar
        OnChange = sb_Hue_gainChange
      end
      inherited sb_dif_n: TScrollBar
        Visible = False
      end
      inherited sb_dif_p: TScrollBar
        Visible = False
      end
      inherited sb_Sat_gain: TScrollBar
        OnChange = sb_Hue_gainChange
      end
      inherited sb_Val_gain: TScrollBar
        OnChange = sb_Hue_gainChange
      end
    end
    inherited Btn_HSV_reload: TBitBtn
      Left = 14
      Top = 637
    end
    inherited Hue_Img_Infor: TStaticText
      Left = 454
      Top = 635
      Visible = False
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 120
      Width = 577
      Height = 233
      Caption = 'HSV Change'
      TabOrder = 14
      object GroupBox3: TGroupBox
        Left = 8
        Top = 24
        Width = 81
        Height = 193
        Caption = '60'#176' Base'
        TabOrder = 0
        object RadioButton_deg0: TRadioButton
          Left = 8
          Top = 16
          Width = 65
          Height = 25
          Caption = 'R 0'#176
          Color = clRed
          ParentColor = False
          TabOrder = 0
        end
        object RadioButton_deg60: TRadioButton
          Left = 8
          Top = 40
          Width = 65
          Height = 25
          Caption = 'Y 60'#176
          Color = clYellow
          ParentColor = False
          TabOrder = 1
        end
        object RadioButton_deg120: TRadioButton
          Left = 8
          Top = 64
          Width = 65
          Height = 25
          Caption = 'G 120'#176
          Color = clLime
          ParentColor = False
          TabOrder = 2
        end
        object RadioButton_deg180: TRadioButton
          Left = 8
          Top = 88
          Width = 65
          Height = 25
          Caption = 'C 180'#176
          Color = clAqua
          ParentColor = False
          TabOrder = 3
        end
        object RadioButton_deg240: TRadioButton
          Left = 8
          Top = 112
          Width = 65
          Height = 25
          Caption = 'B 240'#176
          Color = clBlue
          ParentColor = False
          TabOrder = 4
        end
        object RadioButton_deg300: TRadioButton
          Left = 8
          Top = 136
          Width = 65
          Height = 25
          Caption = 'M 300'#176
          Color = clFuchsia
          ParentColor = False
          TabOrder = 5
        end
      end
      object GroupBox4: TGroupBox
        Left = 88
        Top = 24
        Width = 113
        Height = 193
        Caption = '30'#176' Base'
        TabOrder = 1
        object RadioButton1: TRadioButton
          Left = 8
          Top = 16
          Width = 73
          Height = 25
          Caption = 'RY 30'#176
          Color = 33023
          ParentColor = False
          TabOrder = 0
        end
        object RadioButton2: TRadioButton
          Left = 8
          Top = 40
          Width = 73
          Height = 25
          Caption = 'GY 90'#176
          Color = 65408
          ParentColor = False
          TabOrder = 1
        end
        object RadioButton3: TRadioButton
          Left = 8
          Top = 64
          Width = 73
          Height = 25
          Caption = 'GC 150'#176
          Color = 8453888
          ParentColor = False
          TabOrder = 2
        end
        object RadioButton4: TRadioButton
          Left = 8
          Top = 88
          Width = 73
          Height = 25
          Caption = 'BC 210'#176
          Color = clAqua
          ParentColor = False
          TabOrder = 3
        end
        object RadioButton5: TRadioButton
          Left = 8
          Top = 112
          Width = 73
          Height = 25
          Caption = 'BM 270'#176
          Color = clBlue
          ParentColor = False
          TabOrder = 4
        end
        object RadioButton6: TRadioButton
          Left = 8
          Top = 136
          Width = 73
          Height = 25
          Caption = 'RM 330'#176
          Color = clFuchsia
          ParentColor = False
          TabOrder = 5
        end
      end
      object GroupBox5: TGroupBox
        Left = 248
        Top = 24
        Width = 121
        Height = 193
        Caption = '15'#176' Base1'
        TabOrder = 2
      end
      object GroupBox6: TGroupBox
        Left = 376
        Top = 24
        Width = 121
        Height = 193
        Caption = '15'#176' Base2'
        TabOrder = 3
      end
    end
  end
  inherited OpenDialog1: TOpenDialog
    Left = 848
    Top = 8
  end
  inherited SaveDialog1: TSaveDialog
    Left = 824
    Top = 8
  end
end
