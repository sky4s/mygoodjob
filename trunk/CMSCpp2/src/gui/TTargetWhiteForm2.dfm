object TargetWhiteForm2: TTargetWhiteForm2
  Left = 119
  Top = 116
  Width = 921
  Height = 530
  Caption = 'TargetWhiteForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox3: TGroupBox
    Left = 16
    Top = 9
    Width = 257
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
      Left = 97
      Top = 16
      Width = 48
      Height = 24
      TabOrder = 0
      Text = '0'
    end
    object Edit_TargetCH: TEdit
      Left = 97
      Top = 48
      Width = 48
      Height = 24
      TabOrder = 1
      Text = '2'
    end
    object Edit_TargetID: TEdit
      Left = 97
      Top = 80
      Width = 104
      Height = 24
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 128
    Width = 257
    Height = 361
    Caption = 'Matrix Calibration'
    TabOrder = 1
    object RadioGroup1: TRadioGroup
      Left = 8
      Top = 25
      Width = 241
      Height = 296
      Caption = 'Adjustment Options'
      TabOrder = 1
    end
    object RadioButton1: TRadioButton
      Left = 16
      Top = 168
      Width = 168
      Height = 25
      Caption = 'Adjust to Target x,y'
      Checked = True
      TabOrder = 2
      TabStop = True
    end
    object RadioButton2: TRadioButton
      Left = 16
      Top = 81
      Width = 160
      Height = 24
      Caption = 'Adjust by RGB ratio'
      TabOrder = 3
    end
    object Button2: TButton
      Left = 89
      Top = 328
      Width = 80
      Height = 25
      Caption = 'Run'
      TabOrder = 4
    end
    object GroupBox4: TGroupBox
      Left = 32
      Top = 193
      Width = 209
      Height = 120
      Caption = 'Target xy on D-Locus'
      TabOrder = 0
      object Label10: TLabel
        Left = 9
        Top = 25
        Width = 6
        Height = 16
        Caption = 'x'
      end
      object Label11: TLabel
        Left = 113
        Top = 25
        Width = 7
        Height = 16
        Caption = 'y'
      end
      object Label2: TLabel
        Left = 105
        Top = 64
        Width = 8
        Height = 16
        Caption = 'K'
      end
      object Label1: TLabel
        Left = 9
        Top = 64
        Width = 18
        Height = 16
        Caption = 'CT'
      end
      object Label5: TLabel
        Left = 8
        Top = 97
        Width = 10
        Height = 16
        Caption = 'u'#39
      end
      object Label6: TLabel
        Left = 112
        Top = 97
        Width = 10
        Height = 16
        Caption = 'v'#39
      end
      object Edit_targetx: TEdit
        Left = 33
        Top = 25
        Width = 72
        Height = 24
        TabOrder = 0
        Text = '0.2788'
        OnChange = Edit_targetxChange
      end
      object Edit_targety: TEdit
        Left = 129
        Top = 25
        Width = 72
        Height = 24
        TabOrder = 1
        Text = '0.2920'
        OnChange = Edit_targetyChange
      end
      object Edit_CT: TEdit
        Left = 32
        Top = 57
        Width = 73
        Height = 24
        TabOrder = 2
        Text = '10000'
        OnChange = Edit_CTChange
      end
      object Edit_up: TEdit
        Left = 32
        Top = 89
        Width = 73
        Height = 24
        Enabled = False
        TabOrder = 3
        Text = '0.1876'
      end
      object Edit_vp: TEdit
        Left = 128
        Top = 89
        Width = 73
        Height = 24
        Enabled = False
        TabOrder = 4
        Text = '0.4419'
      end
    end
    object RadioButton3: TRadioButton
      Left = 16
      Top = 48
      Width = 145
      Height = 25
      Caption = 'Adjust to Max RGB'
      TabOrder = 5
      OnClick = RadioButton3Click
    end
    object GroupBox1: TGroupBox
      Left = 32
      Top = 104
      Width = 209
      Height = 57
      Caption = 'RGB ratio'
      TabOrder = 6
      object Edit_R: TEdit
        Left = 9
        Top = 25
        Width = 40
        Height = 24
        TabOrder = 0
        Text = '255'
      end
      object Edit_G: TEdit
        Left = 57
        Top = 25
        Width = 40
        Height = 24
        TabOrder = 1
        Text = '255'
      end
      object Edit_B: TEdit
        Left = 105
        Top = 25
        Width = 40
        Height = 24
        TabOrder = 2
        Text = '255'
      end
    end
  end
  object GroupBox5: TGroupBox
    Left = 288
    Top = 8
    Width = 617
    Height = 481
    Caption = 'RGB Pattern'
    TabOrder = 2
    object Label13: TLabel
      Left = 8
      Top = 417
      Width = 10
      Height = 16
      Caption = 'G'
    end
    object Label14: TLabel
      Left = 8
      Top = 449
      Width = 9
      Height = 16
      Caption = 'B'
    end
    object Label12: TLabel
      Left = 8
      Top = 385
      Width = 10
      Height = 16
      Caption = 'R'
    end
    object ScrollBar_R: TScrollBar
      Left = 80
      Top = 392
      Width = 529
      Height = 17
      LargeChange = 10
      Max = 255
      PageSize = 0
      Position = 255
      TabOrder = 0
      OnChange = ScrollBar_RChange
    end
    object ScrollBar_G: TScrollBar
      Left = 80
      Top = 424
      Width = 529
      Height = 17
      LargeChange = 10
      Max = 255
      PageSize = 0
      Position = 255
      TabOrder = 1
      OnChange = ScrollBar_GChange
    end
    object ScrollBar_B: TScrollBar
      Left = 80
      Top = 456
      Width = 529
      Height = 17
      LargeChange = 10
      Max = 255
      PageSize = 0
      Position = 255
      TabOrder = 2
      OnChange = ScrollBar_BChange
    end
    object Panel1: TPanel
      Left = 9
      Top = 25
      Width = 600
      Height = 352
      Color = clWhite
      TabOrder = 3
    end
    object Edit_ScrollR: TEdit
      Left = 25
      Top = 385
      Width = 40
      Height = 24
      Enabled = False
      TabOrder = 4
      Text = '255'
    end
    object Edit_ScrollG: TEdit
      Left = 25
      Top = 417
      Width = 40
      Height = 24
      Enabled = False
      TabOrder = 5
      Text = '255'
    end
    object Edit_ScrollB: TEdit
      Left = 25
      Top = 449
      Width = 40
      Height = 24
      Enabled = False
      TabOrder = 6
      Text = '255'
    end
  end
end
