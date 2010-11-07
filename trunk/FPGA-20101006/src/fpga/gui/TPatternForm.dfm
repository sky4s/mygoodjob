object PatternForm: TPatternForm
  Left = 703
  Top = 353
  Width = 273
  Height = 663
  Caption = 'PatternForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  WindowState = wsMinimized
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 120
  TextHeight = 16
  object Button_Show7p5Deg: TButton
    Left = 0
    Top = 0
    Width = 25
    Height = 17
    Caption = '<<'
    TabOrder = 0
    OnClick = Button_Show7p5DegClick
  end
  object Button_Show15Deg: TButton
    Left = 24
    Top = 0
    Width = 25
    Height = 17
    Caption = '<'
    TabOrder = 1
    OnClick = Button_Show15DegClick
  end
  object Button_ShowSingleDeg: TButton
    Left = 48
    Top = 0
    Width = 25
    Height = 17
    Caption = '||'
    TabOrder = 2
    OnClick = Button_ShowSingleDegClick
  end
end
