object GammaAdjustmentForm: TGammaAdjustmentForm
  Left = 300
  Top = 300
  Width = 467
  Height = 426
  Caption = 'Gamma Adjustment'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object Label9: TLabel
    Left = 96
    Top = 368
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 16
    Width = 217
    Height = 57
    Caption = 'Gray Level Step'
    TabOrder = 0
    object ComboBox_LevelStep: TComboBox
      Left = 8
      Top = 25
      Width = 105
      Height = 24
      ItemHeight = 16
      TabOrder = 0
      Text = '1'
      Items.Strings = (
        '1'
        '2'
        '4'
        '8'
        '16'
        '32')
    end
  end
  object GroupBox3: TGroupBox
    Left = 232
    Top = 16
    Width = 217
    Height = 249
    Caption = 'Gamma'
    TabOrder = 1
    object GroupBox4: TGroupBox
      Left = 8
      Top = 24
      Width = 201
      Height = 57
      Caption = 'Gray'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 24
        Width = 13
        Height = 16
        Caption = 'W'
      end
      object Edit_GammaW: TEdit
        Left = 40
        Top = 24
        Width = 73
        Height = 24
        TabOrder = 0
        Text = '2.4'
      end
      object Button1: TButton
        Left = 120
        Top = 24
        Width = 73
        Height = 25
        Caption = 'Run'
        TabOrder = 1
      end
    end
    object GroupBox5: TGroupBox
      Left = 8
      Top = 88
      Width = 201
      Height = 121
      Caption = 'RGB'
      TabOrder = 1
      object Label2: TLabel
        Left = 16
        Top = 24
        Width = 10
        Height = 16
        Caption = 'R'
      end
      object Label3: TLabel
        Left = 16
        Top = 56
        Width = 10
        Height = 16
        Caption = 'G'
      end
      object Label4: TLabel
        Left = 16
        Top = 88
        Width = 9
        Height = 16
        Caption = 'B'
      end
      object Edit1: TEdit
        Left = 40
        Top = 24
        Width = 73
        Height = 24
        TabOrder = 0
        Text = '2.4'
      end
      object Edit2: TEdit
        Left = 40
        Top = 56
        Width = 73
        Height = 24
        TabOrder = 1
        Text = '2.4'
      end
      object Edit3: TEdit
        Left = 40
        Top = 88
        Width = 73
        Height = 24
        TabOrder = 2
        Text = '2.4'
      end
      object Button2: TButton
        Left = 120
        Top = 88
        Width = 73
        Height = 25
        Caption = 'Run'
        TabOrder = 3
      end
    end
    object Button3: TButton
      Left = 64
      Top = 216
      Width = 97
      Height = 25
      Caption = 'Load Gamma'
      TabOrder = 2
    end
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 80
    Width = 217
    Height = 185
    Caption = 'Options'
    TabOrder = 2
    object CheckBox_AvoidNoise: TCheckBox
      Left = 8
      Top = 56
      Width = 137
      Height = 25
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 8
      Top = 24
      Width = 153
      Height = 25
      Caption = 'Keep Max Luminance'
      TabOrder = 1
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 8
    Top = 272
    Width = 449
    Height = 88
    TabOrder = 3
    inherited GroupBox_OutputFile: TGroupBox
      Width = 442
      inherited Edit_Directory: TEdit
        Width = 257
      end
      inherited Button_BrowseDir: TButton
        Left = 376
      end
    end
  end
end
