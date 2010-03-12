VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form GTable 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "CCT (LUT)"
   ClientHeight    =   6000
   ClientLeft      =   156
   ClientTop       =   432
   ClientWidth     =   11736
   Icon            =   "GTable.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6000
   ScaleWidth      =   11736
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame16 
      Caption         =   "7. B Max"
      Height          =   1095
      Left            =   9720
      TabIndex        =   58
      Top             =   2160
      Width           =   1455
      Begin VB.CheckBox chk_BMax 
         Caption         =   "Enable"
         Height          =   255
         Left            =   240
         TabIndex        =   59
         Top             =   480
         Width           =   855
      End
   End
   Begin VB.Frame Frame15 
      Caption         =   "6. B Intensity Gain"
      Height          =   1815
      Left            =   6840
      TabIndex        =   50
      Top             =   2160
      Width           =   2775
      Begin VB.CheckBox chk_BGain 
         Caption         =   "Enable"
         Height          =   375
         Left            =   480
         TabIndex        =   64
         Top             =   240
         Width           =   1335
      End
      Begin VB.Frame Frame4 
         Height          =   855
         Left            =   360
         TabIndex        =   60
         Top             =   720
         Width           =   2055
         Begin VB.TextBox Text4 
            Height          =   375
            Left            =   1320
            TabIndex        =   62
            Text            =   "236"
            Top             =   840
            Visible         =   0   'False
            Width           =   495
         End
         Begin VB.TextBox Text3 
            Height          =   375
            Left            =   1200
            TabIndex        =   61
            Text            =   "1.05"
            Top             =   360
            Width           =   495
         End
         Begin VB.Label Label11 
            Caption         =   "Gain"
            Height          =   255
            Left            =   360
            TabIndex        =   63
            Top             =   360
            Width           =   495
         End
      End
   End
   Begin VB.Frame Frame14 
      Caption         =   "4. Low Level Correction"
      Height          =   1695
      Left            =   7245
      TabIndex        =   41
      Top             =   345
      Width           =   4425
      Begin VB.Frame Frame13 
         Caption         =   "Selection"
         Height          =   1215
         Left            =   225
         TabIndex        =   51
         Top             =   240
         Width           =   1830
         Begin VB.OptionButton op_rb_interp 
            Caption         =   "RB Interp"
            Height          =   255
            Left            =   240
            TabIndex        =   53
            Top             =   720
            Width           =   1455
         End
         Begin VB.OptionButton op_p1p2 
            Caption         =   "P1 P2"
            Height          =   375
            Left            =   240
            TabIndex        =   52
            Top             =   240
            Value           =   -1  'True
            Width           =   1335
         End
      End
      Begin VB.Frame FrameRB 
         Caption         =   "RB Interp"
         Height          =   975
         Left            =   2175
         TabIndex        =   47
         Top             =   360
         Visible         =   0   'False
         Width           =   1815
         Begin VB.TextBox txt_RB_Interp 
            Height          =   288
            Left            =   1080
            TabIndex        =   48
            Text            =   "50"
            Top             =   480
            Width           =   615
         End
         Begin VB.Label Label3 
            Caption         =   "Interp Level"
            Height          =   255
            Left            =   120
            TabIndex        =   49
            Top             =   480
            Width           =   975
         End
      End
      Begin VB.Frame FrameP1P2 
         Caption         =   "P1P2"
         Height          =   975
         Left            =   2175
         TabIndex        =   42
         Top             =   360
         Width           =   1815
         Begin VB.TextBox TEXT_P1 
            Alignment       =   2  'Center
            Height          =   270
            Left            =   840
            TabIndex        =   44
            Text            =   "20"
            Top             =   240
            Width           =   615
         End
         Begin VB.TextBox TEXT_P2 
            Alignment       =   2  'Center
            Height          =   270
            Left            =   840
            TabIndex        =   43
            Text            =   "50"
            Top             =   585
            Width           =   615
         End
         Begin VB.Label Label4 
            Caption         =   "Point 1"
            Height          =   255
            Left            =   240
            TabIndex        =   46
            Top             =   285
            Width           =   495
         End
         Begin VB.Label Label8 
            Caption         =   "Point 2"
            Height          =   255
            Left            =   240
            TabIndex        =   45
            Top             =   645
            Width           =   495
         End
      End
   End
   Begin VB.Frame Frame8 
      Caption         =   "5. Bit Depth"
      Height          =   2265
      Left            =   2760
      TabIndex        =   31
      Top             =   2040
      Width           =   3840
      Begin VB.Frame Frame9 
         Caption         =   "In"
         Height          =   1455
         Left            =   240
         TabIndex        =   54
         Top             =   240
         Width           =   1020
         Begin VB.OptionButton op_in_10 
            Caption         =   "10"
            Height          =   255
            Left            =   120
            TabIndex        =   57
            Top             =   960
            Width           =   615
         End
         Begin VB.OptionButton op_in_8 
            Caption         =   "8"
            Height          =   255
            Left            =   120
            TabIndex        =   56
            Top             =   600
            Value           =   -1  'True
            Width           =   750
         End
         Begin VB.OptionButton op_in_6 
            Caption         =   "6"
            Height          =   255
            Left            =   120
            TabIndex        =   55
            Top             =   240
            Width           =   615
         End
      End
      Begin VB.CheckBox chk_frc2 
         Caption         =   "Avoid FRC Noise"
         Enabled         =   0   'False
         Height          =   315
         Left            =   1845
         TabIndex        =   40
         Top             =   1800
         Width           =   1575
      End
      Begin VB.CheckBox chk_ga256 
         Caption         =   "Gamma256"
         Height          =   375
         Left            =   465
         TabIndex        =   39
         Top             =   1785
         Width           =   1290
      End
      Begin VB.Frame Frame11 
         Caption         =   "Out"
         Height          =   1455
         Left            =   2580
         TabIndex        =   33
         Top             =   240
         Width           =   1020
         Begin VB.OptionButton op_out_10 
            Caption         =   "10"
            Enabled         =   0   'False
            Height          =   255
            Left            =   120
            TabIndex        =   38
            Top             =   960
            Width           =   615
         End
         Begin VB.OptionButton op_out_8 
            Caption         =   "8"
            Height          =   255
            Left            =   120
            TabIndex        =   37
            Top             =   600
            Value           =   -1  'True
            Width           =   615
         End
         Begin VB.OptionButton op_out_6 
            Caption         =   "6"
            Height          =   255
            Left            =   120
            TabIndex        =   36
            Top             =   240
            Width           =   615
         End
      End
      Begin VB.Frame Frame10 
         Caption         =   "LUT"
         Height          =   1455
         Left            =   1395
         TabIndex        =   32
         Top             =   240
         Width           =   1020
         Begin VB.OptionButton op_12bit2 
            Caption         =   "12 bit"
            Height          =   255
            Left            =   120
            TabIndex        =   35
            Top             =   600
            Width           =   735
         End
         Begin VB.OptionButton op_10bit2 
            Caption         =   "10 bit"
            Height          =   255
            Left            =   120
            TabIndex        =   34
            Top             =   240
            Value           =   -1  'True
            Width           =   735
         End
      End
   End
   Begin MSComDlg.CommonDialog cmdDiag 
      Left            =   7785
      Top             =   5400
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton btn_debug 
      Caption         =   "Debug"
      Height          =   825
      Left            =   7470
      TabIndex        =   20
      Top             =   4200
      Visible         =   0   'False
      Width           =   1350
   End
   Begin VB.Frame Frame1 
      Caption         =   "Bit Depth"
      Height          =   1950
      Left            =   12480
      TabIndex        =   19
      Top             =   2280
      Width           =   4455
      Begin VB.Frame Frame7 
         Caption         =   "LUT Option"
         Height          =   1545
         Left            =   3075
         TabIndex        =   28
         Top             =   225
         Width           =   1245
         Begin VB.OptionButton op_12bit 
            Caption         =   "12 bit"
            Height          =   360
            Left            =   165
            TabIndex        =   30
            Top             =   810
            Value           =   -1  'True
            Width           =   885
         End
         Begin VB.OptionButton op_10bit 
            Caption         =   "10 bit"
            Height          =   315
            Left            =   165
            TabIndex        =   29
            Top             =   330
            Width           =   900
         End
      End
      Begin VB.Frame Frame6 
         Caption         =   "Panel Option"
         Height          =   1545
         Left            =   120
         TabIndex        =   22
         Top             =   240
         Width           =   2925
         Begin VB.CheckBox Chk_frc 
            Caption         =   "Avoid FRC Noise"
            Enabled         =   0   'False
            Height          =   315
            Left            =   1260
            TabIndex        =   27
            Top             =   840
            Width           =   1575
         End
         Begin VB.OptionButton Option3 
            Caption         =   " 6 + 2 FRC"
            Height          =   255
            Left            =   165
            TabIndex        =   26
            Top             =   1155
            Width           =   1680
         End
         Begin VB.OptionButton Option2 
            Caption         =   " 6 + 3 FRC"
            Height          =   255
            Left            =   165
            TabIndex        =   25
            Top             =   870
            Width           =   1320
         End
         Begin VB.OptionButton Option1 
            Caption         =   " 8 + 2 FRC"
            Height          =   255
            Left            =   165
            TabIndex        =   24
            Top             =   585
            Width           =   1320
         End
         Begin VB.OptionButton Option4 
            Caption         =   "10 + 2 FRC"
            Height          =   180
            Left            =   165
            TabIndex        =   23
            Top             =   330
            Value           =   -1  'True
            Width           =   1650
         End
      End
   End
   Begin VB.Frame Frame5 
      Caption         =   "3. Gamma"
      Height          =   1455
      Left            =   4545
      TabIndex        =   16
      Top             =   360
      Width           =   2565
      Begin VB.CheckBox chk_gbypass 
         Caption         =   "G bypass"
         Height          =   300
         Left            =   1440
         TabIndex        =   65
         Top             =   870
         Visible         =   0   'False
         Width           =   960
      End
      Begin VB.CommandButton btn_loadG 
         Caption         =   "Load Gamma"
         Height          =   360
         Left            =   45
         TabIndex        =   21
         Top             =   840
         Width           =   1200
      End
      Begin VB.TextBox Text_Ga 
         Alignment       =   2  'Center
         Height          =   270
         Left            =   480
         TabIndex        =   17
         Text            =   "2.4"
         Top             =   360
         Width           =   675
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "10. Auto Run"
      Height          =   735
      Left            =   9480
      TabIndex        =   15
      Top             =   4560
      Width           =   1500
   End
   Begin VB.Frame Frame3 
      Caption         =   "2. Target W Channel"
      Height          =   1260
      Left            =   2805
      TabIndex        =   13
      Top             =   360
      Width           =   1590
      Begin VB.TextBox TCH 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   600
         TabIndex        =   14
         Text            =   "2"
         Top             =   360
         Width           =   612
      End
   End
   Begin VB.TextBox SAL 
      Height          =   264
      Left            =   2160
      TabIndex        =   10
      Text            =   "D:\Gamma Table\"
      Top             =   5040
      Width           =   4875
   End
   Begin VB.TextBox SAFN 
      Height          =   264
      Left            =   2160
      TabIndex        =   9
      Text            =   "Calib00_Table"
      Top             =   4440
      Width           =   1572
   End
   Begin VB.Frame Frame2 
      Caption         =   "1. Gray Level Option"
      Height          =   2730
      Left            =   120
      TabIndex        =   0
      Top             =   360
      Width           =   2532
      Begin VB.TextBox GLS 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   1905
         TabIndex        =   6
         Text            =   "0"
         Top             =   2040
         Width           =   192
      End
      Begin VB.TextBox GEL 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   1590
         TabIndex        =   2
         Text            =   "0"
         Top             =   1380
         Width           =   612
      End
      Begin VB.TextBox GSL 
         Alignment       =   2  'Center
         Height          =   264
         Left            =   1560
         TabIndex        =   1
         Text            =   "255"
         Top             =   615
         Width           =   612
      End
      Begin VB.Label GLST 
         Caption         =   "1"
         Height          =   255
         Left            =   1410
         TabIndex        =   12
         Top             =   2220
         Width           =   210
      End
      Begin VB.Label Label7 
         Caption         =   "2"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   10.8
            Charset         =   136
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1785
         TabIndex        =   11
         Top             =   2280
         Width           =   255
      End
      Begin VB.Label Label1 
         Caption         =   "Gray Level Step"
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   2220
         Width           =   1215
      End
      Begin VB.Label Label6 
         Caption         =   "End Gray Level"
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   1425
         Width           =   1335
      End
      Begin VB.Label Label5 
         Caption         =   "Start Gray Level"
         Height          =   255
         Left            =   240
         TabIndex        =   3
         Top             =   615
         Width           =   1215
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
      Left            =   2400
      TabIndex        =   18
      Top             =   5640
      Width           =   4395
   End
   Begin VB.Label Label10 
      Caption         =   "9. Save As Location"
      Height          =   255
      Left            =   480
      TabIndex        =   8
      Top             =   5040
      Width           =   1455
   End
   Begin VB.Label Label9 
      Caption         =   "8. Save As File Name"
      Height          =   255
      Left            =   480
      TabIndex        =   7
      Top             =   4440
      Width           =   1590
   End
