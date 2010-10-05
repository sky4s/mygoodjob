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
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  PrintScale = poNone
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 16
  object lb_c3d_showY: TLabel
    Left = 69
    Top = 436
    Width = 21
    Height = 16
    Caption = 'Y:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showX: TLabel
    Left = 22
    Top = 436
    Width = 20
    Height = 16
    Caption = 'X:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showR: TLabel
    Left = 130
    Top = 436
    Width = 22
    Height = 16
    Caption = 'R:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showG: TLabel
    Left = 177
    Top = 436
    Width = 22
    Height = 16
    Caption = 'G:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showB: TLabel
    Left = 226
    Top = 436
    Width = 21
    Height = 16
    Caption = 'B:   '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showH: TLabel
    Left = 286
    Top = 436
    Width = 19
    Height = 16
    Caption = 'H:  '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showS: TLabel
    Left = 335
    Top = 436
    Width = 18
    Height = 16
    Caption = 'S:  '
    Color = clCream
    ParentColor = False
  end
  object lb_c3d_showV: TLabel
    Left = 394
    Top = 436
    Width = 18
    Height = 16
    Caption = 'V:  '
    Color = clCream
    ParentColor = False
  end
  object Label28: TLabel
    Left = 20
    Top = 463
    Width = 87
    Height = 16
    Caption = 'Cursor Color'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object cb_en: TCheckBox
    Left = 20
    Top = 0
    Width = 99
    Height = 31
    Caption = '&Enable'
    TabOrder = 0
    OnClick = cb_enClick
  end
  object cb_demo: TCheckBox
    Left = 118
    Top = 0
    Width = 100
    Height = 31
    Caption = '&Demo'
    TabOrder = 1
  end
  object rg_c3d_hsv_mode: TRadioGroup
    Left = 207
    Top = 620
    Width = 109
    Height = 90
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
    Left = 345
    Top = 709
    Width = 99
    Height = 31
    Caption = 'Load Tbl old'
    TabOrder = 3
    OnClick = btn_c3d_loadClick
  end
  object btn_c3d_save_h: TButton
    Left = 217
    Top = 719
    Width = 99
    Height = 31
    Caption = 'Save Table H'
    TabOrder = 4
    OnClick = btn_c3d_save_hClick
  end
  object btn_c3d_check: TButton
    Left = 345
    Top = 629
    Width = 70
    Height = 26
    Caption = 'Tcon Chk'
    TabOrder = 6
    OnClick = btn_c3d_checkClick
  end
  object GroupBox36: TGroupBox
    Left = 443
    Top = 533
    Width = 247
    Height = 258
    Caption = 'Method'
    TabOrder = 7
    object rb_c3d_point: TRadioButton
      Left = 0
      Top = 49
      Width = 110
      Height = 31
      Caption = 'Point Color'
      Checked = True
      Color = clMoneyGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -15
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
      Top = 79
      Width = 110
      Height = 31
      Caption = 'Red        0'#176
      Color = clRed
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 1
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_y: TRadioButton
      Left = 0
      Top = 108
      Width = 110
      Height = 31
      Caption = 'Yellow    60'#176
      Color = clYellow
      ParentColor = False
      TabOrder = 2
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_g: TRadioButton
      Left = 0
      Top = 138
      Width = 110
      Height = 31
      Caption = 'Green    120'#176
      Color = clGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 3
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_c: TRadioButton
      Left = 0
      Top = 167
      Width = 110
      Height = 31
      Caption = 'Cyan      180'#176
      Color = clAqua
      ParentColor = False
      TabOrder = 4
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_b: TRadioButton
      Left = 0
      Top = 197
      Width = 110
      Height = 31
      Caption = 'Blue       240'#176
      Color = clBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 5
      OnClick = rb_c3d_colorClick
    end
    object rb_c3d_m: TRadioButton
      Left = 0
      Top = 226
      Width = 110
      Height = 31
      Caption = 'Magenta300'#176
      Color = clFuchsia
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -10
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      TabOrder = 6
      OnClick = rb_c3d_colorClick
    end
    object sg_c3d_hsvi: TStringGrid
      Left = 103
      Top = 49
      Width = 141
      Height = 212
      ColCount = 3
      DefaultColWidth = 36
      DefaultRowHeight = 23
      FixedCols = 0
      RowCount = 7
      FixedRows = 0
      TabOrder = 7
    end
    object StaticText34: TStaticText
      Left = 103
      Top = 30
      Width = 47
      Height = 20
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Hue'
      TabOrder = 8
    end
    object StaticText35: TStaticText
      Left = 150
      Top = 30
      Width = 47
      Height = 20
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Sat'
      TabOrder = 9
    end
    object StaticText36: TStaticText
      Left = 197
      Top = 30
      Width = 45
      Height = 20
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Bright'
      TabOrder = 10
    end
    object StaticText37: TStaticText
      Left = 197
      Top = 10
      Width = 47
      Height = 21
      Alignment = taCenter
      AutoSize = False
      BevelKind = bkFlat
      Caption = 'Intenst'
      TabOrder = 11
      Visible = False
    end
  end
  object GroupBox38: TGroupBox
    Left = 345
    Top = 542
    Width = 99
    Height = 40
    Caption = 'table index'
    TabOrder = 9
    object Label231: TLabel
      Left = 10
      Top = 20
      Width = 7
      Height = 16
      Caption = 'r:'
    end
    object lb_c3d_tbl_ir: TLabel
      Left = 20
      Top = 20
      Width = 7
      Height = 16
      Caption = '0'
    end
    object Label233: TLabel
      Left = 39
      Top = 20
      Width = 11
      Height = 16
      Caption = 'g:'
    end
    object lb_c3d_tbl_ig: TLabel
      Left = 49
      Top = 20
      Width = 7
      Height = 16
      Caption = '0'
    end
    object Label235: TLabel
      Left = 69
      Top = 20
      Width = 11
      Height = 16
      Caption = 'b:'
    end
    object lb_c3d_tbl_ib: TLabel
      Left = 79
      Top = 20
      Width = 7
      Height = 16
      Caption = '0'
    end
  end
  object rg_c3d_interpl: TRadioGroup
    Left = 197
    Top = 561
    Width = 128
    Height = 41
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
    Left = 345
    Top = 660
    Width = 70
    Height = 30
    Caption = 'tbl_search'
    TabOrder = 11
    OnClick = btn_tbl_searchClick
  end
  object btn_directly_sim: TButton
    Left = 345
    Top = 748
    Width = 89
    Height = 31
    Caption = 'Directly Sim'
    TabOrder = 12
    OnClick = btn_directly_simClick
  end
  object LabeledEdit1: TLabeledEdit
    Left = 384
    Top = 492
    Width = 50
    Height = 24
    EditLabel.Width = 61
    EditLabel.Height = 16
    EditLabel.Caption = 'Show Hue'
    EditLabel.OnClick = LabeledEdit1SubLabelClick
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 13
    Text = '0'
    Visible = False
  end
  object BitBtn2: TBitBtn
    Left = 443
    Top = 492
    Width = 41
    Height = 21
    Caption = 'ok'
    TabOrder = 14
    Visible = False
    OnClick = BitBtn2Click
  end
  object edt_show_h: TEdit
    Left = 689
    Top = 748
    Width = 51
    Height = 24
    TabOrder = 15
    Visible = False
  end
  object rg_c3d_TblSize: TRadioGroup
    Left = 778
    Top = 433
    Width = 178
    Height = 61
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
    Left = 345
    Top = 591
    Width = 60
    Height = 24
    ItemHeight = 16
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
    Left = 778
    Top = 551
    Width = 159
    Height = 110
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
    Left = 778
    Top = 502
    Width = 129
    Height = 41
    Caption = 'VSmoothG'
    Columns = 2
    ItemIndex = 1
    Items.Strings = (
      'off'
      'on')
    TabOrder = 5
  end
  object pc_Adjust: TPageControl
    Left = 167
    Top = 450
    Width = 602
    Height = 368
    ActivePage = TabSheet20
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
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
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      object pc_global_adj: TPageControl
        Left = 0
        Top = 0
        Width = 592
        Height = 336
        ActivePage = TabSheet7
        TabIndex = 0
        TabOrder = 0
        OnChange = pc_global_adjChange
        object TabSheet7: TTabSheet
          Caption = '&Auto 729 Color Adjust'
          object GroupBox20: TGroupBox
            Left = 0
            Top = 10
            Width = 474
            Height = 168
            Caption = 'Source Panel'
            TabOrder = 0
            object GroupBox21: TGroupBox
              Left = 108
              Top = 20
              Width = 228
              Height = 139
              Caption = 'RGB2XYZ Matrix'
              TabOrder = 0
              object edt_auto_rgb2xyz11: TEdit
                Left = 20
                Top = 20
                Width = 60
                Height = 24
                TabOrder = 0
              end
              object edt_auto_rgb2xyz12: TEdit
                Left = 89
                Top = 20
                Width = 60
                Height = 24
                TabOrder = 1
              end
              object edt_auto_rgb2xyz13: TEdit
                Left = 158
                Top = 20
                Width = 60
                Height = 24
                TabOrder = 2
              end
              object edt_auto_rgb2xyz21: TEdit
                Left = 20
                Top = 59
                Width = 60
                Height = 24
                TabOrder = 3
              end
              object edt_auto_rgb2xyz22: TEdit
                Left = 89
                Top = 59
                Width = 60
                Height = 24
                TabOrder = 4
              end
              object edt_auto_rgb2xyz23: TEdit
                Left = 158
                Top = 59
                Width = 60
                Height = 24
                TabOrder = 5
              end
              object edt_auto_rgb2xyz31: TEdit
                Left = 20
                Top = 98
                Width = 60
                Height = 24
                TabOrder = 6
              end
              object edt_auto_rgb2xyz32: TEdit
                Left = 89
                Top = 98
                Width = 60
                Height = 24
                TabOrder = 7
              end
              object edt_auto_rgb2xyz33: TEdit
                Left = 158
                Top = 98
                Width = 60
                Height = 24
                TabOrder = 8
              end
            end
            object GroupBox23: TGroupBox
              Left = 354
              Top = 20
              Width = 100
              Height = 139
              Caption = 'Gamma'
              TabOrder = 1
              object lble_auto_Gm_R: TLabeledEdit
                Left = 30
                Top = 20
                Width = 50
                Height = 24
                EditLabel.Width = 10
                EditLabel.Height = 16
                EditLabel.Caption = 'R'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 0
              end
              object lble_auto_Gm_G: TLabeledEdit
                Left = 30
                Top = 59
                Width = 50
                Height = 24
                EditLabel.Width = 10
                EditLabel.Height = 16
                EditLabel.Caption = 'G'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 1
              end
              object lble_auto_Gm_B: TLabeledEdit
                Left = 30
                Top = 98
                Width = 50
                Height = 24
                EditLabel.Width = 9
                EditLabel.Height = 16
                EditLabel.Caption = 'B'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 2
              end
            end
            object btn_Auto_Src_Load: TButton
              Left = 20
              Top = 49
              Width = 80
              Height = 31
              Caption = 'Load Data'
              TabOrder = 2
              OnClick = btn_Auto_Src_LoadClick
            end
            object btn_Auto_Src_Calc: TButton
              Left = 20
              Top = 108
              Width = 80
              Height = 31
              Caption = 'Calculate'
              Enabled = False
              TabOrder = 3
              OnClick = btn_Auto_Src_CalcClick
            end
          end
          object GroupBox24: TGroupBox
            Left = 0
            Top = 192
            Width = 474
            Height = 95
            Caption = 'Target Panel'
            TabOrder = 1
            object btn_Auto_Trg_Load: TButton
              Left = 79
              Top = 39
              Width = 80
              Height = 31
              Caption = 'Load Data'
              TabOrder = 0
              OnClick = btn_Auto_Trg_LoadClick
            end
            object GroupBox26: TGroupBox
              Left = 305
              Top = 0
              Width = 169
              Height = 90
              Caption = 'Smooth Color Translation'
              TabOrder = 1
              Visible = False
              object LabeledEdit5: TLabeledEdit
                Left = 89
                Top = 20
                Width = 50
                Height = 24
                EditLabel.Width = 53
                EditLabel.Height = 16
                EditLabel.Caption = 'Distance'
                LabelPosition = lpLeft
                LabelSpacing = 3
                TabOrder = 0
              end
              object Button6: TButton
                Left = 49
                Top = 49
                Width = 61
                Height = 31
                Caption = 'Run'
                TabOrder = 1
              end
            end
            object btn_Auto_Trg_BuildTbl: TButton
              Left = 197
              Top = 39
              Width = 80
              Height = 31
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
            Left = 394
            Top = -30
            Width = 257
            Height = 359
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
                Width = 178
                Height = 343
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
                Width = 178
                Height = 316
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
                Left = 10
                Top = 217
                Width = 90
                Height = 30
                Caption = 'Dark < 64'
                TabOrder = 0
                Visible = False
                OnClick = btn_darkClick
              end
              object sg_Dark: TStringGrid
                Left = 0
                Top = -2
                Width = 178
                Height = 168
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
                Width = 178
                Height = 237
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
            Top = 84
            Width = 396
            Height = 213
            TabOrder = 1
            object GroupBox40: TGroupBox
              Left = 0
              Top = 0
              Width = 395
              Height = 80
              TabOrder = 0
              object lb_c3d_Manual39_h: TLabel
                Left = 335
                Top = 39
                Width = 11
                Height = 16
                Caption = '0'#176
              end
              object Label197: TLabel
                Left = 10
                Top = 30
                Width = 25
                Height = 16
                Caption = 'Hue'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Manual39_h: TScrollBar
                Left = 61
                Top = 39
                Width = 247
                Height = 21
                Max = 120
                PageSize = 0
                Position = 60
                TabOrder = 0
                OnChange = sb_c3d_Manual39_hChange
              end
              object Edit_c3d_Manual39_h_adj: TEdit
                Left = 89
                Top = 10
                Width = 50
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
            end
            object GroupBox41: TGroupBox
              Left = 0
              Top = 69
              Width = 395
              Height = 76
              TabOrder = 1
              object lb_c3d_Manual39_s: TLabel
                Left = 335
                Top = 39
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Label207: TLabel
                Left = 10
                Top = 30
                Width = 56
                Height = 16
                Caption = 'Satuation'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Manual39_s: TScrollBar
                Left = 61
                Top = 47
                Width = 247
                Height = 21
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 0
                OnChange = sb_c3d_Manual39_sChange
              end
              object edt_c3d_satC: TEdit
                Left = 358
                Top = 15
                Width = 30
                Height = 24
                Hint = 'constant'
                ParentShowHint = False
                ShowHint = True
                TabOrder = 1
                Text = '1.5'
                Visible = False
              end
              object Edit_c3d_Manual39_s_adj: TEdit
                Left = 89
                Top = 10
                Width = 50
                Height = 24
                ReadOnly = True
                TabOrder = 2
                Text = '0'
              end
            end
            object GroupBox7: TGroupBox
              Left = 0
              Top = 136
              Width = 393
              Height = 73
              TabOrder = 2
              object lb_c3d_Manual39_v: TLabel
                Left = 341
                Top = 41
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Label25: TLabel
                Left = 5
                Top = 41
                Width = 63
                Height = 16
                Caption = 'Brightness'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Manual39_v: TScrollBar
                Left = 69
                Top = 36
                Width = 247
                Height = 21
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 0
                OnChange = sb_c3d_Manual39_vChange
              end
              object Edit_c3d_Manual39_v_adj: TEdit
                Left = 89
                Top = 9
                Width = 50
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
              object edt_c3d_valC: TEdit
                Left = 354
                Top = 9
                Width = 31
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
            Left = 401
            Top = 276
            Width = 40
            Height = 24
            EditLabel.Width = 136
            EditLabel.Height = 16
            EditLabel.Caption = 'Saturation Light Sigma '
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 2
            Text = '0.35'
            Visible = False
            OnChange = lbe_sat_sigma_lightChange
          end
          object rg_manual_39_choice: TRadioGroup
            Left = 167
            Top = 0
            Width = 228
            Height = 70
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
        Left = 433
        Top = 20
        Width = 77
        Height = 16
        Caption = 'Point Color'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object pc_point_color_adj: TPageControl
        Left = 0
        Top = 0
        Width = 415
        Height = 336
        ActivePage = TabSheet10
        TabIndex = 1
        TabOrder = 0
        object TabSheet9: TTabSheet
          Caption = '&RGB Domain'
          object Label1: TLabel
            Left = 459
            Top = 10
            Width = 132
            Height = 16
            Caption = 'Point Color Record'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Visible = False
          end
          object btn_LoadRecord: TButton
            Left = 473
            Top = 271
            Width = 89
            Height = 31
            Caption = 'Load Record'
            TabOrder = 0
            Visible = False
            OnClick = btn_LoadRecordClick
          end
          object btn_AddPoint: TButton
            Left = 473
            Top = 236
            Width = 89
            Height = 31
            Caption = 'Add Point'
            TabOrder = 1
            Visible = False
            OnClick = btn_AddPointClick
          end
          object btn_SaveRecord: TButton
            Left = 571
            Top = 271
            Width = 90
            Height = 31
            Caption = 'Save Record'
            TabOrder = 2
            Visible = False
            OnClick = btn_SaveRecordClick
          end
          object btn_DeletePoint: TButton
            Left = 571
            Top = 236
            Width = 90
            Height = 31
            Caption = 'Delete Point'
            TabOrder = 3
            Visible = False
            OnClick = btn_DeletePointClick
          end
          object ListBox_PointColor: TListBox
            Left = 463
            Top = 30
            Width = 198
            Height = 198
            ItemHeight = 16
            TabOrder = 4
            Visible = False
            OnClick = ListBox_PointColorClick
          end
          object gb_c3d_RGB_adj: TGroupBox
            Left = 0
            Top = 5
            Width = 405
            Height = 292
            TabOrder = 5
            object Label181: TLabel
              Left = 20
              Top = 39
              Width = 53
              Height = 16
              Caption = 'Distance'
            end
            object lb_c3d_rgb_dis: TLabel
              Left = 358
              Top = 39
              Width = 7
              Height = 16
              Caption = '0'
            end
            object sb_c3d_rgb_dis: TScrollBar
              Left = 82
              Top = 39
              Width = 248
              Height = 21
              Max = 10
              PageSize = 0
              TabOrder = 0
              OnChange = sb_c3d_rgb_disChange
            end
            object rg_PCrgb_choose: TRadioGroup
              Left = 10
              Top = 89
              Width = 168
              Height = 50
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
              Top = 158
              Width = 405
              Height = 129
              Caption = 'HSV'
              TabOrder = 2
              object lb_c3d_hsv_v: TLabel
                Left = 354
                Top = 103
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Label188: TLabel
                Left = 6
                Top = 103
                Width = 63
                Height = 16
                Caption = 'Brightness'
              end
              object lb_c3d_hsv_s: TLabel
                Left = 354
                Top = 59
                Width = 7
                Height = 16
                Caption = '0'
              end
              object lb_c3d_hsv_h: TLabel
                Left = 354
                Top = 20
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Label186: TLabel
                Left = 20
                Top = 20
                Width = 25
                Height = 16
                Caption = 'Hue'
              end
              object Label187: TLabel
                Left = 4
                Top = 59
                Width = 71
                Height = 16
                Caption = 'Sataturation'
              end
              object sb_c3d_hsv_v: TScrollBar
                Left = 79
                Top = 98
                Width = 247
                Height = 21
                PageSize = 0
                Position = 50
                TabOrder = 0
                OnChange = sb_c3d_hsv_Change
              end
              object sb_c3d_hsv_s: TScrollBar
                Left = 79
                Top = 59
                Width = 247
                Height = 21
                PageSize = 0
                Position = 50
                TabOrder = 1
                OnChange = sb_c3d_hsv_Change
              end
              object sb_c3d_hsv_h: TScrollBar
                Left = 79
                Top = 20
                Width = 247
                Height = 21
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 2
                OnChange = sb_c3d_hsv_Change
              end
            end
            object gb_PCrgb_rgb: TGroupBox
              Left = 0
              Top = 158
              Width = 405
              Height = 129
              Caption = 'RGB'
              TabOrder = 3
              object Label182: TLabel
                Left = 30
                Top = 20
                Width = 26
                Height = 16
                Caption = 'Red'
              end
              object lb_c3d_rgb_r: TLabel
                Left = 354
                Top = 20
                Width = 7
                Height = 16
                Caption = '0'
              end
              object lb_c3d_rgb_g: TLabel
                Left = 354
                Top = 59
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Label183: TLabel
                Left = 20
                Top = 59
                Width = 37
                Height = 16
                Caption = 'Green'
              end
              object Label184: TLabel
                Left = 30
                Top = 103
                Width = 27
                Height = 16
                Caption = 'Blue'
              end
              object lb_c3d_rgb_b: TLabel
                Left = 354
                Top = 103
                Width = 7
                Height = 16
                Caption = '0'
              end
              object sb_c3d_rgb_r: TScrollBar
                Left = 79
                Top = 20
                Width = 247
                Height = 21
                PageSize = 0
                Position = 50
                TabOrder = 0
                OnChange = sb_c3d_rgb_rChange
              end
              object sb_c3d_rgb_g: TScrollBar
                Left = 79
                Top = 59
                Width = 247
                Height = 21
                PageSize = 0
                Position = 50
                TabOrder = 1
                OnChange = sb_c3d_rgb_gChange
              end
              object sb_c3d_rgb_b: TScrollBar
                Left = 79
                Top = 98
                Width = 247
                Height = 21
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
            Top = 5
            Width = 405
            Height = 105
            TabOrder = 0
            object Label204: TLabel
              Left = 316
              Top = 39
              Width = 32
              Height = 16
              Caption = '(Pos)'
            end
            object Label203: TLabel
              Left = 62
              Top = 39
              Width = 34
              Height = 16
              Caption = '(Neg)'
            end
            object lb_c3d_Point_HSV_hdn: TLabel
              Left = 50
              Top = 20
              Width = 22
              Height = 16
              Caption = '-30'#176
            end
            object Label185: TLabel
              Left = 4
              Top = -2
              Width = 63
              Height = 16
              Caption = 'Diffusion    '
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -15
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object lb_c3d_Point_HSV_hdp: TLabel
              Left = 336
              Top = 20
              Width = 18
              Height = 16
              Caption = '30'#176
            end
            object Label2: TLabel
              Left = 10
              Top = 20
              Width = 25
              Height = 16
              Caption = 'Hue'
            end
            object Label3: TLabel
              Left = 10
              Top = 59
              Width = 30
              Height = 16
              Caption = 'S/ V '
            end
            object lb_c3d_Point_HSV_svd: TLabel
              Left = 345
              Top = 59
              Width = 7
              Height = 16
              Caption = '1'
            end
            object sb_c3d_Point_HSV_hdn: TScrollBar
              Left = 79
              Top = 20
              Width = 123
              Height = 21
              PageSize = 0
              Position = 70
              TabOrder = 0
              OnChange = sb_c3d_Point_HSV_hdnChange
            end
            object sb_c3d_Point_HSV_hdp: TScrollBar
              Left = 203
              Top = 20
              Width = 123
              Height = 21
              PageSize = 0
              Position = 30
              TabOrder = 1
              OnChange = sb_c3d_Point_HSV_hdpChange
            end
            object sb_c3d_Point_HSV_svd: TScrollBar
              Left = 79
              Top = 59
              Width = 247
              Height = 21
              Max = 10
              PageSize = 0
              Position = 10
              TabOrder = 2
              OnChange = sb_c3d_Point_HSV_svdChange
            end
          end
          object GroupBox4: TGroupBox
            Left = 0
            Top = 89
            Width = 405
            Height = 208
            TabOrder = 1
            object lb_c3d_Point_HSV_v: TLabel
              Left = 341
              Top = 177
              Width = 7
              Height = 16
              Caption = '0'
            end
            object Label5: TLabel
              Left = 5
              Top = 158
              Width = 63
              Height = 16
              Caption = 'Brightness'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -15
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object GroupBox5: TGroupBox
              Left = 0
              Top = 0
              Width = 405
              Height = 80
              TabOrder = 0
              object lb_c3d_Point_HSV_h: TLabel
                Left = 335
                Top = 39
                Width = 11
                Height = 16
                Caption = '0'#176
              end
              object Label7: TLabel
                Left = 20
                Top = 20
                Width = 25
                Height = 16
                Caption = 'Hue'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Point_HSV_h: TScrollBar
                Left = 69
                Top = 39
                Width = 247
                Height = 21
                Max = 120
                PageSize = 0
                Position = 60
                TabOrder = 0
                OnChange = sb_c3d_Point_HSV_hChange
              end
              object Edit_c3d_Point_HSV_h_adj: TEdit
                Left = 89
                Top = 10
                Width = 50
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
              object cb_c3d_Point_HSV_h_g: TCheckBox
                Left = 158
                Top = 15
                Width = 70
                Height = 21
                Caption = 'Global'
                TabOrder = 2
              end
            end
            object GroupBox6: TGroupBox
              Left = 0
              Top = 69
              Width = 405
              Height = 70
              TabOrder = 1
              object lb_c3d_Point_HSV_s: TLabel
                Left = 335
                Top = 39
                Width = 7
                Height = 16
                Caption = '0'
              end
              object Label10: TLabel
                Left = 10
                Top = 20
                Width = 56
                Height = 16
                Caption = 'Satuation'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = []
                ParentFont = False
              end
              object sb_c3d_Point_HSV_s: TScrollBar
                Left = 69
                Top = 39
                Width = 247
                Height = 21
                Max = 200
                PageSize = 0
                Position = 100
                TabOrder = 0
                OnChange = sb_c3d_Point_HSV_sChange
              end
              object Edit_c3d_Point_HSV_s_adj: TEdit
                Left = 89
                Top = 10
                Width = 50
                Height = 24
                ReadOnly = True
                TabOrder = 1
                Text = '0'
              end
              object cb_c3d_Point_HSV_s_g: TCheckBox
                Left = 158
                Top = 15
                Width = 70
                Height = 21
                Caption = 'Global'
                TabOrder = 2
              end
            end
            object Edit_c3d_Point_HSV_v_adj: TEdit
              Left = 89
              Top = 148
              Width = 50
              Height = 24
              ReadOnly = True
              TabOrder = 2
              Text = '0'
            end
            object sb_c3d_Point_HSV_v: TScrollBar
              Left = 69
              Top = 177
              Width = 247
              Height = 21
              Max = 200
              PageSize = 0
              Position = 100
              TabOrder = 3
              OnChange = sb_c3d_Point_HSV_vChange
            end
            object cb_c3d_Point_HSV_v_g: TCheckBox
              Left = 158
              Top = 153
              Width = 70
              Height = 21
              Caption = 'Global'
              TabOrder = 4
            end
          end
        end
      end
      object sg_rgb_input: TStringGrid
        Left = 433
        Top = 39
        Width = 137
        Height = 50
        ColCount = 3
        DefaultColWidth = 35
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 1
      end
      object btn_key_in_HSV: TBitBtn
        Left = 502
        Top = 98
        Width = 60
        Height = 21
        Caption = 'HSV GO'
        TabOrder = 2
        Visible = False
        OnClick = btn_key_in_HSVClick
      end
      object btn_key_in_RGB: TBitBtn
        Left = 473
        Top = 98
        Width = 89
        Height = 31
        Hint = 'Click to show color in "Colors" page'
        Caption = 'Show RGB'
        TabOrder = 3
        OnClick = btn_key_in_RGBClick
      end
      object rg_PointNum: TRadioGroup
        Left = 433
        Top = 197
        Width = 149
        Height = 70
        Caption = 'Adjust Point'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
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
        Left = 473
        Top = 138
        Width = 89
        Height = 31
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
        Left = 10
        Top = 30
        Width = 405
        Height = 70
        ColCount = 9
        DefaultColWidth = 35
        FixedCols = 0
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 0
        OnKeyDown = sg_table_stepKeyDown
      end
      object BitBtn1: TBitBtn
        Left = 335
        Top = 108
        Width = 70
        Height = 31
        Caption = 'Done'
        TabOrder = 1
        OnClick = BitBtn1Click
      end
      object btn_sim_by_val: TButton
        Left = 20
        Top = 158
        Width = 99
        Height = 40
        Caption = 'sim by value'
        TabOrder = 2
        OnClick = btn_sim_by_valClick
      end
      object btn_dirSim_by_val: TButton
        Left = 148
        Top = 158
        Width = 99
        Height = 40
        Caption = 'dirsim by value'
        TabOrder = 3
        OnClick = btn_dirSim_by_valClick
      end
    end
  end
  object PageControl7: TPageControl
    Left = 551
    Top = -22
    Width = 218
    Height = 494
    ActivePage = TabSheet23
    TabIndex = 0
    TabOrder = 19
    TabWidth = 189
    object TabSheet23: TTabSheet
      Caption = 'Point Color'
      object GroupBox44: TGroupBox
        Left = 0
        Top = 0
        Width = 208
        Height = 458
        TabOrder = 0
        object GroupBox34: TGroupBox
          Left = 0
          Top = 0
          Width = 208
          Height = 228
          Caption = 'Point Color'
          Enabled = False
          TabOrder = 0
          object Img_c3d_sel: TImage
            Left = 0
            Top = 17
            Width = 208
            Height = 169
          end
          object lb_c3d_selR: TLabel
            Left = 30
            Top = 187
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selH: TLabel
            Left = 30
            Top = 207
            Width = 7
            Height = 16
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selG: TLabel
            Left = 98
            Top = 187
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selB: TLabel
            Left = 167
            Top = 187
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selV: TLabel
            Left = 167
            Top = 207
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selS: TLabel
            Left = 98
            Top = 207
            Width = 7
            Height = 16
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_selI: TLabel
            Left = 187
            Top = 167
            Width = 12
            Height = 16
            Caption = '    '
            Color = clCream
            ParentColor = False
            Visible = False
          end
          object Label190: TLabel
            Left = 12
            Top = 187
            Width = 13
            Height = 16
            Caption = 'R:'
          end
          object Label198: TLabel
            Left = 81
            Top = 187
            Width = 13
            Height = 16
            Caption = 'G:'
          end
          object Label202: TLabel
            Left = 150
            Top = 187
            Width = 12
            Height = 16
            Caption = 'B:'
          end
          object Label206: TLabel
            Left = 12
            Top = 207
            Width = 13
            Height = 16
            Caption = 'H:'
          end
          object Label208: TLabel
            Left = 81
            Top = 207
            Width = 12
            Height = 16
            Caption = 'S:'
          end
          object Label209: TLabel
            Left = 170
            Top = 167
            Width = 9
            Height = 16
            Caption = ' I:'
            Visible = False
          end
          object Label213: TLabel
            Left = 150
            Top = 207
            Width = 12
            Height = 16
            Caption = 'V:'
          end
        end
        object GroupBox45: TGroupBox
          Left = 0
          Top = 229
          Width = 208
          Height = 228
          Caption = 'Simulate Color'
          Enabled = False
          TabOrder = 1
          object lb_c3d_simR: TLabel
            Left = 30
            Top = 187
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simH: TLabel
            Left = 30
            Top = 207
            Width = 7
            Height = 16
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simG: TLabel
            Left = 98
            Top = 187
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simB: TLabel
            Left = 167
            Top = 187
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simV: TLabel
            Left = 169
            Top = 207
            Width = 21
            Height = 16
            Caption = '255'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simS: TLabel
            Left = 98
            Top = 207
            Width = 7
            Height = 16
            Caption = '0'
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_simI: TLabel
            Left = 177
            Top = 158
            Width = 12
            Height = 16
            Caption = '    '
            Color = clCream
            ParentColor = False
            Visible = False
          end
          object Label246: TLabel
            Left = 12
            Top = 187
            Width = 13
            Height = 16
            Caption = 'R:'
          end
          object Label247: TLabel
            Left = 81
            Top = 187
            Width = 13
            Height = 16
            Caption = 'G:'
          end
          object Label248: TLabel
            Left = 150
            Top = 187
            Width = 12
            Height = 16
            Caption = 'B:'
          end
          object Label249: TLabel
            Left = 12
            Top = 207
            Width = 13
            Height = 16
            Caption = 'H:'
          end
          object Label250: TLabel
            Left = 81
            Top = 207
            Width = 12
            Height = 16
            Caption = 'S:'
          end
          object Label251: TLabel
            Left = 160
            Top = 158
            Width = 9
            Height = 16
            Caption = ' I:'
            Visible = False
          end
          object Label252: TLabel
            Left = 150
            Top = 207
            Width = 12
            Height = 16
            Caption = 'V:'
          end
          object Img_c3d_sim: TImage
            Left = 0
            Top = 17
            Width = 208
            Height = 169
          end
        end
      end
    end
    object TabSheet24: TTabSheet
      Caption = 'Debug-modified'
      ImageIndex = 1
      TabVisible = False
      object GroupBox22: TGroupBox
        Left = 10
        Top = -2
        Width = 198
        Height = 464
        TabOrder = 0
        object GroupBox35: TGroupBox
          Left = 0
          Top = 0
          Width = 198
          Height = 228
          Caption = 'Matrix RGB'
          Enabled = False
          TabOrder = 0
          object Img_c3d_tbl: TImage
            Left = 10
            Top = 20
            Width = 178
            Height = 139
          end
          object lb_c3d_tblR: TLabel
            Left = 30
            Top = 167
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblG: TLabel
            Left = 30
            Top = 187
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblB: TLabel
            Left = 30
            Top = 207
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblH: TLabel
            Left = 98
            Top = 167
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblS: TLabel
            Left = 98
            Top = 187
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblI: TLabel
            Left = 98
            Top = 207
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_tblV: TLabel
            Left = 159
            Top = 167
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object Label215: TLabel
            Left = 12
            Top = 167
            Width = 13
            Height = 16
            Caption = 'R:'
          end
          object Label216: TLabel
            Left = 10
            Top = 187
            Width = 13
            Height = 16
            Caption = 'G:'
          end
          object Label219: TLabel
            Left = 10
            Top = 207
            Width = 12
            Height = 16
            Caption = 'B:'
          end
          object Label220: TLabel
            Left = 81
            Top = 167
            Width = 13
            Height = 16
            Caption = 'H:'
          end
          object Label221: TLabel
            Left = 79
            Top = 187
            Width = 12
            Height = 16
            Caption = 'S:'
          end
          object Label222: TLabel
            Left = 79
            Top = 207
            Width = 9
            Height = 16
            Caption = ' I:'
          end
          object Label223: TLabel
            Left = 145
            Top = 167
            Width = 12
            Height = 16
            Caption = 'V:'
          end
        end
        object GroupBox37: TGroupBox
          Left = 0
          Top = 236
          Width = 198
          Height = 228
          Caption = 'Correction RGB'
          Enabled = False
          TabOrder = 1
          object Img_c3d_cor: TImage
            Left = 10
            Top = 20
            Width = 178
            Height = 139
          end
          object lb_c3d_corG: TLabel
            Left = 30
            Top = 187
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corB: TLabel
            Left = 30
            Top = 207
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corH: TLabel
            Left = 98
            Top = 167
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corS: TLabel
            Left = 98
            Top = 187
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corI: TLabel
            Left = 98
            Top = 207
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corV: TLabel
            Left = 159
            Top = 167
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object lb_c3d_corR: TLabel
            Left = 30
            Top = 167
            Width = 15
            Height = 16
            Caption = '     '
            Color = clCream
            ParentColor = False
          end
          object Label224: TLabel
            Left = 12
            Top = 167
            Width = 13
            Height = 16
            Caption = 'R:'
          end
          object Label225: TLabel
            Left = 10
            Top = 187
            Width = 13
            Height = 16
            Caption = 'G:'
          end
          object Label226: TLabel
            Left = 10
            Top = 207
            Width = 12
            Height = 16
            Caption = 'B:'
          end
          object Label227: TLabel
            Left = 81
            Top = 167
            Width = 13
            Height = 16
            Caption = 'H:'
          end
          object Label228: TLabel
            Left = 79
            Top = 187
            Width = 12
            Height = 16
            Caption = 'S:'
          end
          object Label229: TLabel
            Left = 79
            Top = 207
            Width = 9
            Height = 16
            Caption = ' I:'
          end
          object Label230: TLabel
            Left = 145
            Top = 167
            Width = 12
            Height = 16
            Caption = 'V:'
          end
        end
      end
    end
  end
  object GroupBox2: TGroupBox
    Left = 20
    Top = 679
    Width = 119
    Height = 139
    TabOrder = 20
    object btn_c3d_reset: TButton
      Left = 20
      Top = 98
      Width = 80
      Height = 31
      Caption = '&Reset Table'
      TabOrder = 0
      OnClick = btn_c3d_resetClick
    end
    object btn_c3d_load_rgb: TButton
      Left = 20
      Top = 20
      Width = 80
      Height = 30
      Caption = '&Load Table'
      TabOrder = 1
      OnClick = btn_c3d_load_rgbClick
    end
    object btn_c3d_save_rgb: TButton
      Left = 20
      Top = 59
      Width = 80
      Height = 31
      Caption = 'Sa&ve Table'
      TabOrder = 2
      OnClick = btn_c3d_save_rgbClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 20
    Top = 522
    Width = 119
    Height = 139
    TabOrder = 21
    object btn_c3d_sim: TButton
      Left = 20
      Top = 20
      Width = 80
      Height = 30
      Caption = '&Simulate'
      TabOrder = 0
      OnClick = btn_c3d_simClick
    end
    object BitBtn_c3d_undo: TBitBtn
      Left = 20
      Top = 98
      Width = 80
      Height = 31
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
      Left = 20
      Top = 59
      Width = 80
      Height = 31
      Caption = 'Tcon &Write'
      TabOrder = 2
      OnClick = btn_c3d_writeClick
    end
  end
  object Edit1: TEdit
    Left = 20
    Top = 482
    Width = 129
    Height = 24
    TabOrder = 22
    Text = 'Cursor Color'
  end
  object cb_show_ref_img: TCheckBox
    Left = 976
    Top = 470
    Width = 159
    Height = 20
    Caption = 'Show Compare &Figure'
    TabOrder = 23
    Visible = False
    OnClick = cb_show_ref_imgClick
  end
  object rg_normal_target: TRadioGroup
    Left = 778
    Top = 670
    Width = 159
    Height = 70
    Caption = 'Normal_Target (Auto)'
    ItemIndex = 0
    Items.Strings = (
      'With Target'
      'With Source')
    TabOrder = 24
  end
  object rg_Color_Model: TRadioGroup
    Left = 778
    Top = 748
    Width = 159
    Height = 70
    Caption = 'Color Model Method'
    ItemIndex = 0
    Items.Strings = (
      'SR,SG,SB parameter'
      'RGB255 linear')
    TabOrder = 25
  end
  object CheckBox1: TCheckBox
    Left = 217
    Top = 5
    Width = 158
    Height = 21
    Caption = 'CheckBox1'
    TabOrder = 26
  end
  object btn_c3d_load_img: TButton
    Left = 974
    Top = 438
    Width = 80
    Height = 31
    Caption = 'Loa&d Image'
    TabOrder = 27
    Visible = False
    OnClick = btn_c3d_load_imgClick
  end
  inline colorPicker: TColorPickerFrame
    Left = 0
    Top = 32
    Width = 552
    Height = 420
    TabOrder = 28
    inherited pc_img: TPageControl
      ActivePage = colorPicker.ts_image
      TabIndex = 0
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
