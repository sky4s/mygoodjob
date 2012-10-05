#ifndef METERH
#define METERH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <ca210api/CA210API.h>
#ifdef EYE_ONE_SUPPORT
#include <EyeOneLib/EYEONECTRLLib_OCX.h>
#endif


namespace cms {
    namespace measure {
	Enumeration(FakeMode)
	None, Component, Patch EnumerationEnd()
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

	    class Meter:public jObject {
	      public:
		int getSuggestedWaitTimes();
		void setLogoFileHeader(cms::colorformat::logo::LogoFile & logo);

		virtual void close() = 0;
		virtual bool isConnected() = 0;
		virtual void calibrate() = 0;
		virtual string_ptr getCalibrationDescription() = 0;
		virtual void setPatchIntensity(PatchIntensity patchIntensity) = 0;
		virtual double_array triggerMeasurementInXYZ() = 0;
		virtual string_ptr getLastCalibration() = 0;
		virtual string_ptr getCalibrationCount() = 0;
		virtual void setScreenType(ScreenType screenType) = 0;
		virtual Instr getType() = 0;

	    };


	    class CA210:public Meter {
	      protected:
		static bptr < ca210api::CA210API > CA210API_;
		//Date calibrateTime;
		static void initCA210API();
		int measureCount;
	      public:
		 CA210();
		 bptr < ca210api::CA210API > getCA210API();
		bool isConnected();
		void calibrate();
		string_ptr getCalibrationDescription();
		void setPatchIntensity(PatchIntensity patchIntensity);
		double_array triggerMeasurementInXYZ();
		double triggerMeasurementInFlickerFMA();
		string_ptr getLastCalibration();
		string_ptr getCalibrationCount();
		void setScreenType(ScreenType screenType);
		Instr getType();
		void close();
	    };
#ifdef EYE_ONE_SUPPORT
	    class EyeOne:public Meter {
	      private:
		bptr < TEyeOneCtrl > i1;
	      public:
		EyeOne();
		virtual void close();
		virtual bool isConnected();
		virtual void calibrate();
		virtual string_ptr getCalibrationDescription();
		virtual void setPatchIntensity(PatchIntensity patchIntensity);
		virtual double_array triggerMeasurementInXYZ();
		virtual string_ptr getLastCalibration();
		virtual string_ptr getCalibrationCount();
		virtual void setScreenType(ScreenType screenType);
		virtual Instr getType();

	    };
#endif

	    class DGLutFileMeter:public Meter {
	      private:
		Component_vector_ptr vector;
		int index;
		Component_ptr c;
		Patch_vector_ptr measurePatchVector;
	      public:
		 DGLutFileMeter(bptr < cms::colorformat::DGLutFile > dglut);
		void close();
		bool isConnected();
		void calibrate();
		string_ptr getCalibrationDescription();
		void setPatchIntensity(PatchIntensity patchIntensity);
		double_array triggerMeasurementInXYZ();
		string_ptr getLastCalibration();
		string_ptr getCalibrationCount();
		void setScreenType(ScreenType screenType);
		Instr getType();
		Component_ptr getComponent();
		void setIndex(int index);
		void reset();
		bool isMeasureFromPatchVector();
		FakeMode getFakeMode();
	    };

	};
    };
};
#endif

