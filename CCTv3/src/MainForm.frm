VERSION 5.00
Begin VB.Form MainForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "CCT Adjustment V3.13a"
   ClientHeight    =   4680
   ClientLeft      =   120
   ClientTop       =   684
   ClientWidth     =   10320
   Icon            =   "MainForm.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4680
   ScaleWidth      =   10320
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame5 
      Caption         =   "Output File Format"
      Height          =   1092
      Left            =   120
      TabIndex        =   31
      Top             =   2640
      Width           =   3252
      Begin VB.OptionButton Option_OOo 
         Caption         =   "OpenOffice"
         Height          =   372
         Left            =   1560
         TabIndex        =   33
         Top             =   480
         Width           =   1335
      End
      Begin VB.OptionButton Option_MSOffice 
         Caption         =   "MS Office"
         Height          =   372
         Left            =   120
         TabIndex        =   32
         Top             =   480
         Value           =   -1  'True
         Width           =   1092
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "3. Input Source"
      Height          =   3660
      Left            =   3480
      TabIndex        =   9
      Top             =   120
      Width           =   6696
      Begin VB.Frame GaTest_set 
         Caption         =   "Gamma Test Address"
         Height          =   2952
         Left            =   3840
         TabIndex        =   20
         Top             =   600
         Visible         =   0   'False
         Width           =   2772
         Begin VB.ComboBox Com_Tcon_sel 
            Height          =   288
            ItemData        =   "MainForm.frx":030A
            Left            =   120
            List            =   "MainForm.frx":0317
            TabIndex        =   30
            Text            =   "AUO-12401"
            Top             =   300
            Width           =   2085
         End
         Begin VB.ComboBox Com_type 
            Enabled         =   0   'False
            Height          =   288
            ItemData        =   "MainForm.frx":0338
            Left            =   1320
            List            =   "MainForm.frx":0342
            TabIndex        =   29
            Text            =   "AUO-12401"
            Top             =   2520
            Width           =   1428
         End
         Begin VB.TextBox txt_LUT_ST 
            Enabled         =   0   'False
            Height          =   288
            Left            =   1320
            TabIndex        =   23
            Text            =   "4A7"
            Top             =   2040
            Width           =   855
         End
         Begin VB.Frame Frame4 
            Caption         =   "Eable"
            Height          =   1050
            Left            =   120
            TabIndex        =   24
            Top             =   825
            Width           =   2055
            Begin VB.TextBox txt_en_bit 
               Enabled         =   0   'False
               Height          =   288
               Left            =   1080
               TabIndex        =   28
               Text            =   "1"
               Top             =   630
               Width           =   585
            End
            Begin VB.TextBox txt_en_addr 
               Enabled         =   0   'False
               Height          =   288
               Left            =   1080
               TabIndex        =   26
               Text            =   "4A1"
               Top             =   210
               Width           =   585
            End
            Begin VB.Label Label7 
               Caption         =   "bit"
               Height          =   255
               Left            =   330
               TabIndex        =   27
               Top             =   690
               Width           =   390
            End
            Begin VB.Label Label4 
               Caption         =   "Addr"
               Height          =   255
               Left            =   300
               TabIndex        =   25
               Top             =   270
               Width           =   570
            End
         End
         Begin VB.Label Label6 
            Caption         =   "Type"
            Height          =   252
            Left            =   120
            TabIndex        =   22
            Top             =   2520
            Width           =   612
         End
         Begin VB.Label Label5 
            Caption         =   "LUT Start Addr"
            Height          =   252
            Left            =   120
            TabIndex        =   21
            Top             =   2052
            Width           =   1212
         End
      End
      Begin VB.Frame TCON_Set 
         Caption         =   "Device Address"
         Height          =   1800
         Left            =   960
         TabIndex        =   12
         Top             =   600
         Visible         =   0   'False
         Width           =   2775
         Begin VB.CommandButton btn_Reset 
            Caption         =   "Reset"
            Height          =   435
            Left            =   1680
            TabIndex        =   19
            Top             =   1200
            Width           =   915
         End
         Begin VB.CommandButton btn_Connect 
            Caption         =   "Connect"
            Height          =   435
            Left            =   465
            TabIndex        =   18
            Top             =   1200
            Width           =   915
         End
         Begin VB.OptionButton op_dual 
            Caption         =   "Dual TCON"
            Height          =   270
            Left            =   105
            TabIndex        =   17
            Top             =   720
            Width           =   1305
         End
         Begin VB.OptionButton op_single 
            Caption         =   "Single TCON"
            Height          =   285
            Left            =   105
            TabIndex        =   16
            Top             =   255
            Value           =   -1  'True
            Width           =   1290
         End
         Begin VB.TextBox Dev_master 
            Alignment       =   2  'Center
            Height          =   288
            Left            =   1440
            TabIndex        =   15
            Text            =   "7C"
            Top             =   690
            Width           =   615
         End
         Begin VB.TextBox Dev_slave 
            Alignment       =   2  'Center
            Height          =   288
            Left            =   2040
            TabIndex        =   14
            Text            =   "7E"
            Top             =   690
            Width           =   690
         End
         Begin VB.TextBox Dev_single 
            Alignment       =   2  'Center
            Height          =   288
            Left            =   1440
            TabIndex        =   13
            Text            =   "7C"
            Top             =   270
            Width           =   615
         End
      End
      Begin VB.OptionButton op_tcon 
         Caption         =   "T-Con"
         Height          =   360
         Left            =   120
         TabIndex        =   11
         Top             =   720
         Width           =   885
      End
      Begin VB.OptionButton op_pc 
         Caption         =   "PC"
         Height          =   330
         Left            =   120
         TabIndex        =   10
         Top             =   300
         Value           =   -1  'True
         Width           =   1395
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "2. Pattern Display Interval"
      Height          =   1092
      Left            =   120
      TabIndex        =   5
      Top             =   1440
      Width           =   3252
      Begin VB.TextBox IT 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   480
         TabIndex        =   6
         Text            =   "750"
         Top             =   480
         Width           =   612
      End
      Begin VB.Label Label3 
         Caption         =   "Milli-seconds"
         Height          =   252
         Left            =   1320
         TabIndex        =   7
         Top             =   480
         Width           =   972
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "1. Resolution"
      Height          =   1212
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3252
      Begin VB.TextBox Ry 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   960
         TabIndex        =   4
         Text            =   "768"
         Top             =   720
         Width           =   612
      End
      Begin VB.TextBox Rx 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   960
         TabIndex        =   3
         Text            =   "1366"
         Top             =   360
         Width           =   612
      End
      Begin VB.Label Label2 
         Caption         =   "Y"
         Height          =   252
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   252
      End
      Begin VB.Label Label1 
         Caption         =   "X"
         Height          =   252
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   252
      End
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      Caption         =   "Copyright (C) 2005. AU Optronics Corp., All Rights Reserved"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Left            =   1920
      TabIndex        =   8
      Top             =   4200
      Width           =   4395
   End
   Begin VB.Image Image1 
      Height          =   504
      Left            =   240
      Picture         =   "MainForm.frx":035C
      Top             =   3960
      Width           =   1200
   End
   Begin VB.Menu MatrixC 
      Caption         =   "Matrix Calibration"
   End
   Begin VB.Menu RGB校正 
      Caption         =   "Target White"
   End
   Begin VB.Menu GammaTable 
      Caption         =   "CCT(LUT)"
   End
   Begin VB.Menu GammaAdj 
      Caption         =   "GammaAdj"
   End
   Begin VB.Menu Measure 
      Caption         =   "Measurement"
      Begin VB.Menu 灰階量測 
         Caption         =   "Gamma Measurement"
      End
      Begin VB.Menu ManualMeasurement 
         Caption         =   "Manual Measurement"
      End
      Begin VB.Menu StabilityMeasurement 
         Caption         =   "Stability Measurement"
      End
   End
   Begin VB.Menu Minolta 
      Caption         =   "Config"
   End
   Begin VB.Menu ab 
      Caption         =   "About"
   End
   Begin VB.Menu Exit 
      Caption         =   "Exit"
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Algorithm_Click()
    Form2.Show
