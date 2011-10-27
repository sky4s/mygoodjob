object CCTLUTForm: TCCTLUTForm
  Left = 347
  Top = 327
  Width = 844
  Height = 404
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label9: TLabel
    Left = 551
    Top = 360
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2012, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 7
    Top = 7
    Width = 156
    Height = 260
    Caption = 'Gray Level Option'
    TabOrder = 0
    object Label1: TLabel
      Left = 7
      Top = 39
      Width = 51
      Height = 13
      Caption = 'Start Level'
    end
    object Label2: TLabel
      Left = 7
      Top = 65
      Width = 48
      Height = 13
      Caption = 'End Level'
    end
    object Label3: TLabel
      Left = 7
      Top = 91
      Width = 51
      Height = 13
      Caption = 'Level Step'
    end
    object Edit_StartLevel: TEdit
      Left = 65
      Top = 39
      Width = 79
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '255'
    end
    object ComboBox_LevelStep: TComboBox
      Left = 65
      Top = 91
      Width = 79
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      ItemHeight = 13
      TabOrder = 1
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '4'
        '8'
        '16'
        '17'
        '32'
        '34')
    end
    object Edit_EndLevel: TEdit
      Left = 65
      Top = 65
      Width = 79
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '0'
    end
    object CheckBox_Expand: TCheckBox
      Left = 7
      Top = 13
      Width = 98
      Height = 20
      Caption = 'Expand Mode'
      TabOrder = 3
      OnClick = CheckBox_ExpandClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 170
    Top = 7
    Width = 169
    Height = 162
    Caption = 'Gamma'
    TabOrder = 1
    object Label16: TLabel
      Left = 72
      Top = 40
      Width = 9
      Height = 13
      Caption = '0-'
    end
    object Label_BrightZone: TLabel
      Left = 72
      Top = 64
      Width = 33
      Height = 13
      Caption = '51-255'
    end
    object RadioButton_GammaCurve: TRadioButton
      Left = 7
      Top = 81
      Width = 91
      Height = 20
      Caption = 'Gamma Curve'
      TabOrder = 0
      OnClick = RadioButton_GammaCurveClick
    end
    object CheckBox_GByPass: TCheckBox
      Left = 27
      Top = 100
      Width = 78
      Height = 20
      Caption = 'G ByPass'
      TabOrder = 1
      Visible = False
    end
    object RadioButton_Gamma: TRadioButton
      Left = 7
      Top = 13
      Width = 65
      Height = 20
      Caption = 'Gamma'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RadioButton_GammaClick
    end
    object ComboBox_Gamma: TComboBox
      Left = 72
      Top = 13
      Width = 49
      Height = 21
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 3
      Text = '2.2'
      OnChange = ComboBox_GammaChange
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
    object RadioButton_GammaValue: TRadioButton
      Left = 7
      Top = 140
      Width = 112
      Height = 13
      Caption = 'Gamma Value'
      TabOrder = 4
      Visible = False
      OnClick = RadioButton_GammaValueClick
    end
    object RadioButton_OriginalGamma: TRadioButton
      Left = 7
      Top = 120
      Width = 111
      Height = 13
      Caption = 'Original Gamma'
      TabOrder = 5
    end
    object RadioButton_2Gamma: TRadioButton
      Left = 7
      Top = 48
      Width = 65
      Height = 17
      Caption = '2 Gamma'
      TabOrder = 6
    end
    object ComboBox_DimGamma: TComboBox
      Left = 112
      Top = 37
      Width = 49
      Height = 21
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 7
      Text = '2.4'
      OnChange = ComboBox_GammaChange
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
    object ComboBox_BrightGamma: TComboBox
      Left = 112
      Top = 61
      Width = 49
      Height = 21
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 8
      Text = '2.2'
      OnChange = ComboBox_GammaChange
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
    object Edit_DimGammaEnd: TEdit
      Left = 83
      Top = 37
      Width = 25
      Height = 21
      TabOrder = 9
      Text = '50'
      OnChange = Edit_DimGammaEndChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 345
    Top = 7
    Width = 156
    Height = 258
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 26
      Top = 72
      Width = 29
      Height = 13
      Caption = 'Under'
    end
    object Label7: TLabel
      Left = 26
      Top = 33
      Width = 13
      Height = 13
      Caption = 'P1'
    end
    object Label8: TLabel
      Left = 98
      Top = 33
      Width = 13
      Height = 13
      Caption = 'P2'
    end
    object Label17: TLabel
      Left = 26
      Top = 124
      Width = 29
      Height = 13
      Caption = 'Under'
    end
    object Label14: TLabel
      Left = 26
      Top = 144
      Width = 40
      Height = 13
      Caption = 'Strength'
    end
    object RadioButton_P1P2: TRadioButton
      Left = 7
      Top = 14
      Width = 78
      Height = 19
      Caption = 'P1 P2'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_P1P2Click
    end
    object RadioButton_RBInterp: TRadioButton
      Left = 7
      Top = 53
      Width = 104
      Height = 19
      Caption = 'RB Interpolation'
      TabOrder = 1
    end
    object Edit_RBInterpUnder: TEdit
      Left = 72
      Top = 72
      Width = 59
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '50'
    end
    object Edit_P1: TEdit
      Left = 46
      Top = 33
      Width = 33
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 3
      Text = '20'
    end
    object Edit_P2: TEdit
      Left = 117
      Top = 33
      Width = 33
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '50'
    end
    object RadioButton_NoneLowLevelCorrect: TRadioButton
      Left = 7
      Top = 88
      Width = 59
      Height = 20
      Caption = 'None'
      TabOrder = 5
      Visible = False
    end
    object RadioButton_DefinedDim: TRadioButton
      Left = 7
      Top = 105
      Width = 98
      Height = 19
      Caption = 'Defined Dim'
      Enabled = False
      TabOrder = 6
    end
    object Edit_DefinedDimUnder: TEdit
      Left = 72
      Top = 124
      Width = 59
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 7
      Text = '50'
    end
    object CheckBox_Smoothing: TCheckBox
      Left = 26
      Top = 211
      Width = 111
      Height = 20
      Caption = 'Smooth Data'
      TabOrder = 8
      Visible = False
    end
    object Edit_DimGamma: TEdit
      Left = 72
      Top = 144
      Width = 59
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 9
      Text = '1.0'
    end
    object CheckBox_DimFix: TCheckBox
      Left = 26
      Top = 192
      Width = 71
      Height = 20
      Caption = 'Dim Fix'
      TabOrder = 10
      OnClick = CheckBox_DimFixClick
    end
    object Edit_DimFixThreshold: TEdit
      Left = 104
      Top = 168
      Width = 49
      Height = 21
      TabOrder = 11
      Text = '0.0000'
    end
    object CheckBox_Feedback: TCheckBox
      Left = 26
      Top = 168
      Width = 71
      Height = 20
      Caption = 'Feedback'
      Checked = True
      State = cbChecked
      TabOrder = 12
      OnClick = CheckBox_FeedbackClick
    end
  end
  object GroupBox4: TGroupBox
    Left = 672
    Top = 7
    Width = 156
    Height = 58
    Caption = 'Blue Correction'
    TabOrder = 3
    object CheckBox_BGain: TCheckBox
      Left = 7
      Top = 14
      Width = 98
      Height = 19
      Caption = 'B Intensity Gain'
      TabOrder = 0
    end
    object Edit_BGain: TEdit
      Left = 105
      Top = 14
      Width = 45
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox_BMax: TCheckBox
      Left = 7
      Top = 33
      Width = 78
      Height = 20
      Caption = 'B Max'
      TabOrder = 2
    end
  end
  object GroupBox5: TGroupBox
    Left = 170
    Top = 168
    Width = 169
    Height = 99
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_AvoidNoise: TCheckBox
      Left = 7
      Top = 14
      Width = 111
      Height = 19
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_NewMethod: TCheckBox
      Left = 7
      Top = 33
      Width = 117
      Height = 20
      Caption = 'New CCT Method'
      TabOrder = 1
      OnClick = CheckBox_NewMethodClick
    end
    object CheckBox_MultiGen: TCheckBox
      Left = 26
      Top = 52
      Width = 118
      Height = 14
      Caption = 'Multi Generate'
      Enabled = False
      TabOrder = 2
      Visible = False
    end
    object Edit_MultiGenTimes: TEdit
      Left = 117
      Top = 46
      Width = 27
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = '1'
      Visible = False
    end
    object CheckBox_BTargetIntensity: TCheckBox
      Left = 7
      Top = 72
      Width = 111
      Height = 19
      Caption = 'B Target intensity'
      TabOrder = 4
      OnClick = CheckBox_BTargetIntensityClick
    end
    object Edit_BTargetIntensity: TEdit
      Left = 117
      Top = 72
      Width = 33
      Height = 21
      Enabled = False
      TabOrder = 5
      Text = '100'
    end
  end
  object Button_MeaRun: TButton
    Left = 508
    Top = 306
    Width = 84
    Height = 20
    Hint = 'Measure panel characteristic and produce CCT DG LUT.'
    Caption = 'Measure&&Run'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = Button_MeaRunClick
  end
  object Button_Debug: TButton
    Left = 596
    Top = 333
    Width = 45
    Height = 13
    Caption = 'debug'
    TabOrder = 6
    Visible = False
    OnClick = Button_DebugClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 7
    Top = 274
    Width = 501
    Height = 78
    TabOrder = 7
    inherited GroupBox_OutputFile: TGroupBox
      Width = 496
      Height = 73
      inherited Label5: TLabel
        Left = 7
        Top = 23
        Font.Height = -10
      end
      inherited Label6: TLabel
        Left = 7
        Top = 46
      end
      inherited Label_Warning: TLabel
        Left = 256
        Font.Height = -10
      end
      inherited Edit_Prefix: TEdit
        Left = 91
        Top = 20
        Width = 163
        Text = 'Cal_Table'
      end
      inherited Edit_Directory: TEdit
        Left = 91
        Top = 46
        Width = 345
      end
      inherited Button_BrowseDir: TButton
        Left = 443
        Top = 46
        Width = 45
        Height = 20
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object Panel_Expand: TPanel
    Left = 14
    Top = 40
    Width = 143
    Height = 208
    Caption = 'Panel_Expand'
    TabOrder = 8
    Visible = False
    object GroupBox6: TGroupBox
      Left = 7
      Top = 7
      Width = 130
      Height = 98
      Caption = 'Low Gray Level'
      TabOrder = 0
      object Label5: TLabel
        Left = 7
        Top = 72
        Width = 51
        Height = 13
        Caption = 'Level Step'
      end
      object Label6: TLabel
        Left = 7
        Top = 46
        Width = 48
        Height = 13
        Caption = 'End Level'
      end
      object Label10: TLabel
        Left = 7
        Top = 20
        Width = 51
        Height = 13
        Caption = 'Start Level'
      end
      object ComboBox_LowStep: TComboBox
        Left = 65
        Top = 72
        Width = 59
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        ItemHeight = 13
        TabOrder = 0
        Text = '8'
        Items.Strings = (
          '1'
          '2'
          '4'
          '8'
          '16'
          '32')
      end
      object Edit_LowEndLevel: TEdit
        Left = 65
        Top = 46
        Width = 59
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '0'
      end
      object Edit_LowStartLevel: TEdit
        Left = 65
        Top = 20
        Width = 59
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 2
        Text = '64'
      end
    end
    object GroupBox7: TGroupBox
      Left = 7
      Top = 104
      Width = 130
      Height = 98
      Caption = 'High Gray Level'
      TabOrder = 1
      object Label11: TLabel
        Left = 7
        Top = 20
        Width = 51
        Height = 13
        Caption = 'Start Level'
      end
      object Label12: TLabel
        Left = 7
        Top = 72
        Width = 51
        Height = 13
        Caption = 'Level Step'
      end
      object Label13: TLabel
        Left = 7
        Top = 46
        Width = 48
        Height = 13
        Caption = 'End Level'
      end
      object Edit_HighStartLevel: TEdit
        Left = 65
        Top = 20
        Width = 59
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 0
        Text = '255'
      end
      object Edit_HighEndLevel: TEdit
        Left = 65
        Top = 46
        Width = 59
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '64'
      end
      object ComboBox_HighStep: TComboBox
        Left = 65
        Top = 72
        Width = 59
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        ItemHeight = 13
        TabOrder = 2
        Text = '16'
        Items.Strings = (
          '1'
          '2'
          '4'
          '8'
          '16'
          '32')
      end
    end
  end
  object Button_Reset: TButton
    Left = 596
    Top = 320
    Width = 45
    Height = 13
    Caption = 'reset'
    TabOrder = 9
    Visible = False
    OnClick = Button_ResetClick
  end
  object Button_Run: TButton
    Left = 508
    Top = 326
    Width = 84
    Height = 19
    Caption = 'Run'
    Enabled = False
    TabOrder = 10
    Visible = False
    OnClick = Button_RunClick
  end
  object GroupBox_KeepMaxLuminance: TGroupBox
    Left = 507
    Top = 7
    Width = 157
    Height = 258
    Caption = 'Keep Max Luminance'
    TabOrder = 11
    object Label20: TLabel
      Left = 26
      Top = 85
      Width = 27
      Height = 13
      Caption = 'Begin'
      Visible = False
    end
    object Label21: TLabel
      Left = 26
      Top = 105
      Width = 40
      Height = 13
      Caption = 'Strength'
      Visible = False
    end
    object Label18: TLabel
      Left = 26
      Top = 163
      Width = 27
      Height = 13
      Caption = 'Begin'
      Visible = False
    end
    object Label19: TLabel
      Left = 26
      Top = 183
      Width = 40
      Height = 13
      Caption = 'Strength'
      Visible = False
    end
    object RadioButton_MaxYTarget: TRadioButton
      Left = 7
      Top = 14
      Width = 59
      Height = 19
      Caption = 'None'
      Checked = True
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
      TabStop = True
    end
    object RadioButton_MaxYNative: TRadioButton
      Left = 7
      Top = 33
      Width = 130
      Height = 20
      Caption = 'Native White'
      TabOrder = 1
    end
    object RadioButton_MaxYNone: TRadioButton
      Left = 98
      Top = 14
      Width = 52
      Height = 20
      Caption = 'N/A'
      TabOrder = 2
      Visible = False
    end
    object RadioButton_MaxYNativeAdv: TRadioButton
      Left = 7
      Top = 53
      Width = 137
      Height = 19
      Caption = 'Native White (Smooth)'
      Enabled = False
      TabOrder = 3
      OnClick = RadioButton_MaxYNativeAdvClick
    end
    object Edit_MaxYAdvOver: TEdit
      Left = 72
      Top = 85
      Width = 59
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '235'
      Visible = False
      OnChange = Edit_MaxYAdvOverChange
    end
    object Edit_MaxYAdvGamma: TEdit
      Left = 72
      Top = 105
      Width = 59
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 5
      Text = '1'
      Visible = False
    end
    object CheckBox_AvoidHookNB: TCheckBox
      Left = 7
      Top = 144
      Width = 104
      Height = 19
      Caption = 'Avoid Hook'
      TabOrder = 6
      Visible = False
      OnClick = CheckBox_AvoidHookNBClick
    end
    object CheckBox_BMax2: TCheckBox
      Left = 84
      Top = 144
      Width = 97
      Height = 19
      Caption = 'B Max (Smooth)'
      TabOrder = 7
      Visible = False
      OnClick = CheckBox_BMax2Click
    end
    object Edit_BMax2Begin: TEdit
      Left = 72
      Top = 163
      Width = 59
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 8
      Text = '235'
      Visible = False
    end
    object Edit_BMax2Gamma: TEdit
      Left = 72
      Top = 183
      Width = 59
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 9
      Text = '2.2'
      Visible = False
    end
    object CheckBox_SkipInverseB: TCheckBox
      Left = 26
      Top = 130
      Width = 105
      Height = 14
      Caption = 'Skip Inverse B'
      Checked = True
      Enabled = False
      State = cbChecked
      TabOrder = 10
      Visible = False
    end
    object CheckBox_MaxYAdvAuto: TCheckBox
      Left = 26
      Top = 72
      Width = 105
      Height = 13
      Caption = 'Auto'
      Checked = True
      Enabled = False
      State = cbChecked
      TabOrder = 11
      Visible = False
      OnClick = CheckBox_MaxYAdvAutoClick
    end
  end
  object CheckBox_MemoryMeasure: TCheckBox
    Left = 512
    Top = 288
    Width = 113
    Height = 17
    Caption = 'Memory Measure'
    TabOrder = 12
    Visible = False
  end
  object GroupBox8: TGroupBox
    Left = 672
    Top = 71
    Width = 156
    Height = 146
    Caption = 'Test Function'
    TabOrder = 13
    object Label15: TLabel
      Left = 18
      Top = 35
      Width = 59
      Height = 13
      Caption = 'Middle Ratio'
    end
    object Edit_MiddleRatio: TEdit
      Left = 86
      Top = 35
      Width = 51
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '0.5'
    end
    object CheckBox_MiddleCCT: TCheckBox
      Left = 7
      Top = 16
      Width = 104
      Height = 19
      Caption = 'Middle CCT'
      TabOrder = 1
      OnClick = CheckBox_MiddleCCTClick
    end
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 352
    Width = 225
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 14
  end
  object RadioGroup_NormalCase: TRadioGroup
    Left = 672
    Top = 216
    Width = 153
    Height = 49
    Caption = 'Normal Case'
    Items.Strings = (
      'NB'
      'TV')
    TabOrder = 15
    Visible = False
    OnClick = RadioGroup_NormalCaseClick
  end
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
  end
end
