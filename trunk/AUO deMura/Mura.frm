VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   Caption         =   "Mura"
   ClientHeight    =   4650
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10125
   Icon            =   "Mura.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4650
   ScaleWidth      =   10125
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command4 
      Caption         =   "END"
      Height          =   435
      Left            =   8100
      TabIndex        =   8
      Top             =   3960
      Width           =   1935
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Select Picture"
      Height          =   435
      Left            =   8100
      TabIndex        =   7
      Top             =   120
      Width           =   1935
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Start"
      Height          =   435
      Left            =   8100
      TabIndex        =   6
      Top             =   1200
      Width           =   1935
   End
   Begin MSComctlLib.ProgressBar ProgressBar1 
      Height          =   255
      Left            =   0
      TabIndex        =   4
      Top             =   4260
      Width           =   7935
      _ExtentX        =   13996
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   1
   End
   Begin VB.Frame Frame1 
      Height          =   1035
      Left            =   0
      TabIndex        =   3
      Top             =   3120
      Width           =   8055
      Begin VB.Label Label2 
         Caption         =   "Label2"
         Height          =   795
         Left            =   60
         TabIndex        =   5
         Top             =   180
         Width           =   7875
      End
   End
   Begin VB.PictureBox Picture2 
      AutoRedraw      =   -1  'True
      Height          =   2955
      Left            =   4140
      ScaleHeight     =   193
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   257
      TabIndex        =   2
      Top             =   60
      Width           =   3915
   End
   Begin VB.PictureBox inPic 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      Height          =   555
      Left            =   780
      ScaleHeight     =   33
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   37
      TabIndex        =   1
      Top             =   2400
      Visible         =   0   'False
      Width           =   615
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   180
      Top             =   2520
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.PictureBox Picture1 
      AutoRedraw      =   -1  'True
      Height          =   2955
      Left            =   60
      ScaleHeight     =   193
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   257
      TabIndex        =   0
      Top             =   60
      Width           =   3915
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Option Explicit

Dim MyBit As Integer
Dim Dispbit As Integer
Dim Pic() As Single
Dim inPicWid As Integer
Dim inPicHgt As Integer
Dim inPicBitPixel As Integer



Dim FileMuraData() As Integer   '8bit  H x V x Plane x RGB
Dim FileMuraNumH As Integer
Dim FileMuraNumV As Integer
Dim InputPicture() As Integer  '10bit
Dim OutputPicture() As Integer  '12bit
Dim PictureWidth As Integer
Dim PictureHeight As Integer







Private Sub Command1_Click()

'**************     Picture Select    *************************************


Dim i As Integer
Dim ii As Integer

Dim j As Integer
Dim jj As Integer

Dim c As Integer


Dim Color As Integer
Dim N As Integer


Dim PictureName As String

Dim IniDir As String
Dim Data_file As String





    '**********  ファイルの指定  *****************************

        CommonDialog1.FileName = ""
        CommonDialog1.InitDir = App.Path & "\data"
        CommonDialog1.Filter = "bmp|*.bmp"
        CommonDialog1.ShowOpen
        Data_file = CommonDialog1.FileName
            If Data_file = "" Then Exit Sub

        PictureName = CommonDialog1.FileTitle












inPic.Picture = LoadPicture(Data_file)  'Input Picture

'画像の分析
hbm = inPic.Picture
status = GetObject(hbm, BITMAP_SIZE, bm)
inPicWid = bm.bmWidthBytes
inPicHgt = bm.bmHeight
inPicBitPixel = bm.bmBitsPixel  '24bit or 32bit

    Select Case inPicBitPixel
    Case 24
    Dispbit = 3
    inPicWid = inPicWid \ Dispbit
    Case 32
    Dispbit = 4
    inPicWid = inPicWid \ Dispbit
    Case Else
    MsgBox "24bit or 32bit のbmpを選択してください"
    Exit Sub
    End Select

Label2.Caption = PictureName & Chr$(13)
Label2.Caption = Label2.Caption & "Picture Size  " & inPicWid & " x " & inPicHgt & "   " & inPicBitPixel & "bit"


Picture1.Width = 256 * 15 + 60
Picture1.Height = 192 * 15 + 60
Picture1.PaintPicture inPic.Picture, 0, 0, 256, 192, 0, 0, inPicWid, inPicHgt '全体表示
Picture1.Refresh


Picture2.Width = 256 * 15 + 60
Picture2.Height = 192 * 15 + 60
Picture2.PaintPicture inPic.Picture, 0, 0, 256, 192, 0, 0, inPicWid, inPicHgt '全体表示
Picture2.Refresh



