object SharpnessV1Form: TSharpnessV1Form
  Left = 241
  Top = 146
  Width = 654
  Height = 716
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
    Width = 633
    Height = 617
    TabOrder = 0
    object CheckBox1: TCheckBox
      Left = 16
      Top = 16
      Width = 105
      Height = 25
      Caption = 'CheckBox1'
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 16
      Top = 48
      Width = 105
      Height = 17
      Caption = 'CheckBox2'
      TabOrder = 1
    end
    object CheckBox4: TCheckBox
      Left = 128
      Top = 16
      Width = 113
      Height = 25
      Caption = 'CheckBox4'
      TabOrder = 2
    end
    object CheckBox5: TCheckBox
      Left = 128
      Top = 48
      Width = 121
      Height = 17
      Caption = 'CheckBox5'
      TabOrder = 3
    end
    object GroupBox1: TGroupBox
      Left = 264
      Top = 56
      Width = 361
      Height = 89
      Caption = 'Text Detection'
      TabOrder = 4
      object Label1: TLabel
        Left = 8
        Top = 24
        Width = 32
        Height = 13
        Caption = 'Label1'
      end
      object Label2: TLabel
        Left = 8
        Top = 56
        Width = 32
        Height = 13
        Caption = 'Label2'
      end
      object ScrollBar1: TScrollBar
        Left = 144
        Top = 24
        Width = 185
        Height = 17
        PageSize = 0
        TabOrder = 0
      end
      object ScrollBar2: TScrollBar
        Left = 144
        Top = 56
        Width = 185
        Height = 17
        PageSize = 0
        TabOrder = 1
      end
      object StaticText1: TStaticText
        Left = 336
        Top = 24
        Width = 58
        Height = 17
        BorderStyle = sbsSunken
        Caption = 'StaticText1'
        TabOrder = 2
      end
      object StaticText2: TStaticText
        Left = 336
        Top = 56
        Width = 58
        Height = 17
        BorderStyle = sbsSunken
        Caption = 'StaticText2'
        TabOrder = 3
      end
      object CheckBox3: TCheckBox
        Left = 112
        Top = -3
        Width = 73
        Height = 25
        Caption = 'CheckBox3'
        TabOrder = 4
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 152
      Width = 617
      Height = 425
      Caption = 'Weighting'
      TabOrder = 5
      object Label3: TLabel
        Left = 24
        Top = 24
        Width = 32
        Height = 13
        Caption = 'Label3'
      end
      object Label4: TLabel
        Left = 24
        Top = 48
        Width = 32
        Height = 13
        Caption = 'Label4'
      end
      object Label5: TLabel
        Left = 24
        Top = 72
        Width = 67
        Height = 13
        Caption = 'Software Gain'
      end
      object ScrollBar3: TScrollBar
        Left = 176
        Top = 24
        Width = 273
        Height = 17
        PageSize = 0
        TabOrder = 0
      end
      object ScrollBar4: TScrollBar
        Left = 176
        Top = 48
        Width = 273
        Height = 17
        PageSize = 0
        TabOrder = 1
      end
      object sb_softgain: TScrollBar
        Left = 176
        Top = 72
        Width = 273
        Height = 17
        Max = 150
        PageSize = 0
        Position = 10
        TabOrder = 2
        OnChange = sb_softgainChange
      end
      object StaticText3: TStaticText
        Left = 464
        Top = 24
        Width = 58
        Height = 17
        BorderStyle = sbsSunken
        Caption = 'StaticText3'
        TabOrder = 3
      end
      object StaticText4: TStaticText
        Left = 464
        Top = 48
        Width = 58
        Height = 17
        BorderStyle = sbsSunken
        Caption = 'StaticText4'
        TabOrder = 4
      end
      object st_softgain: TStaticText
        Left = 464
        Top = 72
        Width = 10
        Height = 17
        BorderStyle = sbsSunken
        Caption = '1'
        TabOrder = 5
      end
      object GroupBox47: TGroupBox
        Left = 16
        Top = 96
        Width = 473
        Height = 321
        TabOrder = 6
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
        Left = 496
        Top = 72
        Width = 65
        Height = 25
        Caption = 'Gain Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        OnClick = btn_GainSetClick
      end
    end
    object LUT_type: TRadioGroup
      Left = 8
      Top = 72
      Width = 121
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
      TabOrder = 6
      OnClick = LUT_typeClick
    end
    object btn_sp_Load: TButton
      Left = 136
      Top = 88
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
      TabOrder = 7
      OnClick = btn_sp_LoadClick
    end
    object btn_sp_Save: TButton
      Left = 136
      Top = 112
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
      TabOrder = 8
      OnClick = btn_sp_SaveClick
    end
    object Btn_SP_reload: TBitBtn
      Left = 8
      Top = 584
      Width = 73
      Height = 25
      Caption = '&Reload'
      ModalResult = 6
      TabOrder = 9
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
    object CheckBox6: TCheckBox
      Left = 256
      Top = 24
      Width = 97
      Height = 17
      Caption = 'CheckBox6'
      TabOrder = 10
    end
    object GroupBox4: TGroupBox
      Left = 192
      Top = 72
      Width = 65
      Height = 73
      Caption = 'Old Setting'
      TabOrder = 11
      object Button_LoadOldSetting: TButton
        Left = 8
        Top = 16
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
        TabOrder = 0
        OnClick = Button_LoadOldSettingClick
      end
      object Button_SaveOldSetting: TButton
        Left = 8
        Top = 40
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
        TabOrder = 1
        OnClick = Button_SaveOldSettingClick
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 576
  end
  object SaveDialog1: TSaveDialog
    Left = 544
  end
end
