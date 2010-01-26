#ifndef METERH
#define METERH

#include <java/lang.h>
#include <cms/colorformat/logo.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <string>
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
		 Instr(double width, double length):widthInch(width),
		    lengthInch(length) {
		};
	    };


	    enum PatchIntensity {
		Bleak, Bright, Auto
	    };

	    enum ScreenType {
		LCD, CRT
	    };

	    using std::string;
	    using boost::shared_ptr;
	    using boost::shared_array;
	    using java::lang::Object;
	    using cms::colorformat::logo::LogoFile;

	    class Meter:public Object {
	      public:
		virtual void close() = 0;
		virtual bool isConnected() = 0;
		virtual void calibrate() = 0;
		virtual shared_ptr < string > getCalibrationDescription() =
		    0;
		virtual void setPatchIntensity(PatchIntensity
					       patchIntensity) = 0;
		virtual shared_array < double >triggerMeasurementInXYZ() =
		    0;
		virtual shared_ptr < string > getLastCalibration() = 0;
		virtual shared_ptr < string > getCalibrationCount() = 0;
		virtual void setScreenType(ScreenType screenType) = 0;
		virtual Instr getType() = 0;


  /**
   * setLogoFileHeader
   *
   * @param logo LogoFile
   */
		void setLogoFileHeader(LogoFile & logo) {
		    /*logo.setHeader(LogoFile.Reserved.Created,
		       new Date().toString());
		       logo.setHeader(LogoFile.Reserved.Instrumentation,
		       getType().name());
		       logo.setHeader(LogoFile.Reserved.MeasurementSource,
		       "Illumination=Unknown    ObserverAngle=Unknown   WhiteBase=Abs   Filter=Unknown");
		       logo.setNumberOfFields(8);
		       logo.addKeyword("SampleID");
		       logo.addKeyword("SAMPLE_NAME");
		       logo.
		       setDataFormat
		       ("SampleID       SAMPLE_NAME     RGB_R   RGB_G   RGB_B   XYZ_X   XYZ_Y   XYZ_Z"); */
		};
		/*static void setLogoPatchList(LogoFile logo,
		   List < Patch > patchList) {
		   int size = patchList.size();
		   for (int x = 0; x < size; x++) {
		   Patch p = patchList.get(x);
		   CIEXYZ XYZ = p.getXYZ();
		   RGB rgb = p.getRGB();
		   String pName = p.getName();
		   int index = x + 1;
		   String name = (pName == null
		   || pName.length() ==
		   0) ? String.valueOf(index) : pName;
		   String data =
		   index + "\t" + name + "\t" + rgb.R + "\t" +
		   rgb.G + "\t" + rgb.B + "\t" + XYZ.X + "\t" +
		   XYZ.Y + " " + XYZ.Z;
		   logo.addData(data);
		   };
		   };
		   void setLogoFileData(LogoFile logo,
		   List < Patch > patchList) {
		   setLogoPatchList(logo, patchList);
		   }; */

		int getSuggestedWaitTimes() {
		    return 300;
		};
	    };

	    class CA210:public Meter {
	      protected:
		static ca210api::CA210API _CA210API;
		//Date calibrateTime;
		int measureCount;
	      public:

		  /**
   * isConnected
   *
   * @return boolean
   */
		 bool isConnected() {
		    return true;
		};
		  /**
   * calibrate
   *
   */
		void calibrate() {
		    _CA210API.calibrate();
		    //calibrateTime = new Date();
		    measureCount = 0;
		};


		shared_ptr < string > getCalibrationDescription() {
		    return shared_ptr < string >
			("Set the pointing ring to the 0-CAL position.");
		};

		void setPatchIntensity(PatchIntensity patchIntensity) {
		    //using namespace ca210api;
		    switch (patchIntensity) {
		    case Bleak:
			_CA210API.setAveragingMode(ca210api::Fast);
			break;
		    case Bright:
			_CA210API.setAveragingMode(ca210api::Slow);
			break;
		    case Auto:
			_CA210API.setAveragingMode(ca210api::Auto);
			break;
		    }
		};
		shared_array < double >triggerMeasurementInXYZ() {
		    measureCount++;
		    shared_array < float >values =
			_CA210API.triggerMeasurement();
		    shared_array < double >result(new double[3]);
		    result[0] = values[0];
		    result[1] = values[1];
		    result[2] = values[2];
		    return result;
		};

		shared_ptr < string > getLastCalibration() {
		    return shared_ptr < string > (NULL);
		};
		shared_ptr < string > getCalibrationCount() {
		    return shared_ptr < string > (NULL);
		};
		void setScreenType(ScreenType screenType) {
		};
		Instr getType() {
		    return Instr::CA210;
		};

	    };
	};
    };
};
#endif

