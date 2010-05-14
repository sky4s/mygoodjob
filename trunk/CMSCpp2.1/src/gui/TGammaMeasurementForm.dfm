object GammaMeasurementForm: TGammaMeasurementForm
  Left = 252
  Top = 251
  Width = 418
  Height = 468
  Caption = 'Gamma Measurement'
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
  object Copyright: TLabel
    Left = 34
    Top = 333
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
    IsControl = True
  end
  object Panel1: TPanel
    Left = 7
    Top = 13
    Width = 247
    Height = 241
    Caption = 'Panel1'
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 7
      Top = 7
      Width = 234
      Height = 228
      Caption = 'Gamma Measurement (PC Input)'
      TabOrder = 0
      object GroupBox2: TGroupBox
        Left = 7
        Top = 20
        Width = 156
        Height = 98
        Caption = 'Gray Level Option'
        TabOrder = 0
        object Label1: TLabel
          Left = 7
          Top = 20
          Width = 51
          Height = 13
          Caption = 'Start Level'
        end
        object Label2: TLabel
          Left = 7
          Top = 46
          Width = 48
          Height = 13
          Caption = 'End Level'
        end
        object Label3: TLabel
          Left = 7
          Top = 72
          Width = 51
          Height = 13
          Caption = 'Level Step'
        end
        object Edit_StartLevel: TEdit
          Left = 65
          Top = 20
          Width = 85
          Height = 21
          TabOrder = 0
          Text = '255'
        end
        object ComboBox_LevelStep: TComboBox
          Left = 65
          Top = 72
          Width = 85
          Height = 21
          ItemHeight = 13
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
          Left = 65
          Top = 46
          Width = 85
          Height = 21
          TabOrder = 2
          Text = '0'
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 7
    Top = 13
    Width = 247
    Height = 241
    Caption = 'Panel2'
    TabOrder = 1
    Visible = False
    object GroupBox5: TGroupBox
      Left = 7
      Top = 7
      Width = 234
      Height = 228
      Caption = 'Direct Pattern Measurement (T-CON Input)'
      TabOrder = 0
      object GroupBox6: TGroupBox
        Left = 7
        Top = 20
        Width = 137
        Height = 91
        Caption = 'Pattern Type'
        TabOrder = 0
        object GroupBox9: TGroupBox
          Left = 7
          Top = 20
          Width = 124
          Height = 65
          Caption = 'Patterns'
          TabOrder = 0
          object RadioButton_0To256: TRadioButton
            Left = 7
            Top = 20
            Width = 91
            Height = 20
            Caption = '0~256 Pattern'
            Checked = True
            TabOrder = 0
            TabStop = True
          end
          object RadioButton_0To1023: TRadioButton
            Left = 7
            Top = 39
            Width = 91
            Height = 20
            Caption = '0~1023 Pattern'
            TabOrder = 1
          end
        end
      end
      object Table: TGroupBox
        Left = 150
        Top = 20
        Width = 78
        Height = 91
        Caption = 'Table'
        TabOrder = 1
        object RadioButton_10Bit: TRadioButton
          Left = 7
          Top = 20
          Width = 59
          Height = 20
          Caption = '10bit'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton_12Bit: TRadioButton
          Left = 7
          Top = 39
          Width = 65
          Height = 20
          Caption = '12bit'
          TabOrder = 1
        end
        object Button2: TButton
          Left = 7
          Top = 65
          Width = 65
          Height = 20
          Caption = 'Load Table'
          TabOrder = 2
          OnClick = Button2Click
        end
      end
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 7
    Top = 260
    Width = 319
    Height = 72
    TabOrder = 2
    inherited GroupBox_OutputFile: TGroupBox
      Width = 314
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
        Text = 'Measurement'
      end
      inherited Edit_Directory: TEdit
        Left = 91
        Top = 46
        Width = 163
      end
      inherited Button_BrowseDir: TButton
        Left = 260
        Top = 46
        Width = 46
        Height = 20
        OnClick = TOutputFileFrame1Button_BrowseDirClick
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 260
    Top = 13
    Width = 59
    Height = 215
    Caption = 'Color'
    TabOrder = 3
    object CheckBox_W: TCheckBox
      Left = 7
      Top = 20
      Width = 33
      Height = 20
      Caption = 'W'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object CheckBox_R: TCheckBox
      Left = 7
      Top = 46
      Width = 33
      Height = 20
      Caption = 'R'
      TabOrder = 1
    end
    object CheckBox_G: TCheckBox
      Left = 7
      Top = 72
      Width = 33
      Height = 20
      Caption = 'G'
      TabOrder = 2
    end
    object CheckBox_B: TCheckBox
      Left = 7
      Top = 98
      Width = 26
      Height = 20
      Caption = 'B'
      TabOrder = 3
    end
  end
  object Button_Measure: TButton
    Left = 260
    Top = 234
    Width = 59
    Height = 20
    Caption = 'Measure'
    TabOrder = 4
    OnClick = Button_MeasureClick
  end
  object OpenDialog1: TOpenDialog
  end
end
