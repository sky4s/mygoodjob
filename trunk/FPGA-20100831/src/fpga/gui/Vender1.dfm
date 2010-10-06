object VenderForm1: TVenderForm1
  Left = 263
  Top = 175
  Width = 717
  Height = 497
  Caption = 'Vender'
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
  WindowState = wsMaximized
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 705
    Height = 457
    ActivePage = ts_vender
    TabIndex = 0
    TabOrder = 0
    object ts_vender: TTabSheet
      Caption = 'Vender'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 4
        Width = 705
        Height = 429
        TabOrder = 0
        object Label1: TLabel
          Left = 208
          Top = 24
          Width = 32
          Height = 13
          Caption = 'Label1'
        end
        object Label2: TLabel
          Left = 208
          Top = 56
          Width = 32
          Height = 13
          Caption = 'Label2'
        end
        object Label3: TLabel
          Left = 208
          Top = 88
          Width = 32
          Height = 13
          Caption = 'Label3'
        end
        object Label4: TLabel
          Left = 208
          Top = 120
          Width = 32
          Height = 13
          Caption = 'Label4'
        end
        object Label5: TLabel
          Left = 208
          Top = 152
          Width = 32
          Height = 13
          Caption = 'Label5'
        end
        object Label6: TLabel
          Left = 208
          Top = 184
          Width = 32
          Height = 13
          Caption = 'Label6'
        end
        object Label7: TLabel
          Left = 208
          Top = 216
          Width = 32
          Height = 13
          Caption = 'Label7'
        end
        object CheckBox1: TCheckBox
          Left = 16
          Top = 24
          Width = 145
          Height = 17
          Caption = 'CheckBox1'
          TabOrder = 0
        end
        object CheckBox2: TCheckBox
          Left = 16
          Top = 56
          Width = 169
          Height = 17
          Caption = 'CheckBox2'
          TabOrder = 1
        end
        object CheckBox3: TCheckBox
          Left = 16
          Top = 88
          Width = 169
          Height = 17
          Caption = 'CheckBox3'
          TabOrder = 2
        end
        object CheckBox4: TCheckBox
          Left = 16
          Top = 120
          Width = 177
          Height = 17
          Caption = 'CheckBox4'
          TabOrder = 3
        end
        object ComboBox1: TComboBox
          Left = 344
          Top = 24
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 4
          Text = 'ComboBox1'
        end
        object ComboBox2: TComboBox
          Left = 344
          Top = 56
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 5
          Text = 'ComboBox2'
        end
        object ComboBox3: TComboBox
          Left = 344
          Top = 88
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 6
          Text = 'ComboBox3'
        end
        object ComboBox4: TComboBox
          Left = 344
          Top = 120
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 7
          Text = 'ComboBox4'
        end
        object ComboBox5: TComboBox
          Left = 344
          Top = 152
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 8
          Text = 'ComboBox5'
        end
        object ComboBox6: TComboBox
          Left = 344
          Top = 184
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 9
          Text = 'ComboBox6'
        end
        object ComboBox7: TComboBox
          Left = 344
          Top = 216
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 10
          Text = 'ComboBox7'
        end
        object Btn_vender_reload: TBitBtn
          Left = 16
          Top = 216
          Width = 73
          Height = 25
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
        Left = 8
        Top = 8
        Width = 673
        Height = 369
        Caption = 'Debug Mode'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label12: TLabel
          Left = 16
          Top = 90
          Width = 38
          Height = 13
          Caption = 'Label12'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label8: TLabel
          Left = 16
          Top = 130
          Width = 32
          Height = 13
          Caption = 'Label8'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label9: TLabel
          Left = 16
          Top = 170
          Width = 32
          Height = 13
          Caption = 'Label9'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label10: TLabel
          Left = 16
          Top = 250
          Width = 38
          Height = 13
          Caption = 'Label10'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label11: TLabel
          Left = 16
          Top = 290
          Width = 38
          Height = 13
          Caption = 'Label11'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label18: TLabel
          Left = 16
          Top = 330
          Width = 38
          Height = 13
          Caption = 'Label18'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object Label19: TLabel
          Left = 16
          Top = 210
          Width = 38
          Height = 13
          Caption = 'Label19'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object GroupBox15: TGroupBox
          Left = 360
          Top = 192
          Width = 297
          Height = 161
          Caption = 'Test Mode'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clTeal
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          object CheckBox8: TCheckBox
            Left = 16
            Top = 32
            Width = 129
            Height = 17
            Caption = 'CheckBox8'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object LabeledEdit3: TLabeledEdit
            Left = 168
            Top = 32
            Width = 73
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit3'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 1
          end
          object LabeledEdit4: TLabeledEdit
            Left = 168
            Top = 80
            Width = 73
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit4'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 2
          end
          object LabeledEdit5: TLabeledEdit
            Left = 168
            Top = 128
            Width = 73
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit5'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 3
          end
          object CheckBox7: TCheckBox
            Left = 16
            Top = 72
            Width = 129
            Height = 17
            Caption = 'CheckBox7'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 4
          end
          object CheckBox9: TCheckBox
            Left = 16
            Top = 112
            Width = 145
            Height = 17
            Caption = 'CheckBox9'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 5
          end
        end
        object DCR: TGroupBox
          Left = 360
          Top = 16
          Width = 297
          Height = 169
          Caption = 'DCR'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clTeal
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          object CheckBox6: TCheckBox
            Left = 16
            Top = 72
            Width = 137
            Height = 17
            Caption = 'CheckBox6'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
          object CheckBox5: TCheckBox
            Left = 16
            Top = 32
            Width = 129
            Height = 17
            Caption = 'CheckBox5'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
          object LabeledEdit11: TLabeledEdit
            Left = 144
            Top = 132
            Width = 73
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit11'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 2
          end
          object LabeledEdit1: TLabeledEdit
            Left = 144
            Top = 28
            Width = 73
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit1'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 3
          end
          object LabeledEdit2: TLabeledEdit
            Left = 144
            Top = 76
            Width = 73
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit2'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            LabelPosition = lpAbove
            LabelSpacing = 3
            ParentFont = False
            TabOrder = 4
          end
        end
        object ComboBox8: TComboBox
          Left = 152
          Top = 88
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 2
          Text = 'ComboBox8'
        end
        object CheckBox10: TCheckBox
          Left = 16
          Top = 24
          Width = 169
          Height = 17
          Caption = 'CheckBox10'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox11: TCheckBox
          Left = 16
          Top = 56
          Width = 169
          Height = 17
          Caption = 'CheckBox11'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object ComboBox14: TComboBox
          Left = 152
          Top = 128
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 5
          Text = 'ComboBox14'
        end
        object ComboBox15: TComboBox
          Left = 152
          Top = 168
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 6
          Text = 'ComboBox15'
        end
        object ComboBox16: TComboBox
          Left = 152
          Top = 248
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 7
          Text = 'ComboBox16'
        end
        object ComboBox17: TComboBox
          Left = 152
          Top = 288
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 8
          Text = 'ComboBox17'
        end
        object ComboBox18: TComboBox
          Left = 152
          Top = 328
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 9
          Text = 'ComboBox18'
        end
        object LabeledEdit10: TLabeledEdit
          Left = 248
          Top = 48
          Width = 73
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit10'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clBlack
          EditLabel.Font.Height = -11
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 10
        end
        object ComboBox19: TComboBox
          Left = 152
          Top = 208
          Width = 185
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 11
          Text = 'ComboBox19'
        end
      end
      object btn_debug_reload: TBitBtn
        Left = 8
        Top = 384
        Width = 73
        Height = 25
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
        Left = 16
        Top = 8
        Width = 577
        Height = 417
        Caption = 'Status'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object btn_status_refresh: TBitBtn
          Left = 24
          Top = 32
          Width = 65
          Height = 25
          Caption = 'Re&fresh'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btn_status_refreshClick
        end
        object GroupBox17: TGroupBox
          Left = 272
          Top = 16
          Width = 273
          Height = 361
          Caption = 'DCR'
          TabOrder = 1
          object LabeledEdit6: TLabeledEdit
            Left = 184
            Top = 28
            Width = 57
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit6'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 60
            Width = 57
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit7'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 96
            Width = 57
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit8'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 128
            Width = 57
            Height = 21
            EditLabel.Width = 62
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit9'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 160
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit12'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 192
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit13'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 224
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit14'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 256
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit15'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 288
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit16'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 184
            Top = 320
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit17'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
          Left = 24
          Top = 76
          Width = 241
          Height = 301
          Caption = 'State Check'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clTeal
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          object Label13: TLabel
            Left = 8
            Top = 28
            Width = 38
            Height = 13
            Caption = 'Label13'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label14: TLabel
            Left = 8
            Top = 68
            Width = 38
            Height = 13
            Caption = 'Label14'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label15: TLabel
            Left = 8
            Top = 109
            Width = 38
            Height = 13
            Caption = 'Label15'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label16: TLabel
            Left = 8
            Top = 148
            Width = 38
            Height = 13
            Caption = 'Label16'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object Label17: TLabel
            Left = 8
            Top = 184
            Width = 38
            Height = 13
            Caption = 'Label17'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
          end
          object ComboBox9: TComboBox
            Left = 136
            Top = 24
            Width = 89
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 0
            Text = 'ComboBox9'
          end
          object ComboBox10: TComboBox
            Left = 136
            Top = 64
            Width = 89
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 1
            Text = 'ComboBox10'
          end
          object ComboBox11: TComboBox
            Left = 136
            Top = 104
            Width = 89
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 2
            Text = 'ComboBox11'
          end
          object ComboBox12: TComboBox
            Left = 136
            Top = 144
            Width = 89
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 3
            Text = 'ComboBox12'
          end
          object ComboBox13: TComboBox
            Left = 136
            Top = 184
            Width = 89
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ItemHeight = 13
            ParentFont = False
            TabOrder = 4
            Text = 'ComboBox13'
          end
          object LabeledEdit20: TLabeledEdit
            Left = 160
            Top = 224
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit20'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
            Left = 160
            Top = 264
            Width = 57
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit21'
            EditLabel.Font.Charset = DEFAULT_CHARSET
            EditLabel.Font.Color = clBlack
            EditLabel.Font.Height = -11
            EditLabel.Font.Name = 'MS Sans Serif'
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clBlack
            Font.Height = -11
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
