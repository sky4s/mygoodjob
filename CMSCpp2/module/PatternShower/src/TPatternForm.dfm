object PatternForm: TPatternForm
  Left = 552
  Top = 181
  BorderStyle = bsNone
  Caption = 'PatternForm'
  ClientHeight = 720
  ClientWidth = 1297
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnDblClick = FormDblClick
  PixelsPerInch = 120
  TextHeight = 16
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 1297
    Height = 29
    ButtonHeight = 24
    Caption = 'ToolBar1'
    TabOrder = 0
    object Edit_Start: TEdit
      Left = 0
      Top = 2
      Width = 40
      Height = 24
      TabOrder = 2
      Text = '0'
    end
    object Splitter5: TSplitter
      Left = 40
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object Edit_End: TEdit
      Left = 43
      Top = 2
      Width = 40
      Height = 24
      TabOrder = 3
      Text = '255'
    end
    object Splitter6: TSplitter
      Left = 83
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object Edit_Code: TEdit
      Left = 86
      Top = 2
      Width = 40
      Height = 24
      Enabled = False
      TabOrder = 4
    end
    object Splitter7: TSplitter
      Left = 126
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object Button1: TButton
      Left = 129
      Top = 2
      Width = 47
      Height = 24
      Caption = 'reset'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Splitter4: TSplitter
      Left = 176
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object Button2: TButton
      Left = 179
      Top = 2
      Width = 30
      Height = 24
      Caption = '256'
      TabOrder = 5
    end
    object Button3: TButton
      Left = 209
      Top = 2
      Width = 30
      Height = 24
      Caption = '128'
      TabOrder = 6
    end
    object Button4: TButton
      Left = 239
      Top = 2
      Width = 26
      Height = 24
      Caption = '64'
      TabOrder = 7
    end
    object Button5: TButton
      Left = 265
      Top = 2
      Width = 26
      Height = 24
      Caption = '32'
      TabOrder = 8
    end
    object Button6: TButton
      Left = 291
      Top = 2
      Width = 26
      Height = 24
      Caption = '16'
      TabOrder = 9
    end
    object Button7: TButton
      Left = 317
      Top = 2
      Width = 20
      Height = 24
      Caption = '8'
      TabOrder = 10
    end
    object Button8: TButton
      Left = 337
      Top = 2
      Width = 20
      Height = 24
      Caption = '4'
      TabOrder = 11
    end
    object Splitter3: TSplitter
      Left = 357
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object SpeedButton1: TSpeedButton
      Left = 360
      Top = 2
      Width = 23
      Height = 24
      GroupIndex = 1
      Down = True
      Caption = 'R'
    end
    object SpeedButton2: TSpeedButton
      Left = 383
      Top = 2
      Width = 23
      Height = 24
      GroupIndex = 2
      Down = True
      Caption = 'G'
    end
    object SpeedButton3: TSpeedButton
      Left = 406
      Top = 2
      Width = 23
      Height = 24
      GroupIndex = 3
      Down = True
      Caption = 'B'
    end
    object Splitter8: TSplitter
      Left = 429
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object Button12: TButton
      Left = 432
      Top = 2
      Width = 48
      Height = 24
      Caption = 'mono'
      TabOrder = 12
    end
    object Button13: TButton
      Left = 480
      Top = 2
      Width = 32
      Height = 24
      Caption = 'inv'
      TabOrder = 13
    end
    object Button14: TButton
      Left = 512
      Top = 2
      Width = 64
      Height = 24
      Caption = 'vectical'
      TabOrder = 14
    end
    object Button15: TButton
      Left = 576
      Top = 2
      Width = 40
      Height = 24
      Caption = 'grid'
      TabOrder = 15
    end
    object Button16: TButton
      Left = 616
      Top = 2
      Width = 48
      Height = 24
      Caption = 'HSB'
      TabOrder = 16
    end
    object Button17: TButton
      Left = 664
      Top = 2
      Width = 33
      Height = 24
      Caption = 'fill'
      TabOrder = 17
    end
    object Splitter2: TSplitter
      Left = 697
      Top = 2
      Width = 3
      Height = 24
      Cursor = crHSplit
    end
    object Button_Exit: TButton
      Left = 700
      Top = 2
      Width = 40
      Height = 24
      Caption = 'Exit'
      TabOrder = 0
      OnClick = Button_ExitClick
    end
  end
end
