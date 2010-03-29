object MainForm: TMainForm
  Left = 203
  Top = 111
  Width = 706
  Height = 282
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
      Height = 25
      TabOrder = 0
      Text = '1366'
    end
    object Edit_Height: TEdit
      Left = 56
      Top = 56
      Width = 89
      Height = 25
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
      Height = 25
      Caption = 'msec'
    end
    object Edit_Interval: TEdit
      Left = 8
      Top = 24
      Width = 97
      Height = 25
      TabOrder = 0
      Text = '750'
    end
  end
  object GroupBox2: TGroupBox
    Left = 192
    Top = 16
    Width = 489
    Height = 201
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
    object GroupBox3: TGroupBox
      Left = 88
      Top = 56
      Width = 217
      Height = 137
      Caption = 'Device Address'
      TabOrder = 2
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
        Height = 25
        TabOrder = 2
        Text = '7C'
      end
      object Edit_MasterDeviceAddress: TEdit
        Left = 120
        Top = 56
        Width = 41
        Height = 25
        TabOrder = 3
        Text = '7C'
      end
      object Edit_SlaveDeviceAddress: TEdit
        Left = 168
        Top = 56
        Width = 41
        Height = 25
        TabOrder = 4
        Text = '7E'
      end
      object Button_Connect: TButton
        Left = 72
        Top = 104
        Width = 73
        Height = 25
        Caption = 'Connect'
        TabOrder = 5
      end
    end
    object GroupBox4: TGroupBox
      Left = 312
      Top = 56
      Width = 169
      Height = 137
      Caption = 'Gamma Test Address'
      TabOrder = 3
      object Label4: TLabel
        Left = 8
        Top = 104
        Width = 81
        Height = 25
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
          Width = 57
          Height = 25
          Caption = 'Address'
        end
        object Label3: TLabel
          Left = 8
          Top = 48
          Width = 49
          Height = 25
          Caption = 'Bit'
        end
        object Edit_EnableAddress: TEdit
          Left = 64
          Top = 16
          Width = 81
          Height = 25
          TabOrder = 0
          Text = '4A1'
        end
        object Edit_EnableBit: TEdit
          Left = 64
          Top = 48
          Width = 81
          Height = 25
          TabOrder = 1
          Text = '1'
        end
      end
      object Edit_LUTAddress: TEdit
        Left = 96
        Top = 104
        Width = 57
        Height = 25
        TabOrder = 1
        Text = '4A7'
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
    object config1: TMenuItem
      Caption = 'Config'
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
