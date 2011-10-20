object TargetWhiteForm2: TTargetWhiteForm2
  Left = 219
  Top = 138
  Width = 767
  Height = 506
  Caption = 'TargetWhiteForm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 455
    Top = 456
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2012, AU Optronics Corp., All Right Reserved.'
  end
  object PageControl1: TPageControl
    Left = 7
    Top = 7
    Width = 735
    Height = 442
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Target White'
      object GroupBox2: TGroupBox
        Left = 7
        Top = 7
        Width = 195
        Height = 403
        Caption = 'Target Color'
        TabOrder = 0
        object RadioButton_Targetxy: TRadioButton
          Left = 7
          Top = 91
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
        object Button_Run: TButton
          Left = 72
          Top = 378
          Width = 65
          Height = 18
          Caption = 'Run'
          TabOrder = 3
          OnClick = Button_RunClick
        end
        object GroupBox4: TGroupBox
          Left = 20
          Top = 111
          Width = 169
          Height = 117
          Caption = 'Target xy on D-Illuminant Locus'
          TabOrder = 0
          object Label10: TLabel
            Left = 7
            Top = 14
            Width = 5
            Height = 13
            Caption = 'x'
          end
          object Label11: TLabel
            Left = 92
            Top = 14
            Width = 5
            Height = 13
            Caption = 'y'
          end
          object Label2: TLabel
            Left = 85
            Top = 39
            Width = 7
            Height = 13
            Caption = 'K'
          end
          object Label1: TLabel
            Left = 7
            Top = 39
            Width = 14
            Height = 13
            Caption = 'CT'
          end
          object Label5: TLabel
            Left = 7
            Top = 59
            Width = 8
            Height = 13
            Caption = 'u'#39
          end
          object Label6: TLabel
            Left = 91
            Top = 59
            Width = 8
            Height = 13
            Caption = 'v'#39
          end
          object Edit_targetx: TEdit
            Left = 27
            Top = 14
            Width = 58
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 0
            Text = '0.2788'
            OnChange = Edit_targetxChange
          end
          object Edit_targety: TEdit
            Left = 105
            Top = 14
            Width = 58
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 1
            Text = '0.2920'
            OnChange = Edit_targetyChange
          end
          object Edit_CT: TEdit
            Left = 26
            Top = 33
            Width = 59
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 2
            Text = '10000'
            OnChange = Edit_CTChange
          end
          object Edit_up: TEdit
            Left = 26
            Top = 53
            Width = 59
            Height = 21
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 3
            Text = '0.1876'
          end
          object Edit_vp: TEdit
            Left = 104
            Top = 53
            Width = 59
            Height = 21
            Enabled = False
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 4
            Text = '0.4419'
          end
          object CheckBox_MoreAccurate: TCheckBox
            Left = 7
            Top = 94
            Width = 98
            Height = 20
            Caption = 'More Accurate'
            Enabled = False
            TabOrder = 5
            Visible = False
          end
          object CheckBox_AvoidHookTV: TCheckBox
            Left = 7
            Top = 77
            Width = 105
            Height = 21
            Hint = 'Find Target and keep B at maximum B Intensity'
            Caption = 'Avoid Hook(TV)'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 6
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
          Height = 40
          Caption = 'RGB ratio'
          TabOrder = 5
          object Edit_R: TEdit
            Left = 7
            Top = 14
            Width = 33
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 0
            Text = '0'
            OnChange = Edit_RChange
          end
          object Edit_G: TEdit
            Left = 46
            Top = 14
            Width = 33
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 1
            Text = '0'
            OnChange = Edit_GChange
          end
          object Edit_B: TEdit
            Left = 85
            Top = 14
            Width = 33
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 2
            Text = '0'
            OnChange = Edit_BChange
          end
        end
        object GroupBox3: TGroupBox
          Left = 7
          Top = 312
          Width = 182
          Height = 60
          Caption = 'CA-210'
          TabOrder = 6
          object Button_Connect: TButton
            Left = 26
            Top = 12
            Width = 59
            Height = 20
            Caption = 'Connect'
            Enabled = False
            TabOrder = 0
            OnClick = Button_ConnectClick
          end
          object Button_Disconnect: TButton
            Left = 91
            Top = 12
            Width = 72
            Height = 20
            Caption = 'Disconnect'
            TabOrder = 1
            OnClick = Button_DisconnectClick
          end
        end
        object Edit_InverseB: TEdit
          Left = 111
          Top = 235
          Width = 33
          Height = 21
          Hint = 'Click this can auto copy Inverse B to B of RGB Ratio'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 7
          OnClick = Edit_InverseBClick
        end
        object Button_FindInverseB: TButton
          Left = 10
          Top = 235
          Width = 95
          Height = 19
          Hint = 'Find Inverse B Intensity '
          Caption = 'Find Inverse Z of B'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 8
          OnClick = Button_FindInverseBClick
        end
        object GroupBox7: TGroupBox
          Left = 7
          Top = 264
          Width = 182
          Height = 49
          Caption = 'Reference Color'
          TabOrder = 9
          object Label4: TLabel
            Left = 7
            Top = 19
            Width = 5
            Height = 13
            Caption = 'x'
          end
          object Label7: TLabel
            Left = 67
            Top = 19
            Width = 5
            Height = 13
            Caption = 'y'
          end
          object Label8: TLabel
            Left = 119
            Top = 19
            Width = 7
            Height = 13
            Caption = 'Y'
          end
          object Edit_refx: TEdit
            Left = 13
            Top = 19
            Width = 40
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 0
            Text = '0.0000'
          end
          object Edit_refy: TEdit
            Left = 74
            Top = 19
            Width = 39
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 1
            Text = '0.0000'
          end
          object Edit_refLuminance: TEdit
            Left = 132
            Top = 19
            Width = 39
            Height = 21
            ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
            TabOrder = 2
            Text = '0.0'
          end
        end
        object Button_ContinueMeasure: TButton
          Left = 48
          Top = 346
          Width = 113
          Height = 20
          Caption = 'Continue Measure'
          TabOrder = 10
          OnClick = Button_ContinueMeasureClick
        end
      end
      object GroupBox5: TGroupBox
        Left = 208
        Top = 7
        Width = 514
        Height = 403
        Caption = 'RGB Pattern'
        TabOrder = 1
        object Label13: TLabel
          Left = 7
          Top = 332
          Width = 8
          Height = 13
          Caption = 'G'
        end
        object Label14: TLabel
          Left = 7
          Top = 358
          Width = 7
          Height = 13
          Caption = 'B'
        end
        object Label12: TLabel
          Left = 7
          Top = 306
          Width = 8
          Height = 13
          Caption = 'R'
        end
        object ScrollBar_R: TScrollBar
          Left = 59
          Top = 312
          Width = 449
          Height = 14
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 0
          OnChange = ScrollBar_RChange
        end
        object ScrollBar_G: TScrollBar
          Left = 59
          Top = 338
          Width = 449
          Height = 14
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 1
          OnChange = ScrollBar_GChange
        end
        object ScrollBar_B: TScrollBar
          Left = 59
          Top = 364
          Width = 449
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
          Height = 287
          Color = clWhite
          TabOrder = 3
        end
        object Edit_ScrollR: TEdit
          Left = 20
          Top = 306
          Width = 33
          Height = 21
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 4
          Text = '255'
        end
        object Edit_ScrollG: TEdit
          Left = 20
          Top = 332
          Width = 33
          Height = 21
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 5
          Text = '255'
        end
        object Edit_ScrollB: TEdit
          Left = 20
          Top = 358
          Width = 33
          Height = 21
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 6
          Text = '255'
        end
        object CheckBox_Lock: TCheckBox
          Left = 7
          Top = 377
          Width = 78
          Height = 20
          Caption = 'RGB Lock'
          TabOrder = 7
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Max Matrix'
      ImageIndex = 1
      object GroupBox6: TGroupBox
        Left = 7
        Top = 7
        Width = 228
        Height = 169
        Caption = 'Target Color'
        TabOrder = 0
        object Label17: TLabel
          Left = 7
          Top = 111
          Width = 11
          Height = 13
          Caption = 'W'
        end
        object Label20: TLabel
          Left = 7
          Top = 85
          Width = 7
          Height = 13
          Caption = 'B'
        end
        object Label18: TLabel
          Left = 7
          Top = 59
          Width = 8
          Height = 13
          Caption = 'G'
        end
        object Label19: TLabel
          Left = 7
          Top = 33
          Width = 8
          Height = 13
          Caption = 'R'
        end
        object Label15: TLabel
          Left = 117
          Top = 14
          Width = 7
          Height = 13
          Caption = 'Y'
        end
        object Label9: TLabel
          Left = 53
          Top = 14
          Width = 7
          Height = 13
          Caption = 'X'
        end
        object Label16: TLabel
          Left = 182
          Top = 14
          Width = 7
          Height = 13
          Caption = 'Z'
        end
        object Edit_RZ: TEdit
          Left = 156
          Top = 33
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 0
          Text = '0'
        end
        object Edit_GZ: TEdit
          Left = 156
          Top = 59
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 1
          Text = '0'
        end
        object Edit_BZ: TEdit
          Left = 156
          Top = 85
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 2
          Text = '0'
          OnChange = Edit_BZChange
        end
        object Edit_WZ: TEdit
          Left = 156
          Top = 111
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 3
          Text = '0'
        end
        object Edit_WY: TEdit
          Left = 92
          Top = 111
          Width = 58
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 4
          Text = '0'
        end
        object Edit_BY: TEdit
          Left = 92
          Top = 85
          Width = 58
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 5
          Text = '0'
        end
        object Edit_GY: TEdit
          Left = 92
          Top = 59
          Width = 58
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 6
          Text = '0'
        end
        object Edit_RY: TEdit
          Left = 92
          Top = 33
          Width = 58
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 7
          Text = '0'
        end
        object Edit_RX: TEdit
          Left = 26
          Top = 33
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 8
          Text = '0'
        end
        object Edit_GX: TEdit
          Left = 26
          Top = 59
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 9
          Text = '0'
        end
        object Edit_BX: TEdit
          Left = 26
          Top = 85
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 10
          Text = '0'
        end
        object Edit_WX: TEdit
          Left = 26
          Top = 111
          Width = 59
          Height = 21
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 11
          Text = '0'
        end
        object Button_setMaxMatrix: TButton
          Left = 92
          Top = 138
          Width = 58
          Height = 19
          Caption = 'Set'
          Enabled = False
          TabOrder = 12
          OnClick = Button_setMaxMatrixClick
        end
      end
    end
  end
end
