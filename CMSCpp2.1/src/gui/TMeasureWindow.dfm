object MeasureWindow: TMeasureWindow
  Left = 325
  Top = 181
  BorderStyle = bsNone
  Caption = 'MeasureWindow'
  ClientHeight = 447
  ClientWidth = 655
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 105
    Height = 105
    AutoSize = True
    Visible = False
  end
  object Button1: TButton
    Left = 9
    Top = 9
    Width = 73
    Height = 24
    Caption = 'Test'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 121
    Top = 9
    Width = 80
    Height = 24
    Caption = 'Button2'
    TabOrder = 1
    Visible = False
    OnClick = Button2Click
  end
end
