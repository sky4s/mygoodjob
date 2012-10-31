object ExampleForm: TExampleForm
  Left = 403
  Top = 148
  Width = 278
  Height = 620
  Caption = 'ExampleForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label5: TLabel
    Left = 8
    Top = 552
    Width = 32
    Height = 13
    Caption = 'Label5'
  end
  object GroupBox1: TGroupBox
    Left = 7
    Top = 7
    Width = 254
    Height = 226
    Caption = 'Test'
    TabOrder = 0
    object Label1: TLabel
      Left = 7
      Top = 39
      Width = 28
      Height = 13
      Caption = 'FPGA'
    end
    object Label2: TLabel
      Left = 7
      Top = 121
      Width = 44
      Height = 13
      Caption = 'HUE_EN'
    end
    object Label3: TLabel
      Left = 7
      Top = 71
      Width = 21
      Height = 13
      Caption = 'FPG'
    end
    object Label4: TLabel
      Left = 7
      Top = 191
      Width = 21
      Height = 13
      Caption = 'FPG'
    end
    object CheckBox1: TCheckBox
      Left = 7
      Top = 20
      Width = 78
      Height = 13
      Caption = 'HUE_EN'
      TabOrder = 0
    end
    object ComboBox1: TComboBox
      Left = 59
      Top = 39
      Width = 117
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'ComboBox1'
    end
    object ScrollBar1: TScrollBar
      Left = 59
      Top = 121
      Width = 98
      Height = 17
      PageSize = 0
      TabOrder = 2
    end
    object StaticText1: TStaticText
      Left = 169
      Top = 121
      Width = 58
      Height = 17
      Caption = 'StaticText1'
      TabOrder = 3
    end
    object LabeledEdit1: TLabeledEdit
      Left = 55
      Top = 160
      Width = 130
      Height = 21
      EditLabel.Width = 50
      EditLabel.Height = 11
      EditLabel.Caption = 'LabeledEdit1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
    end
    object CheckBox2: TCheckBox
      Left = 103
      Top = 20
      Width = 78
      Height = 13
      Caption = 'HSV_EN'
      TabOrder = 5
    end
    object ComboBox2: TComboBox
      Left = 59
      Top = 71
      Width = 117
      Height = 21
      ItemHeight = 13
      TabOrder = 6
      Text = 'ComboBox1'
    end
    object ComboBox3: TComboBox
      Left = 59
      Top = 95
      Width = 117
      Height = 21
      ItemHeight = 13
      TabOrder = 7
      Text = 'ComboBox1'
    end
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 248
    Width = 249
    Height = 297
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    TabOrder = 1
    OnSelectCell = StringGrid1SelectCell
    RowHeights = (
      24
      24
      24
      24
      24)
  end
end
