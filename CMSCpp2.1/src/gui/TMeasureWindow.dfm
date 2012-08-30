object MeasureWindow: TMeasureWindow
  Left = 164
  Top = 193
  BorderStyle = bsNone
  Caption = 'MeasureWindow'
  ClientHeight = 363
  ClientWidth = 532
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 85
    Height = 85
    AutoSize = True
    Visible = False
  end
  object Button1: TButton
    Left = 7
    Top = 7
    Width = 60
    Height = 20
    Caption = 'Test'
    TabOrder = 0
    Visible = False
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 98
    Top = 7
    Width = 65
    Height = 20
    Caption = 'Button2'
    TabOrder = 1
    Visible = False
    OnClick = Button2Click
  end
end
