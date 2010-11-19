#ifndef INDEPENDH
#define INDEPENDH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "colorspace.h"

namespace cms {
    namespace colorspace {
	namespace independ {
	    enum CIEStandard {
		//CIE���Ѫ���
		ActualStandard,
		//�ץ�CIE����(�|���ǽT)
		IntentStandard
	    };
	    enum Degree {
		Two = 2, Ten = 10
	    };

	    enum NormalizeY {
		Normal100 = 100, Normal1 = 1, Not = -1
	    };

	    class CIEXYZ;

	    class DeviceIndependentSpace:public ColorSpace {
	      protected:
		Degree degree_;
		static double epsilon;
		static double kappa;
		int getNumberBands();
		XYZ_ptr white;
		XYZ_ptr originalWhite;
		boolean adaptedToD65;

		 DeviceIndependentSpace();
		 DeviceIndependentSpace(XYZ_ptr white);
	      public:
		 boolean isAdaptedToD65();
		Degree getDegree();
		void setDegree(Degree degree);
		static void setCIEStandard(CIEStandard standard);
		static const double ACTUAL_EPSILON;
		static const double ACTUAL_KAPPA;

		static const double INTENT_EPSILON;
		static const double INTENT_KAPPA;
		virtual XYZ_ptr toXYZ() = 0;
		XYZ_ptr getWhite();
	    };

	    class NormalizeYOperator {
	      protected:
		NormalizeY normalizeY_;
	      public:
		virtual void normalize(NormalizeY normalizeY) = 0;
		virtual void normalizeY() = 0;

		void normalizeY100();
		void setNormalizeNot();

		const static double NormalFactor;
	    };
	};
    };
};

#endif

