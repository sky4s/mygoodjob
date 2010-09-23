object C3D_SimualteForm: TC3D_SimualteForm
  Left = 201
  Top = 52
  Width = 458
  Height = 428
  Caption = 'C3D_SimualteForm '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  WindowState = wsMinimized
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox2: TGroupBox
    Left = 80
    Top = 64
    Width = 361
    Height = 233
    Caption = 'GroupBox2'
    TabOrder = 0
    Visible = False
    object Img_diff: TImage
      Left = 152
      Top = 188
      Width = 433
      Height = 301
      Visible = False
    end
    object lb_hsv_dis_max: TLabel
      Left = 504
      Top = 492
      Width = 75
      Height = 13
      Caption = 'lb_hsv_dis_max'
    end
    object cb_record_u_want: TCheckBox
      Left = 8
      Top = 16
      Width = 121
      Height = 17
      Caption = 'cb_record_u_want'
      TabOrder = 0
      Visible = False
      OnClick = cb_record_u_wantClick
    end
    object PageControl1: TPageControl
      Left = 8
      Top = 39
      Width = 457
      Height = 329
      ActivePage = TabSheet1
      TabIndex = 0
      TabOrder = 1
      Visible = False
      object TabSheet1: TTabSheet
        Caption = 'R_diff'
        object Image2: TImage
          Left = 6
          Top = 0
          Width = 443
          Height = 301
          OnMouseMove = Image1MouseMove
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'G_diff'
        ImageIndex = 1
        object Image3: TImage
          Left = 6
          Top = 0
          Width = 443
          Height = 301
          OnMouseMove = Image1MouseMove
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'B_diff'
        ImageIndex = 2
        object Image4: TImage
          Left = 6
          Top = 0
          Width = 443
          Height = 301
          OnMouseMove = Image1MouseMove
        end
      end
    end
    object pc_hsv_dif: TPageControl
      Left = 16
      Top = 80
      Width = 513
      Height = 329
      ActivePage = ts_h_diff
      TabIndex = 0
      TabOrder = 2
      Visible = False
      object ts_h_diff: TTabSheet
        Caption = 'H_diff'
        object Image_h: TImage
          Left = 6
          Top = 0
          Width = 443
          Height = 301
          OnMouseMove = Image1MouseMove
        end
        object btn_saveHSV: TBitBtn
          Left = 454
          Top = 276
          Width = 51
          Height = 25
          Caption = 'save'
          TabOrder = 0
          OnClick = btn_saveHSVClick
        end
      end
      object ts_S_diff: TTabSheet
        Caption = 'S_diff'
        ImageIndex = 1
        object Image_s: TImage
          Left = 6
          Top = 0
          Width = 433
          Height = 301
        end
      end
      object ts_V_diff: TTabSheet
        Caption = 'V_diff'
        ImageIndex = 2
        object Image_v: TImage
          Left = 6
          Top = 0
          Width = 433
          Height = 301
          OnMouseMove = Image1MouseMove
        end
      end
    end
    object btn_dif_save: TButton
      Left = 520
      Top = 464
      Width = 65
      Height = 25
      Caption = 'Save Image'
      TabOrder = 3
      OnClick = btn_dif_saveClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 449
    Height = 385
    Caption = 'Panel1'
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 441
      Height = 33
      Caption = 'HSV Adjust Set'
      TabOrder = 0
      Visible = False
      object Label1: TLabel
        Left = 16
        Top = 16
        Width = 11
        Height = 13
        Caption = 'H:'
      end
      object lb_hsv_adj_h: TLabel
        Left = 32
        Top = 16
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label2: TLabel
        Left = 88
        Top = 16
        Width = 10
        Height = 13
        Caption = 'S:'
      end
      object lb_hsv_adj_s: TLabel
        Left = 104
        Top = 16
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label3: TLabel
        Left = 152
        Top = 16
        Width = 10
        Height = 13
        Caption = 'V:'
      end
      object lb_hsv_adj_v: TLabel
        Left = 168
        Top = 16
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label4: TLabel
        Left = 264
        Top = 8
        Width = 32
        Height = 13
        Caption = 'Label4'
        Visible = False
      end
    end
    object GroupBox9: TGroupBox
      Left = 240
      Top = 352
      Width = 201
      Height = 25
      Enabled = False
      TabOrder = 1
      object lb_c3d_showS: TLabel
        Left = 56
        Top = 10
        Width = 16
        Height = 13
        Caption = 'S:  '
      end
      object lb_c3d_showH: TLabel
        Left = 8
        Top = 10
        Width = 17
        Height = 13
        Caption = 'H:  '
      end
      object lb_c3d_showI: TLabel
        Left = 152
        Top = 10
        Width = 12
        Height = 13
        Caption = 'I:  '
        Visible = False
      end
      object lb_c3d_showV: TLabel
        Left = 104
        Top = 10
        Width = 16
        Height = 13
        Caption = 'V:  '
      end
    end
    object GroupBox4: TGroupBox
      Left = 96
      Top = 352
      Width = 145
      Height = 25
      Enabled = False
      TabOrder = 2
      object lb_c3d_showG: TLabel
        Left = 56
        Top = 10
        Width = 20
        Height = 13
        Caption = 'G:   '
      end
      object lb_c3d_showB: TLabel
        Left = 104
        Top = 10
        Width = 19
        Height = 13
        Caption = 'B:   '
      end
      object lb_c3d_showR: TLabel
        Left = 10
        Top = 10
        Width = 20
        Height = 13
        Caption = 'R:   '
      end
    end
    object GroupBox46: TGroupBox
      Left = 0
      Top = 352
      Width = 97
      Height = 25
      Enabled = False
      TabOrder = 3
      object lb_c3d_showY: TLabel
        Left = 56
        Top = 10
        Width = 19
        Height = 13
        Caption = 'Y:   '
      end
      object lb_c3d_showX: TLabel
        Left = 10
        Top = 10
        Width = 19
        Height = 13
        Caption = 'X:   '
      end
    end
    object btn_img_save: TButton
      Left = 368
      Top = 328
      Width = 73
      Height = 25
      Caption = 'Save Image'
      TabOrder = 4
      OnClick = btn_img_saveClick
    end
    object ScrollBox1: TScrollBox
      Left = 0
      Top = 24
      Width = 441
      Height = 305
      TabOrder = 5
      object Image1: TImage
        Left = 3
        Top = -1
        Width = 433
        Height = 301
        Hint = 'OnMouseDown_record_points2error_point.txt'
        OnDblClick = Image1DblClick
        OnMouseDown = Image1MouseDown
        OnMouseMove = Image1MouseMove
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 640
  end
  object OpenDialog1: TOpenDialog
    Left = 608
  end
  object SaveDialog_Img: TSaveDialog
    FileName = '.bmp'
    Filter = 'BMP|*.bmp|JPEG|*.jpg'
    OnTypeChange = SaveDialog_ImgTypeChange
    Left = 416
  end
end
