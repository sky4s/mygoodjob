Attribute VB_Name = "Regress"

'''''''''Multiple Regress
Public Const N2 = 256 ' For every 8 Gray level measure
Public Const N22 = 257 ' For Gamma 256

Public Const ka = 4 ' For 3 independent variable Y= R G B
Public K As Integer ' For independent variable

Dim x(N2, ka) As Double, XT(ka, N2) As Double, y(N2, 1) As Double, YT(1, N2) As Double
Dim X2(N22, ka) As Double, XT2(ka, N22) As Double, Y2(N22, 1) As Double, YT2(1, N22) As Double
Dim InvXTXom(ka, 2 * ka) As Double
Dim XTX(ka, ka) As Double, InvXTX(ka, ka) As Double, XTY(ka, 1) As Double
Dim BetaT(1, ka) As Double
Dim BetaV(ka, ka) As Double, SEBeta(ka) As Double
Dim YTY As Double, BetaTXTY As Double
Dim RSS As Double
Dim TSS As Double
Dim ESS As Double
Dim RMS As Double
Dim MY As Double, SY As Double, AdjRsq As Double
Dim XTXD As Double
Dim XTYD As Double
Dim BetaD As Double
Dim YTYD As Double
Dim BetaTXTYD As Double

Public Beta(ka, 1) As Double
Public Rsq As Double
''''''''''''''''''''''''''''''''''''''''''''''''

'''''''' Simple Regress
Public SRC As Single
Const M = 200 ' For R,G,B intensity (%)
Dim Xs(M) As Double, Ys(M) As Double
Dim Es(M) As Single, Fs(M) As Single, Gs(M) As Single, Hs(M) As Single
Dim Ks(M) As Single, Ls(M) As Single, Ms(M) As Single

Public Beta1 As Double, Beta2 As Double
Public Rsqs As Double

'''' Reference (EXCEL EXERCISE #11: Bivariate Regression)

Sub SimpleRegress(SST As String)
    ''''''' Data loading for Y,X  ''''''''''''''''
    SD = Empty
    SD = Split(SST, ",")
    RDC = 0
    
    For i = 1 To SRC - 1
        Ys(i) = SD(RDC)
        RDC = RDC + 1
    Next i
    For i = 1 To SRC - 1
        Xs(i) = SD(RDC)
        RDC = RDC + 1
    Next i
    ''''''''''''''''''''''''''''''''''''''''''''''
    '''''''' Calculate (X,Y) Sum and Average
    Xssum = 0
    Yssum = 0
    Gssum = 0
    Hssum = 0
    Lssum = 0
    Mssum = 0
    
    For i = 1 To SRC - 1
        Xssum = Xssum + Xs(i)
        Yssum = Yssum + Ys(i)
    Next i
    
    Xsmean = Xssum / (SRC - 1)
    Ysmean = Yssum / (SRC - 1)
    '''''''''''''''''''''''''''''''''''''''''''''''
    '''''''' Calculate Es_(Yi-Ybar), Fs_(Xi-Xbar), Gs_(Fs*Es), Hs_(Xi-Xbar)^2
    For j = 1 To SRC - 1
        
        Es(j) = Ys(j) - Ysmean
        Fs(j) = Xs(j) - Xsmean
        Gs(j) = Fs(j) * Es(j)
        Hs(j) = Fs(j) ^ 2
        
        Gsum = Gsum + Gs(j)
        Hsum = Hsum + Hs(j)
        
    Next j
    '''''''''''''''''''''''''''''''''''''''''''''''
    '''''''' Calculator Beta «Y¼Æ
    Beta2 = Gsum / Hsum
    Beta1 = Ysmean - Beta2 * Xsmean
    '''''''''''''''''''''''''''''''''''''''''''''''
    '''''''''  Calculator R-Square
    For i = 1 To SRC - 1
        Ks(i) = Beta1 + Beta2 * Xs(i)
        Ls(i) = (Ys(i) - Ysmean) ^ 2
        Ms(i) = (Ys(i) - Ks(i)) ^ 2
        
        Lssum = Lssum + Ls(i)
        Mssum = Mssum + Ms(i)
    Next i
    
    Rsqs = (Lssum - Mssum) / Lssum
    
End Sub


