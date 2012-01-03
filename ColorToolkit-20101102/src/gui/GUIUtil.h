#ifndef GUIUTILH
#define GUIUTILH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���
#include "inifiles.hpp"
//��L�w�Y���
#include <java/lang.h>
//�����ؤ��Y���

//�����ؤ�gui�Y���

namespace gui {

    class IniFileUtil {
      private:
	bool callEventHandler;
	String section;
      public:
	void setCallEventHandlerWhenReading(bool call);
	 bptr < TIniFile > iniFile;
	 IniFileUtil(std::string iniFilename);
	 IniFileUtil(String iniFilename);
	 IniFileUtil(bptr < TIniFile > ini);
	void writeScrollBar(const AnsiString Section, const AnsiString Ident, TScrollBar * scroll);
	void writeCheckBox(const AnsiString Section, TCheckBox * check);
	void writeComboBox(const AnsiString Section, const AnsiString Ident, TComboBox * combo);
	void writeLabeledEdit(const AnsiString Section, TLabeledEdit * edit);

	void readScrollBar(const AnsiString Section, const AnsiString Ident, TScrollBar * scroll);
	void readCheckBox(const AnsiString Section, TCheckBox * check);
	void readComboBox(const AnsiString Section, const AnsiString Ident, TComboBox * combo);
	void readLabeledEdit(const AnsiString Section, TLabeledEdit * edit);

	void writeScrollBar(const AnsiString Ident, TScrollBar * scroll);
	void writeCheckBox(TCheckBox * check);
	void writeComboBox(const AnsiString Ident, TComboBox * combo);
	void writeLabeledEdit(TLabeledEdit * edit);

	void readScrollBar(const AnsiString Ident, TScrollBar * scroll);
	void readCheckBox(TCheckBox * check);
	void readComboBox(const AnsiString Ident, TComboBox * combo);
	void readLabeledEdit(TLabeledEdit * edit);
	__property String Section = { write = section };
	void updateFile(void);
	void writeString(const AnsiString Section, const AnsiString Ident, const AnsiString Value);
	void writeString(const AnsiString Ident, const AnsiString Value);
	void writeIntArray(const AnsiString Section, const AnsiString Ident, int *array,
			   int length);
	void writeIntArray(const AnsiString Ident, int *array, int length);
	bool readIntArray(const AnsiString Section, const AnsiString Ident, int *array, int length);
	bool readIntArray(const AnsiString Ident, int *array, int length);
	String readString(const AnsiString Ident);
	String readString(const AnsiString Section, const AnsiString Ident);
	double readDouble(const AnsiString Section, const AnsiString Ident);
	double readDouble(const AnsiString Ident);
	int readInt(const AnsiString Section, const AnsiString Ident);
	int readInt(const AnsiString Ident);
    };
};
#endif