End
Attribute VB_Name = "GTable"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Const GLT = 256
Dim DesiredGamma(1024) As Single
Dim DesiredGammaR(1024) As Single
Dim DesiredGammaG(1024) As Single
Dim DesiredGammaB(1024) As Single

Public Enum enuDataGroup
    DG_Sample = 0
    DG_Default = DG_Sample
    DG_Population = 1
End Enum


Private Sub btn_loadG_Click()
    Dim fm As String, fnum As Integer, fname As String
    'Dim iCheck As Integer
    
    'iCheck = MsgBox("Are you sure to load file to CA-210", vbOKCancel)
    
    'If iCheck = 2 Then
    'Exit Sub
    'End If
    
    On Error Resume Next
    cmdDiag.CancelError = True
    cmdDiag.filename = "*.xls"
    cmdDiag.Filter = "Normalizaed Gamma data (*.xls)|*.xls"
    cmdDiag.FilterIndex = 2
    cmdDiag.Action = 1
    If Err.Number = cdlCancel Then
        Exit Sub
    Else
        fm = cmdDiag.filename
        'fm = Mid$(fm, 1, InStr(1, fm, ".")) + "xls"
    End If
    
    fname = Dir$(fm, vbNormal Or vbReadOnly)
    If fname = "" Then
        MsgBox "No File", vbOKOnly
        Exit Sub
    Else
    End If
    
    Dim xlApp As Excel.Application '定義EXCEL類
    Dim xlBook As Excel.workbook '定義工件簿類
    Dim xlsheet As Excel.Worksheet '定義工作表類
    
    Set xlApp = CreateObject("Excel.Application") '創建EXCEL應用類
    xlApp.visible = False '設置EXCEL不可見
    Set xlBook = xlApp.Workbooks.Open(fm) '打開EXCEL工作簿
    Set xlsheet = xlBook.Worksheets(1) '打開EXCEL工作表
    xlsheet.Activate '啟動工作表
    If chk_ga256.Value = 1 Then
        con_num = 256
    Else
        con_num = 255
    End If
    
    For i = 0 To con_num
        DesiredGamma(i) = xlsheet.Cells(i + 2, 2)
        DesiredGammaR(i) = xlsheet.Cells(i + 2, 3)
        DesiredGammaG(i) = xlsheet.Cells(i + 2, 4)
        DesiredGammaB(i) = xlsheet.Cells(i + 2, 5)
    Next i
    flag_LoadG = True
    chk_gbypass.visible = True
End Sub


