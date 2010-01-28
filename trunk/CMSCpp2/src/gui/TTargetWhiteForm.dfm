object TargetWhiteForm: TTargetWhiteForm
  Left = 382
  Top = 190
  Width = 908
  Height = 578
  Caption = 'Target White'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Label12: TLabel
    Left = 864
    Top = 432
    Width = 10
    Height = 16
    Caption = 'R'
  end
  object Label13: TLabel
    Left = 864
    Top = 464
    Width = 10
    Height = 16
    Caption = 'G'
  end
  object Label14: TLabel
    Left = 864
    Top = 496
    Width = 9
    Height = 16
    Caption = 'B'
  end
  object Label15: TLabel
    Left = 528
    Top = 528
    Width = 353
    Height = 16
    Caption = 'Copyright (C) 2010. AU Optronics Corp., All Rights Reserved'
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 233
    Height = 153
    Caption = '1. CCT to xy on D-Locus'
    TabOrder = 0
    object Label1: TLabel
      Left = 9
      Top = 32
      Width = 18
      Height = 16
      Caption = 'CT'
    end
    object Label2: TLabel
      Left = 121
      Top = 32
      Width = 8
      Height = 16
      Caption = 'K'
    end
    object Label3: TLabel
      Left = 16
      Top = 57
      Width = 13
      Height = 16
      Caption = 'x='
    end
    object Label4: TLabel
      Left = 128
      Top = 57
      Width = 14
      Height = 16
      Caption = 'y='
    end
    object Label5: TLabel
      Left = 16
      Top = 89
      Width = 17
      Height = 16
      Caption = 'u'#39'='
    end
    object Label6: TLabel
      Left = 128
      Top = 89
      Width = 17
      Height = 16
      Caption = 'v'#39'='
    end
    object Edit_CT: TEdit
      Left = 32
      Top = 25
      Width = 81
      Height = 24
      TabOrder = 0
      Text = '10000'
      OnChange = Edit_CTChange
    end
    object Edit_x: TEdit
      Left = 32
      Top = 57
      Width = 81
      Height = 24
      Enabled = False
      TabOrder = 1
      Text = '0.2788'
    end
    object Edit_y: TEdit
      Left = 144
      Top = 57
      Width = 81
      Height = 24
      Enabled = False
      TabOrder = 2
      Text = '0.2920'
    end
    object Edit_up: TEdit
      Left = 32
      Top = 89
      Width = 81
      Height = 24
      Enabled = False
      TabOrder = 3
      Text = '0.1876'
    end
    object Edit_vp: TEdit
      Left = 144
      Top = 89
      Width = 81
      Height = 24
      Enabled = False
      TabOrder = 4
      Text = '0.4419'
    end
    object Button_Calculate: TButton
      Left = 89
      Top = 121
      Width = 80
      Height = 24
      Caption = 'Calculate'
      TabOrder = 5
      Visible = False
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 176
    Width = 233
    Height = 337
    Caption = '2. Auto Matrix Calibration'
    TabOrder = 1
    object GroupBox3: TGroupBox
      Left = 16
      Top = 25
      Width = 201
      Height = 112
      Caption = 'CH Setting'
      TabOrder = 0
      object Label7: TLabel
        Left = 9
        Top = 25
        Width = 65
        Height = 16
        Caption = 'Source CH'
      end
      object Label8: TLabel
        Left = 9
        Top = 57
        Width = 75
        Height = 16
        Caption = 'TargetW CH'
      end
      object Label9: TLabel
        Left = 9
        Top = 89
        Width = 69
        Height = 16
        Caption = 'TargetW ID'
      end
      object Edit_SourceCH: TEdit
        Left = 89
        Top = 16
        Width = 48
        Height = 24
        TabOrder = 0
        Text = '0'
      end
      object Edit_TargetCH: TEdit
        Left = 89
        Top = 48
        Width = 48
        Height = 24
        TabOrder = 1
        Text = '2'
      end
      object Edit_TargetID: TEdit
        Left = 89
        Top = 80
        Width = 104
        Height = 24
        TabOrder = 2
      end
    end
    object GroupBox4: TGroupBox
      Left = 16
      Top = 145
      Width = 201
      Height = 56
      Caption = 'Target xy'
      TabOrder = 1
      object Label10: TLabel
        Left = 9
        Top = 25
        Width = 6
        Height = 16
        Caption = 'x'
      end
      object Label11: TLabel
        Left = 105
        Top = 25
        Width = 7
        Height = 16
        Caption = 'y'
      end
      object Edit_targetx: TEdit
        Left = 25
        Top = 25
        Width = 72
        Height = 24
        TabOrder = 0
        Text = '.2788'
      end
      object Edit_targety: TEdit
        Left = 121
        Top = 25
        Width = 72
        Height = 24
        TabOrder = 1
        Text = '.2920'
      end
    end
    object RadioGroup1: TRadioGroup
      Left = 16
      Top = 217
      Width = 201
      Height = 80
      Caption = 'Adjustment Options'
      TabOrder = 2
    end
    object RadioButton1: TRadioButton
      Left = 25
      Top = 240
      Width = 168
      Height = 25
      Caption = 'Adjust to Target x,y'
      Checked = True
      TabOrder = 3
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 25
      Top = 265
      Width = 168
      Height = 24
      Caption = 'Adjust by RGB ratio'
      TabOrder = 4
    end
    object Button2: TButton
      Left = 73
      Top = 304
      Width = 80
      Height = 25
      Caption = 'Run'
      TabOrder = 5
      OnClick = Button2Click
    end
  end
  object Panel1: TPanel
    Left = 265
    Top = 25
    Width = 616
    Height = 392
    Color = clWhite
    TabOrder = 2
  end
  object ScrollBar_R: TScrollBar
    Left = 320
    Top = 432
    Width = 529
    Height = 17
    LargeChange = 10
    Max = 255
    PageSize = 0
    Position = 255
    TabOrder = 3
    OnChange = ScrollBar_RChange
  end
  object Edit_R: TEdit
    Left = 265
    Top = 425
    Width = 40
    Height = 24
    Enabled = False
    TabOrder = 4
    Text = '255'
  end
  object Edit_G: TEdit
    Left = 265
    Top = 457
    Width = 40
    Height = 24
    Enabled = False
    TabOrder = 5
    Text = '255'
  end
  object Edit_B: TEdit
    Left = 265
    Top = 489
    Width = 40
    Height = 24
    Enabled = False
    TabOrder = 6
    Text = '255'
  end
  object ScrollBar_G: TScrollBar
    Left = 320
    Top = 464
    Width = 529
    Height = 17
    LargeChange = 10
    Max = 255
    PageSize = 0
    Position = 255
    TabOrder = 7
    OnChange = ScrollBar_GChange
  end
  object ScrollBar_B: TScrollBar
    Left = 320
    Top = 496
    Width = 529
    Height = 17
    LargeChange = 10
    Max = 255
    PageSize = 0
    Position = 255
    TabOrder = 8
    OnChange = ScrollBar_BChange
  end
end
