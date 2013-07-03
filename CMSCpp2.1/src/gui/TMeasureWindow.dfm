object MeasureWindow: TMeasureWindow
  Left = 286
  Top = 180
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
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 88
    Top = 72
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
  object Button3: TButton
    Left = 184
    Top = 8
    Width = 75
    Height = 25
    Caption = 'agingTest'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 184
    Top = 48
    Width = 75
    Height = 25
    Caption = 'DirectGAM'
    TabOrder = 3
    OnClick = Button4Click
  end
end
