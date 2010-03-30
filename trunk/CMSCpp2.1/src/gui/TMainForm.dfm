object MainForm: TMainForm
  Left = 203
  Top = 111
  Width = 818
  Height = 321
  Caption = 'CCT Adjustment v3'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object Resolution: TGroupBox
    Left = 16
    Top = 16
    Width = 153
    Height = 89
    Caption = 'Resolution'
    TabOrder = 0
    object Width: TLabel
      Left = 8
      Top = 24
      Width = 34
      Height = 16
      Caption = 'Width'
    end
    object Height: TLabel
      Left = 8
      Top = 56
      Width = 39
      Height = 16
      Caption = 'Height'
    end
    object Edit_Width: TEdit
      Left = 56
      Top = 24
      Width = 89
      Height = 24
      TabOrder = 0
      Text = '1366'
    end
    object Edit_Height: TEdit
      Left = 56
      Top = 56
      Width = 89
      Height = 24
      TabOrder = 1
      Text = '768'
    end
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 120
    Width = 153
    Height = 89
    Caption = 'Pattern Display Interval'
    TabOrder = 1
    object Label1: TLabel
      Left = 112
      Top = 24
      Width = 33
      Height = 16
      Caption = 'msec'
    end
    object Edit_Interval: TEdit
      Left = 8
      Top = 24
      Width = 97
      Height = 24
      TabOrder = 0
      Text = '750'
    end
  end
  object GroupBox2: TGroupBox
    Left = 192
    Top = 16
    Width = 601
    Height = 233
    Caption = 'Input Source'
    TabOrder = 2
    object RadioButton_PC: TRadioButton
      Left = 8
      Top = 24
      Width = 73
      Height = 25
      Caption = 'PC'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = RadioButton_PCClick
    end
    object RadioButton_TCON: TRadioButton
      Left = 8
      Top = 56
      Width = 81
      Height = 25
      Caption = 'T-CON'
      TabOrder = 1
      OnClick = RadioButton_TCONClick
    end
    object GroupBox_DeviceAddress: TGroupBox
      Left = 200
      Top = 56
      Width = 217
      Height = 169
      Caption = 'Device Address'
      Enabled = False
      TabOrder = 2
      object Label5: TLabel
        Left = 16
        Top = 88
        Width = 97
        Height = 25
        Caption = 'EEPROM Size'
      end
      object RadioButton_SingleTCON: TRadioButton
        Left = 8
        Top = 24
        Width = 113
        Height = 25
        Caption = 'Single T-CON'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton_DualTCON: TRadioButton
        Left = 8
        Top = 56
        Width = 113
        Height = 25
        Caption = 'Dual T-CON'
        TabOrder = 1
      end
      object Edit_DeviceAddress: TEdit
        Left = 120
        Top = 24
        Width = 41
        Height = 24
        TabOrder = 2
        Text = '7C'
      end
      object Edit_MasterDeviceAddress: TEdit
        Left = 120
        Top = 56
        Width = 41
        Height = 24
        TabOrder = 3
        Text = '7C'
      end
      object Edit_SlaveDeviceAddress: TEdit
        Left = 168
        Top = 56
        Width = 41
        Height = 24
        TabOrder = 4
        Text = '7E'
      end
      object Button_Connect: TButton
        Left = 16
        Top = 136
        Width = 73
        Height = 25
        Caption = 'Connect'
        TabOrder = 5
        OnClick = Button_ConnectClick
      end
      object CheckBox_Connecting: TCheckBox
        Left = 104
        Top = 136
        Width = 97
        Height = 25
        Caption = 'Connecting'
        Enabled = False
        TabOrder = 6
      end
      object ComboBox_AddressingSize: TComboBox
        Left = 120
        Top = 88
        Width = 89
        Height = 24
        ItemHeight = 16
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
      Left = 424
      Top = 56
      Width = 169
      Height = 169
      Caption = 'Gamma Test Address'
      Enabled = False
      TabOrder = 3
      object Label4: TLabel
        Left = 8
        Top = 104
        Width = 80
        Height = 16
        Caption = 'LUT Address'
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 16
        Width = 153
        Height = 81
        Caption = 'Enable'
        TabOrder = 0
        object Label2: TLabel
          Left = 8
          Top = 16
          Width = 51
          Height = 16
          Caption = 'Address'
        end
        object Label3: TLabel
          Left = 8
          Top = 48
          Width = 15
          Height = 16
          Caption = 'Bit'
        end
        object Edit_EnableAddress: TEdit
          Left = 64
          Top = 16
          Width = 81
          Height = 24
          TabOrder = 0
          Text = '4A1'
        end
        object Edit_EnableBit: TEdit
          Left = 64
          Top = 48
          Width = 81
          Height = 24
          TabOrder = 1
          Text = '1'
        end
      end
      object Edit_LUTAddress: TEdit
        Left = 96
        Top = 104
        Width = 57
        Height = 24
        TabOrder = 1
        Text = '4A7'
      end
      object CheckBox_IndepRGB: TCheckBox
        Left = 8
        Top = 136
        Width = 129
        Height = 25
        Caption = 'Independent RGB'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
    end
    object GroupBox_Card: TGroupBox
      Left = 81
      Top = 57
      Width = 112
      Height = 168
      Caption = 'Card'
      Color = clBtnFace
      Enabled = False
      ParentColor = False
      TabOrder = 4
      object RadioButton_USB: TRadioButton
        Left = 9
        Top = 25
        Width = 64
        Height = 24
        Caption = 'USB'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object RadioButton_LPTLarge: TRadioButton
        Left = 9
        Top = 56
        Width = 88
        Height = 25
        Caption = 'LPT Large'
        TabOrder = 1
      end
      object RadioButton_LPTSmall: TRadioButton
        Left = 9
        Top = 88
        Width = 89
        Height = 25
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
    object GammaAdj1: TMenuItem
      Caption = 'GammaAdj'
      OnClick = GammaAdj1Click
    end
    object Measurement1: TMenuItem
      Caption = 'Measurement'
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
