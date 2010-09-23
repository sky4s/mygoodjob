object MainForm: TMainForm
  Left = 275
  Top = 22
  Width = 732
  Height = 712
  Caption = 'C3D_12401'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
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
