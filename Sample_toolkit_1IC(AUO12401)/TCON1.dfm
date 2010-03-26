object TCONForm1: TTCONForm1
  Left = 208
  Top = 157
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
        Left = 16
        Top = 168
        Width = 32
        Height = 13
        Caption = 'Label1'
      end
      object Label3: TLabel
        Left = 152
        Top = 168
        Width = 32
        Height = 13
        Caption = 'Label3'
      end
      object Label4: TLabel
        Left = 272
        Top = 168
        Width = 32
        Height = 13
        Caption = 'Label4'
      end
      object CheckBox1: TCheckBox
        Left = 16
        Top = 16
        Width = 97
        Height = 17
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 16
        Top = 48
        Width = 97
        Height = 17
        Caption = 'CheckBox2'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 16
        Top = 80
        Width = 97
        Height = 17
        Caption = 'CheckBox3'
        TabOrder = 2
      end
      object CheckBox4: TCheckBox
        Left = 136
        Top = 80
        Width = 97
        Height = 17
        Caption = 'CheckBox7'
        TabOrder = 3
      end
      object CheckBox5: TCheckBox
        Left = 136
        Top = 16
        Width = 97
        Height = 17
        Caption = 'CheckBox5'
        TabOrder = 4
      end
      object CheckBox6: TCheckBox
        Left = 136
        Top = 48
        Width = 97
        Height = 17
        Caption = 'CheckBox6'
        TabOrder = 5
      end
      object CheckBox7: TCheckBox
        Left = 16
        Top = 112
        Width = 97
        Height = 17
        Caption = 'CheckBox4'
        TabOrder = 6
      end
      object CheckBox8: TCheckBox
        Left = 136
        Top = 112
        Width = 97
        Height = 17
        Caption = 'CheckBox8'
        TabOrder = 7
      end
      object CheckBox9: TCheckBox
        Left = 248
        Top = 16
        Width = 97
        Height = 17
        Caption = 'CheckBox9'
        TabOrder = 8
      end
      object CheckBox10: TCheckBox
        Left = 248
        Top = 48
        Width = 97
        Height = 17
        Caption = 'CheckBox10'
        TabOrder = 9
      end
      object ComboBox1: TComboBox
        Left = 16
        Top = 184
        Width = 81
        Height = 21
        ItemHeight = 13
        TabOrder = 10
        Text = 'ComboBox1'
      end
      object ComboBox2: TComboBox
        Left = 152
        Top = 184
        Width = 81
        Height = 21
        ItemHeight = 13
        TabOrder = 11
        Text = 'ComboBox2'
      end
      object ComboBox3: TComboBox
        Left = 272
        Top = 184
        Width = 81
        Height = 21
        ItemHeight = 13
        TabOrder = 12
        Text = 'ComboBox3'
      end
      object Btn_TCON_dev_reload: TBitBtn
        Left = 16
        Top = 240
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 13
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
    end
    object ts_tcon_drive: TTabSheet
      Caption = 'Dri&ving'
      ImageIndex = 2
      object GroupBox3: TGroupBox
        Left = 8
        Top = 16
        Width = 289
        Height = 321
        Caption = 'Driving Type'
        TabOrder = 0
        object Label8: TLabel
          Left = 136
          Top = 96
          Width = 32
          Height = 13
          Caption = 'Label8'
        end
        object Label14: TLabel
          Left = 136
          Top = 32
          Width = 38
          Height = 13
          Caption = 'Label14'
        end
        object CheckBox32: TCheckBox
          Left = 16
          Top = 88
          Width = 81
          Height = 17
          Caption = 'CheckBox32'
          TabOrder = 0
        end
        object CheckBox33: TCheckBox
          Left = 16
          Top = 112
          Width = 89
          Height = 25
          Caption = 'CheckBox33'
          TabOrder = 1
        end
        object CheckBox34: TCheckBox
          Left = 16
          Top = 144
          Width = 89
          Height = 25
          Caption = 'CheckBox34'
          TabOrder = 2
        end
        object CheckBox35: TCheckBox
          Left = 16
          Top = 176
          Width = 89
          Height = 25
          Caption = 'CheckBox35'
          TabOrder = 3
        end
        object CheckBox36: TCheckBox
          Left = 16
          Top = 208
          Width = 81
          Height = 25
          Caption = 'CheckBox36'
          TabOrder = 4
        end
        object CheckBox37: TCheckBox
          Left = 16
          Top = 240
          Width = 97
          Height = 25
          Caption = 'CheckBox37'
          TabOrder = 5
        end
        object ComboBox7: TComboBox
          Left = 136
          Top = 112
          Width = 89
          Height = 21
          ItemHeight = 13
          TabOrder = 6
          Text = 'ComboBox7'
        end
        object LabeledEdit1: TLabeledEdit
          Left = 136
          Top = 176
          Width = 89
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit1'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 7
        end
        object LabeledEdit2: TLabeledEdit
          Left = 136
          Top = 232
          Width = 89
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit2'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 8
        end
        object ComboBox5: TComboBox
          Left = 136
          Top = 48
          Width = 89
          Height = 21
          ItemHeight = 13
          TabOrder = 9
          Text = 'ComboBox5'
        end
        object CheckBox31: TCheckBox
          Left = 16
          Top = 48
          Width = 97
          Height = 25
          Caption = 'CheckBox31'
          TabOrder = 10
        end
        object CheckBox30: TCheckBox
          Left = 16
          Top = 24
          Width = 105
          Height = 17
          Caption = 'CheckBox30'
          TabOrder = 11
        end
      end
      object GroupBox5: TGroupBox
        Left = 488
        Top = 16
        Width = 169
        Height = 201
        Caption = 'Data Shift Control'
        TabOrder = 1
        object Label12: TLabel
          Left = 16
          Top = 96
          Width = 38
          Height = 13
          Caption = 'Label12'
        end
        object Label13: TLabel
          Left = 16
          Top = 152
          Width = 38
          Height = 13
          Caption = 'Label13'
        end
        object CheckBox40: TCheckBox
          Left = 16
          Top = 56
          Width = 89
          Height = 17
          Caption = 'CheckBox40'
          TabOrder = 0
        end
        object ComboBox11: TComboBox
          Left = 16
          Top = 112
          Width = 105
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = 'ComboBox11'
        end
        object ComboBox12: TComboBox
          Left = 16
          Top = 168
          Width = 105
          Height = 21
          ItemHeight = 13
          TabOrder = 2
          Text = 'ComboBox12'
        end
        object CheckBox39: TCheckBox
          Left = 16
          Top = 24
          Width = 105
          Height = 17
          Caption = 'CheckBox39'
          TabOrder = 3
        end
      end
      object GroupBox6: TGroupBox
        Left = 304
        Top = 16
        Width = 177
        Height = 201
        Caption = 'Blanking Gray Insertion'
        TabOrder = 2
        object Label9: TLabel
          Left = 16
          Top = 152
          Width = 32
          Height = 13
          Caption = 'Label9'
        end
        object ComboBox8: TComboBox
          Left = 16
          Top = 168
          Width = 129
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'ComboBox8'
        end
        object LabeledEdit4: TLabeledEdit
          Left = 16
          Top = 72
          Width = 89
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit4'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
        end
        object LabeledEdit5: TLabeledEdit
          Left = 16
          Top = 120
          Width = 89
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit5'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
        end
        object CheckBox38: TCheckBox
          Left = 16
          Top = 24
          Width = 81
          Height = 17
          Caption = 'CheckBox38'
          TabOrder = 3
        end
      end
      object GroupBox7: TGroupBox
        Left = 304
        Top = 224
        Width = 177
        Height = 113
        Caption = 'Inversion Select'
        TabOrder = 3
        object Label10: TLabel
          Left = 16
          Top = 16
          Width = 38
          Height = 13
          Caption = 'Label10'
        end
        object Label11: TLabel
          Left = 16
          Top = 64
          Width = 38
          Height = 13
          Caption = 'Label11'
        end
        object ComboBox9: TComboBox
          Left = 16
          Top = 32
          Width = 129
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'ComboBox9'
        end
        object ComboBox10: TComboBox
          Left = 16
          Top = 80
          Width = 129
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = 'ComboBox10'
        end
      end
      object Btn_TCON_drv_reload: TBitBtn
        Left = 16
        Top = 352
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 4
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
        TabOrder = 0
        object Label2: TLabel
          Left = 16
          Top = 32
          Width = 32
          Height = 13
          Caption = 'Label2'
        end
        object CheckBox11: TCheckBox
          Left = 16
          Top = 80
          Width = 137
          Height = 25
          Caption = 'CheckBox11'
          TabOrder = 0
        end
        object CheckBox12: TCheckBox
          Left = 16
          Top = 104
          Width = 137
          Height = 25
          Caption = 'CheckBox12'
          TabOrder = 1
        end
        object CheckBox13: TCheckBox
          Left = 16
          Top = 128
          Width = 137
          Height = 25
          Caption = 'CheckBox13'
          TabOrder = 2
        end
        object ComboBox4: TComboBox
          Left = 16
          Top = 48
          Width = 97
          Height = 21
          ItemHeight = 0
          TabOrder = 3
          Text = 'ComboBox4'
        end
      end
      object GroupBox2: TGroupBox
        Left = 192
        Top = 24
        Width = 241
        Height = 305
        Caption = 'Output'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object Label5: TLabel
          Left = 8
          Top = 88
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
          Top = 24
          Width = 81
          Height = 17
          Caption = 'CheckBox14'
          TabOrder = 0
        end
        object CheckBox15: TCheckBox
          Left = 16
          Top = 48
          Width = 89
          Height = 17
          Caption = 'CheckBox15'
          TabOrder = 1
        end
        object CheckBox16: TCheckBox
          Left = 128
          Top = 16
          Width = 89
          Height = 25
          Caption = 'CheckBox16'
          TabOrder = 2
        end
        object CheckBox17: TCheckBox
          Left = 16
          Top = 112
          Width = 89
          Height = 25
          Caption = 'CheckBox17'
          TabOrder = 3
        end
        object CheckBox18: TCheckBox
          Left = 16
          Top = 144
          Width = 89
          Height = 25
          Caption = 'CheckBox18'
          TabOrder = 4
        end
        object CheckBox19: TCheckBox
          Left = 16
          Top = 176
          Width = 89
          Height = 25
          Caption = 'CheckBox19'
          TabOrder = 5
        end
        object CheckBox20: TCheckBox
          Left = 16
          Top = 208
          Width = 89
          Height = 25
          Caption = 'CheckBox20'
          TabOrder = 6
        end
        object CheckBox21: TCheckBox
          Left = 16
          Top = 240
          Width = 81
          Height = 25
          Caption = 'CheckBox21'
          TabOrder = 7
        end
        object CheckBox22: TCheckBox
          Left = 16
          Top = 272
          Width = 81
          Height = 25
          Caption = 'CheckBox22'
          TabOrder = 8
        end
        object CheckBox23: TCheckBox
          Left = 136
          Top = 112
          Width = 89
          Height = 25
          Caption = 'CheckBox23'
          TabOrder = 9
        end
        object CheckBox24: TCheckBox
          Left = 136
          Top = 144
          Width = 97
          Height = 25
          Caption = 'CheckBox24'
          TabOrder = 10
        end
        object CheckBox25: TCheckBox
          Left = 136
          Top = 176
          Width = 97
          Height = 25
          Caption = 'CheckBox25'
          TabOrder = 11
        end
        object CheckBox26: TCheckBox
          Left = 136
          Top = 208
          Width = 97
          Height = 25
          Caption = 'CheckBox26'
          TabOrder = 12
        end
        object CheckBox27: TCheckBox
          Left = 136
          Top = 248
          Width = 97
          Height = 17
          Caption = 'CheckBox27'
          TabOrder = 13
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
        Top = 392
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
        Width = 513
        Height = 65
        Caption = 'Source'
        TabOrder = 1
        object LabeledEdit6: TLabeledEdit
          Left = 128
          Top = 32
          Width = 49
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit6'
          LabelPosition = lpAbove
          LabelSpacing = 3
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
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
        end
        object LabeledEdit7: TLabeledEdit
          Left = 248
          Top = 32
          Width = 49
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit7'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
        end
        object LabeledEdit8: TLabeledEdit
          Left = 376
          Top = 32
          Width = 49
          Height = 21
          EditLabel.Width = 62
          EditLabel.Height = 13
          EditLabel.Caption = 'LabeledEdit8'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
        end
      end
      object PageControl2: TPageControl
        Left = 0
        Top = 72
        Width = 601
        Height = 313
        ActivePage = TabSheet4
        TabIndex = 0
        TabOrder = 2
        object TabSheet4: TTabSheet
          Caption = 'Normal Mode'
          object GroupBox4: TGroupBox
            Left = 0
            Top = -4
            Width = 593
            Height = 289
            TabOrder = 0
            object Label16: TLabel
              Left = 8
              Top = 64
              Width = 50
              Height = 13
              Caption = 'PreCharge'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -11
              Font.Name = 'MS Sans Serif'
              Font.Style = []
              ParentFont = False
            end
            object PageControl1: TPageControl
              Left = 8
              Top = 128
              Width = 577
              Height = 153
              ActivePage = TabSheet2
              TabIndex = 0
              TabOrder = 0
              object TabSheet2: TTabSheet
                Caption = 'Frame 60'
                object GroupBox8: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 569
                  Height = 125
                  TabOrder = 0
                  object Label6: TLabel
                    Left = 8
                    Top = 64
                    Width = 50
                    Height = 13
                    Caption = 'FixGateOn'
                    Font.Charset = DEFAULT_CHARSET
                    Font.Color = clWindowText
                    Font.Height = -11
                    Font.Name = 'MS Sans Serif'
                    Font.Style = []
                    ParentFont = False
                  end
                  object LabeledEdit13: TLabeledEdit
                    Left = 8
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
                    Left = 136
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
                    Left = 264
                    Top = 32
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
                    Left = 392
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit16'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit17: TLabeledEdit
                    Left = 8
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit17'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit18: TLabeledEdit
                    Left = 136
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit18'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit19: TLabeledEdit
                    Left = 264
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit19'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit20: TLabeledEdit
                    Left = 392
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit20'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
              object TabSheet3: TTabSheet
                Caption = 'Frame 40'
                ImageIndex = 1
                object GroupBox9: TGroupBox
                  Left = 0
                  Top = -4
                  Width = 569
                  Height = 125
                  TabOrder = 0
                  object Label7: TLabel
                    Left = 8
                    Top = 64
                    Width = 50
                    Height = 13
                    Caption = 'FixGateOn'
                    Font.Charset = DEFAULT_CHARSET
                    Font.Color = clWindowText
                    Font.Height = -11
                    Font.Name = 'MS Sans Serif'
                    Font.Style = []
                    ParentFont = False
                  end
                  object LabeledEdit21: TLabeledEdit
                    Left = 8
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
                    Left = 136
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
                    Left = 264
                    Top = 32
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
                    Left = 392
                    Top = 32
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit24'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 3
                  end
                  object LabeledEdit25: TLabeledEdit
                    Left = 8
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit25'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 4
                  end
                  object LabeledEdit26: TLabeledEdit
                    Left = 136
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit26'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 5
                  end
                  object LabeledEdit27: TLabeledEdit
                    Left = 264
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit27'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 6
                  end
                  object LabeledEdit28: TLabeledEdit
                    Left = 392
                    Top = 96
                    Width = 49
                    Height = 21
                    EditLabel.Width = 68
                    EditLabel.Height = 13
                    EditLabel.Caption = 'LabeledEdit28'
                    LabelPosition = lpAbove
                    LabelSpacing = 3
                    TabOrder = 7
                  end
                end
              end
            end
            object LabeledEdit9: TLabeledEdit
              Left = 16
              Top = 32
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
              Left = 144
              Top = 32
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
              Left = 272
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit11'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
            end
            object LabeledEdit29: TLabeledEdit
              Left = 16
              Top = 96
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit29'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
            object LabeledEdit30: TLabeledEdit
              Left = 144
              Top = 96
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit30'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 5
            end
            object LabeledEdit12: TLabeledEdit
              Left = 400
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit12'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 6
            end
            object LabeledEdit31: TLabeledEdit
              Left = 272
              Top = 96
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit31'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 7
            end
            object LabeledEdit42: TLabeledEdit
              Left = 400
              Top = 96
              Width = 65
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit42'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 8
              Visible = False
            end
          end
        end
        object TabSheet5: TTabSheet
          Caption = 'GOA'
          ImageIndex = 1
          object GroupBox12: TGroupBox
            Left = 0
            Top = -4
            Width = 593
            Height = 285
            TabOrder = 0
            object LabeledEdit32: TLabeledEdit
              Left = 8
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit32'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit33: TLabeledEdit
              Left = 144
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit33'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit34: TLabeledEdit
              Left = 272
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit34'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
            end
            object LabeledEdit35: TLabeledEdit
              Left = 8
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit35'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
            end
            object LabeledEdit36: TLabeledEdit
              Left = 144
              Top = 80
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit36'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
            object LabeledEdit37: TLabeledEdit
              Left = 8
              Top = 128
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit37'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 5
            end
            object LabeledEdit38: TLabeledEdit
              Left = 144
              Top = 128
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit38'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 6
            end
          end
        end
        object TabSheet6: TTabSheet
          Caption = '2G1D'
          ImageIndex = 2
          object GroupBox11: TGroupBox
            Left = 0
            Top = -4
            Width = 593
            Height = 285
            TabOrder = 0
            object LabeledEdit39: TLabeledEdit
              Left = 8
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit39'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit40: TLabeledEdit
              Left = 144
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit40'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit41: TLabeledEdit
              Left = 272
              Top = 32
              Width = 49
              Height = 21
              EditLabel.Width = 68
              EditLabel.Height = 13
              EditLabel.Caption = 'LabeledEdit41'
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
            end
          end
        end
      end
    end
  end
end
