object HSVAdjustFrame: THSVAdjustFrame
  Left = 0
  Top = 0
  Width = 361
  Height = 163
  TabOrder = 0
  object GroupBox40: TGroupBox
    Left = 1
    Top = -6
    Width = 360
    Height = 63
    TabOrder = 0
    object lb_Hue_gain: TLabel
      Left = 319
      Top = 39
      Width = 10
      Height = 13
      Caption = '0'#176
    end
    object Label197: TLabel
      Left = 18
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
    object sb_Hue_gain: TScrollBar
      Left = 69
      Top = 32
      Width = 244
      Height = 21
      Max = 120
      PageSize = 0
      Position = 60
      TabOrder = 0
      OnChange = sb_Hue_gainChange
    end
    object Edit_c3d_Manual39_h_adj: TEdit
      Left = 177
      Top = 8
      Width = 50
      Height = 21
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object Button_HueReset: TButton
      Left = 232
      Top = 8
      Width = 49
      Height = 17
      Caption = 'Reset'
      TabOrder = 2
      OnClick = Button_HueResetClick
    end
    object Button_HueReturn: TButton
      Left = 288
      Top = 8
      Width = 49
      Height = 17
      Caption = 'Return'
      TabOrder = 3
      Visible = False
      OnClick = Button_HueReturnClick
    end
  end
  object GroupBox41: TGroupBox
    Left = 1
    Top = 47
    Width = 360
    Height = 58
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 1
    object lb_Sat_gain: TLabel
      Left = 319
      Top = 39
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label207: TLabel
      Left = 5
      Top = 30
      Width = 60
      Height = 16
      Caption = 'Saturation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object sb_Sat_gain: TScrollBar
      Left = 69
      Top = 32
      Width = 244
      Height = 21
      Max = 127
      PageSize = 0
      Position = 32
      TabOrder = 0
      OnChange = sb_Sat_gainChange
    end
    object edt_c3d_satC: TEdit
      Left = 6
      Top = 7
      Width = 30
      Height = 21
      Hint = 'constant'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      Text = '1.5'
      Visible = False
    end
    object Edit_c3d_Manual39_s_adj: TEdit
      Left = 177
      Top = 8
      Width = 50
      Height = 21
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object Button_SaturationReset: TButton
      Left = 232
      Top = 8
      Width = 49
      Height = 17
      Caption = 'Reset'
      TabOrder = 3
      OnClick = Button_SaturationResetClick
    end
    object Button_SaturationReturn: TButton
      Left = 288
      Top = 8
      Width = 49
      Height = 17
      Caption = 'Return'
      TabOrder = 4
      Visible = False
    end
  end
  object GroupBox7: TGroupBox
    Left = 1
    Top = 100
    Width = 360
    Height = 61
    TabOrder = 2
    object lb_Val_gain: TLabel
      Left = 319
      Top = 41
      Width = 6
      Height = 13
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
    object sb_Val_gain: TScrollBar
      Left = 69
      Top = 32
      Width = 244
      Height = 21
      Max = 63
      Min = -64
      PageSize = 0
      TabOrder = 0
      OnChange = sb_Val_gainChange
    end
    object Edit_c3d_Manual39_v_adj: TEdit
      Left = 177
      Top = 8
      Width = 50
      Height = 21
      ReadOnly = True
      TabOrder = 1
      Text = '0'
    end
    object edt_c3d_valC: TEdit
      Left = 10
      Top = 9
      Width = 31
      Height = 21
      Hint = 'constant'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      Text = '2'
      Visible = False
    end
    object Button_BrightnessReset: TButton
      Left = 232
      Top = 8
      Width = 49
      Height = 17
      Caption = 'Reset'
      TabOrder = 3
      OnClick = Button_BrightnessResetClick
    end
    object Button_BrightnessReturn: TButton
      Left = 288
      Top = 8
      Width = 49
      Height = 17
      Caption = 'Return'
      TabOrder = 4
      Visible = False
    end
  end
end
