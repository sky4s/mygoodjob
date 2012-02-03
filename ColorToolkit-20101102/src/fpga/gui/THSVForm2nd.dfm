object HSVForm2nd: THSVForm2nd
  Left = 341
  Top = 239
  Width = 869
  Height = 797
  Caption = 'HSV2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
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
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 7
    Top = 0
    Width = 802
    Height = 681
    TabOrder = 0
    object CheckBox1: TCheckBox
      Left = 129
      Top = 8
      Width = 86
      Height = 17
      Caption = 'CheckBox1'
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 207
      Top = 8
      Width = 86
      Height = 17
      Caption = 'CheckBox2'
      TabOrder = 1
    end
    object rg_HSV_Mode: TRadioGroup
      Left = 8
      Top = 33
      Width = 116
      Height = 42
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
      Left = 10
      Top = 8
      Width = 57
      Height = 25
      Caption = 'Load File'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btn_hsv_loadClick
    end
    object btn_hsv_save: TButton
      Left = 68
      Top = 8
      Width = 57
      Height = 25
      Caption = 'Save File'
      TabOrder = 4
      OnClick = btn_hsv_saveClick
    end
    object CheckBox3: TCheckBox
      Left = 292
      Top = 8
      Width = 117
      Height = 17
      Caption = 'CheckBox3'
      TabOrder = 5
    end
    object CheckBox4: TCheckBox
      Left = 408
      Top = 8
      Width = 105
      Height = 17
      Caption = 'CheckBox4'
      TabOrder = 6
    end
    object stringGrid_HSV: TStringGrid
      Left = 627
      Top = 45
      Width = 166
      Height = 540
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
      Left = 176
      Top = 33
      Width = 449
      Height = 351
      TabOrder = 8
      inherited lb_c3d_showV: TLabel
        Left = 320
        Top = 328
      end
      inherited lb_c3d_showS: TLabel
        Left = 272
        Top = 328
      end
      inherited lb_c3d_showH: TLabel
        Left = 232
        Top = 328
      end
      inherited lb_c3d_showB: TLabel
        Left = 184
        Top = 328
      end
      inherited lb_c3d_showG: TLabel
        Left = 144
        Top = 328
      end
      inherited lb_c3d_showR: TLabel
        Left = 106
        Top = 328
      end
      inherited lb_c3d_showY: TLabel
        Left = 56
        Top = 328
      end
      inherited lb_c3d_showX: TLabel
        Left = 18
        Top = 328
      end
      inherited pc_img: TPageControl
        Width = 448
        Height = 328
        inherited ts_image: TTabSheet
          inherited ScrollBox1: TScrollBox
            Width = 441
            Height = 305
            inherited image: TImage
              Width = 433
              Height = 301
            end
          end
        end
        inherited ts_color: TTabSheet
          inherited originalColor: TImage
            Width = 433
            Height = 301
          end
          inherited btn_img_next: TBitBtn
            Left = 400
            Top = 264
            Width = 25
            Height = 25
          end
          inherited btn_img_prev: TBitBtn
            Left = 368
            Top = 264
            Width = 25
            Height = 25
          end
        end
        inherited TabSheet3: TTabSheet
          inherited simulatedColor: TImage
            Width = 433
            Height = 301
          end
        end
      end
      inherited btn_c3d_load_img: TButton
        Left = 232
        Top = 5
        Width = 65
        Height = 15
        OnClick = colorPickerbtn_c3d_load_imgClick
      end
      inherited cb_show_ref_img: TCheckBox
        Left = 306
        Top = 5
        Width = 129
        Height = 16
        OnClick = colorPickercb_show_ref_imgClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 176
      Top = 384
      Width = 449
      Height = 289
      Caption = 'HSV Adjustment'
      TabOrder = 9
      object btn_set: TButton
        Left = 394
        Top = 256
        Width = 49
        Height = 15
        Caption = 'Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        Visible = False
        OnClick = btn_setClick
      end
      object btn_reset: TButton
        Left = 394
        Top = 120
        Width = 49
        Height = 15
        Caption = 'Reset'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        OnClick = btn_resetClick
      end
      object btn_hsv_write: TButton
        Left = 394
        Top = 136
        Width = 49
        Height = 15
        Caption = 'Write'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        OnClick = btn_hsv_writeClick
      end
      object btn_hsv_read: TButton
        Left = 394
        Top = 152
        Width = 49
        Height = 15
        Caption = 'Read'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btn_hsv_readClick
      end
      object Btn_HSV_reload: TBitBtn
        Left = 371
        Top = 168
        Width = 72
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 4
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
        Left = 377
        Top = 221
        Width = 66
        Height = 14
        Caption = 'Auto Set'
        TabOrder = 6
        Visible = False
      end
      object CheckBox_AutoWrite: TCheckBox
        Left = 273
        Top = 11
        Width = 72
        Height = 14
        Caption = 'Auto Write'
        Checked = True
        State = cbChecked
        TabOrder = 5
      end
      inline hsvAdjust: THSVAdjustFrame
        Left = 4
        Top = 57
        Width = 361
        Height = 178
        TabOrder = 7
        inherited GroupBox40: TGroupBox
          inherited lb_Hue_gain: TLabel
            Left = 332
          end
          inherited sb_Hue_gain: TScrollBar
            Left = 82
            Hint = '[1] for minus, [2] for plus'
            Max = 96
            Min = -96
            ParentShowHint = False
            Position = 0
            ShowHint = True
            OnChange = hsvAdjustsb_Hue_gainChange
          end
          inherited Edit_c3d_Manual39_h_adj: TEdit
            Visible = False
          end
          inherited Button_HueReset: TButton
            Hint = '[3]'
            ParentShowHint = False
            ShowHint = True
            OnClick = hsvAdjustButton_HueResetClick
          end
        end
        inherited GroupBox41: TGroupBox
          Top = 55
          inherited lb_Sat_gain: TLabel
            Left = 332
          end
          inherited sb_Sat_gain: TScrollBar
            Left = 82
            Hint = '[q] for minus, [w] for plus'
            Max = 63
            Min = -63
            ParentShowHint = False
            Position = 0
            ShowHint = True
            OnChange = hsvAdjustsb_Sat_gainChange
          end
          inherited Edit_c3d_Manual39_s_adj: TEdit
            Visible = False
          end
          inherited Button_SaturationReset: TButton
            Hint = '[e]'
            ParentShowHint = False
            ShowHint = True
          end
        end
        inherited GroupBox7: TGroupBox
          Top = 108
          inherited lb_Val_gain: TLabel
            Left = 332
          end
          inherited sb_Val_gain: TScrollBar
            Left = 82
            Hint = '[a] for minus, [s] for plus'
            Min = -63
            ParentShowHint = False
            ShowHint = True
            OnChange = hsvAdjustsb_Val_gainChange
          end
          inherited Edit_c3d_Manual39_v_adj: TEdit
            Visible = False
          end
          inherited Button_BrightnessReset: TButton
            Hint = '[d]'
            ParentShowHint = False
            ShowHint = True
          end
        end
      end
      object CheckBox_OffWhenWrite: TCheckBox
        Left = 379
        Top = 237
        Width = 126
        Height = 14
        Caption = 'Off when Write'
        Checked = True
        State = cbChecked
        TabOrder = 8
        Visible = False
      end
      object Button_15BaseInterp: TButton
        Left = 392
        Top = 29
        Width = 49
        Height = 14
        Caption = 'I&nterp.'
        TabOrder = 9
        OnClick = Button_15BaseInterpClick
      end
      object Button_HInterp: TButton
        Left = 392
        Top = 45
        Width = 49
        Height = 14
        Caption = 'H Interp.'
        TabOrder = 10
        OnClick = Button_HInterpClick
      end
      object Button_SInterp: TButton
        Left = 392
        Top = 61
        Width = 49
        Height = 14
        Caption = 'S Interp.'
        TabOrder = 11
        OnClick = Button_SInterpClick
      end
      object Button_VInterp: TButton
        Left = 392
        Top = 77
        Width = 49
        Height = 14
        Caption = 'V Interp.'
        TabOrder = 12
        OnClick = Button_VInterpClick
      end
      object CheckBox_ShowPattern: TCheckBox
        Left = 344
        Top = 11
        Width = 97
        Height = 14
        Caption = 'Show Pattern'
        TabOrder = 13
        OnClick = CheckBox_ShowPatternClick
      end
      object GroupBox5: TGroupBox
        Left = 4
        Top = 14
        Width = 185
        Height = 41
        Caption = 'Select Mode'
        TabOrder = 14
        object RadioButton_Global: TRadioButton
          Left = 120
          Top = 16
          Width = 57
          Height = 17
          Caption = 'Global'
          TabOrder = 0
          OnClick = RadioButton_GlobalClick
        end
        object RadioButton_Local: TRadioButton
          Left = 64
          Top = 16
          Width = 57
          Height = 17
          Caption = 'Local'
          TabOrder = 1
          OnClick = RadioButton_LocalClick
        end
        object RadioButton_Single: TRadioButton
          Left = 8
          Top = 16
          Width = 57
          Height = 17
          Caption = 'Single'
          Checked = True
          TabOrder = 2
          TabStop = True
          OnClick = RadioButton_SingleClick
        end
      end
    end
    object GroupBox3: TGroupBox
      Left = 7
      Top = 78
      Width = 163
      Height = 283
      Caption = 'HSV Change'
      TabOrder = 10
      object GroupBox6: TGroupBox
        Left = 7
        Top = 280
        Width = 143
        Height = 137
        Caption = '15'#176' Base'
        TabOrder = 0
        Visible = False
        object RadioButton1: TRadioButton
          Left = 7
          Top = 13
          Width = 52
          Height = 20
          Caption = '15'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 0
        end
        object RadioButton2: TRadioButton
          Left = 7
          Top = 111
          Width = 52
          Height = 20
          Caption = '165'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 1
        end
        object RadioButton3: TRadioButton
          Left = 7
          Top = 33
          Width = 52
          Height = 20
          Caption = '45'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 2
        end
        object RadioButton4: TRadioButton
          Left = 7
          Top = 52
          Width = 52
          Height = 20
          Caption = '75'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 3
        end
        object RadioButton5: TRadioButton
          Left = 7
          Top = 72
          Width = 52
          Height = 20
          Caption = '105'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 4
        end
        object RadioButton6: TRadioButton
          Left = 7
          Top = 91
          Width = 52
          Height = 20
          Caption = '135'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 5
        end
        object RadioButton13: TRadioButton
          Left = 78
          Top = 13
          Width = 53
          Height = 20
          Caption = '195'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 6
        end
        object RadioButton14: TRadioButton
          Left = 78
          Top = 33
          Width = 53
          Height = 20
          Caption = '225'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 7
        end
        object RadioButton15: TRadioButton
          Left = 78
          Top = 52
          Width = 53
          Height = 20
          Caption = '255'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 8
        end
        object RadioButton16: TRadioButton
          Left = 78
          Top = 72
          Width = 53
          Height = 20
          Caption = '285'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 9
        end
        object RadioButton17: TRadioButton
          Left = 78
          Top = 91
          Width = 53
          Height = 20
          Caption = '315'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 10
        end
        object RadioButton18: TRadioButton
          Left = 78
          Top = 111
          Width = 53
          Height = 20
          Caption = '345'#176
          Color = clBtnFace
          ParentColor = False
          TabOrder = 11
        end
      end
      object GroupBox4: TGroupBox
        Left = 7
        Top = 13
        Width = 150
        Height = 176
        Caption = 'Hue'
        TabOrder = 1
        object GroupBox_60base: TGroupBox
          Left = 7
          Top = 13
          Width = 65
          Height = 157
          Caption = '60'#176' Base'
          TabOrder = 0
          object RadioButton_deg0: TRadioButton
            Left = 7
            Top = 13
            Width = 52
            Height = 20
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
            Left = 7
            Top = 33
            Width = 52
            Height = 20
            Hint = '60'
            Caption = 'Y 60'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 1
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg120: TRadioButton
            Left = 7
            Top = 52
            Width = 52
            Height = 20
            Hint = '120'
            Caption = 'G 120'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 2
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg180: TRadioButton
            Left = 7
            Top = 72
            Width = 52
            Height = 20
            Hint = '180'
            Caption = 'C 180'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 3
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg240: TRadioButton
            Left = 7
            Top = 91
            Width = 52
            Height = 20
            Hint = '240'
            Caption = 'B 240'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 4
            OnClick = RadioButton_deg60baseClick
          end
          object RadioButton_deg300: TRadioButton
            Left = 7
            Top = 111
            Width = 52
            Height = 20
            Hint = '300'
            Caption = 'M 300'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 5
            OnClick = RadioButton_deg60baseClick
          end
          object Button_60BaseInterp: TButton
            Left = 7
            Top = 130
            Width = 52
            Height = 20
            Caption = 'Interp.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = Button_60BaseInterpClick
          end
        end
        object GroupBox_30base: TGroupBox
          Left = 72
          Top = 13
          Width = 72
          Height = 157
          Caption = '30'#176' Base'
          TabOrder = 1
          object RadioButton_deg30: TRadioButton
            Left = 7
            Top = 13
            Width = 59
            Height = 20
            Hint = '30'
            Caption = 'RY 30'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 0
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg90: TRadioButton
            Left = 7
            Top = 33
            Width = 59
            Height = 20
            Hint = '90'
            Caption = 'GY 90'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 1
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg150: TRadioButton
            Left = 7
            Top = 52
            Width = 59
            Height = 20
            Hint = '150'
            Caption = 'GC 150'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 2
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg210: TRadioButton
            Left = 7
            Top = 72
            Width = 59
            Height = 20
            Hint = '210'
            Caption = 'BC 210'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 3
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg270: TRadioButton
            Left = 7
            Top = 91
            Width = 59
            Height = 20
            Hint = '270'
            Caption = 'BM 270'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 4
            OnClick = RadioButton_deg30baseClick
          end
          object RadioButton_deg330: TRadioButton
            Left = 7
            Top = 111
            Width = 59
            Height = 20
            Hint = '330'
            Caption = 'RM 330'#176
            Color = clBtnFace
            ParentColor = False
            TabOrder = 5
            OnClick = RadioButton_deg30baseClick
          end
          object Button_30BaseInterp: TButton
            Left = 7
            Top = 130
            Width = 52
            Height = 20
            Caption = 'Interp.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 6
            OnClick = Button_30BaseInterpClick
          end
        end
      end
      object RadioGroup_Saturation: TRadioGroup
        Left = 7
        Top = 189
        Width = 72
        Height = 85
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
        Left = 85
        Top = 189
        Width = 65
        Height = 85
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
      Left = 8
      Top = 368
      Width = 161
      Height = 21
      TabOrder = 11
      Text = 'RGB Cursor Color'
    end
    object GroupBox_OoG: TGroupBox
      Left = 8
      Top = 544
      Width = 161
      Height = 89
      Caption = 'Out of Gamut Indicator'
      TabOrder = 12
      object CheckBox_OoG: TCheckBox
        Left = 8
        Top = 16
        Width = 89
        Height = 17
        Caption = 'Out of Gamut'
        Color = clBtnFace
        Enabled = False
        ParentColor = False
        TabOrder = 0
      end
      object Button_OoGSetup: TButton
        Left = 96
        Top = 16
        Width = 57
        Height = 17
        Caption = 'Setup'
        TabOrder = 1
        OnClick = Button_OoGSetupClick
      end
      object Edit_TargetCursorColor: TEdit
        Left = 8
        Top = 36
        Width = 145
        Height = 21
        TabOrder = 2
      end
      object Edit_TargetCursorColorHSV: TEdit
        Left = 8
        Top = 56
        Width = 145
        Height = 21
        TabOrder = 3
      end
    end
    object Edit_CursorColorHSV: TEdit
      Left = 8
      Top = 388
      Width = 161
      Height = 21
      TabOrder = 13
      Text = 'HSV Cursor Color'
    end
    object GroupBox7: TGroupBox
      Left = 8
      Top = 632
      Width = 161
      Height = 41
      Caption = 'Turn Point'
      TabOrder = 14
      object Label_TurnPoint: TLabel
        Left = 113
        Top = 16
        Width = 6
        Height = 13
        Caption = '0'
      end
      object ScrollBar_TurnPoint: TScrollBar
        Left = 4
        Top = 16
        Width = 105
        Height = 17
        Max = 15
        PageSize = 0
        Position = 7
        TabOrder = 0
        OnChange = ScrollBar_TurnPointChange
      end
    end
    object CheckBox_SAT_CLIP_EN: TCheckBox
      Left = 504
      Top = 8
      Width = 89
      Height = 17
      Caption = 'SAT_CLIP_EN'
      TabOrder = 15
    end
    object GroupBox8: TGroupBox
      Left = 8
      Top = 416
      Width = 161
      Height = 121
      Caption = 'Memory Color'
      TabOrder = 16
      object RadioButton_CSkin: TRadioButton
        Left = 8
        Top = 16
        Width = 113
        Height = 17
        Hint = '0'
        Caption = 'Caucasian Skin'
        TabOrder = 0
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_OSkin: TRadioButton
        Left = 8
        Top = 32
        Width = 113
        Height = 17
        Hint = '15'
        Caption = 'Oriental Skin'
        TabOrder = 1
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_Orange: TRadioButton
        Left = 8
        Top = 48
        Width = 113
        Height = 17
        Hint = '30'
        Caption = 'Orange'
        TabOrder = 2
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_GreenGrass: TRadioButton
        Left = 8
        Top = 64
        Width = 113
        Height = 17
        Hint = '120'
        Caption = 'Green Grass'
        TabOrder = 3
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_DFoliage: TRadioButton
        Left = 8
        Top = 80
        Width = 113
        Height = 17
        Hint = '135'
        Caption = 'Deciduous Foliage'
        TabOrder = 4
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object RadioButton_BlueSky: TRadioButton
        Left = 8
        Top = 96
        Width = 113
        Height = 17
        Hint = '195'
        Caption = 'Blue Sky'
        TabOrder = 5
        OnClick = RadioButton_MemoryColorClick
        OnMouseDown = RadioButton_MemoryColorMouseDown
      end
      object CheckBox_MemoryColor: TCheckBox
        Left = 80
        Top = -1
        Width = 57
        Height = 17
        Caption = 'Check'
        TabOrder = 6
        Visible = False
      end
    end
    object GroupBox9: TGroupBox
      Left = 181
      Top = 609
      Width = 360
      Height = 61
      TabOrder = 17
      object Label25: TLabel
        Left = 5
        Top = 33
        Width = 47
        Height = 16
        Caption = 'Chroma'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label_Chroma: TLabel
        Left = 332
        Top = 41
        Width = 6
        Height = 13
        Caption = '0'
      end
      object ScrollBar_Chroma: TScrollBar
        Left = 82
        Top = 32
        Width = 244
        Height = 21
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
        Left = 232
        Top = 8
        Width = 49
        Height = 17
        Hint = '[c]'
        Caption = 'Reset'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Button_ChromaResetClick
      end
    end
    object GroupBox_HSVVersion: TGroupBox
      Left = 632
      Top = 8
      Width = 105
      Height = 33
      Caption = 'HSV'
      TabOrder = 18
      object RadioButton_v1: TRadioButton
        Left = 16
        Top = 15
        Width = 57
        Height = 16
        Caption = 'v1'
        TabOrder = 0
      end
      object RadioButton_v2: TRadioButton
        Left = 56
        Top = 15
        Width = 41
        Height = 16
        Caption = 'v2'
        Checked = True
        TabOrder = 1
        TabStop = True
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
