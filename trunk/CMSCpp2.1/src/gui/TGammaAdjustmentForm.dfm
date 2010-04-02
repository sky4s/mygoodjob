object GammaAdjustmentForm: TGammaAdjustmentForm
  Left = 300
  Top = 300
  Width = 481
  Height = 490
  Caption = 'Gamma Adjustment'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Label9: TLabel
    Left = 104
    Top = 432
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 240
    Top = 16
    Width = 89
    Height = 57
    Caption = 'Channel'
    TabOrder = 0
    object Edit_Channel: TEdit
      Left = 24
      Top = 24
      Width = 41
      Height = 24
      TabOrder = 0
      Text = '0'
    end
  end
  object GroupBox2: TGroupBox
    Left = 336
    Top = 16
    Width = 121
    Height = 57
    Caption = 'Gray Level Step'
    TabOrder = 1
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
  inline TOptionsFrame1: TOptionsFrame
    Left = 16
    Top = 16
    Width = 218
    Height = 313
    TabOrder = 2
    inherited GroupBox5: TGroupBox
      Height = 314
      inherited GroupBox6: TGroupBox
        inherited GroupBox8: TGroupBox
          inherited RadioButton_In8: TRadioButton
            OnClick = nil
          end
          inherited RadioButton_In10: TRadioButton
            OnClick = nil
          end
        end
        inherited GroupBox9: TGroupBox
          inherited RadioButton_Lut10: TRadioButton
            OnClick = nil
          end
          inherited RadioButton_Lut12: TRadioButton
            OnClick = nil
          end
        end
        inherited GroupBox10: TGroupBox
          inherited RadioButton_Out6: TRadioButton
            OnClick = nil
          end
          inherited RadioButton_Out8: TRadioButton
            OnClick = nil
          end
          inherited RadioButton_Out10: TRadioButton
            OnClick = nil
          end
        end
      end
      inherited CheckBox_Gamma256: TCheckBox
        Visible = False
        OnClick = nil
      end
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 16
    Top = 336
    Width = 441
    Height = 88
    TabOrder = 3
    inherited GroupBox7: TGroupBox
      Width = 442
      inherited Edit_Directory: TEdit
        Width = 257
      end
      inherited Button_BrowseDir: TButton
        Left = 376
        OnClick = nil
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 240
    Top = 80
    Width = 217
    Height = 249
    Caption = 'Gamma'
    TabOrder = 4
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
        Width = 25
        Height = 25
        Caption = 'W'
      end
      object Edit_GammaW: TEdit
        Left = 40
        Top = 24
        Width = 73
        Height = 25
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
        Width = 25
        Height = 25
        Caption = 'R'
      end
      object Label3: TLabel
        Left = 16
        Top = 56
        Width = 25
        Height = 25
        Caption = 'G'
      end
      object Label4: TLabel
        Left = 16
        Top = 88
        Width = 17
        Height = 25
        Caption = 'B'
      end
      object Edit1: TEdit
        Left = 40
        Top = 24
        Width = 73
        Height = 25
        TabOrder = 0
        Text = '2.4'
      end
      object Edit2: TEdit
        Left = 40
        Top = 56
        Width = 73
        Height = 25
        TabOrder = 1
        Text = '2.4'
      end
      object Edit3: TEdit
        Left = 40
        Top = 88
        Width = 73
        Height = 25
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
end
