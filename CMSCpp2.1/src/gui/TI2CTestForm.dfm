object I2CTestForm: TI2CTestForm
  Left = 338
  Top = 221
  Width = 234
  Height = 300
  BiDiMode = bdRightToLeft
  Caption = 'I2C Tester'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  ParentBiDiMode = False
  Position = poDefault
  Visible = True
  OnDeactivate = FormDeactivate
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 105
    Top = 14
    Width = 65
    Height = 20
    Caption = 'Connect'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -10
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = Button1Click
  end
  object GroupBox1: TGroupBox
    Left = 225
    Top = 7
    Width = 234
    Height = 65
    Caption = 'T-CON'
    TabOrder = 1
    Visible = False
    object RadioButton_Single: TRadioButton
      Left = 7
      Top = 20
      Width = 91
      Height = 13
      Caption = 'Single T-CON'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object Edit_Single: TEdit
      Left = 98
      Top = 13
      Width = 39
      Height = 21
      TabOrder = 1
      Text = '7C'
    end
    object RadioButton_Dual: TRadioButton
      Left = 7
      Top = 39
      Width = 91
      Height = 14
      Caption = 'Dual  T-CON'
      TabOrder = 2
    end
    object Edit_Master: TEdit
      Left = 98
      Top = 40
      Width = 39
      Height = 21
      TabOrder = 3
      Text = '7C'
    end
    object Edit_Slave: TEdit
      Left = 143
      Top = 40
      Width = 40
      Height = 21
      TabOrder = 4
      Text = '7E'
    end
  end
  object GroupBox_I2CCard: TGroupBox
    Left = 223
    Top = 263
    Width = 91
    Height = 91
    Caption = 'Card'
    TabOrder = 2
    Visible = False
    object RadioButton_USB: TRadioButton
      Left = 7
      Top = 20
      Width = 46
      Height = 20
      Caption = 'USB'
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object RadioButton_LPTLarge: TRadioButton
      Left = 7
      Top = 39
      Width = 72
      Height = 20
      Caption = 'LPT Large'
      TabOrder = 1
    end
    object RadioButton_LPTSmall: TRadioButton
      Left = 7
      Top = 59
      Width = 73
      Height = 20
      Caption = 'LPT Small'
      TabOrder = 2
    end
  end
  object GroupBox3: TGroupBox
    Left = 7
    Top = 8
    Width = 91
    Height = 177
    Caption = 'Gamma Test'
    TabOrder = 3
    object Label1: TLabel
      Left = 7
      Top = 46
      Width = 8
      Height = 13
      Caption = 'R'
    end
    object Label2: TLabel
      Left = 7
      Top = 72
      Width = 8
      Height = 13
      Caption = 'G'
    end
    object Label3: TLabel
      Left = 7
      Top = 98
      Width = 7
      Height = 13
      Caption = 'B'
    end
    object Label8: TLabel
      Left = 7
      Top = 122
      Width = 11
      Height = 13
      Caption = 'W'
    end
    object CheckBox1: TCheckBox
      Left = 7
      Top = 20
      Width = 65
      Height = 20
      Caption = 'Enable'
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object Edit_R: TEdit
      Left = 20
      Top = 46
      Width = 59
      Height = 21
      TabOrder = 1
      Text = '0'
      OnChange = Edit_RChange
      OnKeyDown = Edit_RKeyDown
    end
    object Edit_G: TEdit
      Left = 20
      Top = 72
      Width = 59
      Height = 21
      TabOrder = 2
      Text = '0'
      OnChange = Edit_RChange
      OnKeyDown = Edit_RKeyDown
    end
    object Edit_B: TEdit
      Left = 20
      Top = 98
      Width = 59
      Height = 21
      TabOrder = 3
      Text = '0'
      OnChange = Edit_RChange
      OnKeyDown = Edit_RKeyDown
    end
    object CheckBox_IndepRGB: TCheckBox
      Left = 7
      Top = 148
      Width = 72
      Height = 20
      Caption = 'Indep RGB'
      Checked = True
      State = cbChecked
      TabOrder = 4
      Visible = False
    end
    object Edit_W: TEdit
      Left = 20
      Top = 122
      Width = 59
      Height = 21
      TabOrder = 5
      Text = '0'
      OnChange = Edit_WChange
      OnKeyDown = Edit_RKeyDown
    end
  end
  object GroupBox4: TGroupBox
    Left = 224
    Top = 104
    Width = 111
    Height = 150
    Caption = 'Address'
    TabOrder = 4
    Visible = False
    object Label4: TLabel
      Left = 7
      Top = 20
      Width = 34
      Height = 13
      Caption = 'Device'
    end
    object Label5: TLabel
      Left = 7
      Top = 46
      Width = 12
      Height = 13
      Caption = 'Bit'
    end
    object Label6: TLabel
      Left = 7
      Top = 72
      Width = 36
      Height = 13
      Caption = 'Gamma'
    end
    object Edit_GammaTestAddress: TEdit
      Left = 46
      Top = 20
      Width = 59
      Height = 21
      TabOrder = 0
      Text = '4A1'
    end
    object Edit_GammaTestBit: TEdit
      Left = 46
      Top = 46
      Width = 59
      Height = 21
      TabOrder = 1
      Text = '2'
    end
    object Edit_TestRGBAdress: TEdit
      Left = 46
      Top = 72
      Width = 59
      Height = 21
      TabOrder = 2
      Text = '4A7'
    end
    object ComboBox_AddressingSize: TComboBox
      Left = 8
      Top = 104
      Width = 89
      Height = 21
      ItemHeight = 13
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
    Left = 101
    Top = 40
    Width = 118
    Height = 145
    Caption = 'Data'
    TabOrder = 5
    object Label7: TLabel
      Left = 7
      Top = 20
      Width = 38
      Height = 13
      Caption = 'Address'
    end
    object Edit_WriteData: TEdit
      Left = 52
      Top = 46
      Width = 59
      Height = 21
      TabOrder = 0
    end
    object Edit_ReadData: TEdit
      Left = 52
      Top = 72
      Width = 59
      Height = 21
      Color = cl3DLight
      Enabled = False
      TabOrder = 1
    end
    object Button_Write: TButton
      Left = 7
      Top = 46
      Width = 39
      Height = 20
      Caption = 'Write'
      TabOrder = 2
      OnClick = Button_WriteClick
    end
    object Button_Read: TButton
      Left = 7
      Top = 72
      Width = 39
      Height = 20
      Caption = 'Read'
      TabOrder = 3
      OnClick = Button_ReadClick
    end
    object Edit_Address: TEdit
      Left = 52
      Top = 20
      Width = 59
      Height = 21
      TabOrder = 4
      Text = '0'
    end
  end
  object CheckBox_DG: TCheckBox
    Left = 8
    Top = 188
    Width = 76
    Height = 14
    Caption = 'DG Enable'
    TabOrder = 6
    OnClick = CheckBox_DGClick
  end
  object CheckBox_DGTest: TCheckBox
    Left = 8
    Top = 204
    Width = 85
    Height = 14
    Caption = 'DG Test'
    TabOrder = 7
    OnClick = CheckBox_DGTestClick
  end
end
