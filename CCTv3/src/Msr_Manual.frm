VERSION 5.00
Begin VB.Form Msr_Manual 
   Caption         =   "Manual"
   ClientHeight    =   3192
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   4680
   Icon            =   "Msr_Manual.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   3192
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Source CH"
      Height          =   885
      Left            =   1275
      TabIndex        =   1
      Top             =   360
      Width           =   2010
      Begin VB.TextBox Text_C 
         Alignment       =   2  'Center
         Height          =   390
         Left            =   540
         TabIndex        =   2
         Text            =   "0"
         Top             =   300
         Width           =   855
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Measure"
      Height          =   675
      Left            =   1320
      TabIndex        =   0
      Top             =   1665
      Width           =   1920
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
      Left            =   120
      TabIndex        =   3
      Top             =   2820
      Width           =   4395
   End
End
Attribute VB_Name = "Msr_Manual"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private sheet As SpreadSheet

Private Sub Command1_Click()
    objCa.RemoteMode = 1
    objMemory.ChannelNO = Val(Text_C.Text)
    Call RGBcal.CADataCT210(Cx, Cy, Yx, CT, uv, LR, LG, LB)
    'Call Background.BGShow2(X2, Yx, 0)
    'Background.BKB2 = Yx
    row1 = row1 + 1
    
    sheet.cell(row1, 1) = row1 - 1
    
    sheet.cell(row1, 2) = Cx
    sheet.cell(row1, 3) = Cy
    sheet.cell(row1, 4) = Yx
    sheet.cell(row1, 5) = CT
    sheet.cell(row1, 6) = uv
    sheet.cell(row1, 7) = LR
    sheet.cell(row1, 8) = LG
    sheet.cell(row1, 9) = LB
End Sub

Private Sub Form_Load()
    row1 = 1
    'Dim sheet As SpreadSheet
    Set sheet = Utils.newSheet
    
    sheet.cell(1, 1) = "Pattern NO."
    sheet.cell(1, 2) = "W_x"
    sheet.cell(1, 3) = "W_y"
    sheet.cell(1, 4) = "W_Y (nit)"
    sheet.cell(1, 5) = "W_C.T."
    sheet.cell(1, 6) = "£GUV"
    sheet.cell(1, 7) = "W_R"
    sheet.cell(1, 8) = "W_G"
    sheet.cell(1, 9) = "W_B"
    
    
    '''''' Start Test
    
End Sub
