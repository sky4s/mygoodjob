object StabilityForm: TStabilityForm
  Left = 378
  Top = 470
  Width = 221
  Height = 293
  Caption = 'Stability Measure'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 16
    Top = 8
    Width = 48
    Height = 13
    Caption = 'Wait Time'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 32
    Width = 193
    Height = 137
    Caption = 'Condition'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 76
      Height = 13
      Caption = 'Start Gray Level'
    end
    object Label2: TLabel
      Left = 8
      Top = 40
      Width = 76
      Height = 13
      Caption = 'Gray Level Step'
    end
    object Label3: TLabel
      Left = 8
      Top = 64
      Width = 72
      Height = 13
      Caption = 'Measure Count'
    end
    object Label5: TLabel
      Left = 8
      Top = 88
      Width = 53
      Height = 13
      Caption = 'Blank Time'
    end
    object Edit_Start: TEdit
      Left = 96
      Top = 16
      Width = 81
      Height = 21
      TabOrder = 0
      Text = '240'
    end
    object Edit_Step: TEdit
      Left = 96
      Top = 40
      Width = 81
      Height = 21
      TabOrder = 1
      Text = '32'
    end
    object Edit_Count: TEdit
      Left = 96
      Top = 64
      Width = 81
      Height = 21
      TabOrder = 2
      Text = '20'
    end
    object Button3: TButton
      Left = 15
      Top = 112
      Width = 74
      Height = 19
      Caption = 'Load Table'
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button1: TButton
      Left = 104
      Top = 112
      Width = 74
      Height = 19
      Caption = 'Go'
      TabOrder = 4
      OnClick = Button1Click
    end
    object Edit_Blank: TEdit
      Left = 96
      Top = 88
      Width = 81
      Height = 21
      TabOrder = 5
      Text = '0'
    end
  end
  object Button_ContinueMeasure: TButton
    Left = 64
    Top = 232
    Width = 105
    Height = 17
    Caption = 'Continue Measure'
    TabOrder = 1
    OnClick = Button_ContinueMeasureClick
  end
  object Edit_WaitTime: TEdit
    Left = 104
    Top = 8
    Width = 81
    Height = 21
    TabOrder = 2
    Text = '500'
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 168
    Width = 193
    Height = 49
    Caption = 'GroupBox2'
    TabOrder = 3
    object Button2: TButton
      Left = 15
      Top = 22
      Width = 74
      Height = 19
      Caption = 'Load Table'
      TabOrder = 0
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 104
      Top = 22
      Width = 74
      Height = 19
      Caption = 'Go'
      TabOrder = 1
      OnClick = Button4Click
    end
  end
  object OpenDialog1: TOpenDialog
    Top = 232
  end
end
