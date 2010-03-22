object CCTLUTForm: TCCTLUTForm
  Left = 203
  Top = 401
  Width = 656
  Height = 426
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 193
    Height = 129
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
    Top = 152
    Width = 193
    Height = 129
    Caption = 'Gamma'
    TabOrder = 1
    object RadioButton_GammaCurve: TRadioButton
      Left = 8
      Top = 56
      Width = 113
      Height = 25
      Caption = 'Gamma Curve'
      TabOrder = 0
    end
    object Button_LoadGammaCurve: TButton
      Left = 120
      Top = 56
      Width = 65
      Height = 25
      Caption = 'Load'
      TabOrder = 1
      OnClick = Button_LoadGammaCurveClick
    end
    object CheckBox_GByPass: TCheckBox
      Left = 8
      Top = 88
      Width = 97
      Height = 25
      Caption = 'G ByPass'
      TabOrder = 2
      Visible = False
    end
    object RadioButton_Gamma: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 25
      Caption = 'Gamma'
      Checked = True
      TabOrder = 3
      TabStop = True
    end
    object ComboBox_Gamma: TComboBox
      Left = 80
      Top = 24
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
    Height = 105
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
    Height = 265
    Caption = 'Options'
    TabOrder = 4
    object GroupBox6: TGroupBox
      Left = 8
      Top = 24
      Width = 201
      Height = 169
      Caption = 'Bit Depth'
      TabOrder = 2
      object GroupBox8: TGroupBox
        Left = 8
        Top = 24
        Width = 57
        Height = 137
        Caption = 'IN'
        TabOrder = 0
        object RadioButton_In6: TRadioButton
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = '6'
          TabOrder = 0
          OnClick = RadioButton_In6Click
        end
        object RadioButton_In8: TRadioButton
          Left = 8
          Top = 64
          Width = 40
          Height = 17
          Caption = '8'
          Checked = True
          TabOrder = 1
          TabStop = True
          OnClick = RadioButton_In8Click
        end
        object RadioButton_In10: TRadioButton
          Left = 8
          Top = 104
          Width = 40
          Height = 17
          Caption = '10'
          TabOrder = 2
          OnClick = RadioButton_In10Click
        end
      end
      object GroupBox9: TGroupBox
        Left = 72
        Top = 24
        Width = 57
        Height = 137
        Caption = 'LUT'
        TabOrder = 1
        object RadioButton_Lut10: TRadioButton
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = '10'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton_Lut12: TRadioButton
          Left = 8
          Top = 64
          Width = 40
          Height = 17
          Caption = '12'
          TabOrder = 1
        end
      end
      object GroupBox10: TGroupBox
        Left = 136
        Top = 24
        Width = 57
        Height = 137
        Caption = 'OUT'
        TabOrder = 2
        object RadioButton_Out6: TRadioButton
          Left = 8
          Top = 24
          Width = 40
          Height = 17
          Caption = '6'
          TabOrder = 0
          OnClick = RadioButton_Out6Click
        end
        object RadioButton_Out8: TRadioButton
          Left = 8
          Top = 64
          Width = 40
          Height = 17
          Caption = '8'
          Checked = True
          TabOrder = 1
          TabStop = True
          OnClick = RadioButton_Out8Click
        end
        object RadioButton_Out10: TRadioButton
          Left = 8
          Top = 104
          Width = 40
          Height = 17
          Caption = '10'
          Enabled = False
          TabOrder = 2
          OnClick = RadioButton_Out10Click
        end
      end
    end
    object CheckBox_Gamma256: TCheckBox
      Left = 112
      Top = 184
      Width = 97
      Height = 25
      Caption = 'Gamma 256'
      TabOrder = 0
      OnClick = CheckBox_Gamma256Click
    end
    object CheckBox_AvoidNoise: TCheckBox
      Left = 8
      Top = 232
      Width = 137
      Height = 25
      Caption = 'Avoid FRC Noise'
      TabOrder = 1
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 8
      Top = 200
      Width = 153
      Height = 25
      Caption = 'Keep Max Luminance'
      TabOrder = 3
    end
  end
  object GroupBox7: TGroupBox
    Left = 16
    Top = 288
    Width = 553
    Height = 89
    Caption = 'Output File'
    TabOrder = 5
    object Label5: TLabel
      Left = 8
      Top = 24
      Width = 92
      Height = 16
      Caption = 'Filename Prefix'
    end
    object Label6: TLabel
      Left = 8
      Top = 56
      Width = 95
      Height = 16
      Caption = 'Output Directory'
    end
    object Edit_Prefix: TEdit
      Left = 112
      Top = 24
      Width = 201
      Height = 24
      TabOrder = 0
      Text = 'Calib00_Table'
    end
    object Edit_Directory: TEdit
      Left = 112
      Top = 56
      Width = 369
      Height = 24
      TabOrder = 1
      Text = 'D:\Gamma Table\'
    end
    object Button_BrowseDir: TButton
      Left = 488
      Top = 56
      Width = 57
      Height = 25
      Caption = 'Browse'
      TabOrder = 2
      OnClick = Button_BrowseDirClick
    end
  end
  object Button_Run: TButton
    Left = 576
    Top = 344
    Width = 57
    Height = 25
    Caption = 'Run'
    TabOrder = 6
    OnClick = Button_RunClick
  end
  object Button_Debug: TButton
    Left = 576
    Top = 312
    Width = 57
    Height = 25
    Caption = 'Debug'
    TabOrder = 7
    Visible = False
    OnClick = Button_DebugClick
  end
  object Button_Reset: TButton
    Left = 616
    Top = 296
    Width = 17
    Height = 17
    Caption = 'R'
    TabOrder = 8
    Visible = False
    OnClick = Button_ResetClick
  end
  object OpenDialog1: TOpenDialog
    Filter = 'DGCode Files(*.xls)|*.xls'
    Options = [ofEnableSizing]
  end
end
