object AnalyzerFrame: TAnalyzerFrame
  Left = 0
  Top = 0
  Width = 244
  Height = 224
  TabOrder = 0
  object GroupBox3: TGroupBox
    Left = 16
    Top = 9
    Width = 209
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
  object GroupBox1: TGroupBox
    Left = 16
    Top = 128
    Width = 209
    Height = 57
    Caption = 'RGB ratio'
    TabOrder = 1
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
  object Button1: TButton
    Left = 80
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Enter'
    TabOrder = 2
  end
end
