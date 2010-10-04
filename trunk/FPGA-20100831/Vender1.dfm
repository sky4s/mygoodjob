object VenderForm1: TVenderForm1
  Left = 263
  Top = 175
  Width = 717
  Height = 497
  Caption = 'Vender'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 868
    Height = 562
    ActivePage = ts_vender
    TabIndex = 0
    TabOrder = 0
    object ts_vender: TTabSheet
      Caption = 'Vender'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 5
        Width = 868
        Height = 528
        TabOrder = 0
        object Label1: TLabel
          Left = 256
          Top = 30
          Width = 41
          Height = 16
          Caption = 'Label1'
        end
        object Label2: TLabel
          Left = 256
          Top = 69
          Width = 41
          Height = 16
          Caption = 'Label2'
        end
        object Label3: TLabel
          Left = 256
          Top = 108
          Width = 41
          Height = 16
          Caption = 'Label3'
        end
        object Label4: TLabel
          Left = 256
          Top = 148
          Width = 41
          Height = 16
          Caption = 'Label4'
        end
        object Label5: TLabel
          Left = 256
          Top = 187
          Width = 41
          Height = 16
          Caption = 'Label5'
        end
        object Label6: TLabel
          Left = 256
          Top = 226
          Width = 41
          Height = 16
          Caption = 'Label6'
        end
        object Label7: TLabel
          Left = 256
          Top = 266
          Width = 41
          Height = 16
          Caption = 'Label7'
        end
        object CheckBox1: TCheckBox
          Left = 20
          Top = 30
          Width = 178
          Height = 20
          Caption = 'CheckBox1'
          TabOrder = 0
        end
        object CheckBox2: TCheckBox
          Left = 20
          Top = 69
          Width = 208
          Height = 21
          Caption = 'CheckBox2'
          TabOrder = 1
        end
        object CheckBox3: TCheckBox
          Left = 20
          Top = 108
          Width = 208
          Height = 21
          Caption = 'CheckBox3'
          TabOrder = 2
        end
        object CheckBox4: TCheckBox
          Left = 20
          Top = 148
          Width = 218
          Height = 21
          Caption = 'CheckBox4'
          TabOrder = 3
        end
        object ComboBox1: TComboBox
          Left = 423
          Top = 30
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 4
          Text = 'ComboBox1'
        end
        object ComboBox2: TComboBox
          Left = 423
          Top = 69
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 5
          Text = 'ComboBox2'
        end
        object ComboBox3: TComboBox
          Left = 423
          Top = 108
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 6
          Text = 'ComboBox3'
        end
        object ComboBox4: TComboBox
          Left = 423
          Top = 148
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 7
          Text = 'ComboBox4'
        end
        object ComboBox5: TComboBox
          Left = 423
          Top = 187
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 8
          Text = 'ComboBox5'
        end
        object ComboBox6: TComboBox
          Left = 423
          Top = 226
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 9
          Text = 'ComboBox6'
        end
        object ComboBox7: TComboBox
          Left = 423
          Top = 266
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 10
          Text = 'ComboBox7'
        end
        object Btn_vender_reload: TBitBtn
          Left = 20
          Top = 266
          Width = 90
          Height = 31
          Caption = '&Reload'
          ModalResult = 6
          TabOrder = 11
          OnClick = Btn_vender_reloadClick
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
    object ts_debug: TTabSheet
      Caption = 'Debug'
      ImageIndex = 1
      object GroupBox14: TGroupBox
        Left = 10
        Top = 10
        Width = 828
        Height = 454
        Caption = 'Debug Mode'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label12: TLabel
          Left = 20
          Top = 111
          Width = 48
          Height = 16
          Caption = 'Label12'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label8: TLabel
          Left = 20
          Top = 160
          Width = 41
          Height = 16
          Caption = 'Label8'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label9: TLabel
          Left = 20
          Top = 209
          Width = 41
          Height = 16
          Caption = 'Label9'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 20
          Top = 308
          Width = 48
          Height = 16
          Caption = 'Label10'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label11: TLabel
          Left = 20
          Top = 357
          Width = 48
          Height = 16
          Caption = 'Label11'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label18: TLabel
          Left = 20
          Top = 406
          Width = 48
          Height = 16
          Caption = 'Label18'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label19: TLabel
          Left = 20
          Top = 258
          Width = 48
          Height = 16
          Caption = 'Label19'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object GroupBox15: TGroupBox
          Left = 443
          Top = 236
          Width = 366
          Height = 198
          Caption = 'Test Mode'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clTeal
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          object CheckBox8: TCheckBox
            Left = 20
            Top = 39
            Width = 158
            Height = 21
            Caption = 'CheckBox8'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object LabeledEdit3: TLabeledEdit
            Left = 207
            Top = 39
            Width = 90
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit3'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 1
          end
          object LabeledEdit4: TLabeledEdit
            Left = 207
            Top = 98
            Width = 90
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit4'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 2
          end
          object LabeledEdit5: TLabeledEdit
            Left = 207
            Top = 158
            Width = 90
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit5'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 3
          end
          object CheckBox7: TCheckBox
            Left = 20
            Top = 89
            Width = 158
            Height = 21
            Caption = 'CheckBox7'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
          end
          object CheckBox9: TCheckBox
            Left = 20
            Top = 138
            Width = 178
            Height = 21
            Caption = 'CheckBox9'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
          end
        end
        object DCR: TGroupBox
          Left = 443
          Top = 20
          Width = 366
          Height = 208
          Caption = 'DCR'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clTeal
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          object CheckBox6: TCheckBox
            Left = 20
            Top = 89
            Width = 168
            Height = 21
            Caption = 'CheckBox6'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object CheckBox5: TCheckBox
            Left = 20
            Top = 39
            Width = 158
            Height = 21
            Caption = 'CheckBox5'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
          object LabeledEdit11: TLabeledEdit
            Left = 177
            Top = 162
            Width = 90
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit11'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 2
          end
          object LabeledEdit1: TLabeledEdit
            Left = 177
            Top = 34
            Width = 90
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit1'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 3
          end
          object LabeledEdit2: TLabeledEdit
            Left = 177
            Top = 94
            Width = 90
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit2'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 4
          end
        end
        object ComboBox8: TComboBox
          Left = 187
          Top = 108
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 2
          Text = 'ComboBox8'
        end
        object CheckBox10: TCheckBox
          Left = 20
          Top = 30
          Width = 208
          Height = 20
          Caption = 'CheckBox10'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox11: TCheckBox
          Left = 20
          Top = 69
          Width = 208
          Height = 21
          Caption = 'CheckBox11'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object ComboBox14: TComboBox
          Left = 187
          Top = 158
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 5
          Text = 'ComboBox14'
        end
        object ComboBox15: TComboBox
          Left = 187
          Top = 207
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 6
          Text = 'ComboBox15'
        end
        object ComboBox16: TComboBox
          Left = 187
          Top = 305
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 7
          Text = 'ComboBox16'
        end
        object ComboBox17: TComboBox
          Left = 187
          Top = 354
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 8
          Text = 'ComboBox17'
        end
        object ComboBox18: TComboBox
          Left = 187
          Top = 404
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 9
          Text = 'ComboBox18'
        end
        object LabeledEdit10: TLabeledEdit
          Left = 305
          Top = 59
          Width = 90
          Height = 21
          EditLabel.Width = 87
          EditLabel.Height = 16
          EditLabel.Caption = 'LabeledEdit10'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clBlack
          EditLabel.Font.Height = -15
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 10
        end
        object ComboBox19: TComboBox
          Left = 187
          Top = 256
          Width = 228
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 0
          ParentFont = False
          TabOrder = 11
          Text = 'ComboBox19'
        end
      end
      object btn_debug_reload: TBitBtn
        Left = 10
        Top = 473
        Width = 90
        Height = 30
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 1
        OnClick = btn_debug_reloadClick
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
    object TabSheet1: TTabSheet
      Caption = 'Status'
      ImageIndex = 2
      object GroupBox16: TGroupBox
        Left = 20
        Top = 10
        Width = 710
        Height = 513
        Caption = 'Status'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object btn_status_refresh: TBitBtn
          Left = 30
          Top = 39
          Width = 80
          Height = 31
          Caption = 'Re&fresh'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btn_status_refreshClick
        end
        object GroupBox17: TGroupBox
          Left = 335
          Top = 20
          Width = 336
          Height = 444
          Caption = 'DCR'
          TabOrder = 1
          object LabeledEdit6: TLabeledEdit
            Left = 226
            Top = 34
            Width = 71
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit6'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 0
          end
          object LabeledEdit7: TLabeledEdit
            Left = 226
            Top = 74
            Width = 71
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit7'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 1
          end
          object LabeledEdit8: TLabeledEdit
            Left = 226
            Top = 118
            Width = 71
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit8'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 2
          end
          object LabeledEdit9: TLabeledEdit
            Left = 226
            Top = 158
            Width = 71
            Height = 21
            EditLabel.Width = 80
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit9'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
          end
          object LabeledEdit12: TLabeledEdit
            Left = 226
            Top = 197
            Width = 71
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit12'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 4
          end
          object LabeledEdit13: TLabeledEdit
            Left = 226
            Top = 236
            Width = 71
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit13'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 5
          end
          object LabeledEdit14: TLabeledEdit
            Left = 226
            Top = 276
            Width = 71
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit14'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 6
          end
          object LabeledEdit15: TLabeledEdit
            Left = 226
            Top = 315
            Width = 71
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit15'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 7
          end
          object LabeledEdit16: TLabeledEdit
            Left = 226
            Top = 354
            Width = 71
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit16'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 8
          end
          object LabeledEdit17: TLabeledEdit
            Left = 226
            Top = 394
            Width = 71
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit17'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 9
          end
        end
        object GroupBox18: TGroupBox
          Left = 30
          Top = 94
          Width = 296
          Height = 370
          Caption = 'State Check'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clTeal
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          object Label13: TLabel
            Left = 10
            Top = 34
            Width = 48
            Height = 16
            Caption = 'Label13'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label14: TLabel
            Left = 10
            Top = 84
            Width = 48
            Height = 16
            Caption = 'Label14'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label15: TLabel
            Left = 10
            Top = 134
            Width = 48
            Height = 16
            Caption = 'Label15'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label16: TLabel
            Left = 10
            Top = 182
            Width = 48
            Height = 16
            Caption = 'Label16'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label17: TLabel
            Left = 10
            Top = 226
            Width = 48
            Height = 16
            Caption = 'Label17'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object ComboBox9: TComboBox
            Left = 167
            Top = 30
            Width = 110
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 0
            ParentFont = False
            TabOrder = 0
            Text = 'ComboBox9'
          end
          object ComboBox10: TComboBox
            Left = 167
            Top = 79
            Width = 110
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 0
            ParentFont = False
            TabOrder = 1
            Text = 'ComboBox10'
          end
          object ComboBox11: TComboBox
            Left = 167
            Top = 128
            Width = 110
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 0
            ParentFont = False
            TabOrder = 2
            Text = 'ComboBox11'
          end
          object ComboBox12: TComboBox
            Left = 167
            Top = 177
            Width = 110
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 0
            ParentFont = False
            TabOrder = 3
            Text = 'ComboBox12'
          end
          object ComboBox13: TComboBox
            Left = 167
            Top = 226
            Width = 110
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 0
            ParentFont = False
            TabOrder = 4
            Text = 'ComboBox13'
          end
          object LabeledEdit20: TLabeledEdit
            Left = 197
            Top = 276
            Width = 70
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit20'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 5
          end
          object LabeledEdit21: TLabeledEdit
            Left = 197
            Top = 325
            Width = 70
            Height = 21
            EditLabel.Width = 87
            EditLabel.Height = 16
            EditLabel.Caption = 'LabeledEdit21'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -15
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ParentFont = False
            ReadOnly = True
            TabOrder = 6
          end
        end
      end
    end
  end
end
