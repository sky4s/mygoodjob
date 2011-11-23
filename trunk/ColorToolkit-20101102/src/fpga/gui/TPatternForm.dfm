object PatternForm: TPatternForm
  Left = 965
  Top = 60
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'PatternForm'
  ClientHeight = 780
  ClientWidth = 326
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  ShowHint = True
  Visible = True
  WindowState = wsMinimized
  OnDblClick = FormDblClick
  OnKeyPress = FormKeyPress
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 120
  TextHeight = 16
  object Button_Show7p5Deg: TButton
    Left = 0
    Top = 0
    Width = 25
    Height = 17
    Hint = '15'#176'+7.5'#176' extend'
    Caption = '<<'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    OnClick = Button_Show7p5DegClick
  end
  object Button_Show15Deg: TButton
    Left = 25
    Top = 0
    Width = 24
    Height = 17
    Hint = '15'#176' extend'
    Caption = '<'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = Button_Show15DegClick
  end
  object Button_ShowSingleDeg: TButton
    Left = 48
    Top = 0
    Width = 25
    Height = 17
    Hint = 'Single Hue'
    Caption = '||'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = Button_ShowSingleDegClick
  end
end
