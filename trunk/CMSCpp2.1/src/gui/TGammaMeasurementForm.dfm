object GammaMeasurementForm: TGammaMeasurementForm
  Left = 252
  Top = 236
  Width = 418
  Height = 468
  Caption = 'Gamma Measurement'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyPress = FormKeyPress
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
    Left = 9
    Top = 16
    Width = 304
    Height = 297
    Caption = 'Panel1'
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 9
      Top = 9
      Width = 288
      Height = 280
      Caption = 'Gamma Measurement (PC Input)'
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 9
        Top = 25
        Width = 192
        Height = 120
        Caption = 'Gray Level Option'
        TabOrder = 0
        object Label1: TLabel
          Left = 9
          Top = 25
          Width = 63
          Height = 16
          Caption = 'Start Level'
        end
        object Label2: TLabel
          Left = 9
          Top = 57
          Width = 60
          Height = 16
          Caption = 'End Level'
        end
        object Label3: TLabel
          Left = 9
          Top = 89
          Width = 64
          Height = 16
          Caption = 'Level Step'
        end
        object Edit_StartLevel: TEdit
          Left = 80
          Top = 25
          Width = 105
          Height = 24
          TabOrder = 0
          Text = '255'
        end
        object ComboBox_LevelStep: TComboBox
          Left = 80
          Top = 89
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
            '17'
            '32'
            '34')
        end
        object Edit_EndLevel: TEdit
          Left = 80
          Top = 57
          Width = 105
          Height = 24
          TabOrder = 2
          Text = '0'
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 9
    Top = 16
    Width = 304
    Height = 297
    Caption = 'Panel2'
    TabOrder = 1
    Visible = False
    object GroupBox5: TGroupBox
      Left = 9
      Top = 9
      Width = 288
      Height = 280
      Caption = 'Direct Pattern Measurement (T-CON Input)'
      TabOrder = 0
      object GroupBox6: TGroupBox
        Left = 113
        Top = 17
        Width = 168
        Height = 112
        Caption = 'Pattern Type'
        TabOrder = 0
        object GroupBox9: TGroupBox
          Left = 9
          Top = 25
          Width = 152
          Height = 80
          Caption = 'Patterns'
          TabOrder = 0
          object RadioButton_0To256: TRadioButton
            Left = 9
            Top = 25
            Width = 112
            Height = 24
            Caption = '0~256 Pattern'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton_0To1023: TRadioButton
            Left = 9
            Top = 48
            Width = 112
            Height = 25
            Caption = '0~1023 Pattern'
            TabOrder = 1
          end
        end
      end
      object Table: TGroupBox
        Left = 9
        Top = 17
        Width = 96
        Height = 112
        Caption = 'Table'
        TabOrder = 1
        object RadioButton_10Bit: TRadioButton
          Left = 9
          Top = 25
          Width = 72
          Height = 24
          Caption = '10bit'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton_12Bit: TRadioButton
          Left = 9
          Top = 48
          Width = 80
          Height = 25
          Caption = '12bit'
          TabOrder = 1
        end
        object Button2: TButton
          Left = 9
          Top = 80
          Width = 80
          Height = 25
          Caption = 'Load Table'
          TabOrder = 2
          OnClick = Button2Click
        end
      end
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 9
    Top = 320
    Width = 392
    Height = 89
    TabOrder = 2
    inherited GroupBox_OutputFile: TGroupBox
      Width = 386
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
        Text = 'Measurement'
      end
      inherited Edit_Directory: TEdit
        Top = 57
        Width = 201
      end
      inherited Button_BrowseDir: TButton
        Left = 320
        Top = 57
        Height = 24
        OnClick = TOutputFileFrame1Button_BrowseDirClick
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
      Left = 9
      Top = 25
      Width = 40
      Height = 24
      Caption = 'W'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object CheckBox_R: TCheckBox
      Left = 9
      Top = 57
      Width = 40
      Height = 24
      Caption = 'R'
      TabOrder = 1
    end
    object CheckBox_G: TCheckBox
      Left = 9
      Top = 89
      Width = 40
      Height = 24
      Caption = 'G'
      TabOrder = 2
    end
    object CheckBox_B: TCheckBox
      Left = 9
      Top = 121
      Width = 32
      Height = 24
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
  object OpenDialog1: TOpenDialog
  end
end
