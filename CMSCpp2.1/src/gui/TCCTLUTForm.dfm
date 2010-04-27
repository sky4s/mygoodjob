object CCTLUTForm: TCCTLUTForm
  Left = 281
  Top = 302
  Width = 657
  Height = 480
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
    Top = 425
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 193
    Height = 313
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
      Width = 105
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 0
      Text = '255'
    end
    object ComboBox_LevelStep: TComboBox
      Left = 80
      Top = 112
      Width = 105
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
      Width = 105
      Height = 24
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
    Left = 217
    Top = 16
    Width = 200
    Height = 113
    Caption = 'Gamma'
    TabOrder = 1
    object RadioButton_GammaCurve: TRadioButton
      Left = 9
      Top = 48
      Width = 112
      Height = 25
      Caption = 'Gamma Curve'
      TabOrder = 0
      OnClick = RadioButton_GammaCurveClick
    end
    object Button_LoadGammaCurve: TButton
      Left = 121
      Top = 48
      Width = 64
      Height = 25
      Caption = 'Load'
      TabOrder = 1
      Visible = False
    end
    object CheckBox_GByPass: TCheckBox
      Left = 9
      Top = 80
      Width = 96
      Height = 25
      Caption = 'G ByPass'
      TabOrder = 2
      Visible = False
    end
    object RadioButton_Gamma: TRadioButton
      Left = 9
      Top = 16
      Width = 112
      Height = 25
      Caption = 'Gamma'
      Checked = True
      TabOrder = 3
      TabStop = True
      OnClick = RadioButton_GammaClick
    end
    object ComboBox_Gamma: TComboBox
      Left = 89
      Top = 16
      Width = 96
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      ItemHeight = 16
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
  end
  object GroupBox3: TGroupBox
    Left = 217
    Top = 137
    Width = 200
    Height = 192
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 32
      Top = 97
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
      Left = 121
      Top = 48
      Width = 16
      Height = 16
      Caption = 'P2'
    end
    object RadioButton_P1P2: TRadioButton
      Left = 9
      Top = 25
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
      Top = 73
      Width = 128
      Height = 24
      Caption = 'RB Interpolation'
      TabOrder = 1
      OnClick = RadioButton_RBInterpClick
    end
    object Edit_RBInterpUnder: TEdit
      Left = 80
      Top = 97
      Width = 81
      Height = 24
      Enabled = False
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 2
      Text = '50'
    end
    object Edit_P1: TEdit
      Left = 57
      Top = 48
      Width = 40
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 3
      Text = '20'
    end
    object Edit_P2: TEdit
      Left = 144
      Top = 48
      Width = 41
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 4
      Text = '50'
    end
    object RadioButton_None: TRadioButton
      Left = 9
      Top = 124
      Width = 112
      Height = 25
      Caption = 'None'
      TabOrder = 5
    end
    object RadioButton1: TRadioButton
      Left = 9
      Top = 150
      Width = 128
      Height = 25
      Caption = 'New'
      TabOrder = 6
      Visible = False
    end
  end
  object GroupBox4: TGroupBox
    Left = 425
    Top = 16
    Width = 208
    Height = 137
    Caption = 'Blue Correction'
    TabOrder = 3
    object CheckBox_BGain: TCheckBox
      Left = 9
      Top = 25
      Width = 120
      Height = 24
      Caption = 'B Intensity Gain'
      TabOrder = 0
    end
    object Edit_BGain: TEdit
      Left = 137
      Top = 25
      Width = 56
      Height = 24
      ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox_BMax: TCheckBox
      Left = 9
      Top = 57
      Width = 96
      Height = 24
      Caption = 'B Max'
      TabOrder = 2
    end
  end
  object GroupBox5: TGroupBox
    Left = 425
    Top = 160
    Width = 208
    Height = 169
    Caption = 'Options'
    TabOrder = 4
    object CheckBox_AvoidNoise: TCheckBox
      Left = 9
      Top = 57
      Width = 136
      Height = 24
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 9
      Top = 25
      Width = 152
      Height = 24
      Caption = 'Keep Max Luminance'
      TabOrder = 1
    end
  end
  object Button_Run: TButton
    Left = 576
    Top = 393
    Width = 57
    Height = 24
    Caption = 'Run'
    TabOrder = 5
    OnClick = Button_RunClick
  end
  object Button_Debug: TButton
    Left = 576
    Top = 361
    Width = 57
    Height = 24
    Caption = 'Debug'
    TabOrder = 6
    Visible = False
    OnClick = Button_DebugClick
  end
  object Button_Reset: TButton
    Left = 592
    Top = 345
    Width = 41
    Height = 16
    Caption = 'reset'
    TabOrder = 7
    Visible = False
    OnClick = Button_ResetClick
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 16
    Top = 336
    Width = 553
    Height = 89
    TabOrder = 8
    inherited GroupBox_OutputFile: TGroupBox
      Width = 554
      Height = 90
      inherited Label5: TLabel
        Left = 9
        Top = 25
      end
      inherited Label6: TLabel
        Left = 9
        Top = 57
      end
      inherited Edit_Prefix: TEdit
        Top = 25
      end
      inherited Edit_Directory: TEdit
        Top = 57
      end
      inherited Button_BrowseDir: TButton
        Left = 489
        Top = 57
        Width = 56
        Height = 24
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object Panel_Expand: TPanel
    Left = 25
    Top = 64
    Width = 176
    Height = 257
    Caption = 'Panel_Expand'
    TabOrder = 9
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
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 1
        Text = '0'
      end
      object Edit_LowStartLevel: TEdit
        Left = 80
        Top = 25
        Width = 73
        Height = 24
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
        Height = 24
        ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
        TabOrder = 0
        Text = '255'
      end
      object Edit_HighEndLevel: TEdit
        Left = 80
        Top = 57
        Width = 73
        Height = 24
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
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
  end
end
