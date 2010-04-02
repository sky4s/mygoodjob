object OutputFileFrame: TOutputFileFrame
  Left = 0
  Top = 0
  Width = 553
  Height = 88
  TabOrder = 0
  object GroupBox7: TGroupBox
    Left = -1
    Top = -1
    Width = 553
    Height = 89
    Caption = 'Output File'
    TabOrder = 0
    object Label5: TLabel
      Left = 8
      Top = 24
      Width = 92
      Height = 16
      Caption = 'Filename Prefix'
    end
    object Label6: TLabel
      Left = 8
      Top = 56
      Width = 95
      Height = 16
      Caption = 'Output Directory'
    end
    object Edit_Prefix: TEdit
      Left = 112
      Top = 24
      Width = 201
      Height = 24
      TabOrder = 0
      Text = 'Calib00_Table'
    end
    object Edit_Directory: TEdit
      Left = 112
      Top = 56
      Width = 369
      Height = 24
      TabOrder = 1
      Text = 'D:\Gamma Table\'
    end
    object Button_BrowseDir: TButton
      Left = 488
      Top = 56
      Width = 57
      Height = 25
      Caption = 'Browse'
      TabOrder = 2
    end
  end
end
