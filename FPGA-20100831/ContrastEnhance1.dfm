object ContrastEnhanceForm1: TContrastEnhanceForm1
  Left = 369
  Top = 145
  Width = 687
  Height = 570
  Caption = 'Contrast Enhancement'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  PopupMenu = MainForm.PopupMenu1
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox3: TGroupBox
    Left = 10
    Top = 0
    Width = 818
    Height = 671
    TabOrder = 0
    object Label1: TLabel
      Left = 10
      Top = 305
      Width = 41
      Height = 16
      Caption = 'Label1'
    end
    object Label2: TLabel
      Left = 10
      Top = 374
      Width = 41
      Height = 16
      Caption = 'Label2'
    end
    object Label3: TLabel
      Left = 10
      Top = 433
      Width = 41
      Height = 16
      Caption = 'Label3'
    end
    object CheckBox1: TCheckBox
      Left = 10
      Top = 20
      Width = 100
      Height = 21
      Caption = 'CheckBox1'
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 138
      Top = 20
      Width = 100
      Height = 21
      Caption = 'CheckBox2'
      TabOrder = 1
    end
    object CheckBox3: TCheckBox
      Left = 10
      Top = 98
      Width = 119
      Height = 21
      Caption = 'CheckBox3'
      TabOrder = 2
    end
    object CheckBox4: TCheckBox
      Left = 138
      Top = 98
      Width = 119
      Height = 21
      Caption = 'CheckBox4'
      TabOrder = 3
    end
    object CheckBox5: TCheckBox
      Left = 10
      Top = 138
      Width = 119
      Height = 21
      Caption = 'CheckBox5'
      TabOrder = 4
    end
    object CheckBox6: TCheckBox
      Left = 138
      Top = 138
      Width = 109
      Height = 21
      Caption = 'CheckBox6'
      TabOrder = 5
    end
    object ComboBox1: TComboBox
      Left = 10
      Top = 325
      Width = 168
      Height = 24
      ItemHeight = 16
      TabOrder = 6
      Text = 'ComboBox1'
    end
    object ComboBox2: TComboBox
      Left = 10
      Top = 394
      Width = 168
      Height = 24
      ItemHeight = 16
      TabOrder = 7
      Text = 'ComboBox2'
    end
    object PageControl1: TPageControl
      Left = 246
      Top = 10
      Width = 572
      Height = 661
      ActivePage = TabSheet5
      TabIndex = 4
      TabOrder = 8
      object TabSheet1: TTabSheet
        Caption = 'Progressive Gamma \ Contrast Setting'
        object GroupBox1: TGroupBox
          Left = 20
          Top = 158
          Width = 454
          Height = 168
          Caption = 'Progressive Gamma'
          TabOrder = 0
          object Label8: TLabel
            Left = 10
            Top = 49
            Width = 41
            Height = 16
            Caption = 'Label8'
          end
          object Label9: TLabel
            Left = 10
            Top = 89
            Width = 41
            Height = 16
            Caption = 'Label9'
          end
          object Label10: TLabel
            Left = 10
            Top = 128
            Width = 48
            Height = 16
            Caption = 'Label10'
          end
          object CheckBox7: TCheckBox
            Left = 10
            Top = 20
            Width = 149
            Height = 30
            Caption = 'CheckBox7'
            TabOrder = 0
          end
          object ScrollBar3: TScrollBar
            Left = 148
            Top = 49
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 1
          end
          object StaticText3: TStaticText
            Left = 404
            Top = 49
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText3'
            TabOrder = 2
          end
          object ScrollBar4: TScrollBar
            Left = 148
            Top = 89
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 3
          end
          object ScrollBar5: TScrollBar
            Left = 148
            Top = 128
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 4
          end
          object StaticText4: TStaticText
            Left = 404
            Top = 89
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText4'
            TabOrder = 5
          end
          object StaticText5: TStaticText
            Left = 404
            Top = 128
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText5'
            TabOrder = 6
          end
        end
        object GroupBox2: TGroupBox
          Left = 20
          Top = 354
          Width = 454
          Height = 258
          Caption = 'Contrast Setting'
          TabOrder = 1
          object Label11: TLabel
            Left = 10
            Top = 30
            Width = 48
            Height = 16
            Caption = 'Label11'
          end
          object Label12: TLabel
            Left = 10
            Top = 69
            Width = 48
            Height = 16
            Caption = 'Label12'
          end
          object Label13: TLabel
            Left = 10
            Top = 108
            Width = 48
            Height = 16
            Caption = 'Label13'
          end
          object Label14: TLabel
            Left = 10
            Top = 148
            Width = 48
            Height = 16
            Caption = 'Label14'
          end
          object Label15: TLabel
            Left = 10
            Top = 217
            Width = 48
            Height = 16
            Caption = 'Label15'
          end
          object CheckBox8: TCheckBox
            Left = 10
            Top = 187
            Width = 109
            Height = 21
            Caption = 'CheckBox8'
            TabOrder = 0
          end
          object ScrollBar6: TScrollBar
            Left = 148
            Top = 30
            Width = 247
            Height = 20
            PageSize = 0
            TabOrder = 1
          end
          object StaticText6: TStaticText
            Left = 404
            Top = 30
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText6'
            TabOrder = 2
          end
          object ScrollBar7: TScrollBar
            Left = 148
            Top = 69
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 3
          end
          object StaticText7: TStaticText
            Left = 404
            Top = 69
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText7'
            TabOrder = 4
          end
          object ScrollBar8: TScrollBar
            Left = 148
            Top = 108
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 5
          end
          object StaticText8: TStaticText
            Left = 404
            Top = 108
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText8'
            TabOrder = 6
          end
          object ScrollBar9: TScrollBar
            Left = 148
            Top = 148
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 7
          end
          object StaticText9: TStaticText
            Left = 404
            Top = 148
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText9'
            TabOrder = 8
          end
          object ScrollBar10: TScrollBar
            Left = 148
            Top = 226
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 9
          end
          object StaticText10: TStaticText
            Left = 404
            Top = 226
            Width = 77
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText10'
            TabOrder = 10
          end
        end
        object GroupBox4: TGroupBox
          Left = 20
          Top = 30
          Width = 454
          Height = 99
          Caption = 'Pattern Detection'
          TabOrder = 2
          object Label6: TLabel
            Left = 10
            Top = 25
            Width = 41
            Height = 16
            Caption = 'Label6'
          end
          object Label7: TLabel
            Left = 10
            Top = 59
            Width = 41
            Height = 16
            Caption = 'Label7'
          end
          object ScrollBar1: TScrollBar
            Left = 148
            Top = 20
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 0
          end
          object StaticText1: TStaticText
            Left = 402
            Top = 20
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText1'
            TabOrder = 1
          end
          object ScrollBar2: TScrollBar
            Left = 148
            Top = 59
            Width = 247
            Height = 21
            PageSize = 0
            TabOrder = 2
          end
          object StaticText2: TStaticText
            Left = 402
            Top = 59
            Width = 70
            Height = 20
            BorderStyle = sbsSunken
            Caption = 'StaticText2'
            TabOrder = 3
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'JND'
        ImageIndex = 1
        DesignSize = (
          564
          630)
        object Label4: TLabel
          Left = 10
          Top = 10
          Width = 41
          Height = 16
          Caption = 'Label4'
        end
        object Label16: TLabel
          Left = 226
          Top = 10
          Width = 48
          Height = 16
          Caption = 'Label16'
        end
        object Label17: TLabel
          Left = 226
          Top = 39
          Width = 48
          Height = 16
          Caption = 'Label17'
        end
        object JND_LUT: TImage
          Left = 10
          Top = 64
          Width = 464
          Height = 518
          OnMouseDown = JND_LUTMouseDown
        end
        object ComboBox4: TComboBox
          Left = 10
          Top = 30
          Width = 188
          Height = 21
          ItemHeight = 0
          TabOrder = 0
          Text = 'ComboBox4'
        end
        object ScrollBar11: TScrollBar
          Left = 295
          Top = 10
          Width = 208
          Height = 21
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar12: TScrollBar
          Left = 295
          Top = 39
          Width = 208
          Height = 21
          PageSize = 0
          TabOrder = 2
        end
        object StaticText11: TStaticText
          Left = 512
          Top = 10
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText11'
          TabOrder = 3
        end
        object StaticText12: TStaticText
          Left = 512
          Top = 39
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText12'
          TabOrder = 4
        end
        object JND_Write: TButton
          Left = 492
          Top = 128
          Width = 51
          Height = 31
          Caption = 'Write'
          TabOrder = 5
          OnClick = JND_WriteClick
        end
        object btn_JND_Clear: TButton
          Left = 492
          Top = 207
          Width = 51
          Height = 31
          Caption = 'Clear'
          TabOrder = 6
          OnClick = btn_JND_ClearClick
        end
        object sg_JND_LUT: TStringGrid
          Left = 69
          Top = 591
          Width = 395
          Height = 31
          Anchors = [akLeft, akTop, akRight, akBottom]
          Color = clWhite
          ColCount = 16
          Ctl3D = False
          DefaultColWidth = 19
          DefaultRowHeight = 20
          FixedColor = clWindow
          FixedCols = 0
          RowCount = 1
          FixedRows = 0
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          ParentCtl3D = False
          ParentFont = False
          ParentShowHint = False
          ScrollBars = ssNone
          ShowHint = False
          TabOrder = 7
        end
        object JND_Read: TButton
          Left = 492
          Top = 167
          Width = 51
          Height = 31
          Caption = 'Read'
          TabOrder = 8
          OnClick = JND_ReadClick
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'ST'
        ImageIndex = 2
        object Label5: TLabel
          Left = 10
          Top = 10
          Width = 41
          Height = 16
          Caption = 'Label5'
        end
        object Label18: TLabel
          Left = 236
          Top = 10
          Width = 48
          Height = 16
          Caption = 'Label18'
        end
        object Label19: TLabel
          Left = 236
          Top = 39
          Width = 48
          Height = 16
          Caption = 'Label19'
        end
        object ST_LUT: TImage
          Left = 10
          Top = 64
          Width = 464
          Height = 518
          OnMouseDown = ST_LUTMouseDown
        end
        object ComboBox5: TComboBox
          Left = 10
          Top = 30
          Width = 198
          Height = 21
          ItemHeight = 0
          TabOrder = 0
          Text = 'ComboBox5'
        end
        object ScrollBar13: TScrollBar
          Left = 295
          Top = 10
          Width = 208
          Height = 21
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar14: TScrollBar
          Left = 295
          Top = 39
          Width = 208
          Height = 21
          PageSize = 0
          TabOrder = 2
        end
        object StaticText13: TStaticText
          Left = 512
          Top = 10
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText13'
          TabOrder = 3
        end
        object StaticText14: TStaticText
          Left = 512
          Top = 39
          Width = 77
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText14'
          TabOrder = 4
        end
        object sg_ST_LUT: TStringGrid
          Left = 69
          Top = 591
          Width = 395
          Height = 31
          Color = clWhite
          ColCount = 16
          Ctl3D = False
          DefaultColWidth = 19
          DefaultRowHeight = 20
          FixedColor = clWindow
          FixedCols = 0
          RowCount = 1
          FixedRows = 0
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          ParentCtl3D = False
          ParentFont = False
          ParentShowHint = False
          ScrollBars = ssNone
          ShowHint = False
          TabOrder = 5
        end
        object ST_Write: TButton
          Left = 492
          Top = 128
          Width = 51
          Height = 31
          Caption = 'Write'
          TabOrder = 6
          OnClick = ST_WriteClick
        end
        object btn_ST_Clear: TButton
          Left = 492
          Top = 207
          Width = 51
          Height = 31
          Caption = 'Clear'
          TabOrder = 7
          OnClick = btn_ST_ClearClick
        end
        object ST_Read: TButton
          Left = 492
          Top = 167
          Width = 51
          Height = 31
          Caption = 'Read'
          TabOrder = 8
          OnClick = ST_ReadClick
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'MAX'
        ImageIndex = 3
        object MAX_LUT: TImage
          Left = 10
          Top = 64
          Width = 464
          Height = 518
          OnMouseDown = MAX_LUTMouseDown
        end
        object sg_MAX_LUT: TStringGrid
          Left = 69
          Top = 591
          Width = 395
          Height = 31
          Color = clWhite
          ColCount = 16
          Ctl3D = False
          DefaultColWidth = 19
          DefaultRowHeight = 20
          FixedColor = clWindow
          FixedCols = 0
          RowCount = 1
          FixedRows = 0
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          ParentCtl3D = False
          ParentFont = False
          ParentShowHint = False
          ScrollBars = ssNone
          ShowHint = False
          TabOrder = 0
        end
        object MAX_Write: TButton
          Left = 492
          Top = 128
          Width = 51
          Height = 31
          Caption = 'Write'
          TabOrder = 1
          OnClick = MAX_WriteClick
        end
        object btn_MAX_Clear: TButton
          Left = 492
          Top = 207
          Width = 51
          Height = 31
          Caption = 'Clear'
          TabOrder = 2
          OnClick = btn_MAX_ClearClick
        end
        object MAX_Read: TButton
          Left = 492
          Top = 167
          Width = 51
          Height = 31
          Caption = 'Read'
          TabOrder = 3
          OnClick = MAX_ReadClick
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'MIN'
        ImageIndex = 4
        object MIN_LUT: TImage
          Left = 10
          Top = 64
          Width = 464
          Height = 518
          OnMouseDown = MIN_LUTMouseDown
        end
        object sg_MIN_LUT: TStringGrid
          Left = 69
          Top = 591
          Width = 395
          Height = 31
          Color = clWhite
          ColCount = 16
          Ctl3D = False
          DefaultColWidth = 19
          DefaultRowHeight = 20
          FixedColor = clWindow
          FixedCols = 0
          RowCount = 1
          FixedRows = 0
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          ParentCtl3D = False
          ParentFont = False
          ParentShowHint = False
          ScrollBars = ssNone
          ShowHint = False
          TabOrder = 0
        end
        object MIN_Write: TButton
          Left = 492
          Top = 128
          Width = 51
          Height = 31
          Caption = 'Write'
          TabOrder = 1
          OnClick = MIN_WriteClick
        end
        object btn_MIN_Clear: TButton
          Left = 492
          Top = 207
          Width = 51
          Height = 31
          Caption = 'Clear'
          TabOrder = 2
          OnClick = btn_MIN_ClearClick
        end
        object MIN_Read: TButton
          Left = 492
          Top = 167
          Width = 51
          Height = 31
          Caption = 'Read'
          TabOrder = 3
          OnClick = MIN_ReadClick
        end
      end
    end
    object ComboBox3: TComboBox
      Left = 10
      Top = 453
      Width = 168
      Height = 24
      ItemHeight = 16
      TabOrder = 9
      Text = 'ComboBox3'
    end
    object rg_ce_mode: TRadioGroup
      Left = 10
      Top = 187
      Width = 228
      Height = 51
      Caption = 'CE Mode'
      Columns = 3
      Items.Strings = (
        '1'
        '2'
        '3')
      TabOrder = 10
      OnClick = rg_ce_modeClick
    end
    object btn_CE_load: TButton
      Left = 10
      Top = 256
      Width = 70
      Height = 31
      Caption = 'Load File'
      TabOrder = 11
      OnClick = btn_CE_loadClick
    end
    object btn_CE_save: TButton
      Left = 89
      Top = 256
      Width = 70
      Height = 31
      Caption = 'Save File'
      TabOrder = 12
      OnClick = btn_CE_saveClick
    end
    object btn_wrt_all: TButton
      Left = 167
      Top = 256
      Width = 71
      Height = 31
      Caption = 'Write All'
      TabOrder = 13
      OnClick = btn_wrt_allClick
    end
    object Btn_CE_reload: TBitBtn
      Left = 30
      Top = 551
      Width = 89
      Height = 31
      Caption = '&Reload'
      ModalResult = 6
      TabOrder = 14
      OnClick = Btn_CE_reloadClick
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
    object CheckBox9: TCheckBox
      Left = 10
      Top = 59
      Width = 188
      Height = 21
      Caption = 'CheckBox9'
      TabOrder = 15
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 624
    Top = 65528
  end
  object SaveDialog1: TSaveDialog
    Left = 656
    Top = 65528
  end
end