Private Sub Command2_Click() '''''''AUTORUN
    ' 某種flag?
    Go_ahead = True
    
    MainForm.WindowState = vbMinimized
    '''''''''' Parameter
    ' =============================================================================
    ' 處理step與level的部份
    ' =============================================================================
    'gray level step
    If GLS > 0 Then
        ' gray start level
        StartG = Val(GSL) + 1
    Else
        StartG = Val(GSL)
    End If
    
    ' gray end level
    EndG = Val(GEL)
    ' gray level step
    STP = 2 ^ Val(GLS)
    ' =============================================================================
    
    
    If ((chk_ga256.Value = 1) And (op_in_10.Value = True)) Then
        max_c = 256
    ElseIf (op_in_6.Value = True And op_out_6.Value = True) Then
        max_c = 252
    Else
        max_c = 255
    End If
    
    '''''' Record Original Data    Measurement
    
    
    ''''''''''''''''Test Remove recipe by stockton 12/14
    If ((chk_ga256.Value = 1) And (op_in_10.Value = True)) Then
        GLT = 257
    ElseIf (op_in_6.Value = True And op_out_6.Value = True) Then
        GLT = 253
    Else
        GLT = 256
    End If
    
    
    
    Background.BKIGL = 0
    Background.BKA = 0
    
    ' =============================================================================
    ' excel r/w
    ' =============================================================================
    ''''''''' Open Index File
    Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
    
    sheet.setSheetIndex 1
    sheet.cell(1, 1) = "Gray Level"
    sheet.cell(1, 2) = "Gamma R"
    sheet.cell(1, 3) = "Gamma G"
    sheet.cell(1, 4) = "Gamma B"
    sheet.setSheetIndex 2
    sheet.cell(1, 1) = "Gray Level"
    sheet.cell(1, 2) = "W_x"
    sheet.cell(1, 3) = "W_y"
    sheet.cell(1, 4) = "W_Y (nit)"
    sheet.cell(1, 5) = "W_R"
    sheet.cell(1, 6) = "W_G"
    sheet.cell(1, 7) = "W_B"
    ' =============================================================================
    
    
    ' =============================================================================
    ' CA-210 setup
    ' =============================================================================
    '''''' Record Original Data    Measurement
    objCa.RemoteMode = 1
    objMemory.ChannelNO = TCH
    ' =============================================================================
    
    ''''''''''''''''Test Remove recipe by stockton 12/14
    
    Dim Lx(1024) As Double
    Dim Ly(1024) As Double
    Dim YYN(1024) As Double
    Dim RN(1024) As Double
    Dim GN(1024) As Double
    Dim BN(1024) As Double
    Dim YYR(1024) As Single
    
    Dim Lgain(1024) As Single
    
    Dim YYP(1024) As Single
    Dim RP(1024) As Single
    Dim GP(1024) As Single
    Dim BP(1024) As Single
    
    Dim index(1024) As Single
    
    Dim RL(1024) As Single
    Dim GL(1024) As Single
    Dim BL(1024) As Single
    Dim GrayL(1024) As Single
    Dim GL_tmp(1024) As Single
    If (MainForm.op_pc.Value = True) Then
        Call PatternI(GSL)
    Else
        Call PatternI(GSL * 4)
    End If
    
    row1 = 1
    
    If MainForm.op_pc.Value = True Then
        Background.setShow
    End If
    
    ' 停10s
    Tims (10)
    Call RGBcal.CA210(Cx, Cy, Y255)
    'If MainForm.op_pc.Value = True Then
    Call Background.BGShow1(255, Y255, 0)
    'End If
    
    ' =========================================================================
    ' 將灰階量測並儲存結果到excel
    ' =========================================================================
    sheet.setSheetIndex 2
    For GLX = StartG To EndG Step -STP
        x = GLX
        
        If ((chk_ga256.Value = 1) And (op_in_10.Value = True)) Then
            If x > 1023 Then x = 1023
        Else
            If x > 255 Then x = 255
        End If
        
        GrayL(row1 - 1) = x
        If (MainForm.op_pc.Value = True) Then
            Call PatternI(x)
        Else
            Call PatternI(x * 4)
        End If
        
        Call RGBcal.CAData210(Cx, Cy, Yx, LR, LG, LB)
        Call Background.BGShow2(x, Yx, 0)
        row1 = row1 + 1
        ' x y Y R G B
        Lx(row1 - 2) = Cx 'L(0)=L255
        Ly(row1 - 2) = Cy
        YYN(row1 - 2) = Yx
        RN(row1 - 2) = LR
        GN(row1 - 2) = LG
        BN(row1 - 2) = LB
        
        ' 2擺的是raw data
        sheet.cell(row1, 1) = x
        sheet.cell(row1, 2) = Cx
        sheet.cell(row1, 3) = Cy
        sheet.cell(row1, 4) = Yx
        sheet.cell(row1, 5) = LR
        sheet.cell(row1, 6) = LG
        sheet.cell(row1, 7) = LB
        
    Next GLX
    ' =========================================================================
    
    
    '''''''''''''''Data Normalize Remove Recipe by Stockton 12/14
    Dim n As Integer
    n = row1 - 1
    ' Ymin一定是code 0...為什麼還要用變數指定?
    Ymin = YYN(n - 1)
    ' =========================================================================
    ' Correct_Error_MeasureData
    ' 做了怎樣的修正? 反正是0不用看了
    ' =========================================================================
    If 0 Then
        For i = 0 To n - 2
            YTmax = 0
            RTmax = 0
            GTmax = 0
            BTmax = 0
            If i + 2 <= n - 1 Then
                For j = i + 2 To n - 1
                    If YTmax < YYN(j) Then YTmax = YYN(j)
                    If RTmax < RN(j) Then RTmax = RN(j)
                    If GTmax < GN(j) Then GTmax = GN(j)
                    If BTmax < BN(j) Then BTmax = BN(j)
                Next j
                '''''''''''''YY
                If YYN(i) < YYN(i + 1) Or YYN(i) < YTmax Then
                    If YYN(i) < YYN(i + 1) And YYN(i + 1) > YTmax Then
                        YYN(i + 1) = (YYN(i) + YYN(i + 2)) / 2
                    Else
                        YYN(i) = YTmax
                    End If
                    If YYN(i) > YYN(i + 1) And YYN(i) < YTmax Then YYN(i) = YTmax
                End If
                ''''''''''''' R
                If RN(i) < RN(i + 1) Or RN(i) < RTmax Then
                    If RN(i) < RN(i + 1) And RN(i + 1) > RTmax Then
                        RN(i + 1) = (RN(i) + RN(i + 2)) / 2
                    Else
                        RN(i) = RTmax
                    End If
                    If RN(i) > RN(i + 1) And RN(i) < RTmax Then RN(i) = RTmax
                End If
                '''''''''''' G
                If GN(i) < GN(i + 1) Or GN(i) < GTmax Then
                    If GN(i) < GN(i + 1) And GN(i + 1) > GTmax Then
                        GN(i + 1) = (GN(i) + GN(i + 2)) / 2
                    Else
                        GN(i) = GTmax
                    End If
                    If GN(i) > GN(i + 1) And GN(i) < GTmax Then GN(i) = GTmax
                End If
                '''''''''''' B
                If BN(i) < BN(i + 1) Or BN(i) < BTmax Then
                    If BN(i) < BN(i + 1) And BN(i + 1) > BTmax Then
                        BN(i + 1) = (BN(i) + BN(i + 2)) / 2
                    Else
                        BN(i) = BTmax
                    End If
                    If BN(i) > BN(i + 1) And BN(i) < BTmax Then BN(i) = BTmax
                End If
            Else
                ''''''' YY
                If YYN(i) < YYN(i + 1) Then
                    Ytemporal = YYN(i)
                    YYN(i) = YYN(i + 1)
                    YYN(i + 1) = Ytemporal
                End If
                ''''''' RR
                If RN(i) < RN(i + 1) Then
                    Rtemporal = RN(i)
                    RN(i) = RN(i + 1)
                    RN(i + 1) = Rtemporal
                End If
                ''''''' GG
                If GN(i) < GN(i + 1) Then
                    Gtemporal = GN(i)
                    GN(i) = GN(i + 1)
                    GN(i + 1) = Gtemporal
                End If
                ''''''' BB
                If BN(i) < BN(i + 1) Then
                    Btemporal = BN(i)
                    BN(i) = BN(i + 1)
                    BN(i + 1) = Btemporal
                End If
            End If
        Next i
    End If
    ' =========================================================================
    
    ' =========================================================================
    ' regress 回歸免看
    ' =========================================================================
    '''''''''''''''Regress Y remove recipe by Stockton 12/14
    ''''''''' Regression Y
    ' 用字串做回歸?!?!?
    Dim RegressData As String
    RegressData = Empty
    K = 4 ' For 3 independent variable Y= R G B
    '''''''' YYN
    RegressData = YYN(0)
    For i = 1 To n - 1
        RegressData = RegressData & "," & YYN(i)
    Next i
    '''''''' RN
    For i = 0 To n - 1
        RegressData = RegressData & "," & RN(i)
    Next i
    '''''''' GN
    For i = 0 To n - 1
        RegressData = RegressData & "," & GN(i)
    Next i
    '''''''' BN
    For i = 0 To n - 1
        RegressData = RegressData & "," & BN(i)
    Next i
    
    ' 看起來是以 Y1Y2...R1R2...G1G2...B1B2的方式把所有數字串起來
    
    Call MultipleRegress(RegressData, n)
    ' =========================================================================
    
    
    '''''''''''''' Precdit Y Remove Recipe by Stockton 12/14
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ''''''''' Predict Y
    Dim rr As String, Gr As String, Br As String, YR As String
    rr = Empty
    YR = Empty
    rr = 1
    ' Beta是MultipleRegress的結果
    YR = Beta(1, 1) + Beta(2, 1) * 1 + Beta(3, 1) * 1 + Beta(4, 1) * 1
    
    ' 用意是?
    For SRC = 2 To GLT
        If SRC <= Round(RN(0), 0) And SRC <= Round(GN(0), 0) And SRC <= Round(BN(0), 0) Then
            ' 倘若SRC同時 <= RN/GN/BN (四捨五入後)
            YYR(SRC) = Beta(1, 1) + Beta(2, 1) * SRC + Beta(3, 1) * SRC + Beta(4, 1) * SRC
            rr = rr & "," & SRC
            YR = YR & "," & YYR(SRC)
            
        Else
            Exit For
        End If
    Next SRC
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    
    '''''''''''''' Regress RGB Remove Recipe by Stockton 12/14
    Dim RRP As String, GRP As String, BRP As String
    RRP = Empty
    'GRP = Empty
    'BRP = Empty
    
    ' 把經過上面處理的Rr YR湊起來, 拿來做回歸
    RRP = rr & "," & YR
    Call SimpleRegress(RRP)
    RBeta1 = Beta1
    RBeta2 = Beta2
    RRsq = Rsqs
    
    
    '''''''''''''' Lookup Table
    Unload Background
    
    ' =========================================================================
    ' 產生目標亮度
    ' =========================================================================
    
    '''''''''''''' Predict RGB Remove Recipe by Stockton 12/14 TEST OK
    If flag_LoadG = False Then
        ' 若沒有load G
        ' 根據in/out決定的maximum值來產生gamma
        If ((chk_ga256.Value = 1) And (op_in_10.Value = True)) Then
            For i = 0 To 256
                DesiredGamma(i) = ((256 - i) / 256) ^ Val(Text_Ga.Text)
                'DesiredGamma(i) = ((1023 - i * 4) / 1023) ^ Val(Text_Ga.Text)
            Next i
        ElseIf (op_out_6.Value = True And op_in_6.Value = True) Then
            
            For i = 0 To 252
                DesiredGamma(i) = ((252 - i) / 252) ^ Val(Text_Ga.Text)
            Next i
        Else
            
            For i = 0 To 255 '''''Normal Case
                'Lgain(i) = ((255 - i) / 255) ^ Val(Text_Ga.Text)
                DesiredGamma(i) = ((255 - i) / 255) ^ Val(Text_Ga.Text)
                'RSDC = RSDC + 1
            Next i
        End If
    End If
    
    'For i = 0 To 255
    '    Lgain(i) = ((255 - i) / 255) ^ Val(Text_Ga.Text)
    'RSDC = RSDC + 1
    'Next i
    ' =========================================================================
    
    ''''''''''here
    
    ' =========================================================================
    ' 從目標亮度算出RGB亮度
    ' =========================================================================
    For i = 0 To max_c
        ' 計算出目標亮度值
        ' DesiredGamma是反的, YYP自然也是反的
        YYP(i) = (YYR(SRC - 1) - YYN(n - 1)) * DesiredGamma(i) + YYN(n - 1)
        'YYP(i) = (YYR(SRC - 1) - YYN(n - 1)) * Lgain(i) + YYN(n - 1)
        'YYP(i) = (YYR(SRC - 1) - YYN(n - 1)) * (i / 255) ^ 2.4 + YYN(n - 1)
        ' 藉由回歸的數值產生RP GP BP
        RP(i) = RBeta1 + RBeta2 * YYP(i)
        GP(i) = RBeta1 + RBeta2 * YYP(i)
        BP(i) = RBeta1 + RBeta2 * YYP(i)
    Next i
    ' =========================================================================
    
    '==========================================================================
    ' 從亮度產生出code
    '==========================================================================
    For i = 0 To max_c
        
        ' Text4預設是236, temp_diff會是19
        temp_diff = 255 - Val(Text4.Text) ''''' B Intensity Gain
        ' 計算出來的第i個BP值
        temp_bbb = BP(i)
        
        ' =========================================================================
        ' B Gain的處理, 是處理B目標亮度
        ' =========================================================================
        
        If chk_BGain.Value = 1 Then
            ' 如果gain為1 (就是開啟gain!?)
            If i >= (temp_diff) Then
                '19以上 其實就是236以下 (0~236)
                BP(i) = BP(i) * Val(Text3.Text) '''' Gain
            Else
                '19以下 其實就是236以上 (236~255)
                ' 19thBP*gain+(100-19thBP*gain)/(255-236)*(19-i)
                ' 起始亮度 + (殘餘亮度)/(code區間*殘餘code)
                ' 起始亮度 + (殘餘亮度)/(code區間*19)
                ' 起始亮度 + (殘餘亮度)/(code區間*18) ??
                BP(i) = BP(temp_diff) * Val(Text3.Text) + (100 - BP(temp_diff) * Val(Text3.Text)) / (255 - Val(Text4.Text)) * (temp_diff - i)
                'BP(i) = BP(i) * Val(Text3.Text)
            End If
        End If
        ' =========================================================================
        
        'BKR = 1000
        'BKG = 1000
        'BKB = 1000
        
        
        
        ' =========================================================================
        ' jj似乎擔當了甚麼起點的作用
        ' =========================================================================
        ''''''''''''''''10 bit Gamma  by Stockton
        ' gray level step
        If GLS = 0 Then '1
            jj = 4
        ElseIf GLS = 1 Then '2
            jj = 3
        ElseIf GLS = 2 Then '4
            jj = 2
        Else
            jj = 1 '??
        End If
        ' =========================================================================
        
        '==========================================================================
        ' R (RN是量測到的R亮度)
        '==========================================================================
        ''''''R
        'If ((Option1.Value = True) Or (Option4.Value = True)) Then
        If ((op_in_10.Value = True) Or (op_in_8.Value = True) Or (op_in_6.Value = True)) Then
            For j = 0 To n - 1
                errorR = (RP(i) - RN(j))
                ' 若R的差異>0則跳出回圈!?
                If errorR > 0 Then Exit For
            Next j
        Else
            ' 差異僅在jj........
            For j = jj To n - 1
                errorR = (RP(i) - RN(j))
                If errorR > 0 Then Exit For
            Next j
        End If
        
        If j - 1 < 0 Then
            indexRR = GrayL(0)
        Else
            ' 線性內插, j 似乎由上面的迴圈找出來的, i是當下處理的code
            indexRR = GrayL(j) + (RP(i) - RN(j)) / (RN(j - 1) - RN(j)) * (GrayL(j - 1) - GrayL(j))
        End If
        
        
        If (op_10bit2.Value = True) Then
            'If ((Option1.Value = True) Or (Option4.Value = True)) Then
            If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                RL(i) = Round(indexRR * 4, 0)
            Else
                RL(i) = Round(indexRR * 2, 0) * 2
            End If
        Else
            'If ((Option1.Value = True) Or (Option4.Value = True)) Then
            If (op_out_10.Value = True) Then
                If MainForm.op_pc.Value = True Then
                    RL(i) = Round(indexRR * 16, 0) '''''''10+2
                Else
                    RL(i) = Round(indexRR * 4, 0)
                End If
            ElseIf (op_out_8.Value = True) Then
                If MainForm.op_pc.Value = True Then
                    RL(i) = Round(indexRR * 8, 0) * 2
                Else
                    RL(i) = Round(indexRR * 2, 0) * 2
                End If
            Else
                RL(i) = Round(indexRR * 8, 0) * 2
            End If
        End If
        'If Option2.Value = True Then RL(i) = Round(indexRR * 2, 0) * 2
        
        'If Option3.Value = True Then RL(i) = Round(indexRR / 255 * 1008, 0)
        '==========================================================================
        
        '==========================================================================
        ' G
        '==========================================================================
        ''''''G
        'If ((Option1.Value = True) Or (Option4.Value = True)) Then
        If ((op_in_10.Value = True) Or (op_in_8.Value = True) Or (op_in_6.Value = True)) Then
            For j = 0 To n - 1
                errorG = (GP(i) - GN(j))
                If errorG > 0 Then Exit For
            Next j
        Else
            For j = jj To n - 1
                errorG = (GP(i) - GN(j))
                If errorG > 0 Then Exit For
            Next j
        End If
        If j - 1 < 0 Then
            indexGG = GrayL(0)
        Else
            
            indexGG = GrayL(j) + (GP(i) - GN(j)) / (GN(j - 1) - GN(j)) * (GrayL(j - 1) - GrayL(j))
        End If
        
        
        If (op_10bit2.Value = True) Then
            'If ((Option1.Value = True) Or (Option4.Value = True)) Then
            If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                GL(i) = Round(indexGG * 4, 0)
            Else
                GL(i) = Round(indexGG * 2, 0) * 2
            End If
        Else
            'If ((Option1.Value = True) Or (Option4.Value = True)) Then
            If (op_out_10.Value = True) Then
                If MainForm.op_pc.Value = True Then
                    GL(i) = Round(indexGG * 16, 0)
                Else
                    GL(i) = Round(indexGG * 4, 0)
                End If
            ElseIf (op_out_8.Value = True) Then
                If MainForm.op_pc.Value = True Then
                    GL(i) = Round(indexGG * 8, 0) * 2
                Else
                    GL(i) = Round(indexGG * 2, 0) * 2
                End If
            Else
                GL(i) = Round(indexGG * 8, 0) * 2
            End If
        End If
        'If Option2.Value = True Then GL(i) = Round(indexGG * 2, 0) * 2
        
        'If Option3.Value = True Then GL(i) = Round(indexGG / 255 * 1008, 0)
        
        '==========================================================================
        ' B
        '==========================================================================
        If ((op_in_10.Value = True) Or (op_in_8.Value = True) Or (op_in_6.Value = True)) Then
            If True Then
                ''''''''''B sorting from minimum to abord B hook reverse
                For j = n - 1 To 0 Step -1
                    errorB = (BP(i) - BN(j))
                    If errorB < 0 Then Exit For
                Next j
                
            Else
                
                For j = 0 To n - 1
                    errorB = (BP(i) - BN(j))
                    If errorB > 0 Then Exit For
                Next j
            End If
        Else
            For j = jj To n - 1
                errorB = (BP(i) - BN(j))
                If errorB > 0 Then Exit For
            Next j
        End If
        
        If j - 1 < 0 Then
            indexBB = GrayL(0)
        Else
            '    indexBB = GrayL(j) + (BP(i) - BN(j)) / (BN(j - 1) - BN(j)) * (GrayL(j - 1) - GrayL(j))   '''''''上到下
            indexBB = GrayL(j) - (BN(j) - BP(i)) / (BN(j) - BN(j + 1)) * (GrayL(j) - GrayL(j + 1)) '''''''下到上
        End If
        
        If (op_10bit2.Value = True) Then
            'If ((Option1.Value = True) Or (Option4.Value = True)) Then
            If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                BL(i) = Round(indexBB * 4, 0)
            Else
                BL(i) = Round(indexBB * 2, 0) * 2
            End If
        Else
            'If ((Option1.Value = True) Or (Option4.Value = True)) Then
            If (op_out_10.Value = True) Then
                If MainForm.op_pc.Value = True Then
                    BL(i) = Round(indexBB * 16, 0)
                Else
                    BL(i) = Round(indexBB * 4, 0)
                End If
            ElseIf (op_out_8.Value = True) Then
                If MainForm.op_pc.Value = True Then
                    BL(i) = Round(indexBB * 8, 0) * 2
                Else
                    BL(i) = Round(indexBB * 2, 0) * 2
                End If
            Else
                BL(i) = Round(indexBB * 8, 0) * 2
            End If
        End If
        '==========================================================================
        
        'If Option2.Value = True Then BL(i) = Round(indexBB * 2, 0) * 2
        
        'If Option3.Value = True Then BL(i) = Round(indexBB / 255 * 1008, 0)
        
    Next i
    '==========================================================================
    
    
    RL(max_c) = 0
    GL(max_c) = 0
    BL(max_c) = 0
    ''''Low Gray Level fix Add by Stockton 10/19/2005
    Dim P1 As Integer
    Dim P2 As Integer
    Dim RL2(1024) As Double
    Dim GL2(1024) As Double
    Dim BL2(1024) As Double
    Dim RP2(1024) As Double
    Dim GP2(1024) As Double
    Dim BP2(1024) As Double
    Dim RN2(1024) As Double
    Dim GN2(1024) As Double
    Dim BN2(1024) As Double
    '==========================================================================
    ' RL GL BL是產生的DG code, RP GP BP 是目標亮度 (免看)
    '==========================================================================
    '目標亮度 YYP
    '目標RGB亮度 RP/GP/BP
    '量測亮度(component) RN/GN/BN
    'DGCode RL/GL/BL
    For i = 0 To max_c
        '反轉處理了, why?
        RL2(i) = RL(max_c - i)
        GL2(i) = GL(max_c - i)
        BL2(i) = BL(max_c - i)
        RP2(i) = RP(max_c - i)
        GP2(i) = GP(max_c - i)
        BP2(i) = BP(max_c - i)
        
    Next i
    sheet.cell(1, 8) = "RP"
    sheet.cell(1, 9) = "GP"
    sheet.cell(1, 10) = "BP"
    For i = 0 To max_c
        
        sheet.cell(i + 2, 8) = RP(i)
        sheet.cell(i + 2, 9) = GP(i)
        sheet.cell(i + 2, 10) = BP(i)
    Next i
    
    '==========================================================================
    ' P1P2
    '==========================================================================
    ' P1P2 start
    If op_p1p2.Value = True Then
        
        P1 = Val(TEXT_P1.Text)
        P2 = Val(TEXT_P2.Text)
        
        
        '''''P1P2
        
        
        If P2 > 0 Then ''''P2<=0  BYPASS
        
            '==================================================================
            ' 處理了R&B
            '==================================================================
    '目標亮度 YYP
    '目標RGB亮度 RP/GP/BP
    '量測亮度(component) RN/GN/BN
    'DGCode RL/GL/BL
            temp_g = GL2(P1) '原本P1下的G的DG Code
            i = 0
            Do
                diff_r = RL2(i) - temp_g
                If diff_r > 0 Then '找到r比temp_g大的index值
                    index_r = i
                    Exit Do
                End If
                i = i + 1
            Loop
            i = 0
            Do
                diff_b = BL2(i) - temp_g
                If diff_b > 0 Then '找到b比temp_g大的index值
                    index_b = i
                    Exit Do
                End If
                i = i + 1
            Loop
            
            'P1點的處理
            RP2(P1) = RP2(index_r) + (RP2(index_r + 1) - RP2(index_r)) * (temp_g - RL2(index_r)) / (RL2(index_r + 1) - RL2(index_r))
            BP2(P1) = BP2(index_b) + (BP2(index_b + 1) - BP2(index_b)) * (temp_g - BL2(index_b)) / (BL2(index_b + 1) - BL2(index_b))
            '==================================================================
            
            
            
            
            
            '==================================================================
            ' P1-P2 Gamma變化
            '==================================================================
            '''''''''P1-P2 成Gamma變化  讓他急遽變化一點
    '目標亮度 YYP
    '目標RGB亮度 RP/GP/BP
    '量測亮度(component) RN/GN/BN
    'DGCode RL/GL/BL
            For i = P1 + 1 To P2 - 1
                Gratio = (GP2(i) - GP2(P1)) / (GP2(P2) - GP2(P1))
                RP2(i) = RP2(P1) + (RP2(P2) - RP2(P1)) * Gratio
                
                BP2(i) = BP2(P1) + (BP2(P2) - BP2(P1)) * Gratio
                
            Next i
            '==================================================================
            
            '==================================================================
            ' 複製而以? 免看
            '==================================================================
            For i = 0 To max_c
                RL(i) = RL2(max_c - i)
                GL(i) = GL2(max_c - i)
                BL(i) = BL2(max_c - i)
                RP(i) = RP2(i)
                GP(i) = GP2(i)
                BP(i) = BP2(i)
                
            Next i
            '==================================================================
            
            '==================================================================
            ' 把RP GP BP填到excel(免看)
            '==================================================================
            ' 因為P1P2修了RPGPBP, 所以目標亮度跟著改變了
            sheet.cell(1, 11) = "RP_Intensity_Fix"
            sheet.cell(1, 12) = "GP_Intensity_Fix"
            sheet.cell(1, 13) = "BP_Intensity_Fix"
            For i = 0 To max_c
                
                sheet.cell(i + 2, 11) = RP(i)
                sheet.cell(i + 2, 12) = GP(i)
                sheet.cell(i + 2, 13) = BP(i)
            Next i
            '==================================================================
            
            '==================================================================
            ' 亮度轉DG Code(重複,免看)
            '==================================================================
            '頭到尾都作了處理
            For i = 0 To max_c
                
                '==================================================================
                ' R
                '==================================================================
                '找j
                For j = 0 To n - 1
                    errorR = (RP(i) - RN(j))
                    If errorR > 0 Then Exit For
                Next j
                
                '找indexRR
                If j - 1 < 0 Then
                    indexRR = GrayL(0)
                Else
                    indexRR = GrayL(j) + (RP(i) - RN(j)) / (RN(j - 1) - RN(j)) * (GrayL(j - 1) - GrayL(j))
                End If
                
                'RL由indexRR產出
                If (op_10bit2.Value = True) Then
                    'If ((Option1.Value = True) Or (Option4.Value = True)) Then
                    If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                        RL(i) = Round(indexRR * 4, 0)
                    Else
                        RL(i) = Round(indexRR * 2, 0) * 2
                    End If
                Else
                    'If ((Option1.Value = True) Or (Option4.Value = True)) Then
                    If (op_out_10.Value = True) Then
                        If MainForm.op_pc.Value = True Then
                            RL(i) = Round(indexRR * 16, 0)
                        Else
                            RL(i) = Round(indexRR * 4, 0)
                        End If
                    ElseIf (op_out_8.Value = True) Then
                        If MainForm.op_pc.Value = True Then
                            RL(i) = Round(indexRR * 8, 0) * 2
                        Else
                            RL(i) = Round(indexRR * 2, 0) * 2
                        End If
                    Else
                        RL(i) = Round(indexRR * 8, 0) * 2
                    End If
                End If
                'If Option2.Value = True Then RL(i) = Round(indexRR * 2, 0) * 2
                
                'If Option3.Value = True Then RL(i) = Round(indexRR / 255 * 1008, 0)
                '==================================================================
                
                '==================================================================
                ' G (R&G完全相同)
                '==================================================================
                ''''''G
                For j = 0 To n - 1
                    errorG = (GP(i) - GN(j))
                    If errorG > 0 Then Exit For
                Next j
                
                If j - 1 < 0 Then
                    indexGG = GrayL(0)
                Else
                    indexGG = GrayL(j) + (GP(i) - GN(j)) / (GN(j - 1) - GN(j)) * (GrayL(j - 1) - GrayL(j))
                End If
                
                If (op_10bit2.Value = True) Then
                    'If ((Option1.Value = True) Or (Option4.Value = True)) Then
                    If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                        GL(i) = Round(indexGG * 4, 0)
                    Else
                        GL(i) = Round(indexGG * 2, 0) * 2
                    End If
                Else
                    
                    If (op_out_10.Value = True) Then
                        If MainForm.op_pc.Value = True Then
                            GL(i) = Round(indexGG * 16, 0)
                        Else
                            GL(i) = Round(indexGG * 4, 0)
                        End If
                    ElseIf (op_out_8.Value = True) Then
                        If MainForm.op_pc.Value = True Then
                            GL(i) = Round(indexGG * 8, 0) * 2
                        Else
                            GL(i) = Round(indexGG * 2, 0) * 2
                        End If
                    Else
                        GL(i) = Round(indexGG * 8, 0) * 2
                    End If
                End If
                '==================================================================
                
                'If Option2.Value = True Then GL(i) = Round(indexGG * 2, 0) * 2
                
                'If Option3.Value = True Then GL(i) = Round(indexGG / 255 * 1008, 0)
                
                '==================================================================
                ' B
                '==================================================================
                If ((op_in_10.Value = True) Or (op_in_8.Value = True) Or (op_in_6.Value = True)) Then
                    ' 除了6 8 10還有其他選項嗎? 所以此block一定會被執行到
                    If True Then
                        '為了修正hook, 方向相反了!?
                        ''''''''''B sorting from minimum to abord B hook reverse
                        For j = n - 1 To 0 Step -1
                            errorB = (BP(i) - BN(j))
                            If errorB < 0 Then Exit For
                        Next j
                        
                    Else '不會執行到此
                        
                        For j = 0 To n - 1
                            errorB = (BP(i) - BN(j))
                            If errorB > 0 Then Exit For
                        Next j
                    End If
                Else '不會執行到此
                    For j = jj To n - 1
                        errorB = (BP(i) - BN(j))
                        If errorB > 0 Then Exit For
                    Next j
                End If
                
                ' 此處以下B與R&G相同
                If j - 1 < 0 Then
                    indexBB = GrayL(0)
                Else
                    '    indexBB = GrayL(j) + (BP(i) - BN(j)) / (BN(j - 1) - BN(j)) * (GrayL(j - 1) - GrayL(j))   '''''''上到下
                    indexBB = GrayL(j) - (BN(j) - BP(i)) / (BN(j) - BN(j + 1)) * (GrayL(j) - GrayL(j + 1)) '''''''下到上
                    
                End If
                
                If (op_10bit2.Value = True) Then
                    'If ((Option1.Value = True) Or (Option4.Value = True)) Then
                    If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                        BL(i) = Round(indexBB * 4, 0)
                    Else
                        BL(i) = Round(indexBB * 2, 0) * 2
                    End If
                Else
                    'If ((Option1.Value = True) Or (Option4.Value = True)) Then
                    If (op_out_10.Value = True) Then
                        If MainForm.op_pc.Value = True Then
                            BL(i) = Round(indexBB * 16, 0)
                        Else
                            BL(i) = Round(indexBB * 4, 0)
                        End If
                    ElseIf (op_out_8.Value = True) Then
                        
                        If MainForm.op_pc.Value = True Then
                            BL(i) = Round(indexBB * 8, 0) * 2
                        Else
                            BL(i) = Round(indexBB * 2, 0) * 2
                        End If
                    Else
                        BL(i) = Round(indexBB * 8, 0) * 2
                    End If
                End If
                '==================================================================
                
                'If Option2.Value = True Then BL(i) = Round(indexBB * 2, 0) * 2
                
                'If Option3.Value = True Then BL(i) = Round(indexBB / 255 * 1008, 0)
                
            Next i
            '==================================================================
            
            
            '==================================================================
            ' 0-P1 線性
            '==================================================================
            '''''Linear
    '目標亮度 YYP
    '目標RGB亮度 RP/GP/BP
    '量測亮度(component) RN/GN/BN
    'DGCode RL/GL/BL
            For i = 0 To P1
                
                'If ((Option1.Value = True) Or (Option4.Value = True)) Then
                If ((op_in_10.Value = True) Or (op_in_8.Value = True)) Then
                    
                    LowG = Round(i * temp_g / P1, 0)
                Else
                    LowG = Round(Round(i * temp_g / P1, 0) / 2, 0) * 2
                End If
                RL(i) = LowG
                GL(i) = LowG
                BL(i) = LowG
                
            Next i
            
            
            
        End If
        
        '==================================================================
        ' smooth
        '==================================================================
        ''''Smoonth
        If op_in_6.Value = True Then
            
            RL(P1) = Round(Round((RL(P1 - 1) + RL(P1 + 1)) / 2, 0) / 2, 0) * 2
            GL(P1) = Round(Round((GL(P1 - 1) + GL(P1 + 1)) / 2, 0) / 2, 0) * 2
            BL(P1) = Round(Round((BL(P1 - 1) + BL(P1 + 1)) / 2, 0) / 2, 0) * 2
            
        Else
            
            RL(P1) = Round((RL(P1 - 1) + RL(P1 + 1)) / 2, 0)
            GL(P1) = Round((GL(P1 - 1) + GL(P1 + 1)) / 2, 0)
            BL(P1) = Round((BL(P1 - 1) + BL(P1 + 1)) / 2, 0)
        End If
        '==================================================================
        
        
        
        '''' for 6+3 Low Gray Fix by Stockton 2007/01/29
        If P2 > 0 Then
            
            '==========================================================================
            If 0 Then '免看
                If ((op_in_8.Value = True) And (op_out_6.Value = True)) Then
                    
                    For i = P2 To 2 Step -1
                        temp = GL(i)
                        GL_tmp(i - 1) = temp - 4
                        diff = GL_tmp(i - 1) - GL(i - 1)
                        RL(i - 1) = RL(i - 1) + diff
                        BL(i - 1) = BL(i - 1) + diff
                        GL(i - 1) = GL_tmp(i - 1)
                        
                    Next i
                    'If (1) Then
                    For i = 4 To 1 Step -1
                        GL(i) = GL(i + 1) - Round(Round(GL(5) / 5, 0) / 2, 0) * 2
                        RL(i) = GL(i)
                        BL(i) = GL(i)
                    Next i
                    GL(5) = (GL(6) + GL(4)) / 2
                    BL(5) = GL(5)
                    RL(5) = GL(5)
                    'End If
                    
                    
                    RL(P2) = Round(((RL(P2 + 1) + RL(P2 - 1)) / 2) / 2, 0) * 2
                    
                    BL(P2) = Round(((BL(P2 + 1) + BL(P2 - 1)) / 2) / 2, 0) * 2
                    
                    
                    For i = 1 To 255
                        If GL(i) > 1008 Then GL(i) = 1008
                        If RL(i) > 1008 Then RL(i) = 1008
                        If BL(i) > 1008 Then BL(i) = 1008
                    Next i
                    For i = 1 To 254
                        If ((GL(i) - GL(i - 1)) <= 0) Then GL(i) = Round(((GL(i - 1) + GL(i + 1)) / 2) / 2, 0) * 2
                        If ((RL(i) - RL(i - 1)) <= 0) Then RL(i) = Round(((RL(i - 1) + RL(i + 1)) / 2) / 2, 0) * 2
                        If ((BL(i) - BL(i - 1)) <= 0) Then BL(i) = Round(((BL(i - 1) + BL(i + 1)) / 2) / 2, 0) * 2
                        If RL(i) < 0 Then RL(i) = 0
                        If GL(i) < 0 Then GL(i) = 0
                        If BL(i) < 0 Then BL(i) = 0
                    Next i
                    
                    
                End If
            End If
            '==========================================================================
            
            Dim up_limit(5) As Integer
            
            Dim down_limit(1) As Integer
            
            down_limit(0) = 4
            down_limit(1) = 12
            
            up_limit(0) = 994
            up_limit(1) = 996
            up_limit(2) = 998
            up_limit(3) = 1002
            up_limit(4) = 1004
            up_limit(5) = 1006
            
            '==========================================================================
            ' avoid FRC noise
            '==========================================================================
            ''''avoid FRC Noise
            If chk_frc2.Value = 1 Then
                
                '==========================================================================
                ' High code
                '==========================================================================
                
                '''''''''''''''''''''High Level
                'up_limit(0) = 994
                
                If ((RL(255) - up_limit(0)) >= 0) Then
                    '若r[255]>=994
                    
                    '強制設定255~253
                    RL(255) = 1008
                    RL(254) = 1000
                    RL(253) = 992
                    
                    For K = 252 To 0 Step -1
                        If ((RL(K) - RL(K + 1)) >= 0) Then
                            '若r[k] >= r[k+1] 反轉?
                            RL(K) = RL(K + 1) - 2
                        Else
                            Exit For
                        End If
                        
                    Next K
                End If
                
                If ((GL(255) - up_limit(0)) >= 0) Then
                    
                    GL(255) = 1008
                    GL(254) = 1000
                    GL(253) = 992
                    
                    For K = 252 To 0 Step -1
                        If ((GL(K) - GL(K + 1)) >= 0) Then
                            GL(K) = GL(K + 1) - 2
                        Else
                            Exit For
                        End If
                        
                    Next K
                End If
                
                If ((BL(255) - up_limit(0)) >= 0) Then
                    
                    BL(255) = 1008
                    BL(254) = 1000
                    BL(253) = 992
                    
                    For K = 252 To 0 Step -1
                        If ((BL(K) - BL(K + 1)) >= 0) Then
                            BL(K) = BL(K + 1) - 2
                        Else
                            Exit For
                        End If
                        
                    Next K
                End If
                '==========================================================================
                
                '==========================================================================
                ' Low Code
                '==========================================================================
                
                ''''''''''''''''''Low Level
                For L = 1 To 30
                    
                    
                    If RL(L) = 12 Then
                        '12修成10, why?
                        RL(L) = 10
                        '若r(L-1) == r(L)則r(L-1)-=2
                        If RL(L - 1) = RL(L) Then RL(L - 1) = RL(L - 1) - 2
                        '若<0則設為0
                        If RL(L - 1) < 0 Then RL(L - 1) = 0
                    End If
                    
                    If GL(L) = 12 Then
                        GL(L) = 10
                        If GL(L - 1) = GL(L) Then GL(L - 1) = GL(L - 1) - 2
                        If GL(L - 1) < 0 Then GL(L - 1) = 0
                    End If
                    
                    If BL(L) = 12 Then
                        BL(L) = 10
                        If BL(L - 1) = BL(L) Then BL(L - 1) = BL(L - 1) - 2
                        If BL(L - 1) < 0 Then BL(L - 1) = 0
                    End If
                    
                    
                    If RL(L) = 4 Then
                        '4修成2
                        RL(L) = 2
                        If RL(L - 1) = RL(L) Then RL(L - 1) = RL(L - 1) - 2
                        If RL(L - 1) < 0 Then RL(L - 1) = 0
                    End If
                    
                    
                    If GL(L) = 4 Then
                        GL(L) = 2
                        If GL(L - 1) = GL(L) Then GL(L - 1) = GL(L - 1) - 2
                        If GL(L - 1) < 0 Then GL(L - 1) = 0
                    End If
                    
                    If BL(L) = 4 Then
                        BL(L) = 2
                        If BL(L - 1) = BL(L) Then BL(L - 1) = BL(L - 1) - 2
                        If BL(L - 1) < 0 Then BL(L - 1) = 0
                    End If
                    
                    'If RL(L) = 12 Then RL(L) = 10
                Next L
                '==========================================================================
            End If
            '==========================================================================
            
        End If
        
        
        
        
        
        '==========================================================================
        ' BMax
        '==========================================================================
        If chk_BMax.Value = 1 Then ''''''''''''''''    BMax
            
            If op_10bit2.Value = True Then
                
                If op_out_6.Value = True Then
                    BL(255) = 1008
                Else
                    BL(255) = 1020
                End If
                
            Else
                If op_out_8.Value = True Then
                    BL(255) = 4080
                Else
                    BL(255) = 4092
                End If
                
            End If
            
            For i = 255 To 0 Step -1 '由大到小
    '目標亮度 YYP
    '目標RGB亮度 RP/GP/BP
    '量測亮度(component) RN/GN/BN
    'DGCode RL/GL/BL
                If i > 252 Then
                    diff = 10
                ElseIf i > 232 Then
                    diff = 8
                Else
                    diff = 6
                End If
                
                If op_12bit2.Value = True Then
                    
                    diff = diff * 4
                    
                End If
                
                temp_b = BL(i)
                
                If (BL(i) - BL(i - 1)) > 0 Then '若沒有反轉
                    BL(i - 1) = BL(i) - diff
                Else
                    '若反轉? 是這樣嗎?
                    BL(i) = Round((BL(i + 1) + BL(i - 1)) / 2, 0)
                    Exit For
                    
                End If
            Next i
            
        End If
        '==========================================================================
        
        '==========================================================================
        ' G ByPass
        '==========================================================================
        If chk_gbypass.Value = 1 Then
            If op_in_8.Value = True Then
                If op_out_6.Value = True Then
                    For i = 0 To 244
                        GL(i) = i * 4
                    Next i
                    For i = 245 To 250
                        GL(i) = GL(i - 1) + 2
                        
                    Next i
                    For i = 251 To 255
                        GL(i) = GL(i - 1) + 4
                        
                    Next i
                End If
            End If
            
            If op_in_6.Value = True Then
                If op_out_6.Value = True Then
                    For i = 0 To 252
                        GL(i) = i * 4
                    Next i
                    
                    For i = 252 To 255
                        GL(i) = 1008
                        
                    Next i
                End If
            End If
            
            
        End If
        '==========================================================================
        
        
        '======================================================================
        ' 寫到excel 免看
        '======================================================================
        sheet.setSheetIndex 1
        If P2 > 0 Then
            For i = 0 To max_c
                sheet.cell(i + 2, 1) = i
                sheet.cell(i + 2, 2) = RL(i)
                sheet.cell(i + 2, 3) = GL(i)
                sheet.cell(i + 2, 4) = BL(i)
            Next i
            
        Else
            
            For i = 0 To max_c
                sheet.cell(i + 2, 1) = i
                sheet.cell(i + 2, 2) = RL(max_c - i)
                sheet.cell(i + 2, 3) = GL(max_c - i)
                sheet.cell(i + 2, 4) = BL(max_c - i)
            Next i
        End If
        '======================================================================
        
    '==========================================================================
    Else '''''''''P1P2 End
    '==========================================================================
    ' RB Interp
    '==========================================================================
    '目標亮度 YYP
    '目標RGB亮度 RP/GP/BP
    '量測亮度(component) RN/GN/BN
    'DGCode RL/GL/BL
        ''RB Interpolation
        'P3指的是RB的under, 預設為50
        P3 = Val(txt_RB_Interp.Text)
        If op_in_6.Value = True Then
            ccc = 252
        Else
            ccc = 255
        End If
        
        'temp_index為255-50=205 (預設狀況)
        temp_index = ccc - P3
        'RL/GL/BL為code, interval為205下的dgcode/50
        R_interval = RL(temp_index) / P3
        G_interval = GL(temp_index) / P3
        B_interval = BL(temp_index) / P3
        
        '處理0~under區間?
        For i = 0 To P3
            '全部round為整數(可能是因為值域為0~1020)
            RL(255 - i) = Round(i * R_interval, 0)
            GL(255 - i) = Round(i * G_interval, 0)
            BL(255 - i) = Round(i * B_interval, 0)
        Next i
        
        
        '======================================================================
        ' B Max
        '======================================================================
        If chk_BMax.Value = 1 Then '''''''''''''''''Bmax
            If op_10bit2.Value = True Then
                If op_out_6.Value = True Then
                    tmp_max = 1008
                Else
                    tmp_max = 1020
                End If
            Else
                If op_out_8.Value = True Then
                    tmp_max = 4080
                Else
                    tmp_max = 4092
                End If
                
                
            End If
            
            If BL(0) < tmp_max Then
                
                If op_10bit2.Value = True Then
                    
                    If op_out_6.Value = True Then
                        BL(0) = 1008
                    Else
                        BL(0) = 1020
                    End If
                    
                Else
                    If op_out_8.Value = True Then
                        BL(0) = 4080
                    Else
                        BL(0) = 4092
                    End If
                    
                End If
                
                For i = 0 To 255
                    
                    
                    If i < 4 Then
                        diff = 10
                    ElseIf i < 12 Then
                        diff = 8
                    Else
                        diff = 6
                    End If
                    
                    If op_12bit2.Value = True Then
                        
                        diff = diff * 4
                        
                    End If
                    temp_b = BL(i)
                    
                    If (BL(i) - BL(i + 1)) > 0 Then
                        BL(i + 1) = BL(i) - diff
                    Else
                        BL(i) = Round((BL(i + 1) + BL(i - 1)) / 2, 0)
                        Exit For
                        
                    End If
                Next i
            End If
        End If
        '======================================================================
        
        
        '==========================================================================
        ' 寫入到excel...免看
        '==========================================================================
        sheet.setSheetIndex 1
        For i = 0 To max_c
            sheet.cell(i + 2, 1) = i
            '反過來寫?255 254 253...0
            sheet.cell(i + 2, 2) = RL(max_c - i)
            sheet.cell(i + 2, 3) = GL(max_c - i)
            sheet.cell(i + 2, 4) = BL(max_c - i)
        Next i
        '==========================================================================
        
        
    End If 'Low Level Correct end
    '==========================================================================
    
    
    If (op_in_6.Value = True) Then
        sheet.setSheetIndex 1
        For i = 0 To 2
            sheet.cell(255 + i, 2) = sheet.cell(254, 2)
            sheet.cell(255 + i, 3) = sheet.cell(254, 3)
            sheet.cell(255 + i, 4) = sheet.cell(254, 4)
        Next i
    End If
    
    
    '==========================================================================
    ' gamma256的處理
    '==========================================================================
    '''''''Copy Gamma256 for 8in 8out gamma256
    If ((op_in_8.Value = True) And (op_out_8.Value = True) And (chk_ga256.Value = 1)) Then
        sheet.setSheetIndex 1
        sheet.cell(258, 1) = 256
        sheet.cell(258, 2) = RL(255)
        sheet.cell(258, 3) = GL(255)
        sheet.cell(258, 4) = BL(255)
        
    End If
    
    If ((op_in_10.Value = True) And (op_out_10.Value = True) And (chk_ga256.Value = 1)) Then
        sheet.setSheetIndex 1
        If sheet.cell(258, 2) > 4092 Then sheet.cell(258, 2) = 4092
        If sheet.cell(258, 3) > 4092 Then sheet.cell(258, 3) = 4092
        If sheet.cell(258, 4) > 4092 Then sheet.cell(258, 4) = 4092
    End If
    '==========================================================================
    
    sheet.setSheetIndex 1
    sheet.setSheetName "Gamma Table"
    
    Utils.changeColorAnd sheet
    
    sheet.setSheetIndex 2
    sheet.setSheetName "Raw Data"
    
    '''''''''''''' Save Data
    sheet.setSheetFilename (SAL & SAFN)
    sheet.store
    sheet.closing
    
    'ETime = Time  '''''''''' Timer
    'MsgBox "Start Time - End Time : " & STime & " - " & ETime
    'EndG:
    
    
    GTable.Show
    
