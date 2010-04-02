object CA210SettingFrame: TCA210SettingFrame
  Left = 0
  Top = 0
  Width = 499
  Height = 154
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 497
    Height = 153
    Caption = 'CA210 Setting'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 68
      Height = 16
      Caption = 'Sync Mode'
    end
    object Label2: TLabel
      Left = 8
      Top = 56
      Width = 41
      Height = 16
      Caption = 'Speed'
    end
    object Label3: TLabel
      Left = 8
      Top = 88
      Width = 78
      Height = 16
      Caption = 'Cal Standard'
    end
    object Label4: TLabel
      Left = 256
      Top = 24
      Width = 16
      Height = 16
      Caption = 'Hz'
    end
    object Label5: TLabel
      Left = 8
      Top = 120
      Width = 84
      Height = 16
      Caption = 'Display Mode'
    end
    object ComboBox_SyncMode: TComboBox
      Left = 96
      Top = 24
      Width = 97
      Height = 24
      ItemHeight = 16
      TabOrder = 0
      Text = 'NTSC'
      OnChange = ComboBox_SyncModeChange
      Items.Strings = (
        'NTSC'
        'PAL'
        'EXT'
        'UNIV')
    end
    object ComboBox_Speed: TComboBox
      Left = 96
      Top = 56
      Width = 97
      Height = 24
      Enabled = False
      ItemHeight = 16
      ItemIndex = 0
      TabOrder = 1
      Text = 'AUTO'
      Items.Strings = (
        'AUTO')
    end
    object ComboBox_CalStandard: TComboBox
      Left = 96
      Top = 88
      Width = 97
      Height = 24
      ItemHeight = 16
      ItemIndex = 1
      TabOrder = 2
      Text = '9300K'
      OnChange = ComboBox_CalStandardChange
      Items.Strings = (
        '6500K'
        '9300K')
    end
    object Edit1_Hz: TEdit
      Left = 200
      Top = 24
      Width = 49
      Height = 24
      Enabled = False
      TabOrder = 3
      Text = '60'
    end
    object ComboBox_DisplayMode: TComboBox
      Left = 96
      Top = 120
      Width = 97
      Height = 24
      Enabled = False
      ItemHeight = 16
      ItemIndex = 0
      TabOrder = 4
      Text = 'Lvxy'
      Items.Strings = (
        'Lvxy')
    end
    object Button_Connect: TButton
      Left = 272
      Top = 120
      Width = 105
      Height = 25
      Caption = 'Connect'
      TabOrder = 5
      OnClick = Button_ConnectClick
    end
    object Button_Disconnect: TButton
      Left = 384
      Top = 120
      Width = 105
      Height = 25
      Caption = 'Disconnect'
      TabOrder = 6
      OnClick = Button_DisconnectClick
    end
  end
end
