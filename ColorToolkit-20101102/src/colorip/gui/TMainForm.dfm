object MainForm: TMainForm
  Left = 198
  Top = 0
  Width = 826
  Height = 692
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
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 629
    Width = 818
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
  object MainMenu1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    object Device1: TMenuItem
      Caption = '&Device'
      ImageIndex = 0
      object mn_LoadAddressFromFile: TMenuItem
        Caption = 'Load T-CON Address File'
        OnClick = mn_LoadAddressFromFileClick
      end
      object mn_Header2Address: TMenuItem
        Caption = 'Header to Address File'
        Visible = False
        OnClick = mn_Header2AddressClick
      end
    end
    object mn_Function: TMenuItem
      Caption = '&Function'
      ImageIndex = 2
      OnClick = mn_FunctionClick
    end
    object mn_ImageProc: TMenuItem
      Caption = 'Image Process'
      ImageIndex = 5
      object mn_CM: TMenuItem
        Caption = '&Color Matrix'
        OnClick = mn_CMClick
      end
      object mn_Sharpness: TMenuItem
        Caption = '&Sharpness v1'
        OnClick = mn_SharpnessClick
      end
      object mn_Sharpness12307: TMenuItem
        Caption = 'Sharpness v2'
        OnClick = mn_Sharpness12307Click
      end
      object mn_Sharpness_v2_1: TMenuItem
        Caption = 'Sharpness v2.1'
        OnClick = mn_Sharpness_v2_1Click
      end
      object mn_CE: TMenuItem
        Caption = '&Contrast Enhancement'
        OnClick = mn_CEClick
      end
      object mn_HSV1: TMenuItem
        Caption = 'HSV v1'
        OnClick = mn_HSV1Click
      end
      object mn_HSV2: TMenuItem
        Caption = 'HSV v2'
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
    object mn_Test: TMenuItem
      Caption = 'Test'
      object mn_Example2: TMenuItem
        Caption = 'Example'
        OnClick = mn_Example2Click
      end
      object mn_Debug: TMenuItem
        Caption = 'Debug'
        OnClick = mn_DebugClick
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
