#ifndef METERH
#define METERH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
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

	    class Meter:public jObject {
	      public:
		int getSuggestedWaitTimes();
		void setLogoFileHeader(cms::colorformat::logo::
				       LogoFile & logo);

		virtual void close() = 0;
		virtual bool isConnected() = 0;
		virtual void calibrate() = 0;
		virtual string_ptr getCalibrationDescription() = 0;
		virtual void setPatchIntensity(PatchIntensity
					       patchIntensity) = 0;
		virtual double_array triggerMeasurementInXYZ() = 0;
		virtual string_ptr getLastCalibration() = 0;
		virtual string_ptr getCalibrationCount() = 0;
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
		string_ptr getCalibrationDescription();
		void setPatchIntensity(PatchIntensity patchIntensity);
		double_array triggerMeasurementInXYZ();
		string_ptr getLastCalibration();
		string_ptr getCalibrationCount();
		void setScreenType(ScreenType screenType);
		Instr getType();
		void close();
	    };

	    class DGCodeFileMeter:public Meter {
	      private:
		bptr < cms::colorformat::DGCodeFile > dgcode;
		const Composition_vector_ptr vector;
		int index;
		Composition_ptr c;
	      public:
		 DGCodeFileMeter(bptr < cms::colorformat::DGCodeFile >
				 dgcode);
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
		Composition_ptr getComposition();
		void setIndex(int index);
	    };

	};
    };
};
#endif

