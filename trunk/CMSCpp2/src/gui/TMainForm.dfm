object MainForm: TMainForm
  Left = 208
  Top = 148
  Width = 666
  Height = 284
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
    Width = 161
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
      Width = 97
      Height = 24
      TabOrder = 0
      Text = '1366'
    end
    object Edit_Height: TEdit
      Left = 56
      Top = 56
      Width = 97
      Height = 24
      TabOrder = 1
      Text = '768'
    end
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 120
    Width = 161
    Height = 89
    Caption = 'Pattern Display Interval'
    TabOrder = 1
    object Label1: TLabel
      Left = 120
      Top = 24
      Width = 33
      Height = 16
      Caption = 'msec'
    end
    object Edit_Interval: TEdit
      Left = 8
      Top = 24
      Width = 105
      Height = 24
      TabOrder = 0
      Text = '750'
    end
  end
  object GroupBox2: TGroupBox
    Left = 192
    Top = 16
    Width = 393
    Height = 193
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
    end
    object RadioButton_TCON: TRadioButton
      Left = 8
      Top = 56
      Width = 81
      Height = 25
      Caption = 'T-CON'
      TabOrder = 1
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
