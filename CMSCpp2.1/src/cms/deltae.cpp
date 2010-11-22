#include <includeall.h>
#pragma hdrstop
#include "deltae.h"


//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    using namespace java::lang;
    using namespace math;
    using namespace Indep;

     DeltaE::DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2):Lab1(Lab1),
	Lab2(Lab2), adaptedToD65(false), cie2000DeltaE(-1), cieDeltaE(-1), cie94DeltaE(-1) {

    };
    DeltaE::DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2,
		   bool adaptedToD65):Lab1(adaptedToD65 ? Lab1->
					   getLabAdaptedToD65() : Lab1),
	Lab2(adaptedToD65 ? Lab2->getLabAdaptedToD65() : Lab2), adaptedToD65(false),
	cie2000DeltaE(-1), cieDeltaE(-1), cie94DeltaE(-1) {

    }

    double DeltaE::CIE2000DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2,
				 double Kl, double Kc, double Kh) {
	calculateCIE2000Parameters(Lab1, Lab2, Kc, Kc, Kh);
	double dL = _CIE2000Parameters[0];
	double dC = _CIE2000Parameters[1];
	double dh = _CIE2000Parameters[2];
	double Sl = _CIE2000Parameters[3];
	double Sc = _CIE2000Parameters[4];
	double Sh = _CIE2000Parameters[5];
	double Rt = _CIE2000Parameters[6];

	_CIE2000DeltaLCH[0] = dL;
	_CIE2000DeltaLCH[1] = dC;
	_CIE2000DeltaLCH[2] = dh;

	double deltaE00 = Math::sqrt(Math::sqr(dL / (Sl * Kl)) +
				     Math::sqr(dC / (Sc * Kc)) +
				     Math::sqr(dh / (Sh * Kh)) +
				     Rt * (dC / (Sc * Kc)) * (dh / (Sh * Kh)));

	return deltaE00;
    };

    double DeltaE::CIEDeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2) {
	double dL, da, db;

	if (Lab1->L == 0 && Lab2->L == 0) {
	    return 0;
	}

	dL = Math::abs(Lab1->L - Lab2->L);
	da = Math::abs(Lab1->a - Lab2->a);
	db = Math::abs(Lab1->b - Lab2->b);

	return Math::pow(dL * dL + da * da + db * db, 0.5);
    }

    double DeltaE::CIE94DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2) {
	return CIE94DeltaE(Lab1, Lab2, GraphicArts);
    };
    double DeltaE::CIE94DeltaE(const Lab_ptr Lab1, const Lab_ptr Lab2, Material material) {
	double KL = 0, KC = 1, KH = 1, K1 = 0, K2 = 0;
	switch (material) {
	case GraphicArts:
	    KL = 1;
	    K1 = 0.045;
	    K2 = 0.015;
	    break;
	case Textiles:
	    KL = 2;
	    K1 = 0.048;
	    K2 = 0.014;
	    break;
	}
	double da = Lab1->a - Lab2->a;
	double db = Lab1->b - Lab2->b;
	CIELCh LCh1(Lab1);
	CIELCh LCh2(Lab2);


	double dL = LCh1.L - LCh2.L;
	double dC = LCh1.C - LCh2.C;
	double abc = Math::sqr(da) + Math::sqr(db) - Math::sqr(dC);
	abc = abc < 0 ? 0 : abc;
	double dH = Math::sqrt(abc);
	double SL = 1;
	double SC = 1 + K1 * LCh1.C;
	double SH = 1 + K2 * LCh1.C;
	double deltaE = Math::sqrt(Math::sqr(dL / (KL * SL)) +
				   Math::sqr(dC / (KC * SC)) + Math::sqr(dH / (KH * SH)));
	return deltaE;
    };

    double DeltaE::getCIE2000Deltaab() {
	getCIE2000DeltaE();
	double dC = CIE2000Parameters[1];
	double dh = CIE2000Parameters[2];
	double Sc = CIE2000Parameters[4];
	double Sh = CIE2000Parameters[5];
	double Rt = CIE2000Parameters[6];
	double Kc = CIE2000Parameters[8];
	double Kh = CIE2000Parameters[9];

	double deltaab = Math::sqrt(Math::sqr(dC / (Sc * Kc)) +
				    Math::sqr(dh / (Sh * Kh)) +
				    Rt * (dC / (Sc * Kc)) * (dh / (Sh * Kh)));
	return deltaab;
    }

    double DeltaE::getCIE2000DeltaE() {
	if (cie2000DeltaE == -1) {
	    cie2000DeltaE = CIE2000DeltaE(Lab1, Lab2, 1, 1, 1);
	    CIE2000DeltaLCh = double_array(new double[3]);
	    DoubleArray::arraycopy(_CIE2000DeltaLCH, 0, CIE2000DeltaLCh, 0, 3);
	    CIE2000Parameters = double_array(new double[10]);
	    DoubleArray::arraycopy(_CIE2000Parameters, 0, CIE2000Parameters, 0, 10);
	}
	return cie2000DeltaE;
    }

    double DeltaE::getCIEDeltaE() {
	if (cieDeltaE == -1) {
	    cieDeltaE = CIEDeltaE(Lab1, Lab2);
	}
	return cieDeltaE;
    }
    double DeltaE::getCIE94DeltaE() {
	if (cie94DeltaE == -1) {
	    cie94DeltaE = CIE94DeltaE(Lab1, Lab2);
	}
	return cie94DeltaE;
    }

    double DeltaE::RADIANES(double deg) {
	return (deg * Math::PI) / 180.;
    }
    void DeltaE::calculateCIE2000Parameters(const Lab_ptr Lab1,
					    const Lab_ptr Lab2, double Kl, double Kc, double Kh) {
	double L1 = Lab1->L;
	double a1 = Lab1->a;
	double b1 = Lab1->b;
	double C = Math::sqrt(Math::sqr(a1) + Math::sqr(b1));

	double Ls = Lab2->L;
	double as = Lab2->a;
	double bs = Lab2->b;
	double Cs = Math::sqrt(Math::sqr(as) + Math::sqr(bs));

	//==========================================================================
	// Neutral Correction (Derby)
	//==========================================================================
	double G = 0.5 *
	    (1 -
	     Math::sqrt(Math::pow((C + Cs) / 2, 7) /
			(Math::pow((C + Cs) / 2, 7) + Math::pow(25, 7))));

	double a_p = (1 + G) * a1;
	//==========================================================================

	double b_p = b1;
	double C_p = Math::sqrt(Math::sqr(a_p) + Math::sqr(b_p));
	double h_p = Math::atan2deg(a_p, b_p);

	double a_ps = (1 + G) * as;
	double b_ps = bs;
	double C_ps = Math::sqrt(Math::sqr(a_ps) + Math::sqr(b_ps));
	double h_ps = Math::atan2deg(a_ps, b_ps);

	double meanC_p = (C_p + C_ps) / 2;

	double meanh_p = Math::abs(h_ps - h_p) <= 180 ? (h_ps + h_p) / 2 : (h_ps + h_p - 360) / 2;

	double delta_h =
	    Math::abs(h_p - h_ps) <= 180 ? Math::abs(h_p - h_ps) : 360 - Math::abs(h_p - h_ps);
	double delta_L = Math::abs(L1 - Ls);
	double delta_C = Math::abs(C_p - C_ps);

	double delta_H = 2 * Math::sqrt(C_ps * C_p) * Math::sin(RADIANES(delta_h) / 2);
	//==========================================================================
	//Hue weighting function
	//==========================================================================
	//chroma correction
	double T = 1 - 0.17 * Math::cos(RADIANES(meanh_p - 30))
	    + 0.24 * Math::cos(RADIANES(2 * meanh_p))
	    + 0.32 * Math::cos(RADIANES(3 * meanh_p + 6))
	    - 0.2 * Math::cos(RADIANES(4 * meanh_p - 63));
	//hue correction
	double Sh = 1 + 0.015 * ((C_ps + C_p) / 2) * T;
	//==========================================================================

	//Lightness weight function (Leeds)
	double Sl = 1 +
	    (0.015 * Math::sqr((Ls + L1) / 2 - 50)) / Math::sqrt(20 +
								 Math::sqr((Ls + L1) / 2 - 50));
	//Chroma weighting function
	double Sc = 1 + 0.045 * (C_p + C_ps) / 2;

	//==========================================================================
	//Rotation Function
	//==========================================================================
	double delta_ro = 30 * Math::exp(-Math::sqr(((meanh_p - 275) / 25)));
	double Rc =
	    2 * Math::sqrt((Math::pow(meanC_p, 7)) / (Math::pow(meanC_p, 7) + Math::pow(25, 7)));
	double Rt = -Math::sin(2 * RADIANES(delta_ro)) * Rc;
	//==========================================================================

	_CIE2000Parameters[0] = delta_L;
	_CIE2000Parameters[1] = delta_C;
	_CIE2000Parameters[2] = delta_H;
	_CIE2000Parameters[3] = Sl;
	_CIE2000Parameters[4] = Sc;
	_CIE2000Parameters[5] = Sh;
	_CIE2000Parameters[6] = Rt;
	_CIE2000Parameters[7] = Kl;
	_CIE2000Parameters[8] = Kc;
	_CIE2000Parameters[9] = Kh;
    };
    double_array DeltaE::_CIE2000Parameters = double_array(new double[10]);
    double_array DeltaE::_CIE2000DeltaLCH = double_array(new double[3]);
}

