object VenderForm1: TVenderForm1
  Left = 250
  Top = 140
  Width = 705
  Height = 497
  VertScrollBar.Position = 119
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
    Top = -119
    Width = 858
    Height = 562
    ActivePage = ts_debug
    TabIndex = 1
    TabOrder = 0
    object ts_vender: TTabSheet
      Caption = 'Vender'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 5
        Width = 848
        Height = 528
        TabOrder = 0
        object Label8: TLabel
          Left = 20
          Top = 325
          Width = 41
          Height = 16
          Caption = 'Label8'
        end
        object Label9: TLabel
          Left = 20
          Top = 364
          Width = 41
          Height = 16
          Caption = 'Label9'
        end
        object Label10: TLabel
          Left = 20
          Top = 404
          Width = 48
          Height = 16
          Caption = 'Label10'
        end
        object Label11: TLabel
          Left = 20
          Top = 443
          Width = 48
          Height = 16
          Caption = 'Label11'
        end
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
        object ScrollBar1: TScrollBar
          Left = 158
          Top = 325
          Width = 355
          Height = 21
          PageSize = 0
          TabOrder = 4
        end
        object ScrollBar2: TScrollBar
          Left = 158
          Top = 364
          Width = 355
          Height = 21
          DragKind = dkDock
          PageSize = 0
          TabOrder = 5
        end
        object ScrollBar3: TScrollBar
          Left = 158
          Top = 404
          Width = 355
          Height = 21
          DragMode = dmAutomatic
          PageSize = 0
          TabOrder = 6
        end
        object ScrollBar4: TScrollBar
          Left = 158
          Top = 443
          Width = 355
          Height = 21
          PageSize = 0
          TabOrder = 7
        end
        object ComboBox1: TComboBox
          Left = 423
          Top = 30
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 8
          Text = 'ComboBox1'
        end
        object ComboBox2: TComboBox
          Left = 423
          Top = 69
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 9
          Text = 'ComboBox2'
        end
        object ComboBox3: TComboBox
          Left = 423
          Top = 108
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 10
          Text = 'ComboBox3'
        end
        object ComboBox4: TComboBox
          Left = 423
          Top = 148
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 11
          Text = 'ComboBox4'
        end
        object ComboBox5: TComboBox
          Left = 423
          Top = 187
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 12
          Text = 'ComboBox5'
        end
        object ComboBox6: TComboBox
          Left = 423
          Top = 226
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 13
          Text = 'ComboBox6'
        end
        object ComboBox7: TComboBox
          Left = 423
          Top = 266
          Width = 179
          Height = 24
          ItemHeight = 16
          TabOrder = 14
          Text = 'ComboBox7'
        end
        object StaticText1: TStaticText
          Left = 522
          Top = 325
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText1'
          TabOrder = 15
        end
        object StaticText2: TStaticText
          Left = 522
          Top = 364
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText2'
          TabOrder = 16
        end
        object StaticText3: TStaticText
          Left = 522
          Top = 404
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText3'
          TabOrder = 17
        end
        object StaticText4: TStaticText
          Left = 522
          Top = 443
          Width = 70
          Height = 20
          BorderStyle = sbsSunken
          Caption = 'StaticText4'
          TabOrder = 18
        end
        object Btn_vender_reload: TBitBtn
          Left = 20
          Top = 482
          Width = 90
          Height = 31
          Caption = '&Reload'
          ModalResult = 6
          TabOrder = 19
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
        Width = 346
        Height = 424
        Caption = 'Debug Mode'
        TabOrder = 0
        object Label12: TLabel
          Left = 10
          Top = 52
          Width = 48
          Height = 16
          Caption = 'Label12'
        end
        object CheckBox5: TCheckBox
          Left = 30
          Top = 20
          Width = 158
          Height = 21
          Caption = 'CheckBox5'
          TabOrder = 0
        end
        object GroupBox15: TGroupBox
          Left = 49
          Top = 236
          Width = 257
          Height = 179
          Caption = 'Gamma Test'
          TabOrder = 1
          object LabeledEdit3: TLabeledEdit
            Left = 167
            Top = 59
            Width = 71
            Height = 24
            EditLabel.Width = 99
            EditLabel.Height = 19
            EditLabel.Caption = 'LabeledEdit3'
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 0
          end
          object CheckBox8: TCheckBox
            Left = 20
            Top = 30
            Width = 158
            Height = 20
            Caption = 'CheckBox8'
            TabOrder = 1
          end
          object LabeledEdit4: TLabeledEdit
            Left = 167
            Top = 98
            Width = 71
            Height = 24
            EditLabel.Width = 99
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit4'
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 2
          end
          object LabeledEdit5: TLabeledEdit
            Left = 167
            Top = 138
            Width = 71
            Height = 24
            EditLabel.Width = 99
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit5'
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 3
          end
        end
        object DCR: TGroupBox
          Left = 49
          Top = 79
          Width = 257
          Height = 149
          Caption = 'DCR'
          TabOrder = 2
          object CheckBox7: TCheckBox
            Left = 20
            Top = 49
            Width = 158
            Height = 21
            Caption = 'CheckBox7'
            TabOrder = 0
          end
          object CheckBox6: TCheckBox
            Left = 20
            Top = 20
            Width = 168
            Height = 21
            Caption = 'CheckBox6'
            TabOrder = 1
          end
          object LabeledEdit1: TLabeledEdit
            Left = 167
            Top = 79
            Width = 71
            Height = 24
            EditLabel.Width = 99
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit1'
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 2
          end
          object LabeledEdit2: TLabeledEdit
            Left = 167
            Top = 113
            Width = 71
            Height = 24
            EditLabel.Width = 99
            EditLabel.Height = 19
            EditLabel.Caption = 'LabeledEdit2'
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 3
          end
        end
        object ComboBox8: TComboBox
          Left = 108
          Top = 49
          Width = 228
          Height = 24
          ItemHeight = 16
          TabOrder = 3
          Text = 'ComboBox8'
        end
      end
      object GroupBox16: TGroupBox
        Left = 374
        Top = 10
        Width = 297
        Height = 424
        Caption = 'Status'
        TabOrder = 1
        object btn_status_refresh: TBitBtn
          Left = 207
          Top = 20
          Width = 80
          Height = 30
          Caption = 'Re&fresh'
          TabOrder = 0
          OnClick = btn_status_refreshClick
        end
        object GroupBox17: TGroupBox
          Left = 10
          Top = 54
          Width = 277
          Height = 174
          Caption = 'DCR'
          TabOrder = 1
          object LabeledEdit6: TLabeledEdit
            Left = 197
            Top = 15
            Width = 70
            Height = 24
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit6'
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ReadOnly = True
            TabOrder = 0
          end
          object LabeledEdit7: TLabeledEdit
            Left = 197
            Top = 54
            Width = 70
            Height = 24
            EditLabel.Width = 98
            EditLabel.Height = 19
            EditLabel.Caption = 'LabeledEdit7'
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ReadOnly = True
            TabOrder = 1
          end
          object LabeledEdit8: TLabeledEdit
            Left = 197
            Top = 89
            Width = 70
            Height = 24
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit8'
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ReadOnly = True
            TabOrder = 2
          end
          object LabeledEdit9: TLabeledEdit
            Left = 197
            Top = 128
            Width = 70
            Height = 24
            EditLabel.Width = 98
            EditLabel.Height = 20
            EditLabel.Caption = 'LabeledEdit9'
            LabelPosition = lpLeft
            LabelSpacing = 3
            ParentColor = True
            ReadOnly = True
            TabOrder = 3
          end
        end
        object GroupBox18: TGroupBox
          Left = 10
          Top = 241
          Width = 277
          Height = 174
          Caption = 'CORE State'
          TabOrder = 2
          object Label13: TLabel
            Left = 30
            Top = 30
            Width = 48
            Height = 16
            Caption = 'Label13'
          end
          object Label14: TLabel
            Left = 30
            Top = 59
            Width = 48
            Height = 16
            Caption = 'Label14'
          end
          object Label15: TLabel
            Left = 30
            Top = 89
            Width = 48
            Height = 16
            Caption = 'Label15'
          end
          object Label16: TLabel
            Left = 30
            Top = 118
            Width = 48
            Height = 16
            Caption = 'Label16'
          end
          object Label17: TLabel
            Left = 30
            Top = 148
            Width = 48
            Height = 16
            Caption = 'Label17'
          end
          object ComboBox9: TComboBox
            Left = 158
            Top = 20
            Width = 109
            Height = 24
            ItemHeight = 16
            TabOrder = 0
            Text = 'ComboBox9'
          end
          object ComboBox10: TComboBox
            Left = 158
            Top = 49
            Width = 109
            Height = 24
            ItemHeight = 16
            TabOrder = 1
            Text = 'ComboBox10'
          end
          object ComboBox11: TComboBox
            Left = 158
            Top = 79
            Width = 109
            Height = 24
            ItemHeight = 16
            TabOrder = 2
            Text = 'ComboBox11'
          end
          object ComboBox12: TComboBox
            Left = 158
            Top = 108
            Width = 109
            Height = 24
            ItemHeight = 16
            TabOrder = 3
            Text = 'ComboBox12'
          end
          object ComboBox13: TComboBox
            Left = 158
            Top = 138
            Width = 109
            Height = 24
            ItemHeight = 16
            TabOrder = 4
            Text = 'ComboBox13'
          end
        end
      end
      object btn_debug_reload: TBitBtn
        Left = 10
        Top = 453
        Width = 90
        Height = 31
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 2
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
  end
end
