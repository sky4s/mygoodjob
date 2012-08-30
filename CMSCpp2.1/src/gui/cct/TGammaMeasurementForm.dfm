object GammaMeasurementForm: TGammaMeasurementForm
  Left = 336
  Top = 226
  Width = 406
  Height = 407
  Caption = 'Gamma Measurement'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnKeyPress = FormKeyPress
  OnMouseMove = FormMouseMove
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Copyright: TLabel
    Left = 34
    Top = 357
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2012, AU Optronics Corp., All Right Reserved.'
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
      object CheckBox_FlickerFMA: TCheckBox
        Left = 7
        Top = 124
        Width = 78
        Height = 13
        Caption = 'FlickerFMA'
        TabOrder = 1
        Visible = False
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
      object Table: TGroupBox
        Left = 7
        Top = 14
        Width = 221
        Height = 139
        Caption = 'Table'
        TabOrder = 0
        object Label4: TLabel
          Left = 8
          Top = 64
          Width = 85
          Height = 13
          Caption = 'Load Table Count'
        end
        object Label5: TLabel
          Left = 8
          Top = 88
          Width = 95
          Height = 13
          Caption = 'Measure Start Level'
        end
        object Label6: TLabel
          Left = 8
          Top = 112
          Width = 92
          Height = 13
          Caption = 'Measure End Level'
        end
        object RadioButton_10Bit: TRadioButton
          Left = 7
          Top = 14
          Width = 59
          Height = 19
          Caption = '10bit'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object RadioButton_12Bit: TRadioButton
          Left = 59
          Top = 14
          Width = 65
          Height = 20
          Caption = '12bit'
          TabOrder = 1
        end
        object Button2: TButton
          Left = 7
          Top = 40
          Width = 74
          Height = 19
          Caption = 'Load Table'
          TabOrder = 2
          OnClick = Button2Click
        end
        object CheckBox_Loaded: TCheckBox
          Left = 88
          Top = 39
          Width = 65
          Height = 20
          Caption = 'Loaded'
          Enabled = False
          TabOrder = 3
          OnClick = CheckBox_LoadedClick
        end
        object Edit_StartLevelT: TEdit
          Left = 112
          Top = 88
          Width = 65
          Height = 21
          TabOrder = 4
          Text = '0'
        end
        object Edit_EndLevelT: TEdit
          Left = 112
          Top = 112
          Width = 65
          Height = 21
          TabOrder = 5
          Text = '0'
        end
        object Edit_Count: TEdit
          Left = 112
          Top = 64
          Width = 65
          Height = 21
          Enabled = False
          TabOrder = 6
          Text = '0'
        end
      end
    end
  end
  inline TOutputFileFrame1: TOutputFileFrame
    Left = 7
    Top = 260
    Width = 386
    Height = 93
    TabOrder = 2
    inherited GroupBox_OutputFile: TGroupBox
      Width = 378
      Height = 74
      OnClick = Button_MeasureClick
      inherited Label5: TLabel
        Left = 7
        Top = 20
      end
      inherited Label6: TLabel
        Left = 7
        Top = 46
      end
      inherited Label_Warning: TLabel
        Left = 96
        Top = 40
      end
      inherited Edit_Prefix: TEdit
        Left = 91
        Top = 20
        Width = 278
        Text = 'Measurement'
      end
      inherited Edit_Directory: TEdit
        Left = 91
        Top = 46
        Width = 230
      end
      inherited Button_BrowseDir: TButton
        Left = 324
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
    Width = 125
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
    object Panel3: TPanel
      Left = 8
      Top = 40
      Width = 113
      Height = 113
      TabOrder = 1
      object CheckBox_B: TCheckBox
        Left = 7
        Top = 69
        Width = 26
        Height = 20
        Caption = 'B'
        TabOrder = 0
      end
      object CheckBox_R: TCheckBox
        Left = 7
        Top = 21
        Width = 33
        Height = 20
        Caption = 'R'
        TabOrder = 1
      end
      object CheckBox_G: TCheckBox
        Left = 7
        Top = 45
        Width = 33
        Height = 20
        Caption = 'G'
        TabOrder = 2
      end
      object GroupBox4: TGroupBox
        Left = 40
        Top = 8
        Width = 65
        Height = 97
        Caption = 'Backgroud'
        TabOrder = 3
        object Edit_BackgroundR: TEdit
          Left = 8
          Top = 16
          Width = 49
          Height = 21
          TabOrder = 0
          Text = '0'
        end
        object Edit_BackgroundG: TEdit
          Left = 8
          Top = 40
          Width = 49
          Height = 21
          TabOrder = 1
          Text = '0'
        end
        object Edit_BackgroundB: TEdit
          Left = 8
          Top = 64
          Width = 49
          Height = 21
          TabOrder = 2
          Text = '0'
        end
      end
    end
  end
  object Button_Measure: TButton
    Left = 324
    Top = 234
    Width = 59
    Height = 20
    Caption = 'Measure'
    TabOrder = 4
    OnClick = Button_MeasureClick
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 336
    Width = 225
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 5
    Visible = False
  end
  object OpenDialog1: TOpenDialog
  end
end
