object HSVForm2nd: THSVForm2nd
  Left = 511
  Top = 77
  Width = 1060
  Height = 932
  Caption = 'HSV2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyPress = FormKeyPress
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox1: TGroupBox
    Left = 9
    Top = 0
    Width = 987
    Height = 838
    TabOrder = 0
    object CheckBox1: TCheckBox
      Left = 159
      Top = 10
      Width = 106
      Height = 21
      Caption = 'CheckBox1'
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 255
      Top = 10
      Width = 106
      Height = 21
      Caption = 'CheckBox2'
      TabOrder = 1
    end
    object rg_HSV_Mode: TRadioGroup
      Left = 10
      Top = 41
      Width = 143
      Height = 51
      Caption = 'HUE/Sat Mode'
      Columns = 3
      Items.Strings = (
        '1'
        '2'
        '3')
      TabOrder = 2
      OnClick = rg_HSV_ModeClick
    end
    object btn_hsv_load: TButton
      Left = 12
      Top = 10
      Width = 70
      Height = 31
      Caption = 'Load File'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btn_hsv_loadClick
    end
    object btn_hsv_save: TButton
      Left = 84
      Top = 10
      Width = 70
      Height = 31
      Caption = 'Save File'
      TabOrder = 4
      OnClick = btn_hsv_saveClick
    end
    object CheckBox3: TCheckBox
      Left = 359
      Top = 10
      Width = 144
      Height = 21
      Caption = 'CheckBox3'
      TabOrder = 5
    end
    object CheckBox4: TCheckBox
      Left = 502
      Top = 10
      Width = 129
      Height = 21
      Caption = 'CheckBox4'
      TabOrder = 6
    end
    object stringGrid_HSV: TStringGrid
      Left = 772
      Top = 55
      Width = 204
      Height = 665
      Cursor = crIBeam
      ColCount = 4
      DefaultColWidth = 38
      DefaultRowHeight = 16
      RowCount = 25
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goDrawFocusSelected, goTabs, goRowSelect]
      TabOrder = 7
      OnDrawCell = stringGrid_HSVDrawCell
      OnSelectCell = stringGrid_HSVSelectCell
      RowHeights = (
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16
        16)
    end
    inline colorPicker: TColorPickerFrame
      Left = 217
      Top = 41
      Width = 552
      Height = 432
      TabOrder = 8
      inherited btn_c3d_load_img: TButton
        OnClick = colorPickerbtn_c3d_load_imgClick
      end
      inherited cb_show_ref_img: TCheckBox
        Left = 377
        Width = 158
        OnClick = colorPickercb_show_ref_imgClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 217
      Top = 473
      Width = 552
      Height = 355
      Caption = 'HSV Adjustment'
      TabOrder = 9
      object cb_Hue_rotation: TCheckBox
        Left = 398
        Top = 41
        Width = 76
        Height = 21
        Caption = 'Global'
        TabOrder = 0
        Visible = False
      end
      object btn_set: TButton
        Left = 485
        Top = 315
        Width = 60
        Height = 19
        Caption = 'Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        Visible = False
        OnClick = btn_setClick
      end
      object btn_reset: TButton
        Left = 485
        Top = 148
        Width = 60
        Height = 18
        Caption = 'Reset'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = btn_resetClick
      end
      object btn_hsv_write: TButton
        Left = 485
        Top = 167
        Width = 60
        Height = 19
        Caption = 'Write'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btn_hsv_writeClick
      end
      object btn_hsv_read: TButton
        Left = 485
        Top = 187
        Width = 60
        Height = 19
        Caption = 'Read'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        OnClick = btn_hsv_readClick
      end
      object Btn_HSV_reload: TBitBtn
        Left = 457
        Top = 207
        Width = 88
        Height = 31
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 5
        OnClick = Btn_HSV_reloadClick
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
      object CheckBox_AutoSet: TCheckBox
        Left = 464
        Top = 272
        Width = 81
        Height = 17
        Caption = 'Auto Set'
        Checked = True
        State = cbChecked
        TabOrder = 7
        Visible = False
      end
      object CheckBox_AutoWrite: TCheckBox
        Left = 336
        Top = 14
        Width = 89
        Height = 17
        Caption = 'Auto Write'
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
      inline hsvAdjust: THSVAdjustFrame
        Left = 5
        Top = 70
        Width = 444
        Height = 219
        TabOrder = 8
        inherited GroupBox40: TGroupBox
          Top = -7
          Width = 443
          Height = 77
          inherited lb_Hue_gain: TLabel
            Left = 409
            Top = 48
          end
          inherited Label197: TLabel
            Left = 22
            Top = 37
            Width = 30
            Height = 20
            Font.Height = -17
          end
          inherited sb_Hue_gain: TScrollBar
            Left = 101
            Top = 39
            Width = 300
            Height = 26
            Hint = '[1] for minus, [2] for plus'
            Max = 96
            Min = -96
            ParentShowHint = False
            Position = 0
            ShowHint = True
            OnChange = hsvAdjustsb_Hue_gainChange
          end
          inherited Edit_c3d_Manual39_h_adj: TEdit
            Left = 218
            Top = 10
            Width = 61
            Visible = False
          end
          inherited Button_HueReset: TButton
            Left = 286
            Top = 10
            Width = 60
            Height = 21
            Hint = '[3]'
            ParentShowHint = False
            ShowHint = True
            OnClick = hsvAdjustButton_HueResetClick
          end
          inherited Button_HueReturn: TButton
            Left = 354
            Top = 10
            Width = 61
            Height = 21
          end
        end
        inherited GroupBox41: TGroupBox
          Top = 68
          Width = 443
          Height = 71
          inherited lb_Sat_gain: TLabel
            Left = 409
            Top = 48
          end
          inherited Label207: TLabel
            Left = 6
            Top = 37
            Width = 74
            Height = 20
            Font.Height = -17
          end
          inherited sb_Sat_gain: TScrollBar
            Left = 101
            Top = 39
            Width = 300
            Height = 26
            Hint = '[q] for minus, [w] for plus'
            Max = 63
            Min = -63
            ParentShowHint = False
            Position = 0
            ShowHint = True
            OnChange = hsvAdjustsb_Sat_gainChange
          end
          inherited edt_c3d_satC: TEdit
            Left = 7
            Top = 9
            Width = 37
          end
          inherited Edit_c3d_Manual39_s_adj: TEdit
            Left = 218
            Top = 10
            Width = 61
            Visible = False
          end
          inherited Button_SaturationReset: TButton
            Left = 286
            Top = 10
            Width = 60
            Height = 21
            Hint = '[e]'
            ParentShowHint = False
            ShowHint = True
          end
          inherited Button_SaturationReturn: TButton
            Left = 354
            Top = 10
            Width = 61
            Height = 21
          end
        end
        inherited GroupBox7: TGroupBox
          Top = 133
          Width = 443
          Height = 75
          inherited lb_Val_gain: TLabel
            Left = 409
            Top = 50
          end
          inherited Label25: TLabel
            Left = 6
            Top = 41
            Width = 41
            Height = 20
            Font.Height = -17
          end
          inherited sb_Val_gain: TScrollBar
            Left = 101
            Top = 39
            Width = 300
            Height = 26
            Hint = '[a] for minus, [s] for plus'
            Min = -63
            ParentShowHint = False
            ShowHint = True
            OnChange = hsvAdjustsb_Val_gainChange
          end
          inherited Edit_c3d_Manual39_v_adj: TEdit
            Left = 218
            Top = 10
            Width = 61
            Visible = False
          end
          inherited edt_c3d_valC: TEdit
            Left = 12
            Top = 11
            Width = 38
          end
          inherited Button_BrightnessReset: TButton
            Left = 286
            Top = 10
            Width = 60
            Height = 21
            Hint = '[d]'
            ParentShowHint = False
            ShowHint = True
          end
          inherited Button_BrightnessReturn: TButton
            Left = 354
            Top = 10
            Width = 61
            Height = 21
          end
        end
      end
      object CheckBox_OffWhenWrite: TCheckBox
        Left = 466
        Top = 292
        Width = 156
        Height = 17
        Caption = 'Off when Write'
        Checked = True
        State = cbChecked
        TabOrder = 9
        Visible = False
      end
      object Button_15BaseInterp: TButton
        Left = 482
        Top = 36
        Width = 61
        Height = 17
        Caption = 'I&nterp.'
        TabOrder = 10
        OnClick = Button_15BaseInterpClick
      end
      object Button_HInterp: TButton
        Left = 482
        Top = 55
        Width = 61
        Height = 18
        Caption = 'H Interp.'
        TabOrder = 11
        OnClick = Button_HInterpClick
      end
      object Button_SInterp: TButton
        Left = 482
        Top = 75
        Width = 61
        Height = 17
        Caption = 'S Interp.'
        TabOrder = 12
        OnClick = Button_SInterpClick
      end
      object Button_VInterp: TButton
        Left = 482
        Top = 95
        Width = 61
        Height = 17
        Caption = 'V Interp.'
        TabOrder = 13
        OnClick = Button_VInterpClick
      end
      object CheckBox_ShowPattern: TCheckBox
        Left = 423
        Top = 14
        Width = 120
        Height = 17
        Caption = 'Show Pattern'
        TabOrder = 14
        OnClick = CheckBox_ShowPatternClick
      end
      object GroupBox5: TGroupBox
        Left = 5
        Top = 17
        Width = 228
        Height = 51
        Caption = 'Select Mode'
        TabOrder = 15
        object RadioButton_Global: TRadioButton
          Left = 148
          Top = 20
          Width = 70
          Height = 21
          Caption = 'Global'
          TabOrder = 0
          OnClick = RadioButton_GlobalClick
        end
        object RadioButton_Local: TRadioButton
          Left = 79
          Top = 20
          Width = 70
          Height = 21
          Caption = 'Local'
          TabOrder = 1
          OnClick = RadioButton_LocalClick
        end
        object RadioButton_Single: TRadioButton
          Left = 10
          Top = 20
          Width = 70
          Height = 21
          Caption = 'Single'
          Checked = True
          TabOrder = 2
          TabStop = True
          OnClick = RadioButton_SingleClick
        end
      end
    end
    object GroupBox3: TGroupBox
      Left = 9
      Top = 96
      Width = 200
      Height = 348
      Caption = 'HSV Change'
      TabOrder = 10
      object GroupBox6: TGroupBox
        Left = 9
        Top = 345
        Width = 176
        Height = 168
        Caption = '15'#176' Base'
        TabOrder = 0
        Visible = False
        object RadioButton1: TRadioButton
          Left = 9
          Top = 16
          Width = 64
          Height = 25
          Caption = '15'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 0
        end
        object RadioButton2: TRadioButton
          Left = 9
          Top = 137
          Width = 64
          Height = 24
          Caption = '165'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 1
        end
        object RadioButton3: TRadioButton
          Left = 9
          Top = 41
          Width = 64
          Height = 24
          Caption = '45'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 2
        end
        object RadioButton4: TRadioButton
          Left = 9
          Top = 64
          Width = 64
          Height = 25
          Caption = '75'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 3
        end
        object RadioButton5: TRadioButton
          Left = 9
          Top = 89
          Width = 64
          Height = 24
          Caption = '105'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 4
        end
        object RadioButton6: TRadioButton
          Left = 9
          Top = 112
          Width = 64
          Height = 25
          Caption = '135'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 5
        end
        object RadioButton13: TRadioButton
          Left = 96
          Top = 16
          Width = 65
          Height = 25
          Caption = '195'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 6
        end
        object RadioButton14: TRadioButton
          Left = 96
          Top = 41
          Width = 65
          Height = 24
          Caption = '225'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 7
        end
        object RadioButton15: TRadioButton
          Left = 96
          Top = 64
          Width = 65
          Height = 25
          Caption = '255'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 8
        end
        object RadioButton16: TRadioButton
          Left = 96
          Top = 89
          Width = 65
          Height = 24
          Caption = '285'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 9
        end
        object RadioButton17: TRadioButton
          Left = 96
          Top = 112
          Width = 65
          Height = 25
          Caption = '315'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 10
        end
        object RadioButton18: TRadioButton
          Left = 96
          Top = 137
          Width = 65
          Height = 24
          Caption = '345'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 11
        end
      end
      object GroupBox4: TGroupBox
        Left = 9
        Top = 16
        Width = 184
        Height = 217
        Caption = 'Hue'
        TabOrder = 1
        object GroupBox_60base: TGroupBox
          Left = 9
          Top = 16
          Width = 80
          Height = 193
          Caption = '60'#176' Base'
          TabOrder = 0
          object RadioButton_deg0: TRadioButton
            Left = 9
            Top = 16
            Width = 64
            Height = 25
            Hint = '0'
            Caption = 'R 0'#176
            Checked = True
            Color = clBtnFace
            ParentColor = False
            TabOrder = 0
            TabStop = True
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg60: TRadioButton
            Left = 9
            Top = 41
            Width = 64
            Height = 24
            Hint = '60'
            Caption = 'Y 60'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 1
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg120: TRadioButton
            Left = 9
            Top = 64
            Width = 64
            Height = 25
            Hint = '120'
            Caption = 'G 120'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 2
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg180: TRadioButton
            Left = 9
            Top = 89
            Width = 64
            Height = 24
            Hint = '180'
            Caption = 'C 180'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 3
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg240: TRadioButton
            Left = 9
            Top = 112
            Width = 64
            Height = 25
            Hint = '240'
            Caption = 'B 240'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 4
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg300: TRadioButton
            Left = 9
            Top = 137
            Width = 64
            Height = 24
            Hint = '300'
            Caption = 'M 300'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 5
            OnClick = RadioButton_deg60baseClick
          end
          object Button_60BaseInterp: TButton
            Left = 9
            Top = 160
            Width = 64
            Height = 25
            Caption = 'Interp.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = Button_60BaseInterpClick
          end
        end
        object GroupBox_30base: TGroupBox
          Left = 89
          Top = 16
          Width = 88
          Height = 193
          Caption = '30'#176' Base'
          TabOrder = 1
          object RadioButton_deg30: TRadioButton
            Left = 9
            Top = 16
            Width = 72
            Height = 25
            Hint = '30'
            Caption = 'RY 30'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 0
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg90: TRadioButton
            Left = 9
            Top = 41
            Width = 72
            Height = 24
            Hint = '90'
            Caption = 'GY 90'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 1
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg150: TRadioButton
            Left = 9
            Top = 64
            Width = 72
            Height = 25
            Hint = '150'
            Caption = 'GC 150'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 2
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg210: TRadioButton
            Left = 9
            Top = 89
            Width = 72
            Height = 24
            Hint = '210'
            Caption = 'BC 210'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 3
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg270: TRadioButton
            Left = 9
            Top = 112
            Width = 72
            Height = 25
            Hint = '270'
            Caption = 'BM 270'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 4
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg330: TRadioButton
            Left = 9
            Top = 137
            Width = 72
            Height = 24
            Hint = '330'
            Caption = 'RM 330'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 5
            OnClick = RadioButton_deg30baseClick
          end
          object Button_30BaseInterp: TButton
            Left = 9
            Top = 160
            Width = 64
            Height = 25
            Caption = 'Interp.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = Button_30BaseInterpClick
          end
        end
      end
      object RadioGroup_Saturation: TRadioGroup
        Left = 9
        Top = 233
        Width = 88
        Height = 104
        Caption = 'Saturation'
        ItemIndex = 3
        Items.Strings = (
          'Low '
          'Middle '
          'High '
          'Max')
        TabOrder = 2
        OnClick = RadioGroup_SaturationClick
      end
      object RadioGroup_Value: TRadioGroup
        Left = 105
        Top = 233
        Width = 80
        Height = 104
        Caption = 'Value'
        ItemIndex = 2
        Items.Strings = (
          'Low'
          'Middle'
          'High'
          'Max')
        TabOrder = 3
        OnClick = RadioGroup_ValueClick
      end
    end
    object Edit_CursorColor: TEdit
      Left = 10
      Top = 453
      Width = 198
      Height = 24
      TabOrder = 11
      Text = 'RGB Cursor Color'
    end
    object GroupBox_OoG: TGroupBox
      Left = 10
      Top = 670
      Width = 198
      Height = 109
      Caption = 'Out of Gamut Indicator'
      TabOrder = 12
      object CheckBox_OoG: TCheckBox
        Left = 10
        Top = 20
        Width = 109
        Height = 21
        Caption = 'Out of Gamut'
        Color = clBtnFace
        Enabled = False
        ParentColor = False
        TabOrder = 0
      end
      object Button_OoGSetup: TButton
        Left = 118
        Top = 20
        Width = 70
        Height = 21
        Caption = 'Setup'
        TabOrder = 1
        OnClick = Button_OoGSetupClick
      end
      object Edit_TargetCursorColor: TEdit
        Left = 10
        Top = 44
        Width = 178
        Height = 24
        TabOrder = 2
      end
      object Edit_TargetCursorColorHSV: TEdit
        Left = 10
        Top = 69
        Width = 178
        Height = 24
        TabOrder = 3
      end
    end
    object Edit_CursorColorHSV: TEdit
      Left = 10
      Top = 478
      Width = 198
      Height = 24
      TabOrder = 13
      Text = 'HSV Cursor Color'
    end
    object GroupBox7: TGroupBox
      Left = 10
      Top = 778
      Width = 198
      Height = 50
      Caption = 'Turn Point'
      TabOrder = 14
      object Label_TurnPoint: TLabel
        Left = 139
        Top = 20
        Width = 7
        Height = 16
        Caption = '0'
      end
      object ScrollBar_TurnPoint: TScrollBar
        Left = 5
        Top = 20
        Width = 129
        Height = 21
        Max = 15
        PageSize = 0
        Position = 7
        TabOrder = 0
        OnChange = ScrollBar_TurnPointChange
      end
    end
    object CheckBox_SAT_CLIP_EN: TCheckBox
      Left = 620
      Top = 10
      Width = 110
      Height = 21
      Caption = 'SAT_CLIP_EN'
      TabOrder = 15
    end
    object GroupBox8: TGroupBox
      Left = 10
      Top = 512
      Width = 198
      Height = 149
      Caption = 'Memory Color'
      TabOrder = 16
      object RadioButton_CSkin: TRadioButton
        Left = 10
        Top = 20
        Width = 139
        Height = 21
        Hint = '0'
        Caption = 'Caucasian Skin'
        TabOrder = 0
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_OSkin: TRadioButton
        Left = 10
        Top = 39
        Width = 139
        Height = 21
        Hint = '15'
        Caption = 'Oriental Skin'
        TabOrder = 1
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_Orange: TRadioButton
        Left = 10
        Top = 59
        Width = 139
        Height = 21
        Hint = '30'
        Caption = 'Orange'
        TabOrder = 2
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_GreenGrass: TRadioButton
        Left = 10
        Top = 79
        Width = 139
        Height = 21
        Hint = '120'
        Caption = 'Green Grass'
        TabOrder = 3
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_DFoliage: TRadioButton
        Left = 10
        Top = 98
        Width = 139
        Height = 21
        Hint = '135'
        Caption = 'Deciduous Foliage'
        TabOrder = 4
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_BlueSky: TRadioButton
        Left = 10
        Top = 118
        Width = 139
        Height = 21
        Hint = '195'
        Caption = 'Blue Sky'
        TabOrder = 5
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object CheckBox_MemoryColor: TCheckBox
        Left = 98
        Top = -1
        Width = 71
        Height = 21
        Caption = 'Check'
        TabOrder = 6
        Visible = False
      end
    end
    object GroupBox9: TGroupBox
      Left = 223
      Top = 750
      Width = 443
      Height = 75
      TabOrder = 17
      object Label25: TLabel
        Left = 6
        Top = 41
        Width = 56
        Height = 20
        Caption = 'Chroma'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -17
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label_Chroma: TLabel
        Left = 409
        Top = 50
        Width = 7
        Height = 16
        Caption = '0'
      end
      object ScrollBar_Chroma: TScrollBar
        Left = 101
        Top = 39
        Width = 300
        Height = 26
        Hint = '[z] for minus, [x] for plus'
        Max = 63
        Min = -63
        PageSize = 0
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnChange = ScrollBar_ChromaChange
      end
      object Button_ChromaReset: TButton
        Left = 286
        Top = 10
        Width = 60
        Height = 21
        Hint = '[c]'
        Caption = 'Reset'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Button_ChromaResetClick
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 760
    Top = 688
  end
  object SaveDialog1: TSaveDialog
    Left = 736
    Top = 688
  end
end
