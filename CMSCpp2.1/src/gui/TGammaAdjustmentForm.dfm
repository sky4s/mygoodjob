object GammaAdjustmentForm: TGammaAdjustmentForm
  Left = 252
  Top = 251
  Width = 467
  Height = 426
  Caption = 'Gamma Adjustment'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label9: TLabel
    Left = 78
    Top = 299
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox2: TGroupBox
    Left = 7
    Top = 13
    Width = 176
    Height = 46
    Caption = 'Gray Level Step'
    TabOrder = 0
    object ComboBox_LevelStep: TComboBox
      Left = 7
      Top = 20
      Width = 85
      Height = 21
      ItemHeight = 13
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
    Left = 189
    Top = 13
    Width = 176
    Height = 202
    Caption = 'Gamma'
    TabOrder = 1
    object GroupBox4: TGroupBox
      Left = 7
      Top = 20
      Width = 163
      Height = 46
      Caption = 'Gray'
      TabOrder = 0
      object Label1: TLabel
        Left = 13
        Top = 20
        Width = 11
        Height = 13
        Caption = 'W'
      end
      object Edit_GammaW: TEdit
        Left = 33
        Top = 20
        Width = 59
        Height = 24
        TabOrder = 0
        Text = '2.4'
      end
      object Button1: TButton
        Left = 98
        Top = 20
        Width = 59
        Height = 20
        Caption = 'Run'
        TabOrder = 1
      end
    end
    object GroupBox5: TGroupBox
      Left = 7
      Top = 72
      Width = 163
      Height = 98
      Caption = 'RGB'
      TabOrder = 1
      object Label2: TLabel
        Left = 13
        Top = 20
        Width = 8
        Height = 13
        Caption = 'R'
      end
      object Label3: TLabel
        Left = 13
        Top = 46
        Width = 8
        Height = 13
        Caption = 'G'
      end
      object Label4: TLabel
        Left = 13
        Top = 72
        Width = 7
        Height = 13
        Caption = 'B'
      end
      object Edit1: TEdit
        Left = 33
        Top = 20
        Width = 59
        Height = 24
        TabOrder = 0
        Text = '2.4'
      end
      object Edit2: TEdit
        Left = 33
        Top = 46
        Width = 59
        Height = 24
        TabOrder = 1
        Text = '2.4'
      end
      object Edit3: TEdit
        Left = 33
        Top = 72
        Width = 59
        Height = 24
        TabOrder = 2
        Text = '2.4'
      end
      object Button2: TButton
        Left = 98
        Top = 72
        Width = 59
        Height = 20
        Caption = 'Run'
        TabOrder = 3
      end
    end
    object Button3: TButton
      Left = 52
      Top = 176
      Width = 79
      Height = 20
      Caption = 'Load Gamma'
      TabOrder = 2
    end
  end
  object GroupBox1: TGroupBox
    Left = 7
    Top = 65
    Width = 176
    Height = 150
    Caption = 'Options'
    TabOrder = 2
    object CheckBox_AvoidNoise: TCheckBox
      Left = 7
      Top = 46
      Width = 111
      Height = 20
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 7
      Top = 20
      Width = 124
      Height = 20
      Caption = 'Keep Max Luminance'
      TabOrder = 1
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 7
    Top = 221
    Width = 364
    Height = 72
    TabOrder = 3
    inherited GroupBox_OutputFile: TGroupBox
      Width = 359
      Height = 73
      inherited Label5: TLabel
        Left = 7
        Top = 20
      end
      inherited Label6: TLabel
        Left = 7
        Top = 46
      end
      inherited Edit_Prefix: TEdit
        Left = 91
        Top = 20
        Width = 163
        Height = 24
      end
      inherited Edit_Directory: TEdit
        Left = 91
        Top = 46
        Width = 209
        Height = 24
      end
      inherited Button_BrowseDir: TButton
        Left = 306
        Top = 46
        Width = 46
        Height = 20
      end
    end
  end
end
