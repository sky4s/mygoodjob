object CCTLUTForm: TCCTLUTForm
  Left = 334
  Top = 360
  Width = 642
  Height = 473
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label9: TLabel
    Left = 228
    Top = 339
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 7
    Top = 7
    Width = 156
    Height = 254
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
      Width = 85
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '255'
    end
    object ComboBox_LevelStep: TComboBox
      Left = 65
      Top = 91
      Width = 85
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
      Width = 85
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
    Width = 162
    Height = 91
    Caption = 'Gamma'
    TabOrder = 1
    object RadioButton_GammaCurve: TRadioButton
      Left = 7
      Top = 39
      Width = 91
      Height = 20
      Caption = 'Gamma Curve'
      TabOrder = 0
      OnClick = RadioButton_GammaCurveClick
    end
    object CheckBox_GByPass: TCheckBox
      Left = 7
      Top = 65
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
      Width = 78
      Height = 21
      ImeName = #20013#25991' ('#32321#39636') - '#26032#27880#38899
      ItemHeight = 13
      TabOrder = 3
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
  end
  object GroupBox3: TGroupBox
    Left = 339
    Top = 7
    Width = 169
    Height = 254
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
      Top = 131
      Width = 29
      Height = 13
      Caption = 'Under'
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
      OnClick = RadioButton_RBInterpClick
    end
    object Edit_RBInterpUnder: TEdit
      Left = 65
      Top = 72
      Width = 66
      Height = 21
      Enabled = False
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
    object RadioButton_None: TRadioButton
      Left = 7
      Top = 88
      Width = 59
      Height = 20
      Caption = 'None'
      TabOrder = 5
      OnClick = RadioButton_NoneClick
    end
    object RadioButton_New2: TRadioButton
      Left = 7
      Top = 111
      Width = 52
      Height = 20
      Caption = 'New2'
      TabOrder = 6
      OnClick = RadioButton_New2Click
    end
    object Edit_New2Under: TEdit
      Left = 65
      Top = 131
      Width = 66
      Height = 21
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 7
      Text = '50'
    end
  end
  object GroupBox4: TGroupBox
    Left = 170
    Top = 189
    Width = 162
    Height = 72
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
      Left = 111
      Top = 14
      Width = 46
      Height = 21
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox_BMax: TCheckBox
      Left = 7
      Top = 40
      Width = 78
      Height = 19
      Caption = 'B Max'
      TabOrder = 2
    end
  end
  object GroupBox5: TGroupBox
    Left = 170
    Top = 98
    Width = 162
    Height = 91
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_AvoidNoise: TCheckBox
      Left = 7
      Top = 40
      Width = 111
      Height = 19
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 7
      Top = 14
      Width = 124
      Height = 19
      Caption = 'Keep Max Luminance'
      TabOrder = 1
    end
    object CheckBox_: TCheckBox
      Left = 7
      Top = 65
      Width = 112
      Height = 20
      Caption = 'New DG Generate'
      TabOrder = 2
    end
  end
  object Button_Run: TButton
    Left = 462
    Top = 300
    Width = 46
    Height = 19
    Caption = 'Run'
    TabOrder = 5
    OnClick = Button_RunClick
  end
  object Button_Debug: TButton
    Left = 462
    Top = 287
    Width = 46
    Height = 13
    Caption = 'debug'
    TabOrder = 6
    OnClick = Button_DebugClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 7
    Top = 267
    Width = 449
    Height = 72
    TabOrder = 7
    inherited GroupBox_OutputFile: TGroupBox
      Width = 450
      Height = 73
      inherited Label5: TLabel
        Left = 7
        Top = 20
      end
      inherited Label6: TLabel
        Left = 7
        Top = 46
      end
      inherited Edit_Prefix: TEdit
        Left = 91
        Top = 20
        Width = 163
      end
      inherited Edit_Directory: TEdit
        Left = 91
        Top = 46
        Width = 300
      end
      inherited Button_BrowseDir: TButton
        Left = 397
        Top = 46
        Width = 46
        Height = 20
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object Panel_Expand: TPanel
    Left = 14
    Top = 46
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
    Left = 462
    Top = 273
    Width = 46
    Height = 14
    Caption = 'reset'
    TabOrder = 9
    Visible = False
    OnClick = Button_ResetClick
  end
  object Button_Process: TButton
    Left = 462
    Top = 319
    Width = 46
    Height = 20
    Caption = 'Process'
    TabOrder = 10
    Visible = False
  end
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
  end
end
