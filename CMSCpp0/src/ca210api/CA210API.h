//---------------------------------------------------------------------------
#ifndef CA210APIH
#define CA210APIH
//---------------------------------------------------------------------------
#include "CA200SRVRLib_TLB.h"
//---------------------------------------------------------------------------

namespace ca210api {

    class CA210API {
      private:
	ICa200Disp ca200;
	ICaDisp ca;
	IProbeDisp probe;
	float measureValues[3];
      public:
	 CA210API();
	void calibrate();
	void close();
	float *triggerMeasurement();
    };
}
#endif

