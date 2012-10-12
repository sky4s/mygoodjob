object OffsetForm: TOffsetForm
  Left = 383
  Top = 229
  Width = 696
  Height = 480
  Caption = 'OFFSET'
  Color = clBtnFace
  DefaultMonitor = dmDesktop
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
  object Label1: TLabel
    Left = 40
    Top = 72
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object btn_reload: TBitBtn
    Left = 8
    Top = 412
    Width = 73
    Height = 25
    Caption = '&Reload'
    ModalResult = 6
    TabOrder = 0
    OnClick = btn_reloadClick
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
  object CheckBox1: TCheckBox
    Left = 40
    Top = 32
    Width = 97
    Height = 17
    Caption = 'CheckBox1'
    TabOrder = 1
  end
  object CheckBox2: TCheckBox
    Left = 152
    Top = 32
    Width = 97
    Height = 17
    Caption = 'CheckBox2'
    TabOrder = 2
  end
  object CheckBox3: TCheckBox
    Left = 272
    Top = 32
    Width = 97
    Height = 17
    Caption = 'CheckBox3'
    TabOrder = 3
  end
  object ScrollBar1: TScrollBar
    Left = 136
    Top = 72
    Width = 121
    Height = 17
    PageSize = 0
    TabOrder = 4
  end
  object StaticText1: TStaticText
    Left = 264
    Top = 72
    Width = 58
    Height = 17
    Caption = 'StaticText1'
    TabOrder = 5
  end
end
