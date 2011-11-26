object ExampleForm: TExampleForm
  Left = 352
  Top = 143
  Width = 353
  Height = 750
  Caption = 'ExampleForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 313
    Height = 161
    Caption = 'GroupBox1'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 48
      Width = 41
      Height = 16
      Caption = 'Label1'
    end
    object Label2: TLabel
      Left = 8
      Top = 80
      Width = 41
      Height = 16
      Caption = 'Label2'
    end
    object CheckBox1: TCheckBox
      Left = 8
      Top = 24
      Width = 97
      Height = 17
      Caption = 'CheckBox1'
      TabOrder = 0
    end
    object ComboBox1: TComboBox
      Left = 72
      Top = 48
      Width = 145
      Height = 24
      ItemHeight = 16
      TabOrder = 1
      Text = 'ComboBox1'
    end
    object ScrollBar1: TScrollBar
      Left = 72
      Top = 80
      Width = 121
      Height = 21
      PageSize = 0
      TabOrder = 2
    end
    object StaticText1: TStaticText
      Left = 208
      Top = 80
      Width = 70
      Height = 20
      Caption = 'StaticText1'
      TabOrder = 3
    end
    object LabeledEdit1: TLabeledEdit
      Left = 8
      Top = 128
      Width = 121
      Height = 24
      EditLabel.Width = 80
      EditLabel.Height = 16
      EditLabel.Caption = 'LabeledEdit1'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
    end
  end
end
