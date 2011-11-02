object SharpnessForm12307: TSharpnessForm12307
  Left = 341
  Top = 244
  Width = 821
  Height = 755
  Caption = 'Sharpness'
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
  object GroupBox3: TGroupBox
    Left = 8
    Top = 0
    Width = 769
    Height = 689
    TabOrder = 0
    object GroupBox2: TGroupBox
      Left = 272
      Top = 16
      Width = 489
      Height = 385
      Caption = 'Weighting'
      TabOrder = 0
      object Software: TLabel
        Left = 8
        Top = 24
        Width = 67
        Height = 13
        Caption = 'Software Gain'
      end
      object sb_softgain: TScrollBar
        Left = 96
        Top = 24
        Width = 273
        Height = 17
        Max = 150
        PageSize = 0
        Position = 10
        TabOrder = 0
        OnChange = sb_softgainChange
      end
      object st_softgain: TStaticText
        Left = 376
        Top = 24
        Width = 10
        Height = 17
        BorderStyle = sbsSunken
        Caption = '1'
        TabOrder = 1
      end
      object GroupBox47: TGroupBox
        Left = 8
        Top = 48
        Width = 473
        Height = 329
        TabOrder = 2
        object SP_LUT: TImage
          Left = 8
          Top = 16
          Width = 369
          Height = 305
          OnDblClick = SP_LUTDblClick
          OnMouseDown = SP_LUTMouseDown
        end
        object btn_sp_lut_write: TButton
          Left = 400
          Top = 24
          Width = 57
          Height = 25
          Caption = 'Write'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btn_sp_lut_writeClick
        end
        object btn_sp_lut_Set: TButton
          Left = 400
          Top = 104
          Width = 57
          Height = 25
          Caption = 'Clear'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btn_sp_lut_SetClick
        end
        object btn_sp_lut_read: TBitBtn
          Left = 400
          Top = 64
          Width = 57
          Height = 25
          Caption = 'Read'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = btn_sp_lut_readClick
        end
      end
      object btn_GainSet: TButton
        Left = 400
        Top = 16
        Width = 65
        Height = 25
        Caption = 'Gain Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btn_GainSetClick
      end
    end
    object LUT_type: TRadioGroup
      Left = 8
      Top = 336
      Width = 193
      Height = 49
      Caption = 'Sharpness Mode'
      Columns = 3
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      Items.Strings = (
        '1'
        '2'
        '3')
      ParentFont = False
      TabOrder = 1
      OnClick = LUT_typeClick
    end
    object btn_sp_Load: TButton
      Left = 208
      Top = 336
      Width = 49
      Height = 25
      Caption = 'Load'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = btn_sp_LoadClick
    end
    object btn_sp_Save: TButton
      Left = 208
      Top = 360
      Width = 49
      Height = 25
      Hint = 'Save SP Table'
      Caption = 'Save'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = btn_sp_SaveClick
    end
    object Btn_SP_reload: TBitBtn
      Left = 688
      Top = 416
      Width = 73
      Height = 25
      Caption = '&Reload'
      ModalResult = 6
      TabOrder = 4
      OnClick = Btn_SP_reloadClick
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
    object Sharpness: TGroupBox
      Left = 8
      Top = 16
      Width = 257
      Height = 297
      Caption = 'Sharpness'
      TabOrder = 5
      object Label1: TLabel
        Left = 8
        Top = 48
        Width = 32
        Height = 13
        Caption = 'Label1'
      end
      object Label2: TLabel
        Left = 8
        Top = 72
        Width = 32
        Height = 13
        Caption = 'Label2'
      end
      object Label3: TLabel
        Left = 8
        Top = 96
        Width = 32
        Height = 13
        Caption = 'Label3'
      end
      object Label4: TLabel
        Left = 8
        Top = 120
        Width = 32
        Height = 13
        Caption = 'Label4'
      end
      object Label5: TLabel
        Left = 8
        Top = 168
        Width = 32
        Height = 13
        Caption = 'Label5'
      end
      object Label6: TLabel
        Left = 8
        Top = 192
        Width = 32
        Height = 13
        Caption = 'Label6'
      end
      object Label7: TLabel
        Left = 8
        Top = 224
        Width = 32
        Height = 13
        Caption = 'Label7'
      end
      object Label8: TLabel
        Left = 8
        Top = 248
        Width = 32
        Height = 13
        Caption = 'Label8'
      end
      object CheckBox1: TCheckBox
        Left = 80
        Top = 0
        Width = 97
        Height = 17
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 8
        Top = 24
        Width = 97
        Height = 17
        Caption = 'CheckBox2'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 128
        Top = 24
        Width = 97
        Height = 17
        Caption = 'CheckBox3'
        TabOrder = 2
      end
      object ScrollBar1: TScrollBar
        Left = 88
        Top = 48
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 3
      end
      object StaticText1: TStaticText
        Left = 216
        Top = 48
        Width = 58
        Height = 17
        Caption = 'StaticText1'
        TabOrder = 4
      end
      object ScrollBar2: TScrollBar
        Left = 88
        Top = 72
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 5
      end
      object ScrollBar3: TScrollBar
        Left = 88
        Top = 96
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 6
      end
      object ScrollBar4: TScrollBar
        Left = 88
        Top = 120
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 7
      end
      object StaticText2: TStaticText
        Left = 216
        Top = 72
        Width = 58
        Height = 17
        Caption = 'StaticText2'
        TabOrder = 8
      end
      object StaticText3: TStaticText
        Left = 216
        Top = 96
        Width = 58
        Height = 17
        Caption = 'StaticText3'
        TabOrder = 9
      end
      object StaticText4: TStaticText
        Left = 216
        Top = 120
        Width = 58
        Height = 17
        Caption = 'StaticText4'
        TabOrder = 10
      end
      object CheckBox4: TCheckBox
        Left = 8
        Top = 144
        Width = 97
        Height = 17
        Caption = 'CheckBox4'
        TabOrder = 11
      end
      object CheckBox5: TCheckBox
        Left = 128
        Top = 144
        Width = 97
        Height = 17
        Caption = 'CheckBox5'
        TabOrder = 12
      end
      object ScrollBar5: TScrollBar
        Left = 88
        Top = 168
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 13
      end
      object ScrollBar6: TScrollBar
        Left = 88
        Top = 192
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 14
      end
      object StaticText5: TStaticText
        Left = 216
        Top = 168
        Width = 58
        Height = 17
        Caption = 'StaticText5'
        TabOrder = 15
      end
      object StaticText6: TStaticText
        Left = 216
        Top = 192
        Width = 58
        Height = 17
        Caption = 'StaticText6'
        TabOrder = 16
      end
      object ComboBox1: TComboBox
        Left = 64
        Top = 216
        Width = 185
        Height = 21
        ItemHeight = 13
        TabOrder = 17
        Text = 'ComboBox1'
      end
      object ComboBox2: TComboBox
        Left = 64
        Top = 240
        Width = 185
        Height = 21
        ItemHeight = 13
        TabOrder = 18
        Text = 'ComboBox2'
      end
      object CheckBox6: TCheckBox
        Left = 8
        Top = 272
        Width = 97
        Height = 17
        Caption = 'CheckBox6'
        TabOrder = 19
      end
      object CheckBox7: TCheckBox
        Left = 128
        Top = 272
        Width = 97
        Height = 17
        Caption = 'CheckBox7'
        TabOrder = 20
      end
    end
    object Contrast: TGroupBox
      Left = 8
      Top = 408
      Width = 673
      Height = 273
      Caption = 'Contrast'
      TabOrder = 6
      object Label9: TLabel
        Left = 8
        Top = 80
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
      object Label11: TLabel
        Left = 8
        Top = 128
        Width = 38
        Height = 13
        Caption = 'Label11'
      end
      object Label12: TLabel
        Left = 8
        Top = 152
        Width = 38
        Height = 13
        Caption = 'Label12'
      end
      object Label13: TLabel
        Left = 8
        Top = 176
        Width = 38
        Height = 13
        Caption = 'Label13'
      end
      object Label14: TLabel
        Left = 8
        Top = 200
        Width = 38
        Height = 13
        Caption = 'Label14'
      end
      object Label15: TLabel
        Left = 8
        Top = 224
        Width = 38
        Height = 13
        Caption = 'Label15'
      end
      object Label16: TLabel
        Left = 8
        Top = 248
        Width = 38
        Height = 13
        Caption = 'Label16'
      end
      object Label17: TLabel
        Left = 328
        Top = 72
        Width = 38
        Height = 13
        Caption = 'Label17'
      end
      object Label18: TLabel
        Left = 328
        Top = 96
        Width = 38
        Height = 13
        Caption = 'Label18'
      end
      object Label19: TLabel
        Left = 328
        Top = 128
        Width = 38
        Height = 13
        Caption = 'Label19'
      end
      object Label20: TLabel
        Left = 328
        Top = 152
        Width = 38
        Height = 13
        Caption = 'Label20'
      end
      object Label21: TLabel
        Left = 328
        Top = 176
        Width = 38
        Height = 13
        Caption = 'Label21'
      end
      object Label22: TLabel
        Left = 328
        Top = 200
        Width = 38
        Height = 13
        Caption = 'Label22'
      end
      object CheckBox8: TCheckBox
        Left = 72
        Top = 0
        Width = 97
        Height = 17
        Caption = 'CheckBox8'
        TabOrder = 0
      end
      object CheckBox9: TCheckBox
        Left = 8
        Top = 24
        Width = 97
        Height = 17
        Caption = 'CheckBox9'
        TabOrder = 1
      end
      object CheckBox10: TCheckBox
        Left = 120
        Top = 24
        Width = 97
        Height = 17
        Caption = 'CheckBox10'
        TabOrder = 2
      end
      object CheckBox11: TCheckBox
        Left = 8
        Top = 48
        Width = 97
        Height = 17
        Caption = 'CheckBox11'
        TabOrder = 3
      end
      object CheckBox12: TCheckBox
        Left = 120
        Top = 48
        Width = 97
        Height = 17
        Caption = 'CheckBox12'
        TabOrder = 4
      end
      object ComboBox3: TComboBox
        Left = 120
        Top = 72
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 5
        Text = 'ComboBox3'
      end
      object ComboBox4: TComboBox
        Left = 120
        Top = 96
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = 'ComboBox4'
      end
      object ScrollBar7: TScrollBar
        Left = 112
        Top = 128
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 7
      end
      object ScrollBar8: TScrollBar
        Left = 112
        Top = 152
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 8
      end
      object ScrollBar9: TScrollBar
        Left = 112
        Top = 176
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 9
      end
      object ScrollBar10: TScrollBar
        Left = 112
        Top = 200
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 10
      end
      object ScrollBar11: TScrollBar
        Left = 112
        Top = 224
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 11
      end
      object ScrollBar12: TScrollBar
        Left = 112
        Top = 248
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 12
      end
      object StaticText7: TStaticText
        Left = 240
        Top = 128
        Width = 58
        Height = 17
        Caption = 'StaticText7'
        TabOrder = 13
      end
      object StaticText8: TStaticText
        Left = 240
        Top = 152
        Width = 58
        Height = 17
        Caption = 'StaticText8'
        TabOrder = 14
      end
      object StaticText9: TStaticText
        Left = 240
        Top = 176
        Width = 58
        Height = 17
        Caption = 'StaticText9'
        TabOrder = 15
      end
      object StaticText10: TStaticText
        Left = 240
        Top = 200
        Width = 64
        Height = 17
        Caption = 'StaticText10'
        TabOrder = 16
      end
      object StaticText11: TStaticText
        Left = 240
        Top = 224
        Width = 64
        Height = 17
        Caption = 'StaticText11'
        TabOrder = 17
      end
      object StaticText12: TStaticText
        Left = 240
        Top = 248
        Width = 64
        Height = 17
        Caption = 'StaticText12'
        TabOrder = 18
      end
      object LabeledEdit1: TLabeledEdit
        Left = 328
        Top = 32
        Width = 121
        Height = 21
        EditLabel.Width = 62
        EditLabel.Height = 13
        EditLabel.Caption = 'LabeledEdit1'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 19
      end
      object ComboBox5: TComboBox
        Left = 424
        Top = 64
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 20
        Text = 'ComboBox5'
      end
      object ComboBox6: TComboBox
        Left = 424
        Top = 88
        Width = 145
        Height = 21
        ItemHeight = 13
        TabOrder = 21
        Text = 'ComboBox6'
      end
      object ScrollBar13: TScrollBar
        Left = 424
        Top = 128
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 22
      end
      object ScrollBar14: TScrollBar
        Left = 424
        Top = 152
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 23
      end
      object ScrollBar15: TScrollBar
        Left = 424
        Top = 176
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 24
      end
      object ScrollBar16: TScrollBar
        Left = 424
        Top = 200
        Width = 121
        Height = 17
        PageSize = 0
        TabOrder = 25
      end
      object StaticText13: TStaticText
        Left = 552
        Top = 128
        Width = 64
        Height = 17
        Caption = 'StaticText13'
        TabOrder = 26
      end
      object StaticText14: TStaticText
        Left = 552
        Top = 152
        Width = 64
        Height = 17
        Caption = 'StaticText14'
        TabOrder = 27
      end
      object StaticText15: TStaticText
        Left = 552
        Top = 176
        Width = 64
        Height = 17
        Caption = 'StaticText15'
        TabOrder = 28
      end
      object StaticText16: TStaticText
        Left = 552
        Top = 200
        Width = 64
        Height = 17
        Caption = 'StaticText16'
        TabOrder = 29
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 739
  end
  object SaveDialog1: TSaveDialog
    Left = 707
  end
end