'********** ビットマップ画像の取得    **********
    
    hbm = Picture1.Image
    status = GetObject(hbm, BITMAP_SIZE, bm)
    wid = bm.bmWidthBytes
    hgt = bm.bmHeight
    BitPixel = bm.bmBitsPixel  '24bit or 32bit
    Dispbit = BitPixel \ 8
    PictureWidth = wid \ Dispbit
    PictureHeight = hgt
    ReDim bytes(1 To wid, 1 To hgt)
    ReDim InputPicture(0 To wid / Dispbit - 1, 0 To hgt - 1, 3) 'Wid=1024  hgt=192
    ReDim OutputPicture(0 To wid / Dispbit - 1, 0 To hgt - 1, 3) 'Wid=1024  hgt=192
    
    status = GetBitmapBits(hbm, wid * hgt, bytes(1, 1))
    
    For Color = 1 To 3
    For j = 0 To hgt - 1
    For i = 0 To wid \ Dispbit - 1
    InputPicture(i, j, Color) = 4 * bytes(i * Dispbit + 4 - Color, j + 1) 'assigned to InputPicture  10bit
    Next i
    Next j
    Next Color



Command3.Enabled = True




End Sub







Private Sub Command3_Click()


ProgressBar1.Value = 0





'****************   de-Mura Calculation  ***********************************



'de-Mura LUT data
Dim deMuraLUT() As Integer 'H , V , Plane , RGB



'Tcon Register
Dim PlaneLevel1 As Integer '10bit
Dim PlaneLevel2 As Integer '10bit
Dim PlaneLevel3 As Integer '10bit

Dim PixelMode As Byte   '4x16 or 8x8 or 16x4
Dim ColorMode As Byte   'Color de-Mura or Luminous de-mura

Dim PlaneB1Coef As Long   'Coefficient between Black and Plane1
Dim Plane12Coef As Long   'Coefficient between Plane1 and Plane2  　　2^16/(Plane2-Plane1) の下位12bit
Dim Plane23Coef As Long   'Coefficient between Plane2 and Plane3　　　2^16/(Plane3-Plane2) の下位12bit
Dim Plane3WCoef As Long   'Coefficient between Plane3 and White

Dim BlackLimitPictureLevel As Long  '10bit
Dim WhiteLimitPictureLevel As Long  '10bit

Dim DataMag(3) As Byte  '2bit x 3Plane =6bit    Data bitShift   MuraData<<1 ,  MuraData<<2 , MuraData<<3
Dim DataOffset(3) As Integer '10bit x 3Plane    Data offset -512 to 511





'My Variable   no need Tcon
Dim i As Integer
Dim j As Integer
Dim Color As Integer
Dim Plane As Integer
Dim Temp As Integer
Dim TempLong As Long

Dim MuraHpixel As Integer  '4,8,16
Dim MuraVpixel As Integer  '4,8,16
Dim MuranumH As Integer   '0 to
Dim MuranumV As Integer
Dim ModuloH As Integer
Dim ModuloV As Integer


Dim S1 As Integer
Dim S2 As Integer
Dim S3 As Integer
Dim S4 As Integer

Dim deMuravalue(3, 3) As Integer  'Plane,RGB
Dim TotaldeMuraValue(3) As Long   'RGB

Dim Hosei12bit(256, 192, 3) As Integer
Dim deMuraSingle(256, 192, 3, 3) As Single












' Register Setting   --------------------------------------------------

PixelMode = 1

        Select Case PixelMode
            Case 0
            MuraHpixel = 4
            MuraVpixel = 16
            Case 1
            MuraHpixel = 8
            MuraVpixel = 8
            Case 2
            MuraHpixel = 16
            MuraVpixel = 4
        End Select


PlaneLevel1 = 100  '10bit    over 17 10%
PlaneLevel2 = 204  '10bit 20%
PlaneLevel3 = 502  '10bit 50%

DataMag(1) = 0 'Plane1
DataMag(2) = 0 'Plane2
DataMag(3) = 1 'Plane3

DataOffset(1) = 10 'Plane1
DataOffset(2) = 0 'Plane2
DataOffset(3) = -10 'Plane3



PlaneB1Coef = Round(0 * (2 ^ 15) / PlaneLevel1)     '0 to 2047  11bit

Plane12Coef = Round(2 ^ 16 / (PlaneLevel2 - PlaneLevel1))   '12bit  PlaneLevel2 - PlaneLevel1 >= 17
Plane23Coef = Round(2 ^ 16 / (PlaneLevel3 - PlaneLevel2))   '12bit  PlaneLevel3 - PlaneLevel2 >= 17

