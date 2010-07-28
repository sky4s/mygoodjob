object I2CTestForm: TI2CTestForm
  Left = 200
  Top = 200
  Width = 434
  Height = 356
  Caption = 'I2C Tester'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnDeactivate = FormDeactivate
  PixelsPerInch = 120
  TextHeight = 16
  object Button1: TButton
    Left = 129
    Top = 96
    Width = 80
    Height = 25
    Caption = 'Connect'
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 129
    Top = 9
    Width = 288
    Height = 80
    Caption = 'T-CON'
    TabOrder = 1
    object RadioButton_Single: TRadioButton
      Left = 9
      Top = 25
      Width = 112
      Height = 16
      Caption = 'Single T-CON'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object Edit_Single: TEdit
      Left = 121
      Top = 16
      Width = 48
      Height = 24
      TabOrder = 1
      Text = '7C'
    end
    object RadioButton_Dual: TRadioButton
      Left = 9
      Top = 48
      Width = 112
      Height = 17
      Caption = 'Dual  T-CON'
      TabOrder = 2
    end
    object Edit_Master: TEdit
      Left = 121
      Top = 49
      Width = 48
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
  object GroupBox_I2CCard: TGroupBox
    Left = 9
    Top = 9
    Width = 112
    Height = 112
    Caption = 'Card'
    TabOrder = 2
    object RadioButton_USB: TRadioButton
      Left = 9
      Top = 25
      Width = 56
      Height = 24
      Caption = 'USB'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton_LPTLarge: TRadioButton
      Left = 9
      Top = 48
      Width = 88
      Height = 25
      Caption = 'LPT Large'
      TabOrder = 1
    end
    object RadioButton_LPTSmall: TRadioButton
      Left = 9
      Top = 73
      Width = 89
      Height = 24
      Caption = 'LPT Small'
      TabOrder = 2
    end
  end
  object CheckBox_Connecting: TCheckBox
    Left = 217
    Top = 96
    Width = 104
    Height = 25
    Caption = 'Connecting'
    Enabled = False
    TabOrder = 3
    OnClick = CheckBox_ConnectingClick
  end
  object GroupBox3: TGroupBox
    Left = 9
    Top = 128
    Width = 112
    Height = 185
    Caption = 'Gamma Test'
    TabOrder = 4
    object Label1: TLabel
      Left = 9
      Top = 57
      Width = 10
      Height = 16
      Caption = 'R'
    end
    object Label2: TLabel
      Left = 9
      Top = 89
      Width = 10
      Height = 16
      Caption = 'G'
    end
    object Label3: TLabel
      Left = 9
      Top = 121
      Width = 9
      Height = 16
      Caption = 'B'
    end
    object CheckBox1: TCheckBox
      Left = 9
      Top = 25
      Width = 80
      Height = 24
      Caption = 'Enable'
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object Edit_R: TEdit
      Left = 25
      Top = 57
      Width = 72
      Height = 24
      TabOrder = 1
      Text = '0'
      OnChange = Edit_RChange
    end
    object Edit_G: TEdit
      Left = 25
      Top = 89
      Width = 72
      Height = 24
      TabOrder = 2
      Text = '0'
      OnChange = Edit_GChange
    end
    object Edit_B: TEdit
      Left = 25
      Top = 121
      Width = 72
      Height = 24
      TabOrder = 3
      Text = '0'
      OnChange = Edit_BChange
    end
    object CheckBox_IndepRGB: TCheckBox
      Left = 9
      Top = 153
      Width = 88
      Height = 24
      Caption = 'Indep RGB'
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
  end
  object GroupBox4: TGroupBox
    Left = 128
    Top = 128
    Width = 137
    Height = 185
    Caption = 'Address'
    TabOrder = 5
    object Label4: TLabel
      Left = 9
      Top = 25
      Width = 43
      Height = 16
      Caption = 'Device'
    end
    object Label5: TLabel
      Left = 9
      Top = 57
      Width = 15
      Height = 16
      Caption = 'Bit'
    end
    object Label6: TLabel
      Left = 9
      Top = 89
      Width = 48
      Height = 16
      Caption = 'Gamma'
    end
    object Edit_GammaTestAddress: TEdit
      Left = 57
      Top = 25
      Width = 72
      Height = 24
      TabOrder = 0
      Text = '4A1'
    end
    object Edit_GammaTestBit: TEdit
      Left = 57
      Top = 57
      Width = 72
      Height = 24
      TabOrder = 1
      Text = '2'
    end
    object Edit_TestRGBAdress: TEdit
      Left = 57
      Top = 89
      Width = 72
      Height = 24
      TabOrder = 2
      Text = '4A7'
    end
    object ComboBox_AddressingSize: TComboBox
      Left = 10
      Top = 128
      Width = 109
      Height = 24
      ItemHeight = 16
      ItemIndex = 0
      TabOrder = 3
      Text = '2k'
      Items.Strings = (
        '2k'
        '4k'
        '8k'
        '16k'
        '32k'
        '64k'
        '128k'
        '256k'
        '512k')
    end
  end
  object GroupBox5: TGroupBox
    Left = 272
    Top = 128
    Width = 145
    Height = 185
    Caption = 'Data'
    TabOrder = 6
    object Label7: TLabel
      Left = 9
      Top = 25
      Width = 51
      Height = 16
      Caption = 'Address'
    end
    object Edit_WriteData: TEdit
      Left = 64
      Top = 57
      Width = 73
      Height = 24
      TabOrder = 0
    end
    object Edit_ReadData: TEdit
      Left = 64
      Top = 89
      Width = 73
      Height = 24
      Color = cl3DLight
      Enabled = False
      TabOrder = 1
    end
    object Button_Write: TButton
      Left = 9
      Top = 57
      Width = 48
      Height = 24
      Caption = 'Write'
      TabOrder = 2
      OnClick = Button_WriteClick
    end
    object Button_Read: TButton
      Left = 9
      Top = 89
      Width = 48
      Height = 24
      Caption = 'Read'
      TabOrder = 3
      OnClick = Button_ReadClick
    end
    object Edit_Address: TEdit
      Left = 64
      Top = 25
      Width = 73
      Height = 24
      TabOrder = 4
      Text = '0'
    end
  end
end
