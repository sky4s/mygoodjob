object ContrastEnhanceForm1: TContrastEnhanceForm1
  Left = 369
  Top = 145
  Width = 687
  Height = 570
  Caption = 'Contrast Enhancement'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
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
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox3: TGroupBox
    Left = 8
    Top = 0
    Width = 665
    Height = 545
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 248
      Width = 32
      Height = 13
      Caption = 'Label1'
    end
    object Label2: TLabel
      Left = 8
      Top = 304
      Width = 32
      Height = 13
      Caption = 'Label2'
    end
    object Label3: TLabel
      Left = 8
      Top = 352
      Width = 32
      Height = 13
      Caption = 'Label3'
    end
    object CheckBox1: TCheckBox
      Left = 8
      Top = 16
      Width = 81
      Height = 17
      Caption = 'CheckBox1'
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 112
      Top = 16
      Width = 81
      Height = 17
      Caption = 'CheckBox2'
      TabOrder = 1
    end
    object CheckBox3: TCheckBox
      Left = 8
      Top = 80
      Width = 97
      Height = 17
      Caption = 'CheckBox3'
      TabOrder = 2
    end
    object CheckBox4: TCheckBox
      Left = 112
      Top = 80
      Width = 97
      Height = 17
      Caption = 'CheckBox4'
      TabOrder = 3
    end
    object CheckBox5: TCheckBox
      Left = 8
      Top = 112
      Width = 97
      Height = 17
      Caption = 'CheckBox5'
      TabOrder = 4
    end
    object CheckBox6: TCheckBox
      Left = 112
      Top = 112
      Width = 89
      Height = 17
      Caption = 'CheckBox6'
      TabOrder = 5
    end
    object ComboBox1: TComboBox
      Left = 8
      Top = 264
      Width = 137
      Height = 21
      ItemHeight = 13
      TabOrder = 6
      Text = 'ComboBox1'
    end
    object ComboBox2: TComboBox
      Left = 8
      Top = 320
      Width = 137
      Height = 21
      ItemHeight = 13
      TabOrder = 7
      Text = 'ComboBox2'
    end
    object PageControl1: TPageControl
      Left = 200
      Top = 8
      Width = 465
      Height = 537
      ActivePage = TabSheet5
      TabIndex = 4
      TabOrder = 8
      object TabSheet1: TTabSheet
        Caption = 'Progressive Gamma \ Contrast Setting'
        object GroupBox1: TGroupBox
          Left = 16
          Top = 128
          Width = 369
          Height = 137
          Caption = 'Progressive Gamma'
          TabOrder = 0
          object Label8: TLabel
            Left = 8
            Top = 40
            Width = 32
            Height = 13
            Caption = 'Label8'
          end
          object Label9: TLabel
            Left = 8
            Top = 72
            Width = 32
            Height = 13
            Caption = 'Label9'
          end
          object Label10: TLabel
            Left = 8
            Top = 104
            Width = 38
            Height = 13
            Caption = 'Label10'
          end
          object CheckBox7: TCheckBox
            Left = 8
            Top = 16
            Width = 121
            Height = 25
            Caption = 'CheckBox7'
            TabOrder = 0
          end
          object ScrollBar3: TScrollBar
            Left = 120
            Top = 40
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 1
          end
          object StaticText3: TStaticText
            Left = 328
            Top = 40
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText3'
            TabOrder = 2
          end
          object ScrollBar4: TScrollBar
            Left = 120
            Top = 72
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 3
          end
          object ScrollBar5: TScrollBar
            Left = 120
            Top = 104
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 4
          end
          object StaticText4: TStaticText
            Left = 328
            Top = 72
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText4'
            TabOrder = 5
          end
          object StaticText5: TStaticText
            Left = 328
            Top = 104
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText5'
            TabOrder = 6
          end
        end
        object GroupBox2: TGroupBox
          Left = 16
          Top = 288
          Width = 369
          Height = 209
          Caption = 'Contrast Setting'
          TabOrder = 1
          object Label11: TLabel
            Left = 8
            Top = 24
            Width = 38
            Height = 13
            Caption = 'Label11'
          end
          object Label12: TLabel
            Left = 8
            Top = 56
            Width = 38
            Height = 13
            Caption = 'Label12'
          end
          object Label13: TLabel
            Left = 8
            Top = 88
            Width = 38
            Height = 13
            Caption = 'Label13'
          end
          object Label14: TLabel
            Left = 8
            Top = 120
            Width = 38
            Height = 13
            Caption = 'Label14'
          end
          object Label15: TLabel
            Left = 8
            Top = 176
            Width = 38
            Height = 13
            Caption = 'Label15'
          end
          object CheckBox8: TCheckBox
            Left = 8
            Top = 152
            Width = 89
            Height = 17
            Caption = 'CheckBox8'
            TabOrder = 0
          end
          object ScrollBar6: TScrollBar
            Left = 120
            Top = 24
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 1
          end
          object StaticText6: TStaticText
            Left = 328
            Top = 24
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText6'
            TabOrder = 2
          end
          object ScrollBar7: TScrollBar
            Left = 120
            Top = 56
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 3
          end
          object StaticText7: TStaticText
            Left = 328
            Top = 56
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText7'
            TabOrder = 4
          end
          object ScrollBar8: TScrollBar
            Left = 120
            Top = 88
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 5
          end
          object StaticText8: TStaticText
            Left = 328
            Top = 88
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText8'
            TabOrder = 6
          end
          object ScrollBar9: TScrollBar
            Left = 120
            Top = 120
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 7
          end
          object StaticText9: TStaticText
            Left = 328
            Top = 120
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText9'
            TabOrder = 8
          end
          object ScrollBar10: TScrollBar
            Left = 120
            Top = 184
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 9
          end
          object StaticText10: TStaticText
            Left = 328
            Top = 184
            Width = 64
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText10'
            TabOrder = 10
          end
        end
        object GroupBox4: TGroupBox
          Left = 16
          Top = 24
          Width = 369
          Height = 81
          Caption = 'Pattern Detection'
          TabOrder = 2
          object Label6: TLabel
            Left = 8
            Top = 20
            Width = 32
            Height = 13
            Caption = 'Label6'
          end
          object Label7: TLabel
            Left = 8
            Top = 48
            Width = 32
            Height = 13
            Caption = 'Label7'
          end
          object ScrollBar1: TScrollBar
            Left = 120
            Top = 16
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 0
          end
          object StaticText1: TStaticText
            Left = 327
            Top = 16
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText1'
            TabOrder = 1
          end
          object ScrollBar2: TScrollBar
            Left = 120
            Top = 48
            Width = 201
            Height = 17
            PageSize = 0
            TabOrder = 2
          end
          object StaticText2: TStaticText
            Left = 327
            Top = 48
            Width = 58
            Height = 17
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
          457
          509)
        object Label4: TLabel
          Left = 8
          Top = 8
          Width = 32
          Height = 13
          Caption = 'Label4'
        end
        object Label16: TLabel
          Left = 184
          Top = 8
          Width = 38
          Height = 13
          Caption = 'Label16'
        end
        object Label17: TLabel
          Left = 184
          Top = 32
          Width = 38
          Height = 13
          Caption = 'Label17'
        end
        object JND_LUT: TImage
          Left = 8
          Top = 52
          Width = 377
          Height = 421
          OnMouseDown = JND_LUTMouseDown
        end
        object ComboBox4: TComboBox
          Left = 8
          Top = 24
          Width = 153
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'ComboBox4'
        end
        object ScrollBar11: TScrollBar
          Left = 240
          Top = 8
          Width = 169
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar12: TScrollBar
          Left = 240
          Top = 32
          Width = 169
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText11: TStaticText
          Left = 416
          Top = 8
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText11'
          TabOrder = 3
        end
        object StaticText12: TStaticText
          Left = 416
          Top = 32
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText12'
          TabOrder = 4
        end
        object JND_Write: TButton
          Left = 400
          Top = 104
          Width = 41
          Height = 25
          Caption = 'Write'
          TabOrder = 5
          OnClick = JND_WriteClick
        end
        object btn_JND_Clear: TButton
          Left = 400
          Top = 168
          Width = 41
          Height = 25
          Caption = 'Clear'
          TabOrder = 6
          OnClick = btn_JND_ClearClick
        end
        object sg_JND_LUT: TStringGrid
          Left = 56
          Top = 480
          Width = 321
          Height = 25
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
          Font.Height = -12
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
          Left = 400
          Top = 136
          Width = 41
          Height = 25
          Caption = 'Read'
          TabOrder = 8
          OnClick = JND_ReadClick
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'ST'
        ImageIndex = 2
        object Label5: TLabel
          Left = 8
          Top = 8
          Width = 32
          Height = 13
          Caption = 'Label5'
        end
        object Label18: TLabel
          Left = 192
          Top = 8
          Width = 38
          Height = 13
          Caption = 'Label18'
        end
        object Label19: TLabel
          Left = 192
          Top = 32
          Width = 38
          Height = 13
          Caption = 'Label19'
        end
        object ST_LUT: TImage
          Left = 8
          Top = 52
          Width = 377
          Height = 421
          OnMouseDown = ST_LUTMouseDown
        end
        object ComboBox5: TComboBox
          Left = 8
          Top = 24
          Width = 161
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'ComboBox5'
        end
        object ScrollBar13: TScrollBar
          Left = 240
          Top = 8
          Width = 169
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar14: TScrollBar
          Left = 240
          Top = 32
          Width = 169
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText13: TStaticText
          Left = 416
          Top = 8
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText13'
          TabOrder = 3
        end
        object StaticText14: TStaticText
          Left = 416
          Top = 32
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText14'
          TabOrder = 4
        end
        object sg_ST_LUT: TStringGrid
          Left = 56
          Top = 480
          Width = 321
          Height = 25
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
          Font.Height = -12
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
          Left = 400
          Top = 104
          Width = 41
          Height = 25
          Caption = 'Write'
          TabOrder = 6
          OnClick = ST_WriteClick
        end
        object btn_ST_Clear: TButton
          Left = 400
          Top = 168
          Width = 41
          Height = 25
          Caption = 'Clear'
          TabOrder = 7
          OnClick = btn_ST_ClearClick
        end
        object ST_Read: TButton
          Left = 400
          Top = 136
          Width = 41
          Height = 25
          Caption = 'Read'
          TabOrder = 8
          OnClick = ST_ReadClick
        end
      end
      object TabSheet4: TTabSheet
        Caption = 'MAX'
        ImageIndex = 3
        object MAX_LUT: TImage
          Left = 8
          Top = 52
          Width = 377
          Height = 421
          OnMouseDown = MAX_LUTMouseDown
        end
        object sg_MAX_LUT: TStringGrid
          Left = 56
          Top = 480
          Width = 321
          Height = 25
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
          Font.Height = -12
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
          Left = 400
          Top = 104
          Width = 41
          Height = 25
          Caption = 'Write'
          TabOrder = 1
          OnClick = MAX_WriteClick
        end
        object btn_MAX_Clear: TButton
          Left = 400
          Top = 168
          Width = 41
          Height = 25
          Caption = 'Clear'
          TabOrder = 2
          OnClick = btn_MAX_ClearClick
        end
        object MAX_Read: TButton
          Left = 400
          Top = 136
          Width = 41
          Height = 25
          Caption = 'Read'
          TabOrder = 3
          OnClick = MAX_ReadClick
        end
      end
      object TabSheet5: TTabSheet
        Caption = 'MIN'
        ImageIndex = 4
        object MIN_LUT: TImage
          Left = 8
          Top = 52
          Width = 377
          Height = 421
          OnMouseDown = MIN_LUTMouseDown
        end
        object sg_MIN_LUT: TStringGrid
          Left = 56
          Top = 480
          Width = 321
          Height = 25
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
          Font.Height = -12
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
          Left = 400
          Top = 104
          Width = 41
          Height = 25
          Caption = 'Write'
          TabOrder = 1
          OnClick = MIN_WriteClick
        end
        object btn_MIN_Clear: TButton
          Left = 400
          Top = 168
          Width = 41
          Height = 25
          Caption = 'Clear'
          TabOrder = 2
          OnClick = btn_MIN_ClearClick
        end
        object MIN_Read: TButton
          Left = 400
          Top = 136
          Width = 41
          Height = 25
          Caption = 'Read'
          TabOrder = 3
          OnClick = MIN_ReadClick
        end
      end
    end
    object ComboBox3: TComboBox
      Left = 8
      Top = 368
      Width = 137
      Height = 21
      ItemHeight = 13
      TabOrder = 9
      Text = 'ComboBox3'
    end
    object rg_ce_mode: TRadioGroup
      Left = 8
      Top = 152
      Width = 185
      Height = 41
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
      Left = 8
      Top = 208
      Width = 57
      Height = 25
      Caption = 'Load File'
      TabOrder = 11
      OnClick = btn_CE_loadClick
    end
    object btn_CE_save: TButton
      Left = 72
      Top = 208
      Width = 57
      Height = 25
      Caption = 'Save File'
      TabOrder = 12
      OnClick = btn_CE_saveClick
    end
    object btn_wrt_all: TButton
      Left = 136
      Top = 208
      Width = 57
      Height = 25
      Caption = 'Write All'
      TabOrder = 13
      OnClick = btn_wrt_allClick
    end
    object Btn_CE_reload: TBitBtn
      Left = 24
      Top = 448
      Width = 73
      Height = 25
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
      Left = 8
      Top = 48
      Width = 153
      Height = 17
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
