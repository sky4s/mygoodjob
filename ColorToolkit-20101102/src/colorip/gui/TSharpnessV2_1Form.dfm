object SharpnessV2_1Form: TSharpnessV2_1Form
  Left = 300
  Top = 5
  Width = 761
  Height = 852
  Caption = 'SharpnessV2_1Form'
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
  OnKeyPress = FormKeyPress
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox3: TGroupBox
    Left = 8
    Top = 1
    Width = 737
    Height = 816
    TabOrder = 0
    object Btn_SP_reload: TBitBtn
      Left = 648
      Top = 24
      Width = 73
      Height = 25
      Caption = '&Reload'
      ModalResult = 6
      TabOrder = 0
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object GroupBox1: TGroupBox
      Left = 8
      Top = 8
      Width = 241
      Height = 57
      Caption = 'Load / Save'
      TabOrder = 1
      object LUT_type: TRadioGroup
        Left = 8
        Top = 16
        Width = 121
        Height = 33
        Caption = 'Default Setting'
        Columns = 3
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Items.Strings = (
          '1'
          '2'
          '3')
        ParentFont = False
        TabOrder = 0
      end
      object btn_sp_Load: TButton
        Left = 136
        Top = 24
        Width = 49
        Height = 25
        Caption = 'Load'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
      end
      object btn_sp_Save: TButton
        Left = 184
        Top = 24
        Width = 49
        Height = 25
        Hint = 'Save SP Table'
        Caption = 'Save'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
      end
    end
    object Sharpness: TGroupBox
      Left = 8
      Top = 72
      Width = 721
      Height = 433
      Caption = 'Sharpness'
      TabOrder = 2
      object CheckBox1: TCheckBox
        Left = 72
        Top = 0
        Width = 65
        Height = 17
        Caption = 'SP_EN'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 528
        Top = 0
        Width = 81
        Height = 17
        Caption = 'SP_DEMO'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 608
        Top = 0
        Width = 105
        Height = 17
        Caption = 'SP_DEMO_LEFT'
        TabOrder = 2
      end
      object CheckBox6: TCheckBox
        Left = 456
        Top = 0
        Width = 73
        Height = 17
        Caption = 'DEB_EN'
        TabOrder = 3
      end
      object GroupBox2: TGroupBox
        Left = 272
        Top = 24
        Width = 441
        Height = 401
        Caption = 'Look-Up Table'
        TabOrder = 4
        object Label3: TLabel
          Left = 16
          Top = 15
          Width = 51
          Height = 13
          Caption = 'EDGE_TH'
        end
        object GroupBox4: TGroupBox
          Left = 8
          Top = 35
          Width = 425
          Height = 361
          Caption = 'SP_LUT 0 - 31'
          TabOrder = 0
          object SP_LUT: TImage
            Left = 8
            Top = 48
            Width = 369
            Height = 305
          end
          object Software: TLabel
            Left = 312
            Top = 24
            Width = 67
            Height = 13
            Caption = 'Software Gain'
          end
          object btn_sp_lut_write: TButton
            Left = 8
            Top = 16
            Width = 57
            Height = 25
            Caption = 'Write'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
          end
          object btn_sp_lut_read: TBitBtn
            Left = 72
            Top = 16
            Width = 57
            Height = 25
            Caption = 'Read'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
          end
          object btn_sp_lut_Set: TButton
            Left = 136
            Top = 16
            Width = 57
            Height = 25
            Caption = 'Clear'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
          end
          object sb_softgain: TScrollBar
            Left = 389
            Top = 47
            Width = 17
            Height = 273
            Kind = sbVertical
            Max = 150
            PageSize = 0
            Position = 140
            TabOrder = 3
          end
          object st_softgain: TStaticText
            Left = 392
            Top = 24
            Width = 10
            Height = 17
            BorderStyle = sbsSunken
            Caption = '1'
            TabOrder = 4
          end
          object btn_GainSet: TButton
            Left = 380
            Top = 326
            Width = 35
            Height = 25
            Caption = 'Set'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 5
          end
        end
        object ScrollBar3: TScrollBar
          Left = 80
          Top = 13
          Width = 127
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText3: TStaticText
          Left = 209
          Top = 14
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 2
        end
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 171
        Width = 249
        Height = 41
        Caption = 'Spike Noise Detection'
        TabOrder = 5
        object Label2: TLabel
          Left = 8
          Top = 18
          Width = 52
          Height = 13
          Caption = 'SPIKE_TH'
        end
        object ScrollBar2: TScrollBar
          Left = 80
          Top = 16
          Width = 137
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText2: TStaticText
          Left = 224
          Top = 17
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 1
        end
      end
      object GroupBox6: TGroupBox
        Left = 8
        Top = 24
        Width = 249
        Height = 41
        Caption = 'Global Strength'
        TabOrder = 6
        object Label1: TLabel
          Left = 8
          Top = 18
          Width = 49
          Height = 13
          Caption = 'GLB_STR'
        end
        object ScrollBar1: TScrollBar
          Left = 80
          Top = 16
          Width = 137
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText1: TStaticText
          Left = 224
          Top = 17
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 1
        end
      end
      object GroupBox7: TGroupBox
        Left = 8
        Top = 229
        Width = 249
        Height = 49
        Caption = 'Noise Filter'
        TabOrder = 7
        object Label4: TLabel
          Left = 8
          Top = 26
          Width = 58
          Height = 13
          Caption = 'FILTER_TH'
        end
        object CheckBox4: TCheckBox
          Left = 72
          Top = 0
          Width = 97
          Height = 17
          Caption = 'FILTER_OFF'
          TabOrder = 0
        end
        object ScrollBar4: TScrollBar
          Left = 80
          Top = 24
          Width = 137
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText4: TStaticText
          Left = 224
          Top = 25
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 2
        end
      end
      object GroupBox8: TGroupBox
        Left = 8
        Top = 293
        Width = 249
        Height = 108
        Caption = 'Texture Detection'
        TabOrder = 8
        object Label5: TLabel
          Left = 8
          Top = 50
          Width = 66
          Height = 13
          Caption = 'MAG_TH[5:0]'
        end
        object Label6: TLabel
          Left = 8
          Top = 81
          Width = 43
          Height = 13
          Caption = 'TAN_TH'
        end
        object Bevel5: TBevel
          Left = 0
          Top = 72
          Width = 249
          Height = 2
        end
        object Label27: TLabel
          Left = 8
          Top = 22
          Width = 57
          Height = 13
          Caption = 'MAG_TH[6]'
        end
        object CheckBox5: TCheckBox
          Left = 104
          Top = 0
          Width = 97
          Height = 17
          Caption = 'TEXT_DET'
          TabOrder = 0
        end
        object ScrollBar5: TScrollBar
          Left = 80
          Top = 48
          Width = 137
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText5: TStaticText
          Left = 224
          Top = 49
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 2
        end
        object ScrollBar6: TScrollBar
          Left = 80
          Top = 80
          Width = 137
          Height = 17
          PageSize = 0
          TabOrder = 3
        end
        object StaticText6: TStaticText
          Left = 224
          Top = 81
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 4
        end
        object ComboBox7: TComboBox
          Left = 80
          Top = 19
          Width = 161
          Height = 21
          ItemHeight = 13
          TabOrder = 5
        end
      end
      object GroupBox9: TGroupBox
        Left = 8
        Top = 80
        Width = 249
        Height = 73
        Caption = 'Pixel Strength'
        TabOrder = 9
        object Label7: TLabel
          Left = 8
          Top = 23
          Width = 48
          Height = 13
          Caption = 'STR_TP1'
        end
        object Label8: TLabel
          Left = 8
          Top = 47
          Width = 48
          Height = 13
          Caption = 'STR_TP2'
        end
        object ComboBox1: TComboBox
          Left = 64
          Top = 20
          Width = 177
          Height = 21
          ItemHeight = 13
          TabOrder = 0
        end
        object ComboBox2: TComboBox
          Left = 64
          Top = 44
          Width = 177
          Height = 21
          ItemHeight = 13
          TabOrder = 1
        end
      end
    end
    object GroupBox10: TGroupBox
      Left = 8
      Top = 512
      Width = 721
      Height = 297
      Caption = 'Contrast'
      TabOrder = 3
      object Bevel1: TBevel
        Left = 272
        Top = 192
        Width = 249
        Height = 0
      end
      object CheckBox8: TCheckBox
        Left = 64
        Top = 0
        Width = 65
        Height = 17
        Caption = 'CE_EN'
        TabOrder = 0
      end
      object CheckBox9: TCheckBox
        Left = 512
        Top = 0
        Width = 81
        Height = 17
        Caption = 'CE_DEMO'
        TabOrder = 1
      end
      object CheckBox10: TCheckBox
        Left = 592
        Top = 0
        Width = 105
        Height = 17
        Caption = 'CE_DEMO_LEFT'
        TabOrder = 2
      end
      object GroupBox14: TGroupBox
        Left = 248
        Top = 24
        Width = 249
        Height = 121
        Caption = 'Basic Curve'
        TabOrder = 3
        object Label17: TLabel
          Left = 8
          Top = 17
          Width = 50
          Height = 13
          Caption = 'DARK_TP'
        end
        object Label19: TLabel
          Left = 8
          Top = 42
          Width = 57
          Height = 13
          Caption = 'DARK_OFS'
        end
        object Label18: TLabel
          Left = 8
          Top = 76
          Width = 61
          Height = 13
          Caption = 'BRIGHT_TP'
        end
        object Label20: TLabel
          Left = 8
          Top = 98
          Width = 68
          Height = 13
          Caption = 'BRIGHT_OFS'
        end
        object Bevel2: TBevel
          Left = 0
          Top = 64
          Width = 249
          Height = 2
        end
        object ComboBox5: TComboBox
          Left = 88
          Top = 12
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 0
        end
        object ScrollBar13: TScrollBar
          Left = 88
          Top = 40
          Width = 129
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText13: TStaticText
          Left = 225
          Top = 41
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 2
        end
        object ComboBox6: TComboBox
          Left = 88
          Top = 72
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 3
        end
        object ScrollBar14: TScrollBar
          Left = 88
          Top = 96
          Width = 129
          Height = 17
          PageSize = 0
          TabOrder = 4
        end
        object StaticText14: TStaticText
          Left = 225
          Top = 97
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 5
        end
      end
      object GroupBox15: TGroupBox
        Left = 248
        Top = 152
        Width = 249
        Height = 140
        Caption = 'Dark/Bright Scene Control'
        TabOrder = 4
        object Label14: TLabel
          Left = 7
          Top = 46
          Width = 85
          Height = 13
          Caption = 'DARK_MAX_ADJ'
        end
        object Label21: TLabel
          Left = 7
          Top = 70
          Width = 52
          Height = 13
          Caption = 'DARK_DR'
        end
        object Bevel3: TBevel
          Left = 0
          Top = 89
          Width = 249
          Height = 2
        end
        object Label15: TLabel
          Left = 7
          Top = 97
          Width = 96
          Height = 13
          Caption = 'BRIGHT_MAX_ADJ'
        end
        object Label22: TLabel
          Left = 7
          Top = 117
          Width = 63
          Height = 13
          Caption = 'BRIGHT_DR'
        end
        object Bevel4: TBevel
          Left = 0
          Top = 38
          Width = 249
          Height = 2
        end
        object Label16: TLabel
          Left = 7
          Top = 18
          Width = 42
          Height = 13
          Caption = 'CE_STR'
        end
        object ScrollBar10: TScrollBar
          Left = 112
          Top = 44
          Width = 112
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText10: TStaticText
          Left = 231
          Top = 45
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 1
        end
        object ScrollBar15: TScrollBar
          Left = 112
          Top = 68
          Width = 112
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText15: TStaticText
          Left = 231
          Top = 69
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 3
        end
        object ScrollBar11: TScrollBar
          Left = 112
          Top = 94
          Width = 113
          Height = 17
          PageSize = 0
          TabOrder = 4
        end
        object StaticText11: TStaticText
          Left = 231
          Top = 95
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 5
        end
        object ScrollBar16: TScrollBar
          Left = 112
          Top = 115
          Width = 113
          Height = 17
          PageSize = 0
          TabOrder = 6
        end
        object StaticText16: TStaticText
          Left = 231
          Top = 116
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 7
        end
        object ScrollBar12: TScrollBar
          Left = 112
          Top = 16
          Width = 113
          Height = 17
          PageSize = 0
          TabOrder = 8
        end
        object StaticText12: TStaticText
          Left = 231
          Top = 17
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 9
        end
      end
      object GroupBox16: TGroupBox
        Left = 504
        Top = 24
        Width = 209
        Height = 81
        Caption = 'Timing Smooth'
        TabOrder = 5
        object Label25: TLabel
          Left = 8
          Top = 26
          Width = 60
          Height = 13
          Caption = 'STEP_GAIN'
        end
        object Label26: TLabel
          Left = 8
          Top = 58
          Width = 68
          Height = 13
          Caption = 'VARIANT_TH'
        end
        object CheckBox12: TCheckBox
          Left = 88
          Top = 0
          Width = 113
          Height = 17
          Caption = 'CE_SMOOTH_EN'
          TabOrder = 0
        end
        object ScrollBar17: TScrollBar
          Left = 80
          Top = 24
          Width = 105
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText17: TStaticText
          Left = 189
          Top = 26
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 2
        end
        object ScrollBar18: TScrollBar
          Left = 80
          Top = 56
          Width = 105
          Height = 17
          PageSize = 0
          TabOrder = 3
        end
        object StaticText18: TStaticText
          Left = 189
          Top = 57
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 4
        end
      end
      object GroupBox11: TGroupBox
        Left = 8
        Top = 24
        Width = 233
        Height = 41
        Caption = 'Luminance Reference'
        TabOrder = 6
        object Label11: TLabel
          Left = 8
          Top = 18
          Width = 71
          Height = 13
          Caption = 'LUM_MEDIAN'
        end
        object ScrollBar7: TScrollBar
          Left = 88
          Top = 16
          Width = 121
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText7: TStaticText
          Left = 214
          Top = 17
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 1
        end
      end
      object GroupBox12: TGroupBox
        Left = 8
        Top = 80
        Width = 233
        Height = 113
        Caption = 'Average Mask'
        TabOrder = 7
        object Label9: TLabel
          Left = 8
          Top = 16
          Width = 63
          Height = 13
          Caption = 'VMASK_SEL'
        end
        object Label10: TLabel
          Left = 8
          Top = 40
          Width = 64
          Height = 13
          Caption = 'HMASK_SEL'
        end
        object Label24: TLabel
          Left = 119
          Top = 88
          Width = 12
          Height = 13
          Caption = '<='
        end
        object Label23: TLabel
          Left = 175
          Top = 88
          Width = 5
          Height = 13
          Caption = 'x'
        end
        object ComboBox3: TComboBox
          Left = 88
          Top = 12
          Width = 129
          Height = 21
          ItemHeight = 13
          TabOrder = 0
        end
        object ComboBox4: TComboBox
          Left = 88
          Top = 36
          Width = 129
          Height = 21
          ItemHeight = 13
          TabOrder = 1
        end
        object LabeledEdit1: TLabeledEdit
          Left = 8
          Top = 84
          Width = 105
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'CE_PIX_NUM'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
        end
        object Edit_ResolutionH: TEdit
          Left = 136
          Top = 84
          Width = 33
          Height = 21
          TabOrder = 3
          Text = '1920'
        end
        object Edit_ResolutionV: TEdit
          Left = 184
          Top = 84
          Width = 33
          Height = 21
          TabOrder = 4
          Text = '1080'
        end
      end
      object GroupBox13: TGroupBox
        Left = 8
        Top = 206
        Width = 233
        Height = 67
        Caption = 'Pixel Filter'
        TabOrder = 8
        object Label12: TLabel
          Left = 8
          Top = 20
          Width = 96
          Height = 13
          Caption = 'PIX_FILTER_DARK'
        end
        object Label13: TLabel
          Left = 8
          Top = 43
          Width = 107
          Height = 13
          Caption = 'PIX_FILTER_BRIGHT'
        end
        object CheckBox11: TCheckBox
          Left = 64
          Top = 0
          Width = 97
          Height = 17
          Caption = 'PIX_FILTER'
          TabOrder = 0
        end
        object ScrollBar8: TScrollBar
          Left = 120
          Top = 18
          Width = 97
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar9: TScrollBar
          Left = 120
          Top = 42
          Width = 97
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText8: TStaticText
          Left = 219
          Top = 19
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 3
        end
        object StaticText9: TStaticText
          Left = 219
          Top = 43
          Width = 10
          Height = 17
          Caption = '0'
          TabOrder = 4
        end
      end
    end
    object CheckBox7: TCheckBox
      Left = 144
      Top = 72
      Width = 81
      Height = 17
      Caption = 'IMGEN_SP'
      TabOrder = 4
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 589
    Top = 24
  end
  object OpenDialog1: TOpenDialog
    Left = 621
    Top = 24
  end
end
