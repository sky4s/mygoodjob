object TargetWhiteForm2: TTargetWhiteForm2
  Left = 398
  Top = 287
  Width = 898
  Height = 642
  Caption = 'Target White'
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
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 607
    Top = 576
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2012, AU Optronics Corp., All Right Reserved.'
  end
  object PageControl1: TPageControl
    Left = 7
    Top = 7
    Width = 874
    Height = 562
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    OnResize = PageControl1Resize
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
          Top = 380
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
          Height = 106
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
            Top = 78
            Width = 98
            Height = 20
            Caption = 'More Accurate'
            Enabled = False
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
          Top = 288
          Width = 182
          Height = 41
          Caption = 'CA-210'
          TabOrder = 6
          object Button_Measure: TButton
            Left = 104
            Top = 14
            Width = 65
            Height = 17
            Caption = 'Measure'
            TabOrder = 0
            OnClick = Button_MeasureClick
          end
          object Button_ConnectToggle: TButton
            Left = 8
            Top = 14
            Width = 89
            Height = 17
            Caption = 'Connect'
            TabOrder = 1
            OnClick = Button_ConnectToggleClick
          end
        end
        object GroupBox7: TGroupBox
          Left = 7
          Top = 328
          Width = 182
          Height = 49
          Caption = 'Reference Color'
          TabOrder = 7
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
        object Edit_InverseIntensityofB: TEdit
          Left = 95
          Top = 224
          Width = 33
          Height = 21
          Hint = 'Click this can auto copy Inverse B to B of RGB Ratio'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 8
          OnKeyPress = Edit_InverseIntensityofBKeyPress
        end
        object Button_FindInverseIntensity: TButton
          Left = 18
          Top = 224
          Width = 71
          Height = 17
          Hint = 'Find Inverse B Intensity '
          Caption = 'De-Hook'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 9
          OnClick = Button_FindInverseIntensityClick
        end
        object Button_Connect: TButton
          Left = 128
          Top = 260
          Width = 59
          Height = 20
          Caption = 'Connect'
          Enabled = False
          TabOrder = 10
          Visible = False
          OnClick = Button_ConnectClick
        end
        object Button_Disconnect: TButton
          Left = 123
          Top = 276
          Width = 72
          Height = 20
          Caption = 'Disconnect'
          TabOrder = 11
          Visible = False
          OnClick = Button_DisconnectClick
        end
      end
      object GroupBox5: TGroupBox
        Left = 208
        Top = 416
        Width = 514
        Height = 113
        Caption = 'RGB Pattern'
        TabOrder = 1
        object Label13: TLabel
          Left = 7
          Top = 44
          Width = 8
          Height = 13
          Caption = 'G'
        end
        object Label14: TLabel
          Left = 7
          Top = 70
          Width = 7
          Height = 13
          Caption = 'B'
        end
        object Label12: TLabel
          Left = 7
          Top = 18
          Width = 8
          Height = 13
          Caption = 'R'
        end
        object ScrollBar_R: TScrollBar
          Left = 59
          Top = 24
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
          Top = 50
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
          Top = 76
          Width = 449
          Height = 14
          LargeChange = 10
          Max = 255
          PageSize = 0
          Position = 255
          TabOrder = 2
          OnChange = ScrollBar_BChange
        end
        object Edit_ScrollR: TEdit
          Left = 20
          Top = 18
          Width = 33
          Height = 21
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 3
          Text = '255'
        end
        object Edit_ScrollG: TEdit
          Left = 20
          Top = 44
          Width = 33
          Height = 21
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 4
          Text = '255'
        end
        object Edit_ScrollB: TEdit
          Left = 20
          Top = 70
          Width = 33
          Height = 21
          Enabled = False
          ImeName = #26085#25991#36664#20837#31995#32113' (MS-IME2002)'
          TabOrder = 5
          Text = '255'
        end
        object CheckBox_Lock: TCheckBox
          Left = 7
          Top = 91
          Width = 78
          Height = 18
          Caption = 'RGB Lock'
          TabOrder = 6
        end
      end
      object Panel1: TPanel
        Left = 207
        Top = 13
        Width = 650
        Height = 396
        Color = clWhite
        TabOrder = 2
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
  object StatusBar1: TStatusBar
    Left = 0
    Top = 596
    Width = 890
    Height = 17
    Color = clWhite
    Panels = <
      item
        Text = 'Target White: N/A'
        Width = 200
      end
      item
        Text = 'De-Hook: N/A'
        Width = 100
      end
      item
        Text = 'DG:'
        Width = 200
      end>
    SimplePanel = False
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 576
    Width = 225
    Height = 17
    Min = 0
    Max = 100
    TabOrder = 1
    Visible = False
  end
end
