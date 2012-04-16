object FunctionForm1: TFunctionForm1
  Left = 558
  Top = 241
  Width = 724
  Height = 534
  Align = alCustom
  Caption = 'Function'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  PrintScale = poPrintToFit
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object pc_Function: TPageControl
    Left = 0
    Top = 0
    Width = 713
    Height = 497
    ActivePage = ts_frc_gamma
    TabIndex = 0
    TabOrder = 0
    object ts_frc_gamma: TTabSheet
      Caption = 'FRC/D&G'
      object GroupBox1: TGroupBox
        Left = 16
        Top = 8
        Width = 249
        Height = 281
        Caption = 'FRC'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label3: TLabel
          Left = 176
          Top = 216
          Width = 39
          Height = 13
          Caption = 'Label3'
        end
        object CheckBox5: TCheckBox
          Left = 16
          Top = 72
          Width = 161
          Height = 25
          Caption = 'CheckBox5'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object CheckBox6: TCheckBox
          Left = 16
          Top = 120
          Width = 153
          Height = 17
          Caption = 'CheckBox6'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object CheckBox7: TCheckBox
          Left = 16
          Top = 168
          Width = 161
          Height = 17
          Caption = 'CheckBox7'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object CheckBox9: TCheckBox
          Left = 16
          Top = 216
          Width = 169
          Height = 17
          Caption = 'CheckBox9'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox14: TCheckBox
          Left = 16
          Top = 32
          Width = 169
          Height = 17
          Caption = 'CheckBox14'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object ComboBox3: TComboBox
          Left = 96
          Top = 400
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 5
          Text = 'ComboBox3'
        end
      end
      object GroupBox2: TGroupBox
        Left = 272
        Top = 8
        Width = 409
        Height = 409
        Caption = 'Digital Gamma'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object sg_dg: TStringGrid
          Left = 16
          Top = 24
          Width = 225
          Height = 377
          ColCount = 4
          DefaultColWidth = 50
          DefaultRowHeight = 20
          RowCount = 258
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
          ParentFont = False
          TabOrder = 0
          RowHeights = (
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20
            20)
        end
        object btn_dg_read: TButton
          Left = 312
          Top = 64
          Width = 65
          Height = 25
          Caption = '&Read'
          TabOrder = 1
          OnClick = btn_dg_readClick
        end
        object btn_dg_wrt: TButton
          Left = 312
          Top = 112
          Width = 65
          Height = 25
          Caption = '&Write'
          TabOrder = 2
          OnClick = btn_dg_wrtClick
        end
        object btn_dg_save: TButton
          Left = 312
          Top = 160
          Width = 65
          Height = 25
          Caption = '&Save File'
          TabOrder = 3
          OnClick = btn_dg_saveClick
        end
        object btn_dg_load: TButton
          Left = 312
          Top = 208
          Width = 65
          Height = 25
          Caption = '&Load File'
          TabOrder = 4
          OnClick = btn_dg_loadClick
        end
        object CheckBox8: TCheckBox
          Left = 112
          Top = 0
          Width = 89
          Height = 17
          Caption = 'CheckBox8'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object CheckBox_FuncOn: TCheckBox
          Left = 312
          Top = 88
          Width = 73
          Height = 17
          Caption = 'Func On'
          TabOrder = 6
        end
      end
      object Btn_FRC_DG_reload: TBitBtn
        Left = 16
        Top = 336
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 2
        OnClick = Btn_FRC_DG_reloadClick
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
    end
    object ts_p_state: TTabSheet
      Caption = '&Pstate'
      ImageIndex = 2
      TabVisible = False
      object Label1: TLabel
        Left = 24
        Top = 160
        Width = 32
        Height = 13
        Caption = 'Label1'
      end
      object CheckBox1: TCheckBox
        Left = 24
        Top = 24
        Width = 121
        Height = 17
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 168
        Top = 24
        Width = 113
        Height = 25
        Caption = 'CheckBox2'
        TabOrder = 1
      end
      object ComboBox1: TComboBox
        Left = 24
        Top = 176
        Width = 113
        Height = 21
        ItemHeight = 13
        TabOrder = 2
        Text = 'ComboBox1'
      end
      object LabeledEdit1: TLabeledEdit
        Left = 24
        Top = 72
        Width = 73
        Height = 21
        EditLabel.Width = 51
        EditLabel.Height = 11
        EditLabel.Caption = 'LabeledEdit1'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
      object LabeledEdit2: TLabeledEdit
        Left = 24
        Top = 120
        Width = 73
        Height = 21
        EditLabel.Width = 51
        EditLabel.Height = 11
        EditLabel.Caption = 'LabeledEdit2'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 4
      end
      object LabeledEdit3: TLabeledEdit
        Left = 168
        Top = 72
        Width = 73
        Height = 21
        EditLabel.Width = 51
        EditLabel.Height = 11
        EditLabel.Caption = 'LabeledEdit3'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 5
      end
      object LabeledEdit4: TLabeledEdit
        Left = 168
        Top = 120
        Width = 73
        Height = 21
        EditLabel.Width = 51
        EditLabel.Height = 11
        EditLabel.Caption = 'LabeledEdit4'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 6
      end
      object Btn_Pstate_reload: TBitBtn
        Left = 32
        Top = 336
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 7
        OnClick = Btn_Pstate_reloadClick
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
    end
    object ts_agbs: TTabSheet
      Caption = '&AGBS'
      ImageIndex = 3
      TabVisible = False
      object CheckBox3: TCheckBox
        Left = 32
        Top = 24
        Width = 105
        Height = 25
        Caption = 'CheckBox3'
        TabOrder = 0
      end
      object CheckBox4: TCheckBox
        Left = 32
        Top = 64
        Width = 105
        Height = 17
        Caption = 'CheckBox4'
        TabOrder = 1
      end
      object LabeledEdit5: TLabeledEdit
        Left = 32
        Top = 176
        Width = 89
        Height = 21
        EditLabel.Width = 50
        EditLabel.Height = 11
        EditLabel.Caption = 'LabeledEdit5'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
      object LabeledEdit6: TLabeledEdit
        Left = 32
        Top = 232
        Width = 89
        Height = 21
        EditLabel.Width = 50
        EditLabel.Height = 11
        EditLabel.Caption = 'LabeledEdit6'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
      object LabeledEdit7: TLabeledEdit
        Left = 32
        Top = 288
        Width = 89
        Height = 21
        EditLabel.Width = 50
        EditLabel.Height = 10
        EditLabel.Caption = 'LabeledEdit7'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 4
      end
      object Btn_AGBS_reload: TBitBtn
        Left = 32
        Top = 336
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 5
        OnClick = Btn_AGBS_reloadClick
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
      object CheckBox13: TCheckBox
        Left = 32
        Top = 104
        Width = 105
        Height = 17
        Caption = 'CheckBox13'
        TabOrder = 6
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'OD'
      ImageIndex = 3
      TabVisible = False
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 705
        Height = 473
        ActivePage = TabSheet6
        TabIndex = 0
        TabOrder = 0
        object TabSheet6: TTabSheet
          Caption = 'OD Setting'
          object Label4: TLabel
            Left = 208
            Top = 24
            Width = 32
            Height = 13
            Caption = 'Label4'
          end
          object Label5: TLabel
            Left = 208
            Top = 58
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label6: TLabel
            Left = 208
            Top = 90
            Width = 32
            Height = 13
            Caption = 'Label6'
          end
          object Label7: TLabel
            Left = 208
            Top = 134
            Width = 32
            Height = 13
            Caption = 'Label7'
          end
          object Label8: TLabel
            Left = 128
            Top = 208
            Width = 32
            Height = 13
            Caption = 'Label8'
          end
          object Label9: TLabel
            Left = 128
            Top = 240
            Width = 32
            Height = 13
            Caption = 'Label9'
          end
          object Label10: TLabel
            Left = 128
            Top = 272
            Width = 38
            Height = 13
            Caption = 'Label10'
          end
          object CheckBox10: TCheckBox
            Left = 40
            Top = 24
            Width = 121
            Height = 25
            Caption = 'CheckBox10'
            TabOrder = 0
          end
          object CheckBox11: TCheckBox
            Left = 40
            Top = 56
            Width = 113
            Height = 17
            Caption = 'CheckBox11'
            TabOrder = 1
          end
          object CheckBox12: TCheckBox
            Left = 40
            Top = 88
            Width = 113
            Height = 17
            Caption = 'CheckBox12'
            TabOrder = 2
          end
          object ComboBox4: TComboBox
            Left = 304
            Top = 16
            Width = 145
            Height = 21
            ItemHeight = 13
            TabOrder = 3
            Text = 'ComboBox4'
          end
          object ComboBox5: TComboBox
            Left = 304
            Top = 56
            Width = 145
            Height = 21
            ItemHeight = 13
            TabOrder = 4
            Text = 'ComboBox5'
          end
          object ComboBox6: TComboBox
            Left = 304
            Top = 88
            Width = 145
            Height = 21
            ItemHeight = 13
            TabOrder = 5
            Text = 'ComboBox6'
          end
          object ComboBox7: TComboBox
            Left = 304
            Top = 128
            Width = 145
            Height = 21
            ItemHeight = 13
            TabOrder = 6
            Text = 'ComboBox7'
          end
          object ScrollBar3: TScrollBar
            Left = 224
            Top = 272
            Width = 225
            Height = 17
            PageSize = 0
            TabOrder = 7
          end
          object ScrollBar2: TScrollBar
            Left = 224
            Top = 240
            Width = 225
            Height = 17
            PageSize = 0
            TabOrder = 8
          end
          object ScrollBar1: TScrollBar
            Left = 224
            Top = 208
            Width = 225
            Height = 17
            PageSize = 0
            TabOrder = 9
          end
          object StaticText1: TStaticText
            Left = 463
            Top = 208
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText1'
            TabOrder = 10
          end
          object StaticText2: TStaticText
            Left = 463
            Top = 240
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText2'
            TabOrder = 11
          end
          object StaticText3: TStaticText
            Left = 463
            Top = 272
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText3'
            TabOrder = 12
          end
        end
        object TabSheet7: TTabSheet
          Caption = 'OD Table'
          ImageIndex = 1
          object OD: TPageControl
            Left = 0
            Top = 16
            Width = 697
            Height = 425
            ActivePage = TabSheet4
            TabIndex = 0
            TabOrder = 0
            object TabSheet4: TTabSheet
              Caption = 'OD1_LUT'
              object Label13: TLabel
                Left = 80
                Top = 0
                Width = 47
                Height = 16
                Caption = 'Target'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label14: TLabel
                Left = 0
                Top = 24
                Width = 33
                Height = 16
                Caption = 'Start'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object sg_od_1: TStringGrid
                Left = 40
                Top = 16
                Width = 649
                Height = 380
                ColCount = 19
                DefaultColWidth = 35
                DefaultRowHeight = 20
                RowCount = 19
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
                ScrollBars = ssNone
                TabOrder = 0
                ColWidths = (
                  35
                  37
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35
                  35)
              end
            end
            object TabSheet5: TTabSheet
              Caption = 'OD2_LUT'
              ImageIndex = 1
              object Label15: TLabel
                Left = 80
                Top = 0
                Width = 47
                Height = 16
                Caption = 'Target'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object Label16: TLabel
                Left = 0
                Top = 24
                Width = 33
                Height = 16
                Caption = 'Start'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -15
                Font.Name = 'MS Sans Serif'
                Font.Style = [fsBold]
                ParentFont = False
              end
              object sg_od_2: TStringGrid
                Left = 40
                Top = 16
                Width = 649
                Height = 380
                ColCount = 19
                DefaultColWidth = 35
                DefaultRowHeight = 20
                RowCount = 19
                Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
                ScrollBars = ssNone
                TabOrder = 0
              end
            end
          end
          object btn_od_read: TButton
            Left = 336
            Top = 8
            Width = 57
            Height = 25
            Caption = '&Read'
            TabOrder = 1
          end
          object btn_od_write: TButton
            Left = 408
            Top = 8
            Width = 57
            Height = 25
            Caption = '&Write'
            TabOrder = 2
          end
          object btn_od_load: TButton
            Left = 480
            Top = 8
            Width = 57
            Height = 25
            Caption = '&Load File'
            TabOrder = 3
          end
          object btn_od_save: TButton
            Left = 552
            Top = 8
            Width = 57
            Height = 25
            Caption = '&Save File'
            TabOrder = 4
            OnClick = btn_od_saveClick
          end
          object rg_od_table_type: TRadioGroup
            Left = 168
            Top = 0
            Width = 153
            Height = 33
            Caption = 'TableType'
            Columns = 2
            ItemIndex = 0
            Items.Strings = (
              'Difference'
              'Target')
            TabOrder = 5
            OnClick = rg_od_table_typeClick
          end
        end
      end
      object Btn_OD_reload: TBitBtn
        Left = 632
        Top = 0
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 1
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
    end
  end
  object LoadDialog: TOpenDialog
    Left = 632
    Top = 65528
  end
  object SaveDialog: TSaveDialog
    Filter = 'Text|*.txt'
    Left = 664
    Top = 65528
  end
end
