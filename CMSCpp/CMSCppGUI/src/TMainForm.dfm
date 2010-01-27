object MainForm: TMainForm
  Left = 153
  Top = 243
  Width = 870
  Height = 640
  Caption = 'CCT Adjustment V3.10'
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
  object MainMenu1: TMainMenu
    object MatrixCalibration1: TMenuItem
      Caption = 'Matrix Calibration'
    end
    object TargetWhite1: TMenuItem
      Caption = 'Target White'
      OnClick = TargetWhite1Click
    end
    object CCTLUT1: TMenuItem
      Caption = 'CCT(LUT)'
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
