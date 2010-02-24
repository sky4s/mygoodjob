object CCTLUTForm: TCCTLUTForm
  Left = 329
  Top = 244
  Width = 656
  Height = 425
  Caption = 'CCT LUT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
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
    object Edit1: TEdit
      Left = 80
      Top = 24
      Width = 105
      Height = 24
      TabOrder = 0
      Text = '255'
    end
    object ComboBox1: TComboBox
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
    object Edit2: TEdit
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
    object RadioButton2: TRadioButton
      Left = 8
      Top = 56
      Width = 113
      Height = 25
      Caption = 'Gamma Curve'
      TabOrder = 0
    end
    object Button1: TButton
      Left = 120
      Top = 56
      Width = 65
      Height = 25
      Caption = 'Load'
      TabOrder = 1
    end
    object CheckBox1: TCheckBox
      Left = 8
      Top = 88
      Width = 97
      Height = 25
      Caption = 'G ByPass'
      TabOrder = 2
    end
    object RadioButton1: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 25
      Caption = 'Gamma'
      TabOrder = 3
    end
    object ComboBox2: TComboBox
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
    Height = 129
    Caption = 'Low Level Correction'
    TabOrder = 2
    object Label4: TLabel
      Left = 32
      Top = 88
      Width = 37
      Height = 16
      Caption = 'Under'
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'P1 P2'
      TabOrder = 0
    end
    object RadioButton4: TRadioButton
      Left = 8
      Top = 56
      Width = 113
      Height = 17
      Caption = 'RB Interpolation'
      TabOrder = 1
    end
    object Edit3: TEdit
      Left = 80
      Top = 88
      Width = 105
      Height = 24
      TabOrder = 2
      Text = '50'
    end
  end
  object GroupBox4: TGroupBox
    Left = 216
    Top = 152
    Width = 193
    Height = 129
    Caption = 'Blue Correction'
    TabOrder = 3
    object CheckBox2: TCheckBox
      Left = 8
      Top = 24
      Width = 121
      Height = 25
      Caption = 'B Intensity Gain'
      TabOrder = 0
    end
    object Edit4: TEdit
      Left = 128
      Top = 24
      Width = 57
      Height = 24
      TabOrder = 1
      Text = '1.05'
    end
    object CheckBox3: TCheckBox
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
      TabOrder = 5
      object Edit_available: TEdit
        Left = 56
        Top = 144
        Width = 89
        Height = 17
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clLime
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = 'available'
      end
    end
    object RadioGroup_in: TRadioGroup
      Left = 16
      Top = 40
      Width = 57
      Height = 121
      Caption = 'IN'
      Items.Strings = (
        '6'
        '8'
        '10')
      TabOrder = 0
      OnClick = RadioGroup_inClick
    end
    object RadioGroup_lut: TRadioGroup
      Left = 80
      Top = 40
      Width = 57
      Height = 121
      Caption = 'LUT'
      Items.Strings = (
        '10'
        '12')
      TabOrder = 1
      OnClick = RadioGroup_lutClick
    end
    object RadioGroup_out: TRadioGroup
      Left = 144
      Top = 40
      Width = 57
      Height = 121
      Caption = 'OUT'
      Items.Strings = (
        '6'
        '8'
        '10')
      TabOrder = 2
      OnClick = RadioGroup_outClick
    end
    object CheckBox5: TCheckBox
      Left = 8
      Top = 200
      Width = 97
      Height = 25
      Caption = 'Gamma 256'
      TabOrder = 3
    end
    object CheckBox6: TCheckBox
      Left = 8
      Top = 232
      Width = 137
      Height = 25
      Caption = 'Avoid FRC Noise'
      TabOrder = 4
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
    object Edit5: TEdit
      Left = 112
      Top = 24
      Width = 201
      Height = 24
      TabOrder = 0
      Text = 'Calib00_Table'
    end
    object Edit6: TEdit
      Left = 112
      Top = 56
      Width = 369
      Height = 24
      TabOrder = 1
      Text = 'D:\Gamma Table\'
    end
    object Button2: TButton
      Left = 488
      Top = 56
      Width = 57
      Height = 25
      Caption = 'Browse'
      TabOrder = 2
      OnClick = Button2Click
    end
  end
  object Button3: TButton
    Left = 576
    Top = 344
    Width = 57
    Height = 25
    Caption = 'Run'
    TabOrder = 6
  end
  object OpenDialog1: TOpenDialog
    Options = [ofEnableSizing]
  end
end
