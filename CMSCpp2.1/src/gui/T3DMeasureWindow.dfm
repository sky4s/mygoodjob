object ThreeDMeasureWindow: TThreeDMeasureWindow
  Left = -12
  Top = 67
  BorderStyle = bsNone
  Caption = 'ThreeDMeasureWindow'
  ClientHeight = 825
  ClientWidth = 1284
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  WindowState = wsMaximized
  OnKeyPress = FormKeyPress
  OnPaint = FormPaint
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 473
    Height = 433
    BevelOuter = bvNone
    Color = clMaroon
    TabOrder = 0
    object Button1: TButton
      Left = 9
      Top = 9
      Width = 73
      Height = 24
      Caption = 'Button1'
      TabOrder = 0
      Visible = False
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 473
    Top = 0
    Width = 448
    Height = 433
    BevelOuter = bvNone
    Color = clOlive
    TabOrder = 1
  end
end
