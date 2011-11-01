object CCTLUTForm: TCCTLUTForm
  Left = 347
  Top = 327
  Width = 844
  Height = 404
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label9: TLabel
    Left = 678
    Top = 443
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2012, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 9
    Top = 9
    Width = 192
    Height = 320
    Caption = 'Gray Level Option'
    TabOrder = 0
    object Label1: TLabel
      Left = 9
      Top = 48
      Width = 63
      Height = 16
      Caption = 'Start Level'
    end
    object Label2: TLabel
      Left = 9
      Top = 80
      Width = 60
      Height = 16
      Caption = 'End Level'
    end
    object Label3: TLabel
      Left = 9
      Top = 112
      Width = 64
      Height = 16
      Caption = 'Level Step'
    end
    object Edit_StartLevel: TEdit
      Left = 80
      Top = 48
      Width = 97
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '255'
    end
    object ComboBox_LevelStep: TComboBox
      Left = 80
      Top = 112
      Width = 97
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      ItemHeight = 16
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
      Left = 80
      Top = 80
      Width = 97
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '0'
    end
    object CheckBox_Expand: TCheckBox
      Left = 9
      Top = 16
      Width = 120
      Height = 25
      Caption = 'Expand Mode'
      TabOrder = 3
      OnClick = CheckBox_ExpandClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 209
    Top = 9
    Width = 208
    Height = 199
    Caption = 'Gamma'
    TabOrder = 1
    object Label16: TLabel
      Left = 89
      Top = 49
      Width = 11
      Height = 16
      Caption = '0-'
    end
    object Label_BrightZone: TLabel
      Left = 89
      Top = 79
      Width = 39
      Height = 16
      Caption = '51-255'
    end
    object RadioButton_GammaCurve: TRadioButton
      Left = 9
      Top = 100
      Width = 112
      Height = 24
      Caption = 'Gamma Curve'
      TabOrder = 0
      OnClick = RadioButton_GammaCurveClick
    end
    object CheckBox_GByPass: TCheckBox
      Left = 33
      Top = 123
      Width = 96
      Height = 25
      Caption = 'G ByPass'
      TabOrder = 1
      Visible = False
    end
    object RadioButton_Gamma: TRadioButton
      Left = 9
      Top = 16
      Width = 80
      Height = 25
      Caption = 'Gamma'
      Checked = True
      TabOrder = 2
      TabStop = True
      OnClick = RadioButton_GammaClick
    end
    object ComboBox_Gamma: TComboBox
      Left = 89
      Top = 16
      Width = 60
      Height = 24
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 16
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
      Left = 9
      Top = 172
      Width = 137
      Height = 16
      Caption = 'Gamma Value'
      TabOrder = 4
      Visible = False
      OnClick = RadioButton_GammaValueClick
    end
    object RadioButton_OriginalGamma: TRadioButton
      Left = 9
      Top = 148
      Width = 136
      Height = 16
      Caption = 'Original Gamma'
      TabOrder = 5
    end
    object RadioButton_2Gamma: TRadioButton
      Left = 9
      Top = 59
      Width = 80
      Height = 21
      Caption = '2 Gamma'
      TabOrder = 6
    end
    object ComboBox_DimGamma: TComboBox
      Left = 138
      Top = 46
      Width = 60
      Height = 24
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 16
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
      Left = 138
      Top = 75
      Width = 60
      Height = 24
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 16
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
      Left = 102
      Top = 46
      Width = 31
      Height = 21
      TabOrder = 9
      Text = '50'
      OnChange = Edit_DimGammaEndChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 425
    Top = 9
    Width = 192
    Height = 317
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 32
      Top = 89
      Width = 37
      Height = 16
      Caption = 'Under'
    end
    object Label7: TLabel
      Left = 32
      Top = 41
      Width = 16
      Height = 16
      Caption = 'P1'
    end
    object Label8: TLabel
      Left = 121
      Top = 41
      Width = 16
      Height = 16
      Caption = 'P2'
    end
    object Label17: TLabel
      Left = 32
      Top = 153
      Width = 37
      Height = 16
      Caption = 'Under'
    end
    object Label14: TLabel
      Left = 32
      Top = 177
      Width = 49
      Height = 16
      Caption = 'Strength'
    end
    object RadioButton_P1P2: TRadioButton
      Left = 9
      Top = 17
      Width = 96
      Height = 24
      Caption = 'P1 P2'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_P1P2Click
    end
    object RadioButton_RBInterp: TRadioButton
      Left = 9
      Top = 65
      Width = 128
      Height = 24
      Caption = 'RB Interpolation'
      TabOrder = 1
    end
    object Edit_RBInterpUnder: TEdit
      Left = 89
      Top = 89
      Width = 72
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '50'
    end
    object Edit_P1: TEdit
      Left = 57
      Top = 41
      Width = 40
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 3
      Text = '20'
    end
    object Edit_P2: TEdit
      Left = 144
      Top = 41
      Width = 41
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '50'
    end
    object RadioButton_NoneLowLevelCorrect: TRadioButton
      Left = 9
      Top = 108
      Width = 72
      Height = 25
      Caption = 'None'
      TabOrder = 5
      Visible = False
    end
    object RadioButton_DefinedDim: TRadioButton
      Left = 9
      Top = 129
      Width = 120
      Height = 24
      Caption = 'Defined Dim'
      Enabled = False
      TabOrder = 6
    end
    object Edit_DefinedDimUnder: TEdit
      Left = 89
      Top = 153
      Width = 72
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 7
      Text = '50'
    end
    object CheckBox_Smoothing: TCheckBox
      Left = 32
      Top = 260
      Width = 137
      Height = 24
      Caption = 'Smooth Data'
      TabOrder = 8
      Visible = False
    end
    object Edit_DimGamma: TEdit
      Left = 89
      Top = 177
      Width = 72
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 9
      Text = '1.0'
    end
    object CheckBox_DimFix: TCheckBox
      Left = 32
      Top = 236
      Width = 87
      Height = 25
      Caption = 'Dim Fix'
      TabOrder = 10
      OnClick = CheckBox_DimFixClick
    end
    object Edit_DimFixThreshold: TEdit
      Left = 128
      Top = 207
      Width = 60
      Height = 21
      TabOrder = 11
      Text = '0.0000'
    end
    object CheckBox_Feedback: TCheckBox
      Left = 32
      Top = 207
      Width = 87
      Height = 24
      Caption = 'Feedback'
      Checked = True
      State = cbChecked
      TabOrder = 12
      OnClick = CheckBox_FeedbackClick
    end
  end
  object GroupBox4: TGroupBox
    Left = 827
    Top = 9
    Width = 192
    Height = 71
    Caption = 'Blue Correction'
    TabOrder = 3
    object CheckBox_BGain: TCheckBox
      Left = 9
      Top = 17
      Width = 120
      Height = 24
      Caption = 'B Intensity Gain'
      TabOrder = 0
    end
    object Edit_BGain: TEdit
      Left = 129
      Top = 17
      Width = 56
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox_BMax: TCheckBox
      Left = 9
      Top = 41
      Width = 96
      Height = 24
      Caption = 'B Max'
      TabOrder = 2
    end
  end
  object GroupBox5: TGroupBox
    Left = 209
    Top = 207
    Width = 208
    Height = 122
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_AvoidNoise: TCheckBox
      Left = 9
      Top = 17
      Width = 136
      Height = 24
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_NewMethod: TCheckBox
      Left = 9
      Top = 41
      Width = 144
      Height = 24
      Caption = 'New CCT Method'
      TabOrder = 1
      OnClick = CheckBox_NewMethodClick
    end
    object CheckBox_MultiGen: TCheckBox
      Left = 32
      Top = 64
      Width = 145
      Height = 17
      Caption = 'Multi Generate'
      Enabled = False
      TabOrder = 2
      Visible = False
    end
    object Edit_MultiGenTimes: TEdit
      Left = 144
      Top = 57
      Width = 33
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = '1'
      Visible = False
    end
    object CheckBox_BTargetIntensity: TCheckBox
      Left = 9
      Top = 89
      Width = 136
      Height = 23
      Caption = 'B Target intensity'
      TabOrder = 4
      OnClick = CheckBox_BTargetIntensityClick
    end
    object Edit_BTargetIntensity: TEdit
      Left = 144
      Top = 89
      Width = 41
      Height = 21
      Enabled = False
      TabOrder = 5
      Text = '100'
    end
  end
  object Button_MeaRun: TButton
    Left = 625
    Top = 377
    Width = 104
    Height = 24
    Hint = 'Measure panel characteristic and produce CCT DG LUT.'
    Caption = 'Measure&&Run'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = Button_MeaRunClick
  end
  object Button_Debug: TButton
    Left = 734
    Top = 410
    Width = 55
    Height = 16
    Caption = 'debug'
    TabOrder = 6
    Visible = False
    OnClick = Button_DebugClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 9
    Top = 337
    Width = 616
    Height = 96
    TabOrder = 7
    inherited GroupBox_OutputFile: TGroupBox
      Width = 610
      Height = 90
      inherited Label5: TLabel
        Left = 9
        Top = 28
        Font.Height = -12
      end
      inherited Label6: TLabel
        Left = 9
        Top = 57
      end
      inherited Label_Warning: TLabel
        Left = 315
        Top = 30
        Font.Height = -12
      end
      inherited Edit_Prefix: TEdit
        Top = 25
        Height = 21
        Text = 'Cal_Table'
      end
      inherited Edit_Directory: TEdit
        Top = 57
        Width = 425
        Height = 21
      end
      inherited Button_BrowseDir: TButton
        Left = 545
        Top = 57
        Width = 56
        Height = 24
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object Panel_Expand: TPanel
    Left = 17
    Top = 49
    Width = 176
    Height = 256
    Caption = 'Panel_Expand'
    TabOrder = 8
    Visible = False
    object GroupBox6: TGroupBox
      Left = 9
      Top = 9
      Width = 160
      Height = 120
      Caption = 'Low Gray Level'
      TabOrder = 0
      object Label5: TLabel
        Left = 9
        Top = 89
        Width = 64
        Height = 16
        Caption = 'Level Step'
      end
      object Label6: TLabel
        Left = 9
        Top = 57
        Width = 60
        Height = 16
        Caption = 'End Level'
      end
      object Label10: TLabel
        Left = 9
        Top = 25
        Width = 63
        Height = 16
        Caption = 'Start Level'
      end
      object ComboBox_LowStep: TComboBox
        Left = 80
        Top = 89
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        ItemHeight = 16
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
        Left = 80
        Top = 57
        Width = 73
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '0'
      end
      object Edit_LowStartLevel: TEdit
        Left = 80
        Top = 25
        Width = 73
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 2
        Text = '64'
      end
    end
    object GroupBox7: TGroupBox
      Left = 9
      Top = 128
      Width = 160
      Height = 121
      Caption = 'High Gray Level'
      TabOrder = 1
      object Label11: TLabel
        Left = 9
        Top = 25
        Width = 63
        Height = 16
        Caption = 'Start Level'
      end
      object Label12: TLabel
        Left = 9
        Top = 89
        Width = 64
        Height = 16
        Caption = 'Level Step'
      end
      object Label13: TLabel
        Left = 9
        Top = 57
        Width = 60
        Height = 16
        Caption = 'End Level'
      end
      object Edit_HighStartLevel: TEdit
        Left = 80
        Top = 25
        Width = 73
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 0
        Text = '255'
      end
      object Edit_HighEndLevel: TEdit
        Left = 80
        Top = 57
        Width = 73
        Height = 21
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '64'
      end
      object ComboBox_HighStep: TComboBox
        Left = 80
        Top = 89
        Width = 73
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        ItemHeight = 16
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
    Left = 734
    Top = 394
    Width = 55
    Height = 16
    Caption = 'reset'
    TabOrder = 9
    Visible = False
    OnClick = Button_ResetClick
  end
  object Button_Run: TButton
    Left = 625
    Top = 401
    Width = 104
    Height = 24
    Caption = 'Run'
    Enabled = False
    TabOrder = 10
    Visible = False
    OnClick = Button_RunClick
  end
  object GroupBox_KeepMaxLuminance: TGroupBox
    Left = 624
    Top = 9
    Width = 193
    Height = 317
    Caption = 'Keep Max Luminance'
    TabOrder = 11
    object Label20: TLabel
      Left = 32
      Top = 105
      Width = 35
      Height = 16
      Caption = 'Begin'
      Visible = False
    end
    object Label21: TLabel
      Left = 32
      Top = 129
      Width = 49
      Height = 16
      Caption = 'Strength'
      Visible = False
    end
    object Label18: TLabel
      Left = 32
      Top = 201
      Width = 35
      Height = 16
      Caption = 'Begin'
      Visible = False
    end
    object Label19: TLabel
      Left = 32
      Top = 225
      Width = 49
      Height = 16
      Caption = 'Strength'
      Visible = False
    end
    object RadioButton_MaxYTarget: TRadioButton
      Left = 9
      Top = 17
      Width = 72
      Height = 24
      Caption = 'None'
      Checked = True
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
      TabStop = True
    end
    object RadioButton_MaxYNative: TRadioButton
      Left = 9
      Top = 41
      Width = 160
      Height = 24
      Caption = 'Native White'
      TabOrder = 1
    end
    object RadioButton_MaxYNone: TRadioButton
      Left = 121
      Top = 17
      Width = 64
      Height = 25
      Caption = 'N/A'
      TabOrder = 2
      Visible = False
    end
    object RadioButton_MaxYNativeAdv: TRadioButton
      Left = 9
      Top = 65
      Width = 168
      Height = 24
      Caption = 'Native White (Smooth)'
      Enabled = False
      TabOrder = 3
      OnClick = RadioButton_MaxYNativeAdvClick
    end
    object Edit_MaxYAdvOver: TEdit
      Left = 89
      Top = 105
      Width = 72
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '235'
      Visible = False
      OnChange = Edit_MaxYAdvOverChange
    end
    object Edit_MaxYAdvGamma: TEdit
      Left = 89
      Top = 129
      Width = 72
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 5
      Text = '1'
      Visible = False
    end
    object CheckBox_AvoidHookNB: TCheckBox
      Left = 9
      Top = 177
      Width = 128
      Height = 24
      Caption = 'Avoid Hook'
      TabOrder = 6
      Visible = False
      OnClick = CheckBox_AvoidHookNBClick
    end
    object CheckBox_BMax2: TCheckBox
      Left = 103
      Top = 177
      Width = 120
      Height = 24
      Caption = 'B Max (Smooth)'
      TabOrder = 7
      Visible = False
      OnClick = CheckBox_BMax2Click
    end
    object Edit_BMax2Begin: TEdit
      Left = 89
      Top = 201
      Width = 72
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 8
      Text = '235'
      Visible = False
    end
    object Edit_BMax2Gamma: TEdit
      Left = 89
      Top = 225
      Width = 72
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 9
      Text = '2.2'
      Visible = False
    end
    object CheckBox_SkipInverseB: TCheckBox
      Left = 32
      Top = 160
      Width = 129
      Height = 17
      Caption = 'Skip Inverse B'
      Checked = True
      Enabled = False
      State = cbChecked
      TabOrder = 10
      Visible = False
    end
    object CheckBox_MaxYAdvAuto: TCheckBox
      Left = 32
      Top = 89
      Width = 129
      Height = 16
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
    Left = 630
    Top = 354
    Width = 139
    Height = 21
    Caption = 'Memory Measure'
    TabOrder = 12
    Visible = False
  end
  object GroupBox8: TGroupBox
    Left = 827
    Top = 87
    Width = 192
    Height = 180
    Caption = 'Test Function'
    TabOrder = 13
    object Label15: TLabel
      Left = 22
      Top = 43
      Width = 76
      Height = 16
      Caption = 'Middle Ratio'
    end
    object Edit_MiddleRatio: TEdit
      Left = 106
      Top = 43
      Width = 63
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '0.5'
    end
    object CheckBox_MiddleCCT: TCheckBox
      Left = 9
      Top = 20
      Width = 128
      Height = 23
      Caption = 'Middle CCT'
      TabOrder = 1
      OnClick = CheckBox_MiddleCCTClick
    end
  end
  object ProgressBar1: TProgressBar
    Left = 10
    Top = 433
    Width = 277
    Height = 21
    Min = 0
    Max = 100
    TabOrder = 14
  end
  object RadioGroup_NormalCase: TRadioGroup
    Left = 827
    Top = 266
    Width = 188
    Height = 60
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
