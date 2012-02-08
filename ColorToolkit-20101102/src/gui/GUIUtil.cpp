#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "GUIUtil.h"

namespace gui {

    IniFileUtil::IniFileUtil(std::string iniFilename):iniFile(bptr < TIniFile >
							      (new TIniFile(iniFilename.c_str()))),
	callEventHandler(false), section(null) {

    };
  IniFileUtil::IniFileUtil(String iniFilename):iniFile(bptr < TIniFile >
	    (new TIniFile(iniFilename))),
	callEventHandler(false), section(null) {

    };
  IniFileUtil::IniFileUtil(bptr < TIniFile > _ini):iniFile(_ini), callEventHandler(false),
	section(null) {
    };

    void IniFileUtil::writeScrollBar(const AnsiString section, const AnsiString ident,
				     TScrollBar * scroll) {

	iniFile->WriteInteger(section, ident, scroll->Position);
    };
    void IniFileUtil::writeCheckBox(const AnsiString section, TCheckBox * check) {

	iniFile->WriteInteger(section, check->Caption, true == check->Checked ? 1 : 0);
    };
    void IniFileUtil::writeComboBox(const AnsiString section, const AnsiString ident,
				    TComboBox * combo) {

	iniFile->WriteInteger(section, ident, combo->ItemIndex);
    };
    void IniFileUtil::writeLabeledEdit(const AnsiString section, TLabeledEdit * edit) {
	iniFile->WriteInteger(section, edit->EditLabel->Caption, edit->Text.ToInt());
    };

    void IniFileUtil::readScrollBar(const AnsiString Section, const AnsiString Ident,
				    TScrollBar * scroll) {
	scroll->Position = iniFile->ReadInteger(Section, Ident, 0);
	if (callEventHandler) {
	    scroll->OnChange;
	}
    };
    void IniFileUtil::readCheckBox(const AnsiString Section, TCheckBox * check) {
	check->Checked = iniFile->ReadInteger(Section, check->Caption, 0) == 0 ? false : true;
	if (callEventHandler) {
	    check->OnClick;
	}
    };
    void IniFileUtil::readComboBox(const AnsiString Section, const AnsiString Ident,
				   TComboBox * combo) {
	combo->ItemIndex = iniFile->ReadInteger(Section, Ident, 0);
	if (callEventHandler) {
	    combo->OnChange;
	}
    };
    void IniFileUtil::readLabeledEdit(const AnsiString Section, TLabeledEdit * edit) {
	edit->Text = iniFile->ReadInteger(Section, edit->EditLabel->Caption, 0);
	if (callEventHandler) {
	    edit->OnKeyPress;
	}
    };
    void IniFileUtil::setCallEventHandlerWhenReading(bool call) {
	callEventHandler = call;
    }


    void IniFileUtil::writeScrollBar(const AnsiString Ident, TScrollBar * scroll) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	writeScrollBar(section, Ident, scroll);
    };
    void IniFileUtil::writeCheckBox(TCheckBox * check) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	writeCheckBox(section, check);
    };
    void IniFileUtil::writeComboBox(const AnsiString Ident, TComboBox * combo) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	writeComboBox(section, Ident, combo);
    };
    void IniFileUtil::writeLabeledEdit(TLabeledEdit * edit) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	writeLabeledEdit(section, edit);
    };

    void IniFileUtil::readScrollBar(const AnsiString Ident, TScrollBar * scroll) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	readScrollBar(section, Ident, scroll);
    };
    void IniFileUtil::readCheckBox(TCheckBox * check) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	readCheckBox(section, check);
    };
    void IniFileUtil::readComboBox(const AnsiString Ident, TComboBox * combo) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	readComboBox(section, Ident, combo);
    };
    void IniFileUtil::readLabeledEdit(TLabeledEdit * edit) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	readLabeledEdit(section, edit);
    };
    void IniFileUtil::updateFile(void) {
	iniFile->UpdateFile();
    };
    void IniFileUtil::writeString(const AnsiString Section, const AnsiString Ident,
				  const AnsiString Value) {
	iniFile->WriteString(Section, Ident, Value);
    };
    void IniFileUtil::writeString(const AnsiString Ident, const AnsiString Value) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	writeString(section, Ident, Value);
    };


    String IniFileUtil::readString(const AnsiString Ident) {
	return readString(section, Ident);
    };
    String IniFileUtil::readString(const AnsiString Section, const AnsiString Ident) {
	return iniFile->ReadString(Section, Ident, "");
    };

    void IniFileUtil::writeIntArray(const AnsiString Section, const AnsiString Ident, int *array,
				    int length) {
	writeString(Section, Ident, math::IntArray::toString(array, length).c_str());
    };
    void IniFileUtil::writeIntArray(const AnsiString Ident, int *array, int length) {
	if (section == null) {
	    throw new java::lang::IllegalStateException("");
	}
	writeIntArray(section, Ident, array, length);
    };
    bool IniFileUtil::readIntArray(const AnsiString Section, const AnsiString Ident, int *array,
				   int length) {
	String str = iniFile->ReadString(Section, Ident, "");
	if (str.Length() == 0 /* || str.Length() != length */) {
	    return false;
	}
	using namespace math;
	int_array intarray = IntArray::fromString(str.c_str());
	IntArray::arraycopy(intarray, array, length);

    };
    bool IniFileUtil::readIntArray(const AnsiString Ident, int *array, int length) {
	return readIntArray(section, Ident, array, length);
    };

    double IniFileUtil::readDouble(const AnsiString Section, const AnsiString Ident) {
	return readString(Section, Ident).ToDouble();
    };
    double IniFileUtil::readDouble(const AnsiString Ident) {
	return readDouble(section, Ident);
    };
    int IniFileUtil::readInt(const AnsiString Section, const AnsiString Ident) {
	return readString(Section, Ident).ToInt();
    };
    int IniFileUtil::readInt(const AnsiString Ident) {
	return readInt(section, Ident);
    };
}

