VERSION 5.00
Begin VB.Form ConfigForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Config"
   ClientHeight    =   2736
   ClientLeft      =   36
   ClientTop       =   312
   ClientWidth     =   6120
   Icon            =   "ChromaForm.frx":0000
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2736
   ScaleWidth      =   6120
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command3 
      Caption         =   "Connect"
      Height          =   372
      Left            =   3960
      TabIndex        =   4
      Top             =   720
      Width           =   975
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Disconnect"
      Height          =   372
      Left            =   5040
      TabIndex        =   3
      Top             =   720
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   372
      Left            =   3960
      TabIndex        =   2
      Top             =   1920
      Width           =   1935
   End
   Begin VB.Frame Frame1 
      Caption         =   "CA-210"
      Height          =   2172
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3732
      Begin VB.ComboBox DM 
         Height          =   288
         ItemData        =   "ChromaForm.frx":030A
         Left            =   1320
         List            =   "ChromaForm.frx":0326
         TabIndex        =   8
         Top             =   1560
         Width           =   2172
      End
      Begin VB.ComboBox MR 
         Height          =   288
         ItemData        =   "ChromaForm.frx":0394
         Left            =   1320
         List            =   "ChromaForm.frx":03A1
         TabIndex        =   6
         Top             =   960
         Width           =   852
      End
      Begin VB.ComboBox SyncM 
         Height          =   288
         ItemData        =   "ChromaForm.frx":03B7
         Left            =   1320
         List            =   "ChromaForm.frx":03C7
         TabIndex        =   5
         Top             =   360
         Width           =   852
      End
      Begin VB.Label Label3 
         Caption         =   "Display Mode"
         Height          =   252
         Left            =   240
         TabIndex        =   9
         Top             =   1560
         Width           =   1332
      End
      Begin VB.Label Label2 
         Caption         =   "Measure Rate"
         Height          =   252
         Left            =   240
         TabIndex        =   7
         Top             =   960
         Width           =   1332
      End
      Begin VB.Label Label1 
         Caption         =   "Sync Mode"
         Height          =   252
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   1332
      End
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      Caption         =   "Copyright (C) 2005. AU Optronics Corp., All Rights Reserved"
      BeginProperty Font 
         Name            =   "·s²Ó©úÅé"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   180
      Left            =   1560
      TabIndex        =   10
      Top             =   2400
      Width           =   4395
   End
End
Attribute VB_Name = "ConfigForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
    Call MinoltaP
    
    objCa.SyncMode = SyncM1
    objCa.AveragingMode = MR1
    objCa.DisplayMode = DM1
    
End Sub


Private Sub Command2_Click()
    objCa.RemoteMode = 0
End Sub


Private Sub Command3_Click()
    objCa.RemoteMode = 1
End Sub


Private Sub Form_Load()
    
    SyncM.ListIndex = SyncM1
    MR.ListIndex = MR1
    DM.ListIndex = DM1
    
    
End Sub