End Sub

Private Sub ab_Click()
frmAbout.Show
End Sub

Private Sub Com_Tcon_sel_Click()
'Text4.Text = Com_Tcon_sel.Text
Key = Com_Tcon_sel.ListIndex
Select Case Key
Case 0
txt_en_addr.Enabled = False
txt_en_addr.Text = "4A1"
txt_en_bit.Enabled = False
txt_en_bit.Text = "1"
txt_LUT_ST.Enabled = False
txt_LUT_ST.Text = "4A7"
Com_type.Enabled = False
Com_type.ListIndex = 0
Case 1
txt_en_addr.Enabled = False
txt_en_addr.Text = "FF9"
txt_en_bit.Enabled = False
txt_en_bit.Text = "4"
txt_LUT_ST.Enabled = False
txt_LUT_ST.Text = "FFA"
Com_type.Enabled = False
Com_type.ListIndex = 1
Case 2
txt_en_addr.Enabled = True
txt_en_bit.Enabled = True
txt_LUT_ST.Enabled = True
Com_type.Enabled = True
End Select
'Text4.Text = Com_Tcon_sel.ListIndex
End Sub

Private Sub Command1_Click()
Label8.caption = Combo1.Text

End Sub

Private Sub btn_connect_Click()
 '  Addr_dev = Val("&H" & DEV.Text)
