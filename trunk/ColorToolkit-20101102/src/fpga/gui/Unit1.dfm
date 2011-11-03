object MainForm: TMainForm
  Left = 344
  Top = 160
  Width = 749
  Height = 588
  Caption = 'Toolkit'
  Color = clBtnFace
  ParentFont = True
  FormStyle = fsMDIForm
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnMouseDown = FormMouseDown
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 523
    Width = 741
    Height = 17
    Color = clYellow
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -12
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
    Left = 640
    Top = 520
    Width = 97
    Height = 17
    Caption = 'Address from txt file'
    TabOrder = 1
    Visible = False
    OnClick = cb_address_txtClick
  end
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    object Device1: TMenuItem
      Caption = '&Device'
      ImageIndex = 0
      object AUO_11307: TMenuItem
        Caption = '&1.11307'
        Visible = False
        OnClick = AUO_11307Click
      end
      object AUO_12303: TMenuItem
        Caption = '&2.12303'
        Visible = False
        OnClick = AUO_12303Click
      end
      object addressFromFile: TMenuItem
        Caption = 'Load T-CON Address File'
        OnClick = addressFromFileClick
      end
      object Header2Address1: TMenuItem
        Caption = 'Header to Address File'
        Visible = False
        OnClick = Header2Address1Click
      end
    end
    object mn_TCON: TMenuItem
      Caption = '&TCON'
      ImageIndex = 1
      Visible = False
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
      Visible = False
      OnClick = mn_DCRClick
    end
    object mn_Vender: TMenuItem
      Caption = '&Vender'
      ImageIndex = 4
      Visible = False
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
      object mn_Sharpness12307: TMenuItem
        Caption = '&Sharpness_12307'
        OnClick = mn_Sharpness12307Click
      end
      object mn_CE: TMenuItem
        Caption = '&Contrast Enhancement'
        OnClick = mn_CEClick
      end
      object HSV1: TMenuItem
        Caption = 'HSV'
        OnClick = HSV1Click
      end
      object mn_HSV: TMenuItem
        Caption = '&Hue/Saturation/Value'
        Visible = False
        OnClick = mn_HSVClick
      end
      object mn_HSV2: TMenuItem
        Caption = '&Hue/Saturation/Value2'
        OnClick = mn_HSV2Click
      end
      object mn_C3D: TMenuItem
        Caption = 'C3D'
        Visible = False
        OnClick = mn_C3DClick
      end
      object mn_C3D_777: TMenuItem
        Caption = 'C3D 777'
        OnClick = mn_C3D_777Click
      end
      object mn_C3D_999: TMenuItem
        Caption = 'C3D 999'
        OnClick = mn_C3D_999Click
      end
      object mn_SAT: TMenuItem
        Caption = 'SAT'
        OnClick = mn_SATClick
      end
      object mn_offset: TMenuItem
        Caption = 'OFFSET'
        OnClick = mn_offsetClick
      end
    end
    object mn_Engineer: TMenuItem
      Caption = '&Engineer'
      ImageIndex = 6
      OnClick = mn_EngineerClick
    end
  end
  object PopupMenu1: TPopupMenu
    OwnerDraw = True
    Left = 32
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
      end
      object C3D1: TMenuItem
        Caption = 'C3D'
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 64
  end
  object SaveDialog1: TSaveDialog
    Left = 96
  end
end