End Sub




Private Sub Form_Load()
    flag_LoadG = False
    If Calib_CH <> 0 Then TCH.Text = Str(Calib_CH)
    If Debug_enable = True Then btn_debug.visible = True
    If MainForm.op_pc.Value = True Then GTable.GSL.Text = 255
End Sub

Private Sub GLS_Change()
    If Val(GLS) = 0 Or Val(GLS) > 8 Then
        'MsgBox "The Step 最小為 0  最大為 8 !!"
        GLS = 0
    End If
    GLST = 2 ^ Val(GLS)
End Sub




Private Sub op_10bit_Click()
    
    GTable.GSL.Text = 1023
    GrayTest.FSL.Text = 1023
    
End Sub

Private Sub op_12bit_Click()
    
    GTable.GSL.Text = 4095
    GrayTest.FSL.Text = 4095
    
End Sub

Private Sub op_in_10_Click()
    op_out_6.Enabled = False
    op_out_10.Enabled = True
    op_out_8.Enabled = True
    op_10bit2.Enabled = False
    op_out_8.Value = True
    op_12bit2.Value = True
    If MainForm.op_tcon.Value = True Then
        GSL = 1023
        GLS = 2
    Else
        GSL = 255
        GLS = 0
    End If
    
    chk_ga256.Value = 1
    'If op_out_8.Value = True Then
    chk_frc2.Enabled = False
    