'AA = Val("&H" And Dev_single.Text)
If op_single.Value = True Then
Addr_master = Val("&H" & Dev_single.Text)
Else
Addr_master = Val("&H" & Dev_master.Text)
End If
Add_slave = Val("&H" & Dev_slave.Text)
i2c_initial


If MainForm.Com_Tcon_sel.Text = "AUO-12401" Then

    If op_single.Value = True Then
        Write_Byte Addr_master, &H4A1, 2   'Gamma_Test ON
        Write_Byte Addr_master, &H4A7, &HFF 'RH
        Write_Byte Addr_master, &H4A8, &HFF 'RL
        Write_Byte Addr_master, &H4A9, &HFF 'GH
        Write_Byte Addr_master, &H4AA, &HFF 'GL
        Write_Byte Addr_master, &H4AB, &HFF 'BH
        Write_Byte Addr_master, &H4AC, &HFF 'BL
        
    Else
        Write_Byte Addr_master, &H4A1, 2
        Write_Byte Addr_master, &H4A7, &HFF
        Write_Byte Addr_master, &H4A8, &HFF
        Write_Byte Addr_master, &H4A9, &HFF
        Write_Byte Addr_master, &H4AA, &HFF
        Write_Byte Addr_master, &H4AB, &HFF
        Write_Byte Addr_master, &H4AC, &HFF
        
        Write_Byte Add_slave, &H4A1, 2
        Write_Byte Add_slave, &H4A7, &HFF
        Write_Byte Add_slave, &H4A8, &HFF
        Write_Byte Add_slave, &H4A9, &HFF
        Write_Byte Add_slave, &H4AA, &HFF
        Write_Byte Add_slave, &H4AB, &HFF
        Write_Byte Add_slave, &H4AC, &HFF
    End If
