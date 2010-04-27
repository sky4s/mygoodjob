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
  OnCreate = FormCreate
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
    Left = 9
    Top = 16
    Width = 216
    Height = 57
    Caption = 'Gray Level Step'
    TabOrder = 0
    object ComboBox_LevelStep: TComboBox
      Left = 9
      Top = 25
      Width = 104
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
    Left = 233
    Top = 16
    Width = 216
    Height = 249
    Caption = 'Gamma'
    TabOrder = 1
    object GroupBox4: TGroupBox
      Left = 9
      Top = 25
      Width = 200
      Height = 56
      Caption = 'Gray'
      TabOrder = 0
      object Label1: TLabel
        Left = 16
        Top = 25
        Width = 13
        Height = 16
        Caption = 'W'
      end
      object Button_GrayGamma: TButton
        Left = 144
        Top = 25
        Width = 49
        Height = 24
        Caption = 'Run'
        TabOrder = 0
        OnClick = Button_GrayGammaClick
      end
      object ComboBox_GrayGamma: TComboBox
        Left = 40
        Top = 24
        Width = 97
        Height = 24
        ItemHeight = 16
        ItemIndex = 4
        TabOrder = 1
        Text = '2.2'
        Items.Strings = (
          '1.8'
          '1.9'
          '2.0'
          '2.1'
          '2.2'
          '2.3'
          '2.4'
          '2.5')
      end
    end
    object GroupBox5: TGroupBox
      Left = 9
      Top = 89
      Width = 200
      Height = 120
      Caption = 'RGB'
      TabOrder = 1
      object Label2: TLabel
        Left = 16
        Top = 25
        Width = 10
        Height = 16
        Caption = 'R'
      end
      object Label3: TLabel
        Left = 16
        Top = 57
        Width = 10
        Height = 16
        Caption = 'G'
      end
      object Label4: TLabel
        Left = 16
        Top = 89
        Width = 9
        Height = 16
        Caption = 'B'
      end
      object Button_RGBGamma: TButton
        Left = 152
        Top = 89
        Width = 41
        Height = 24
        Caption = 'Run'
        TabOrder = 0
        OnClick = Button_RGBGammaClick
      end
      object ComboBox_RGamma: TComboBox
        Left = 40
        Top = 24
        Width = 97
        Height = 24
        ItemHeight = 16
        ItemIndex = 4
        TabOrder = 1
        Text = '2.2'
        Items.Strings = (
          '1.8'
          '1.9'
          '2.0'
          '2.1'
          '2.2'
          '2.3'
          '2.4'
          '2.5')
      end
      object ComboBox_GGamma: TComboBox
        Left = 40
        Top = 56
        Width = 97
        Height = 24
        ItemHeight = 16
        ItemIndex = 4
        TabOrder = 2
        Text = '2.2'
        Items.Strings = (
          '1.8'
          '1.9'
          '2.0'
          '2.1'
          '2.2'
          '2.3'
          '2.4'
          '2.5')
      end
      object ComboBox_BGamma: TComboBox
        Left = 40
        Top = 88
        Width = 97
        Height = 24
        ItemHeight = 16
        ItemIndex = 4
        TabOrder = 3
        Text = '2.2'
        Items.Strings = (
          '1.8'
          '1.9'
          '2.0'
          '2.1'
          '2.2'
          '2.3'
          '2.4'
          '2.5')
      end
    end
    object Button3: TButton
      Left = 16
      Top = 217
      Width = 97
      Height = 24
      Caption = 'Load Gamma'
      TabOrder = 2
      OnClick = Button3Click
    end
    object CheckBox_LoadingGamma: TCheckBox
      Left = 120
      Top = 216
      Width = 81
      Height = 25
      Caption = 'Loading'
      Enabled = False
      TabOrder = 3
      OnClick = CheckBox_LoadingGammaClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 9
    Top = 80
    Width = 216
    Height = 185
    Caption = 'Options'
    TabOrder = 2
    object CheckBox_AvoidNoise: TCheckBox
      Left = 9
      Top = 57
      Width = 136
      Height = 24
      Caption = 'Avoid FRC Noise'
      TabOrder = 0
    end
    object CheckBox_KeepMax: TCheckBox
      Left = 9
      Top = 25
      Width = 152
      Height = 24
      Caption = 'Keep Max Luminance'
      TabOrder = 1
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 9
    Top = 272
    Width = 448
    Height = 89
    TabOrder = 3
    inherited GroupBox_OutputFile: TGroupBox
      Width = 442
      Height = 90
      inherited Label5: TLabel
        Left = 9
        Top = 25
      end
      inherited Label6: TLabel
        Left = 9
        Top = 57
      end
      inherited Edit_Prefix: TEdit
        Top = 25
      end
      inherited Edit_Directory: TEdit
        Top = 57
        Width = 257
      end
      inherited Button_BrowseDir: TButton
        Left = 377
        Top = 57
        Width = 56
        Height = 24
      end
    end
  end
  object OpenDialog1: TOpenDialog
  end
end