End Sub

Private Sub op_in_6_Click()
    op_out_6.Enabled = True
    op_10bit2.Enabled = True
    op_10bit2.Value = True
    op_12bit2.Enabled = False
    op_out_10.Enabled = False
    op_out_8.Enabled = False
    op_out_6.Value = True
    'op_out_8.Enabled = False
    'If op_out_8.Value = True Then
    GSL = 255
    GLS = 0
    chk_ga256.Value = 0
    chk_frc2.Enabled = True
    GSL.Text = 252
    GLS.Text = 2
    
    'End If
End Sub

Private Sub op_in_8_Click()
    op_out_6.Enabled = True
    op_10bit2.Enabled = True
    op_12bit2.Enabled = True
    op_10bit2.Value = True
    op_out_10.Enabled = False
    op_out_8.Value = True
    op_out_8.Enabled = True
    'If op_out_8.Value = True Then
    GSL = 255
    GLS = 0
    'End If
    
    chk_ga256.Value = 0
    chk_frc2.Enabled = True
    
    
End Sub

Private Sub op_out_10_Click()
    If MainForm.op_pc Then
        GSL.Text = 255
        GLS.Text = 0
    Else
        GSL.Text = 1023
        GLS.Text = 2
    End If
End Sub

Private Sub op_out_6_Click()
    GSL.Text = 252
    If op_in_6.Value = True Then
        GLS.Text = 2
    Else
        GLS.Text = 0
    End If
End Sub

Private Sub op_out_8_Click()
    If MainForm.op_pc Then
        GSL.Text = 255
        GLS.Text = 0
    Else
        GSL.Text = 1023
        GLS.Text = 2
    End If
End Sub

Private Sub op_p1p2_Click()
    FrameP1P2.visible = True
    FrameRB.visible = False
End Sub

Private Sub op_rb_interp_Click()
    
    FrameP1P2.visible = False
    FrameRB.visible = True
End Sub

Private Sub Option1_Click()
    Chk_frc.Enabled = False
    Chk_frc.Value = 0
End Sub

Private Sub Option2_Click()
    
    Chk_frc.Enabled = True
    'frc_counter = frc_counter + 1
End Sub

Private Sub Option3_Click()
    Chk_frc.Enabled = False
    Chk_frc.Value = 0
End Sub

Private Sub Option5_Click()
    Frame4.visible = True
    Frame12.visible = False
End Sub

Private Sub Option6_Click()
    Frame4.visible = False
    Frame12.visible = True
End Sub
