object DCRForm1: TDCRForm1
  Left = -4
  Top = -4
  Width = 1928
  Height = 1148
  Align = alCustom
  Caption = 'DCR'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 738
    Height = 490
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'DCR Setting'
      object CheckBox1: TCheckBox
        Left = 8
        Top = 10
        Width = 106
        Height = 18
        Caption = 'CheckBox1'
        TabOrder = 0
      end
      object GroupBox1: TGroupBox
        Left = 376
        Top = 371
        Width = 353
        Height = 84
        Caption = 'BackLight Gradient Step'
        TabOrder = 1
        object Label3: TLabel
          Left = 10
          Top = 23
          Width = 32
          Height = 13
          Caption = 'Label3'
        end
        object Label32: TLabel
          Left = 10
          Top = 43
          Width = 38
          Height = 13
          Caption = 'Label32'
        end
        object Label35: TLabel
          Left = 10
          Top = 63
          Width = 26
          Height = 13
          Caption = 'Label'
        end
        object CheckBox6: TCheckBox
          Left = 136
          Top = 0
          Width = 162
          Height = 18
          Caption = 'CheckBox6'
          TabOrder = 0
        end
        object ScrollBar3: TScrollBar
          Left = 136
          Top = 20
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 1
        end
        object StaticText3: TStaticText
          Left = 312
          Top = 21
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText3'
          TabOrder = 2
        end
        object ScrollBar28: TScrollBar
          Left = 136
          Top = 41
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 3
        end
        object StaticText28: TStaticText
          Left = 312
          Top = 42
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText28'
          TabOrder = 4
        end
        object ScrollBar31: TScrollBar
          Left = 136
          Top = 62
          Width = 169
          Height = 18
          PageSize = 0
          TabOrder = 5
        end
        object StaticText31: TStaticText
          Left = 313
          Top = 62
          Width = 52
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 6
        end
      end
      object GroupBox2: TGroupBox
        Left = 8
        Top = 371
        Width = 362
        Height = 84
        Caption = 'Histogram difference ratio'
        TabOrder = 2
        object Label4: TLabel
          Left = 10
          Top = 22
          Width = 32
          Height = 13
          Caption = 'Label4'
        end
        object ScrollBar4: TScrollBar
          Left = 144
          Top = 20
          Width = 169
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object StaticText4: TStaticText
          Left = 320
          Top = 20
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText4'
          TabOrder = 1
        end
        object CheckBox7: TCheckBox
          Left = 168
          Top = 0
          Width = 170
          Height = 18
          Caption = 'CheckBox7'
          TabOrder = 2
        end
        object GroupBox17: TGroupBox
          Left = 3
          Top = 42
          Width = 350
          Height = 33
          Caption = 'Noise Filter'
          TabOrder = 3
          object Label42: TLabel
            Left = 10
            Top = 14
            Width = 26
            Height = 13
            Caption = 'Label'
          end
          object ScrollBar38: TScrollBar
            Left = 141
            Top = 10
            Width = 169
            Height = 18
            PageSize = 0
            TabOrder = 0
          end
          object StaticText38: TStaticText
            Left = 317
            Top = 10
            Width = 52
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 1
          end
        end
      end
      object GroupBox6: TGroupBox
        Left = 376
        Top = 84
        Width = 353
        Height = 225
        Caption = 'Duty Detect'
        TabOrder = 3
        object Label10: TLabel
          Left = 8
          Top = 48
          Width = 38
          Height = 13
          Caption = 'Label10'
        end
        object Label11: TLabel
          Left = 8
          Top = 70
          Width = 38
          Height = 13
          Caption = 'Label11'
        end
        object Label81: TLabel
          Left = 8
          Top = 24
          Width = 38
          Height = 13
          Caption = 'Label81'
        end
        object ScrollBar10: TScrollBar
          Left = 136
          Top = 48
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object StaticText10: TStaticText
          Left = 312
          Top = 49
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText10'
          TabOrder = 1
        end
        object ScrollBar11: TScrollBar
          Left = 136
          Top = 71
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 2
        end
        object StaticText11: TStaticText
          Left = 312
          Top = 70
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText11'
          TabOrder = 3
        end
        object CheckBox5: TCheckBox
          Left = 136
          Top = 0
          Width = 169
          Height = 18
          Caption = 'CheckBox5'
          TabOrder = 4
        end
        object GroupBox3: TGroupBox
          Left = 3
          Top = 91
          Width = 345
          Height = 130
          Caption = 'PWM Frequency Setting'
          TabOrder = 5
          object Label5: TLabel
            Left = 10
            Top = 42
            Width = 32
            Height = 13
            Caption = 'Label5'
          end
          object Label14: TLabel
            Left = 10
            Top = 20
            Width = 38
            Height = 13
            Caption = 'Label14'
          end
          object ComboBox1: TComboBox
            Left = 136
            Top = 16
            Width = 122
            Height = 21
            ItemHeight = 13
            TabOrder = 0
            Text = 'ComboBox1'
          end
          object ScrollBar5: TScrollBar
            Left = 136
            Top = 40
            Width = 170
            Height = 18
            PageSize = 0
            TabOrder = 1
          end
          object StaticText5: TStaticText
            Left = 312
            Top = 40
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText5'
            TabOrder = 2
          end
          object GroupBox7: TGroupBox
            Left = 3
            Top = 60
            Width = 340
            Height = 65
            Caption = 'PWM_Coefficient'
            TabOrder = 3
            object Label13: TLabel
              Left = 8
              Top = 42
              Width = 38
              Height = 13
              Caption = 'Label13'
            end
            object Label12: TLabel
              Left = 8
              Top = 20
              Width = 38
              Height = 13
              Caption = 'Label12'
            end
            object ScrollBar12: TScrollBar
              Left = 133
              Top = 19
              Width = 170
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object ScrollBar13: TScrollBar
              Left = 133
              Top = 42
              Width = 170
              Height = 18
              PageSize = 0
              TabOrder = 1
            end
            object StaticText12: TStaticText
              Left = 309
              Top = 20
              Width = 64
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText12'
              TabOrder = 2
            end
            object StaticText13: TStaticText
              Left = 309
              Top = 41
              Width = 64
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText13'
              TabOrder = 3
            end
            object CheckBox9: TCheckBox
              Left = 138
              Top = 0
              Width = 160
              Height = 18
              Caption = 'CheckBox9'
              TabOrder = 4
            end
          end
        end
        object ComboBox13: TComboBox
          Left = 136
          Top = 20
          Width = 209
          Height = 21
          ItemHeight = 13
          TabOrder = 6
          Text = 'ComboBox13'
        end
      end
      object CheckBox12: TCheckBox
        Left = 8
        Top = 37
        Width = 98
        Height = 18
        Caption = 'CheckBox12'
        TabOrder = 4
      end
      object GroupBox32: TGroupBox
        Left = 8
        Top = 98
        Width = 362
        Height = 276
        Caption = 'BL_IDX/ PWM modulation'
        TabOrder = 5
        object GroupBox31: TGroupBox
          Left = 8
          Top = 13
          Width = 346
          Height = 65
          Caption = 'Modulation Select '
          TabOrder = 0
          object Label1: TLabel
            Left = 8
            Top = 40
            Width = 32
            Height = 13
            Caption = 'Label1'
          end
          object Label80: TLabel
            Left = 8
            Top = 17
            Width = 38
            Height = 13
            Caption = 'Label80'
          end
          object ScrollBar1: TScrollBar
            Left = 136
            Top = 40
            Width = 170
            Height = 18
            PageSize = 0
            TabOrder = 0
          end
          object StaticText1: TStaticText
            Left = 312
            Top = 40
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText1'
            TabOrder = 1
          end
          object ComboBox12: TComboBox
            Left = 136
            Top = 12
            Width = 201
            Height = 21
            ItemHeight = 13
            TabOrder = 2
            Text = 'ComboBox12'
          end
        end
        object GroupBox5: TGroupBox
          Left = 8
          Top = 77
          Width = 346
          Height = 103
          Caption = 'Image loading ratio boundary and BL_IDX curve slope setting'
          TabOrder = 1
          object Label8: TLabel
            Left = 8
            Top = 39
            Width = 32
            Height = 13
            Caption = 'Label8'
          end
          object Label9: TLabel
            Left = 8
            Top = 18
            Width = 32
            Height = 13
            Caption = 'Label9'
          end
          object ScrollBar8: TScrollBar
            Left = 136
            Top = 40
            Width = 170
            Height = 18
            PageSize = 0
            TabOrder = 0
          end
          object StaticText8: TStaticText
            Left = 312
            Top = 40
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText8'
            TabOrder = 1
          end
          object ScrollBar9: TScrollBar
            Left = 136
            Top = 16
            Width = 170
            Height = 18
            PageSize = 0
            TabOrder = 2
          end
          object StaticText9: TStaticText
            Left = 312
            Top = 16
            Width = 58
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText9'
            TabOrder = 3
          end
          object LabeledEdit1: TLabeledEdit
            Left = 8
            Top = 75
            Width = 73
            Height = 24
            EditLabel.Width = 51
            EditLabel.Height = 10
            EditLabel.Caption = 'LabeledEdit1'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 4
          end
        end
        object GroupBox18: TGroupBox
          Left = 8
          Top = 179
          Width = 346
          Height = 33
          TabOrder = 2
          object Label41: TLabel
            Left = 10
            Top = 11
            Width = 26
            Height = 13
            Caption = 'Label'
          end
          object ScrollBar37: TScrollBar
            Left = 136
            Top = 10
            Width = 170
            Height = 18
            PageSize = 0
            TabOrder = 0
          end
          object StaticText37: TStaticText
            Left = 312
            Top = 10
            Width = 52
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 1
          end
        end
        object GroupBox4: TGroupBox
          Left = 8
          Top = 211
          Width = 346
          Height = 63
          Caption = 'Power saving mode'
          TabOrder = 3
          object Label33: TLabel
            Left = 8
            Top = 22
            Width = 38
            Height = 13
            Caption = 'Label33'
          end
          object Label34: TLabel
            Left = 8
            Top = 42
            Width = 38
            Height = 13
            Caption = 'Label34'
          end
          object ScrollBar29: TScrollBar
            Left = 136
            Top = 20
            Width = 169
            Height = 18
            PageSize = 0
            TabOrder = 0
          end
          object CheckBox21: TCheckBox
            Left = 136
            Top = 0
            Width = 162
            Height = 18
            Caption = 'CheckBox21'
            TabOrder = 1
          end
          object ScrollBar30: TScrollBar
            Left = 136
            Top = 42
            Width = 169
            Height = 18
            PageSize = 0
            TabOrder = 2
          end
          object StaticText29: TStaticText
            Left = 312
            Top = 21
            Width = 64
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText29'
            TabOrder = 3
          end
          object StaticText30: TStaticText
            Left = 312
            Top = 42
            Width = 64
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText30'
            TabOrder = 4
          end
        end
      end
      object GroupBox42: TGroupBox
        Left = 8
        Top = 62
        Width = 362
        Height = 37
        Caption = 'GLT_Sharpness'
        TabOrder = 6
        object Label2: TLabel
          Left = 8
          Top = 15
          Width = 32
          Height = 13
          Caption = 'Label2'
        end
        object ScrollBar2: TScrollBar
          Left = 144
          Top = 13
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object StaticText2: TStaticText
          Left = 319
          Top = 13
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText2'
          TabOrder = 1
        end
      end
      object GroupBox20: TGroupBox
        Left = 376
        Top = 308
        Width = 353
        Height = 65
        Caption = 'Duty Smooth Change function'
        TabOrder = 7
        object Label43: TLabel
          Left = 10
          Top = 18
          Width = 26
          Height = 13
          Caption = 'Label'
        end
        object Label44: TLabel
          Left = 10
          Top = 38
          Width = 26
          Height = 13
          Caption = 'Label'
        end
        object ScrollBar39: TScrollBar
          Left = 136
          Top = 19
          Width = 169
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object StaticText39: TStaticText
          Left = 312
          Top = 20
          Width = 52
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 1
        end
        object ScrollBar40: TScrollBar
          Left = 136
          Top = 42
          Width = 169
          Height = 18
          PageSize = 0
          TabOrder = 2
        end
        object StaticText40: TStaticText
          Left = 312
          Top = 41
          Width = 52
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 3
        end
        object CheckBox22: TCheckBox
          Left = 168
          Top = -1
          Width = 129
          Height = 18
          Caption = 'CheckBox22'
          TabOrder = 4
        end
      end
      object GroupBox44: TGroupBox
        Left = 376
        Top = 54
        Width = 353
        Height = 30
        TabOrder = 8
        object Label84: TLabel
          Left = 8
          Top = 10
          Width = 38
          Height = 13
          Caption = 'Label84'
        end
        object ComboBox16: TComboBox
          Left = 137
          Top = 7
          Width = 208
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = 'ComboBox16'
        end
      end
      object GroupBox46: TGroupBox
        Left = 84
        Top = -2
        Width = 140
        Height = 62
        Caption = 'XOR Operation'
        TabOrder = 9
        object CheckBox2: TCheckBox
          Left = 12
          Top = 12
          Width = 106
          Height = 18
          Caption = 'CheckBox2'
          TabOrder = 0
        end
        object GroupBox33: TGroupBox
          Left = 3
          Top = 28
          Width = 118
          Height = 32
          Caption = 'AND with DCREN pin'
          TabOrder = 1
          object CheckBox17: TCheckBox
            Left = 8
            Top = 12
            Width = 105
            Height = 18
            Caption = 'CheckBox17'
            TabOrder = 0
          end
        end
      end
      object GroupBox47: TGroupBox
        Left = 229
        Top = -2
        Width = 140
        Height = 62
        Caption = 'XOR Operation'
        TabOrder = 10
        object CheckBox3: TCheckBox
          Left = 11
          Top = 13
          Width = 106
          Height = 18
          Caption = 'CheckBox3'
          TabOrder = 0
        end
        object GroupBox48: TGroupBox
          Left = 3
          Top = 28
          Width = 118
          Height = 32
          Caption = 'AND with DCREN pin'
          TabOrder = 1
          object CheckBox18: TCheckBox
            Left = 8
            Top = 12
            Width = 97
            Height = 18
            Caption = 'CheckBox18'
            TabOrder = 0
          end
        end
      end
      object GroupBox12: TGroupBox
        Left = 376
        Top = -2
        Width = 353
        Height = 57
        Caption = 'GLT Demo mode'
        TabOrder = 11
        object Label83: TLabel
          Left = 9
          Top = 15
          Width = 38
          Height = 13
          Caption = 'Label83'
        end
        object CheckBox8: TCheckBox
          Left = 160
          Top = -1
          Width = 129
          Height = 18
          Caption = 'CheckBox8'
          TabOrder = 0
        end
        object ComboBox15: TComboBox
          Left = 8
          Top = 29
          Width = 337
          Height = 21
          ItemHeight = 13
          TabOrder = 1
          Text = 'ComboBox15'
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'DCR | HDR Setting'
      ImageIndex = 1
      object GroupBox11: TGroupBox
        Left = 0
        Top = 0
        Width = 722
        Height = 450
        TabOrder = 0
        object GroupBox19: TGroupBox
          Left = 8
          Top = 158
          Width = 330
          Height = 41
          Caption = 'Demo Mode for Display BL'
          TabOrder = 0
          object Label40: TLabel
            Left = 10
            Top = 18
            Width = 26
            Height = 13
            Caption = 'Label'
          end
          object CheckBox20: TCheckBox
            Left = 168
            Top = -1
            Width = 153
            Height = 18
            Caption = 'CheckBox20'
            TabOrder = 0
          end
          object ScrollBar36: TScrollBar
            Left = 136
            Top = 18
            Width = 162
            Height = 18
            PageSize = 0
            TabOrder = 1
          end
          object StaticText36: TStaticText
            Left = 302
            Top = 18
            Width = 52
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 2
          end
        end
        object GroupBox37: TGroupBox
          Left = 480
          Top = 288
          Width = 162
          Height = 106
          Caption = 'interpolation_coeff'
          TabOrder = 1
          object LabeledEdit9: TLabeledEdit
            Left = 8
            Top = 32
            Width = 122
            Height = 21
            EditLabel.Width = 51
            EditLabel.Height = 10
            EditLabel.Caption = 'LabeledEdit9'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit10: TLabeledEdit
            Left = 8
            Top = 72
            Width = 122
            Height = 21
            EditLabel.Width = 55
            EditLabel.Height = 11
            EditLabel.Caption = 'LabeledEdit10'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
        end
        object GroupBox38: TGroupBox
          Left = 8
          Top = 288
          Width = 153
          Height = 106
          Caption = 'section_num'
          TabOrder = 2
          object LabeledEdit2: TLabeledEdit
            Left = 8
            Top = 32
            Width = 122
            Height = 21
            EditLabel.Width = 51
            EditLabel.Height = 10
            EditLabel.Caption = 'LabeledEdit2'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit3: TLabeledEdit
            Left = 8
            Top = 72
            Width = 122
            Height = 21
            EditLabel.Width = 51
            EditLabel.Height = 11
            EditLabel.Caption = 'LabeledEdit3'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
        end
        object LabeledEdit4: TLabeledEdit
          Left = 344
          Top = 304
          Width = 122
          Height = 21
          EditLabel.Width = 50
          EditLabel.Height = 10
          EditLabel.Caption = 'LabeledEdit4'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
        end
        object GroupBox39: TGroupBox
          Left = 168
          Top = 288
          Width = 169
          Height = 106
          Caption = 'divide_num'
          TabOrder = 4
          object LabeledEdit5: TLabeledEdit
            Left = 8
            Top = 32
            Width = 122
            Height = 21
            EditLabel.Width = 51
            EditLabel.Height = 10
            EditLabel.Caption = 'LabeledEdit5'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit6: TLabeledEdit
            Left = 8
            Top = 72
            Width = 122
            Height = 21
            EditLabel.Width = 51
            EditLabel.Height = 11
            EditLabel.Caption = 'LabeledEdit6'
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
          end
        end
        object LabeledEdit7: TLabeledEdit
          Left = 344
          Top = 344
          Width = 122
          Height = 21
          EditLabel.Width = 50
          EditLabel.Height = 10
          EditLabel.Caption = 'LabeledEdit7'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 5
        end
        object LabeledEdit8: TLabeledEdit
          Left = 344
          Top = 384
          Width = 122
          Height = 21
          EditLabel.Width = 50
          EditLabel.Height = 11
          EditLabel.Caption = 'LabeledEdit8'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 6
        end
        object GroupBox43: TGroupBox
          Left = 8
          Top = 201
          Width = 330
          Height = 80
          Color = clBtnFace
          ParentColor = False
          TabOrder = 7
          object Label15: TLabel
            Left = 11
            Top = 9
            Width = 38
            Height = 13
            Caption = 'Label15'
          end
          object Label16: TLabel
            Left = 11
            Top = 33
            Width = 38
            Height = 13
            Caption = 'Label16'
          end
          object Label17: TLabel
            Left = 11
            Top = 59
            Width = 38
            Height = 13
            Caption = 'Label17'
          end
          object ComboBox2: TComboBox
            Left = 134
            Top = 9
            Width = 190
            Height = 21
            ItemHeight = 13
            TabOrder = 0
            Text = 'ComboBox2'
          end
          object ComboBox3: TComboBox
            Left = 133
            Top = 33
            Width = 190
            Height = 21
            ItemHeight = 13
            TabOrder = 1
            Text = 'ComboBox3'
          end
          object ComboBox4: TComboBox
            Left = 133
            Top = 57
            Width = 190
            Height = 21
            ItemHeight = 13
            TabOrder = 2
            Text = 'ComboBox4'
          end
        end
        object GroupBox21: TGroupBox
          Left = 344
          Top = 8
          Width = 369
          Height = 273
          Caption = 'HDR dedicated'
          TabOrder = 8
          object GroupBox23: TGroupBox
            Left = 11
            Top = 11
            Width = 350
            Height = 30
            TabOrder = 0
            object Label46: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar42: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText42: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox24: TGroupBox
            Left = 11
            Top = 43
            Width = 350
            Height = 30
            TabOrder = 1
            object Label47: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar43: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText43: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox25: TGroupBox
            Left = 11
            Top = 75
            Width = 350
            Height = 30
            TabOrder = 2
            object Label48: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar44: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText44: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox26: TGroupBox
            Left = 11
            Top = 107
            Width = 350
            Height = 30
            TabOrder = 3
            object Label49: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar45: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText45: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox27: TGroupBox
            Left = 11
            Top = 139
            Width = 350
            Height = 30
            TabOrder = 4
            object Label50: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar46: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText46: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox28: TGroupBox
            Left = 11
            Top = 171
            Width = 350
            Height = 30
            TabOrder = 5
            object Label51: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar47: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText47: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox29: TGroupBox
            Left = 11
            Top = 203
            Width = 350
            Height = 30
            TabOrder = 6
            object Label52: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar48: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText48: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox30: TGroupBox
            Left = 11
            Top = 235
            Width = 350
            Height = 30
            TabOrder = 7
            object Label53: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar49: TScrollBar
              Left = 184
              Top = 8
              Width = 130
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText49: TStaticText
              Left = 320
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
        end
        object GroupBox45: TGroupBox
          Left = 8
          Top = 8
          Width = 330
          Height = 33
          TabOrder = 9
          object Label54: TLabel
            Left = 11
            Top = 12
            Width = 38
            Height = 13
            Caption = 'Label54'
          end
          object ComboBox5: TComboBox
            Left = 136
            Top = 8
            Width = 190
            Height = 21
            ItemHeight = 13
            TabOrder = 0
            Text = 'ComboBox5'
          end
        end
        object GroupBox49: TGroupBox
          Left = 8
          Top = 47
          Width = 329
          Height = 105
          Caption = 'BL enhance function'
          TabOrder = 10
          object GroupBox15: TGroupBox
            Left = 8
            Top = 40
            Width = 321
            Height = 30
            TabOrder = 0
            object Label38: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar34: TScrollBar
              Left = 128
              Top = 8
              Width = 162
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText34: TStaticText
              Left = 296
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox14: TGroupBox
            Left = 9
            Top = 11
            Width = 320
            Height = 30
            TabOrder = 1
            object Label37: TLabel
              Left = 10
              Top = 9
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar33: TScrollBar
              Left = 127
              Top = 8
              Width = 162
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText33: TStaticText
              Left = 296
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
          object GroupBox16: TGroupBox
            Left = 8
            Top = 69
            Width = 321
            Height = 30
            TabOrder = 2
            object Label39: TLabel
              Left = 10
              Top = 10
              Width = 26
              Height = 13
              Caption = 'Label'
            end
            object ScrollBar35: TScrollBar
              Left = 128
              Top = 8
              Width = 162
              Height = 18
              PageSize = 0
              TabOrder = 0
            end
            object StaticText35: TStaticText
              Left = 296
              Top = 8
              Width = 52
              Height = 17
              BorderStyle = sbsSunken
              Caption = 'StaticText'
              TabOrder = 1
            end
          end
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'HDR Setting'
      ImageIndex = 3
      object GroupBox34: TGroupBox
        Left = 344
        Top = 0
        Width = 378
        Height = 434
        TabOrder = 0
        object Label55: TLabel
          Left = 8
          Top = 24
          Width = 38
          Height = 13
          Caption = 'Label55'
        end
        object Label56: TLabel
          Left = 8
          Top = 48
          Width = 38
          Height = 13
          Caption = 'Label56'
        end
        object Label57: TLabel
          Left = 8
          Top = 72
          Width = 38
          Height = 13
          Caption = 'Label57'
        end
        object Label58: TLabel
          Left = 8
          Top = 96
          Width = 38
          Height = 13
          Caption = 'Label58'
        end
        object Label59: TLabel
          Left = 8
          Top = 120
          Width = 38
          Height = 13
          Caption = 'Label59'
        end
        object Label60: TLabel
          Left = 8
          Top = 144
          Width = 38
          Height = 13
          Caption = 'Label60'
        end
        object Label61: TLabel
          Left = 8
          Top = 168
          Width = 38
          Height = 13
          Caption = 'Label61'
        end
        object Label62: TLabel
          Left = 8
          Top = 192
          Width = 38
          Height = 13
          Caption = 'Label62'
        end
        object Label63: TLabel
          Left = 8
          Top = 216
          Width = 38
          Height = 13
          Caption = 'Label63'
        end
        object Label64: TLabel
          Left = 8
          Top = 240
          Width = 38
          Height = 13
          Caption = 'Label64'
        end
        object Label65: TLabel
          Left = 8
          Top = 264
          Width = 38
          Height = 13
          Caption = 'Label65'
        end
        object Label66: TLabel
          Left = 8
          Top = 288
          Width = 38
          Height = 13
          Caption = 'Label66'
        end
        object Label67: TLabel
          Left = 8
          Top = 312
          Width = 38
          Height = 13
          Caption = 'Label67'
        end
        object Label68: TLabel
          Left = 8
          Top = 336
          Width = 38
          Height = 13
          Caption = 'Label68'
        end
        object Label69: TLabel
          Left = 8
          Top = 360
          Width = 38
          Height = 13
          Caption = 'Label69'
        end
        object Label70: TLabel
          Left = 8
          Top = 384
          Width = 38
          Height = 13
          Caption = 'Label70'
        end
        object Label71: TLabel
          Left = 7
          Top = 408
          Width = 38
          Height = 13
          Caption = 'Label71'
        end
        object ScrollBar50: TScrollBar
          Left = 171
          Top = 24
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object ScrollBar51: TScrollBar
          Left = 171
          Top = 48
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 1
        end
        object ScrollBar52: TScrollBar
          Left = 171
          Top = 72
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 2
        end
        object ScrollBar53: TScrollBar
          Left = 171
          Top = 96
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 3
        end
        object ScrollBar54: TScrollBar
          Left = 171
          Top = 120
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 4
        end
        object ScrollBar55: TScrollBar
          Left = 171
          Top = 144
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 5
        end
        object ScrollBar56: TScrollBar
          Left = 171
          Top = 168
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 6
        end
        object ScrollBar57: TScrollBar
          Left = 171
          Top = 192
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 7
        end
        object ScrollBar58: TScrollBar
          Left = 171
          Top = 216
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 8
        end
        object ScrollBar59: TScrollBar
          Left = 171
          Top = 240
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 9
        end
        object ScrollBar60: TScrollBar
          Left = 171
          Top = 264
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 10
        end
        object ScrollBar61: TScrollBar
          Left = 171
          Top = 288
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 11
        end
        object ScrollBar62: TScrollBar
          Left = 171
          Top = 312
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 12
        end
        object ScrollBar63: TScrollBar
          Left = 171
          Top = 336
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 13
        end
        object ScrollBar64: TScrollBar
          Left = 171
          Top = 360
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 14
        end
        object ScrollBar65: TScrollBar
          Left = 171
          Top = 384
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 15
        end
        object ScrollBar66: TScrollBar
          Left = 171
          Top = 408
          Width = 170
          Height = 18
          PageSize = 0
          TabOrder = 16
        end
        object StaticText50: TStaticText
          Left = 347
          Top = 24
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 17
        end
        object StaticText51: TStaticText
          Left = 347
          Top = 48
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 18
        end
        object StaticText53: TStaticText
          Left = 347
          Top = 96
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 19
        end
        object StaticText54: TStaticText
          Left = 347
          Top = 120
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 20
        end
        object StaticText55: TStaticText
          Left = 347
          Top = 144
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 21
        end
        object StaticText56: TStaticText
          Left = 347
          Top = 168
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 22
        end
        object StaticText57: TStaticText
          Left = 347
          Top = 192
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 23
        end
        object StaticText58: TStaticText
          Left = 347
          Top = 216
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 24
        end
        object StaticText59: TStaticText
          Left = 347
          Top = 240
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 25
        end
        object StaticText60: TStaticText
          Left = 346
          Top = 264
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 26
        end
        object StaticText61: TStaticText
          Left = 346
          Top = 288
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 27
        end
        object StaticText62: TStaticText
          Left = 347
          Top = 312
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 28
        end
        object StaticText63: TStaticText
          Left = 347
          Top = 336
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 29
        end
        object StaticText64: TStaticText
          Left = 347
          Top = 360
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 30
        end
        object StaticText65: TStaticText
          Left = 347
          Top = 384
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 31
        end
        object StaticText66: TStaticText
          Left = 347
          Top = 408
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText50'
          TabOrder = 32
        end
        object StaticText52: TStaticText
          Left = 347
          Top = 72
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText52'
          TabOrder = 33
        end
      end
      object GroupBox35: TGroupBox
        Left = 4
        Top = 137
        Width = 338
        Height = 249
        TabOrder = 1
        object Label72: TLabel
          Left = 8
          Top = 8
          Width = 38
          Height = 13
          Caption = 'Label72'
        end
        object Label73: TLabel
          Left = 8
          Top = 48
          Width = 38
          Height = 13
          Caption = 'Label73'
        end
        object Label74: TLabel
          Left = 8
          Top = 88
          Width = 38
          Height = 13
          Caption = 'Label74'
        end
        object Label75: TLabel
          Left = 8
          Top = 128
          Width = 38
          Height = 13
          Caption = 'Label75'
        end
        object Label76: TLabel
          Left = 8
          Top = 168
          Width = 38
          Height = 13
          Caption = 'Label76'
        end
        object Label77: TLabel
          Left = 8
          Top = 208
          Width = 38
          Height = 13
          Caption = 'Label77'
        end
        object ComboBox6: TComboBox
          Left = 8
          Top = 24
          Width = 322
          Height = 21
          ItemHeight = 0
          TabOrder = 0
          Text = 'ComboBox6'
        end
        object ComboBox7: TComboBox
          Left = 8
          Top = 64
          Width = 322
          Height = 21
          ItemHeight = 0
          TabOrder = 1
          Text = 'ComboBox7'
        end
        object ComboBox8: TComboBox
          Left = 8
          Top = 104
          Width = 322
          Height = 21
          ItemHeight = 0
          TabOrder = 2
          Text = 'ComboBox8'
        end
        object ComboBox9: TComboBox
          Left = 8
          Top = 144
          Width = 322
          Height = 21
          ItemHeight = 0
          TabOrder = 3
          Text = 'ComboBox9'
        end
        object ComboBox10: TComboBox
          Left = 8
          Top = 184
          Width = 322
          Height = 21
          ItemHeight = 0
          TabOrder = 4
          Text = 'ComboBox10'
        end
        object ComboBox11: TComboBox
          Left = 8
          Top = 224
          Width = 322
          Height = 21
          ItemHeight = 0
          TabOrder = 5
          Text = 'ComboBox11'
        end
      end
      object GroupBox36: TGroupBox
        Left = 4
        Top = 1
        Width = 338
        Height = 138
        TabOrder = 2
        object LabeledEdit11: TLabeledEdit
          Left = 8
          Top = 32
          Width = 122
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 10
          EditLabel.Caption = 'LabeledEdit11'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 0
        end
        object LabeledEdit12: TLabeledEdit
          Left = 8
          Top = 72
          Width = 122
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 11
          EditLabel.Caption = 'LabeledEdit12'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 1
        end
        object LabeledEdit13: TLabeledEdit
          Left = 8
          Top = 112
          Width = 122
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 11
          EditLabel.Caption = 'LabeledEdit13'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 2
        end
        object LabeledEdit14: TLabeledEdit
          Left = 192
          Top = 72
          Width = 122
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 11
          EditLabel.Caption = 'LabeledEdit14'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 3
        end
        object LabeledEdit15: TLabeledEdit
          Left = 192
          Top = 112
          Width = 122
          Height = 21
          EditLabel.Width = 55
          EditLabel.Height = 11
          EditLabel.Caption = 'LabeledEdit15'
          LabelPosition = lpAbove
          LabelSpacing = 3
          TabOrder = 4
        end
      end
      object GroupBox22: TGroupBox
        Left = 5
        Top = 385
        Width = 337
        Height = 49
        TabOrder = 3
        object Label45: TLabel
          Left = 10
          Top = 10
          Width = 26
          Height = 13
          Caption = 'Label'
        end
        object ScrollBar41: TScrollBar
          Left = 8
          Top = 24
          Width = 297
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object StaticText41: TStaticText
          Left = 309
          Top = 24
          Width = 52
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText'
          TabOrder = 1
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = '&ALS SMBUS'
      ImageIndex = 2
      object GroupBox8: TGroupBox
        Left = 0
        Top = 4
        Width = 354
        Height = 74
        Caption = 'SMBUS'
        TabOrder = 0
        object Label6: TLabel
          Left = 10
          Top = 28
          Width = 32
          Height = 13
          Caption = 'Label6'
        end
        object Label7: TLabel
          Left = 10
          Top = 52
          Width = 32
          Height = 13
          Caption = 'Label7'
        end
        object ScrollBar6: TScrollBar
          Left = 120
          Top = 24
          Width = 162
          Height = 18
          PageSize = 0
          TabOrder = 0
        end
        object StaticText6: TStaticText
          Left = 288
          Top = 24
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText6'
          TabOrder = 1
        end
        object ScrollBar7: TScrollBar
          Left = 120
          Top = 48
          Width = 162
          Height = 18
          PageSize = 0
          TabOrder = 2
        end
        object StaticText7: TStaticText
          Left = 288
          Top = 48
          Width = 58
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText7'
          TabOrder = 3
        end
        object CheckBox11: TCheckBox
          Left = 168
          Top = 0
          Width = 90
          Height = 18
          Caption = 'CheckBox11'
          TabOrder = 4
        end
      end
      object GroupBox9: TGroupBox
        Left = 0
        Top = 80
        Width = 721
        Height = 377
        Caption = 'ALS'
        TabOrder = 1
        object Label18: TLabel
          Left = 16
          Top = 48
          Width = 38
          Height = 13
          Caption = 'Label18'
        end
        object Label19: TLabel
          Left = 16
          Top = 80
          Width = 38
          Height = 13
          Caption = 'Label19'
        end
        object Label20: TLabel
          Left = 16
          Top = 112
          Width = 38
          Height = 13
          Caption = 'Label20'
        end
        object Label21: TLabel
          Left = 16
          Top = 144
          Width = 38
          Height = 13
          Caption = 'Label21'
        end
        object Label22: TLabel
          Left = 16
          Top = 176
          Width = 38
          Height = 13
          Caption = 'Label22'
        end
        object Label23: TLabel
          Left = 16
          Top = 208
          Width = 38
          Height = 13
          Caption = 'Label23'
        end
        object Label24: TLabel
          Left = 16
          Top = 240
          Width = 38
          Height = 13
          Caption = 'Label24'
        end
        object Label25: TLabel
          Left = 16
          Top = 272
          Width = 38
          Height = 13
          Caption = 'Label25'
        end
        object Label26: TLabel
          Left = 344
          Top = 48
          Width = 38
          Height = 13
          Caption = 'Label26'
        end
        object Label27: TLabel
          Left = 344
          Top = 80
          Width = 38
          Height = 13
          Caption = 'Label27'
        end
        object Label28: TLabel
          Left = 344
          Top = 112
          Width = 38
          Height = 13
          Caption = 'Label28'
        end
        object Label29: TLabel
          Left = 344
          Top = 144
          Width = 38
          Height = 13
          Caption = 'Label29'
        end
        object Label30: TLabel
          Left = 344
          Top = 176
          Width = 38
          Height = 13
          Caption = 'Label30'
        end
        object Label31: TLabel
          Left = 344
          Top = 208
          Width = 38
          Height = 13
          Caption = 'Label31'
        end
        object Label79: TLabel
          Left = 344
          Top = 240
          Width = 38
          Height = 13
          Caption = 'Label79'
        end
        object CheckBox24: TCheckBox
          Left = 120
          Top = 16
          Width = 98
          Height = 18
          Caption = 'CheckBox24'
          TabOrder = 0
        end
        object CheckBox23: TCheckBox
          Left = 8
          Top = 16
          Width = 98
          Height = 18
          Caption = 'CheckBox23'
          TabOrder = 1
        end
        object ScrollBar14: TScrollBar
          Left = 128
          Top = 48
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 2
        end
        object ScrollBar15: TScrollBar
          Left = 128
          Top = 80
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 3
        end
        object ScrollBar16: TScrollBar
          Left = 128
          Top = 112
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 4
        end
        object ScrollBar17: TScrollBar
          Left = 128
          Top = 144
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 5
        end
        object ScrollBar18: TScrollBar
          Left = 128
          Top = 176
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 6
        end
        object ScrollBar19: TScrollBar
          Left = 128
          Top = 208
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 7
        end
        object ScrollBar20: TScrollBar
          Left = 128
          Top = 240
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 8
        end
        object ScrollBar21: TScrollBar
          Left = 128
          Top = 272
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 9
        end
        object ScrollBar22: TScrollBar
          Left = 456
          Top = 48
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 10
        end
        object ScrollBar23: TScrollBar
          Left = 456
          Top = 80
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 11
        end
        object ScrollBar24: TScrollBar
          Left = 456
          Top = 112
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 12
        end
        object ScrollBar25: TScrollBar
          Left = 456
          Top = 144
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 13
        end
        object ScrollBar26: TScrollBar
          Left = 456
          Top = 176
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 14
        end
        object ScrollBar27: TScrollBar
          Left = 456
          Top = 208
          Width = 154
          Height = 18
          PageSize = 0
          TabOrder = 15
        end
        object StaticText14: TStaticText
          Left = 288
          Top = 48
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText14'
          TabOrder = 16
        end
        object StaticText15: TStaticText
          Left = 288
          Top = 80
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText15'
          TabOrder = 17
        end
        object StaticText16: TStaticText
          Left = 288
          Top = 112
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText16'
          TabOrder = 18
        end
        object StaticText17: TStaticText
          Left = 288
          Top = 144
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText17'
          TabOrder = 19
        end
        object StaticText18: TStaticText
          Left = 288
          Top = 176
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText18'
          TabOrder = 20
        end
        object StaticText19: TStaticText
          Left = 288
          Top = 208
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText19'
          TabOrder = 21
        end
        object StaticText20: TStaticText
          Left = 288
          Top = 240
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText20'
          TabOrder = 22
        end
        object StaticText21: TStaticText
          Left = 288
          Top = 272
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText21'
          TabOrder = 23
        end
        object StaticText22: TStaticText
          Left = 616
          Top = 48
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText22'
          TabOrder = 24
        end
        object StaticText23: TStaticText
          Left = 616
          Top = 80
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText23'
          TabOrder = 25
        end
        object StaticText24: TStaticText
          Left = 616
          Top = 112
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText24'
          TabOrder = 26
        end
        object StaticText25: TStaticText
          Left = 616
          Top = 144
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText25'
          TabOrder = 27
        end
        object StaticText26: TStaticText
          Left = 616
          Top = 176
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText26'
          TabOrder = 28
        end
        object StaticText27: TStaticText
          Left = 616
          Top = 208
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText27'
          TabOrder = 29
        end
        object ScrollBar67: TScrollBar
          Left = 456
          Top = 240
          Width = 153
          Height = 17
          PageSize = 0
          TabOrder = 30
        end
        object StaticText67: TStaticText
          Left = 616
          Top = 240
          Width = 64
          Height = 17
          BorderStyle = sbsSunken
          Caption = 'StaticText67'
          TabOrder = 31
        end
        object GroupBox13: TGroupBox
          Left = 16
          Top = 296
          Width = 330
          Height = 62
          TabOrder = 32
          object Label36: TLabel
            Left = 10
            Top = 42
            Width = 26
            Height = 13
            Caption = 'Label'
          end
          object Label82: TLabel
            Left = 8
            Top = 9
            Width = 38
            Height = 13
            Caption = 'Label82'
          end
          object ScrollBar32: TScrollBar
            Left = 120
            Top = 40
            Width = 178
            Height = 18
            PageSize = 0
            TabOrder = 0
          end
          object StaticText32: TStaticText
            Left = 304
            Top = 40
            Width = 52
            Height = 17
            BorderStyle = sbsSunken
            Caption = 'StaticText'
            TabOrder = 1
          end
          object ComboBox14: TComboBox
            Left = 120
            Top = 9
            Width = 209
            Height = 21
            ItemHeight = 0
            TabOrder = 2
            Text = 'ComboBox14'
          end
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'DCR LUT'
      ImageIndex = 4
      object GroupBox10: TGroupBox
        Left = 464
        Top = 32
        Width = 225
        Height = 145
        TabOrder = 0
        object btn_dcr_lut_read: TButton
          Left = 24
          Top = 24
          Width = 82
          Height = 42
          Caption = 'R&ead'
          TabOrder = 0
          OnClick = btn_dcr_lut_readClick
        end
        object btn_dcr_lut_write: TButton
          Left = 120
          Top = 24
          Width = 82
          Height = 42
          Caption = '&Write'
          TabOrder = 1
          OnClick = btn_dcr_lut_writeClick
        end
        object btn_dcr_lut_save: TButton
          Left = 24
          Top = 80
          Width = 82
          Height = 42
          Hint = 'Save as ".txt", digit type "Hex"'
          Caption = '&Save File'
          TabOrder = 2
          OnClick = btn_dcr_lut_saveClick
        end
        object btn_dcr_lut_load: TButton
          Left = 120
          Top = 80
          Width = 82
          Height = 42
          Hint = 
            'Load ".txt" file, Number is "Hex"Save as ".txt", digits type "He' +
            'x"'
          Caption = '&Load File'
          TabOrder = 3
          OnClick = btn_dcr_lut_loadClick
        end
        object edt_seq_addr: TLabeledEdit
          Left = 32
          Top = 152
          Width = 74
          Height = 21
          EditLabel.Width = 63
          EditLabel.Height = 13
          EditLabel.Caption = 'Address(Hex)'
          EditLabel.Font.Charset = DEFAULT_CHARSET
          EditLabel.Font.Color = clBlack
          EditLabel.Font.Height = -12
          EditLabel.Font.Name = 'MS Sans Serif'
          EditLabel.Font.Style = []
          EditLabel.ParentFont = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          LabelPosition = lpAbove
          LabelSpacing = 3
          ParentFont = False
          TabOrder = 4
          Text = '0'
          Visible = False
        end
      end
    end
  end
  object Btn_DCR_reload: TBitBtn
    Left = 8
    Top = 492
    Width = 74
    Height = 26
    Caption = '&Reload'
    ModalResult = 6
    TabOrder = 1
    OnClick = Btn_DCR_reloadClick
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
  end
  object GroupBox40: TGroupBox
    Left = 392
    Top = 490
    Width = 186
    Height = 31
    Caption = 'hiden'
    TabOrder = 2
    Visible = False
    object CheckBox16: TCheckBox
      Left = 48
      Top = 8
      Width = 98
      Height = 18
      Caption = 'CheckBox16'
      TabOrder = 0
      Visible = False
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 232
    Top = 490
  end
  object SaveDialog1: TSaveDialog
    Left = 184
    Top = 490
  end
end
