object ThreeDMeasurementForm: TThreeDMeasurementForm
  Left = 287
  Top = 178
  Width = 436
  Height = 337
  Caption = '3D OD Measurement'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyPress = FormKeyPress
  PixelsPerInch = 120
  TextHeight = 16
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 409
    Height = 289
    ActivePage = TabSheet3
    TabIndex = 2
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Batch'
      object Button_Measure: TButton
        Left = 322
        Top = 136
        Width = 74
        Height = 25
        Caption = 'Measure'
        TabOrder = 0
        OnClick = Button_MeasureClick
      end
      inline OutputFileFrame1: TOutputFileFrame
        Left = 9
        Top = 161
        Width = 392
        Height = 96
        TabOrder = 1
        inherited GroupBox_OutputFile: TGroupBox
          Width = 386
          Height = 90
          inherited Label5: TLabel
            Left = 9
            Top = 25
          end
          inherited Label6: TLabel
            Left = 9
            Top = 57
          end
          inherited Edit_Prefix: TEdit
            Top = 25
            Text = 'Measurement'
          end
          inherited Edit_Directory: TEdit
            Top = 57
            Width = 201
          end
          inherited Button_BrowseDir: TButton
            Left = 320
            Top = 57
            Height = 24
          end
        end
      end
      object GroupBox1: TGroupBox
        Left = 9
        Top = 9
        Width = 224
        Height = 152
        Caption = 'Common Setup'
        TabOrder = 2
        object Label1: TLabel
          Left = 9
          Top = 25
          Width = 50
          Height = 16
          Caption = 'idle time'
        end
        object Label2: TLabel
          Left = 9
          Top = 57
          Width = 79
          Height = 16
          Caption = 'average time'
        end
        object Label3: TLabel
          Left = 169
          Top = 25
          Width = 18
          Height = 16
          Caption = 'ms'
        end
        object Label4: TLabel
          Left = 169
          Top = 57
          Width = 32
          Height = 16
          Caption = 'times'
        end
        object Edit_IdleTime: TEdit
          Left = 96
          Top = 25
          Width = 65
          Height = 24
          TabOrder = 0
          Text = '200'
        end
        object Edit_AveTimes: TEdit
          Left = 96
          Top = 57
          Width = 65
          Height = 24
          TabOrder = 1
          Text = '2'
        end
        object CheckBox_LeftRightChange: TCheckBox
          Left = 8
          Top = 88
          Width = 177
          Height = 25
          Caption = 'Left<->Right Change'
          TabOrder = 2
        end
        object CheckBox_StableTest: TCheckBox
          Left = 8
          Top = 120
          Width = 97
          Height = 17
          Caption = 'Stable Test'
          TabOrder = 3
          OnClick = CheckBox_StableTestClick
        end
        object ComboBox_MeasureMode: TComboBox
          Left = 112
          Top = 120
          Width = 89
          Height = 24
          Enabled = False
          ItemHeight = 16
          ItemIndex = 1
          TabOrder = 4
          Text = 'Fast'
          Items.Strings = (
            'Auto'
            'Fast')
        end
      end
      object GroupBox3: TGroupBox
        Left = 240
        Top = 9
        Width = 73
        Height = 152
        Caption = 'Color'
        TabOrder = 3
        object CheckBox_W: TCheckBox
          Left = 9
          Top = 25
          Width = 40
          Height = 24
          Caption = 'W'
          Checked = True
          State = cbChecked
          TabOrder = 0
        end
        object CheckBox_R: TCheckBox
          Left = 9
          Top = 57
          Width = 40
          Height = 24
          Caption = 'R'
          TabOrder = 1
        end
        object CheckBox_G: TCheckBox
          Left = 9
          Top = 89
          Width = 40
          Height = 24
          Caption = 'G'
          TabOrder = 2
        end
        object CheckBox_B: TCheckBox
          Left = 9
          Top = 121
          Width = 32
          Height = 24
          Caption = 'B'
          TabOrder = 3
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Spot'
      ImageIndex = 1
      object Button_SpotMeasure: TButton
        Left = 144
        Top = 72
        Width = 73
        Height = 25
        Caption = 'Measure'
        TabOrder = 0
        OnClick = Button_SpotMeasureClick
      end
      object GroupBox4: TGroupBox
        Left = 8
        Top = 8
        Width = 129
        Height = 89
        Caption = 'Spot'
        TabOrder = 1
        object Label5: TLabel
          Left = 8
          Top = 24
          Width = 27
          Height = 16
          Caption = 'Start'
        end
        object Label6: TLabel
          Left = 8
          Top = 56
          Width = 40
          Height = 16
          Caption = 'Target'
        end
        object Edit_Start: TEdit
          Left = 56
          Top = 24
          Width = 65
          Height = 24
          TabOrder = 0
          Text = '16'
        end
        object Edit_Target: TEdit
          Left = 56
          Top = 56
          Width = 65
          Height = 24
          TabOrder = 1
          Text = '32'
        end
      end
      object GroupBox5: TGroupBox
        Left = 8
        Top = 104
        Width = 369
        Height = 161
        Caption = 'Result'
        TabOrder = 2
        object Label7: TLabel
          Left = 320
          Top = 56
          Width = 12
          Height = 16
          Caption = '%'
        end
        object Label8: TLabel
          Left = 320
          Top = 120
          Width = 12
          Height = 16
          Caption = '%'
          Visible = False
        end
        object Edit5: TEdit
          Left = 8
          Top = 24
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 0
        end
        object Edit6: TEdit
          Left = 56
          Top = 24
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 1
        end
        object Edit7: TEdit
          Left = 8
          Top = 56
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 2
        end
        object Edit8: TEdit
          Left = 56
          Top = 56
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 3
        end
        object Edit9: TEdit
          Left = 8
          Top = 88
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 4
        end
        object Edit10: TEdit
          Left = 56
          Top = 88
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 5
        end
        object Edit11: TEdit
          Left = 112
          Top = 24
          Width = 89
          Height = 24
          TabOrder = 6
          Text = '0.0'
        end
        object Edit12: TEdit
          Left = 112
          Top = 56
          Width = 89
          Height = 24
          TabOrder = 7
          Text = '0.0'
        end
        object Edit13: TEdit
          Left = 112
          Top = 88
          Width = 89
          Height = 24
          TabOrder = 8
          Text = '0.0'
        end
        object Edit1: TEdit
          Left = 224
          Top = 56
          Width = 89
          Height = 24
          TabOrder = 9
          Text = '0.0'
        end
        object Edit2: TEdit
          Left = 8
          Top = 120
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 10
          Visible = False
        end
        object Edit3: TEdit
          Left = 56
          Top = 120
          Width = 41
          Height = 24
          Color = cl3DLight
          Enabled = False
          TabOrder = 11
          Visible = False
        end
        object Edit4: TEdit
          Left = 112
          Top = 120
          Width = 89
          Height = 24
          TabOrder = 12
          Text = '0.0'
          Visible = False
        end
        object Edit14: TEdit
          Left = 224
          Top = 120
          Width = 89
          Height = 24
          TabOrder = 13
          Text = '0.0'
          Visible = False
        end
      end
      object CheckBox_Extend: TCheckBox
        Left = 144
        Top = 40
        Width = 89
        Height = 25
        Caption = 'Extend'
        TabOrder = 3
        OnClick = CheckBox_ExtendClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Dynamic'
      ImageIndex = 2
      object GroupBox2: TGroupBox
        Left = 8
        Top = 8
        Width = 129
        Height = 89
        Caption = 'Spot'
        TabOrder = 0
        object Label9: TLabel
          Left = 8
          Top = 24
          Width = 27
          Height = 16
          Caption = 'Start'
        end
        object Label10: TLabel
          Left = 8
          Top = 56
          Width = 40
          Height = 16
          Caption = 'Target'
        end
        object Edit_DStart: TEdit
          Left = 56
          Top = 24
          Width = 65
          Height = 24
          TabOrder = 0
          Text = '16'
        end
        object Edit_DTarget: TEdit
          Left = 56
          Top = 56
          Width = 65
          Height = 24
          TabOrder = 1
          Text = '32'
        end
      end
      object Button_DynamicMeasure: TButton
        Left = 144
        Top = 72
        Width = 73
        Height = 25
        Caption = 'Measure'
        TabOrder = 1
        OnClick = Button_DynamicMeasureClick
      end
    end
  end
end
