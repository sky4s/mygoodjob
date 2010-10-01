object TestForm2: TTestForm2
  Left = 192
  Top = 132
  Width = 967
  Height = 822
  Caption = 'TestForm2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  inline TColorPickerFrame1: TColorPickerFrame
    Left = 8
    Top = 8
    Width = 760
    Height = 458
    TabOrder = 0
  end
  inline HSVAdjustFrame1: THSVAdjustFrame
    Left = 8
    Top = 472
    Width = 395
    Height = 201
    TabOrder = 1
    inherited GroupBox41: TGroupBox
      inherited sb_c3d_Manual39_s: TScrollBar
        OnChange = nil
      end
    end
    inherited GroupBox7: TGroupBox
      inherited sb_c3d_Manual39_v: TScrollBar
        OnChange = nil
      end
    end
  end
end
