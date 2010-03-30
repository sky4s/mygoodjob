object MainForm: TMainForm
  Left = 203
  Top = 111
  Width = 818
  Height = 321
  Caption = 'CCT Adjustment v3'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Resolution: TGroupBox
    Left = 13
    Top = 13
    Width = 124
    Height = 72
    Caption = 'Resolution'
    TabOrder = 0
    object Width: TLabel
      Left = 7
      Top = 20
      Width = 28
      Height = 13
      Caption = 'Width'
    end
    object Height: TLabel
      Left = 7
      Top = 46
      Width = 31
      Height = 13
      Caption = 'Height'
    end
    object Edit_Width: TEdit
      Left = 46
      Top = 20
      Width = 72
      Height = 21
      TabOrder = 0
      Text = '1366'
    end
    object Edit_Height: TEdit
      Left = 46
      Top = 46
      Width = 72
      Height = 21
      TabOrder = 1
      Text = '768'
    end
  end
  object GroupBox1: TGroupBox
    Left = 13
    Top = 98
    Width = 124
    Height = 72
    Caption = 'Pattern Display Interval'
    TabOrder = 1
    object Label1: TLabel
      Left = 91
      Top = 20
      Width = 25
      Height = 13
      Caption = 'msec'
    end
    object Edit_Interval: TEdit
      Left = 7
      Top = 20
      Width = 78
      Height = 21
      TabOrder = 0
      Text = '750'
    end
  end
  object GroupBox2: TGroupBox
    Left = 156
    Top = 13
    Width = 488
    Height = 189
    Caption = 'Input Source'
    TabOrder = 2
    object RadioButton_PC: TRadioButton
      Left = 7
      Top = 20
      Width = 59
      Height = 20
      Caption = 'PC'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_PCClick
    end
    object RadioButton_TCON: TRadioButton
      Left = 7
      Top = 46
      Width = 65
      Height = 20
      Caption = 'T-CON'
      TabOrder = 1
      OnClick = RadioButton_TCONClick
    end
    object GroupBox_DeviceAddress: TGroupBox
      Left = 163
      Top = 46
      Width = 176
      Height = 137
      Caption = 'Device Address'
      Enabled = False
      TabOrder = 2
      object Label5: TLabel
        Left = 13
        Top = 72
        Width = 69
        Height = 13
        Caption = 'EEPROM Size'
      end
      object RadioButton_SingleTCON: TRadioButton
        Left = 7
        Top = 20
        Width = 91
        Height = 20
        Caption = 'Single T-CON'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton_DualTCON: TRadioButton
        Left = 7
        Top = 46
        Width = 91
        Height = 20
        Caption = 'Dual T-CON'
        TabOrder = 1
      end
      object Edit_DeviceAddress: TEdit
        Left = 98
        Top = 20
        Width = 33
        Height = 21
        TabOrder = 2
        Text = '7C'
      end
      object Edit_MasterDeviceAddress: TEdit
        Left = 98
        Top = 46
        Width = 33
        Height = 21
        TabOrder = 3
        Text = '7C'
      end
      object Edit_SlaveDeviceAddress: TEdit
        Left = 137
        Top = 46
        Width = 33
        Height = 21
        TabOrder = 4
        Text = '7E'
      end
      object Button_Connect: TButton
        Left = 13
        Top = 111
        Width = 59
        Height = 20
        Caption = 'Connect'
        TabOrder = 5
        OnClick = Button_ConnectClick
      end
      object CheckBox_Connecting: TCheckBox
        Left = 85
        Top = 111
        Width = 78
        Height = 20
        Caption = 'Connecting'
        Enabled = False
        TabOrder = 6
        OnClick = CheckBox_ConnectingClick
      end
      object ComboBox_AddressingSize: TComboBox
        Left = 98
        Top = 72
        Width = 72
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 7
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
    object GroupBox_GammaTestAddress: TGroupBox
      Left = 345
      Top = 46
      Width = 137
      Height = 137
      Caption = 'Gamma Test Address'
      Enabled = False
      TabOrder = 3
      object Label4: TLabel
        Left = 7
        Top = 85
        Width = 62
        Height = 13
        Caption = 'LUT Address'
      end
      object GroupBox5: TGroupBox
        Left = 7
        Top = 13
        Width = 124
        Height = 66
        Caption = 'Enable'
        TabOrder = 0
        object Label2: TLabel
          Left = 7
          Top = 13
          Width = 38
          Height = 13
          Caption = 'Address'
        end
        object Label3: TLabel
          Left = 7
          Top = 39
          Width = 12
          Height = 13
          Caption = 'Bit'
        end
        object Edit_EnableAddress: TEdit
          Left = 52
          Top = 13
          Width = 66
          Height = 21
          TabOrder = 0
          Text = '4A1'
        end
        object Edit_EnableBit: TEdit
          Left = 52
          Top = 39
          Width = 66
          Height = 21
          TabOrder = 1
          Text = '1'
        end
      end
      object Edit_LUTAddress: TEdit
        Left = 78
        Top = 85
        Width = 46
        Height = 21
        TabOrder = 1
        Text = '4A7'
      end
      object CheckBox_IndepRGB: TCheckBox
        Left = 7
        Top = 111
        Width = 104
        Height = 20
        Caption = 'Independent RGB'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
    end
    object GroupBox_Card: TGroupBox
      Left = 66
      Top = 46
      Width = 91
      Height = 137
      Caption = 'Card'
      Color = clBtnFace
      Enabled = False
      ParentColor = False
      TabOrder = 4
      object RadioButton_USB: TRadioButton
        Left = 7
        Top = 20
        Width = 52
        Height = 20
        Caption = 'USB'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton_LPTLarge: TRadioButton
        Left = 7
        Top = 46
        Width = 72
        Height = 20
        Caption = 'LPT Large'
        TabOrder = 1
      end
      object RadioButton_LPTSmall: TRadioButton
        Left = 7
        Top = 72
        Width = 73
        Height = 20
        Caption = 'LPT Small'
        TabOrder = 2
      end
    end
  end
  object MainMenu1: TMainMenu
    object TargetWhite1: TMenuItem
      Caption = 'Target White'
      OnClick = TargetWhite1Click
    end
    object CCTLUT1: TMenuItem
      Caption = 'CCT(LUT)'
      OnClick = CCTLUT1Click
    end
    object Measurement1: TMenuItem
      Caption = 'Measurement'
      OnClick = Measurement1Click
    end
    object About1: TMenuItem
      Caption = 'About'
      OnClick = About1Click
    end
    object Exit1: TMenuItem
      Caption = 'Exit'
      OnClick = Exit1Click
    end
  end
end
