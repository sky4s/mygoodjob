object I2CTestForm: TI2CTestForm
  Left = 218
  Top = 164
  Width = 289
  Height = 374
  Caption = 'I2CTestForm'
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
  object Button1: TButton
    Left = 8
    Top = 192
    Width = 81
    Height = 25
    Caption = 'Connect'
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 96
    Width = 233
    Height = 81
    Caption = 'T-CON'
    TabOrder = 1
    object RadioButton_Single: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Single T-CON'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object Edit_Single: TEdit
      Left = 120
      Top = 16
      Width = 49
      Height = 24
      TabOrder = 1
      Text = '7C'
    end
    object RadioButton_Dual: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Dual  T-CON'
      TabOrder = 2
    end
    object Edit_Master: TEdit
      Left = 120
      Top = 49
      Width = 49
      Height = 24
      TabOrder = 3
      Text = '7C'
    end
    object Edit_Slave: TEdit
      Left = 176
      Top = 49
      Width = 49
      Height = 24
      TabOrder = 4
      Text = '7E'
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 8
    Width = 233
    Height = 73
    Caption = 'Card'
    TabOrder = 2
    object RadioButton_USB: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'USB'
      TabOrder = 0
    end
    object RadioButton_LPT: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'LPT'
      TabOrder = 1
    end
  end
  object CheckBox2: TCheckBox
    Left = 96
    Top = 192
    Width = 105
    Height = 25
    Caption = 'Connecting'
    TabOrder = 3
  end
end