'''' Reference http://WWW.geocities.com/WallStreet/9245/vba9.htm (Linear Multiple Regression)
'''' Reference http://www.freevbcode.com/ShowCode.Asp?ID=6221 (Matrix Inverse Calculator)
'''' Reference http://home.fh-mainz.de/~zenger/matrix.pdf (Matrixalgebra)


Sub MultipleRegress(SS As String, n As Integer)
    ''''''' Martix loading for Y,X1,X2,X3......
    RD = Split(SS, ",")
    RDC = 0
    
    For i = 1 To n
        Y2(i, 1) = RD(RDC)
        RDC = RDC + 1
        X2(i, 1) = 1
    Next i
    
    For i = 2 To K
        For j = 1 To n
            X2(j, i) = RD(RDC)
            RDC = RDC + 1
        Next j
    Next i
    
    '''''''''''''''''''''''''''''''''''''''''''''
    ''' Transpose X and Y (X' and Y')
    For i = 1 To K
        SY = 0
        For j = 1 To n
            XT2(i, j) = X2(j, i)
            YT2(1, j) = Y2(j, 1)
            SY = SY + Y2(j, 1)
        Next j
    Next i
    MY = SY / n
    '''''''''''''''''''''''''''''''''''''''''''''
    ''' XT*X
    For i = 1 To K
        For ii = 1 To K
            XTXD = 0
            For j = 1 To n
                XTXD = XTXD + XT2(i, j) * X2(j, ii)
            Next j
            XTX(i, ii) = XTXD
        Next ii
    Next i
    ''''''''''''''''''''''''''''''''''''''''''''''
    '''' InvXTX (Matrix Inverse Calculator) and XT*Y
    '''' Load XTX
    For i = 1 To K
        For j = 1 To K
            InvXTXom(i, j) = XTX(i, j)
        Next j
    Next i
    '''' Add Martix[I] at the InvXTXom Right
    For i = 1 To K
        For j = 1 To K
            If i = j Then
                InvXTXom(i, j + K) = 1
            Else
                InvXTXom(i, j + K) = 0
            End If
        Next j
    Next i
    '''' Build Martix[I] at the Left
    For i = 1 To K
        ''Bring a non-zero element
        If InvXTXom(i, i) = 0 Then
            For j = i To K
                If InvXTXom(j, i) <> 0 Then
                    LineA = j
                    Exit For
                End If
            Next j
            ''Change Linei with LineA
            For j = i To K * 2
                TempA = InvXTXom(i, j)
                InvXTXom(i, j) = InvXTXom(LineA, j)
                InvXTXom(LineA, j) = TempA
            Next j
        End If
        ''' '''''''Calculate
        Factor1 = InvXTXom(i, i)
        For j = i To K * 2
            InvXTXom(i, j) = InvXTXom(i, j) / Factor1
        Next j
        ''Ai1=Aij-A11*(Aij/A11)
        For ii = 1 To K
            If ii = i And ii = K Then Exit For 'finish
            If ii = i And ii < K Then ii = ii + 1 'Don't change element (already equal to1) go for next one
            If InvXTXom(ii, i) <> 0 Then ' If it is zero, stays as it is
                Factor2 = InvXTXom(ii, i) / InvXTXom(i, i)
                For j = i To K * 2
                    InvXTXom(ii, j) = InvXTXom(ii, j) - InvXTXom(i, j) * Factor2
                Next j
            End If
        Next ii
    Next i
    ''''''''''''' Assigh the Righr part to the Inverse Matrix InvXT*X
    For i = 1 To K
        For j = 1 To K
            InvXTX(i, j) = InvXTXom(i, K + j)
        Next j
    Next i
    ''''' XT*Y
    For i = 1 To K
        XTYD = 0
        For j = 1 To n
            XTYD = XTYD + XT2(i, j) * Y2(j, 1)
        Next j
        XTY(i, 1) = XTYD
    Next i
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    ''''Beta=InvXTX*XTY  «Y¼Æ B0,B1,B2.....
    For i = 1 To K
        BetaD = 0
        For j = 1 To K
            BetaD = BetaD + InvXTX(i, j) * XTY(j, 1)
        Next j
        Beta(i, 1) = BetaD
    Next i
    ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    '''' R Square
    ''BetaT
    For i = 1 To K
        BetaT(1, i) = Beta(i, 1)
    Next i
    ''YT*Y
    YTYD = 0
    For j = 1 To n
        YTYD = YTYD + YT2(1, j) * Y2(j, 1)
    Next j
    YTY = YTYD
    ''BetaT*XTY
    BetaTXTYD = 0
    For j = 1 To K
        BetaTXTYD = BetaTXTYD + BetaT(1, j) * XTY(j, 1)
    Next j
    BetaTXTY = BetaTXTYD
    ''RSS  regression sum of squares
    RSS = YTY - BetaTXTY
    ''RMS  resideual variance
    RMS = RSS / (n - K)
    ''TSS  total sum of squares
    TSS = YTY - n * MY ^ 2
    ''Ess  residual sum of squares
    ESS = BetaTXTY - n * MY ^ 2
    ''Rsq
    Rsq = ESS / TSS
    '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    
End Sub
