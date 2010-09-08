object TCONForm1: TTCONForm1
  Left = 165
  Top = 142
  Width = 746
  Height = 493
  Align = alCustom
  Caption = 'TCON'
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
  object pc_tcon: TPageControl
    Left = 0
    Top = 0
    Width = 737
    Height = 457
    ActivePage = ts_tcon_dev
    TabIndex = 0
    TabOrder = 0
    object ts_tcon_dev: TTabSheet
      Caption = '&Device'
      object Label1: TLabel
        Left = 152
        Top = 160
        Width = 32
        Height = 13
        Caption = 'Label1'
      end
      object Label3: TLabel
        Left = 152
        Top = 208
        Width = 32
        Height = 13
        Caption = 'Label3'
      end
      object CheckBox1: TCheckBox
        Left = 32
        Top = 192
        Width = 97
        Height = 17
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object ComboBox1: TComboBox
        Left = 152
        Top = 176
        Width = 81
        Height = 21
        ItemHeight = 13
        TabOrder = 1
        Text = 'ComboBox1'
      end
      object ComboBox2: TComboBox
        Left = 152
        Top = 224
        Width = 81
        Height = 21
        ItemHeight = 13
        TabOrder = 2
        Text = 'ComboBox2'
      end
      object Btn_TCON_dev_reload: TBitBtn
        Left = 24
        Top = 272
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 3
        OnClick = Btn_TCON_dev_reloadClick
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
      object GroupBox10: TGroupBox
        Left = 16
        Top = 16
        Width = 265
        Height = 129
        Caption = 'Hardware Pin Setting'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        object CheckBox5: TCheckBox
          Left = 16
          Top = 72
          Width = 113
          Height = 17
          Caption = 'CheckBox5'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object CheckBox8: TCheckBox
          Left = 16
          Top = 96
          Width = 113
          Height = 17
          Caption = 'CheckBox8'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object CheckBox7: TCheckBox
          Left = 16
          Top = 48
          Width = 113
          Height = 17
          Caption = 'CheckBox4'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object CheckBox6: TCheckBox
          Left = 144
          Top = 48
          Width = 113
          Height = 17
          Caption = 'CheckBox6'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox4: TCheckBox
          Left = 144
          Top = 72
          Width = 113
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
        object CheckBox3: TCheckBox
          Left = 16
          Top = 24
          Width = 113
          Height = 17
          Caption = 'CheckBox3'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object CheckBox9: TCheckBox
          Left = 144
          Top = 24
          Width = 113
          Height = 17
          Caption = 'CheckBox9'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
        end
      end
      object CheckBox2: TCheckBox
        Left = 32
        Top = 160
        Width = 97
        Height = 17
        Caption = 'CheckBox2'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
      end
      object GroupBox14: TGroupBox
        Left = 296
        Top = 16
        Width = 321
        Height = 305
        Caption = 'Clock Detect'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        object LabeledEdit45: TLabeledEdit
          Left = 16
          Top = 212
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit45'
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
          TabOrder = 0
        end
        object LabeledEdit50: TLabeledEdit
          Left = 176
          Top = 260
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit50'
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
        object LabeledEdit49: TLabeledEdit
          Left = 176
          Top = 212
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit49'
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
        object LabeledEdit48: TLabeledEdit
          Left = 176
          Top = 168
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit48'
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
        object LabeledEdit47: TLabeledEdit
          Left = 176
          Top = 120
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit47'
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
        object LabeledEdit46: TLabeledEdit
          Left = 16
          Top = 260
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit46'
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
          TabOrder = 5
        end
        object LabeledEdit44: TLabeledEdit
          Left = 16
          Top = 168
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit44'
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
          TabOrder = 6
        end
        object LabeledEdit43: TLabeledEdit
          Left = 16
          Top = 120
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit43'
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
          TabOrder = 7
        end
        object CheckBox10: TCheckBox
          Left = 16
          Top = 24
          Width = 137
          Height = 17
          Caption = 'CheckBox10'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
        end
        object CheckBox29: TCheckBox
          Left = 16
          Top = 72
          Width = 137
          Height = 17
          Caption = 'CheckBox29'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 9
        end
        object CheckBox28: TCheckBox
          Left = 16
          Top = 48
          Width = 137
          Height = 17
          Caption = 'CheckBox28'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 10
        end
      end
    end
    object ts_tcon_drive: TTabSheet
      Caption = 'Dri&ving'
      ImageIndex = 2
      object GroupBox3: TGroupBox
        Left = 8
        Top = 16
        Width = 393
        Height = 353
        Caption = 'Driving Type'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label8: TLabel
          Left = 272
          Top = 16
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
        object Label14: TLabel
          Left = 272
          Top = 112
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
        object Label13: TLabel
          Left = 272
          Top = 64
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
        object Label15: TLabel
          Left = 272
          Top = 160
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
        object CheckBox32: TCheckBox
          Left = 16
          Top = 96
          Width = 105
          Height = 17
          Caption = 'CheckBox32'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object CheckBox33: TCheckBox
          Left = 16
          Top = 128
          Width = 105
          Height = 17
          Caption = 'CheckBox33'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object CheckBox34: TCheckBox
          Left = 16
          Top = 160
          Width = 105
          Height = 17
          Caption = 'CheckBox34'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object CheckBox35: TCheckBox
          Left = 16
          Top = 195
          Width = 105
          Height = 22
          Caption = 'CheckBox35'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox36: TCheckBox
          Left = 16
          Top = 231
          Width = 105
          Height = 18
          Caption = 'CheckBox36'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object CheckBox37: TCheckBox
          Left = 136
          Top = 27
          Width = 129
          Height = 25
          Caption = 'CheckBox37'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object ComboBox7: TComboBox
          Left = 272
          Top = 32
          Width = 105
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 6
          Text = 'ComboBox7'
        end
        object LabeledEdit1: TLabeledEdit
          Left = 16
          Top = 280
          Width = 89
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
          TabOrder = 7
        end
        object LabeledEdit2: TLabeledEdit
          Left = 16
          Top = 320
          Width = 89
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
          TabOrder = 8
        end
        object ComboBox5: TComboBox
          Left = 272
          Top = 128
          Width = 113
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 9
          Text = 'ComboBox5'
        end
        object CheckBox31: TCheckBox
          Left = 16
          Top = 64
          Width = 121
          Height = 17
          Caption = 'CheckBox31'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 10
        end
        object CheckBox39: TCheckBox
          Left = 136
          Top = 67
          Width = 113
          Height = 17
          Caption = 'CheckBox39'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 11
        end
        object CheckBox40: TCheckBox
          Left = 136
          Top = 99
          Width = 113
          Height = 17
          Caption = 'CheckBox40'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 12
        end
        object CheckBox30: TCheckBox
          Left = 16
          Top = 32
          Width = 105
          Height = 17
          Caption = 'CheckBox30'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 13
        end
        object CheckBox45: TCheckBox
          Left = 136
          Top = 131
          Width = 113
          Height = 17
          Caption = 'CheckBox45'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 14
        end
        object CheckBox46: TCheckBox
          Left = 136
          Top = 163
          Width = 113
          Height = 17
          Caption = 'CheckBox46'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 15
        end
        object CheckBox47: TCheckBox
          Left = 136
          Top = 198
          Width = 113
          Height = 17
          Caption = 'CheckBox47'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 16
        end
        object ComboBox12: TComboBox
          Left = 272
          Top = 80
          Width = 105
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 17
          Text = 'ComboBox12'
        end
        object ComboBox6: TComboBox
          Left = 272
          Top = 176
          Width = 105
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 18
          Text = 'ComboBox6'
        end
        object LabeledEdit5: TLabeledEdit
          Left = 128
          Top = 280
          Width = 89
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
          TabOrder = 19
        end
        object LabeledEdit54: TLabeledEdit
          Left = 128
          Top = 320
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit54'
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
          TabOrder = 20
        end
        object LabeledEdit55: TLabeledEdit
          Left = 240
          Top = 280
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit55'
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
          TabOrder = 21
        end
      end
      object GroupBox6: TGroupBox
        Left = 408
        Top = 304
        Width = 313
        Height = 105
        Caption = 'Blanking Gray Insertion'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label9: TLabel
          Left = 16
          Top = 56
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
        object ComboBox8: TComboBox
          Left = 16
          Top = 72
          Width = 129
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 0
          Text = 'ComboBox8'
        end
        object LabeledEdit4: TLabeledEdit
          Left = 168
          Top = 72
          Width = 89
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
          TabOrder = 1
        end
        object CheckBox38: TCheckBox
          Left = 16
          Top = 24
          Width = 105
          Height = 17
          Caption = 'CheckBox38'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
      end
      object GroupBox7: TGroupBox
        Left = 408
        Top = 16
        Width = 313
        Height = 281
        Caption = 'Inversion Select'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        object Label10: TLabel
          Left = 16
          Top = 16
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
          Top = 64
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
        object Label12: TLabel
          Left = 168
          Top = 16
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
        object Label4: TLabel
          Left = 168
          Top = 64
          Width = 32
          Height = 13
          Caption = 'Label4'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object ComboBox9: TComboBox
          Left = 16
          Top = 32
          Width = 129
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
          Left = 16
          Top = 80
          Width = 129
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
        object CheckBox41: TCheckBox
          Left = 16
          Top = 115
          Width = 129
          Height = 17
          Caption = 'CheckBox41'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object CheckBox42: TCheckBox
          Left = 16
          Top = 147
          Width = 129
          Height = 17
          Caption = 'CheckBox42'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox43: TCheckBox
          Left = 16
          Top = 179
          Width = 129
          Height = 17
          Caption = 'CheckBox43'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object CheckBox44: TCheckBox
          Left = 16
          Top = 211
          Width = 129
          Height = 17
          Caption = 'CheckBox44'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object ComboBox11: TComboBox
          Left = 168
          Top = 32
          Width = 113
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 6
          Text = 'ComboBox11'
        end
        object ComboBox3: TComboBox
          Left = 168
          Top = 80
          Width = 113
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 7
          Text = 'ComboBox3'
        end
        object LabeledEdit51: TLabeledEdit
          Left = 168
          Top = 124
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit51'
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
          TabOrder = 8
        end
        object LabeledEdit52: TLabeledEdit
          Left = 168
          Top = 164
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit52'
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
          TabOrder = 9
        end
        object LabeledEdit53: TLabeledEdit
          Left = 168
          Top = 204
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit53'
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
        object LabeledEdit56: TLabeledEdit
          Left = 168
          Top = 244
          Width = 89
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit56'
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
          TabOrder = 11
        end
      end
      object Btn_TCON_drv_reload: TBitBtn
        Left = 16
        Top = 384
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 3
        OnClick = Btn_TCON_drv_reloadClick
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
    object ts_tcon_inoutp: TTabSheet
      Caption = '&Input/Output'
      object GroupBox1: TGroupBox
        Left = 16
        Top = 24
        Width = 161
        Height = 305
        Caption = 'Input'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label2: TLabel
          Left = 16
          Top = 32
          Width = 32
          Height = 13
          Caption = 'Label2'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object CheckBox11: TCheckBox
          Left = 16
          Top = 80
          Width = 137
          Height = 25
          Caption = 'CheckBox11'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object CheckBox12: TCheckBox
          Left = 16
          Top = 104
          Width = 137
          Height = 25
          Caption = 'CheckBox12'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object ComboBox4: TComboBox
          Left = 16
          Top = 48
          Width = 97
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ItemHeight = 13
          ParentFont = False
          TabOrder = 2
          Text = 'ComboBox4'
        end
      end
      object GroupBox2: TGroupBox
        Left = 184
        Top = 24
        Width = 377
        Height = 305
        Caption = 'Output'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label5: TLabel
          Left = 16
          Top = 72
          Width = 100
          Height = 16
          Caption = 'Change Function'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object CheckBox14: TCheckBox
          Left = 16
          Top = 140
          Width = 81
          Height = 17
          Caption = 'CheckBox14'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
        end
        object CheckBox15: TCheckBox
          Left = 16
          Top = 172
          Width = 89
          Height = 17
          Caption = 'CheckBox15'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
        end
        object CheckBox16: TCheckBox
          Left = 16
          Top = 200
          Width = 89
          Height = 25
          Caption = 'CheckBox16'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
        end
        object CheckBox17: TCheckBox
          Left = 16
          Top = 233
          Width = 89
          Height = 25
          Caption = 'CheckBox17'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 3
        end
        object CheckBox18: TCheckBox
          Left = 120
          Top = 24
          Width = 89
          Height = 25
          Caption = 'CheckBox18'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 4
        end
        object CheckBox19: TCheckBox
          Left = 16
          Top = 24
          Width = 89
          Height = 25
          Caption = 'CheckBox19'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 5
        end
        object CheckBox20: TCheckBox
          Left = 216
          Top = 24
          Width = 89
          Height = 25
          Caption = 'CheckBox20'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 6
        end
        object CheckBox21: TCheckBox
          Left = 16
          Top = 264
          Width = 81
          Height = 25
          Caption = 'CheckBox21'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 7
        end
        object CheckBox22: TCheckBox
          Left = 136
          Top = 104
          Width = 81
          Height = 25
          Caption = 'CheckBox22'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 8
        end
        object CheckBox23: TCheckBox
          Left = 136
          Top = 136
          Width = 89
          Height = 25
          Caption = 'CheckBox23'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 9
        end
        object CheckBox13: TCheckBox
          Left = 16
          Top = 104
          Width = 89
          Height = 25
          Caption = 'CheckBox13'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 10
        end
      end
      object Btn_TCON_io_reload: TBitBtn
        Left = 16
        Top = 352
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 2
        OnClick = Btn_TCON_io_reloadClick
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
      Caption = 'Timing'
      ImageIndex = 3
      object Btn_TCON_Tim_reload: TBitBtn
        Left = 8
        Top = 400
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 0
        OnClick = Btn_TCON_Tim_reloadClick
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
      object GroupBox13: TGroupBox
        Left = 0
        Top = 0
        Width = 601
        Height = 65
        Caption = 'Source'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clTeal
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object LabeledEdit6: TLabeledEdit
          Left = 184
          Top = 32
          Width = 49
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
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 0
        end
        object LabeledEdit3: TLabeledEdit
          Left = 8
          Top = 32
          Width = 49
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
        object LabeledEdit7: TLabeledEdit
          Left = 360
          Top = 32
          Width = 49
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
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 2
        end
        object LabeledEdit8: TLabeledEdit
          Left = 448
          Top = 32
          Width = 49
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
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 3
        end
        object LabeledEdit57: TLabeledEdit
          Left = 96
          Top = 32
          Width = 49
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit57'
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
        object LabeledEdit58: TLabeledEdit
          Left = 272
          Top = 32
          Width = 49
          Height = 21
          EditLabel.Width = 68
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit58'
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
          TabOrder = 5
        end
      end
      object PageControl2: TPageControl
        Left = 0
        Top = 72
        Width = 729
        Height = 313
        ActivePage = TabSheet4
        TabIndex = 0
        TabOrder = 2
        object TabSheet4: TTabSheet
          Caption = 'Normal Gate On'
          object GroupBox4: TGroupBox
            Left = 0
            Top = -4
            Width = 697
            Height = 289
            TabOrder = 0
            object PageControl1: TPageControl
              Left = 16
              Top = 88
              Width = 649
              Height = 185
              ActivePage = TabSheet2
              TabIndex = 0
              TabOrder = 0
              object TabSheet2: TTabSheet
                Caption = 'Frame 60 (Area1)'
                object GroupBox8: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 633
                  Height = 149
                  TabOrder = 0
                  object LabeledEdit13: TLabeledEdit
                    Left = 16
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit13'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit14: TLabeledEdit
                    Left = 316
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit14'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit15: TLabeledEdit
                    Left = 16
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit15'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit16: TLabeledEdit
                    Left = 316
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit16'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit59: TLabeledEdit
                    Left = 166
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit59'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit60: TLabeledEdit
                    Left = 467
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit60'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit61: TLabeledEdit
                    Left = 166
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit61'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit62: TLabeledEdit
                    Left = 467
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit62'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet3: TTabSheet
                Caption = 'Frame 40 (Area1)'
                ImageIndex = 1
                object GroupBox9: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 633
                  Height = 149
                  TabOrder = 0
                  object LabeledEdit21: TLabeledEdit
                    Left = 16
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit21'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit22: TLabeledEdit
                    Left = 316
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit22'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit23: TLabeledEdit
                    Left = 16
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit23'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit24: TLabeledEdit
                    Left = 316
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit24'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit67: TLabeledEdit
                    Left = 166
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit67'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit68: TLabeledEdit
                    Left = 467
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit68'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit69: TLabeledEdit
                    Left = 166
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit69'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit70: TLabeledEdit
                    Left = 467
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit70'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet8: TTabSheet
                Caption = 'Frame 60 (Area2)'
                ImageIndex = 2
                object GroupBox5: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 633
                  Height = 149
                  TabOrder = 0
                  object LabeledEdit63: TLabeledEdit
                    Left = 16
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit63'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit64: TLabeledEdit
                    Left = 316
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit64'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit65: TLabeledEdit
                    Left = 16
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit65'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit66: TLabeledEdit
                    Left = 316
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit66'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit71: TLabeledEdit
                    Left = 166
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit71'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit72: TLabeledEdit
                    Left = 475
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit72'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit73: TLabeledEdit
                    Left = 166
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit73'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit74: TLabeledEdit
                    Left = 475
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit74'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet9: TTabSheet
                Caption = 'Frame 40 (Area2)'
                ImageIndex = 3
                object GroupBox15: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 633
                  Height = 149
                  TabOrder = 0
                  object LabeledEdit75: TLabeledEdit
                    Left = 16
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit75'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit76: TLabeledEdit
                    Left = 316
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit76'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit77: TLabeledEdit
                    Left = 16
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit77'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit78: TLabeledEdit
                    Left = 324
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit78'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit79: TLabeledEdit
                    Left = 166
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit79'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit80: TLabeledEdit
                    Left = 475
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit80'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit81: TLabeledEdit
                    Left = 166
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit81'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit82: TLabeledEdit
                    Left = 475
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit82'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet10: TTabSheet
                Caption = 'Frame 60 (Area3)'
                ImageIndex = 4
                object GroupBox16: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 633
                  Height = 149
                  TabOrder = 0
                  object LabeledEdit83: TLabeledEdit
                    Left = 16
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit83'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit84: TLabeledEdit
                    Left = 316
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit84'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit85: TLabeledEdit
                    Left = 16
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit85'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit86: TLabeledEdit
                    Left = 316
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit86'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit87: TLabeledEdit
                    Left = 166
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit87'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit88: TLabeledEdit
                    Left = 475
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit88'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit89: TLabeledEdit
                    Left = 166
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit89'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit90: TLabeledEdit
                    Left = 475
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit90'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet11: TTabSheet
                Caption = 'Frame 40 (Area3)'
                ImageIndex = 5
                object GroupBox17: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 633
                  Height = 149
                  TabOrder = 0
                  object LabeledEdit91: TLabeledEdit
                    Left = 16
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit91'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit92: TLabeledEdit
                    Left = 316
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit92'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit93: TLabeledEdit
                    Left = 16
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit93'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit94: TLabeledEdit
                    Left = 316
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit94'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit95: TLabeledEdit
                    Left = 166
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit95'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit96: TLabeledEdit
                    Left = 475
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit96'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit97: TLabeledEdit
                    Left = 166
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit97'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit98: TLabeledEdit
                    Left = 475
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit98'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
            end
            object LabeledEdit9: TLabeledEdit
              Left = 40
              Top = 48
              Width = 49
              Height = 21
              EditLabel.Width = 62
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit9'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit10: TLabeledEdit
              Left = 160
              Top = 48
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit10'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
            end
            object LabeledEdit11: TLabeledEdit
              Left = 280
              Top = 48
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit11'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
            end
            object LabeledEdit12: TLabeledEdit
              Left = 400
              Top = 48
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit12'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
          end
        end
        object TabSheet6: TTabSheet
          Caption = 'Fix Gate On'
          ImageIndex = 2
          object GroupBox11: TGroupBox
            Left = 0
            Top = -4
            Width = 721
            Height = 285
            TabOrder = 0
            object PageControl3: TPageControl
              Left = 16
              Top = 24
              Width = 673
              Height = 241
              ActivePage = TabSheet7
              TabIndex = 0
              TabOrder = 0
              object TabSheet7: TTabSheet
                Caption = 'Frame 60 (Area1)'
                object GroupBox18: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 561
                  Height = 213
                  TabOrder = 0
                  object LabeledEdit99: TLabeledEdit
                    Left = 270
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit99'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit100: TLabeledEdit
                    Left = 270
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit100'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit101: TLabeledEdit
                    Left = 270
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit101'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit102: TLabeledEdit
                    Left = 270
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit102'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit17: TLabeledEdit
                    Left = 24
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit17'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit20: TLabeledEdit
                    Left = 24
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit20'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit19: TLabeledEdit
                    Left = 24
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit19'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit18: TLabeledEdit
                    Left = 24
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit18'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet12: TTabSheet
                Caption = 'Frame 40 (Area1)'
                ImageIndex = 1
                object GroupBox19: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 561
                  Height = 213
                  TabOrder = 0
                  object LabeledEdit111: TLabeledEdit
                    Left = 270
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit111'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit112: TLabeledEdit
                    Left = 270
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit112'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit113: TLabeledEdit
                    Left = 270
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit113'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit114: TLabeledEdit
                    Left = 270
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit114'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit27: TLabeledEdit
                    Left = 24
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit27'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit28: TLabeledEdit
                    Left = 24
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit28'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit25: TLabeledEdit
                    Left = 24
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit25'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit26: TLabeledEdit
                    Left = 24
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit26'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet13: TTabSheet
                Caption = 'Frame 60 (Area2)'
                ImageIndex = 2
                object GroupBox20: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 561
                  Height = 213
                  TabOrder = 0
                  object LabeledEdit123: TLabeledEdit
                    Left = 24
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit123'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit124: TLabeledEdit
                    Left = 24
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit124'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit125: TLabeledEdit
                    Left = 24
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit125'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit126: TLabeledEdit
                    Left = 24
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit126'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit127: TLabeledEdit
                    Left = 270
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit127'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit128: TLabeledEdit
                    Left = 270
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit128'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit129: TLabeledEdit
                    Left = 270
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit129'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit130: TLabeledEdit
                    Left = 270
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit130'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet14: TTabSheet
                Caption = 'Frame 40 (Area2)'
                ImageIndex = 3
                object GroupBox21: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 561
                  Height = 213
                  TabOrder = 0
                  object LabeledEdit131: TLabeledEdit
                    Left = 24
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit131'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit132: TLabeledEdit
                    Left = 24
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit132'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit133: TLabeledEdit
                    Left = 24
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit133'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit134: TLabeledEdit
                    Left = 24
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit134'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit135: TLabeledEdit
                    Left = 270
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit135'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit136: TLabeledEdit
                    Left = 270
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit136'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit137: TLabeledEdit
                    Left = 270
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit137'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit138: TLabeledEdit
                    Left = 270
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit138'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet15: TTabSheet
                Caption = 'Frame 60 (Area3)'
                ImageIndex = 4
                object GroupBox22: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 561
                  Height = 213
                  TabOrder = 0
                  object LabeledEdit139: TLabeledEdit
                    Left = 24
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit139'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit140: TLabeledEdit
                    Left = 24
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit140'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit141: TLabeledEdit
                    Left = 24
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit141'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit142: TLabeledEdit
                    Left = 24
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit142'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit143: TLabeledEdit
                    Left = 270
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit143'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit144: TLabeledEdit
                    Left = 270
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit144'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit145: TLabeledEdit
                    Left = 270
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit145'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit146: TLabeledEdit
                    Left = 270
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit146'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet16: TTabSheet
                Caption = 'Frame 40 (Area3)'
                ImageIndex = 5
                object GroupBox23: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 561
                  Height = 213
                  TabOrder = 0
                  object LabeledEdit147: TLabeledEdit
                    Left = 24
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit147'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 0
                  end
                  object LabeledEdit148: TLabeledEdit
                    Left = 24
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit148'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 1
                  end
                  object LabeledEdit149: TLabeledEdit
                    Left = 24
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit149'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 2
                  end
                  object LabeledEdit150: TLabeledEdit
                    Left = 24
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit150'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit151: TLabeledEdit
                    Left = 270
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit151'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit152: TLabeledEdit
                    Left = 270
                    Top = 128
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit152'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit153: TLabeledEdit
                    Left = 270
                    Top = 80
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit153'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit154: TLabeledEdit
                    Left = 270
                    Top = 176
                    Width = 49
                    Height = 21
                    EditLabel.Width = 74
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit154'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
            end
          end
        end
        object TabSheet17: TTabSheet
          Caption = 'Precharge'
          ImageIndex = 3
          object GroupBox24: TGroupBox
            Left = 8
            Top = 8
            Width = 265
            Height = 273
            Caption = 'Normal Gate On'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object LabeledEdit31: TLabeledEdit
              Left = 8
              Top = 136
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit31'
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
              TabOrder = 0
            end
            object LabeledEdit42: TLabeledEdit
              Left = 8
              Top = 240
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit42'
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
              Visible = False
            end
            object LabeledEdit30: TLabeledEdit
              Left = 8
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit30'
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
            object LabeledEdit29: TLabeledEdit
              Left = 8
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit29'
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
            object LabeledEdit39: TLabeledEdit
              Left = 128
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit39'
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
            object LabeledEdit40: TLabeledEdit
              Left = 128
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit40'
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
              TabOrder = 5
            end
            object LabeledEdit41: TLabeledEdit
              Left = 128
              Top = 136
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit41'
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
              TabOrder = 6
            end
            object LabeledEdit103: TLabeledEdit
              Left = 8
              Top = 192
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit103'
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
              TabOrder = 7
            end
            object LabeledEdit104: TLabeledEdit
              Left = 128
              Top = 192
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit104'
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
              TabOrder = 8
            end
          end
          object GroupBox25: TGroupBox
            Left = 280
            Top = 8
            Width = 433
            Height = 273
            Caption = 'Fix Gate On'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            object LabeledEdit105: TLabeledEdit
              Left = 8
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit105'
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
              TabOrder = 0
              Visible = False
            end
            object LabeledEdit106: TLabeledEdit
              Left = 208
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit106'
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
              Visible = False
            end
            object LabeledEdit107: TLabeledEdit
              Left = 8
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit107'
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
              Visible = False
            end
            object LabeledEdit108: TLabeledEdit
              Left = 208
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit108'
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
              Visible = False
            end
            object LabeledEdit109: TLabeledEdit
              Left = 8
              Top = 136
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit109'
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
              Visible = False
            end
            object LabeledEdit110: TLabeledEdit
              Left = 208
              Top = 136
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit110'
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
              TabOrder = 5
              Visible = False
            end
            object LabeledEdit115: TLabeledEdit
              Left = 8
              Top = 192
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit115'
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
              TabOrder = 6
              Visible = False
            end
            object LabeledEdit116: TLabeledEdit
              Left = 208
              Top = 192
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit116'
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
              TabOrder = 7
              Visible = False
            end
          end
        end
        object TabSheet5: TTabSheet
          Caption = 'GOA'
          ImageIndex = 3
          object GroupBox12: TGroupBox
            Left = 8
            Top = 56
            Width = 321
            Height = 225
            Caption = 'TVCK'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object LabeledEdit34: TLabeledEdit
              Left = 24
              Top = 40
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit34'
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
              TabOrder = 0
              Visible = False
            end
            object LabeledEdit35: TLabeledEdit
              Left = 24
              Top = 88
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit35'
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
              Visible = False
            end
            object LabeledEdit36: TLabeledEdit
              Left = 24
              Top = 136
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit36'
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
              Visible = False
            end
            object LabeledEdit37: TLabeledEdit
              Left = 24
              Top = 184
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit37'
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
              Visible = False
            end
            object LabeledEdit38: TLabeledEdit
              Left = 96
              Top = 256
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit38'
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
              Visible = False
            end
            object LabeledEdit155: TLabeledEdit
              Left = 160
              Top = 40
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit155'
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
              TabOrder = 5
              Visible = False
            end
            object LabeledEdit156: TLabeledEdit
              Left = 160
              Top = 88
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit156'
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
              TabOrder = 6
              Visible = False
            end
            object LabeledEdit157: TLabeledEdit
              Left = 160
              Top = 136
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit157'
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
              TabOrder = 7
              Visible = False
            end
            object LabeledEdit158: TLabeledEdit
              Left = 160
              Top = 184
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit158'
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
              TabOrder = 8
              Visible = False
            end
          end
          object GroupBox26: TGroupBox
            Left = 336
            Top = 8
            Width = 377
            Height = 137
            Caption = 'VCS'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            object LabeledEdit117: TLabeledEdit
              Left = 24
              Top = 36
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit117'
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
              TabOrder = 0
              Visible = False
            end
            object LabeledEdit118: TLabeledEdit
              Left = 144
              Top = 36
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit118'
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
              Visible = False
            end
            object LabeledEdit119: TLabeledEdit
              Left = 264
              Top = 36
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit119'
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
              Visible = False
            end
            object LabeledEdit159: TLabeledEdit
              Left = 24
              Top = 84
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit159'
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
              Visible = False
            end
            object LabeledEdit160: TLabeledEdit
              Left = 144
              Top = 84
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit160'
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
              Visible = False
            end
            object LabeledEdit161: TLabeledEdit
              Left = 264
              Top = 84
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit161'
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
              TabOrder = 5
              Visible = False
            end
          end
          object GroupBox27: TGroupBox
            Left = 336
            Top = 152
            Width = 377
            Height = 129
            Caption = 'PWVCK'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 2
            object LabeledEdit120: TLabeledEdit
              Left = 24
              Top = 36
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit120'
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
              TabOrder = 0
              Visible = False
            end
            object LabeledEdit121: TLabeledEdit
              Left = 144
              Top = 36
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit121'
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
              Visible = False
            end
            object LabeledEdit122: TLabeledEdit
              Left = 264
              Top = 36
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit122'
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
              Visible = False
            end
            object LabeledEdit162: TLabeledEdit
              Left = 24
              Top = 84
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit162'
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
              Visible = False
            end
            object LabeledEdit163: TLabeledEdit
              Left = 144
              Top = 84
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit163'
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
              Visible = False
            end
            object LabeledEdit164: TLabeledEdit
              Left = 264
              Top = 84
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit164'
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
              TabOrder = 5
              Visible = False
            end
          end
          object LabeledEdit32: TLabeledEdit
            Left = 32
            Top = 24
            Width = 49
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit32'
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
            Visible = False
          end
          object LabeledEdit33: TLabeledEdit
            Left = 168
            Top = 24
            Width = 49
            Height = 21
            EditLabel.Width = 68
            EditLabel.Height = 13
            EditLabel.Caption = 'LabeledEdit33'
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
            Visible = False
          end
        end
        object TabSheet18: TTabSheet
          Caption = 'HSD_XSTB'
          ImageIndex = 4
          object GroupBox28: TGroupBox
            Left = 8
            Top = 8
            Width = 481
            Height = 121
            Caption = 'HSD_XSTB'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clTeal
            Font.Height = -11
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            object LabeledEdit165: TLabeledEdit
              Left = 16
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit165'
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
              TabOrder = 0
            end
            object LabeledEdit166: TLabeledEdit
              Left = 16
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit166'
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
            object LabeledEdit167: TLabeledEdit
              Left = 168
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit167'
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
            object LabeledEdit168: TLabeledEdit
              Left = 168
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit168'
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
            object LabeledEdit169: TLabeledEdit
              Left = 320
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit169'
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
            object LabeledEdit170: TLabeledEdit
              Left = 320
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 74
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit170'
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
              TabOrder = 5
            end
          end
        end
      end
    end
  end
end
