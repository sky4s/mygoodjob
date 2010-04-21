object MatrixCalibrationForm: TMatrixCalibrationForm
  Left = 252
  Top = 252
  Width = 538
  Height = 482
  Caption = 'Matrix Calibration'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label13: TLabel
    Left = 134
    Top = 345
    Width = 281
    Height = 13
    Caption = 'Copyright (C) 2010, AU Optronics Corp., All Right Reserved.'
  end
  object GroupBox1: TGroupBox
    Left = 13
    Top = 143
    Width = 404
    Height = 144
    Caption = 'Matrix Calibration Setting'
    TabOrder = 0
    object Label1: TLabel
      Left = 7
      Top = 20
      Width = 34
      Height = 13
      Caption = 'Pattern'
    end
    object Label2: TLabel
      Left = 59
      Top = 39
      Width = 8
      Height = 13
      Caption = 'R'
    end
    object Label3: TLabel
      Left = 59
      Top = 65
      Width = 8
      Height = 13
      Caption = 'G'
    end
    object Label4: TLabel
      Left = 59
      Top = 91
      Width = 7
      Height = 13
      Caption = 'B'
    end
    object Label5: TLabel
      Left = 59
      Top = 117
      Width = 11
      Height = 13
      Caption = 'W'
    end
    object Label6: TLabel
      Left = 98
      Top = 20
      Width = 5
      Height = 13
      Caption = 'x'
    end
    object Label7: TLabel
      Left = 143
      Top = 20
      Width = 5
      Height = 13
      Caption = 'y'
    end
    object Label8: TLabel
      Left = 182
      Top = 20
      Width = 12
      Height = 13
      Caption = 'Lv'
    end
    object Label9: TLabel
      Left = 221
      Top = 39
      Width = 46
      Height = 13
      Caption = 'Matrix CH'
    end
    object Label10: TLabel
      Left = 221
      Top = 65
      Width = 11
      Height = 13
      Caption = 'ID'
    end
    object Edit_R: TEdit
      Left = 7
      Top = 39
      Width = 39
      Height = 24
      TabOrder = 0
      Text = '255'
    end
    object Edit_G: TEdit
      Left = 7
      Top = 65
      Width = 39
      Height = 24
      TabOrder = 1
      Text = '255'
    end
    object Edit_B: TEdit
      Left = 7
      Top = 91
      Width = 39
      Height = 24
      TabOrder = 2
      Text = '255'
    end
    object Edit_Rx: TEdit
      Left = 78
      Top = 39
      Width = 40
      Height = 24
      TabOrder = 3
      Text = '0'
    end
    object Edit_Gx: TEdit
      Left = 78
      Top = 65
      Width = 40
      Height = 24
      TabOrder = 4
      Text = '0'
    end
    object Edit_Wx: TEdit
      Left = 78
      Top = 117
      Width = 40
      Height = 24
      TabOrder = 5
      Text = '0'
    end
    object Edit_Bx: TEdit
      Left = 78
      Top = 91
      Width = 40
      Height = 24
      TabOrder = 6
      Text = '0'
    end
    object Edit_Ry: TEdit
      Left = 124
      Top = 39
      Width = 39
      Height = 24
      TabOrder = 7
      Text = '0'
    end
    object Edit_Gy: TEdit
      Left = 124
      Top = 65
      Width = 39
      Height = 24
      TabOrder = 8
      Text = '0'
    end
    object Edit_By: TEdit
      Left = 124
      Top = 91
      Width = 39
      Height = 24
      TabOrder = 9
      Text = '0'
    end
    object Edit_Wy: TEdit
      Left = 124
      Top = 117
      Width = 39
      Height = 24
      TabOrder = 10
      Text = '0'
    end
    object Edit_RLv: TEdit
      Left = 169
      Top = 39
      Width = 40
      Height = 24
      TabOrder = 11
      Text = '0'
    end
    object Edit_GLv: TEdit
      Left = 169
      Top = 65
      Width = 40
      Height = 24
      TabOrder = 12
      Text = '0'
    end
    object Edit_BLv: TEdit
      Left = 169
      Top = 91
      Width = 40
      Height = 24
      TabOrder = 13
      Text = '0'
    end
    object Edit_WLv: TEdit
      Left = 169
      Top = 117
      Width = 40
      Height = 24
      TabOrder = 14
      Text = '0'
    end
    object Edit_MatrixChannel: TEdit
      Left = 273
      Top = 39
      Width = 59
      Height = 24
      TabOrder = 15
      Text = '1'
    end
    object Edit_ID: TEdit
      Left = 273
      Top = 65
      Width = 59
      Height = 24
      TabOrder = 16
      Text = ' '
    end
    object Button_Load: TButton
      Left = 221
      Top = 117
      Width = 85
      Height = 20
      Caption = 'Load'
      TabOrder = 17
    end
    object Button_MatrixCalibrate: TButton
      Left = 312
      Top = 117
      Width = 85
      Height = 20
      Caption = 'Matrirx Calibrate'
      TabOrder = 18
      OnClick = Button_MatrixCalibrateClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 13
    Top = 293
    Width = 404
    Height = 46
    Caption = 'Backup'
    Enabled = False
    TabOrder = 1
    object Label11: TLabel
      Left = 13
      Top = 20
      Width = 15
      Height = 13
      Caption = 'CH'
    end
    object Label12: TLabel
      Left = 72
      Top = 20
      Width = 27
      Height = 13
      Caption = 'to CH'
    end
    object Edit_BackupStart: TEdit
      Left = 39
      Top = 20
      Width = 27
      Height = 24
      TabOrder = 0
      Text = '0'
    end
    object Edit_BackupEnd: TEdit
      Left = 104
      Top = 20
      Width = 27
      Height = 24
      TabOrder = 1
      Text = '99'
    end
    object Button_SaveToFile: TButton
      Left = 221
      Top = 20
      Width = 85
      Height = 20
      Caption = 'Save To File'
      TabOrder = 2
    end
    object Button_LoadFromFile: TButton
      Left = 312
      Top = 20
      Width = 85
      Height = 20
      Caption = 'Load From File'
      TabOrder = 3
    end
  end
  inline TCA210SettingFrame1: TCA210SettingFrame
    Left = 13
    Top = 13
    Width = 405
    Height = 125
    TabOrder = 2
    inherited GroupBox1: TGroupBox
      Width = 404
      Height = 124
      inherited Label1: TLabel
        Left = 7
        Top = 20
      end
      inherited Label2: TLabel
        Left = 7
        Top = 46
      end
      inherited Label3: TLabel
        Left = 7
        Top = 72
      end
      inherited Label4: TLabel
        Left = 208
        Top = 20
      end
      inherited Label5: TLabel
        Left = 7
        Top = 98
      end
      inherited ComboBox_SyncMode: TComboBox
        Left = 78
        Top = 20
        Width = 79
        OnChange = TCA210SettingFrame1ComboBox_SyncModeChange
        Items.Strings = (
          'NTSC'
          'PAL'
          'EXT'
          'UNIV'
          'INT')
      end
      inherited ComboBox_Speed: TComboBox
        Left = 78
        Top = 46
        Width = 79
      end
      inherited ComboBox_CalStandard: TComboBox
        Left = 78
        Top = 72
        Width = 79
      end
      inherited Edit_Hz: TEdit
        Left = 163
        Top = 20
        Width = 39
        Height = 24
      end
      inherited ComboBox_DisplayMode: TComboBox
        Left = 78
        Top = 98
        Width = 79
      end
      inherited Button_Connect: TButton
        Left = 221
        Top = 98
        Width = 85
        Height = 20
        OnClick = TCA210SettingFrame1Button_ConnectClick
      end
      inherited Button_Disconnect: TButton
        Left = 312
        Top = 98
        Width = 85
        Height = 20
      end
    end
  end
end
