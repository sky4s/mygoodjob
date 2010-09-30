object MainForm: TMainForm
  Left = 276
  Top = 0
  Width = 732
  Height = 700
  Caption = 'C3D_12401'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object MainMenu1: TMainMenu
    Left = 56
    Top = 24
    object Engineering1: TMenuItem
      Caption = 'Engineering'
      OnClick = Engineering1Click
    end
    object c3d1: TMenuItem
      Caption = '3D LUT'
      OnClick = c3d1Click
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 120
    Top = 48
    object Image1: TMenuItem
      Caption = 'Image'
    end
  end
end
