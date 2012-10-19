object FunctionForm: TFunctionForm
  Left = 494
  Top = 216
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
  KeyPreview = True
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
        Height = 177
        Caption = 'FRC'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label3: TLabel
          Left = 192
          Top = 128
          Width = 39
          Height = 13
          Caption = 'Label3'
        end
        object CheckBox5: TCheckBox
          Left = 16
          Top = 56
          Width = 161
          Height = 17
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
          Top = 80
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
          Top = 104
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
          Top = 128
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
          Left = 16
          Top = 152
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
          Top = 24
          Width = 65
          Height = 25
          Caption = '&Read'
          TabOrder = 1
          OnClick = btn_dg_readClick
        end
        object btn_dg_wrt: TButton
          Left = 312
          Top = 64
          Width = 65
          Height = 25
          Caption = '&Write'
          TabOrder = 2
          OnClick = btn_dg_wrtClick
        end
        object btn_dg_save: TButton
          Left = 312
          Top = 96
          Width = 65
          Height = 25
          Caption = '&Save File'
          TabOrder = 3
          OnClick = btn_dg_saveClick
        end
        object btn_dg_load: TButton
          Left = 312
          Top = 128
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
          Top = 48
          Width = 73
          Height = 17
          Caption = 'Func On'
          TabOrder = 6
        end
      end
      object Btn_FRC_DG_reload: TBitBtn
        Left = 584
        Top = 168
        Width = 65
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
      object GroupBox_ManualAdjust: TGroupBox
        Left = 16
        Top = 200
        Width = 249
        Height = 121
        Caption = 'Manual Adjust'
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        object Edit_R: TEdit
          Left = 32
          Top = 56
          Width = 41
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          Text = '255'
        end
        object Edit_G: TEdit
          Left = 80
          Top = 56
          Width = 41
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          Text = '255'
        end
        object Edit_B: TEdit
          Left = 128
          Top = 56
          Width = 41
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          Text = '255'
        end
        object Button_RAdd: TButton
          Left = 32
          Top = 24
          Width = 41
          Height = 25
          Caption = 'R+'
          TabOrder = 3
          OnClick = Button_RAddClick
        end
        object Button_GAdd: TButton
          Left = 80
          Top = 24
          Width = 41
          Height = 25
          Caption = 'G+'
          TabOrder = 4
          OnClick = Button_GAddClick
        end
        object Button_BAdd: TButton
          Left = 128
          Top = 24
          Width = 41
          Height = 25
          Caption = 'B+'
          TabOrder = 5
          OnClick = Button_BAddClick
        end
        object Button_RMinus: TButton
          Left = 32
          Top = 80
          Width = 41
          Height = 25
          Caption = 'R-'
          TabOrder = 6
          OnClick = Button_RMinusClick
        end
        object Button_GMinus: TButton
          Left = 80
          Top = 80
          Width = 41
          Height = 25
          Caption = 'G-'
          TabOrder = 7
          OnClick = Button_GMinusClick
        end
        object Button_BMinus: TButton
          Left = 128
          Top = 80
          Width = 41
          Height = 25
          Caption = 'B-'
          TabOrder = 8
          OnClick = Button_BMinusClick
        end
      end
      object CheckBox_ManualEnable: TCheckBox
        Left = 200
        Top = 200
        Width = 57
        Height = 17
        Caption = 'Enable'
        TabOrder = 4
        OnClick = CheckBox_ManualEnableClick
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
