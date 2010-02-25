VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form MatrixCalib 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Matrix Calibration"
   ClientHeight    =   5760
   ClientLeft      =   48
   ClientTop       =   336
   ClientWidth     =   6720
   ClipControls    =   0   'False
   Icon            =   "CA210MatrixCalibration.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5760
   ScaleWidth      =   6720
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame5 
      Caption         =   "Backup"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   975
      Left            =   120
      TabIndex        =   42
      Top             =   4320
      Width           =   6375
      Begin VB.TextBox Text_CHE 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   2520
         TabIndex        =   46
         Text            =   "99"
         Top             =   400
         Width           =   375
      End
      Begin VB.TextBox Text_CHS 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   1200
         TabIndex        =   45
         Text            =   "1"
         Top             =   400
         Width           =   375
      End
      Begin VB.CommandButton btn_saveall 
         Caption         =   "Save To File"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   3480
         TabIndex        =   44
         Top             =   360
         Width           =   1335
      End
      Begin VB.CommandButton btn_LoadAll 
         Caption         =   "Load From File"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   4920
         TabIndex        =   43
         Top             =   360
         Width           =   1335
      End
      Begin VB.Label Label19 
         Caption         =   "CH"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2160
         TabIndex        =   49
         Top             =   450
         Width           =   375
      End
      Begin VB.Label Label18 
         Caption         =   "To "
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1800
         TabIndex        =   48
         Top             =   450
         Width           =   375
      End
      Begin VB.Label Label17 
         Caption         =   "CH"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   810
         TabIndex        =   47
         Top             =   450
         Width           =   255
      End
   End
   Begin VB.CommandButton btn_Disconnect 
      Caption         =   "Disconnect"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5040
      TabIndex        =   19
      Top             =   1200
      Width           =   1335
   End
   Begin VB.Frame Frame2 
      Caption         =   "Matrix Calibration Setting"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2055
      Left            =   120
      TabIndex        =   4
      Top             =   2040
      Width           =   6375
      Begin VB.CommandButton btn_LoadM 
         Caption         =   "Load"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   3480
         TabIndex        =   40
         Top             =   1440
         Width           =   1335
      End
      Begin VB.TextBox Text_MxB 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   120
         TabIndex        =   39
         Text            =   "255"
         Top             =   1200
         Width           =   615
      End
      Begin VB.TextBox Text_MxG 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   120
         TabIndex        =   38
         Text            =   "255"
         Top             =   840
         Width           =   615
      End
      Begin VB.TextBox Text_MxR 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   120
         TabIndex        =   37
         Text            =   "255"
         Top             =   480
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   11
         Left            =   2760
         TabIndex        =   35
         Text            =   "0"
         Top             =   1560
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   10
         Left            =   1960
         TabIndex        =   34
         Text            =   "0"
         Top             =   1560
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   9
         Left            =   1200
         TabIndex        =   33
         Text            =   "0"
         Top             =   1560
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   8
         Left            =   2760
         TabIndex        =   32
         Text            =   "0"
         Top             =   1200
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   7
         Left            =   1960
         TabIndex        =   31
         Text            =   "0"
         Top             =   1200
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   6
         Left            =   1200
         TabIndex        =   30
         Text            =   "0"
         Top             =   1200
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   5
         Left            =   2760
         TabIndex        =   29
         Text            =   "0"
         Top             =   840
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   4
         Left            =   1960
         TabIndex        =   28
         Text            =   "0"
         Top             =   840
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   3
         Left            =   1200
         TabIndex        =   27
         Text            =   "0"
         Top             =   840
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   2
         Left            =   2760
         TabIndex        =   26
         Text            =   "0"
         Top             =   480
         Width           =   615
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   1
         Left            =   1960
         TabIndex        =   25
         Text            =   "0"
         Top             =   480
         Width           =   615
      End
      Begin VB.TextBox Text_CH 
         Alignment       =   2  'Center
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   4560
         TabIndex        =   21
         Text            =   "1"
         Top             =   420
         Width           =   1095
      End
      Begin VB.TextBox Text_ID 
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   4560
         MaxLength       =   10
         TabIndex        =   20
         Top             =   960
         Width           =   1095
      End
      Begin VB.TextBox Text1 
         Alignment       =   1  'Right Justify
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Index           =   0
         Left            =   1200
         TabIndex        =   24
         Text            =   "0"
         Top             =   480
         Width           =   615
      End
      Begin VB.CommandButton btn_MatrixC 
         Caption         =   "Matrix Calib"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   4920
         TabIndex        =   12
         Top             =   1440
         Width           =   1335
      End
      Begin VB.Label Label14 
         Caption         =   "Pattern"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Index           =   0
         Left            =   195
         TabIndex        =   41
         Top             =   240
         Width           =   615
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "Matrix CH"
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
         Left            =   3600
         TabIndex        =   23
         Top             =   465
         Width           =   750
      End
      Begin VB.Label Label15 
         Caption         =   "ID"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   3960
         TabIndex        =   22
         Top             =   960
         Width           =   255
      End
      Begin VB.Label Label11 
         Caption         =   "Lv"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   3000
         TabIndex        =   11
         Top             =   240
         Width           =   375
      End
      Begin VB.Label Label10 
         Caption         =   "y"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   2250
         TabIndex        =   10
         Top             =   240
         Width           =   375
      End
      Begin VB.Label Label9 
         Caption         =   "x"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1500
         TabIndex        =   9
         Top             =   240
         Width           =   495
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "W"
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
         Left            =   870
         TabIndex        =   8
         Top             =   1605
         Width           =   165
      End
      Begin VB.Label Label7 
         AutoSize        =   -1  'True
         Caption         =   "B"
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
         Left            =   885
         TabIndex        =   7
         Top             =   1245
         Width           =   120
      End
      Begin VB.Label Label6 
         AutoSize        =   -1  'True
         Caption         =   "G"
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
         Left            =   885
         TabIndex        =   6
         Top             =   885
         Width           =   120
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "R"
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
         Left            =   885
         TabIndex        =   5
         Top             =   525
         Width           =   120
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "CA210 Setting"
      BeginProperty Font 
         Name            =   "新細明體"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1695
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6375
      Begin VB.CommandButton btn_connect 
         Caption         =   "Connect"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   3480
         TabIndex        =   36
         Top             =   1080
         Width           =   1335
      End
      Begin VB.TextBox Text_Fre 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   270
         Left            =   2520
         TabIndex        =   18
         Text            =   "60.0"
         Top             =   360
         Width           =   620
      End
      Begin VB.ComboBox Combo_Dis 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         ItemData        =   "CA210MatrixCalibration.frx":030A
         Left            =   4680
         List            =   "CA210MatrixCalibration.frx":0314
         TabIndex        =   17
         Text            =   "Lvxy"
         Top             =   360
         Width           =   975
      End
      Begin VB.ComboBox Combo_CalStd 
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         ItemData        =   "CA210MatrixCalibration.frx":0325
         Left            =   1440
         List            =   "CA210MatrixCalibration.frx":032F
         TabIndex        =   15
         Text            =   "9300K"
         Top             =   1080
         Width           =   975
      End
      Begin VB.ComboBox Combo_Ave 
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         ItemData        =   "CA210MatrixCalibration.frx":0341
         Left            =   1440
         List            =   "CA210MatrixCalibration.frx":034E
         TabIndex        =   14
         Text            =   "AUTO"
         Top             =   720
         Width           =   975
      End
      Begin VB.ComboBox Combo_Sync 
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   300
         ItemData        =   "CA210MatrixCalibration.frx":0364
         Left            =   1440
         List            =   "CA210MatrixCalibration.frx":0377
         TabIndex        =   13
         Text            =   "NTSC"
         Top             =   360
         Width           =   975
      End
      Begin VB.Label Label12 
         Caption         =   "Display Mode"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   3585
         TabIndex        =   16
         Top             =   405
         Width           =   1095
      End
      Begin VB.Label Label2 
         Caption         =   "Sync Mode"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   510
         TabIndex        =   3
         Top             =   405
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "Speed"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   840
         TabIndex        =   2
         Top             =   765
         Width           =   495
      End
      Begin VB.Label Label4 
         Caption         =   "CalStandard"
         BeginProperty Font 
            Name            =   "新細明體"
            Size            =   9
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   435
         TabIndex        =   1
         Top             =   1125
         Width           =   975
      End
   End
   Begin MSComDlg.CommonDialog cmdDiag 
      Left            =   5520
      Top             =   4560
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
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
      Index           =   1
      Left            =   2160
      TabIndex        =   50
      Top             =   5400
      Width           =   4395
   End
