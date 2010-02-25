VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "mscomm32.ocx"
Begin VB.Form RGBcal 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Target White"
   ClientHeight    =   7680
   ClientLeft      =   120
   ClientTop       =   408
   ClientWidth     =   11520
   Icon            =   "RGBcal.frx":0000
   LinkTopic       =   "Form5"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   7680
   ScaleWidth      =   11520
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame2 
      Caption         =   "2. Auto Matrix Calibration"
      Height          =   4440
      Left            =   120
      TabIndex        =   14
      Top             =   2535
      Width           =   2775
      Begin VB.Frame Frame4 
         Caption         =   "Adjustment Options"
         Height          =   1095
         Left            =   180
         TabIndex        =   21
         Top             =   2820
         Width           =   2205
         Begin VB.OptionButton Option_RGB 
            Caption         =   "Adjust by RGB Ratio"
            Height          =   375
            Left            =   120
            TabIndex        =   23
            Top             =   600
            Width           =   1935
         End
         Begin VB.OptionButton Option_xy 
            Caption         =   "Adjust to Target x, y"
            Height          =   255
            Left            =   120
            TabIndex        =   22
            Top             =   240
            Value           =   -1  'True
            Width           =   1935
         End
      End
      Begin VB.Frame Frame3 
         Caption         =   "Target x y"
         Height          =   855
         Left            =   165
         TabIndex        =   16
         Top             =   1845
         Width           =   2265
         Begin VB.TextBox Target_y 
            Height          =   270
            Left            =   1200
            TabIndex        =   20
            Text            =   "0.292"
            Top             =   360
            Width           =   735
         End
         Begin VB.TextBox Target_x 
            Height          =   270
            Left            =   240
            TabIndex        =   18
            Text            =   "0.2788"
            Top             =   360
            Width           =   735
         End
         Begin VB.Label Label22 
            Caption         =   "y"
            Height          =   255
            Left            =   1080
            TabIndex        =   19
            Top             =   360
            Width           =   255
         End
         Begin VB.Label Label21 
            Caption         =   "x"
            Height          =   255
            Left            =   120
            TabIndex        =   17
            Top             =   360
            Width           =   255
         End
      End
      Begin VB.CommandButton AutoCCT 
         Caption         =   "Run"
         Height          =   375
         Left            =   960
         TabIndex        =   15
         Top             =   3960
         Width           =   975
      End
      Begin VB.Frame Frame5 
         Caption         =   "CH Setting"
         Height          =   1575
         Left            =   210
         TabIndex        =   34
         Top             =   210
         Width           =   2220
         Begin VB.TextBox CH_S 
            Alignment       =   2  'Center
            Height          =   270
            Left            =   1455
            TabIndex        =   37
            Text            =   "0"
            Top             =   285
            Width           =   615
         End
         Begin VB.TextBox CH_C 
            Alignment       =   2  'Center
            Height          =   270
            Left            =   1455
            TabIndex        =   36
            Text            =   "2"
            Top             =   645
            Width           =   615
         End
         Begin VB.TextBox CH_ID 
            Height          =   270
            Left            =   1095
            TabIndex        =   35
            Top             =   1005
            Width           =   975
         End
         Begin VB.Label Label18 
            AutoSize        =   -1  'True
            Caption         =   "Source CH"
            Height          =   180
            Left            =   165
            TabIndex        =   40
            Top             =   285
            Width           =   765
         End
         Begin VB.Label Label19 
            AutoSize        =   -1  'True
            Caption         =   "Target W CH"
            Height          =   195
            Left            =   135
            TabIndex        =   39
            Top             =   705
            Width           =   945
         End
         Begin VB.Label Label20 
            AutoSize        =   -1  'True
            Caption         =   "TargetW ID"
            Height          =   195
            Left            =   135
            TabIndex        =   38
            Top             =   1050
            Width           =   840
         End
      End
   End
   Begin VB.Timer Timer1 
      Interval        =   50
      Left            =   480
      Top             =   7200
   End
   Begin VB.HScrollBar HScrollB 
      Height          =   255
      Left            =   3480
      Max             =   255
      TabIndex        =   4
      Top             =   6840
      Value           =   255
      Width           =   7455
   End
   Begin VB.HScrollBar HScrollG 
      Height          =   255
      Left            =   3465
      Max             =   255
      TabIndex        =   3
      Top             =   6480
      Value           =   255
      Width           =   7455
   End
   Begin VB.HScrollBar HScrollR 
      Height          =   255
      Left            =   3495
      Max             =   255
      TabIndex        =   2
      Top             =   6120
      Value           =   255
      Width           =   7455
   End
   Begin VB.PictureBox Picture1 
      Height          =   5655
      Left            =   3240
      ScaleHeight     =   5604
      ScaleWidth      =   7884
      TabIndex        =   1
      Top             =   240
      Width           =   7935
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   1320
      Top             =   6600
      _ExtentX        =   804
      _ExtentY        =   804
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Frame Frame1 
      Caption         =   "1. CCT to xy on D-illuminant locus"
      Height          =   2175
      Left            =   120
      TabIndex        =   0
      Top             =   225
      Width           =   2775
      Begin VB.CommandButton btn_CCT 
         Caption         =   "Calculate"
         Height          =   420
         Left            =   840
         TabIndex        =   28
         Top             =   1560
         Width           =   975
      End
      Begin VB.TextBox Text_CCT 
         Alignment       =   2  'Center
         Height          =   350
         Left            =   960
         TabIndex        =   24
         Text            =   "10000"
         Top             =   285
         Width           =   735
      End
      Begin VB.Label Label_CCTvs 
         AutoSize        =   -1  'True
         Caption         =   "0.4419"
         Height          =   180
         Left            =   1920
         TabIndex        =   32
         Top             =   1200
         Width           =   495
      End
      Begin VB.Label Label_CCTus 
         AutoSize        =   -1  'True
         Caption         =   "0.1876"
         Height          =   180
         Left            =   600
         TabIndex        =   31
         Top             =   1200
         Width           =   495
      End
      Begin VB.Label Label_23 
         Caption         =   "v' ="
         Height          =   255
         Left            =   1560
         TabIndex        =   30
         Top             =   1200
         Width           =   375
      End
      Begin VB.Label Label_24 
         Caption         =   "u' ="
         Height          =   255
         Left            =   240
         TabIndex        =   29
         Top             =   1200
         Width           =   375
      End
      Begin VB.Label Label_CCTy 
         AutoSize        =   -1  'True
         Caption         =   "0.2920"
         BeginProperty DataFormat 
            Type            =   0
            Format          =   "0.0000"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1028
            SubFormatType   =   0
         EndProperty
         Height          =   180
         Left            =   1920
         TabIndex        =   27
         Top             =   840
         Width           =   495
      End
      Begin VB.Label Label_CCTx 
         AutoSize        =   -1  'True
         Caption         =   "0.2788"
         BeginProperty DataFormat 
            Type            =   1
            Format          =   "0.00000"
            HaveTrueFalseNull=   0
            FirstDayOfWeek  =   0
            FirstWeekOfYear =   0
            LCID            =   1028
            SubFormatType   =   1
         EndProperty
         Height          =   180
         Left            =   600
         TabIndex        =   26
         Top             =   840
         Width           =   495
      End
      Begin VB.Label Label1 
         Caption         =   "K"
         Height          =   255
         Left            =   1800
         TabIndex        =   25
         Top             =   360
         Width           =   495
      End
      Begin VB.Label Label6 
         Alignment       =   2  'Center
         Caption         =   "y ="
         Height          =   255
         Left            =   1440
         TabIndex        =   13
         Top             =   840
         Width           =   495
      End
      Begin VB.Label Label5 
         Alignment       =   2  'Center
         Caption         =   "x ="
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   840
         Width           =   495
      End
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "C.T."
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   360
         Width           =   615
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
      Left            =   6960
      TabIndex        =   33
      Top             =   7320
      Width           =   4395
   End
   Begin VB.Label Label9 
      Alignment       =   2  'Center
      Caption         =   "R"
      Height          =   255
      Left            =   10920
      TabIndex        =   10
      Top             =   6120
      Width           =   375
   End
   Begin VB.Label Label8 
      Alignment       =   2  'Center
      Caption         =   "G"
      Height          =   255
      Left            =   10920
      TabIndex        =   9
      Top             =   6480
      Width           =   375
   End
   Begin VB.Label Label7 
      Alignment       =   2  'Center
      Caption         =   "B"
      Height          =   255
      Left            =   10920
      TabIndex        =   8
      Top             =   6840
      Width           =   375
   End
   Begin VB.Label BText 
      Alignment       =   2  'Center
      Caption         =   "0"
      Height          =   255
      Left            =   2880
      TabIndex        =   7
      Top             =   6840
      Width           =   615
   End
   Begin VB.Label GText 
      Alignment       =   2  'Center
      Caption         =   "0"
      Height          =   255
      Left            =   2880
      TabIndex        =   6
      Top             =   6480
      Width           =   615
   End
   Begin VB.Label RText 
      Alignment       =   2  'Center
      Caption         =   "0"
      Height          =   255
      Left            =   2880
      TabIndex        =   5
      Top             =   6120
      Width           =   615
   End
