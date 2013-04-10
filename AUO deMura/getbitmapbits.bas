Attribute VB_Name = "Module"
Public bytes() As Byte                          '全取得画像のカラーデータの格納用配列
Public hbm As Long
Public status As Long
Public wid As Long
Public hgt As Long
Public bm As BITMAP
Public BitPixel As Integer


Type BITMAP '24 bytes
        bmType As Long
        bmWidth As Long
        bmHeight As Long
        bmWidthBytes As Long
        bmPlanes As Integer
        bmBitsPixel As Integer
        bmBits As Long
End Type

Global Const BITMAP_SIZE = 24

Declare Function GetObject Lib "gdi32" Alias "GetObjectA" (ByVal hObject As Long, ByVal nCount As Long, lpObject As Any) As Long
Declare Function GetBitmapBits Lib "gdi32" (ByVal hBitmap As Long, ByVal dwCount As Long, lpBits As Any) As Long
Declare Function SetBitmapBits Lib "gdi32" (ByVal hBitmap As Long, ByVal dwCount As Long, lpBits As Any) As Long
Declare Function GetTickCount Lib "kernel32" () As Long



