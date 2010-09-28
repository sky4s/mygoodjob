object C3D_SimualteForm: TC3D_SimualteForm
  Left = 201
  Top = 52
  Width = 458
  Height = 428
  Caption = 'C3D_SimualteForm '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  WindowState = wsMinimized
  PixelsPerInch = 120
  TextHeight = 16
  object GroupBox2: TGroupBox
    Left = 98
    Top = 79
    Width = 445
    Height = 287
    Caption = 'GroupBox2'
    TabOrder = 0
    Visible = False
    object Img_diff: TImage
      Left = 187
      Top = 231
      Width = 533
      Height = 371
      Visible = False
    end
    object lb_hsv_dis_max: TLabel
      Left = 620
      Top = 606
      Width = 96
      Height = 16
      Caption = 'lb_hsv_dis_max'
    end
    object cb_record_u_want: TCheckBox
      Left = 10
      Top = 20
      Width = 149
      Height = 21
      Caption = 'cb_record_u_want'
      TabOrder = 0
      Visible = False
      OnClick = cb_record_u_wantClick
    end
    object PageControl1: TPageControl
      Left = 10
      Top = 48
      Width = 562
      Height = 405
      ActivePage = TabSheet1
      TabIndex = 0
      TabOrder = 1
      Visible = False
      object TabSheet1: TTabSheet
        Caption = 'R_diff'
        object Image2: TImage
          Left = 7
          Top = 0
          Width = 546
          Height = 370
          OnMouseMove = Image1MouseMove
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'G_diff'
        ImageIndex = 1
        object Image3: TImage
          Left = 7
          Top = 0
          Width = 546
          Height = 370
          OnMouseMove = Image1MouseMove
        end
      end
      object TabSheet3: TTabSheet
        Caption = 'B_diff'
        ImageIndex = 2
        object Image4: TImage
          Left = 7
          Top = 0
          Width = 546
          Height = 370
          OnMouseMove = Image1MouseMove
        end
      end
    end
    object pc_hsv_dif: TPageControl
      Left = 20
      Top = 98
      Width = 631
      Height = 405
      ActivePage = ts_h_diff
      TabIndex = 0
      TabOrder = 2
      Visible = False
      object ts_h_diff: TTabSheet
        Caption = 'H_diff'
        object Image_h: TImage
          Left = 7
          Top = 0
          Width = 546
          Height = 370
          OnMouseMove = Image1MouseMove
        end
        object btn_saveHSV: TBitBtn
          Left = 559
          Top = 340
          Width = 63
          Height = 30
          Caption = 'save'
          TabOrder = 0
          OnClick = btn_saveHSVClick
        end
      end
      object ts_S_diff: TTabSheet
        Caption = 'S_diff'
        ImageIndex = 1
        object Image_s: TImage
          Left = 7
          Top = 0
          Width = 533
          Height = 370
        end
      end
      object ts_V_diff: TTabSheet
        Caption = 'V_diff'
        ImageIndex = 2
        object Image_v: TImage
          Left = 7
          Top = 0
          Width = 533
          Height = 370
          OnMouseMove = Image1MouseMove
        end
      end
    end
    object btn_dif_save: TButton
      Left = 640
      Top = 571
      Width = 80
      Height = 31
      Caption = 'Save Image'
      TabOrder = 3
      OnClick = btn_dif_saveClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 553
    Height = 474
    Caption = 'Panel1'
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 543
      Height = 41
      Caption = 'HSV Adjust Set'
      TabOrder = 0
      Visible = False
      object Label1: TLabel
        Left = 20
        Top = 20
        Width = 13
        Height = 16
        Caption = 'H:'
      end
      object lb_hsv_adj_h: TLabel
        Left = 39
        Top = 20
        Width = 7
        Height = 16
        Caption = '0'
      end
      object Label2: TLabel
        Left = 108
        Top = 20
        Width = 12
        Height = 16
        Caption = 'S:'
      end
      object lb_hsv_adj_s: TLabel
        Left = 128
        Top = 20
        Width = 7
        Height = 16
        Caption = '0'
      end
      object Label3: TLabel
        Left = 187
        Top = 20
        Width = 12
        Height = 16
        Caption = 'V:'
      end
      object lb_hsv_adj_v: TLabel
        Left = 207
        Top = 20
        Width = 7
        Height = 16
        Caption = '0'
      end
      object Label4: TLabel
        Left = 325
        Top = 10
        Width = 41
        Height = 16
        Caption = 'Label4'
        Visible = False
      end
    end
    object GroupBox9: TGroupBox
      Left = 295
      Top = 433
      Width = 248
      Height = 31
      Enabled = False
      TabOrder = 1
      object lb_c3d_showS: TLabel
        Left = 69
        Top = 12
        Width = 18
        Height = 16
        Caption = 'S:  '
      end
      object lb_c3d_showH: TLabel
        Left = 10
        Top = 12
        Width = 19
        Height = 16
        Caption = 'H:  '
      end
      object lb_c3d_showI: TLabel
        Left = 187
        Top = 12
        Width = 12
        Height = 16
        Caption = 'I:  '
        Visible = False
      end
      object lb_c3d_showV: TLabel
        Left = 128
        Top = 12
        Width = 18
        Height = 16
        Caption = 'V:  '
      end
    end
    object GroupBox4: TGroupBox
      Left = 118
      Top = 433
      Width = 179
      Height = 31
      Enabled = False
      TabOrder = 2
      object lb_c3d_showG: TLabel
        Left = 69
        Top = 12
        Width = 22
        Height = 16
        Caption = 'G:   '
      end
      object lb_c3d_showB: TLabel
        Left = 128
        Top = 12
        Width = 21
        Height = 16
        Caption = 'B:   '
      end
      object lb_c3d_showR: TLabel
        Left = 12
        Top = 12
        Width = 22
        Height = 16
        Caption = 'R:   '
      end
    end
    object GroupBox46: TGroupBox
      Left = 0
      Top = 433
      Width = 119
      Height = 31
      Enabled = False
      TabOrder = 3
      object lb_c3d_showY: TLabel
        Left = 69
        Top = 12
        Width = 21
        Height = 16
        Caption = 'Y:   '
      end
      object lb_c3d_showX: TLabel
        Left = 12
        Top = 12
        Width = 20
        Height = 16
        Caption = 'X:   '
      end
    end
    object btn_img_save: TButton
      Left = 453
      Top = 404
      Width = 90
      Height = 30
      Caption = 'Save Image'
      TabOrder = 4
      OnClick = btn_img_saveClick
    end
    object ScrollBox1: TScrollBox
      Left = 0
      Top = 30
      Width = 543
      Height = 375
      TabOrder = 5
      object Image1: TImage
        Left = 4
        Top = -1
        Width = 533
        Height = 370
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
