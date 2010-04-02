object GammaMeasurementForm: TGammaMeasurementForm
  Left = 192
  Top = 131
  Width = 771
  Height = 379
  Caption = 'GammaMeasurementForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Copyright: TLabel
    Left = 26
    Top = 322
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
    IsControl = True
  end
  object Panel2: TPanel
    Left = 384
    Top = 16
    Width = 369
    Height = 305
    Caption = 'Panel2'
    TabOrder = 1
    Visible = False
    object GroupBox5: TGroupBox
      Left = 8
      Top = 16
      Width = 353
      Height = 281
      Caption = 'Direct Pattern Measurement (T-CON Input for 10in)'
      TabOrder = 0
      object GroupBox6: TGroupBox
        Left = 8
        Top = 24
        Width = 265
        Height = 249
        Caption = 'Pattern Type'
        TabOrder = 0
        object GroupBox7: TGroupBox
          Left = 8
          Top = 24
          Width = 105
          Height = 89
          Caption = 'LUT'
          TabOrder = 0
          object RadioButton1: TRadioButton
            Left = 8
            Top = 24
            Width = 57
            Height = 25
            Caption = '10 bit'
            TabOrder = 0
          end
          object RadioButton2: TRadioButton
            Left = 8
            Top = 48
            Width = 57
            Height = 25
            Caption = '12 bit'
            TabOrder = 1
          end
        end
        object GroupBox8: TGroupBox
          Left = 120
          Top = 24
          Width = 137
          Height = 89
          Caption = 'Other'
          TabOrder = 1
          object CheckBox5: TCheckBox
            Left = 8
            Top = 56
            Width = 97
            Height = 25
            Caption = 'Interpolation'
            TabOrder = 0
          end
          object CheckBox6: TCheckBox
            Left = 8
            Top = 24
            Width = 97
            Height = 25
            Caption = 'Gamma 256'
            TabOrder = 1
          end
        end
        object GroupBox9: TGroupBox
          Left = 8
          Top = 120
          Width = 153
          Height = 121
          Caption = 'Patterns'
          TabOrder = 2
          object Label4: TLabel
            Left = 32
            Top = 72
            Width = 113
            Height = 25
            Caption = '(S/W Interpolation)'
          end
          object RadioButton3: TRadioButton
            Left = 8
            Top = 24
            Width = 113
            Height = 25
            Caption = '0~256 Pattern'
            TabOrder = 0
          end
          object RadioButton4: TRadioButton
            Left = 8
            Top = 48
            Width = 113
            Height = 25
            Caption = '0~1023 Pattern'
            TabOrder = 1
          end
        end
        object Button2: TButton
          Left = 168
          Top = 208
          Width = 89
          Height = 25
          Caption = 'Load Table'
          TabOrder = 3
        end
      end
      object GroupBox10: TGroupBox
        Left = 280
        Top = 24
        Width = 65
        Height = 153
        Caption = 'Color'
        TabOrder = 1
        object CheckBox_W2: TCheckBox
          Left = 8
          Top = 24
          Width = 41
          Height = 25
          Caption = 'W'
          TabOrder = 0
        end
        object CheckBox_R2: TCheckBox
          Left = 8
          Top = 56
          Width = 41
          Height = 25
          Caption = 'R'
          TabOrder = 1
        end
        object CheckBox_G2: TCheckBox
          Left = 8
          Top = 88
          Width = 41
          Height = 25
          Caption = 'G'
          TabOrder = 2
        end
        object CheckBox_B2: TCheckBox
          Left = 8
          Top = 120
          Width = 33
          Height = 25
          Caption = 'B'
          TabOrder = 3
        end
      end
      object GroupBox11: TGroupBox
        Left = 280
        Top = 176
        Width = 65
        Height = 65
        Caption = 'Channel'
        TabOrder = 2
        object Edit_Channel2: TEdit
          Left = 8
          Top = 24
          Width = 41
          Height = 24
          TabOrder = 0
          Text = '0'
        end
      end
      object Button_TCONMeasure: TButton
        Left = 280
        Top = 248
        Width = 65
        Height = 25
        Caption = 'Measure'
        TabOrder = 3
        OnClick = Button_TCONMeasureClick
      end
    end
  end
  object Panel1: TPanel
    Left = 8
    Top = 16
    Width = 369
    Height = 201
    Caption = 'Panel1'
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 353
      Height = 185
      Caption = 'Gamma Measurement (PC Input)'
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 8
        Top = 24
        Width = 193
        Height = 153
        Caption = 'Gray Level Option'
        TabOrder = 0
        object Label1: TLabel
          Left = 8
          Top = 24
          Width = 63
          Height = 16
          Caption = 'Start Level'
        end
        object Label2: TLabel
          Left = 8
          Top = 56
          Width = 60
          Height = 16
          Caption = 'End Level'
        end
        object Label3: TLabel
          Left = 8
          Top = 88
          Width = 64
          Height = 16
          Caption = 'Level Step'
        end
        object Edit_StartLevel: TEdit
          Left = 80
          Top = 24
          Width = 105
          Height = 24
          TabOrder = 0
          Text = '255'
        end
        object ComboBox_LevelStep: TComboBox
          Left = 80
          Top = 88
          Width = 105
          Height = 24
          ItemHeight = 16
          TabOrder = 1
          Text = '1'
          Items.Strings = (
            '1'
            '2'
            '4'
            '8'
            '16'
            '32')
        end
        object Edit_EndLevel: TEdit
          Left = 80
          Top = 56
          Width = 105
          Height = 24
          TabOrder = 2
          Text = '0'
        end
      end
      object GroupBox3: TGroupBox
        Left = 208
        Top = 24
        Width = 57
        Height = 153
        Caption = 'Color'
        TabOrder = 1
        object CheckBox_W: TCheckBox
          Left = 8
          Top = 24
          Width = 41
          Height = 25
          Caption = 'W'
          TabOrder = 0
        end
        object CheckBox_R: TCheckBox
          Left = 8
          Top = 56
          Width = 41
          Height = 25
          Caption = 'R'
          TabOrder = 1
        end
        object CheckBox_G: TCheckBox
          Left = 8
          Top = 88
          Width = 41
          Height = 25
          Caption = 'G'
          TabOrder = 2
        end
        object CheckBox_B: TCheckBox
          Left = 8
          Top = 120
          Width = 33
          Height = 25
          Caption = 'B'
          TabOrder = 3
        end
      end
      object GroupBox4: TGroupBox
        Left = 272
        Top = 24
        Width = 73
        Height = 65
        Caption = 'Channel'
        TabOrder = 2
        object Edit_Channel: TEdit
          Left = 16
          Top = 24
          Width = 41
          Height = 25
          TabOrder = 0
          Text = '0'
        end
      end
      object Button_PCMeasure: TButton
        Left = 272
        Top = 144
        Width = 73
        Height = 25
        Caption = 'Measure'
        TabOrder = 3
        OnClick = Button_PCMeasureClick
      end
    end
  end
end
