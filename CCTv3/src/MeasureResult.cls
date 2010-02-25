VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MeasureResult"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public x As Single
Public y As Single
Public luminance As Single
Public CCT As Single
Public duv As Single
Public r As Single
Public G As Single
Public B As Single

Public Sub init(xx As Single, YY As Single, lumi As Single, colorTemperature As Single, deltauv As Single, rr As Single, gg As Single, bb As Single)
    x = xx
    y = YY
    luminance = lumi
    CCT = colorTemperature
    duv = deltauv
    r = rr
    G = gg
    B = bb
End Sub

Public Sub setSheet(sheet As SpreadSheet, row As Integer)

End Sub
