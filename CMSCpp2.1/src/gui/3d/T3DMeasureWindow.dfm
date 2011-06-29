object ThreeDMeasureWindow: TThreeDMeasureWindow
  Left = 217
  Top = 206
  BorderStyle = bsNone
  Caption = 'ThreeDMeasureWindow'
  ClientHeight = 670
  ClientWidth = 1043
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 384
    Height = 352
    BevelOuter = bvNone
    Color = clMaroon
    TabOrder = 0
    object Label_StartAdj: TLabel
      Left = 20
      Top = 33
      Width = 53
      Height = 20
      Caption = 'start 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TargetAdj: TLabel
      Left = 20
      Top = 59
      Width = 64
      Height = 20
      Caption = 'target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object Label_StartBase: TLabel
      Left = 20
      Top = 85
      Width = 106
      Height = 20
      Caption = 'start->start 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TargetBase: TLabel
      Left = 20
      Top = 111
      Width = 128
      Height = 20
      Caption = 'target->target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_StartTarget: TLabel
      Left = 20
      Top = 137
      Width = 117
      Height = 20
      Caption = 'start->target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_TargetStart: TLabel
      Left = 20
      Top = 163
      Width = 117
      Height = 20
      Caption = 'target->start 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_WXtalk: TLabel
      Left = 20
      Top = 189
      Width = 55
      Height = 20
      Caption = 'w xtalk'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_BXtalk: TLabel
      Left = 20
      Top = 215
      Width = 53
      Height = 20
      Caption = 'b xtalk'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label_RealTimeMeasure: TLabel
      Left = 20
      Top = 260
      Width = 104
      Height = 20
      Caption = 'realtime mea'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object Button1: TButton
      Left = 20
      Top = 7
      Width = 60
      Height = 20
      Caption = 'Button1'
      TabOrder = 0
      Visible = False
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 384
    Top = 0
    Width = 364
    Height = 352
    BevelOuter = bvNone
    Color = clOlive
    TabOrder = 1
    object Label_TargetAdj2: TLabel
      Left = 20
      Top = 59
      Width = 64
      Height = 20
      Caption = 'target 0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
end