ElseIf MainForm.Com_Tcon_sel.Text = "AUO-12403" Then
    Write_Byte Addr_master, &HFF9, 16   'Gamma_Test ON
    Write_Byte Addr_master, &HFFA, &HFF  'RH
    Write_Byte Addr_master, &HFFB, &HFF 'GH * 16 + RL
    Write_Byte Addr_master, &HFFC, &HFF 'GL 'GH
    Write_Byte Addr_master, &HFFD, &HFF 'BL 'GL
    Write_Byte Addr_master, &HFFE, &HF 'BH
    
    
    
    If MainForm.op_single.Value = False Then  ''''''''''Dual TCON
        Write_Byte Add_slave, &HFF9, 16
        Write_Byte Add_slave, &HFFA, &HFF
        Write_Byte Add_slave, &HFFB, &HFF 'GH * 16 + RL
        Write_Byte Add_slave, &HFFC, &HFF 'GL
        Write_Byte Add_slave, &HFFD, &HFF 'BL
        Write_Byte Add_slave, &HFFE, &HF 'BH
    End If



Else
     Add_En = Val("&H" & MainForm.txt_en_addr.Text)
     bit_En = 2 ^ Val(MainForm.txt_en_bit.Text)
     Add_lut = Val("&H" & MainForm.txt_LUT_ST.Text)
    
    If MainForm.Com_type.Text = "AUO-12401" Then
        Write_Byte Addr_master, Add_En, bit_En   'Gamma_Test ON
        Write_Byte Addr_master, Add_lut, &HFF 'RH
        Write_Byte Addr_master, Add_lut + 1, &HFF 'RL
        Write_Byte Addr_master, Add_lut + 2, &HFF 'GH
        Write_Byte Addr_master, Add_lut + 3, &HFF 'GL
        Write_Byte Addr_master, Add_lut + 4, &HFF 'BH
        Write_Byte Addr_master, Add_lut + 5, &HFF 'BL
        
        
        If MainForm.op_single.Value = False Then  ''''''''''Dual TCON
            Write_Byte Add_slave, Add_En, bit_En
            Write_Byte Add_slave, Add_lut, &HFF
            Write_Byte Add_slave, Add_lut + 1, &HFF
            Write_Byte Add_slave, Add_lut + 2, &HFF
            Write_Byte Add_slave, Add_lut + 3, &HFF
            Write_Byte Add_slave, Add_lut + 4, &HFF
            Write_Byte Add_slave, Add_lut + 5, &HFF
        End If
    Else
        
    '''''''''AUO-12403  Gamma Test Address FF9[4] Rh4:4A7 Rl8 4A8
    Write_Byte Addr_master, Add_En, bit_En   'Gamma_Test ON
    Write_Byte Addr_master, Add_lut, &HFF  'RH
    Write_Byte Addr_master, Add_lut + 1, &HFF ' GH * 16 + RL
    Write_Byte Addr_master, Add_lut + 2, &HFF 'GH
    Write_Byte Addr_master, Add_lut + 3, &HFF 'GL
    Write_Byte Addr_master, Add_lut + 4, &HF 'BH
    
    
    
    If MainForm.op_single.Value = False Then  ''''''''''Dual TCON
        Write_Byte Add_slave, Add_En, bit_En
        Write_Byte Add_slave, Add_lut, &HFF
        Write_Byte Add_slave, Add_lut + 1, &HFF 'GH * 16 + RL
        Write_Byte Add_slave, Add_lut + 2, &HFF
        Write_Byte Add_slave, Add_lut + 3, &HFF
        Write_Byte Add_slave, Add_lut + 4, &HF
    End If
    
    End If



End If


End Sub

Private Sub btn_Reset_Click()
If op_single.Value = True Then
    Addr_master = Val("&H" & Dev_single.Text)
Else
    Addr_master = Val("&H" & Dev_master.Text)
End If
    Add_slave = Val("&H" & Dev_slave.Text)

If op_single.Value = True Then
    Write_Byte Addr_master, &H4, &HFF
Else
    Write_Byte Addr_master, &H4, &HFF
    
    Write_Byte Add_slave, &H4, &HFF
End If
End Sub

Private Sub Form_Initialize()

'frmPass.Show
End Sub

Private Sub GammaAdj_Click()
frmGamma.Show
End Sub



Private Sub ManualMeasurement_Click()
Msr_Manual.Show
End Sub

Private Sub MatrixC_Click()
MatrixCalib.Show
End Sub

Private Sub Minolta_Click()
    ConfigForm.Show
End Sub
Private Sub Exit_Click()
    
    If Debug_enable = False And True = UseCA210 Then objCa.RemoteMode = 0
    
    End   '******** End program
