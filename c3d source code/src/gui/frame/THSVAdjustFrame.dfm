object HSVAdjustFrame: THSVAdjustFrame
  Left = 0
  Top = 0
  Width = 395
  Height = 201
  TabOrder = 0
  object GroupBox40: TGroupBox
    Left = 0
    Top = -8
    Width = 395
    Height = 80
    TabOrder = 0
    object lb_c3d_Manual39_h: TLabel
      Left = 335
      Top = 39
      Width = 11
      Height = 16
      Caption = '0'#176
    end
    object Label197: TLabel
      Left = 10
      Top = 30
      Width = 25
      Height = 16
      Caption = 'Hue'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object sb_c3d_Manual39_h: TScrollBar
      Left = 69
      Top = 47
      Width = 247
      Height = 21
      Max = 120
      PageSize = 0
      Position = 60
      TabOrder = 0
      OnChange = sb_c3d_Manual39_hChange
    end
    object Edit_c3d_Manual39_h_adj: TEdit
      Left = 89
      Top = 10
      Width = 50
      Height = 24
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
  end
  object GroupBox41: TGroupBox
    Left = 0
    Top = 61
    Width = 395
    Height = 76
    TabOrder = 1
    object lb_c3d_Manual39_s: TLabel
      Left = 335
      Top = 39
      Width = 7
      Height = 16
      Caption = '0'
    end
    object Label207: TLabel
      Left = 10
      Top = 30
      Width = 56
      Height = 16
      Caption = 'Satuation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object sb_c3d_Manual39_s: TScrollBar
      Left = 69
      Top = 47
      Width = 247
      Height = 21
      Max = 200
      PageSize = 0
      Position = 100
      TabOrder = 0
      OnChange = sb_c3d_Manual39_sChange
    end
    object edt_c3d_satC: TEdit
      Left = 6
      Top = 7
      Width = 30
      Height = 24
      Hint = 'constant'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Text = '1.5'
      Visible = False
    end
    object Edit_c3d_Manual39_s_adj: TEdit
      Left = 89
      Top = 10
      Width = 50
      Height = 24
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
  end
  object GroupBox7: TGroupBox
    Left = 0
    Top = 128
    Width = 393
    Height = 73
    TabOrder = 2
    object lb_c3d_Manual39_v: TLabel
      Left = 335
      Top = 41
      Width = 7
      Height = 16
      Caption = '0'
    end
    object Label25: TLabel
      Left = 5
      Top = 33
      Width = 63
      Height = 16
      Caption = 'Brightness'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object sb_c3d_Manual39_v: TScrollBar
      Left = 69
      Top = 52
      Width = 247
      Height = 21
      Max = 200
      PageSize = 0
      Position = 100
      TabOrder = 0
      OnChange = sb_c3d_Manual39_vChange
    end
    object Edit_c3d_Manual39_v_adj: TEdit
      Left = 89
      Top = 9
      Width = 50
      Height = 24
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object edt_c3d_valC: TEdit
      Left = 10
      Top = 9
      Width = 31
      Height = 24
      Hint = 'constant'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      Text = '2'
      Visible = False
    end
  end
end
