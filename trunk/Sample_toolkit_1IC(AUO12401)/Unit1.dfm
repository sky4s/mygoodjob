object MainForm: TMainForm
  Left = 464
  Top = 143
  Width = 749
  Height = 588
  Caption = 'Toolkit'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnMouseDown = FormMouseDown
  PixelsPerInch = 120
  TextHeight = 16
  object StatusBar1: TStatusBar
    Left = 0
    Top = 512
    Width = 741
    Height = 21
    Color = clYellow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -15
    Font.Name = #26032#32048#26126#39636
    Font.Style = [fsBold]
    Panels = <
      item
        Text = 'Connection: Fail!'
        Width = 120
      end
      item
        Text = 'Device address:'
        Width = 50
      end>
    SimplePanel = False
    UseSystemFont = False
    OnDblClick = StatusBar1DblClick
  end
  object cb_address_txt: TCheckBox
    Left = 788
    Top = 640
    Width = 119
    Height = 21
    Caption = 'Address from txt file'
    TabOrder = 1
    Visible = False
    OnClick = cb_address_txtClick
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 72
    object Device1: TMenuItem
      Caption = '&Device'
      ImageIndex = 0
      object AUO_12401: TMenuItem
        Caption = '&1.12401'
        OnClick = AUO_12401Click
      end
      object AUO_12303: TMenuItem
        Caption = '&2.12303'
        Visible = False
        OnClick = AUO_12303Click
      end
    end
    object mn_TCON: TMenuItem
      Caption = '&TCON'
      ImageIndex = 1
      OnClick = mn_TCONClick
    end
    object mn_Function: TMenuItem
      Caption = '&Function'
      ImageIndex = 2
      OnClick = mn_FunctionClick
    end
    object mn_DCR: TMenuItem
      Caption = 'D&CR'
      ImageIndex = 3
      OnClick = mn_DCRClick
    end
    object mn_Vender: TMenuItem
      Caption = '&Vender'
      ImageIndex = 4
      OnClick = mn_VenderClick
    end
    object mn_ImageProc: TMenuItem
      Caption = 'Image Process'
      ImageIndex = 5
      object mn_CM: TMenuItem
        Caption = '&Color Matrix'
        OnClick = mn_CMClick
      end
      object mn_Sharpness: TMenuItem
        Caption = '&Sharpness'
        OnClick = mn_SharpnessClick
      end
      object mn_CE: TMenuItem
        Caption = '&Contrast Enhancement'
        OnClick = mn_CEClick
      end
      object mn_HSV: TMenuItem
        Caption = '&Hue/Saturation/Value'
        OnClick = mn_HSVClick
      end
    end
    object mn_Engineer: TMenuItem
      Caption = '&Engineer'
      ImageIndex = 6
      OnClick = mn_EngineerClick
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 88
    Top = 64
    object popupmenu2: TMenuItem
      Caption = 'TCON'
      ImageIndex = 0
    end
    object Function1: TMenuItem
      Caption = 'Function'
      ImageIndex = 1
    end
    object DCR1: TMenuItem
      Caption = 'DCR'
      ImageIndex = 2
    end
    object Vender1: TMenuItem
      Caption = 'Vender'
      ImageIndex = 3
    end
    object ImageProcess1: TMenuItem
      Caption = 'Image Process'
      ImageIndex = 4
      object ColorMatrix1: TMenuItem
        Caption = 'Color Matrix'
      end
      object Sharpness1: TMenuItem
        Caption = 'Sharpness'
      end
      object ContrastEnhancement1: TMenuItem
        Caption = 'Contrast Enhancement'
        Visible = False
      end
    end
  end
end
