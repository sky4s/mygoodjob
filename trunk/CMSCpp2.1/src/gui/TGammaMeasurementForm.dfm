object GammaMeasurementForm: TGammaMeasurementForm
  Left = 300
  Top = 300
  Width = 723
  Height = 468
  Caption = 'GammaMeasurementForm'
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
  object Copyright: TLabel
    Left = 42
    Top = 410
    Width = 349
    Height = 16
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
    IsControl = True
  end
  object Panel1: TPanel
    Left = 8
    Top = 16
    Width = 305
    Height = 297
    Caption = 'Panel1'
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 289
      Height = 281
      Caption = 'Gamma Measurement (PC Input)'
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 8
        Top = 24
        Width = 193
        Height = 121
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
    end
  end
  object Panel2: TPanel
    Left = 400
    Top = 16
    Width = 305
    Height = 297
    Caption = 'Panel2'
    TabOrder = 1
    Visible = False
    object GroupBox5: TGroupBox
      Left = 8
      Top = 8
      Width = 289
      Height = 281
      Caption = 'Direct Pattern Measurement (T-CON Input)'
      TabOrder = 0
      object GroupBox6: TGroupBox
        Left = 8
        Top = 24
        Width = 169
        Height = 249
        Caption = 'Pattern Type'
        TabOrder = 0
        object GroupBox8: TGroupBox
          Left = 8
          Top = 152
          Width = 137
          Height = 89
          Caption = 'Options'
          TabOrder = 0
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
          Top = 24
          Width = 153
          Height = 121
          Caption = 'Patterns'
          TabOrder = 1
          object Label4: TLabel
            Left = 32
            Top = 72
            Width = 112
            Height = 16
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
      end
      object Table: TGroupBox
        Left = 184
        Top = 24
        Width = 97
        Height = 113
        Caption = 'Table'
        TabOrder = 1
        object RadioButton1: TRadioButton
          Left = 8
          Top = 24
          Width = 73
          Height = 25
          Caption = '10bit'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton2: TRadioButton
          Left = 8
          Top = 48
          Width = 81
          Height = 25
          Caption = '12bit'
          TabOrder = 1
        end
        object Button2: TButton
          Left = 8
          Top = 80
          Width = 81
          Height = 25
          Caption = 'Load Table'
          TabOrder = 2
        end
      end
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 8
    Top = 320
    Width = 393
    Height = 88
    TabOrder = 2
    inherited GroupBox_OutputFile: TGroupBox
      Width = 386
      inherited Edit_Directory: TEdit
        Width = 201
      end
      inherited Button_BrowseDir: TButton
        Left = 320
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 320
    Top = 16
    Width = 73
    Height = 265
    Caption = 'Color'
    TabOrder = 3
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
  object Button_Measure: TButton
    Left = 320
    Top = 288
    Width = 73
    Height = 25
    Caption = 'Measure'
    TabOrder = 4
    OnClick = Button_MeasureClick
  end
end
