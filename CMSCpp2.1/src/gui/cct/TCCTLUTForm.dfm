object CCTLUTForm: TCCTLUTForm
  Left = 491
  Top = 237
  Width = 841
  Height = 431
  Caption = 'CCT(LUT)'
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
  OnMouseMove = FormMouseMove
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label9: TLabel
    Left = 550
    Top = 360
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2012, AU Optronics Corp., All Right Reserved.'
  end
  object Label26: TLabel
    Left = 672
    Top = 272
    Width = 62
    Height = 13
    Caption = 'Green for NB'
    Color = clMoneyGreen
    ParentColor = False
  end
  object Label27: TLabel
    Left = 736
    Top = 272
    Width = 91
    Height = 13
    Caption = 'Blue for Experiment'
    Color = clSkyBlue
    ParentColor = False
  end
  object GroupBox1: TGroupBox
    Left = 6
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
    Left = 169
    Top = 7
    Width = 169
    Height = 258
    Caption = 'Gamma'
    TabOrder = 1
    object Label16: TLabel
      Left = 72
      Top = 80
      Width = 9
      Height = 13
      Caption = '0-'
    end
    object Label_BrightZone: TLabel
      Left = 72
      Top = 128
      Width = 33
      Height = 13
      Caption = '81-255'
    end
    object Label22: TLabel
      Left = 96
      Top = 48
      Width = 11
      Height = 13
      Caption = 'as'
    end
    object Label23: TLabel
      Left = 32
      Top = 48
      Width = 34
      Height = 13
      Caption = 'Keep L'
    end
    object Label24: TLabel
      Left = 8
      Top = 176
      Width = 147
      Height = 13
      Caption = '=======Load Gamma======='
    end
    object Label25: TLabel
      Left = 8
      Top = 64
      Width = 150
      Height = 13
      Caption = '========================='
    end
    object Label28: TLabel
      Left = 8
      Top = 144
      Width = 150
      Height = 13
      Caption = '========================='
    end
    object Label_MiddleZone: TLabel
      Left = 72
      Top = 104
      Width = 15
      Height = 13
      Caption = '51-'
    end
    object RadioButton_Gamma: TRadioButton
      Left = 7
      Top = 13
      Width = 65
      Height = 20
      Caption = 'Gamma'
      Checked = True
      TabOrder = 0
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
      TabOrder = 1
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
    object RadioButton_OriginalGamma: TRadioButton
      Left = 7
      Top = 160
      Width = 111
      Height = 13
      Caption = 'Original Gamma'
      TabOrder = 2
      OnClick = RadioButton_OriginalGammaClick
    end
    object RadioButton_3Gamma: TRadioButton
      Left = 7
      Top = 88
      Width = 65
      Height = 17
      Caption = '3 Gamma'
      TabOrder = 3
      OnClick = RadioButton_3GammaClick
    end
    object ComboBox_DimGamma: TComboBox
      Left = 116
      Top = 77
      Width = 49
      Height = 21
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 4
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
      Left = 116
      Top = 125
      Width = 49
      Height = 21
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 5
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
      Left = 88
      Top = 77
      Width = 25
      Height = 21
      TabOrder = 6
      Text = '50'
      OnChange = Edit_DimGammaEndChange
    end
    object CheckBox_AbsoluteGamma: TCheckBox
      Left = 24
      Top = 32
      Width = 105
      Height = 17
      Caption = 'Absolute'
      TabOrder = 7
      OnClick = CheckBox_AbsoluteGammaClick
    end
    object Edit_AbsGammaStart: TEdit
      Left = 72
      Top = 48
      Width = 25
      Height = 21
      Enabled = False
      TabOrder = 8
      Text = '8'
    end
    object ComboBox_AbsGammaStartAboveGamma: TComboBox
      Left = 112
      Top = 48
      Width = 49
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 9
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
    object RadioButton_GammaCurve: TRadioButton
      Left = 7
      Top = 189
      Width = 154
      Height = 20
      Caption = 'Gamma Curve'
      TabOrder = 10
      OnClick = RadioButton_GammaCurveClick
    end
    object RadioButton_GammaValue: TRadioButton
      Left = 7
      Top = 212
      Width = 154
      Height = 13
      Caption = 'Gamma Value'
      TabOrder = 11
      OnClick = RadioButton_GammaValueClick
    end
    object CheckBox_GByPass: TCheckBox
      Left = 95
      Top = 189
      Width = 65
      Height = 20
      Caption = 'G bypass'
      Enabled = False
      TabOrder = 12
    end
    object Edit_MiddleGammaEnd: TEdit
      Left = 88
      Top = 101
      Width = 25
      Height = 21
      TabOrder = 13
      Text = '80'
      OnChange = Edit_MiddleGammaEndChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 344
    Top = 7
    Width = 156
    Height = 258
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 26
      Top = 96
      Width = 29
      Height = 13
      Caption = 'Under'
    end
    object Label7: TLabel
      Left = 26
      Top = 57
      Width = 13
      Height = 13
      Caption = 'P1'
    end
    object Label8: TLabel
      Left = 98
      Top = 57
      Width = 13
      Height = 13
      Caption = 'P2'
    end
    object Label17: TLabel
      Left = 26
      Top = 140
      Width = 29
      Height = 13
      Caption = 'Under'
    end
    object Label14: TLabel
      Left = 26
      Top = 160
      Width = 40
      Height = 13
      Caption = 'Strength'
    end
    object RadioButton_P1P2: TRadioButton
      Left = 7
      Top = 38
      Width = 78
      Height = 19
      Caption = 'P1 P2'
      TabOrder = 0
      OnClick = RadioButton_P1P2Click
    end
    object RadioButton_RBInterp: TRadioButton
      Left = 7
      Top = 77
      Width = 104
      Height = 19
      Caption = 'RB Interpolation'
      TabOrder = 1
    end
    object Edit_RBInterpUnder: TEdit
      Left = 72
      Top = 96
      Width = 59
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '50'
    end
    object Edit_P1: TEdit
      Left = 46
      Top = 57
      Width = 33
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 3
      Text = '20'
    end
    object Edit_P2: TEdit
      Left = 117
      Top = 57
      Width = 33
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '50'
    end
    object RadioButton_NoneLowLevelCorrect: TRadioButton
      Left = 7
      Top = 16
      Width = 59
      Height = 20
      Caption = 'None'
      TabOrder = 5
    end
    object RadioButton_DefinedDim: TRadioButton
      Left = 7
      Top = 121
      Width = 98
      Height = 19
      Caption = 'Defined Dim'
      Checked = True
      Enabled = False
      TabOrder = 6
      TabStop = True
    end
    object Edit_DefinedDimUnder: TEdit
      Left = 72
      Top = 140
      Width = 59
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 7
      Text = '50'
      OnChange = Edit_DefinedDimUnderChange
    end
    object Edit_DimFixThreshold: TEdit
      Left = 104
      Top = 184
      Width = 49
      Height = 21
      Enabled = False
      TabOrder = 8
      Text = '0.0001'
    end
    object CheckBox_Feedback: TCheckBox
      Left = 26
      Top = 184
      Width = 71
      Height = 20
      Caption = 'Smooth'
      Enabled = False
      TabOrder = 9
    end
    object ComboBox_DefinedDimGamma: TComboBox
      Left = 72
      Top = 160
      Width = 59
      Height = 21
      ItemHeight = 13
      TabOrder = 10
      Text = '1.0'
      Items.Strings = (
        '0.5'
        '0.6'
        '0.7'
        '0.8'
        '0.85'
        '0.9'
        '0.95'
        '1.0')
    end
  end
  object GroupBox4: TGroupBox
    Left = 671
    Top = 7
    Width = 156
    Height = 122
    Caption = 'Blue Correction'
    Color = clMoneyGreen
    ParentColor = False
    TabOrder = 3
    object Label18: TLabel
      Left = 26
      Top = 69
      Width = 27
      Height = 13
      Caption = 'Begin'
      Visible = False
    end
    object Label19: TLabel
      Left = 26
      Top = 93
      Width = 40
      Height = 13
      Caption = 'Strength'
      Visible = False
    end
    object CheckBox_BGain: TCheckBox
      Left = 7
      Top = 14
      Width = 98
      Height = 19
      Caption = 'B Intensity Gain'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
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
    object CheckBox_BMax2: TCheckBox
      Left = 7
      Top = 52
      Width = 97
      Height = 19
      Caption = 'B Max (Smooth)'
      TabOrder = 3
      Visible = False
      OnClick = CheckBox_BMax2Click
    end
    object Edit_BMax2Begin: TEdit
      Left = 72
      Top = 69
      Width = 59
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '235'
      Visible = False
    end
    object Edit_BMax2Gamma: TEdit
      Left = 72
      Top = 93
      Width = 59
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 5
      Text = '2.2'
      Visible = False
    end
  end
  object GroupBox5: TGroupBox
    Left = 671
    Top = 127
    Width = 156
    Height = 138
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_AvoidNoise: TCheckBox
      Left = 7
      Top = 14
      Width = 111
      Height = 19
      Caption = 'Avoid FRC Noise'
      Color = clMoneyGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
    end
    object CheckBox_NewMethod: TCheckBox
      Left = 7
      Top = 116
      Width = 117
      Height = 19
      Caption = 'New CCT Method'
      TabOrder = 1
      Visible = False
      OnClick = CheckBox_NewMethodClick
    end
    object CheckBox_MultiGen: TCheckBox
      Left = 7
      Top = 77
      Width = 118
      Height = 19
      Caption = 'Multi Generate'
      Color = clSkyBlue
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 2
    end
    object Edit_MultiGenTimes: TEdit
      Left = 115
      Top = 77
      Width = 33
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = '1'
    end
    object CheckBox_BTargetIntensity: TCheckBox
      Left = 7
      Top = 56
      Width = 111
      Height = 19
      Caption = 'B Target intensity'
      Color = clSkyBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 4
      OnClick = CheckBox_BTargetIntensityClick
    end
    object Edit_BTargetIntensity: TEdit
      Left = 115
      Top = 56
      Width = 33
      Height = 21
      Enabled = False
      TabOrder = 5
      Text = '100'
    end
    object CheckBox_RTargetIntensity: TCheckBox
      Left = 7
      Top = 35
      Width = 111
      Height = 19
      Caption = 'R Target intensity'
      Color = clSkyBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 6
      OnClick = CheckBox_RTargetIntensityClick
    end
    object Edit_RTargetIntensity: TEdit
      Left = 115
      Top = 35
      Width = 33
      Height = 21
      Enabled = False
      TabOrder = 7
      Text = '100'
    end
    object CheckBox_KeepMaxYInMultiGen: TCheckBox
      Left = 23
      Top = 96
      Width = 106
      Height = 17
      Caption = 'Keep MaxY'
      TabOrder = 8
      Visible = False
    end
  end
  object Button_MeaRun: TButton
    Left = 507
    Top = 306
    Width = 84
    Height = 20
    Hint = 'Measure panel characteristic and produce CCT DG LUT.'
    Caption = ' Measure&&Run'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    OnClick = Button_MeaRunClick
  end
  object Button_Debug: TButton
    Left = 595
    Top = 328
    Width = 45
    Height = 18
    Caption = 'debug'
    TabOrder = 6
    Visible = False
    OnClick = Button_DebugClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 6
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
        Font.Height = -9
      end
      inherited Label6: TLabel
        Left = 7
        Top = 46
      end
      inherited Label_Warning: TLabel
        Left = 256
        Font.Height = -9
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
    Left = 13
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
    Left = 595
    Top = 312
    Width = 45
    Height = 18
    Caption = 'reset'
    TabOrder = 9
    Visible = False
    OnClick = Button_ResetClick
  end
  object Button_Run: TButton
    Left = 507
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
    Left = 506
    Top = 7
    Width = 157
    Height = 258
    Caption = 'White Definition'
    TabOrder = 11
    object Label20: TLabel
      Left = 26
      Top = 229
      Width = 27
      Height = 13
      Caption = 'Begin'
      Visible = False
    end
    object RadioButton_MaxYNone: TRadioButton
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
      Top = 65
      Width = 130
      Height = 20
      Caption = 'Native White'
      TabOrder = 1
      OnClick = RadioButton_MaxYNativeClick
    end
    object RadioButton_MaxYNativeAdv: TRadioButton
      Left = 7
      Top = 205
      Width = 137
      Height = 19
      Caption = 'Native White (Smooth)'
      Color = clMoneyGreen
      Enabled = False
      ParentColor = False
      TabOrder = 2
    end
    object Edit_MaxYAdvOver: TEdit
      Left = 64
      Top = 229
      Width = 33
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 3
      Text = '245'
      Visible = False
      OnChange = Edit_MaxYAdvOverChange
    end
    object CheckBox_MaxYAdvAuto: TCheckBox
      Left = 106
      Top = 224
      Width = 47
      Height = 25
      Caption = 'Auto'
      Checked = True
      State = cbChecked
      TabOrder = 4
      Visible = False
      OnClick = CheckBox_MaxYAdvAutoClick
    end
    object RadioButton_MaxYTargetWhite: TRadioButton
      Left = 7
      Top = 32
      Width = 129
      Height = 17
      Caption = 'Target White'
      TabOrder = 5
    end
    object CheckBox_SmoothIntensity: TCheckBox
      Left = 24
      Top = 48
      Width = 97
      Height = 17
      Caption = 'Smooth Intensity'
      Checked = True
      State = cbChecked
      TabOrder = 6
      Visible = False
      OnClick = CheckBox_SmoothIntensityClick
    end
    object Edit_SmoothIntensityStart: TEdit
      Left = 120
      Top = 32
      Width = 33
      Height = 21
      TabOrder = 7
      Text = '50'
      Visible = False
    end
    object Edit_SmoothIntensityEnd: TEdit
      Left = 120
      Top = 56
      Width = 33
      Height = 21
      TabOrder = 8
      Text = '255'
      Visible = False
    end
    object GroupBox_DeHook: TGroupBox
      Left = 16
      Top = 80
      Width = 137
      Height = 121
      Caption = 'DeHook'
      TabOrder = 9
      object RadioButton_DeHookNone: TRadioButton
        Left = 8
        Top = 16
        Width = 105
        Height = 17
        Caption = 'None'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = RadioButton_DeHookNoneClick
      end
      object RadioButton_DeHookKeepCCT: TRadioButton
        Left = 8
        Top = 32
        Width = 105
        Height = 17
        Caption = 'Keep CCT'
        Enabled = False
        TabOrder = 1
        OnClick = RadioButton_DeHookKeepCCTClick
      end
      object RadioButton_NewDeHook: TRadioButton
        Left = 8
        Top = 48
        Width = 41
        Height = 17
        Caption = 'New'
        Enabled = False
        TabOrder = 2
        OnClick = RadioButton_NewDeHookClick
      end
      object RadioGroup_NewDeHookPriority: TRadioGroup
        Left = 56
        Top = 48
        Width = 73
        Height = 49
        Caption = 'Priority'
        Enabled = False
        ItemIndex = 1
        Items.Strings = (
          'B Gap'
          'Gamma')
        TabOrder = 3
      end
    end
    object CheckBox_AlterGammaCurveAtDeHook2: TCheckBox
      Left = 40
      Top = 176
      Width = 81
      Height = 17
      Caption = 'Alter r Curve'
      Enabled = False
      TabOrder = 10
    end
  end
  object CheckBox_MemoryMeasure: TCheckBox
    Left = 511
    Top = 288
    Width = 113
    Height = 17
    Caption = 'Memory Measure'
    TabOrder = 12
    Visible = False
  end
  object ProgressBar1: TProgressBar
    Left = 7
    Top = 360
    Width = 225
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 13
  end
  object RadioGroup_NormalCase: TRadioGroup
    Left = 671
    Top = 296
    Width = 156
    Height = 49
    Caption = 'Normal Case'
    Items.Strings = (
      'NB'
      'TV')
    TabOrder = 14
    Visible = False
    OnClick = RadioGroup_NormalCaseClick
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 383
    Width = 833
    Height = 19
    Color = clWhite
    Panels = <
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
    Left = 808
    Top = 336
  end
end
