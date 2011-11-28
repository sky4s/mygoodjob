object CMForm1: TCMForm1
  Left = 360
  Top = 155
  Width = 739
  Height = 455
  Caption = 'Color Matrix'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox19: TGroupBox
    Left = 11
    Top = 12
    Width = 694
    Height = 389
    TabOrder = 0
    object Label4: TLabel
      Left = 24
      Top = 80
      Width = 32
      Height = 13
      Caption = 'Label4'
    end
    object CheckBox1: TCheckBox
      Left = 24
      Top = 32
      Width = 129
      Height = 17
      Caption = 'CheckBox1'
      TabOrder = 1
    end
    object CheckBox2: TCheckBox
      Left = 152
      Top = 32
      Width = 129
      Height = 17
      Caption = 'CheckBox2'
      TabOrder = 2
    end
    object CheckBox3: TCheckBox
      Left = 288
      Top = 32
      Width = 129
      Height = 17
      Caption = 'CheckBox3'
      TabOrder = 3
    end
    object ComboBox1: TComboBox
      Left = 72
      Top = 80
      Width = 81
      Height = 21
      ItemHeight = 13
      TabOrder = 4
    end
    object Btn_CM_reload: TBitBtn
      Left = 32
      Top = 336
      Width = 73
      Height = 25
      Caption = '&Reload'
      TabOrder = 5
      OnClick = Btn_CM_reloadClick
      Kind = bkYes
    end
    object TS_CM: TPageControl
      Left = 16
      Top = 128
      Width = 665
      Height = 185
      ActivePage = th_CM1
      TabIndex = 0
      TabOrder = 0
      TabWidth = 70
      OnChange = TS_CMChange
      object th_CM1: TTabSheet
        Caption = 'CM1'
        DesignSize = (
          657
          157)
        object CM1_hint: TLabel
          Left = 224
          Top = 136
          Width = 168
          Height = 13
          Anchors = [akLeft, akTop, akRight, akBottom]
          Caption = 'Renew CM to Memory, Press Enter '
          Color = clMoneyGreen
          ParentColor = False
          Visible = False
        end
        object Label1: TLabel
          Left = 456
          Top = 80
          Width = 28
          Height = 13
          Caption = 'Offset'
        end
        object StaticText7: TStaticText
          Left = 8
          Top = 56
          Width = 13
          Height = 17
          Caption = 'R'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 0
        end
        object StaticText8: TStaticText
          Left = 8
          Top = 80
          Width = 13
          Height = 17
          Caption = 'G'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 1
        end
        object StaticText9: TStaticText
          Left = 8
          Top = 104
          Width = 12
          Height = 17
          Caption = 'B'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 2
        end
        object CM1_11: TEdit
          Left = 24
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 3
          Text = '1'
          OnKeyPress = CM1_keyPress
        end
        object CM1_12: TEdit
          Left = 64
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 4
          Text = '0'
          OnKeyPress = CM1_keyPress
        end
        object CM1_13: TEdit
          Left = 104
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 5
          Text = '0'
          OnKeyPress = CM1_keyPress
        end
        object CM1_21: TEdit
          Left = 24
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 6
          Text = '0'
          OnKeyPress = CM1_keyPress
        end
        object CM1_22: TEdit
          Left = 64
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 7
          Text = '1'
          OnKeyPress = CM1_keyPress
        end
        object CM1_23: TEdit
          Left = 104
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 8
          Text = '0'
          OnKeyPress = CM1_keyPress
        end
        object CM1_31: TEdit
          Left = 24
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 9
          Text = '0'
          OnKeyPress = CM1_keyPress
        end
        object CM1_32: TEdit
          Left = 64
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 10
          Text = '0'
          OnKeyPress = CM1_keyPress
        end
        object CM1_33: TEdit
          Left = 104
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 11
          Text = '1'
          OnKeyPress = CM1_keyPress
        end
        object btn_CM1_Write: TButton
          Left = 104
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Write'
          ParentShowHint = False
          ShowHint = False
          TabOrder = 12
          OnClick = btn_CM1_WriteClick
        end
        object StaticText12: TStaticText
          Left = 168
          Top = 56
          Width = 41
          Height = 17
          Caption = 'R gain'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 13
        end
        object StaticText13: TStaticText
          Left = 168
          Top = 80
          Width = 41
          Height = 17
          Caption = 'G gain'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 14
        end
        object StaticText14: TStaticText
          Left = 168
          Top = 104
          Width = 40
          Height = 17
          Caption = 'B gain'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 15
        end
        object bn_CM1Save: TButton
          Left = 8
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Save'
          TabOrder = 16
          OnClick = bn_CM1SaveClick
        end
        object bn_CM1Load: TButton
          Left = 56
          Top = 136
          Width = 41
          Height = 17
          Hint = 'Load CM1 Value from File'
          Caption = 'Load'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 17
          OnClick = bn_CM1LoadClick
        end
        object cb_CM1_W255: TCheckBox
          Left = 448
          Top = 24
          Width = 97
          Height = 25
          Caption = 'W255 fix'
          TabOrder = 18
        end
        object rg_CM1_mode: TRadioGroup
          Left = 8
          Top = 8
          Width = 401
          Height = 41
          Caption = 'Adjust Mode'
          Columns = 3
          Items.Strings = (
            'Manual'
            'White Balance'
            'Vivid Mode')
          TabOrder = 19
          OnClick = rg_CM1_modeClick
        end
        object sb_cm11: TScrollBar
          Left = 216
          Top = 56
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 20
          OnChange = sb_cm11Change
        end
        object sb_cm12: TScrollBar
          Left = 216
          Top = 80
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 21
          OnChange = sb_cm12Change
        end
        object sb_cm13: TScrollBar
          Left = 216
          Top = 104
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 22
          OnChange = sb_cm13Change
        end
        object st_ofs1: TStaticText
          Left = 616
          Top = 80
          Width = 38
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'st_ofs1'
          TabOrder = 23
        end
        object st_CM11gain: TStaticText
          Left = 392
          Top = 56
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 24
        end
        object st_CM12gain: TStaticText
          Left = 392
          Top = 80
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 25
        end
        object st_CM13gain: TStaticText
          Left = 392
          Top = 104
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 26
        end
        object btn_CM1_Read: TButton
          Left = 152
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Read'
          TabOrder = 27
          OnClick = btn_CM1_ReadClick
        end
        object sb_ofs1: TScrollBar
          Left = 488
          Top = 80
          Width = 121
          Height = 17
          Max = 1023
          PageSize = 0
          Position = 512
          TabOrder = 28
          OnChange = sb_ofs1Change
        end
      end
      object th_CM2: TTabSheet
        Caption = 'CM2'
        ImageIndex = 1
        DesignSize = (
          657
          157)
        object CM2_hint: TLabel
          Left = 208
          Top = 136
          Width = 168
          Height = 13
          Anchors = [akLeft, akTop, akRight, akBottom]
          Caption = 'Renew CM to Memory, Press Enter '
          Color = clMoneyGreen
          ParentColor = False
          Visible = False
        end
        object Label2: TLabel
          Left = 456
          Top = 80
          Width = 28
          Height = 13
          Caption = 'Offset'
        end
        object btn_CM2_Write: TButton
          Left = 104
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Write'
          TabOrder = 0
          OnClick = btn_CM2_WriteClick
        end
        object StaticText1: TStaticText
          Left = 8
          Top = 56
          Width = 13
          Height = 17
          Caption = 'R'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 1
        end
        object StaticText4: TStaticText
          Left = 8
          Top = 80
          Width = 13
          Height = 17
          Caption = 'G'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 2
        end
        object StaticText5: TStaticText
          Left = 8
          Top = 104
          Width = 12
          Height = 17
          Caption = 'B'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 3
        end
        object CM2_11: TEdit
          Left = 24
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 4
          Text = '1'
          OnKeyPress = CM2_keyPress
        end
        object CM2_12: TEdit
          Left = 64
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 5
          Text = '0'
          OnKeyPress = CM2_keyPress
        end
        object CM2_13: TEdit
          Left = 104
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 6
          Text = '0'
          OnKeyPress = CM2_keyPress
        end
        object CM2_21: TEdit
          Left = 24
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 7
          Text = '0'
          OnKeyPress = CM2_keyPress
        end
        object CM2_22: TEdit
          Left = 64
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 8
          Text = '1'
          OnKeyPress = CM2_keyPress
        end
        object CM2_23: TEdit
          Left = 104
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 9
          Text = '0'
          OnKeyPress = CM2_keyPress
        end
        object CM2_31: TEdit
          Left = 24
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 10
          Text = '0'
          OnKeyPress = CM2_keyPress
        end
        object CM2_32: TEdit
          Left = 64
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 11
          Text = '0'
          OnKeyPress = CM2_keyPress
        end
        object CM2_33: TEdit
          Left = 104
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 12
          Text = '1'
          OnKeyPress = CM2_keyPress
        end
        object StaticText21: TStaticText
          Left = 168
          Top = 56
          Width = 41
          Height = 17
          Caption = 'R gain'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 13
        end
        object StaticText22: TStaticText
          Left = 168
          Top = 80
          Width = 41
          Height = 17
          Caption = 'G gain'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 14
        end
        object StaticText23: TStaticText
          Left = 168
          Top = 104
          Width = 40
          Height = 17
          Caption = 'B gain'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 15
        end
        object bn_CM2Save: TButton
          Left = 8
          Top = 136
          Width = 41
          Height = 17
          HelpType = htKeyword
          HelpKeyword = '3'
          Caption = 'Save'
          TabOrder = 16
          OnClick = bn_CM2SaveClick
        end
        object bn_CM2Load: TButton
          Left = 56
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Load'
          TabOrder = 17
          OnClick = bn_CM2LoadClick
        end
        object cb_CM2_W255: TCheckBox
          Left = 448
          Top = 24
          Width = 97
          Height = 25
          Caption = 'W255 fix'
          TabOrder = 18
        end
        object rg_CM2_mode: TRadioGroup
          Left = 8
          Top = 8
          Width = 401
          Height = 41
          Caption = 'Adjust Mode'
          Columns = 3
          Items.Strings = (
            'Manual'
            'White Balance'
            'Vivid Mode')
          TabOrder = 19
          OnClick = rg_CM2_modeClick
        end
        object sb_ofs2: TScrollBar
          Left = 488
          Top = 80
          Width = 121
          Height = 17
          Max = 1023
          PageSize = 0
          Position = 512
          TabOrder = 20
          OnChange = sb_ofs2Change
        end
        object st_ofs2: TStaticText
          Left = 616
          Top = 80
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText2'
          TabOrder = 21
        end
        object sb_cm21: TScrollBar
          Left = 216
          Top = 56
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 22
          OnChange = sb_cm21Change
        end
        object sb_cm22: TScrollBar
          Left = 216
          Top = 80
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 23
          OnChange = sb_cm22Change
        end
        object sb_cm23: TScrollBar
          Left = 216
          Top = 104
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 24
          OnChange = sb_cm23Change
        end
        object st_CM21gain: TStaticText
          Left = 392
          Top = 56
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 25
        end
        object st_CM22gain: TStaticText
          Left = 392
          Top = 80
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 26
        end
        object st_CM23gain: TStaticText
          Left = 392
          Top = 104
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 27
        end
        object btn_CM2_Read: TButton
          Left = 152
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Read'
          TabOrder = 28
          OnClick = btn_CM2_ReadClick
        end
      end
      object th_CM3: TTabSheet
        Caption = 'CM3'
        ImageIndex = 2
        DesignSize = (
          657
          157)
        object CM3_hint: TLabel
          Left = 208
          Top = 136
          Width = 168
          Height = 13
          Anchors = [akLeft, akTop, akRight, akBottom]
          Caption = 'Renew CM to Memory, Press Enter '
          Color = clMoneyGreen
          ParentColor = False
          Visible = False
        end
        object Label3: TLabel
          Left = 456
          Top = 80
          Width = 28
          Height = 13
          Caption = 'Offset'
        end
        object btn_CM3_Write: TButton
          Left = 104
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Write'
          TabOrder = 0
          OnClick = btn_CM3_WriteClick
        end
        object StaticText6: TStaticText
          Left = 8
          Top = 56
          Width = 13
          Height = 17
          Caption = 'R'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 1
        end
        object StaticText10: TStaticText
          Left = 8
          Top = 80
          Width = 13
          Height = 17
          Caption = 'G'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 2
        end
        object StaticText11: TStaticText
          Left = 8
          Top = 104
          Width = 12
          Height = 17
          Caption = 'B'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 3
        end
        object CM3_11: TEdit
          Left = 24
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 4
          Text = '1'
          OnKeyPress = CM3_keyPress
        end
        object CM3_12: TEdit
          Left = 64
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 5
          Text = '0'
          OnKeyPress = CM3_keyPress
        end
        object CM3_13: TEdit
          Left = 104
          Top = 56
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 6
          Text = '0'
          OnKeyPress = CM3_keyPress
        end
        object CM3_21: TEdit
          Left = 24
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 7
          Text = '0'
          OnKeyPress = CM3_keyPress
        end
        object CM3_22: TEdit
          Left = 64
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 8
          Text = '1'
          OnKeyPress = CM3_keyPress
        end
        object CM3_23: TEdit
          Left = 104
          Top = 80
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 9
          Text = '0'
          OnKeyPress = CM3_keyPress
        end
        object CM3_31: TEdit
          Left = 24
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 10
          Text = '0'
          OnKeyPress = CM3_keyPress
        end
        object CM3_32: TEdit
          Left = 64
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 11
          Text = '0'
          OnKeyPress = CM3_keyPress
        end
        object CM3_33: TEdit
          Left = 104
          Top = 104
          Width = 41
          Height = 21
          Color = clWhite
          TabOrder = 12
          Text = '1'
          OnKeyPress = CM3_keyPress
        end
        object StaticText24: TStaticText
          Left = 168
          Top = 56
          Width = 41
          Height = 17
          Caption = 'R gain'
          Color = clRed
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindow
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 13
        end
        object StaticText25: TStaticText
          Left = 168
          Top = 80
          Width = 41
          Height = 17
          Caption = 'G gain'
          Color = clGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 14
        end
        object StaticText26: TStaticText
          Left = 168
          Top = 104
          Width = 40
          Height = 17
          Caption = 'B gain'
          Color = clBlue
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWhite
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 15
        end
        object bn_CM3Save: TButton
          Left = 8
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Save'
          TabOrder = 16
          OnClick = bn_CM3SaveClick
        end
        object bn_CM3Load: TButton
          Left = 56
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Load'
          TabOrder = 17
          OnClick = bn_CM3LoadClick
        end
        object cb_CM3_W255: TCheckBox
          Left = 448
          Top = 24
          Width = 97
          Height = 25
          Caption = 'W255 fix'
          TabOrder = 18
        end
        object rg_CM3_mode: TRadioGroup
          Left = 8
          Top = 8
          Width = 401
          Height = 41
          Caption = 'Adjust Mode'
          Columns = 3
          Items.Strings = (
            'Manual'
            'White Balance'
            'Vivid Mode')
          TabOrder = 19
          OnClick = rg_CM3_modeClick
        end
        object sb_ofs3: TScrollBar
          Left = 488
          Top = 80
          Width = 121
          Height = 17
          Max = 1023
          PageSize = 0
          Position = 512
          TabOrder = 20
          OnChange = sb_ofs3Change
        end
        object st_ofs3: TStaticText
          Left = 616
          Top = 80
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText2'
          TabOrder = 21
        end
        object sb_cm31: TScrollBar
          Left = 216
          Top = 56
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 22
          OnChange = sb_cm31Change
        end
        object sb_cm32: TScrollBar
          Left = 216
          Top = 80
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 23
          OnChange = sb_cm32Change
        end
        object sb_cm33: TScrollBar
          Left = 216
          Top = 104
          Width = 169
          Height = 17
          Max = 200
          PageSize = 0
          Position = 100
          TabOrder = 24
          OnChange = sb_cm33Change
        end
        object st_CM31gain: TStaticText
          Left = 392
          Top = 56
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 25
        end
        object st_CM32gain: TStaticText
          Left = 392
          Top = 80
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 26
        end
        object st_CM33gain: TStaticText
          Left = 392
          Top = 104
          Width = 30
          Height = 17
          BorderStyle = sbsSunken
          Caption = '100%'
          TabOrder = 27
        end
        object btn_CM3_Read: TButton
          Left = 152
          Top = 136
          Width = 41
          Height = 17
          Caption = 'Read'
          TabOrder = 28
          OnClick = btn_CM3_ReadClick
        end
      end
    end
    object CheckBox4: TCheckBox
      Left = 288
      Top = 80
      Width = 97
      Height = 17
      Caption = 'CheckBox4'
      TabOrder = 6
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 640
  end
  object SaveDialog1: TSaveDialog
    Left = 672
  end
end
