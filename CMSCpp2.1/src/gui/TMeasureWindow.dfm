object MeasureWindow: TMeasureWindow
  Left = 234
  Top = 187
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
  object Button3: TButton
    Left = 184
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button3'
    TabOrder = 2
    Visible = False
    OnClick = Button3Click
  end
  object Button5: TButton
    Left = 272
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button5'
    TabOrder = 3
    Visible = False
    OnClick = Button5Click
  end
  object Button4: TButton
    Left = 16
    Top = 48
    Width = 75
    Height = 25
    Caption = 'Button4'
    TabOrder = 4
    Visible = False
    OnClick = Button4Click
  end
  object Button6: TButton
    Left = 360
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Button6'
    TabOrder = 5
    Visible = False
    OnClick = Button6Click
  end
end
