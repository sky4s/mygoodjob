object TargetWhiteForm2: TTargetWhiteForm2
  Left = 370
  Top = 233
  Width = 922
  Height = 531
  Caption = 'TargetWhiteForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 905
    Height = 489
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Target White'
      object GroupBox2: TGroupBox
        Left = 8
        Top = 9
        Width = 241
        Height = 440
        Caption = 'Target Color'
        TabOrder = 0
        object RadioButton_Targetxy: TRadioButton
          Left = 8
          Top = 128
          Width = 168
          Height = 25
          Caption = 'Adjust to Target x,y'
          TabOrder = 1
        end
        object RadioButton_RGBRatio: TRadioButton
          Left = 8
          Top = 41
          Width = 160
          Height = 24
          Caption = 'Adjust by RGB ratio'
          TabOrder = 2
        end
        object Button2: TButton
          Left = 81
          Top = 408
          Width = 80
          Height = 25
          Caption = 'Run'
          TabOrder = 3
          OnClick = Button2Click
        end
        object GroupBox4: TGroupBox
          Left = 24
          Top = 153
          Width = 209
          Height = 120
          Caption = 'Target xy on D-Locus'
          TabOrder = 0
          object Label10: TLabel
            Left = 9
            Top = 25
            Width = 6
            Height = 16
            Caption = 'x'
          end
          object Label11: TLabel
            Left = 113
            Top = 25
            Width = 7
            Height = 16
            Caption = 'y'
          end
          object Label2: TLabel
            Left = 105
            Top = 64
            Width = 8
            Height = 16
            Caption = 'K'
          end
          object Label1: TLabel
            Left = 9
            Top = 64
            Width = 18
            Height = 16
            Caption = 'CT'
          end
          object Label5: TLabel
            Left = 8
            Top = 97
            Width = 10
            Height = 16
            Caption = 'u'#39
          end
          object Label6: TLabel
            Left = 112
            Top = 97
            Width = 10
            Height = 16
            Caption = 'v'#39
          end
          object Edit_targetx: TEdit
            Left = 33
            Top = 25
            Width = 72
            Height = 24
            TabOrder = 0
            Text = '0.2788'
            OnChange = Edit_targetxChange
          end
          object Edit_targety: TEdit
            Left = 129
            Top = 25
            Width = 72
            Height = 24
            TabOrder = 1
            Text = '0.2920'
            OnChange = Edit_targetyChange
          end
          object Edit_CT: TEdit
            Left = 32
            Top = 57
            Width = 73
            Height = 24
            TabOrder = 2
            Text = '10000'
            OnChange = Edit_CTChange
          end
          object Edit_up: TEdit
            Left = 32
            Top = 89
            Width = 73
            Height = 24
            Enabled = False
            TabOrder = 3
            Text = '0.1876'
          end
          object Edit_vp: TEdit
            Left = 128
            Top = 89
            Width = 73
            Height = 24
            Enabled = False
            TabOrder = 4
            Text = '0.4419'
          end
        end
        object RadioButton_MaxRGB: TRadioButton
          Left = 8
          Top = 16
          Width = 145
          Height = 25
          Caption = 'Adjust to Max RGB'
          Checked = True
          TabOrder = 4
          TabStop = True
          OnClick = RadioButton_MaxRGBClick
        end
        object GroupBox1: TGroupBox
          Left = 24
          Top = 64
          Width = 209
          Height = 57
          Caption = 'RGB ratio'
          TabOrder = 5
          object Edit_R: TEdit
            Left = 9
            Top = 25
            Width = 40
            Height = 24
            TabOrder = 0
            Text = '255'
          end
          object Edit_G: TEdit
            Left = 57
            Top = 25
            Width = 40
            Height = 24
            TabOrder = 1
            Text = '255'
          end
          object Edit_B: TEdit
            Left = 105
            Top = 25
            Width = 40
            Height = 24
            TabOrder = 2
            Text = '255'
          end
        end
      end
      object GroupBox5: TGroupBox
        Left = 256
        Top = 9
        Width = 633
        Height = 440
        Caption = 'RGB Pattern'
        TabOrder = 1
        object Label13: TLabel
          Left = 8
          Top = 377
          Width = 10
          Height = 16
          Caption = 'G'
        end
        object Label14: TLabel
          Left = 8
          Top = 409
          Width = 9
          Height = 16
          Caption = 'B'
        end
        object Label12: TLabel
          Left = 8
          Top = 345
          Width = 10
          Height = 16
          Caption = 'R'
        end
        object ScrollBar_R: TScrollBar
          Left = 80
          Top = 352
          Width = 545
          Height = 17
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 0
          OnChange = ScrollBar_RChange
        end
        object ScrollBar_G: TScrollBar
          Left = 80
          Top = 384
          Width = 545
          Height = 17
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 1
          OnChange = ScrollBar_GChange
        end
        object ScrollBar_B: TScrollBar
          Left = 80
          Top = 416
          Width = 545
          Height = 17
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 2
          OnChange = ScrollBar_BChange
        end
        object Panel1: TPanel
          Left = 9
          Top = 16
          Width = 616
          Height = 321
          Color = clWhite
          TabOrder = 3
        end
        object Edit_ScrollR: TEdit
          Left = 25
          Top = 345
          Width = 40
          Height = 24
          Enabled = False
          TabOrder = 4
          Text = '255'
        end
        object Edit_ScrollG: TEdit
          Left = 25
          Top = 377
          Width = 40
          Height = 24
          Enabled = False
          TabOrder = 5
          Text = '255'
        end
        object Edit_ScrollB: TEdit
          Left = 25
          Top = 409
          Width = 40
          Height = 24
          Enabled = False
          TabOrder = 6
          Text = '255'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'CA-210 Setting'
      ImageIndex = 1
      object GroupBox3: TGroupBox
        Left = 8
        Top = 9
        Width = 209
        Height = 112
        Caption = 'CH Setting'
        TabOrder = 0
        object Label7: TLabel
          Left = 9
          Top = 25
          Width = 65
          Height = 16
          Caption = 'Source CH'
        end
        object Label8: TLabel
          Left = 9
          Top = 57
          Width = 75
          Height = 16
          Caption = 'TargetW CH'
        end
        object Label9: TLabel
          Left = 9
          Top = 89
          Width = 69
          Height = 16
          Caption = 'TargetW ID'
        end
        object Edit_SourceCH: TEdit
          Left = 97
          Top = 16
          Width = 48
          Height = 24
          Enabled = False
          TabOrder = 0
          Text = '0'
        end
        object Edit_TargetCH: TEdit
          Left = 97
          Top = 48
          Width = 48
          Height = 24
          TabOrder = 1
          Text = '2'
        end
        object Edit_TargetID: TEdit
          Left = 97
          Top = 80
          Width = 104
          Height = 24
          TabOrder = 2
          Text = ' '
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 64
    Top = 16
  end
end