End Sub
Private Sub Form_Load()
If 0 Then   ''''''remove password
        Dim i As Integer
            On Error GoTo E
        
        
        
        SCL = 6
        Scl_Level = 0
        SDO = 7
        Sdo_Level = 0
        SDI = 7
        Sdi_Level = 0
        LPTAddressBase = &H378
        LPTOutData = 255
        'i2c_initial ''''op_tcon true
        
        
        
        
        
        
        'Debug_enable = False
        
        
        If Debug_enable = False Then
            MeasureTool.initCA210
        
'        Set objCa200 = New Ca200
'            objCa200.AutoConnect
'
'        Set objCa = objCa200.SingleCa
'        Set objProbe = objCa.SingleProbe
'        Set objMemory = objCa.Memory
'
'
'
'            SyncM1 = 0
'            MR1 = 2
'            DM1 = 0
'
'        objCa.SyncMode = SyncM1
'        objCa.AveragingMode = MR1
        End If
        
        MainForm.Show
        
        
        
        If GetKeyState(vbKeyEscape) And &H1 = &H1 Then
            keystate(vbKeyEscape) = 0
            Rval = SetKeyboardState(keystate(vbKeyEscape))
        End If
            
            px = Screen.Width
            ppx = Screen.TwipsPerPixelX
            plx = px / ppx
            
                py = Screen.Height
                ppy = Screen.TwipsPerPixelY
                ply = py / ppy
            
            MainForm.Rx = plx
            MainForm.Ry = ply
         Exit Sub
        
        
E:
           
            Dim strERR As String
            Dim iReturn As Integer
            
            strERR = "Error from " + Err.Source + Chr$(10) + Chr$(13)
            strERR = strERR + Err.Description + Chr$(10) + Chr$(13)
            strERR = strERR + "HRESULT " + CStr(Err.Number - vbObjectError)
            iReturn = MsgBox(strERR, vbRetryCancel)
            Select Case iReturn
                Case vbRetry: Resume
                Case Else:
               If Debug_enable = False Then objCa.RemoteMode = 0
        
                    End
            End Select
End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If Debug_enable = False And Not objCa Is Nothing Then
        objCa.RemoteMode = 0
    End If  '******** End program
End Sub


Private Sub GammaTable_Click()
    GTable.Show
End Sub

Private Sub op_pc_Click()
TCON_Set.visible = False
GaTest_set.visible = False
GrayTest.FSL.Text = 255
'GrayTest.op_msr_8bit.Value = True
'GrayTest.op_msr_8bit.Enabled = True
GrayTest.op_msr_10bit.Enabled = False
GrayTest.op_msr_12bit.Enabled = False
GTable.GSL.Text = 255
GrayTest.user_define.visible = False
GrayTest.pc_input.visible = True
'X = MsgBox("Please Turn Off DG and Turn On FRC for Measurement when PC Input Source is selected!!!", vbExclamation + vbOKOnly)

End Sub

Private Sub op_tcon_Click()

TCON_Set.visible = True
GaTest_set.visible = True
'GTable.GSL.Text = 1023
GrayTest.FSL.Text = 4095
  
GrayTest.op_msr_12bit.Value = True
'GrayTest.op_msr_8bit.Enabled = False
GrayTest.op_msr_10bit.Enabled = True
GrayTest.op_msr_12bit.Enabled = True
GrayTest.user_define.visible = True

'GrayTest.user_define.Visible = False
GrayTest.pc_input.visible = False
'If GTable.op_10bit2 = True Then
'    GTable.GSL.Text = 1023
'    GrayTest.FSL.Text = 1023
'Else
'    GTable.GSL.Text = 4095
'    GrayTest.FSL.Text = 4095

x = MsgBox("Please Turn On DG and FRC for Measurement when T-con Input Source is selected!!!", vbExclamation + vbOKOnly)
'End If
End Sub

 

Private Sub Option_MSOffice_Click()
    Module1.sheetType = OpType.Excel
End Sub

Private Sub Option_OOo_Click()
    Module1.sheetType = OpType.Calc
End Sub

Private Sub RGB校正_Click()
    RGBcal.Show
End Sub

Private Sub TEST1_Click()
FormTest.Show
End Sub

 

Private Sub StabilityMeasurement_Click()
YStableTime.Show
End Sub



Private Sub 灰階量測_Click()
    GrayTest.Show
End Sub

Private Sub 單色量測_Click()
    GrayRGBTest.Show
End Sub

Private Sub 暗階修正_Click()
DTableFix.Show
End Sub
