//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HueSatVal2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "HueSatVal1"
#pragma resource "*.dfm"
THSVForm2 *HSVForm2;
//---------------------------------------------------------------------------
__fastcall THSVForm2::THSVForm2(TComponent * Owner)
:THSVForm1(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall THSVForm2::sb_Hue_gainScroll(TObject * Sender,
					     TScrollCode ScrollCode, int &ScrollPos)
{
    //double sigma = 0;
    if (ScrollCode != scEndScroll) {
	return;
    }
    int tbl_n = 24;
    //copy過去的用意是??
    for (int i = 0; i < tbl_n; i++) {
	Hue_table_t[i] = Hue_table[i];
	Sat_table_t[i] = Sat_table[i];
	Val_table_t[i] = Val_table[i];
    }

    //將使用者輸入的角度換成table表中的index
    //le_ChAangle: 從RGBCMY中選中的色相角
    //tbl_idx: 色相角對映到LUT的index
    int tbl_idx = Get_select_idx(StrToFloat(le_ChAangle->Text));

    //將scroll bar的值顯示出來
    show_gain(sb_Hue_gain->Position, sb_Sat_gain->Position, sb_Val_gain->Position);
    int gain_h = sb_Hue_gain->Position;	// Hue值為Gain
    int gain_s = sb_Sat_gain->Position - Sat_table[tbl_idx];	// 調整值與table數值的差異為gain
    int gain_v = sb_Val_gain->Position - Val_table[tbl_idx];
    //依照值域(-96~96)來說, 這兩個判斷式應該沒有發生的可能!?
    if (gain_h > 768 / 2) {
	gain_h -= 768;
    } else if (gain_h < (-1) * 768 / 2) {
	gain_h += 768;
    }
    //set按鈕是用來把調整量真正傳送到LUT
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	//似乎是為了diffusion, 所以才展開抓9個值
	int tmp_H[9], tmp_S[9], tmp_V[9];
	Get_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);

	//=====================================================================
	//diffusion
	//=====================================================================
	int low = (4 - sb_dif_n->Position);
	int high = sb_dif_p->Position;

	/*bool dif_ok = CheckDif(high, low, tmp_H, gain_h);
	   if (dif_ok == 0)
	   return; */
	/*sb_dif_p->Position = high;
	   sb_dif_n->Position = 4 - low; */
	tmp_H[4] += gain_h;
	tmp_S[4] += gain_s;
	tmp_V[4] += gain_v;
	//double ratio;

	//=====================================================================
	// high
	//=====================================================================
	//設定diffusion的變化
	/*if (high == 4)
	   sigma = 0.4;
	   else if (high == 3)
	   sigma = 0.5;
	   else if (high == 2)
	   sigma = 0.6;


	   for (int i = 1; i < high; i++) {
	   ratio = pow(double (high - i) / high, 2) + (double) i / high * Gauss(i, sigma);
	   tmp_H[i + 4] = tmp_H[i + 4] + gain_h * ratio;
	   tmp_S[i + 4] = tmp_S[i + 4] + gain_s * ratio;
	   tmp_V[i + 4] = tmp_V[i + 4] + gain_v * ratio;
	   } */
	//=====================================================================

	//=====================================================================
	// low
	//=====================================================================
	/*if (low == 4)
	   sigma = 0.4;
	   else if (low == 3)
	   sigma = 0.5;
	   else if (low == 2)
	   sigma = 0.6;

	   for (int i = 1; i < low; i++) {
	   ratio = pow(double (low - i) / low, 2) + (double) i / low * Gauss(i, sigma);
	   tmp_H[4 - i] = tmp_H[4 - i] + gain_h * ratio;
	   tmp_S[4 - i] = tmp_S[4 - i] + gain_s * ratio;
	   tmp_V[4 - i] = tmp_V[4 - i] + gain_v * ratio;
	   } */
	//=====================================================================
	//=====================================================================


	Set_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);
	if (!CheckHueIncrease(high, low, tmp_H)) {
	    ShowMessage("Hue value has inverse.");
	    btn_set->Enabled = false;
	    return;
	}
    } else {			//rotation
	//全部一起調整一樣的量
	for (int i = 0; i < tbl_n; i++) {
	    Hue_table_t[i] = (Hue_table[i] + gain_h + 768) % 768;
	    Sat_table_t[i] = Sat_table[i] + gain_s;
	    Val_table_t[i] = Val_table[i] + gain_v;
	}
    }

    //=========================================================================
    // 將結果填到table中
    //=========================================================================
    for (int i = 0; i < tbl_n; i++) {
	sg_HSV->Cells[1][i + 1] = FloatToStr((double) Hue_table_t[i] / 768 * 360);
	sg_HSV->Cells[2][i + 1] = FloatToStr((double) (Sat_table_t[i]) / 32);
	sg_HSV->Cells[3][i + 1] = Val_table_t[i];
    }
    for (int i = 0; i < 3; i++) {
	sg_6HSV->Cells[i][0] = sg_HSV->Cells[i + 1][1];	//Red
	sg_6HSV->Cells[i][1] = sg_HSV->Cells[i + 1][5];	//Yellow
	sg_6HSV->Cells[i][2] = sg_HSV->Cells[i + 1][9];	//Green
	sg_6HSV->Cells[i][3] = sg_HSV->Cells[i + 1][13];	//Cyan
	sg_6HSV->Cells[i][4] = sg_HSV->Cells[i + 1][17];	//Blue
	sg_6HSV->Cells[i][5] = sg_HSV->Cells[i + 1][21];	//Magenta
	sg_6HSV->Cells[i][6] = sg_HSV->Cells[i + 1][tbl_idx + 1];
    }
    //=========================================================================
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2::sb_Hue_gainChange(TObject * Sender)
{
    show_gain(sb_Hue_gain->Position, sb_Sat_gain->Position, sb_Val_gain->Position);
}

//---------------------------------------------------------------------------





