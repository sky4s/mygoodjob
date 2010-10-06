object SharpnessForm1: TSharpnessForm1
  Left = 288
  Top = 161
  Width = 654
  Height = 644
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
    Width = 779
    Height = 750
    TabOrder = 0
    object CheckBox1: TCheckBox
      Left = 20
      Top = 20
      Width = 129
      Height = 30
      Caption = 'CheckBox1'
      TabOrder = 0
    end
    object CheckBox2: TCheckBox
      Left = 20
      Top = 59
      Width = 129
      Height = 21
      Caption = 'CheckBox2'
      TabOrder = 1
    end
    object CheckBox4: TCheckBox
      Left = 158
      Top = 20
      Width = 139
      Height = 30
      Caption = 'CheckBox4'
      TabOrder = 2
    end
    object CheckBox5: TCheckBox
      Left = 158
      Top = 59
      Width = 148
      Height = 21
      Caption = 'CheckBox5'
      TabOrder = 3
    end
    object GroupBox1: TGroupBox
      Left = 325
      Top = 69
      Width = 444
      Height = 109
      Caption = 'Text Detection'
      TabOrder = 4
      object Label1: TLabel
        Left = 10
        Top = 30
        Width = 41
        Height = 16
        Caption = 'Label1'
      end
      object Label2: TLabel
        Left = 10
        Top = 69
        Width = 41
        Height = 16
        Caption = 'Label2'
      end
      object ScrollBar1: TScrollBar
        Left = 177
        Top = 30
        Width = 228
        Height = 20
        PageSize = 0
        TabOrder = 0
      end
      object ScrollBar2: TScrollBar
        Left = 177
        Top = 69
        Width = 228
        Height = 21
        PageSize = 0
        TabOrder = 1
      end
      object StaticText1: TStaticText
        Left = 414
        Top = 30
        Width = 70
        Height = 20
        BorderStyle = sbsSunken
        Caption = 'StaticText1'
        TabOrder = 2
      end
      object StaticText2: TStaticText
        Left = 414
        Top = 69
        Width = 70
        Height = 20
        BorderStyle = sbsSunken
        Caption = 'StaticText2'
        TabOrder = 3
      end
      object CheckBox3: TCheckBox
        Left = 138
        Top = -4
        Width = 90
        Height = 31
        Caption = 'CheckBox3'
        TabOrder = 4
      end
    end
    object GroupBox2: TGroupBox
      Left = 10
      Top = 177
      Width = 759
      Height = 523
      Caption = 'Weighting'
      TabOrder = 5
      object Label3: TLabel
        Left = 30
        Top = 30
        Width = 41
        Height = 16
        Caption = 'Label3'
      end
      object Label4: TLabel
        Left = 30
        Top = 59
        Width = 41
        Height = 16
        Caption = 'Label4'
      end
      object Label5: TLabel
        Left = 30
        Top = 89
        Width = 83
        Height = 16
        Caption = 'Software Gain'
      end
      object ScrollBar3: TScrollBar
        Left = 217
        Top = 30
        Width = 336
        Height = 20
        PageSize = 0
        TabOrder = 0
      end
      object ScrollBar4: TScrollBar
        Left = 217
        Top = 59
        Width = 336
        Height = 21
        PageSize = 0
        TabOrder = 1
      end
      object sb_softgain: TScrollBar
        Left = 217
        Top = 89
        Width = 336
        Height = 21
        Max = 150
        PageSize = 0
        Position = 10
        TabOrder = 2
        OnChange = sb_softgainChange
      end
      object StaticText3: TStaticText
        Left = 571
        Top = 30
        Width = 70
        Height = 20
        BorderStyle = sbsSunken
        Caption = 'StaticText3'
        TabOrder = 3
      end
      object StaticText4: TStaticText
        Left = 571
        Top = 59
        Width = 70
        Height = 20
        BorderStyle = sbsSunken
        Caption = 'StaticText4'
        TabOrder = 4
      end
      object st_softgain: TStaticText
        Left = 571
        Top = 89
        Width = 11
        Height = 20
        BorderStyle = sbsSunken
        Caption = '1'
        TabOrder = 5
      end
      object GroupBox47: TGroupBox
        Left = 20
        Top = 118
        Width = 582
        Height = 395
        TabOrder = 6
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
        Left = 610
        Top = 89
        Width = 80
        Height = 30
        Caption = 'Gain Set'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        OnClick = btn_GainSetClick
      end
    end
    object LUT_type: TRadioGroup
      Left = 10
      Top = 108
      Width = 237
      Height = 61
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
      TabOrder = 6
      OnClick = LUT_typeClick
    end
    object btn_sp_Load: TButton
      Left = 256
      Top = 98
      Width = 60
      Height = 31
      Caption = 'Load'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      OnClick = btn_sp_LoadClick
    end
    object btn_sp_Save: TButton
      Left = 256
      Top = 138
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
      TabOrder = 8
      OnClick = btn_sp_SaveClick
    end
    object Btn_SP_reload: TBitBtn
      Left = 30
      Top = 709
      Width = 89
      Height = 31
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
      Left = 315
      Top = 30
      Width = 119
      Height = 20
      Caption = 'CheckBox6'
      TabOrder = 10
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 576
  end
  object SaveDialog1: TSaveDialog
    Left = 544
  end
end
