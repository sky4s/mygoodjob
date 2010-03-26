object I2CTestForm: TI2CTestForm
  Left = 225
  Top = 176
  Width = 259
  Height = 458
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
      Checked = True
      TabOrder = 0
      TabStop = True
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
  object CheckBox_Connecting: TCheckBox
    Left = 96
    Top = 192
    Width = 105
    Height = 25
    Caption = 'Connecting'
    Enabled = False
    TabOrder = 3
    OnClick = CheckBox_ConnectingClick
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 232
    Width = 233
    Height = 185
    Caption = 'Gamma Test'
    TabOrder = 4
    object Label1: TLabel
      Left = 8
      Top = 56
      Width = 25
      Height = 25
      Caption = 'R'
    end
    object Label2: TLabel
      Left = 8
      Top = 88
      Width = 25
      Height = 25
      Caption = 'G'
    end
    object Label3: TLabel
      Left = 8
      Top = 120
      Width = 25
      Height = 25
      Caption = 'B'
    end
    object CheckBox1: TCheckBox
      Left = 8
      Top = 24
      Width = 105
      Height = 25
      Caption = 'Enable'
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object Edit_R: TEdit
      Left = 24
      Top = 56
      Width = 73
      Height = 25
      TabOrder = 1
      Text = '0'
      OnChange = Edit_RChange
    end
    object Edit_G: TEdit
      Left = 24
      Top = 88
      Width = 73
      Height = 25
      TabOrder = 2
      Text = '0'
      OnChange = Edit_GChange
    end
    object Edit_B: TEdit
      Left = 24
      Top = 120
      Width = 73
      Height = 25
      TabOrder = 3
      Text = '0'
      OnChange = Edit_BChange
    end
    object GroupBox4: TGroupBox
      Left = 120
      Top = 24
      Width = 89
      Height = 121
      Caption = 'Address'
      TabOrder = 4
      object Edit_GammaTestAddress: TEdit
        Left = 8
        Top = 24
        Width = 73
        Height = 25
        TabOrder = 0
        Text = '4A1'
      end
      object Edit_GammaTestBit: TEdit
        Left = 8
        Top = 56
        Width = 73
        Height = 25
        TabOrder = 1
        Text = '1'
      end
      object Edit_TestRGBAdress: TEdit
        Left = 8
        Top = 88
        Width = 73
        Height = 25
        TabOrder = 2
        Text = '4A7'
      end
    end
    object CheckBox_IndepRGB: TCheckBox
      Left = 8
      Top = 152
      Width = 89
      Height = 25
      Caption = 'Indep RGB'
      Checked = True
      State = cbChecked
      TabOrder = 5
    end
  end
end
