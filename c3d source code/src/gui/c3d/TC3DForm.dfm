object C3DForm1: TC3DForm1
  Left = 58
  Top = 31
  Width = 968
  Height = 858
  Align = alCustom
  Caption = 'C3D lookup table'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  PrintScale = poNone
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lb_c3d_showY: TLabel
    Left = 56
    Top = 354
    Width = 19
    Height = 13
    Caption = 'Y:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showX: TLabel
    Left = 18
    Top = 354
    Width = 19
    Height = 13
    Caption = 'X:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showR: TLabel
    Left = 106
    Top = 354
    Width = 20
    Height = 13
    Caption = 'R:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showG: TLabel
    Left = 144
    Top = 354
    Width = 20
    Height = 13
    Caption = 'G:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showB: TLabel
    Left = 184
    Top = 354
    Width = 19
    Height = 13
    Caption = 'B:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showH: TLabel
    Left = 232
    Top = 354
    Width = 17
    Height = 13
    Caption = 'H:  '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showS: TLabel
    Left = 272
    Top = 354
    Width = 16
    Height = 13
    Caption = 'S:  '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showV: TLabel
    Left = 320
    Top = 354
    Width = 16
    Height = 13
    Caption = 'V:  '
    Color = clCream
    ParentColor = False
  end
  object Label28: TLabel
    Left = 16
    Top = 376
    Width = 70
    Height = 13
    Caption = 'Cursor Color'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object cb_en: TCheckBox
    Left = 16
    Top = 0
    Width = 81
    Height = 25
    Caption = '&Enable'
    TabOrder = 0
    OnClick = cb_enClick
  end
  object cb_demo: TCheckBox
    Left = 96
    Top = 0
    Width = 81
    Height = 25
    Caption = '&Demo'
    TabOrder = 1
  end
  object rg_c3d_hsv_mode: TRadioGroup
    Left = 168
    Top = 504
    Width = 89
    Height = 73
    Caption = 'HSV Dif Mode'
    ItemIndex = 0
    Items.Strings = (
      'HSV'
      'RGB (6 axis)'
      'RGB+hsv dif'
      'HSV+fix')
    TabOrder = 2
  end
  object btn_c3d_load: TButton
    Left = 280
    Top = 576
    Width = 81
    Height = 25
    Caption = 'Load Tbl old'
    TabOrder = 3
    OnClick = btn_c3d_loadClick
  end
  object btn_c3d_save_h: TButton
    Left = 176
    Top = 584
    Width = 81
    Height = 25
    Caption = 'Save Table H'
    TabOrder = 4
    OnClick = btn_c3d_save_hClick
  end
  object btn_c3d_check: TButton
    Left = 280
    Top = 511
    Width = 57
    Height = 21
    Caption = 'Tcon Chk'
    TabOrder = 6
    OnClick = btn_c3d_checkClick
  end
  object GroupBox36: TGroupBox
    Left = 360
    Top = 433
    Width = 201
    Height = 210
    Caption = 'Method'
    TabOrder = 7
    object rb_c3d_point: TRadioButton
      Left = 0
      Top = 40
      Width = 89
      Height = 25
      Caption = 'Point Color'
      Checked = True
      Color = clMoneyGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 0
      TabStop = True
      OnClick = rb_c3d_pointClick
    end
    object rb_c3d_r: TRadioButton
      Left = 0
      Top = 64
      Width = 89
      Height = 25
      Caption = 'Red        0'#176
      Color = clRed
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_y: TRadioButton
      Left = 0
      Top = 88
      Width = 89
      Height = 25
      Caption = 'Yellow    60'#176
      Color = clYellow
      ParentColor = False
      TabOrder = 2
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_g: TRadioButton
      Left = 0
      Top = 112
      Width = 89
      Height = 25
      Caption = 'Green    120'#176
      Color = clGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 3
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_c: TRadioButton
      Left = 0
      Top = 136
      Width = 89
      Height = 25
      Caption = 'Cyan      180'#176
      Color = clAqua
      ParentColor = False
      TabOrder = 4
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_b: TRadioButton
      Left = 0
      Top = 160
      Width = 89
      Height = 25
      Caption = 'Blue       240'#176
      Color = clBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 5
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_m: TRadioButton
      Left = 0
      Top = 184
      Width = 89
      Height = 25
      Caption = 'Magenta300'#176
      Color = clFuchsia
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -9
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 6
      OnClick = rb_c3d_colorClick
    end
    object sg_c3d_hsvi: TStringGrid
      Left = 84
      Top = 40
      Width = 114
      Height = 172
      ColCount = 3
      DefaultColWidth = 36
      DefaultRowHeight = 23
      FixedCols = 0
      RowCount = 7
      FixedRows = 0
      TabOrder = 7
    end
    object StaticText34: TStaticText
      Left = 84
      Top = 24
      Width = 38
      Height = 17
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Hue'
      TabOrder = 8
    end
    object StaticText35: TStaticText
      Left = 122
      Top = 24
      Width = 38
      Height = 17
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Sat'
      TabOrder = 9
    end
    object StaticText36: TStaticText
      Left = 160
      Top = 24
      Width = 37
      Height = 17
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Bright'
      TabOrder = 10
    end
    object StaticText37: TStaticText
      Left = 160
      Top = 8
      Width = 38
      Height = 17
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Intenst'
      TabOrder = 11
      Visible = False
    end
  end
  object GroupBox38: TGroupBox
    Left = 280
    Top = 440
    Width = 81
    Height = 33
    Caption = 'table index'
    TabOrder = 9
    object Label231: TLabel
      Left = 8
      Top = 16
      Width = 6
      Height = 13
      Caption = 'r:'
    end
    object lb_c3d_tbl_ir: TLabel
      Left = 16
      Top = 16
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label233: TLabel
      Left = 32
      Top = 16
      Width = 9
      Height = 13
      Caption = 'g:'
    end
    object lb_c3d_tbl_ig: TLabel
      Left = 40
      Top = 16
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label235: TLabel
      Left = 56
      Top = 16
      Width = 9
      Height = 13
      Caption = 'b:'
    end
    object lb_c3d_tbl_ib: TLabel
      Left = 64
      Top = 16
      Width = 6
      Height = 13
      Caption = '0'
    end
  end
  object rg_c3d_interpl: TRadioGroup
    Left = 160
    Top = 456
    Width = 104
    Height = 33
    Caption = 'rg_c3d_interpl'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      '4'
      '8')
    TabOrder = 10
    Visible = False
    OnClick = rg_c3d_interplClick
  end
  object btn_tbl_search: TButton
    Left = 280
    Top = 536
    Width = 57
    Height = 25
    Caption = 'tbl_search'
    TabOrder = 11
    OnClick = btn_tbl_searchClick
  end
  object btn_directly_sim: TButton
    Left = 280
    Top = 608
    Width = 73
    Height = 25
    Caption = 'Directly Sim'
    TabOrder = 12
    OnClick = btn_directly_simClick
  end
  object LabeledEdit1: TLabeledEdit
    Left = 312
    Top = 400
    Width = 41
    Height = 24
    EditLabel.Width = 41
    EditLabel.Height = 10
    EditLabel.Caption = 'Show Hue'
    EditLabel.OnClick = LabeledEdit1SubLabelClick
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 13
    Text = '0'
    Visible = False
  end
  object BitBtn2: TBitBtn
    Left = 360
    Top = 400
    Width = 33
    Height = 17
    Caption = 'ok'
    TabOrder = 14
    Visible = False
    OnClick = BitBtn2Click
  end
  object edt_show_h: TEdit
    Left = 560
    Top = 608
    Width = 41
    Height = 24
    TabOrder = 15
    Visible = False
  end
  object rg_c3d_TblSize: TRadioGroup
    Left = 632
    Top = 352
    Width = 145
    Height = 49
    Caption = 'Table Size'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      '9x9x9'
      '7x7x7'
      '17x17x17'
      '33x33x33')
    TabOrder = 16
    OnClick = rg_c3d_TblSizeClick
  end
  object cb_sim_type: TComboBox
    Left = 280
    Top = 480
    Width = 49
    Height = 21
    ItemHeight = 13
    TabOrder = 17
    Text = 'cb_sim_type'
    Items.Strings = (
      'Simple'
      'rgb diff (1)'
      'w diff (1)'
      'g diff (2) '
      'gw diff (1)'
      'dH/ dS/ dV'
      'NCTU diff'
      'NCTU modified')
  end
  object rg_Sat_smooth: TRadioGroup
    Left = 632
    Top = 448
    Width = 129
    Height = 89
    Caption = 'Saturation Smooth'
    ItemIndex = 3
    Items.Strings = (
      'Fix Gain'
      'Linaer Gain'
      'Gaussian distr'
      'New Gauss 1-gain')
    TabOrder = 8
  end
  object rg_v_smooth2gray: TRadioGroup
    Left = 632
    Top = 408
    Width = 105
    Height = 33
    Caption = 'VSmoothG'
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      'off'
      'on')
    TabOrder = 5
  end
  object pc_Adjust: TPageControl
    Left = 136
    Top = 366
    Width = 489
    Height = 299
    ActivePage = TabSheet20
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MultiLine = True
    ParentFont = False
    TabIndex = 0
    TabOrder = 18
    OnChange = pc_AdjustChange
    object TabSheet20: TTabSheet
      Caption = '&Global Color Adjust'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      object pc_global_adj: TPageControl
        Left = 0
        Top = 0
        Width = 481
        Height = 273
        ActivePage = TabSheet7
        TabIndex = 0
        TabOrder = 0
        OnChange = pc_global_adjChange
        object TabSheet7: TTabSheet
          Caption = '&Auto 729 Color Adjust'
          object GroupBox20: TGroupBox
            Left = 0
            Top = 8
            Width = 385
            Height = 137
            Caption = 'Source Panel'
            TabOrder = 0
            object GroupBox21: TGroupBox
              Left = 88
              Top = 16
              Width = 185
              Height = 113
              Caption = 'RGB2XYZ Matrix'
              TabOrder = 0
              object edt_auto_rgb2xyz11: TEdit
                Left = 16
                Top = 16
                Width = 49
                Height = 24
                TabOrder = 0
              end
              object edt_auto_rgb2xyz12: TEdit
                Left = 72
                Top = 16
                Width = 49
                Height = 24
                TabOrder = 1
              end
              object edt_auto_rgb2xyz13: TEdit
                Left = 128
                Top = 16
                Width = 49
                Height = 24
                TabOrder = 2
              end
              object edt_auto_rgb2xyz21: TEdit
                Left = 16
                Top = 48
                Width = 49
                Height = 24
                TabOrder = 3
              end
              object edt_auto_rgb2xyz22: TEdit
                Left = 72
                Top = 48
                Width = 49
                Height = 24
                TabOrder = 4
              end
              object edt_auto_rgb2xyz23: TEdit
                Left = 128
                Top = 48
                Width = 49
                Height = 24
                TabOrder = 5
              end
              object edt_auto_rgb2xyz31: TEdit
                Left = 16
                Top = 80
                Width = 49
                Height = 24
                TabOrder = 6
              end
              object edt_auto_rgb2xyz32: TEdit
                Left = 72
                Top = 80
                Width = 49
                Height = 24
                TabOrder = 7
              end
              object edt_auto_rgb2xyz33: TEdit
                Left = 128
                Top = 80
                Width = 49
                Height = 24
                TabOrder = 8
              end
            end
            object GroupBox23: TGroupBox
              Left = 288
              Top = 16
              Width = 81
              Height = 113
              Caption = 'Gamma'
              TabOrder = 1
              object lble_auto_Gm_R: TLabeledEdit
                Left = 24
                Top = 16
                Width = 41
                Height = 24
                EditLabel.Width = 8
                EditLabel.Height = 13
                EditLabel.Caption = 'R'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 0
              end
              object lble_auto_Gm_G: TLabeledEdit
                Left = 24
                Top = 48
                Width = 41
                Height = 24
                EditLabel.Width = 8
                EditLabel.Height = 13
                EditLabel.Caption = 'G'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 1
              end
              object lble_auto_Gm_B: TLabeledEdit
                Left = 24
                Top = 80
                Width = 41
                Height = 24
                EditLabel.Width = 7
                EditLabel.Height = 13
                EditLabel.Caption = 'B'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 2
              end
            end
            object btn_Auto_Src_Load: TButton
              Left = 16
              Top = 40
              Width = 65
              Height = 25
              Caption = 'Load Data'
              TabOrder = 2
              OnClick = btn_Auto_Src_LoadClick
            end
            object btn_Auto_Src_Calc: TButton
              Left = 16
              Top = 88
              Width = 65
              Height = 25
              Caption = 'Calculate'
              Enabled = False
              TabOrder = 3
              OnClick = btn_Auto_Src_CalcClick
            end
          end
          object GroupBox24: TGroupBox
            Left = 0
            Top = 156
            Width = 385
            Height = 77
            Caption = 'Target Panel'
            TabOrder = 1
            object btn_Auto_Trg_Load: TButton
              Left = 64
              Top = 32
              Width = 65
              Height = 25
              Caption = 'Load Data'
              TabOrder = 0
              OnClick = btn_Auto_Trg_LoadClick
            end
            object GroupBox26: TGroupBox
              Left = 248
              Top = 0
              Width = 137
              Height = 73
              Caption = 'Smooth Color Translation'
              TabOrder = 1
              Visible = False
              object LabeledEdit5: TLabeledEdit
                Left = 72
                Top = 16
                Width = 41
                Height = 24
                EditLabel.Width = 42
                EditLabel.Height = 13
                EditLabel.Caption = 'Distance'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 0
              end
              object Button6: TButton
                Left = 40
                Top = 40
                Width = 49
                Height = 25
                Caption = 'Run'
                TabOrder = 1
              end
            end
            object btn_Auto_Trg_BuildTbl: TButton
              Left = 160
              Top = 32
              Width = 65
              Height = 25
              Caption = 'Build Table'
              Enabled = False
              TabOrder = 2
              OnClick = btn_Auto_Trg_BuildTblClick
            end
          end
        end
        object TabSheet8: TTabSheet
          Caption = '&Manual 39 Color Adjust'
          ImageIndex = 1
          object pc_HuePage_Grid: TPageControl
            Left = 320
            Top = -24
            Width = 209
            Height = 291
            ActivePage = ts_light12
            MultiLine = True
            TabIndex = 0
            TabOrder = 0
            TabWidth = 51
            object ts_light12: TTabSheet
              Caption = 'Light 12 '
              object sg_12color1: TStringGrid
                Left = 0
                Top = 0
                Width = 145
                Height = 279
                ColCount = 4
                DefaultColWidth = 34
                DefaultRowHeight = 18
                RowCount = 13
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goRowSelect]
                TabOrder = 0
                OnDrawCell = sg_12color1DrawCell
                OnSelectCell = sg_12color1SelectCell
                ColWidths = (
                  34
                  34
                  34
                  34)
                RowHeights = (
                  18
                  18
                  18
                  17
                  18
                  18
                  18
                  18
                  18
                  18
                  18
                  18
                  18)
              end
            end
            object ts_middle12: TTabSheet
              Caption = 'Middle 12 '
              ImageIndex = 1
              object sg_12color2: TStringGrid
                Left = 0
                Top = -2
                Width = 145
                Height = 257
                ColCount = 4
                DefaultColWidth = 34
                DefaultRowHeight = 18
                RowCount = 13
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goRowSelect]
                TabOrder = 0
                OnDrawCell = sg_12color2DrawCell
                OnMouseDown = sg_12color2MouseDown
                OnSelectCell = sg_12color2SelectCell
              end
            end
            object ts_dark6: TTabSheet
              Caption = 'Dark6'
              ImageIndex = 2
              object btn_dark: TButton
                Left = 8
                Top = 176
                Width = 73
                Height = 25
                Caption = 'Dark < 64'
                TabOrder = 0
                Visible = False
                OnClick = btn_darkClick
              end
              object sg_Dark: TStringGrid
                Left = 0
                Top = -2
                Width = 145
                Height = 137
                ColCount = 4
                DefaultColWidth = 34
                DefaultRowHeight = 18
                RowCount = 7
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goRowSelect]
                TabOrder = 1
                OnDrawCell = sg_DarkDrawCell
                OnSelectCell = sg_DarkSelectCell
                RowHeights = (
                  18
                  18
                  18
                  18
                  18
                  18
                  18)
              end
            end
            object ts_gray9: TTabSheet
              Caption = 'Gray9'
              ImageIndex = 3
              object sg_Gray: TStringGrid
                Left = 0
                Top = -2
                Width = 145
                Height = 193
                ColCount = 4
                DefaultColWidth = 34
                DefaultRowHeight = 18
                RowCount = 10
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goTabs, goRowSelect]
                TabOrder = 0
                OnDrawCell = sg_GrayDrawCell
                OnSelectCell = sg_GraySelectCell
                ColWidths = (
                  34
                  34
                  34
                  34)
                RowHeights = (
                  18
                  18
                  18
                  18
                  18
                  18
                  18
                  18
                  18
                  18)
              end
            end
          end
          object gb_c3d_HSI_adj: TGroupBox
            Left = 0
            Top = 68
            Width = 322
            Height = 173
            TabOrder = 1
            object GroupBox40: TGroupBox
              Left = 0
              Top = 0
              Width = 321
              Height = 65
              TabOrder = 0
              object lb_c3d_Manual39_h: TLabel
                Left = 272
                Top = 32
                Width = 10
                Height = 13
                Caption = '0'#176
              end
              object Label197: TLabel
                Left = 8
                Top = 24
                Width = 20
                Height = 13
                Caption = 'Hue'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -12
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Manual39_h: TScrollBar
                Left = 50
                Top = 32
                Width = 200
                Height = 17
                Max = 120
                PageSize = 0
                Position = 60
                TabOrder = 0
                OnChange = sb_c3d_Manual39_hChange
              end
              object Edit_c3d_Manual39_h_adj: TEdit
                Left = 72
                Top = 8
                Width = 41
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
            end
            object GroupBox41: TGroupBox
              Left = 0
              Top = 56
              Width = 321
              Height = 62
              TabOrder = 1
              object lb_c3d_Manual39_s: TLabel
                Left = 272
                Top = 32
                Width = 6
                Height = 13
                Caption = '0'
              end
              object Label207: TLabel
                Left = 8
                Top = 24
                Width = 45
                Height = 13
                Caption = 'Satuation'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -12
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Manual39_s: TScrollBar
                Left = 50
                Top = 38
                Width = 200
                Height = 17
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 0
                OnChange = sb_c3d_Manual39_sChange
              end
              object edt_c3d_satC: TEdit
                Left = 291
                Top = 12
                Width = 24
                Height = 24
                Hint = 'constant'
                ParentShowHint = False
                ShowHint = True
                TabOrder = 1
                Text = '1.5'
                Visible = False
              end
              object Edit_c3d_Manual39_s_adj: TEdit
                Left = 72
                Top = 8
                Width = 41
                Height = 24
                ReadOnly = True
                TabOrder = 2
                Text = '0'
              end
            end
            object GroupBox7: TGroupBox
              Left = 0
              Top = 111
              Width = 319
              Height = 59
              TabOrder = 2
              object lb_c3d_Manual39_v: TLabel
                Left = 277
                Top = 33
                Width = 6
                Height = 13
                Caption = '0'
              end
              object Label25: TLabel
                Left = 4
                Top = 33
                Width = 49
                Height = 13
                Caption = 'Brightness'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -12
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Manual39_v: TScrollBar
                Left = 56
                Top = 29
                Width = 201
                Height = 17
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 0
                OnChange = sb_c3d_Manual39_vChange
              end
              object Edit_c3d_Manual39_v_adj: TEdit
                Left = 72
                Top = 7
                Width = 41
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
              object edt_c3d_valC: TEdit
                Left = 288
                Top = 7
                Width = 25
                Height = 24
                Hint = 'constant'
                ParentShowHint = False
                ShowHint = True
                TabOrder = 2
                Text = '2'
                Visible = False
              end
            end
          end
          object lbe_sat_sigma_light: TLabeledEdit
            Left = 326
            Top = 224
            Width = 32
            Height = 24
            EditLabel.Width = 109
            EditLabel.Height = 13
            EditLabel.Caption = 'Saturation Light Sigma '
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 2
            Text = '0.35'
            Visible = False
            OnChange = lbe_sat_sigma_lightChange
          end
          object rg_manual_39_choice: TRadioGroup
            Left = 136
            Top = 0
            Width = 185
            Height = 57
            Caption = 'Manual 39 Color'
            Columns = 2
            ItemIndex = 0
            Items.Strings = (
              'Light 12'
              'Middle 12'
              'Dark 6'
              'Gray 9')
            TabOrder = 3
            OnClick = rg_manual_39_choiceClick
          end
        end
      end
    end
    object TabSheet22: TTabSheet
      Caption = '&Point Color Adjust'
      ImageIndex = 1
      object Label27: TLabel
        Left = 352
        Top = 16
        Width = 63
        Height = 13
        Caption = 'Point Color'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object pc_point_color_adj: TPageControl
        Left = 0
        Top = 0
        Width = 337
        Height = 273
        ActivePage = TabSheet10
        TabIndex = 1
        TabOrder = 0
        object TabSheet9: TTabSheet
          Caption = '&RGB Domain'
          object Label1: TLabel
            Left = 373
            Top = 8
            Width = 108
            Height = 13
            Caption = 'Point Color Record'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -12
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Visible = False
          end
          object btn_LoadRecord: TButton
            Left = 384
            Top = 220
            Width = 73
            Height = 25
            Caption = 'Load Record'
            TabOrder = 0
            Visible = False
            OnClick = btn_LoadRecordClick
          end
          object btn_AddPoint: TButton
            Left = 384
            Top = 192
            Width = 73
            Height = 25
            Caption = 'Add Point'
            TabOrder = 1
            Visible = False
            OnClick = btn_AddPointClick
          end
          object btn_SaveRecord: TButton
            Left = 464
            Top = 220
            Width = 73
            Height = 25
            Caption = 'Save Record'
            TabOrder = 2
            Visible = False
            OnClick = btn_SaveRecordClick
          end
          object btn_DeletePoint: TButton
            Left = 464
            Top = 192
            Width = 73
            Height = 25
            Caption = 'Delete Point'
            TabOrder = 3
            Visible = False
            OnClick = btn_DeletePointClick
          end
          object ListBox_PointColor: TListBox
            Left = 376
            Top = 24
            Width = 161
            Height = 161
            ItemHeight = 16
            TabOrder = 4
            Visible = False
            OnClick = ListBox_PointColorClick
          end
          object gb_c3d_RGB_adj: TGroupBox
            Left = 0
            Top = 4
            Width = 329
            Height = 237
            TabOrder = 5
            object Label181: TLabel
              Left = 16
              Top = 32
              Width = 42
              Height = 13
              Caption = 'Distance'
            end
            object lb_c3d_rgb_dis: TLabel
              Left = 291
              Top = 32
              Width = 6
              Height = 13
              Caption = '0'
            end
            object sb_c3d_rgb_dis: TScrollBar
              Left = 67
              Top = 32
              Width = 201
              Height = 17
              Max = 10
              PageSize = 0
              TabOrder = 0
              OnChange = sb_c3d_rgb_disChange
            end
            object rg_PCrgb_choose: TRadioGroup
              Left = 8
              Top = 72
              Width = 137
              Height = 41
              Caption = 'RGB/HSV Adjust'
              Columns = 2
              ItemIndex = 0
              Items.Strings = (
                'RGB'
                'HSV')
              TabOrder = 1
              OnClick = rg_PCrgb_chooseClick
            end
            object gb_PCrgb_hsv: TGroupBox
              Left = 0
              Top = 128
              Width = 329
              Height = 105
              Caption = 'HSV'
              TabOrder = 2
              object lb_c3d_hsv_v: TLabel
                Left = 288
                Top = 84
                Width = 6
                Height = 13
                Caption = '0'
              end
              object Label188: TLabel
                Left = 5
                Top = 84
                Width = 49
                Height = 13
                Caption = 'Brightness'
              end
              object lb_c3d_hsv_s: TLabel
                Left = 288
                Top = 48
                Width = 6
                Height = 13
                Caption = '0'
              end
              object lb_c3d_hsv_h: TLabel
                Left = 288
                Top = 16
                Width = 6
                Height = 13
                Caption = '0'
              end
              object Label186: TLabel
                Left = 16
                Top = 16
                Width = 20
                Height = 13
                Caption = 'Hue'
              end
              object Label187: TLabel
                Left = 3
                Top = 48
                Width = 57
                Height = 13
                Caption = 'Sataturation'
              end
              object sb_c3d_hsv_v: TScrollBar
                Left = 64
                Top = 80
                Width = 201
                Height = 17
                PageSize = 0
                Position = 50
                TabOrder = 0
                OnChange = sb_c3d_hsv_Change
              end
              object sb_c3d_hsv_s: TScrollBar
                Left = 64
                Top = 48
                Width = 201
                Height = 17
                PageSize = 0
                Position = 50
                TabOrder = 1
                OnChange = sb_c3d_hsv_Change
              end
              object sb_c3d_hsv_h: TScrollBar
                Left = 64
                Top = 16
                Width = 201
                Height = 17
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 2
                OnChange = sb_c3d_hsv_Change
              end
            end
            object gb_PCrgb_rgb: TGroupBox
              Left = 0
              Top = 128
              Width = 329
              Height = 105
              Caption = 'RGB'
              TabOrder = 3
              object Label182: TLabel
                Left = 24
                Top = 16
                Width = 20
                Height = 13
                Caption = 'Red'
              end
              object lb_c3d_rgb_r: TLabel
                Left = 288
                Top = 16
                Width = 6
                Height = 13
                Caption = '0'
              end
              object lb_c3d_rgb_g: TLabel
                Left = 288
                Top = 48
                Width = 6
                Height = 13
                Caption = '0'
              end
              object Label183: TLabel
                Left = 16
                Top = 48
                Width = 29
                Height = 13
                Caption = 'Green'
              end
              object Label184: TLabel
                Left = 24
                Top = 84
                Width = 21
                Height = 13
                Caption = 'Blue'
              end
              object lb_c3d_rgb_b: TLabel
                Left = 288
                Top = 84
                Width = 6
                Height = 13
                Caption = '0'
              end
              object sb_c3d_rgb_r: TScrollBar
                Left = 64
                Top = 16
                Width = 201
                Height = 17
                PageSize = 0
                Position = 50
                TabOrder = 0
                OnChange = sb_c3d_rgb_rChange
              end
              object sb_c3d_rgb_g: TScrollBar
                Left = 64
                Top = 48
                Width = 201
                Height = 17
                PageSize = 0
                Position = 50
                TabOrder = 1
                OnChange = sb_c3d_rgb_gChange
              end
              object sb_c3d_rgb_b: TScrollBar
                Left = 64
                Top = 80
                Width = 201
                Height = 17
                PageSize = 0
                Position = 50
                TabOrder = 2
                OnChange = sb_c3d_rgb_bChange
              end
            end
          end
        end
        object TabSheet10: TTabSheet
          Caption = '&HSV Domain'
          ImageIndex = 1
          object GroupBox1: TGroupBox
            Left = 0
            Top = 4
            Width = 329
            Height = 85
            TabOrder = 0
            object Label204: TLabel
              Left = 257
              Top = 32
              Width = 24
              Height = 13
              Caption = '(Pos)'
            end
            object Label203: TLabel
              Left = 50
              Top = 32
              Width = 26
              Height = 13
              Caption = '(Neg)'
            end
            object lb_c3d_Point_HSV_hdn: TLabel
              Left = 41
              Top = 16
              Width = 19
              Height = 13
              Caption = '-30'#176
            end
            object Label185: TLabel
              Left = 3
              Top = -2
              Width = 53
              Height = 13
              Caption = 'Diffusion    '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object lb_c3d_Point_HSV_hdp: TLabel
              Left = 273
              Top = 16
              Width = 16
              Height = 13
              Caption = '30'#176
            end
            object Label2: TLabel
              Left = 8
              Top = 16
              Width = 20
              Height = 13
              Caption = 'Hue'
            end
            object Label3: TLabel
              Left = 8
              Top = 48
              Width = 25
              Height = 13
              Caption = 'S/ V '
            end
            object lb_c3d_Point_HSV_svd: TLabel
              Left = 280
              Top = 48
              Width = 6
              Height = 13
              Caption = '1'
            end
            object sb_c3d_Point_HSV_hdn: TScrollBar
              Left = 64
              Top = 16
              Width = 100
              Height = 17
              PageSize = 0
              Position = 70
              TabOrder = 0
              OnChange = sb_c3d_Point_HSV_hdnChange
            end
            object sb_c3d_Point_HSV_hdp: TScrollBar
              Left = 165
              Top = 16
              Width = 100
              Height = 17
              PageSize = 0
              Position = 30
              TabOrder = 1
              OnChange = sb_c3d_Point_HSV_hdpChange
            end
            object sb_c3d_Point_HSV_svd: TScrollBar
              Left = 64
              Top = 48
              Width = 201
              Height = 17
              Max = 10
              PageSize = 0
              Position = 10
              TabOrder = 2
              OnChange = sb_c3d_Point_HSV_svdChange
            end
          end
          object GroupBox4: TGroupBox
            Left = 0
            Top = 72
            Width = 329
            Height = 169
            TabOrder = 1
            object lb_c3d_Point_HSV_v: TLabel
              Left = 277
              Top = 144
              Width = 6
              Height = 13
              Caption = '0'
            end
            object Label5: TLabel
              Left = 4
              Top = 128
              Width = 49
              Height = 13
              Caption = 'Brightness'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -12
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object GroupBox5: TGroupBox
              Left = 0
              Top = 0
              Width = 329
              Height = 65
              TabOrder = 0
              object lb_c3d_Point_HSV_h: TLabel
                Left = 272
                Top = 32
                Width = 10
                Height = 13
                Caption = '0'#176
              end
              object Label7: TLabel
                Left = 16
                Top = 16
                Width = 20
                Height = 13
                Caption = 'Hue'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -12
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Point_HSV_h: TScrollBar
                Left = 56
                Top = 32
                Width = 201
                Height = 17
                Max = 120
                PageSize = 0
                Position = 60
                TabOrder = 0
                OnChange = sb_c3d_Point_HSV_hChange
              end
              object Edit_c3d_Point_HSV_h_adj: TEdit
                Left = 72
                Top = 8
                Width = 41
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
              object cb_c3d_Point_HSV_h_g: TCheckBox
                Left = 128
                Top = 12
                Width = 57
                Height = 17
                Caption = 'Global'
                TabOrder = 2
              end
            end
            object GroupBox6: TGroupBox
              Left = 0
              Top = 56
              Width = 329
              Height = 57
              TabOrder = 1
              object lb_c3d_Point_HSV_s: TLabel
                Left = 272
                Top = 32
                Width = 6
                Height = 13
                Caption = '0'
              end
              object Label10: TLabel
                Left = 8
                Top = 16
                Width = 45
                Height = 13
                Caption = 'Satuation'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -12
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Point_HSV_s: TScrollBar
                Left = 56
                Top = 32
                Width = 201
                Height = 17
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 0
                OnChange = sb_c3d_Point_HSV_sChange
              end
              object Edit_c3d_Point_HSV_s_adj: TEdit
                Left = 72
                Top = 8
                Width = 41
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
              object cb_c3d_Point_HSV_s_g: TCheckBox
                Left = 128
                Top = 12
                Width = 57
                Height = 17
                Caption = 'Global'
                TabOrder = 2
              end
            end
            object Edit_c3d_Point_HSV_v_adj: TEdit
              Left = 72
              Top = 120
              Width = 41
              Height = 24
              ReadOnly = True
              TabOrder = 2
              Text = '0'
            end
            object sb_c3d_Point_HSV_v: TScrollBar
              Left = 56
              Top = 144
              Width = 201
              Height = 17
              Max = 200
              PageSize = 0
              Position = 100
              TabOrder = 3
              OnChange = sb_c3d_Point_HSV_vChange
            end
            object cb_c3d_Point_HSV_v_g: TCheckBox
              Left = 128
              Top = 124
              Width = 57
              Height = 17
              Caption = 'Global'
              TabOrder = 4
            end
          end
        end
      end
      object sg_rgb_input: TStringGrid
        Left = 352
        Top = 32
        Width = 111
        Height = 40
        ColCount = 3
        DefaultColWidth = 35
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 1
      end
      object btn_key_in_HSV: TBitBtn
        Left = 408
        Top = 80
        Width = 49
        Height = 17
        Caption = 'HSV GO'
        TabOrder = 2
        Visible = False
        OnClick = btn_key_in_HSVClick
      end
      object btn_key_in_RGB: TBitBtn
        Left = 384
        Top = 80
        Width = 73
        Height = 25
        Hint = 'Click to show color in "Colors" page'
        Caption = 'Show RGB'
        TabOrder = 3
        OnClick = btn_key_in_RGBClick
      end
      object rg_PointNum: TRadioGroup
        Left = 352
        Top = 160
        Width = 121
        Height = 57
        Caption = 'Adjust Point'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        Items.Strings = (
          '1 color (composite)'
          '4 color (table point)')
        ParentFont = False
        TabOrder = 4
        Visible = False
        OnClick = rg_PointNumClick
      end
      object btn_show_4_color: TButton
        Left = 384
        Top = 112
        Width = 73
        Height = 25
        Caption = 'Show 4 Node'
        TabOrder = 5
        OnClick = btn_show_4_colorClick
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Table Step'
      ImageIndex = 2
      TabVisible = False
      object sg_table_step: TStringGrid
        Left = 8
        Top = 24
        Width = 329
        Height = 57
        ColCount = 9
        DefaultColWidth = 35
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 0
        OnKeyDown = sg_table_stepKeyDown
      end
      object BitBtn1: TBitBtn
        Left = 272
        Top = 88
        Width = 57
        Height = 25
        Caption = 'Done'
        TabOrder = 1
        OnClick = BitBtn1Click
      end
      object btn_sim_by_val: TButton
        Left = 16
        Top = 128
        Width = 81
        Height = 33
        Caption = 'sim by value'
        TabOrder = 2
        OnClick = btn_sim_by_valClick
      end
      object btn_dirSim_by_val: TButton
        Left = 120
        Top = 128
        Width = 81
        Height = 33
        Caption = 'dirsim by value'
        TabOrder = 3
        OnClick = btn_dirSim_by_valClick
      end
    end
  end
  object PageControl7: TPageControl
    Left = 448
    Top = -18
    Width = 177
    Height = 402
    ActivePage = TabSheet23
    TabIndex = 0
    TabOrder = 19
    TabWidth = 189
    object TabSheet23: TTabSheet
      Caption = 'Point Color'
      object GroupBox44: TGroupBox
        Left = 0
        Top = 0
        Width = 169
        Height = 372
        TabOrder = 0
        object GroupBox34: TGroupBox
          Left = 0
          Top = 0
          Width = 169
          Height = 185
          Caption = 'Point Color'
          Enabled = False
          TabOrder = 0
          object Img_c3d_sel: TImage
            Left = 0
            Top = 14
            Width = 169
            Height = 137
          end
          object lb_c3d_selR: TLabel
            Left = 24
            Top = 152
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selH: TLabel
            Left = 24
            Top = 168
            Width = 6
            Height = 13
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selG: TLabel
            Left = 80
            Top = 152
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selB: TLabel
            Left = 136
            Top = 152
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selV: TLabel
            Left = 136
            Top = 168
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selS: TLabel
            Left = 80
            Top = 168
            Width = 6
            Height = 13
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selI: TLabel
            Left = 152
            Top = 136
            Width = 12
            Height = 13
            Caption = '    '
            Color = clCream
            ParentColor = False
            Visible = False
          end
          object Label190: TLabel
            Left = 10
            Top = 152
            Width = 11
            Height = 13
            Caption = 'R:'
          end
          object Label198: TLabel
            Left = 66
            Top = 152
            Width = 11
            Height = 13
            Caption = 'G:'
          end
          object Label202: TLabel
            Left = 122
            Top = 152
            Width = 10
            Height = 13
            Caption = 'B:'
          end
          object Label206: TLabel
            Left = 10
            Top = 168
            Width = 11
            Height = 13
            Caption = 'H:'
          end
          object Label208: TLabel
            Left = 66
            Top = 168
            Width = 10
            Height = 13
            Caption = 'S:'
          end
          object Label209: TLabel
            Left = 138
            Top = 136
            Width = 9
            Height = 13
            Caption = ' I:'
            Visible = False
          end
          object Label213: TLabel
            Left = 122
            Top = 168
            Width = 10
            Height = 13
            Caption = 'V:'
          end
        end
        object GroupBox45: TGroupBox
          Left = 0
          Top = 186
          Width = 169
          Height = 185
          Caption = 'Simulate Color'
          Enabled = False
          TabOrder = 1
          object lb_c3d_simR: TLabel
            Left = 24
            Top = 152
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simH: TLabel
            Left = 24
            Top = 168
            Width = 6
            Height = 13
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simG: TLabel
            Left = 80
            Top = 152
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simB: TLabel
            Left = 136
            Top = 152
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simV: TLabel
            Left = 137
            Top = 168
            Width = 18
            Height = 13
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simS: TLabel
            Left = 80
            Top = 168
            Width = 6
            Height = 13
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simI: TLabel
            Left = 144
            Top = 128
            Width = 12
            Height = 13
            Caption = '    '
            Color = clCream
            ParentColor = False
            Visible = False
          end
          object Label246: TLabel
            Left = 10
            Top = 152
            Width = 11
            Height = 13
            Caption = 'R:'
          end
          object Label247: TLabel
            Left = 66
            Top = 152
            Width = 11
            Height = 13
            Caption = 'G:'
          end
          object Label248: TLabel
            Left = 122
            Top = 152
            Width = 10
            Height = 13
            Caption = 'B:'
          end
          object Label249: TLabel
            Left = 10
            Top = 168
            Width = 11
            Height = 13
            Caption = 'H:'
          end
          object Label250: TLabel
            Left = 66
            Top = 168
            Width = 10
            Height = 13
            Caption = 'S:'
          end
          object Label251: TLabel
            Left = 130
            Top = 128
            Width = 9
            Height = 13
            Caption = ' I:'
            Visible = False
          end
          object Label252: TLabel
            Left = 122
            Top = 168
            Width = 10
            Height = 13
            Caption = 'V:'
          end
          object Img_c3d_sim: TImage
            Left = 0
            Top = 14
            Width = 169
            Height = 137
          end
        end
      end
    end
    object TabSheet24: TTabSheet
      Caption = 'Debug-modified'
      ImageIndex = 1
      TabVisible = False
      object GroupBox22: TGroupBox
        Left = 8
        Top = -2
        Width = 161
        Height = 377
        TabOrder = 0
        object GroupBox35: TGroupBox
          Left = 0
          Top = 0
          Width = 161
          Height = 185
          Caption = 'Matrix RGB'
          Enabled = False
          TabOrder = 0
          object Img_c3d_tbl: TImage
            Left = 8
            Top = 16
            Width = 145
            Height = 113
          end
          object lb_c3d_tblR: TLabel
            Left = 24
            Top = 136
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblG: TLabel
            Left = 24
            Top = 152
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblB: TLabel
            Left = 24
            Top = 168
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblH: TLabel
            Left = 80
            Top = 136
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblS: TLabel
            Left = 80
            Top = 152
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblI: TLabel
            Left = 80
            Top = 168
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblV: TLabel
            Left = 129
            Top = 136
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object Label215: TLabel
            Left = 10
            Top = 136
            Width = 11
            Height = 13
            Caption = 'R:'
          end
          object Label216: TLabel
            Left = 8
            Top = 152
            Width = 11
            Height = 13
            Caption = 'G:'
          end
          object Label219: TLabel
            Left = 8
            Top = 168
            Width = 10
            Height = 13
            Caption = 'B:'
          end
          object Label220: TLabel
            Left = 66
            Top = 136
            Width = 11
            Height = 13
            Caption = 'H:'
          end
          object Label221: TLabel
            Left = 64
            Top = 152
            Width = 10
            Height = 13
            Caption = 'S:'
          end
          object Label222: TLabel
            Left = 64
            Top = 168
            Width = 9
            Height = 13
            Caption = ' I:'
          end
          object Label223: TLabel
            Left = 118
            Top = 136
            Width = 10
            Height = 13
            Caption = 'V:'
          end
        end
        object GroupBox37: TGroupBox
          Left = 0
          Top = 192
          Width = 161
          Height = 185
          Caption = 'Correction RGB'
          Enabled = False
          TabOrder = 1
          object Img_c3d_cor: TImage
            Left = 8
            Top = 16
            Width = 145
            Height = 113
          end
          object lb_c3d_corG: TLabel
            Left = 24
            Top = 152
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corB: TLabel
            Left = 24
            Top = 168
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corH: TLabel
            Left = 80
            Top = 136
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corS: TLabel
            Left = 80
            Top = 152
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corI: TLabel
            Left = 80
            Top = 168
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corV: TLabel
            Left = 129
            Top = 136
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corR: TLabel
            Left = 24
            Top = 136
            Width = 15
            Height = 13
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object Label224: TLabel
            Left = 10
            Top = 136
            Width = 11
            Height = 13
            Caption = 'R:'
          end
          object Label225: TLabel
            Left = 8
            Top = 152
            Width = 11
            Height = 13
            Caption = 'G:'
          end
          object Label226: TLabel
            Left = 8
            Top = 168
            Width = 10
            Height = 13
            Caption = 'B:'
          end
          object Label227: TLabel
            Left = 66
            Top = 136
            Width = 11
            Height = 13
            Caption = 'H:'
          end
          object Label228: TLabel
            Left = 64
            Top = 152
            Width = 10
            Height = 13
            Caption = 'S:'
          end
          object Label229: TLabel
            Left = 64
            Top = 168
            Width = 9
            Height = 13
            Caption = ' I:'
          end
          object Label230: TLabel
            Left = 118
            Top = 136
            Width = 10
            Height = 13
            Caption = 'V:'
          end
        end
      end
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 552
    Width = 97
    Height = 113
    TabOrder = 20
    object btn_c3d_reset: TButton
      Left = 16
      Top = 80
      Width = 65
      Height = 25
      Caption = '&Reset Table'
      TabOrder = 0
      OnClick = btn_c3d_resetClick
    end
    object btn_c3d_load_rgb: TButton
      Left = 16
      Top = 16
      Width = 65
      Height = 25
      Caption = '&Load Table'
      TabOrder = 1
      OnClick = btn_c3d_load_rgbClick
    end
    object btn_c3d_save_rgb: TButton
      Left = 16
      Top = 48
      Width = 65
      Height = 25
      Caption = 'Sa&ve Table'
      TabOrder = 2
      OnClick = btn_c3d_save_rgbClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 16
    Top = 424
    Width = 97
    Height = 113
    TabOrder = 21
    object btn_c3d_sim: TButton
      Left = 16
      Top = 16
      Width = 65
      Height = 25
      Caption = '&Simulate'
      TabOrder = 0
      OnClick = btn_c3d_simClick
    end
    object BitBtn_c3d_undo: TBitBtn
      Left = 16
      Top = 80
      Width = 65
      Height = 25
      Caption = '&Undo'
      Enabled = False
      TabOrder = 1
      OnClick = BitBtn_c3d_undoClick
      Glyph.Data = {
        26060000424D2606000000000000360000002800000019000000140000000100
        180000000000F005000000000000000000000000000000000000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0DFDFDFBFBFBFC0C0C0C0C0C0C0C0C0C0C0C000C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C7C7C71E0E0E0000001C0505150303A7A7A7
        C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0EFEFEFC0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C09F9F9F4F0202
        CD0000CD00004F02029F9F9FC0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0
        C0C0CFCFCF0804048F8686C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C09F9F9F4F0202CD0000CD00006600007F7F7FC0C0C0C0C0C0C0C0
        C000C0C0C0C0C0C0C0C0C0C0C0C0483838B70000700E0E584747F7F7F7C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0AFAFAF430303CD0000CD00006600
        007F7F7FC0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0AFAFAF500F0FFF0000
        FF0000A70505301E1ED7D7D7C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0BFBF
        BF370404CD0000CD00006600007F7F7FC0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        F7F7F7201212E70000FF0000FF0000FF0000A70000180A0AB7B1B1C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0AFAFAF430303CD0000CD00006600007F7F7FC0C0C0C0
        C0C0C0C0C000C0C0C0C0C0C07F73732804048F0000FF0000FF0000F700000803
        03403232AFAFAFC0C0C0C0C0C0C0C0C0C0C0C0C0C0C0878787610000CD0000CD
        0000430303AFAFAFC0C0C0C0C0C0C0C0C000C0C0C0C0C0C09F9F9F7F7F7F382D
        2DAF0000FF0000FF0000580E0EA7A7A7C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0665555790000CD0000CD00001C0505DFDFDFC0C0C0C0C0C0C0C0C000C0C0
        C0C0C0C0C0C0C0C0C0C0BFBFBF401010FF0000FF0000BF0000403030C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C03D24249A0000CD0000C000000F0505C0C0C0
        C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0302121CF0000FF
        0000FF0000401010BFBFBFC0C0C0C0C0C0C0C0C0C0C0C0EFEFEF160505C70000
        CD0000930000452C2CC0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C09F9A9A600F0FFF0000FF0000CF0000382525F7F7F7C0C0C0C0C0C0
        C0C0C0979797560101CD0000CD0000430303AFAFAFC0C0C0C0C0C0C0C0C0C0C0
        C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C06051519F0505FF0000FF0000
        870D0D786969C0C0C0C0C0C0C0C0C03D24249A0000CD0000A600002D1717C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        F7F7F7301E1ECF0000FF0000FF0000780F0F706565F7F7F78D7E7E5D0202CD00
        00C000002A0707D7D7D7C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0DFDFDF3825258F0909FF0000FF00007F08
        082014141F03036900007300002B0909B6ACACC0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0F7F7
        F7706262000000280E0E401010000000000000110A0A615656DFDFDFC0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0D7D7D7BFBFBFC0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C000C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
        C0C0C0C0C0C0C0C0C000}
    end
    object btn_c3d_write: TButton
      Left = 16
      Top = 48
      Width = 65
      Height = 25
      Caption = 'Tcon &Write'
      TabOrder = 2
      OnClick = btn_c3d_writeClick
    end
  end
  object Edit1: TEdit
    Left = 16
    Top = 392
    Width = 105
    Height = 24
    TabOrder = 22
    Text = 'Cursor Color'
  end
  object cb_show_ref_img: TCheckBox
    Left = 793
    Top = 382
    Width = 129
    Height = 16
    Caption = 'Show Compare &Figure'
    TabOrder = 23
    Visible = False
    OnClick = cb_show_ref_imgClick
  end
  object rg_normal_target: TRadioGroup
    Left = 632
    Top = 544
    Width = 129
    Height = 57
    Caption = 'Normal_Target (Auto)'
    ItemIndex = 0
    Items.Strings = (
      'With Target'
      'With Source')
    TabOrder = 24
  end
  object rg_Color_Model: TRadioGroup
    Left = 632
    Top = 608
    Width = 129
    Height = 57
    Caption = 'Color Model Method'
    ItemIndex = 0
    Items.Strings = (
      'SR,SG,SB parameter'
      'RGB255 linear')
    TabOrder = 25
  end
  object CheckBox1: TCheckBox
    Left = 176
    Top = 4
    Width = 129
    Height = 17
    Caption = 'CheckBox1'
    TabOrder = 26
  end
  object btn_c3d_load_img: TButton
    Left = 791
    Top = 356
    Width = 65
    Height = 25
    Caption = 'Loa&d Image'
    TabOrder = 27
    Visible = False
    OnClick = btn_c3d_load_imgClick
  end
  inline colorPicker: TColorPickerFrame
    Left = 0
    Top = 26
    Width = 449
    Height = 341
    TabOrder = 28
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
    end
    inherited cb_show_ref_img: TCheckBox
      Left = 306
      Top = 5
      Width = 129
      Height = 16
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Excel '#35430#31639#34920', Text '#25991#23383#25991#20214'|*.xls;*.txt'
    Left = 696
  end
  object SaveDialog1: TSaveDialog
    FileName = '.xls'
    Filter = 'xls|*.xls|txt|*.txt'
    OnTypeChange = SaveDialog1TypeChange
    Left = 696
    Top = 24
  end
  object PopupMenu_HSV_ref_img: TPopupMenu
    Left = 416
    object c3d_Sim_Color_HSV_Step: TMenuItem
      Caption = 'Simulate Color with HSV Step'
      OnClick = c3d_Sim_Color_HSV_StepClick
    end
    object c3d_Sim_Image_HSV_Step: TMenuItem
      Caption = 'Simulate Image with HSV Step'
      OnClick = c3d_Sim_Image_HSV_StepClick
    end
  end
  object OpenDialog_xls: TOpenDialog
    Filter = 'Excel '#35430#31639#34920'|*.xls'
    Left = 368
  end
  object SaveDialog_xls: TSaveDialog
    Left = 336
  end
  object OpenDialog_img: TOpenDialog
    Filter = 'jpg,bmp|*.jpg; *.bmp;*.JPG;*.BMP'
    Left = 312
  end
end
