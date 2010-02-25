Attribute VB_Name = "MeasureTool"
Option Explicit

'******** Minolta
Public SyncM1 As Integer
Public MR1 As Integer
Public DM1 As Integer

'******** SDK Object
Public objCa200 As Ca200
Public objCa As Ca
Public objProbe As Probe
Public objMemory As Memory
Private initialized As Boolean
Public UseCA210 As Boolean


Public Function Measure()
        objCa.DisplayMode = 0
        objCa.Measure
        'Dx = objProbe.sx
        'Dy = objProbe.SY
        'YY = objProbe.Lv
        
        'objCa.DisplayMode = 1
        'objCa.measure
        'CT = objProbe.t
        'uv = objProbe.duv
        
        'objCa.DisplayMode = 3
        'objCa.measure
        'LR = objProbe.r
        'LG = objProbe.G
        'LB = objProbe.B
        
        Dim r As MeasureResult
        Call r.init(objProbe.sx, objProbe.SY, objProbe.Lv, objProbe.t, objProbe.duv, objProbe.r, _
        objProbe.G, objProbe.B)
        Set Measure = r
End Function

Public Sub initCA210()
On Error GoTo E:
        If initialized = True Then
            Exit Sub
        End If
        
        Set objCa200 = New Ca200
        objCa200.AutoConnect
        
        Set objCa = objCa200.SingleCa
        Set objProbe = objCa.SingleProbe
        Set objMemory = objCa.Memory
        
        SyncM1 = 0
        MR1 = 2
        DM1 = 0
        
        objCa.SyncMode = SyncM1
        objCa.AveragingMode = MR1
        
        initialized = True
        Exit Sub
E:
Call Utils.catch
End Sub