Plane3WCoef = Round(0 / (1020 - PlaneLevel3) * (2 ^ 15))  '0 to 2047  11bit


BlackLimitPictureLevel = PlaneLevel1 - (2 ^ 16) \ (PlaneB1Coef * 2 + 1)  '10bit
If BlackLimitPictureLevel < 0 Then BlackLimitPictureLevel = 0


WhiteLimitPictureLevel = PlaneLevel3 + (2 ^ 16) \ (Plane3WCoef * 2 + 1)  '10bit
If WhiteLimitPictureLevel > 1023 Then WhiteLimitPictureLevel = 1023






'**********  Load Mura File to de-Mura LUT  *****************************
    
Dim MuraFileName As String
Dim Data_file As String
Dim Dummy


    CommonDialog1.FileName = ""
    CommonDialog1.InitDir = App.Path & "\data"
    
        Select Case PixelMode
        Case 0
        CommonDialog1.Filter = "csv|*Mode0*.csv"
        Case 1
        CommonDialog1.Filter = "csv|*Mode1*.csv"
        Case 2
        CommonDialog1.Filter = "csv|*Mode2*.csv"
        End Select
        
    CommonDialog1.ShowOpen
    Data_file = CommonDialog1.FileName
    If Data_file = "" Then Exit Sub

    MuraFileName = CommonDialog1.FileTitle



Open Data_file For Input As #1
    
    Input #1, Dummy, FileMuraNumH, FileMuraNumV
    
    ReDim deMuraLUT(0 To (FileMuraNumH - 1), 0 To (FileMuraNumV - 1), 3, 3)
    
    
    For i = 4 To FileMuraNumH
    Input #1, Dummy
    Next i
    
    For Color = 1 To 3
    For Plane = 1 To 3
    For j = 0 To FileMuraNumV - 1
    For i = 0 To FileMuraNumH - 1
    
    Input #1, deMuraLUT(i, j, Plane, Color)
    
    Next i
    Next j
    Next Plane
    Next Color
    
    
Close #1


'----------------------------------------------------------------------








For Color = 1 To 3
For j = 0 To PictureHeight - 1
For i = 0 To PictureWidth - 1





        MuranumH = i \ MuraHpixel
        ModuloH = i Mod MuraHpixel
        
        MuranumV = j \ MuraVpixel
        ModuloV = j Mod MuraVpixel
        
        
'        ______________
'        |     |       |
'        | S1  |   S2  |
'        |-------------|
'        |     |       |
'        | S3  |   S4  |
'        |_____|_______|
'
' f(x,y) := (0,0)(1-x)(1-y)+(1,0)x(1-y)+(0,1)(1-x)y+(1,1)xy
        
        
        S1 = ModuloH * ModuloV '(1,1) xy
        S2 = (MuraHpixel - ModuloH) * ModuloV '(0,1) (1-x)y
        S3 = ModuloH * (MuraVpixel - ModuloV) '(1,0) x(1-y)
        S4 = (MuraHpixel - ModuloH) * (MuraVpixel - ModuloV) '(0,0) (1-x)(1-y)
        
            For Plane = 1 To 3
            
            deMuravalue(Plane, Color) = ((S4 * deMuraLUT(MuranumH, MuranumV, Plane, Color) _
                                        + S3 * deMuraLUT(MuranumH + 1, MuranumV, Plane, Color) _
                                        + S2 * deMuraLUT(MuranumH, MuranumV + 1, Plane, Color) _
                                        + S1 * deMuraLUT(MuranumH + 1, MuranumV + 1, Plane, Color)) * 2 ^ DataMag(Plane)) \ 64 _
                                        + DataOffset(Plane) * (2 ^ DataMag(Plane))
                                        
            
            Next Plane
        
        
        
            'Plane補間
            Select Case InputPicture(i, j, Color)
            
            
            Case Is < BlackLimitPictureLevel
            
                TotaldeMuraValue(Color) = 0
            
            Case BlackLimitPictureLevel To PlaneLevel1 - 1
            
            
                TotaldeMuraValue(Color) = deMuravalue(1, Color) _
                                            - (PlaneLevel1 - InputPicture(i, j, Color)) * PlaneB1Coef * deMuravalue(1, Color) / (2 ^ 15)
            
            
            Case PlaneLevel1 To PlaneLevel2 - 1
        
                                         
                TotaldeMuraValue(Color) = ((PlaneLevel2 - InputPicture(i, j, Color)) * CLng(deMuravalue(1, Color)) _
                                        + (InputPicture(i, j, Color) - PlaneLevel1) * CLng(deMuravalue(2, Color))) _
                                        * (Plane12Coef * 2 + 1) \ (2 ^ 17)
            
            
            Case PlaneLevel2 To PlaneLevel3 - 1
            
                TotaldeMuraValue(Color) = ((PlaneLevel3 - InputPicture(i, j, Color)) * CLng(deMuravalue(2, Color)) _
                                        + (InputPicture(i, j, Color) - PlaneLevel2) * CLng(deMuravalue(3, Color))) _
                                        * (Plane23Coef * 2 + 1) \ (2 ^ 17)
            
            
            
            Case PlaneLevel3 To WhiteLimitPictureLevel
            
                TotaldeMuraValue(Color) = deMuravalue(3, Color) _
                                            - (InputPicture(i, j, Color) - PlaneLevel3) * Plane3WCoef * deMuravalue(3, Color) \ (2 ^ 15)
        
            
            Case Is > WhiteLimitPictureLevel
            
                TotaldeMuraValue(Color) = 0
            
            End Select
            
            
            Hosei12bit(i, j, Color) = TotaldeMuraValue(Color)  'for Check
            OutputPicture(i, j, Color) = InputPicture(i, j, Color) * 4 + TotaldeMuraValue(Color)  'input picture 12bit + deMura
            'OutputPicture is 12bit
    
            If OutputPicture(i, j, Color) < 0 Then OutputPicture(i, j, Color) = 0         'Limit
            If OutputPicture(i, j, Color) > 4080 Then OutputPicture(i, j, Color) = 4080   'Limit
    

