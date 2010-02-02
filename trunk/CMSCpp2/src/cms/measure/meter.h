#ifndef METERH
#define METERH

#include <java/lang.h>
//#include <string>
#include <ca210api/CA210API.h>


namespace cms {
    namespace measure {
	namespace meter {
	    class Instr {
	      public:
		static const Instr i1Display2;
		static const Instr i1Pro;
		static const Instr Spyder2;
		static const Instr Spyder3;
		static const Instr CA210;
		static const Instr Dummy;
		static const Instr Argyll;
		static const Instr Platform;

		double widthInch, lengthInch;

	      private:
		 Instr(double width, double length);
	    };


	    enum PatchIntensity {
		Bleak, Bright, Auto
	    };

	    enum ScreenType {
		LCD, CRT
	    };

	    class Meter:public java::lang::Object {
	      public:
		int getSuggestedWaitTimes();
		void setLogoFileHeader(cms::colorformat::logo::
				       LogoFile & logo);

		virtual void close() = 0;
		virtual bool isConnected() = 0;
		virtual void calibrate() = 0;
		virtual boost::shared_ptr < std::string >
		    getCalibrationDescription() = 0;
		virtual void setPatchIntensity(PatchIntensity
					       patchIntensity) = 0;
		virtual boost::shared_array <
		    double >triggerMeasurementInXYZ() = 0;
		virtual boost::shared_ptr < std::string >
		    getLastCalibration() = 0;
		virtual boost::shared_ptr < std::string >
		    getCalibrationCount() = 0;
		virtual void setScreenType(ScreenType screenType) = 0;
		virtual Instr getType() = 0;

	    };


	    class CA210:public Meter {
	      protected:
		static bptr < ca210api::CA210API > _CA210API;
		//Date calibrateTime;
		static void initCA210API();
		int measureCount;
	      public:
		 CA210();
		 bptr < ca210api::CA210API > getCA210API();
		bool isConnected();
		void calibrate();
		 boost::shared_ptr < std::string >
		    getCalibrationDescription();
		void setPatchIntensity(PatchIntensity patchIntensity);
		 barray < double >triggerMeasurementInXYZ();
		 bptr < std::string > getLastCalibration();
		 bptr < std::string > getCalibrationCount();
		void setScreenType(ScreenType screenType);
		Instr getType();
		void close();
	    };

	};
    };
};
#endif

