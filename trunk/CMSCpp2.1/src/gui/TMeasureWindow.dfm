object MeasureWindow: TMeasureWindow
  Left = 360
  Top = 190
  BorderStyle = bsNone
  Caption = 'MeasureWindow'
  ClientHeight = 492
  ClientWidth = 699
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
  PixelsPerInch = 96
  TextHeight = 13
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
end