Next i
DoEvents
ProgressBar1.Value = ProgressBar1.Value + 1
Next j
Next Color












'Check de-Mura function  ---------------------------------------------------



Dim ii As Integer

Open App.Path & "\Result\OutputPicture12bit.csv" For Output As #1

    For Color = 1 To 3
    For j = 0 To 191
    For i = 0 To 254
        
    Write #1, OutputPicture(i, j, Color),
    
    Next i
    Write #1, OutputPicture(i, j, Color)
    DoEvents
    Next j
    Write #1,
    Next Color
    

Close #1
ProgressBar1.Value = ProgressBar1.Value + 30


Open App.Path & "\Result\deMura12bit.csv" For Output As #1

    For Color = 1 To 3
    For j = 0 To 191
    For i = 0 To 254
        
    Write #1, Hosei12bit(i, j, Color),
    
    Next i
    Write #1, Hosei12bit(i, j, Color)
    DoEvents
    Next j
    Write #1,
    Next Color

Close #1
ProgressBar1.Value = ProgressBar1.Value + 30






'********** ビットマップ画像の取得    **********
    
    hbm = Picture2.Image
    status = GetObject(hbm, BITMAP_SIZE, bm)
    wid = bm.bmWidthBytes
    hgt = bm.bmHeight
    BitPixel = bm.bmBitsPixel  '24bit or 32bit
    Dispbit = BitPixel \ 8
    PictureWidth = wid \ Dispbit
    PictureHeight = hgt
    ReDim bytes(1 To wid, 1 To hgt)
    
    
    status = GetBitmapBits(hbm, wid * hgt, bytes(1, 1))
    
    For Color = 1 To 3
    For j = 0 To hgt - 1
    For i = 0 To wid \ Dispbit - 1
    Temp = OutputPicture(i, j, Color)
    If Temp < 0 Then Temp = 0
    If Temp > 4080 Then Temp = 4080
     bytes(i * Dispbit + 4 - Color, j + 1) = Temp \ 16
    Next i
    DoEvents
    Next j
    Next Color

status = SetBitmapBits(hbm, wid * hgt, bytes(1, 1))
Picture2.Refresh


SavePicture Picture2.Image, App.Path & "\Result\OutPicture.bmp"

ProgressBar1.Value = ProgressBar1.Max

MsgBox "Finish   Please check result Folder"





End Sub

Private Sub Command4_Click()

End



End Sub

Private Sub Form_Load()

'DATA フォルダの作成
On Error Resume Next
MkDir (App.Path & "\Data")
On Error GoTo 0


'Result フォルダの作成
On Error Resume Next
MkDir (App.Path & "\Result")
On Error GoTo 0



Command1.Enabled = True
Command3.Enabled = False


ProgressBar1.Max = 700 '192 * 3 + 1






End Sub



