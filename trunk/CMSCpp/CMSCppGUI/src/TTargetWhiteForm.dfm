object TargetWhiteForm: TTargetWhiteForm
  Left = 156
  Top = 167
  Width = 908
  Height = 578
  Caption = 'Target White'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label12: TLabel
    Left = 702
    Top = 351
    Width = 8
    Height = 13
    Caption = 'R'
  end
  object Label13: TLabel
    Left = 702
    Top = 377
    Width = 8
    Height = 13
    Caption = 'G'
  end
  object Label14: TLabel
    Left = 702
    Top = 403
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label15: TLabel
    Left = 429
    Top = 429
    Width = 283
    Height = 13
    Caption = 'Copyright (C) 2010. AU Optronics Corp., All Rights Reserved'
  end
  object GroupBox1: TGroupBox
    Left = 13
    Top = 13
    Width = 189
    Height = 124
    Caption = '1. CCT to xy on D-Locus'
    TabOrder = 0
    object Label1: TLabel
      Left = 7
      Top = 26
      Width = 14
      Height = 13
      Caption = 'CT'
    end
    object Label2: TLabel
      Left = 98
      Top = 26
      Width = 7
      Height = 13
      Caption = 'K'
    end
    object Label3: TLabel
      Left = 13
      Top = 46
      Width = 11
      Height = 13
      Caption = 'x='
    end
    object Label4: TLabel
      Left = 104
      Top = 46
      Width = 11
      Height = 13
      Caption = 'y='
    end
    object Label5: TLabel
      Left = 13
      Top = 72
      Width = 14
      Height = 13
      Caption = 'u'#39'='
    end
    object Label6: TLabel
      Left = 104
      Top = 72
      Width = 14
      Height = 13
      Caption = 'v'#39'='
    end
    object Edit_CT: TEdit
      Left = 26
      Top = 20
      Width = 66
      Height = 24
      TabOrder = 0
      Text = '10000'
      OnChange = Edit_CTChange
    end
    object Edit_x: TEdit
      Left = 26
      Top = 46
      Width = 66
      Height = 24
      Enabled = False
      TabOrder = 1
      Text = '0.2788'
    end
    object Edit_y: TEdit
      Left = 117
      Top = 46
      Width = 66
      Height = 24
      Enabled = False
      TabOrder = 2
      Text = '0.2920'
    end
    object Edit_up: TEdit
      Left = 26
      Top = 72
      Width = 66
      Height = 24
      Enabled = False
      TabOrder = 3
      Text = '0.1876'
    end
    object Edit_vp: TEdit
      Left = 117
      Top = 72
      Width = 66
      Height = 24
      Enabled = False
      TabOrder = 4
      Text = '0.4419'
    end
    object Button_Calculate: TButton
      Left = 72
      Top = 98
      Width = 65
      Height = 20
      Caption = 'Calculate'
      TabOrder = 5
      Visible = False
    end
  end
  object GroupBox2: TGroupBox
    Left = 13
    Top = 143
    Width = 189
    Height = 274
    Caption = '2. Auto Matrix Calibration'
    TabOrder = 1
    object GroupBox3: TGroupBox
      Left = 13
      Top = 20
      Width = 163
      Height = 91
      Caption = 'CH Setting'
      TabOrder = 0
      object Label7: TLabel
        Left = 7
        Top = 20
        Width = 52
        Height = 13
        Caption = 'Source CH'
      end
      object Label8: TLabel
        Left = 7
        Top = 46
        Width = 60
        Height = 13
        Caption = 'TargetW CH'
      end
      object Label9: TLabel
        Left = 7
        Top = 72
        Width = 56
        Height = 13
        Caption = 'TargetW ID'
      end
      object Edit_SourceCH: TEdit
        Left = 72
        Top = 13
        Width = 39
        Height = 24
        TabOrder = 0
        Text = '0'
      end
      object Edit_TargetCH: TEdit
        Left = 72
        Top = 39
        Width = 39
        Height = 24
        TabOrder = 1
        Text = '2'
      end
      object Edit_TargetID: TEdit
        Left = 72
        Top = 65
        Width = 85
        Height = 24
        TabOrder = 2
      end
    end
    object GroupBox4: TGroupBox
      Left = 13
      Top = 118
      Width = 163
      Height = 45
      Caption = 'Target xy'
      TabOrder = 1
      object Label10: TLabel
        Left = 7
        Top = 20
        Width = 5
        Height = 13
        Caption = 'x'
      end
      object Label11: TLabel
        Left = 85
        Top = 20
        Width = 5
        Height = 13
        Caption = 'y'
      end
      object Edit_targetx: TEdit
        Left = 20
        Top = 20
        Width = 59
        Height = 24
        TabOrder = 0
        Text = '.2788'
      end
      object Edit_targety: TEdit
        Left = 98
        Top = 20
        Width = 59
        Height = 24
        TabOrder = 1
        Text = '.2920'
      end
    end
    object RadioGroup1: TRadioGroup
      Left = 13
      Top = 176
      Width = 163
      Height = 65
      Caption = 'Adjustment Options'
      TabOrder = 2
    end
    object RadioButton1: TRadioButton
      Left = 20
      Top = 195
      Width = 137
      Height = 20
      Caption = 'Adjust to Target x,y'
      Checked = True
      TabOrder = 3
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 20
      Top = 215
      Width = 137
      Height = 20
      Caption = 'Adjust by RGB ratio'
      TabOrder = 4
    end
    object Button2: TButton
      Left = 59
      Top = 247
      Width = 65
      Height = 20
      Caption = 'Run'
      TabOrder = 5
      OnClick = Button2Click
    end
  end
  object Panel1: TPanel
    Left = 215
    Top = 20
    Width = 501
    Height = 319
    Color = clWhite
    TabOrder = 2
  end
  object ScrollBar_R: TScrollBar
    Left = 260
    Top = 351
    Width = 430
    Height = 14
    LargeChange = 10
    Max = 255
    PageSize = 0
    Position = 255
    TabOrder = 3
    OnChange = ScrollBar_RChange
  end
  object Edit_R: TEdit
    Left = 215
    Top = 345
    Width = 33
    Height = 24
    Enabled = False
    TabOrder = 4
    Text = '255'
  end
  object Edit_G: TEdit
    Left = 215
    Top = 371
    Width = 33
    Height = 24
    Enabled = False
    TabOrder = 5
    Text = '255'
  end
  object Edit_B: TEdit
    Left = 215
    Top = 397
    Width = 33
    Height = 24
    Enabled = False
    TabOrder = 6
    Text = '255'
  end
  object ScrollBar_G: TScrollBar
    Left = 260
    Top = 377
    Width = 430
    Height = 14
    LargeChange = 10
    Max = 255
    PageSize = 0
    Position = 255
    TabOrder = 7
    OnChange = ScrollBar_GChange
  end
  object ScrollBar_B: TScrollBar
    Left = 260
    Top = 403
    Width = 430
    Height = 14
    LargeChange = 10
    Max = 255
    PageSize = 0
    Position = 255
    TabOrder = 8
    OnChange = ScrollBar_BChange
  end
end
