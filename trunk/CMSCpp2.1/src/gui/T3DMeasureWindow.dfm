object ThreeDMeasureWindow: TThreeDMeasureWindow
  Left = 217
  Top = 206
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
  OnCreate = FormCreate
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
    object Label_StartAdj: TLabel
      Left = 24
      Top = 40
      Width = 61
      Height = 25
      Caption = 'start 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TargetAdj: TLabel
      Left = 24
      Top = 72
      Width = 74
      Height = 25
      Caption = 'target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_StartBase: TLabel
      Left = 24
      Top = 104
      Width = 124
      Height = 25
      Caption = 'start->start 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TargetBase: TLabel
      Left = 24
      Top = 136
      Width = 150
      Height = 25
      Caption = 'target->target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_StartTarget: TLabel
      Left = 24
      Top = 168
      Width = 137
      Height = 25
      Caption = 'start->target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Button1: TButton
      Left = 25
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
