object PatternForm: TPatternForm
  Left = 1007
  Top = 62
  Anchors = [akLeft, akBottom]
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'PatternForm'
  ClientHeight = 634
  ClientWidth = 265
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefaultSizeOnly
  ShowHint = True
  Visible = True
  WindowState = wsMinimized
  OnClose = FormClose
  OnDblClick = FormDblClick
  OnKeyPress = FormKeyPress
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Button_Show7p5Deg: TButton
    Left = 0
    Top = 0
    Width = 20
    Height = 14
    Hint = '15'#176'+7.5'#176' extend'
    Caption = '<<'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    OnClick = Button_Show7p5DegClick
  end
  object Button_Show15Deg: TButton
    Left = 20
    Top = 0
    Width = 20
    Height = 14
    Hint = '15'#176' extend'
    Caption = '<'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = Button_Show15DegClick
  end
  object Button_ShowSingleDeg: TButton
    Left = 39
    Top = 0
    Width = 20
    Height = 14
    Hint = 'Single Hue'
    Caption = '||'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = Button_ShowSingleDegClick
  end
end
