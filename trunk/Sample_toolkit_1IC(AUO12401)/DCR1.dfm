object DCRForm1: TDCRForm1
  Left = 216
  Top = 205
  Width = 755
  Height = 512
  Align = alCustom
  Caption = 'DCR'
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
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 745
    Height = 473
    ActivePage = TabSheet2
    TabIndex = 1
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'DCR Setting'
      object Label15: TLabel
        Left = 136
        Top = 16
        Width = 38
        Height = 13
        Caption = 'Label15'
      end
      object Label16: TLabel
        Left = 136
        Top = 48
        Width = 38
        Height = 13
        Caption = 'Label16'
      end
      object Label17: TLabel
        Left = 136
        Top = 80
        Width = 38
        Height = 13
        Caption = 'Label17'
      end
      object Label1: TLabel
        Left = 16
        Top = 136
        Width = 32
        Height = 13
        Caption = 'Label1'
      end
      object Label2: TLabel
        Left = 16
        Top = 168
        Width = 32
        Height = 13
        Caption = 'Label2'
      end
      object CheckBox1: TCheckBox
        Left = 16
        Top = 8
        Width = 105
        Height = 17
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 16
        Top = 32
        Width = 105
        Height = 17
        Caption = 'CheckBox2'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 16
        Top = 56
        Width = 105
        Height = 17
        Caption = 'CheckBox3'
        TabOrder = 2
      end
      object CheckBox4: TCheckBox
        Left = 16
        Top = 80
        Width = 97
        Height = 17
        Caption = 'CheckBox4'
        TabOrder = 3
      end
      object CheckBox5: TCheckBox
        Left = 16
        Top = 104
        Width = 97
        Height = 17
        Caption = 'CheckBox5'
        TabOrder = 4
      end
      object ComboBox2: TComboBox
        Left = 248
        Top = 16
        Width = 97
        Height = 21
        ItemHeight = 13
        TabOrder = 5
        Text = 'ComboBox2'
      end
      object ComboBox3: TComboBox
        Left = 248
        Top = 48
        Width = 97
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = 'ComboBox3'
      end
      object ComboBox4: TComboBox
        Left = 248
        Top = 80
        Width = 97
        Height = 21
        ItemHeight = 13
        TabOrder = 7
        Text = 'ComboBox4'
      end
      object ScrollBar1: TScrollBar
        Left = 128
        Top = 136
        Width = 161
        Height = 17
        PageSize = 0
        TabOrder = 8
      end
      object ScrollBar2: TScrollBar
        Left = 128
        Top = 168
        Width = 161
        Height = 17
        PageSize = 0
        TabOrder = 9
      end
      object StaticText1: TStaticText
        Left = 295
        Top = 136
        Width = 58
        Height = 17
        BorderStyle = sbsSunken
        Caption = 'StaticText1'
        TabOrder = 10
      end
      object StaticText2: TStaticText
        Left = 295
        Top = 168
        Width = 58
        Height = 17
        BorderStyle = sbsSunken
        Caption = 'StaticText2'
        TabOrder = 11
      end
      object GroupBox1: TGroupBox
        Left = 8
        Top = 208
        Width = 345
        Height = 49
        Caption = 'BackLight Gradient Step'
        TabOrder = 12
        object Label3: TLabel
          Left = 9
          Top = 28
          Width = 32
          Height = 13
          Caption = 'Label3'
        end
        object CheckBox6: TCheckBox
          Left = 168
          Top = 0
          Width = 97
          Height = 17
          Caption = 'CheckBox6'
          TabOrder = 0
        end
        object ScrollBar3: TScrollBar
          Left = 120
          Top = 24
          Width = 161
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText3: TStaticText
          Left = 287
          Top = 24
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText3'
          TabOrder = 2
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 280
        Width = 345
        Height = 49
        Caption = 'IMG_DIFF'
        TabOrder = 13
        object Label4: TLabel
          Left = 9
          Top = 28
          Width = 32
          Height = 13
          Caption = 'Label4'
        end
        object ScrollBar4: TScrollBar
          Left = 120
          Top = 24
          Width = 161
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText4: TStaticText
          Left = 287
          Top = 24
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText4'
          TabOrder = 1
        end
        object CheckBox7: TCheckBox
          Left = 168
          Top = 0
          Width = 89
          Height = 17
          Caption = 'CheckBox7'
          TabOrder = 2
        end
      end
      object GroupBox3: TGroupBox
        Left = 8
        Top = 344
        Width = 345
        Height = 81
        Caption = 'PWM Frequency Setting'
        TabOrder = 14
        object Label5: TLabel
          Left = 9
          Top = 60
          Width = 32
          Height = 13
          Caption = 'Label5'
        end
        object Label14: TLabel
          Left = 11
          Top = 24
          Width = 38
          Height = 13
          Caption = 'Label14'
        end
        object ComboBox1: TComboBox
          Left = 120
          Top = 24
          Width = 121
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'ComboBox1'
        end
        object ScrollBar5: TScrollBar
          Left = 120
          Top = 56
          Width = 161
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText5: TStaticText
          Left = 287
          Top = 56
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText5'
          TabOrder = 2
        end
      end
      object GroupBox4: TGroupBox
        Left = 376
        Top = 36
        Width = 345
        Height = 73
        Caption = 'SMBUS'
        TabOrder = 15
        object Label6: TLabel
          Left = 9
          Top = 28
          Width = 32
          Height = 13
          Caption = 'Label6'
        end
        object Label7: TLabel
          Left = 9
          Top = 52
          Width = 32
          Height = 13
          Caption = 'Label7'
        end
        object ScrollBar6: TScrollBar
          Left = 120
          Top = 24
          Width = 161
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText6: TStaticText
          Left = 287
          Top = 24
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText6'
          TabOrder = 1
        end
        object ScrollBar7: TScrollBar
          Left = 120
          Top = 48
          Width = 161
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText7: TStaticText
          Left = 287
          Top = 48
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText7'
          TabOrder = 3
        end
        object CheckBox8: TCheckBox
          Left = 168
          Top = 0
          Width = 89
          Height = 17
          Caption = 'CheckBox8'
          TabOrder = 4
        end
      end
      object GroupBox5: TGroupBox
        Left = 376
        Top = 128
        Width = 353
        Height = 73
        Caption = 'Idx Cum Ratio'
        TabOrder = 16
        object Label8: TLabel
          Left = 9
          Top = 28
          Width = 32
          Height = 13
          Caption = 'Label8'
        end
        object Label9: TLabel
          Left = 8
          Top = 52
          Width = 32
          Height = 13
          Caption = 'Label9'
        end
        object ScrollBar8: TScrollBar
          Left = 136
          Top = 24
          Width = 145
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText8: TStaticText
          Left = 289
          Top = 24
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText8'
          TabOrder = 1
        end
        object ScrollBar9: TScrollBar
          Left = 136
          Top = 48
          Width = 145
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText9: TStaticText
          Left = 289
          Top = 48
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText9'
          TabOrder = 3
        end
      end
      object GroupBox6: TGroupBox
        Left = 376
        Top = 224
        Width = 353
        Height = 65
        TabOrder = 17
        object Label10: TLabel
          Left = 8
          Top = 20
          Width = 38
          Height = 13
          Caption = 'Label10'
        end
        object Label11: TLabel
          Left = 8
          Top = 40
          Width = 38
          Height = 13
          Caption = 'Label11'
        end
        object ScrollBar10: TScrollBar
          Left = 136
          Top = 16
          Width = 145
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object StaticText10: TStaticText
          Left = 289
          Top = 16
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText10'
          TabOrder = 1
        end
        object ScrollBar11: TScrollBar
          Left = 136
          Top = 40
          Width = 145
          Height = 17
          PageSize = 0
          TabOrder = 2
        end
        object StaticText11: TStaticText
          Left = 289
          Top = 40
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText11'
          TabOrder = 3
        end
      end
      object GroupBox7: TGroupBox
        Left = 376
        Top = 312
        Width = 353
        Height = 73
        Caption = 'PWM_Coefficient'
        TabOrder = 18
        object Label13: TLabel
          Left = 8
          Top = 48
          Width = 38
          Height = 13
          Caption = 'Label13'
        end
        object Label12: TLabel
          Left = 8
          Top = 24
          Width = 38
          Height = 13
          Caption = 'Label12'
        end
        object ScrollBar12: TScrollBar
          Left = 136
          Top = 24
          Width = 145
          Height = 17
          PageSize = 0
          TabOrder = 0
        end
        object ScrollBar13: TScrollBar
          Left = 136
          Top = 48
          Width = 145
          Height = 17
          PageSize = 0
          TabOrder = 1
        end
        object StaticText12: TStaticText
          Left = 288
          Top = 24
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText12'
          TabOrder = 2
        end
        object StaticText13: TStaticText
          Left = 288
          Top = 48
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText13'
          TabOrder = 3
        end
        object CheckBox9: TCheckBox
          Left = 106
          Top = 0
          Width = 105
          Height = 17
          Caption = 'CheckBox9'
          TabOrder = 4
        end
      end
      object Btn_DCR_reload: TBitBtn
        Left = 384
        Top = 396
        Width = 73
        Height = 25
        Caption = '&Reload'
        ModalResult = 6
        TabOrder = 19
        OnClick = Btn_DCR_reloadClick
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
    object TabSheet2: TTabSheet
      Caption = 'DCR Table'
      ImageIndex = 1
      object sg_dcr_bl: TStringGrid
        Left = 64
        Top = 24
        Width = 106
        Height = 385
        ColCount = 2
        DefaultColWidth = 40
        DefaultRowHeight = 20
        RowCount = 129
        TabOrder = 0
        ColWidths = (
          40
          40)
        RowHeights = (
          20
          20
          20
          20
          18
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
          20
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
      object sg_dcr_dim: TStringGrid
        Left = 209
        Top = 24
        Width = 105
        Height = 385
        ColCount = 2
        DefaultColWidth = 40
        DefaultRowHeight = 20
        RowCount = 129
        TabOrder = 1
        ColWidths = (
          40
          40)
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
          20)
      end
      object btn_dcr_lut_read: TButton
        Left = 344
        Top = 88
        Width = 57
        Height = 25
        Caption = 'R&ead'
        TabOrder = 2
        OnClick = btn_dcr_lut_readClick
      end
      object btn_dcr_lut_write: TButton
        Left = 344
        Top = 128
        Width = 57
        Height = 25
        Caption = '&Write'
        TabOrder = 3
        OnClick = btn_dcr_lut_writeClick
      end
      object btn_dcr_lut_save: TButton
        Left = 344
        Top = 200
        Width = 57
        Height = 25
        Hint = 'Save as ".txt", digit type "Hex"'
        Caption = '&Save File'
        TabOrder = 4
        OnClick = btn_dcr_lut_saveClick
      end
      object btn_dcr_lut_load: TButton
        Left = 344
        Top = 240
        Width = 57
        Height = 25
        Hint = 
          'Load ".txt" file, Number is "Hex"Save as ".txt", digits type "He' +
          'x"'
        Caption = '&Load File'
        TabOrder = 5
        OnClick = btn_dcr_lut_loadClick
      end
    end
  end
  object CheckBox10: TCheckBox
    Left = 704
    Top = 8
    Width = 97
    Height = 17
    Caption = 'CheckBox10'
    TabOrder = 1
    Visible = False
  end
  object OpenDialog1: TOpenDialog
    Left = 712
    Top = 424
  end
  object SaveDialog1: TSaveDialog
    Left = 672
    Top = 424
  end
end