End
Attribute VB_Name = "RGBcal"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
        
        Public CCT As Double
        Public uv As Double
        Public CCT_x As Double
        Public CCY_y As Double
        Public d65x As Double
        Public d65y As Double
        Public us As Double
        Public vs As Double
        
        Public Sub xy2usvs(xx, YY)
            us = 4 * xx / (-2 * xx + 12 * YY + 3)
            vs = 9 * YY / (-2 * xx + 12 * YY + 3)
            
            
        End Sub
        
        ' non-use
        Public Sub xy2CCT(xx, YY)
            Dim rt(30) As Double
            Dim uvt(30, 2) As Double
            Dim CIE_color_match(80, 2) As Double
            
            uvt(0, 0) = 0.18006: uvt(0, 1) = 0.26352: uvt(0, 2) = -0.24341
            uvt(1, 0) = 0.18066: uvt(1, 1) = 0.26589: uvt(1, 2) = -0.25479
            uvt(2, 0) = 0.18133: uvt(2, 1) = 0.26846: uvt(2, 2) = -0.26876
            uvt(3, 0) = 0.18208: uvt(3, 1) = 0.27119: uvt(3, 2) = -0.28539
            uvt(4, 0) = 0.18293: uvt(4, 1) = 0.27407: uvt(4, 2) = -0.3047
            uvt(5, 0) = 0.18388: uvt(5, 1) = 0.27709: uvt(5, 2) = -0.32675
            uvt(6, 0) = 0.18494: uvt(6, 1) = 0.28021: uvt(6, 2) = -0.35156
            uvt(7, 0) = 0.18611: uvt(7, 1) = 0.28342: uvt(7, 2) = -0.37915
            uvt(8, 0) = 0.1874: uvt(8, 1) = 0.28668: uvt(8, 2) = -0.40955
            uvt(9, 0) = 0.1888: uvt(9, 1) = 0.28997: uvt(9, 2) = -0.44278
            uvt(10, 0) = 0.19032: uvt(10, 1) = 0.29326: uvt(10, 2) = -0.47888
            uvt(11, 0) = 0.19462: uvt(11, 1) = 0.30141: uvt(11, 2) = -0.58204
            uvt(12, 0) = 0.19962: uvt(12, 1) = 0.30921: uvt(12, 2) = -0.70471
            uvt(13, 0) = 0.20525: uvt(13, 1) = 0.31647: uvt(13, 2) = -0.84901
            uvt(14, 0) = 0.21142: uvt(14, 1) = 0.32312: uvt(14, 2) = -1.0182
            uvt(15, 0) = 0.21807: uvt(15, 1) = 0.32909: uvt(15, 2) = -1.2168
            uvt(16, 0) = 0.22511: uvt(16, 1) = 0.33439: uvt(16, 2) = -1.4512
            uvt(17, 0) = 0.23247: uvt(17, 1) = 0.33904: uvt(17, 2) = -1.7298
            uvt(18, 0) = 0.2401: uvt(18, 1) = 0.34308: uvt(18, 2) = -2.0637
            uvt(19, 0) = 0.24792: uvt(19, 1) = 0.34655: uvt(19, 2) = -2.4681
            uvt(20, 0) = 0.25591: uvt(20, 1) = 0.34951: uvt(20, 2) = -2.9641
            uvt(21, 0) = 0.264: uvt(21, 1) = 0.352: uvt(21, 2) = -3.5814
            uvt(22, 0) = 0.27218: uvt(22, 1) = 0.35407: uvt(22, 2) = -4.3633
            uvt(23, 0) = 0.28039: uvt(23, 1) = 0.35577: uvt(23, 2) = -5.3762
            uvt(24, 0) = 0.28863: uvt(24, 1) = 0.35714: uvt(24, 2) = -6.7262
            uvt(25, 0) = 0.29685: uvt(25, 1) = 0.35823: uvt(25, 2) = -8.5955
            uvt(26, 0) = 0.30505: uvt(26, 1) = 0.35907: uvt(26, 2) = -11.324
            uvt(27, 0) = 0.3132: uvt(27, 1) = 0.35968: uvt(27, 2) = -15.628
            uvt(28, 0) = 0.32129: uvt(28, 1) = 0.36011: uvt(28, 2) = -23.325
            uvt(29, 0) = 0.32931: uvt(29, 1) = 0.36038: uvt(29, 2) = -40.77
            uvt(30, 0) = 0.33724: uvt(30, 1) = 0.36051: uvt(30, 2) = -116.45
            
            rt(0) = DBL_MIN: rt(1) = 0.00001: rt(2) = 0.00002
            rt(3) = 0.00003: rt(4) = 0.00004: rt(5) = 0.00005
            rt(6) = 0.00006: rt(7) = 0.00007: rt(8) = 0.00008
            rt(9) = 0.00009: rt(10) = 0.0001: rt(11) = 0.000125
            rt(12) = 0.00015: rt(13) = 0.000175: rt(14) = 0.0002
            rt(15) = 0.000225: rt(16) = 0.00025: rt(17) = 0.000275
            rt(18) = 0.0003: rt(19) = 0.000325: rt(20) = 0.00035
            rt(21) = 0.000375: rt(22) = 0.0004: rt(23) = 0.000425
            rt(24) = 0.00045: rt(25) = 0.000475: rt(26) = 0.0005
            rt(27) = 0.000525: rt(28) = 0.00055: rt(29) = 0.000575
            rt(30) = 0.0006
            
            CIE_color_match(0, 0) = 0.0014: CIE_color_match(0, 1) = 0: CIE_color_match(0, 2) = 0.0065
            CIE_color_match(1, 0) = 0.0022: CIE_color_match(1, 1) = 0.0001: CIE_color_match(1, 2) = 0.0105
            CIE_color_match(2, 0) = 0.0042: CIE_color_match(2, 1) = 0.0001: CIE_color_match(2, 2) = 0.0201
            CIE_color_match(3, 0) = 0.0076: CIE_color_match(3, 1) = 0.0002: CIE_color_match(3, 2) = 0.0362
            CIE_color_match(4, 0) = 0.0143: CIE_color_match(4, 1) = 0.0004: CIE_color_match(4, 2) = 0.0679
            CIE_color_match(5, 0) = 0.0232: CIE_color_match(5, 1) = 0.0006: CIE_color_match(5, 2) = 0.1102
            CIE_color_match(6, 0) = 0.0435: CIE_color_match(6, 1) = 0.0012: CIE_color_match(6, 2) = 0.2074
            CIE_color_match(7, 0) = 0.0776: CIE_color_match(7, 1) = 0.0022: CIE_color_match(7, 2) = 0.3713
            CIE_color_match(8, 0) = 0.1344: CIE_color_match(8, 1) = 0.004: CIE_color_match(8, 2) = 0.6456
            CIE_color_match(9, 0) = 0.2148: CIE_color_match(9, 1) = 0.0073: CIE_color_match(9, 2) = 1.0391
            CIE_color_match(10, 0) = 0.2839: CIE_color_match(10, 1) = 0.0116: CIE_color_match(10, 2) = 1.3856
            CIE_color_match(11, 0) = 0.3285: CIE_color_match(11, 1) = 0.0168: CIE_color_match(11, 2) = 1.623
            CIE_color_match(12, 0) = 0.3483: CIE_color_match(12, 1) = 0.023: CIE_color_match(12, 2) = 1.7471
            CIE_color_match(13, 0) = 0.3481: CIE_color_match(13, 1) = 0.0298: CIE_color_match(13, 2) = 1.7826
            CIE_color_match(14, 0) = 0.3362: CIE_color_match(14, 1) = 0.038: CIE_color_match(14, 2) = 1.7721
            CIE_color_match(15, 0) = 0.3187: CIE_color_match(15, 1) = 0.048: CIE_color_match(15, 2) = 1.7441
            CIE_color_match(16, 0) = 0.2908: CIE_color_match(16, 1) = 0.06: CIE_color_match(16, 2) = 1.6692
            CIE_color_match(17, 0) = 0.2511: CIE_color_match(17, 1) = 0.0739: CIE_color_match(17, 2) = 1.5281
            CIE_color_match(18, 0) = 0.1954: CIE_color_match(18, 1) = 0.091: CIE_color_match(18, 2) = 1.2876
            CIE_color_match(19, 0) = 0.1421: CIE_color_match(19, 1) = 0.1126: CIE_color_match(19, 2) = 1.0419
            CIE_color_match(20, 0) = 0.0956: CIE_color_match(20, 1) = 0.139: CIE_color_match(20, 2) = 0.813
            CIE_color_match(21, 0) = 0.058: CIE_color_match(21, 1) = 0.1693: CIE_color_match(21, 2) = 0.6162
            CIE_color_match(22, 0) = 0.032: CIE_color_match(22, 1) = 0.208: CIE_color_match(22, 2) = 0.4652
            CIE_color_match(23, 0) = 0.0147: CIE_color_match(23, 1) = 0.2586: CIE_color_match(23, 2) = 0.3533
            CIE_color_match(24, 0) = 0.0049: CIE_color_match(24, 1) = 0.323: CIE_color_match(24, 2) = 0.272
            CIE_color_match(25, 0) = 0.0024: CIE_color_match(25, 1) = 0.4073: CIE_color_match(25, 2) = 0.2123
            CIE_color_match(26, 0) = 0.0093: CIE_color_match(26, 1) = 0.503: CIE_color_match(26, 2) = 0.1582
            CIE_color_match(27, 0) = 0.0291: CIE_color_match(27, 1) = 0.6082: CIE_color_match(27, 2) = 0.1117
            CIE_color_match(28, 0) = 0.0633: CIE_color_match(28, 1) = 0.71: CIE_color_match(28, 2) = 0.0782
            CIE_color_match(29, 0) = 0.1096: CIE_color_match(29, 1) = 0.7932: CIE_color_match(29, 2) = 0.0573
            CIE_color_match(30, 0) = 0.1655: CIE_color_match(30, 1) = 0.862: CIE_color_match(30, 2) = 0.0422
            CIE_color_match(31, 0) = 0.2257: CIE_color_match(31, 1) = 0.9149: CIE_color_match(31, 2) = 0.0298
            CIE_color_match(32, 0) = 0.2904: CIE_color_match(32, 1) = 0.954: CIE_color_match(32, 2) = 0.0203
            CIE_color_match(33, 0) = 0.3597: CIE_color_match(33, 1) = 0.9803: CIE_color_match(33, 2) = 0.0134
            CIE_color_match(34, 0) = 0.4334: CIE_color_match(34, 1) = 0.995: CIE_color_match(34, 2) = 0.0087
            CIE_color_match(35, 0) = 0.5121: CIE_color_match(35, 1) = 1: CIE_color_match(35, 2) = 0.0057
            CIE_color_match(36, 0) = 0.5945: CIE_color_match(36, 1) = 0.995: CIE_color_match(36, 2) = 0.0039
            CIE_color_match(37, 0) = 0.6784: CIE_color_match(37, 1) = 0.9786: CIE_color_match(37, 2) = 0.0027
            CIE_color_match(38, 0) = 0.7621: CIE_color_match(38, 1) = 0.952: CIE_color_match(38, 2) = 0.0021
            CIE_color_match(39, 0) = 0.8425: CIE_color_match(39, 1) = 0.9154: CIE_color_match(39, 2) = 0.0018
            CIE_color_match(40, 0) = 0.9163: CIE_color_match(40, 1) = 0.87: CIE_color_match(40, 2) = 0.0017
            CIE_color_match(41, 0) = 0.9786: CIE_color_match(41, 1) = 0.8163: CIE_color_match(41, 2) = 0.0014
            CIE_color_match(42, 0) = 1.0263: CIE_color_match(42, 1) = 0.757: CIE_color_match(42, 2) = 0.0011
            CIE_color_match(43, 0) = 1.0567: CIE_color_match(43, 1) = 0.6949: CIE_color_match(43, 2) = 0.001
            CIE_color_match(44, 0) = 1.0622: CIE_color_match(44, 1) = 0.631: CIE_color_match(44, 2) = 0.0008
            CIE_color_match(45, 0) = 1.0456: CIE_color_match(45, 1) = 0.5668: CIE_color_match(45, 2) = 0.0006
            CIE_color_match(46, 0) = 1.0026: CIE_color_match(46, 1) = 0.503: CIE_color_match(46, 2) = 0.0003
            CIE_color_match(47, 0) = 0.9384: CIE_color_match(47, 1) = 0.4412: CIE_color_match(47, 2) = 0.0002
            CIE_color_match(48, 0) = 0.8544: CIE_color_match(48, 1) = 0.381: CIE_color_match(48, 2) = 0.0002
            CIE_color_match(49, 0) = 0.7514: CIE_color_match(49, 1) = 0.321: CIE_color_match(49, 2) = 0.0001
            CIE_color_match(50, 0) = 0.6424: CIE_color_match(50, 1) = 0.265: CIE_color_match(50, 2) = 0
            CIE_color_match(51, 0) = 0.5419: CIE_color_match(51, 1) = 0.217: CIE_color_match(51, 2) = 0
            CIE_color_match(52, 0) = 0.4479: CIE_color_match(52, 1) = 0.175: CIE_color_match(52, 2) = 0
            CIE_color_match(53, 0) = 0.3608: CIE_color_match(53, 1) = 0.1382: CIE_color_match(53, 2) = 0
            CIE_color_match(54, 0) = 0.2835: CIE_color_match(54, 1) = 0.107: CIE_color_match(54, 2) = 0
            CIE_color_match(55, 0) = 0.2187: CIE_color_match(55, 1) = 0.0816: CIE_color_match(55, 2) = 0
            CIE_color_match(56, 0) = 0.1649: CIE_color_match(56, 1) = 0.061: CIE_color_match(56, 2) = 0
            CIE_color_match(57, 0) = 0.1212: CIE_color_match(57, 1) = 0.0446: CIE_color_match(57, 2) = 0
            CIE_color_match(58, 0) = 0.0874: CIE_color_match(58, 1) = 0.032: CIE_color_match(58, 2) = 0
            CIE_color_match(59, 0) = 0.0636: CIE_color_match(59, 1) = 0.0232: CIE_color_match(59, 2) = 0
            CIE_color_match(60, 0) = 0.0468: CIE_color_match(60, 1) = 0.017: CIE_color_match(60, 2) = 0
            CIE_color_match(61, 0) = 0.0329: CIE_color_match(61, 1) = 0.0119: CIE_color_match(61, 2) = 0
            CIE_color_match(62, 0) = 0.0227: CIE_color_match(62, 1) = 0.0082: CIE_color_match(62, 2) = 0
            CIE_color_match(63, 0) = 0.0158: CIE_color_match(63, 1) = 0.0057: CIE_color_match(63, 2) = 0
            CIE_color_match(64, 0) = 0.0114: CIE_color_match(64, 1) = 0.0041: CIE_color_match(64, 2) = 0
            CIE_color_match(65, 0) = 0.0081: CIE_color_match(65, 1) = 0.0029: CIE_color_match(65, 2) = 0
            CIE_color_match(66, 0) = 0.0058: CIE_color_match(66, 1) = 0.0021: CIE_color_match(66, 2) = 0
            CIE_color_match(67, 0) = 0.0041: CIE_color_match(67, 1) = 0.0015: CIE_color_match(67, 2) = 0
            CIE_color_match(68, 0) = 0.0029: CIE_color_match(68, 1) = 0.001: CIE_color_match(68, 2) = 0
            CIE_color_match(69, 0) = 0.002: CIE_color_match(69, 1) = 0.0007: CIE_color_match(69, 2) = 0
            CIE_color_match(70, 0) = 0.0014: CIE_color_match(70, 1) = 0.0005: CIE_color_match(70, 2) = 0
            CIE_color_match(71, 0) = 0.001: CIE_color_match(71, 1) = 0.0004: CIE_color_match(71, 2) = 0
            CIE_color_match(72, 0) = 0.0007: CIE_color_match(72, 1) = 0.0002: CIE_color_match(72, 2) = 0
            CIE_color_match(73, 0) = 0.0005: CIE_color_match(73, 1) = 0.0002: CIE_color_match(73, 2) = 0
            CIE_color_match(74, 0) = 0.0003: CIE_color_match(74, 1) = 0.0001: CIE_color_match(74, 2) = 0
            CIE_color_match(75, 0) = 0.0002: CIE_color_match(75, 1) = 0.0001: CIE_color_match(75, 2) = 0
            CIE_color_match(76, 0) = 0.0002: CIE_color_match(76, 1) = 0.0001: CIE_color_match(76, 2) = 0
            CIE_color_match(77, 0) = 0.0001: CIE_color_match(77, 1) = 0: CIE_color_match(77, 2) = 0
            CIE_color_match(78, 0) = 0.0001: CIE_color_match(78, 1) = 0: CIE_color_match(78, 2) = 0
            CIE_color_match(79, 0) = 0.0001: CIE_color_match(79, 1) = 0: CIE_color_match(79, 2) = 0
            CIE_color_match(80, 0) = 0: CIE_color_match(80, 1) = 0: CIE_color_match(80, 2) = 0
            
            uu = 4 * xx / (-2 * xx + 12 * YY + 3)
            vv = 6 * YY / (-2 * xx + 12 * YY + 3)
            DM = 0
            i = 0
            Do
                
                di = vv - uvt(i, 1) - uvt(i, 2) * (uu - uvt(i, 0))
                If ((i > 0) And (((di < 0) And (DM >= 0)) Or ((di >= 0) And (DM < 0)))) Then
                    
                    Exit Do '/* found lines bounding (us, vs) : i-1 and i */
                End If
                DM = di
                i = i + 1
                If i > 30 Then
                    MsgBox ("Out of range, CCT < 1666.7 K")
                End
            End If
        Loop
        di = di / (1 + uvt(i, 2) * uvt(i, 2)) ^ 0.5
        
        DM = DM / (1 + uvt(i - 1, 2) * uvt(i - 1, 2)) ^ 0.5
        P = DM / (DM - di) ' /* p = interpolation parameter, 0.0 : i-1, 1.0 : i */
        CCT = 1 / (((rt(i)) - (rt(i - 1))) * (P) + (rt(i - 1)))
        
        x = 0
        y = 0
        Z = 0
        i = 0
        For lambda = 380 To 780.1 Step 5
            wlm = lambda * 0.000000001
            Me2 = (3.74183 * 10 ^ (-16) * wlm ^ -5) / (Exp(0.014388 / (wlm * CCT)) - 1)
            x = x + Me2 * CIE_color_match(i, 0)
            y = y + Me2 * CIE_color_match(i, 1)
            Z = Z + Me2 * CIE_color_match(i, 2)
            
            i = i + 1
            
        Next lambda
        CCT_x = x / (x + y + Z)
        cct_y = y / (x + y + Z)
        
        uu2 = 4 * CCT_x / (-2 * CCT_x + 12 * cct_y + 3)
        vv2 = 6 * cct_y / (-2 * CCT_x + 12 * cct_y + 3)
        
        
        del_uv = Sqr((uu2 - uu) ^ 2 + (vv2 - vv) ^ 2)
        del_uv = Round(del_uv * 1000000) / 1000000
        'Label2.Caption = del_uv
        
    End Sub
    
    ' convert from the correlated color temperature of a CIE D-illuminant to the chromaticity of that D-illuminant.
    Public Sub CCT2xy(CCT)
        
        If CCT > 7000 Then
            d65x = -2006400000# / CCT ^ 3 + 1901800# / CCT ^ 2 + 247.48 / CCT + 0.23704
        Else
            d65x = -4607000000# / CCT ^ 3 + 2967800# / CCT ^ 2 + 99.11 / CCT + 0.244063
        End If
        d65y = -3 * d65x ^ 2 + 2.87 * d65x - 0.275
        
    End Sub
    
    
    
    Public Sub CA210(Dx, Dy, YY)
        
        objCa.DisplayMode = 0
        objCa.Measure
        Dx = objProbe.sx
        Dy = objProbe.SY
        YY = objProbe.Lv
        
    End Sub
    
    
    Public Sub CADataCT210(Dx, Dy, YY, CT, uv, LR, LG, LB)
        
        objCa.DisplayMode = 0
        objCa.Measure
        Dx = objProbe.sx
        Dy = objProbe.SY
        YY = objProbe.Lv
        
        objCa.DisplayMode = 1
        objCa.Measure
        CT = objProbe.t
        uv = objProbe.duv
        
        objCa.DisplayMode = 3
        objCa.Measure
        LR = objProbe.r
        LG = objProbe.G
        LB = objProbe.B
        
        
    End Sub
    
    
    Public Sub CADataCT2102(Dx, Dy, YY, CT, uv)
        
        objCa.DisplayMode = 0
        objCa.Measure
        Dx = objProbe.sx
        Dy = objProbe.SY
        YY = objProbe.Lv
        
        objCa.DisplayMode = 1
        objCa.Measure
        CT = objProbe.t
        uv = objProbe.duv
        
        
        
        
    End Sub
    
    
    Public Sub CAData210(Dx, Dy, YY, LR, LG, LB)
        ' 為什麼要量兩次? 量一次不就可以取全部data
        objCa.DisplayMode = 0
        objCa.Measure
        Dx = objProbe.sx
        Dy = objProbe.SY
        YY = objProbe.Lv
        
        objCa.DisplayMode = 3
        objCa.Measure
        LR = objProbe.r
        LG = objProbe.G
        LB = objProbe.B
        
    End Sub
    
    
    Public Sub CACT210(Dx, Dy, YY, CT, uv)
        
        objCa.DisplayMode = 0
        objCa.Measure
        Dx = objProbe.sx
        Dy = objProbe.SY
        YY = objProbe.Lv
        
        objCa.DisplayMode = 1
        objCa.Measure
        CT = objProbe.t
        uv = objProbe.duv
        
        
    End Sub
    
    Private Sub AutoCCT_Click()
        Dim temp_r(1 To 3) As Variant
        Dim temp_g(1 To 3) As Variant
        Dim temp_b(1 To 3) As Variant
        Dim temp_w(1 To 3) As Variant
        
        Go_ahead = True
        objCa.RemoteMode = 1
        objMemory.ChannelNO = CH_S
        Tar_x = Val(Target_x.Text)
        Tar_y = Val(Target_y.Text)
        'Dim min_x As Variant
        'Dim min_y As Variant
        '''''''''''If xy=0 ManualMode else AutoMode
        If Option_xy.Value = True Then
            MainForm.WindowState = vbMinimized
            
            ' blue的處理(x/y)
            Do
                Call PatternRGB(RText, GText, BText)
                Call CA210(Dx, Dy, YY)
                
                ' 目前與目標值的差異
                diff_x = Dx - Tar_x
                diff_y = Dy - Tar_y
                
                If Abs(diff_x) > 0.012 And Abs(diff_y) > 0.012 Then
                    If (MainForm.op_pc.Value = True) Then
                        '如果以pc為input source
                        DD = 5
                    Else
                        DD = 20
                    End If
                ElseIf Abs(diff_x) > 0.003 And Abs(diff_y) > 0.003 Then
                    ' 依據偏移程度不同設定不同的DD
                    If (MainForm.op_pc.Value = True) Then
                        DD = 3
                    Else
                        DD = 8
                    End If
                Else
                    DD = 1
                End If
                If diff_x < 0 Or diff_y < 0 Then
                    ' 若dx與dy皆小於0, 代表偏藍所以減藍
                    HScrollB.Value = HScrollB.Value - DD
                    
                End If
                
                If diff_x > 0 And diff_y > 0 Then Exit Do
            Loop
            
            ' red的處理 (x)
            Do
                Call PatternRGB(RText, GText, BText)
                Call CA210(Dx, Dy, YY)
                
                diff_x = Dx - Tar_x
                If diff_x > 0 Then HScrollR.Value = HScrollR.Value - 1
                
                
                
                If diff_x < 0 Then Exit Do
                
            Loop
            
            
            Do
                Call PatternRGB(RText, GText, BText)
                Call CA210(Dx, Dy, YY)
                diff_x = Dx - Tar_x
                diff_y = Dy - Tar_y
                ' green的處理
                If diff_y > 0 Then HScrollG.Value = HScrollG.Value - 1
                ' blue的處理
                If (diff_x > 0 And HScrollB.Value < 255) Then HScrollB.Value = HScrollB.Value + 1
                ' red的處理
                If (diff_x > 0 And HScrollB.Value = 255) Then HScrollR.Value = HScrollR.Value - 1
                ' 以下兩種狀況則停止處理
                If (diff_x < 0 And diff_y < 0) Or (HScrollB.Value = 255 And diff_y < 0) Then Exit Do
                
            Loop
            
            Call PatternRGB(RText, GText, BText)
            Call CA210(Dx, Dy, YY)
            diff_x = Dx - Tar_x
            diff_y = Dy - Tar_y
            
            
            If HScrollR.Value < 255 Then
                ' 若R<255, 試著把R調大
                HScrollR.Value = HScrollR.Value + 1
                Call PatternRGB(RText, GText, BText)
                Call CA210(Dx, Dy, YY)
                ' 如果誤差會變的更大, 就不要調整R, 把它調回來
                If Abs(Dx - Tar_x) > Abs(diff_x) Then HScrollR.Value = HScrollR.Value - 1
            End If
            
            If HScrollG.Value < 255 Then
                ' 若G還有調整空間
                HScrollG.Value = HScrollG.Value + 1
                Call PatternRGB(RText, GText, BText)
                Call CA210(Dx, Dy, YY)
                ' 如果誤差會變的更大就調回來
                If Abs(Dy - Tar_y) > Abs(diff_y) Then HScrollG.Value = HScrollG.Value - 1
            End If
        End If
        
        
        Call PatternRGB(RText, 0, 0)
        Call Tims(5)
        Call CA210(Dx, Dy, YY)
        temp_r(1) = Dx
        temp_r(2) = Dy
        temp_r(3) = YY
        
        Call PatternRGB(0, GText, 0)
        Call Tims(5)
        Call CA210(Dx, Dy, YY)
        temp_g(1) = Dx
        temp_g(2) = Dy
        temp_g(3) = YY
        
        Call PatternRGB(0, 0, BText)
        Call Tims(5)
        Call CA210(Dx, Dy, YY)
        temp_b(1) = Dx
        temp_b(2) = Dy
        temp_b(3) = YY
        
        Call PatternRGB(RText, GText, BText)
        Call Tims(5)
        Call CA210(Dx, Dy, YY)
        temp_w(1) = Dx
        temp_w(2) = Dy
        temp_w(3) = YY
        Calib_CH = Val(CH_C.Text)
        objMemory.ChannelNO = CH_C
        bSetMode = False
        objCa.SetLvxyCalMode
        bSetMode = True
        
        Background.visible = True
        
        '-------------------------------------------
        'Red
        '-------------------------------------------
        Call PatternRGB(RText, 0, 0)
        Call Tims(5)
        
        objCa.Measure
        objCa.SetLvxyCalData 0, Val(temp_r(1)), Val(temp_r(2)), Val(temp_r(3))
        
        
        
        
        Call PatternRGB(0, GText, 0)
        Call Tims(5)
        objCa.Measure
        objCa.SetLvxyCalData 1, Val(temp_g(1)), Val(temp_g(2)), Val(temp_g(3))
        
        
        Call PatternRGB(0, 0, BText)
        Call Tims(5)
        objCa.Measure
        objCa.SetLvxyCalData 2, Val(temp_b(1)), Val(temp_b(2)), Val(temp_b(3))
        
        
        Call PatternRGB(RText, GText, BText)
        Call Tims(5)
        objCa.Measure
        objCa.SetLvxyCalData 3, Val(temp_w(1)), Val(temp_w(2)), Val(temp_w(3))
        
        
        objCa.Enter
        Call SetID
        objCa.RemoteMode = 0
        MainForm.visible = True
        Unload Background
        
        
    End Sub
    
    
    
    Private Sub btn_CCT_Click()
        CCT = Val(Text_CCT.Text)
        If ((CCT < 4000) Or (CCT > 25000)) Then
            x = MsgBox("Out of range, Please input CCT (4000 ~ 25000)", vbExclamation + vbOKOnly)
            Text_CCT.Text = "10000"
        End If
        Call CCT2xy(CCT)
        'Label_CCTx.Caption = Left(Str(Round(d65x * 1000000) / 1000000), 6)
        Label_CCTx.caption = Val(Format(d65x, "#.####"))
        Label_CCTy.caption = Val(Format(d65y, "#.####"))
        Call xy2usvs(d65x, d65y)
        Label_CCTus.caption = Val(Format(us, "#.####"))
        Label_CCTvs.caption = Val(Format(vs, "#.####"))
        Target_x.Text = Val(Format(d65x, "#.####"))
        Target_y.Text = Val(Format(d65y, "#.####"))
        'Label_CCTy.Caption = Round(d65y * 1000000) / 1000000
        
    End Sub
    
    Private Sub Form_Load()
        Target_x.Enabled = True
        Target_y.Enabled = True
        HScrollR.Enabled = False
        HScrollG.Enabled = False
        HScrollB.Enabled = False
        If Debug_enable = False Then objCa.RemoteMode = 0
        If Source_CH <> 0 Then CH_S.Text = Source_CH
        If Calib_CH <> 0 Then CH_C.Text = Calib_CH
        
        If (MainForm.op_pc.Value = True) Then
            RGBcal.HScrollR.Max = 255
            RGBcal.HScrollG.Max = 255
            RGBcal.HScrollB.Max = 255
            RGBcal.HScrollR.Value = 255
            RGBcal.HScrollG.Value = 255
            RGBcal.HScrollB.Value = 255
        Else
            RGBcal.HScrollR.Max = 4095
            RGBcal.HScrollG.Max = 4095
            RGBcal.HScrollB.Max = 4095
            RGBcal.HScrollR.Value = 4095
            RGBcal.HScrollG.Value = 4095
            RGBcal.HScrollB.Value = 4095
        End If
        
    End Sub
    
    
    
    Private Sub HScrollB_Change()
        RText = HScrollR.Value
        GText = HScrollG.Value
        BText = HScrollB.Value
        
        If MainForm.op_pc.Value = True Then
            Picture1.BackColor = RGB(RText, GText, BText)
        Else
            TCON_RGB RText, GText, BText
        End If
    End Sub
    
    Private Sub HScrollG_Change()
        RText = HScrollR.Value
        GText = HScrollG.Value
        BText = HScrollB.Value
        
        If MainForm.op_pc.Value = True Then
            Picture1.BackColor = RGB(RText, GText, BText)
        Else
            TCON_RGB RText, GText, BText
        End If
    End Sub
    
    Private Sub HScrollR_Change()
        RText = HScrollR.Value
        GText = HScrollG.Value
        BText = HScrollB.Value
        
        If MainForm.op_pc.Value = True Then
            Picture1.BackColor = RGB(RText, GText, BText)
        Else
            TCON_RGB RText, GText, BText
        End If
    End Sub
    
    Private Sub Option_RGB_Click()
        
        Target_x.Enabled = False
        Target_y.Enabled = False
        If MainForm.op_pc.Value = True Then
            HScrollR.Value = 255
            HScrollG.Value = 255
            HScrollB.Value = 255
        Else
            HScrollR.Value = 4095
            HScrollG.Value = 4095
            HScrollB.Value = 4095
        End If
        HScrollR.Enabled = True
        HScrollG.Enabled = True
        HScrollB.Enabled = True
        
    End Sub
    
    Private Sub Option_xy_Click()
        Target_x.Enabled = True
        Target_y.Enabled = True
        If MainForm.op_pc.Value = True Then
            HScrollR.Value = 255
            HScrollG.Value = 255
            HScrollB.Value = 255
        Else
            HScrollR.Value = 4095
            HScrollG.Value = 4095
            HScrollB.Value = 4095
        End If
        HScrollR.Enabled = False
        HScrollG.Enabled = False
        HScrollB.Enabled = False
        
        
    End Sub
    
    ' 設定CA-210的ID為CH_C
    Private Sub SetID()
        objMemory.ChannelNO = Val(CH_C.Text)
        Dim strID As String
        strID = UCase(objMemory.ChannelID)
        
        If UCase(CH_ID.Text) <> strID Then 'CA-210 Can't set the same IDName and empty
            
            If CH_ID.Text = "" Then
                objMemory.SetChannelID "  "
                objMemory.SetChannelID " "
                
            Else
                objMemory.SetChannelID UCase(CH_ID.Text)
            End If
        End If
        
        
    End Sub
