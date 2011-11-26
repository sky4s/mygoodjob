object SharpnessForm12307: TSharpnessForm12307
  Left = 426
  Top = 257
  Width = 821
  Height = 755
  Caption = 'Sharpness'
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
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox3: TGroupBox
    Left = 10
    Top = 0
    Width = 946
    Height = 848
    TabOrder = 0
    object GroupBox2: TGroupBox
      Left = 335
      Top = 20
      Width = 602
      Height = 474
      Caption = 'Weighting'
      TabOrder = 0
      object Software: TLabel
        Left = 10
        Top = 30
        Width = 83
        Height = 16
        Caption = 'Software Gain'
      end
      object sb_softgain: TScrollBar
        Left = 118
        Top = 30
        Width = 336
        Height = 20
        Max = 150
        PageSize = 0
        Position = 10
        TabOrder = 0
        OnChange = sb_softgainChange
      end
      object st_softgain: TStaticText
        Left = 463
        Top = 30
        Width = 11
        Height = 20
        BorderStyle = sbsSunken
        Caption = '1'
        TabOrder = 1
      end
      object GroupBox47: TGroupBox
        Left = 10
        Top = 59
        Width = 582
        Height = 405
        TabOrder = 2
        object SP_LUT: TImage
          Left = 10
          Top = 20
          Width = 454
          Height = 375
          OnDblClick = SP_LUTDblClick
          OnMouseDown = SP_LUTMouseDown
        end
        object btn_sp_lut_write: TButton
          Left = 492
          Top = 30
          Width = 70
          Height = 30
          Caption = 'Write'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 0
          OnClick = btn_sp_lut_writeClick
        end
        object btn_sp_lut_Set: TButton
          Left = 492
          Top = 128
          Width = 70
          Height = 31
          Caption = 'Clear'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
          OnClick = btn_sp_lut_SetClick
        end
        object btn_sp_lut_read: TBitBtn
          Left = 492
          Top = 79
          Width = 70
          Height = 31
          Caption = 'Read'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = btn_sp_lut_readClick
        end
      end
      object btn_GainSet: TButton
        Left = 492
        Top = 20
        Width = 80
        Height = 30
        Caption = 'Gain Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btn_GainSetClick
      end
    end
    object LUT_type: TRadioGroup
      Left = 10
      Top = 414
      Width = 237
      Height = 60
      Caption = 'Sharpness Mode'
      Columns = 3
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -15
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
      Left = 256
      Top = 414
      Width = 60
      Height = 30
      Caption = 'Load'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = btn_sp_LoadClick
    end
    object btn_sp_Save: TButton
      Left = 256
      Top = 443
      Width = 60
      Height = 31
      Hint = 'Save SP Table'
      Caption = 'Save'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = btn_sp_SaveClick
    end
    object Btn_SP_reload: TBitBtn
      Left = 847
      Top = 512
      Width = 90
      Height = 31
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
      Left = 10
      Top = 20
      Width = 316
      Height = 365
      Caption = 'Sharpness'
      TabOrder = 5
      object Label1: TLabel
        Left = 10
        Top = 59
        Width = 41
        Height = 16
        Caption = 'Label1'
      end
      object Label2: TLabel
        Left = 10
        Top = 89
        Width = 41
        Height = 16
        Caption = 'Label2'
      end
      object Label3: TLabel
        Left = 10
        Top = 118
        Width = 41
        Height = 16
        Caption = 'Label3'
      end
      object Label4: TLabel
        Left = 10
        Top = 148
        Width = 41
        Height = 16
        Caption = 'Label4'
      end
      object Label5: TLabel
        Left = 10
        Top = 207
        Width = 41
        Height = 16
        Caption = 'Label5'
      end
      object Label6: TLabel
        Left = 10
        Top = 236
        Width = 41
        Height = 16
        Caption = 'Label6'
      end
      object Label7: TLabel
        Left = 10
        Top = 276
        Width = 41
        Height = 16
        Caption = 'Label7'
      end
      object Label8: TLabel
        Left = 10
        Top = 305
        Width = 41
        Height = 16
        Caption = 'Label8'
      end
      object CheckBox1: TCheckBox
        Left = 98
        Top = 0
        Width = 120
        Height = 21
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object CheckBox2: TCheckBox
        Left = 10
        Top = 30
        Width = 119
        Height = 20
        Caption = 'CheckBox2'
        TabOrder = 1
      end
      object CheckBox3: TCheckBox
        Left = 158
        Top = 30
        Width = 119
        Height = 20
        Caption = 'CheckBox3'
        TabOrder = 2
      end
      object ScrollBar1: TScrollBar
        Left = 108
        Top = 59
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 3
      end
      object StaticText1: TStaticText
        Left = 266
        Top = 59
        Width = 70
        Height = 20
        Caption = 'StaticText1'
        TabOrder = 4
      end
      object ScrollBar2: TScrollBar
        Left = 108
        Top = 89
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 5
      end
      object ScrollBar3: TScrollBar
        Left = 108
        Top = 118
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 6
      end
      object ScrollBar4: TScrollBar
        Left = 108
        Top = 148
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 7
      end
      object StaticText2: TStaticText
        Left = 266
        Top = 89
        Width = 70
        Height = 20
        Caption = 'StaticText2'
        TabOrder = 8
      end
      object StaticText3: TStaticText
        Left = 266
        Top = 118
        Width = 70
        Height = 20
        Caption = 'StaticText3'
        TabOrder = 9
      end
      object StaticText4: TStaticText
        Left = 266
        Top = 148
        Width = 70
        Height = 20
        Caption = 'StaticText4'
        TabOrder = 10
      end
      object CheckBox4: TCheckBox
        Left = 10
        Top = 177
        Width = 119
        Height = 21
        Caption = 'CheckBox4'
        TabOrder = 11
      end
      object CheckBox5: TCheckBox
        Left = 158
        Top = 177
        Width = 119
        Height = 21
        Caption = 'CheckBox5'
        TabOrder = 12
      end
      object ScrollBar5: TScrollBar
        Left = 108
        Top = 207
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 13
      end
      object ScrollBar6: TScrollBar
        Left = 108
        Top = 236
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 14
      end
      object StaticText5: TStaticText
        Left = 266
        Top = 207
        Width = 70
        Height = 20
        Caption = 'StaticText5'
        TabOrder = 15
      end
      object StaticText6: TStaticText
        Left = 266
        Top = 236
        Width = 70
        Height = 20
        Caption = 'StaticText6'
        TabOrder = 16
      end
      object ComboBox1: TComboBox
        Left = 79
        Top = 266
        Width = 227
        Height = 24
        ItemHeight = 16
        TabOrder = 17
        Text = 'ComboBox1'
      end
      object ComboBox2: TComboBox
        Left = 79
        Top = 295
        Width = 227
        Height = 24
        ItemHeight = 16
        TabOrder = 18
        Text = 'ComboBox2'
      end
      object CheckBox6: TCheckBox
        Left = 10
        Top = 335
        Width = 119
        Height = 21
        Caption = 'CheckBox6'
        TabOrder = 19
      end
      object CheckBox7: TCheckBox
        Left = 158
        Top = 335
        Width = 119
        Height = 21
        Caption = 'CheckBox7'
        TabOrder = 20
      end
    end
    object Contrast: TGroupBox
      Left = 10
      Top = 502
      Width = 828
      Height = 336
      Caption = 'Contrast'
      TabOrder = 6
      object Label9: TLabel
        Left = 10
        Top = 98
        Width = 41
        Height = 24
        Caption = 'Label9'
      end
      object Label10: TLabel
        Left = 10
        Top = 128
        Width = 48
        Height = 16
        Caption = 'Label10'
      end
      object Label11: TLabel
        Left = 10
        Top = 158
        Width = 48
        Height = 16
        Caption = 'Label11'
      end
      object Label12: TLabel
        Left = 10
        Top = 187
        Width = 48
        Height = 16
        Caption = 'Label12'
      end
      object Label13: TLabel
        Left = 10
        Top = 217
        Width = 48
        Height = 16
        Caption = 'Label13'
      end
      object Label14: TLabel
        Left = 10
        Top = 246
        Width = 48
        Height = 16
        Caption = 'Label14'
      end
      object Label15: TLabel
        Left = 10
        Top = 276
        Width = 48
        Height = 16
        Caption = 'Label15'
      end
      object Label16: TLabel
        Left = 10
        Top = 305
        Width = 48
        Height = 16
        Caption = 'Label16'
      end
      object Label17: TLabel
        Left = 404
        Top = 89
        Width = 48
        Height = 16
        Caption = 'Label17'
      end
      object Label18: TLabel
        Left = 404
        Top = 118
        Width = 48
        Height = 16
        Caption = 'Label18'
      end
      object Label19: TLabel
        Left = 404
        Top = 158
        Width = 48
        Height = 16
        Caption = 'Label19'
      end
      object Label20: TLabel
        Left = 404
        Top = 187
        Width = 48
        Height = 16
        Caption = 'Label20'
      end
      object Label21: TLabel
        Left = 404
        Top = 217
        Width = 48
        Height = 16
        Caption = 'Label21'
      end
      object Label22: TLabel
        Left = 404
        Top = 246
        Width = 48
        Height = 16
        Caption = 'Label22'
      end
      object CheckBox8: TCheckBox
        Left = 89
        Top = 0
        Width = 119
        Height = 21
        Caption = 'CheckBox8'
        TabOrder = 0
      end
      object CheckBox9: TCheckBox
        Left = 10
        Top = 30
        Width = 119
        Height = 20
        Caption = 'CheckBox9'
        TabOrder = 1
      end
      object CheckBox10: TCheckBox
        Left = 148
        Top = 30
        Width = 119
        Height = 20
        Caption = 'CheckBox10'
        TabOrder = 2
      end
      object CheckBox11: TCheckBox
        Left = 10
        Top = 59
        Width = 119
        Height = 21
        Caption = 'CheckBox11'
        TabOrder = 3
      end
      object CheckBox12: TCheckBox
        Left = 148
        Top = 59
        Width = 119
        Height = 21
        Caption = 'CheckBox12'
        TabOrder = 4
      end
      object ComboBox3: TComboBox
        Left = 148
        Top = 89
        Width = 178
        Height = 24
        ItemHeight = 16
        TabOrder = 5
        Text = 'ComboBox3'
      end
      object ComboBox4: TComboBox
        Left = 148
        Top = 118
        Width = 178
        Height = 24
        ItemHeight = 16
        TabOrder = 6
        Text = 'ComboBox4'
      end
      object ScrollBar7: TScrollBar
        Left = 138
        Top = 158
        Width = 149
        Height = 20
        PageSize = 0
        TabOrder = 7
      end
      object ScrollBar8: TScrollBar
        Left = 138
        Top = 187
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 8
      end
      object ScrollBar9: TScrollBar
        Left = 138
        Top = 217
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 9
      end
      object ScrollBar10: TScrollBar
        Left = 138
        Top = 246
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 10
      end
      object ScrollBar11: TScrollBar
        Left = 138
        Top = 276
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 11
      end
      object ScrollBar12: TScrollBar
        Left = 138
        Top = 305
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 12
      end
      object StaticText7: TStaticText
        Left = 295
        Top = 158
        Width = 70
        Height = 20
        Caption = 'StaticText7'
        TabOrder = 13
      end
      object StaticText8: TStaticText
        Left = 295
        Top = 187
        Width = 70
        Height = 20
        Caption = 'StaticText8'
        TabOrder = 14
      end
      object StaticText9: TStaticText
        Left = 295
        Top = 217
        Width = 70
        Height = 20
        Caption = 'StaticText9'
        TabOrder = 15
      end
      object StaticText10: TStaticText
        Left = 295
        Top = 246
        Width = 77
        Height = 20
        Caption = 'StaticText10'
        TabOrder = 16
      end
      object StaticText11: TStaticText
        Left = 295
        Top = 276
        Width = 77
        Height = 20
        Caption = 'StaticText11'
        TabOrder = 17
      end
      object StaticText12: TStaticText
        Left = 295
        Top = 305
        Width = 77
        Height = 20
        Caption = 'StaticText12'
        TabOrder = 18
      end
      object LabeledEdit1: TLabeledEdit
        Left = 404
        Top = 39
        Width = 149
        Height = 24
        EditLabel.Width = 80
        EditLabel.Height = 16
        EditLabel.Caption = 'LabeledEdit1'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 19
      end
      object ComboBox5: TComboBox
        Left = 522
        Top = 79
        Width = 178
        Height = 24
        ItemHeight = 16
        TabOrder = 20
        Text = 'ComboBox5'
      end
      object ComboBox6: TComboBox
        Left = 522
        Top = 108
        Width = 178
        Height = 24
        ItemHeight = 16
        TabOrder = 21
        Text = 'ComboBox6'
      end
      object ScrollBar13: TScrollBar
        Left = 522
        Top = 158
        Width = 149
        Height = 20
        PageSize = 0
        TabOrder = 22
      end
      object ScrollBar14: TScrollBar
        Left = 522
        Top = 187
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 23
      end
      object ScrollBar15: TScrollBar
        Left = 522
        Top = 217
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 24
      end
      object ScrollBar16: TScrollBar
        Left = 522
        Top = 246
        Width = 149
        Height = 21
        PageSize = 0
        TabOrder = 25
      end
      object StaticText13: TStaticText
        Left = 679
        Top = 158
        Width = 77
        Height = 20
        Caption = 'StaticText13'
        TabOrder = 26
      end
      object StaticText14: TStaticText
        Left = 679
        Top = 187
        Width = 77
        Height = 20
        Caption = 'StaticText14'
        TabOrder = 27
      end
      object StaticText15: TStaticText
        Left = 679
        Top = 217
        Width = 77
        Height = 20
        Caption = 'StaticText15'
        TabOrder = 28
      end
      object StaticText16: TStaticText
        Left = 679
        Top = 246
        Width = 77
        Height = 20
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
