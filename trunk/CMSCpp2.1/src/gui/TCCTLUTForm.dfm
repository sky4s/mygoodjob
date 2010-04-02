object CCTLUTForm: TCCTLUTForm
  Left = 300
  Top = 300
  Width = 657
  Height = 415
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label9: TLabel
    Left = 288
    Top = 360
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 193
    Height = 121
    Caption = 'Gray Level Option'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 63
      Height = 16
      Caption = 'Start Level'
    end
    object Label2: TLabel
      Left = 8
      Top = 56
      Width = 60
      Height = 16
      Caption = 'End Level'
    end
    object Label3: TLabel
      Left = 8
      Top = 88
      Width = 64
      Height = 16
      Caption = 'Level Step'
    end
    object Edit_StartLevel: TEdit
      Left = 80
      Top = 24
      Width = 105
      Height = 24
      TabOrder = 0
      Text = '255'
    end
    object ComboBox_LevelStep: TComboBox
      Left = 80
      Top = 88
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 1
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '4'
        '8'
        '16'
        '32')
    end
    object Edit_EndLevel: TEdit
      Left = 80
      Top = 56
      Width = 105
      Height = 24
      TabOrder = 2
      Text = '0'
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 144
    Width = 193
    Height = 121
    Caption = 'Gamma'
    TabOrder = 1
    object RadioButton_GammaCurve: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 25
      Caption = 'Gamma Curve'
      TabOrder = 0
      OnClick = RadioButton_GammaCurveClick
    end
    object Button_LoadGammaCurve: TButton
      Left = 120
      Top = 48
      Width = 65
      Height = 25
      Caption = 'Load'
      TabOrder = 1
      Visible = False
    end
    object CheckBox_GByPass: TCheckBox
      Left = 8
      Top = 80
      Width = 97
      Height = 25
      Caption = 'G ByPass'
      TabOrder = 2
      Visible = False
    end
    object RadioButton_Gamma: TRadioButton
      Left = 8
      Top = 16
      Width = 113
      Height = 25
      Caption = 'Gamma'
      Checked = True
      TabOrder = 3
      TabStop = True
    end
    object ComboBox_Gamma: TComboBox
      Left = 80
      Top = 16
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 4
      Text = '2.4'
      Items.Strings = (
        '1.8'
        '1.9'
        '2.0'
        '2.1'
        '2.2'
        '2.3'
        '2.4'
        '2.5')
    end
  end
  object GroupBox3: TGroupBox
    Left = 216
    Top = 16
    Width = 193
    Height = 153
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 32
      Top = 104
      Width = 37
      Height = 16
      Caption = 'Under'
    end
    object Label7: TLabel
      Left = 32
      Top = 48
      Width = 16
      Height = 16
      Caption = 'P1'
    end
    object Label8: TLabel
      Left = 120
      Top = 48
      Width = 16
      Height = 16
      Caption = 'P2'
    end
    object RadioButton_P1P2: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'P1 P2'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_P1P2Click
    end
    object RadioButton_RBInterp: TRadioButton
      Left = 8
      Top = 80
      Width = 129
      Height = 17
      Caption = 'RB Interpolation'
      TabOrder = 1
      OnClick = RadioButton_RBInterpClick
    end
    object Edit_RBInterpUnder: TEdit
      Left = 80
      Top = 104
      Width = 105
      Height = 24
      Enabled = False
      TabOrder = 2
      Text = '50'
    end
    object Edit_P1: TEdit
      Left = 56
      Top = 48
      Width = 41
      Height = 24
      TabOrder = 3
      Text = '20'
    end
    object Edit_P2: TEdit
      Left = 144
      Top = 48
      Width = 41
      Height = 24
      TabOrder = 4
      Text = '50'
    end
    object RadioButton_None: TRadioButton
      Left = 8
      Top = 128
      Width = 113
      Height = 17
      Caption = 'None'
      TabOrder = 5
    end
  end
  object GroupBox4: TGroupBox
    Left = 216
    Top = 176
    Width = 193
    Height = 89
    Caption = 'Blue Correction'
    TabOrder = 3
    object CheckBox_BGain: TCheckBox
      Left = 8
      Top = 24
      Width = 121
      Height = 25
      Caption = 'B Intensity Gain'
      TabOrder = 0
    end
    object Edit_BGain: TEdit
      Left = 128
      Top = 24
      Width = 57
      Height = 24
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox_BMax: TCheckBox
      Left = 8
      Top = 56
      Width = 97
      Height = 25
      Caption = 'B Max'
      TabOrder = 2
    end
  end
  object GroupBox5: TGroupBox
    Left = 416
    Top = 16
    Width = 217
    Height = 249
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_Gamma256: TCheckBox
      Left = 120
      Top = 8
      Width = 97
      Height = 25
      Caption = 'Gamma 256'
      TabOrder = 0
      Visible = False
      OnClick = CheckBox_Gamma256Click
    end
    object CheckBox_AvoidNoise: TCheckBox
      Left = 8
      Top = 56
      Width = 137
      Height = 25
      Caption = 'Avoid FRC Noise'
      TabOrder = 1
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 8
      Top = 24
      Width = 153
      Height = 25
      Caption = 'Keep Max Luminance'
      TabOrder = 2
    end
  end
  object Button_Run: TButton
    Left = 576
    Top = 328
    Width = 57
    Height = 25
    Caption = 'Run'
    TabOrder = 5
    OnClick = Button_RunClick
  end
  object Button_Debug: TButton
    Left = 576
    Top = 296
    Width = 57
    Height = 25
    Caption = 'Debug'
    TabOrder = 6
    Visible = False
    OnClick = Button_DebugClick
  end
  object Button_Reset: TButton
    Left = 592
    Top = 280
    Width = 41
    Height = 17
    Caption = 'reset'
    TabOrder = 7
    Visible = False
    OnClick = Button_ResetClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 16
    Top = 272
    Width = 553
    Height = 88
    TabOrder = 8
    inherited GroupBox_OutputFile: TGroupBox
      inherited Button_BrowseDir: TButton
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
  end
end