End
Attribute VB_Name = "MatrixCalib"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub btn_connect_Click()
objCa.RemoteMode = 1
End Sub
Private Sub btn_Disconnect_Click()
objCa.RemoteMode = 0


End Sub

Private Sub btn_LoadAll_Click()

Dim strpath As String
strpath = IIf(Right(App.Path, 1) = "\", App.Path, App.Path & "\")
Dim iCheck As Integer

iCheck = MsgBox("Are You Sure To Load File To CA-210 ?", vbOKCancel + vbExclamation)
    
If iCheck = 2 Then
    Exit Sub
End If
 
 Dim i As Integer
 Dim CH_S As Integer
 Dim CH_E As Integer
 Dim fm As String
 CH_S = Val(Text_CHS.Text)
 CH_E = Val(Text_CHE.Text)
 
 objCa.RemoteMode = 1
 
On Error GoTo E
 For i = CH_S To CH_E
    objMemory.ChannelNO = i
    fm = strpath + "CH" + Str(i)
    objMemory.CopyFromFile objProbe.Number, fm
 Next i

Exit Sub


E:
    
    '===================================
    ' Error Trap
    '===================================
    Dim strERR As String
    Dim iReturn As Integer
    
    strERR = "Error from " + Err.Source + Chr$(10) + Chr$(13)
    strERR = strERR + Err.Description + Chr$(10) + Chr$(13)
    strERR = strERR + "HRESULT " + CStr(Err.Number - vbObjectError)
    iReturn = MsgBox(strERR, vbAbortRetryIgnore)
    Select Case iReturn
        Case vbAbort: End
        Case vbRetry: Resume
        Case vbIgnore: Resume Next
    End Select



End Sub
Private Sub btn_LoadM_Click()
 Dim fm As String, fnum As Integer, fname As String
    'Dim iCheck As Integer
    
    'iCheck = MsgBox("Are you sure to load file to CA-210", vbOKCancel)
    
    'If iCheck = 2 Then
    'Exit Sub
    'End If
    
    On Error Resume Next
    cmdDiag.CancelError = True
    cmdDiag.filename = "*.xls"
    cmdDiag.Filter = "CS-1000 data (*.xls)|*.xls"
    cmdDiag.FilterIndex = 2
    cmdDiag.Action = 1
    If Err.Number = cdlCancel Then
        Exit Sub
    Else
        fm = cmdDiag.filename
        fm = Mid$(fm, 1, InStr(1, fm, ".")) + "xls"
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
    Dim Rx, Ry, RL As Single
    Dim Gx, Gy, GL As Single
    Dim Bx, By, BL As Single
    Dim Wx, Wy, WL As Single
    
    If xlsheet.Cells(1, 2) = "Red_L" Then 'Spectrum
      
        RL = xlsheet.Cells(2, 2)
        Rx = xlsheet.Cells(2, 3)
        Ry = xlsheet.Cells(2, 4)
        GL = xlsheet.Cells(2, 5)
        Gx = xlsheet.Cells(2, 6)
        Gy = xlsheet.Cells(2, 7)
        BL = xlsheet.Cells(2, 8)
        Bx = xlsheet.Cells(2, 9)
        By = xlsheet.Cells(2, 10)
        WL = xlsheet.Cells(2, 11)
        Wx = xlsheet.Cells(2, 12)
        Wy = xlsheet.Cells(2, 13)
    ElseIf xlsheet.Cells(1, 1) = "Red" Then
        RL = xlsheet.Cells(3, 4)
        Rx = xlsheet.Cells(3, 5)
        Ry = xlsheet.Cells(3, 6)
        GL = xlsheet.Cells(4, 4)
        Gx = xlsheet.Cells(4, 5)
        Gy = xlsheet.Cells(4, 6)
        BL = xlsheet.Cells(5, 4)
        Bx = xlsheet.Cells(5, 5)
        By = xlsheet.Cells(5, 6)
        WL = xlsheet.Cells(2, 4)
        Wx = xlsheet.Cells(2, 5)
        Wy = xlsheet.Cells(2, 6)
    Else
         MsgBox "Invalid Data", vbOKOnly
         xlBook.Close
         xlApp.Quit
         Exit Sub
    End If
    
    Text1(0).Text = Rx
    Text1(1).Text = Ry
    Text1(2).Text = RL
    Text1(3).Text = Gx
    Text1(4).Text = Gy
    Text1(5).Text = GL
    Text1(6).Text = Bx
    Text1(7).Text = By
    Text1(8).Text = BL
    Text1(9).Text = Wx
    Text1(10).Text = Wy
    Text1(11).Text = WL
    xlBook.Close
    xlApp.Quit
    
End Sub
Private Sub btn_MatrixC_Click()
Dim x As Integer
Dim y As Integer
Dim bSetMode As Boolean
Dim ch As Integer
Dim Sync As Integer
Dim Ave As Integer
Dim CalStd As Integer
Dim Dis As Integer

Go_ahead = True
MainForm.WindowState = 1
On Error GoTo E

ch = Val(Text_ch.Text)
Source_CH = ch
Sync = Combo_Sync.ListIndex
Ave = Combo_Ave.ListIndex
Dis = Combo_Dis.ListIndex
CalStd = Combo_CalStd.ListIndex
'X = Val(Text_X.Text)
'Y = Val(Text_Y.Text)


If Combo_Sync.Text = "INT" Then
    Sync = Val(Text_Fre.Text)
Else
    Sync = Combo_Sync.ListIndex
End If
    
objCa.RemoteMode = 1

objCa.SyncMode = Sync

objCa.AveragingMode = Ave
objCa.DisplayMode = 0
objCa.CalStandard = CalStd + 1
objMemory.ChannelNO = ch

If objMemory.ChannelNO = 0 Then
    MsgBox "CH00 cannot be calibrated", vbOKOnly
    Exit Sub
End If


bSetMode = False
objCa.SetLvxyCalMode
bSetMode = True
'Background.Width = X
'Background.Height = Y
Background.visible = True

'-------------------------------------------
'Red
'-------------------------------------------
Call PatternRGB(Val(Text_MxR.Text), 0, 0)
Call Tims(10)
objCa.Measure
objCa.SetLvxyCalData 0, Val(Text1(0).Text), Val(Text1(1).Text), Val(Text1(2).Text)




Call PatternRGB(0, Val(Text_MxG.Text), 0)
Call Tims(10)
objCa.Measure
objCa.SetLvxyCalData 1, Val(Text1(3).Text), Val(Text1(4).Text), Val(Text1(5).Text)


Call PatternRGB(0, 0, Val(Text_MxB.Text))
Call Tims(10)
objCa.Measure
objCa.SetLvxyCalData 2, Val(Text1(6).Text), Val(Text1(7).Text), Val(Text1(8).Text)


Call PatternRGB(Val(Text_MxR.Text), Val(Text_MxG.Text), Val(Text_MxB.Text))
Call Tims(15)
objCa.Measure
objCa.SetLvxyCalData 3, Val(Text1(9).Text), Val(Text1(10).Text), Val(Text1(11).Text)


objCa.Enter
Call SetID
objCa.RemoteMode = 0
MainForm.visible = True
Unload Background
'Background.Visible = False



MsgBox "Matrix Calibration is Success!", vbOKOnly
Exit Sub

E:
    '===================================
    ' Error Trap
    '===================================
    If bSetMode = True Then
        objCa.ResetLvxyCalMode
    End If

    Dim strERR As String
    Dim iReturn As Integer
    
    strERR = "Error from " + Err.Source + Chr$(10) + Chr$(13)
    strERR = strERR + Err.Description + Chr$(10) + Chr$(13)
    strERR = strERR + "HRESULT " + CStr(Err.Number - vbObjectError)
    MsgBox strERR, vbOKOnly
    objCa.RemoteMode = 0


End Sub

Private Sub SetID()
objMemory.ChannelNO = Val(Text_ch.Text)
Dim strID As String
strID = UCase(objMemory.ChannelID)

If UCase(Text_ID.Text) <> strID Then 'CA-210 Can't set the same IDName and empty

    If Text_ID.Text = "" Then
    objMemory.SetChannelID "  "
    objMemory.SetChannelID " "
    
    Else
    objMemory.SetChannelID UCase(Text_ID.Text)
    End If
End If


End Sub




Private Sub btn_saveall_Click()
    
    Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
        
        sheet.cell(1, 1) = "CH No."
        sheet.cell(1, 2) = "CH ID"
     
 Dim strpath As String
 strpath = IIf(Right(App.Path, 1) = "\", App.Path, App.Path & "\")
 
 Dim i As Integer
 Dim CH_S As Integer
 Dim CH_E As Integer
 Dim fm As String
 CH_S = Val(Text_CHS.Text)
 CH_E = Val(Text_CHE.Text)

 objCa.RemoteMode = 1
 For i = CH_S To CH_E
    objMemory.ChannelNO = i
    fm = strpath + "CH" + Str(i)
    objMemory.CopyToFile objProbe.Number, fm
    sheet.cell(i + 2, 1) = i
    sheet.cell(i + 2, 2) = objMemory.ChannelID
 Next i
 
 sheet.setSheetFilename strpath + "BACKUP"
 sheet.store
 sheet.closing

End Sub

Private Sub Combo_Sync_Click()

If Combo_Sync.Text = "INT" Then

    Text_Fre.Enabled = True
    Else
    Text_Fre.Enabled = False
End If
End Sub
Private Sub MatrixCalib_Load()
Combo_Sync.ListIndex = 0
Combo_Ave.ListIndex = 2
Combo_CalStd.ListIndex = 1
Combo_Dis.ListIndex = 0
End Sub



Private Sub Form_Load()
Combo_Sync.ListIndex = 0
Combo_Ave.ListIndex = 2
Combo_CalStd.ListIndex = 1
Combo_Dis.ListIndex = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
'End
End Sub

Private Sub Text_CH_Change()
ch = Val(Text_ch.Text)
If ch < 1 Or ch > 99 Then
x = MsgBox("Please input 1 to 99!", vbOKOnly + vbExclamation, "Error")
Text_ch.Text = 1
End If
End Sub

Private Sub Text_CHE_Change()
ch = Val(Text_CHE.Text)
If ch < 1 Or ch > 99 Then
x = MsgBox("Please input 1 to 99!", vbOKOnly + vbExclamation, "Error")
Text_CHE.Text = 99
End If
End Sub

Private Sub Text_CHS_Change()
ch = Val(Text_CHS.Text)
If ch < 1 Or ch > 99 Then
x = MsgBox("Please input 1 to 99!", vbOKOnly + vbExclamation, "Error")
Text_CHS.Text = 1
End If
End Sub

