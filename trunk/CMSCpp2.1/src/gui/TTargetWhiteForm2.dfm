object TargetWhiteForm2: TTargetWhiteForm2
  Left = 300
  Top = 300
  Width = 929
  Height = 553
  Caption = 'TargetWhiteForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 455
    Top = 403
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object PageControl1: TPageControl
    Left = 7
    Top = 7
    Width = 735
    Height = 397
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Target White'
      object GroupBox2: TGroupBox
        Left = 7
        Top = 7
        Width = 195
        Height = 358
        Caption = 'Target Color'
        TabOrder = 0
        object RadioButton_Targetxy: TRadioButton
          Left = 7
          Top = 104
          Width = 136
          Height = 20
          Caption = 'Adjust to Target x,y'
          TabOrder = 1
        end
        object RadioButton_RGBRatio: TRadioButton
          Left = 7
          Top = 33
          Width = 130
          Height = 20
          Caption = 'Adjust by RGB ratio'
          TabOrder = 2
        end
        object Button2: TButton
          Left = 66
          Top = 336
          Width = 65
          Height = 16
          Caption = 'Run'
          TabOrder = 3
          OnClick = Button2Click
        end
        object GroupBox4: TGroupBox
          Left = 20
          Top = 124
          Width = 169
          Height = 124
          Caption = 'Target xy on D-Illuminant Locus'
          TabOrder = 0
          object Label10: TLabel
            Left = 7
            Top = 20
            Width = 5
            Height = 13
            Caption = 'x'
          end
          object Label11: TLabel
            Left = 92
            Top = 20
            Width = 5
            Height = 13
            Caption = 'y'
          end
          object Label2: TLabel
            Left = 85
            Top = 52
            Width = 7
            Height = 13
            Caption = 'K'
          end
          object Label1: TLabel
            Left = 7
            Top = 52
            Width = 14
            Height = 13
            Caption = 'CT'
          end
          object Label5: TLabel
            Left = 7
            Top = 79
            Width = 8
            Height = 13
            Caption = 'u'#39
          end
          object Label6: TLabel
            Left = 91
            Top = 79
            Width = 8
            Height = 13
            Caption = 'v'#39
          end
          object Edit_targetx: TEdit
            Left = 27
            Top = 20
            Width = 58
            Height = 21
            TabOrder = 0
            Text = '0.2788'
            OnChange = Edit_targetxChange
          end
          object Edit_targety: TEdit
            Left = 105
            Top = 20
            Width = 58
            Height = 21
            TabOrder = 1
            Text = '0.2920'
            OnChange = Edit_targetyChange
          end
          object Edit_CT: TEdit
            Left = 26
            Top = 46
            Width = 59
            Height = 21
            TabOrder = 2
            Text = '10000'
            OnChange = Edit_CTChange
          end
          object Edit_up: TEdit
            Left = 26
            Top = 72
            Width = 59
            Height = 21
            Enabled = False
            TabOrder = 3
            Text = '0.1876'
          end
          object Edit_vp: TEdit
            Left = 104
            Top = 72
            Width = 59
            Height = 21
            Enabled = False
            TabOrder = 4
            Text = '0.4419'
          end
          object CheckBox_MoreAccurate: TCheckBox
            Left = 7
            Top = 98
            Width = 98
            Height = 20
            Caption = 'More Accurate'
            TabOrder = 5
            Visible = False
          end
        end
        object RadioButton_MaxRGB: TRadioButton
          Left = 7
          Top = 13
          Width = 117
          Height = 20
          Caption = 'Adjust to Max RGB'
          Checked = True
          TabOrder = 4
          TabStop = True
          OnClick = RadioButton_MaxRGBClick
        end
        object GroupBox1: TGroupBox
          Left = 20
          Top = 52
          Width = 169
          Height = 46
          Caption = 'RGB ratio'
          TabOrder = 5
          object Edit_R: TEdit
            Left = 7
            Top = 20
            Width = 33
            Height = 21
            TabOrder = 0
            Text = '255'
            OnChange = Edit_RChange
          end
          object Edit_G: TEdit
            Left = 46
            Top = 20
            Width = 33
            Height = 21
            TabOrder = 1
            Text = '255'
            OnChange = Edit_GChange
          end
          object Edit_B: TEdit
            Left = 85
            Top = 20
            Width = 33
            Height = 21
            TabOrder = 2
            Text = '255'
            OnChange = Edit_BChange
          end
        end
      end
      object GroupBox5: TGroupBox
        Left = 208
        Top = 7
        Width = 514
        Height = 358
        Caption = 'RGB Pattern'
        TabOrder = 1
        object Label13: TLabel
          Left = 7
          Top = 306
          Width = 8
          Height = 13
          Caption = 'G'
        end
        object Label14: TLabel
          Left = 7
          Top = 332
          Width = 7
          Height = 13
          Caption = 'B'
        end
        object Label12: TLabel
          Left = 7
          Top = 280
          Width = 8
          Height = 13
          Caption = 'R'
        end
        object ScrollBar_R: TScrollBar
          Left = 65
          Top = 286
          Width = 443
          Height = 14
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 0
          OnChange = ScrollBar_RChange
        end
        object ScrollBar_G: TScrollBar
          Left = 65
          Top = 312
          Width = 443
          Height = 14
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 1
          OnChange = ScrollBar_GChange
        end
        object ScrollBar_B: TScrollBar
          Left = 65
          Top = 338
          Width = 443
          Height = 14
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 2
          OnChange = ScrollBar_BChange
        end
        object Panel1: TPanel
          Left = 7
          Top = 13
          Width = 501
          Height = 261
          Color = clWhite
          TabOrder = 3
        end
        object Edit_ScrollR: TEdit
          Left = 20
          Top = 280
          Width = 33
          Height = 21
          Enabled = False
          TabOrder = 4
          Text = '255'
        end
        object Edit_ScrollG: TEdit
          Left = 20
          Top = 306
          Width = 33
          Height = 21
          Enabled = False
          TabOrder = 5
          Text = '255'
        end
        object Edit_ScrollB: TEdit
          Left = 20
          Top = 332
          Width = 33
          Height = 21
          Enabled = False
          TabOrder = 6
          Text = '255'
        end
      end
    end
  end
end
