#include <includeall.h>
#pragma hdrstop
#include "excelfile.h"

//C系統文件

//C++系統文件
#include <iostream>

//其他庫頭文件
#include <comobj.hpp>
//本項目內頭文件

namespace cms {
    namespace colorformat {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
#ifdef COLORSPACE
	using namespace Indep;
	using namespace Dep;
#endif
	using namespace cms::util;

	//======================================================================
	// ExcelFileDB
	//======================================================================
	string ExcelFileDB::getTableName() {
	    if (tableName.size() == 0) {
		throw IllegalStateException("Set tableName first!");
	    };
	     return tableName;
	};
	string ExcelFileDB::getKeyField() {
	    if (keyField.size() == 0) {
		throw IllegalStateException("Set keyField first!");
	    };
	    return keyField;
	};
	string_vector_ptr ExcelFileDB::getFieldNames(string_ptr tableName) {
	    if (null == fieldNames || true == tableChanged) {
		bptr_ < TStringList > stringList(new TStringList());
		connection->GetFieldNames(tableName->c_str(), stringList.get());
		fieldNames = string_vector_ptr(new string_vector());
		for (int x = 0; x != stringList->Count; x++) {
		    AnsiString as = (*stringList)[x];
		    string s(as.c_str());
		    fieldNames->push_back(s);
		};
	    }
	    //return result;
	    return fieldNames;
	};
	bool ExcelFileDB::isAlterable() {
	    return mode == Create || mode == Update;
	};

      ExcelFileDB::ExcelFileDB(const string & fileName, const Mode mode):fileName(fileName),
	    mode(mode), tableChanged(true),
	    caching(false) {

	    WideString connectstr;
	    connectstr = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	    connectstr += fileName.c_str();
	    connectstr +=
		";Mode=ReadWrite;Extended Properties=Excel 8.0;Persist Security Info=False";

	    CoInitialize(null);
	    connection = bptr < TADOConnection > (new TADOConnection(null));
	    connection->ConnectionString = connectstr;
	    connection->Provider = "Microsoft.Jet.OLEDB.4.0";
	    connection->Open();

#ifdef USE_QUERY
	    query = bptr < TADOQuery > (new TADOQuery(null));
#endif
	};
	ExcelFileDB::~ExcelFileDB() {
	    close();
	};

	void ExcelFileDB::createTable(const std::string & tableName, string_vector_ptr fieldNames) {
	    int size = fieldNames->size();
	    string_vector_ptr fieldTypes(new string_vector(size));

            if(tableName=="xyY") {     //為了在量測模式中的excel塞入文字，所以第一列改成Text  20140619 btBS+
                bool firstFlag = true;
                foreach(string & s, *fieldTypes) {
                    if(firstFlag) {
                        s = "Text";
                        firstFlag = 0;
                    } else {
                        s = "Real";
                    }
                };
            } else {
                foreach(string & s, *fieldTypes) {
                    s = "Real";
                };
            }

	    createTable(tableName, fieldNames, fieldTypes);
	};

	void ExcelFileDB::createTable(const std::string & tableName,
				      string_vector_ptr fieldNames, string_vector_ptr fieldTypes) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }
	    if (fieldNames->size() != fieldTypes->size()) {
		throw IllegalArgumentException("fieldNames->size() != fieldTypes->size()");
	    }

	    this->setTableName(tableName);
	    string sql = "CREATE TABLE [" + tableName + "] (";

	    int size = fieldNames->size();
	    for (int x = 0; x != size; x++) {
		string & name = (*fieldNames)[x];
		string & type = (*fieldTypes)[x];
		sql += "[" + name + "] " + type + ((x == size - 1) ? ")" : ",");
	    };

	    execute(sql);
	};

	void ExcelFileDB::setTableName(const std::string & tableName) {
	    this->tableName = tableName;
	}

	void ExcelFileDB::insert(string_vector_ptr fieldNames, string_vector_ptr values) {

	    insert(fieldNames, values, false);
	};

	void ExcelFileDB::insert(string_vector_ptr fieldNames, string_vector_ptr values, bool text) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }
	    string sql;
	    if (caching && cachesql.size() != 0) {
		sql = "(";
	    } else {
		sql = "INSERT INTO [" + getTableName() + "$] (";

		foreach(string s, *fieldNames) {
		    sql += "[" + s + "],";
		};
		sql.replace(sql.size() - 1, 1, ") VALUES (");
	    }

	    foreach(string s, *values) {
		sql += text ? ("\"" + s + "\",") : (s + ",");
	    };
	    sql.replace(sql.size() - 1, 1, ")");

	    if (caching) {
		cachesql += sql + ",";
	    } else {
		execute(sql);
	    };
	};
	void ExcelFileDB::execute(const std::string & sql) {
	    connection->Execute(*Util::toWideString(sql), TCommandType(), TExecuteOptions());
	};
	void ExcelFileDB::update0(const std::string & keyField,
				  const int keyValue,
				  string_vector_ptr fieldNames,
				  string_vector_ptr values, bool textValues) {
	    if (!isAlterable()) {
		throw IllegalStateException("!isAlterable()");
	    }

	    string sql = "UPDATE [" + getTableName() + "$] SET";
	    int size = fieldNames->size();
	    for (int x = 0; x < size; x++) {
		string key = (*fieldNames)[x];
		string val = (*values)[x];
		sql += " [" + key + "] = ";
		sql += textValues ? ("\"" + val + "\"") : val;
		sql += (x == size - 1) ? "" : ",";
	    }

	    sql += " WHERE [" + keyField + "] = " + _toString(keyValue);

	    execute(sql);
	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 string_vector_ptr fieldNames, string_vector_ptr values) {
	    update0(keyField, keyValue, fieldNames, values, true);
	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 string_vector_ptr fieldNames,
				 string_vector_ptr values, bool textValues) {
	    update0(keyField, keyValue, fieldNames, values, textValues);
	};

	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 const std::string & fieldName, const std::string & value) {
	    string_vector_ptr fieldNames(new string_vector());
	    fieldNames->push_back(fieldName);
	    string_vector_ptr values(new string_vector());
	    values->push_back(value);

	    update0(keyField, keyValue, fieldNames, values, true);

	};
	void ExcelFileDB::update(const std::string & keyField,
				 const int keyValue,
				 const std::string & fieldName, const int value) {
	    string_vector_ptr fieldNames(new string_vector());
	    fieldNames->push_back(fieldName);
	    string_vector_ptr values(new string_vector());
	    values->push_back(_toString(value));

	    update0(keyField, keyValue, fieldNames, values, false);
	};

	string_vector_ptr ExcelFileDB::select0(const std::
					       string & keyField,
					       const std::string & keyValue, bool textValues) {
	    string select = "SELECT * FROM [" + getTableName() + "$] Where " + keyField + " = ";
	    select += textValues ? "\"" + keyValue + "\"" : keyValue;
	    bptr < TADODataSet > dataSet = selectDataSet(select);
	    return getResult(dataSet);
	};

	bptr < TADODataSet > ExcelFileDB::selectDataSet(const std::string & sql) {
#define OLE_EXCEPTION
#ifdef OLE_EXCEPTION
	    try {
#endif
		bptr < TADODataSet > dataSet(new TADODataSet((TComponent *) null));
		dataSet->Connection = connection.get();
		dataSet->CommandText = *Util::toWideString(sql);
		dataSet->Open();
		dataSet->First();
		return dataSet;
#ifdef OLE_EXCEPTION
	    }
	    catch(EOleException & ex) {
		return bptr < TADODataSet > ((TADODataSet *) null);
	    }
#endif
	};

	string_vector_ptr ExcelFileDB::getResult(bptr < TADODataSet > dataSet) {
	    string_vector_ptr result(new string_vector());
	    int fields = dataSet->FieldCount;

	    for (int x = 0; x != fields; x++) {
		AnsiString astr = dataSet->Fields->Fields[x]->AsString;
		string str(astr.c_str());
		result->push_back(str);
	    }
	    return result;
	};

	bool ExcelFileDB::isTableExist(const std::string & tableName) {
	    TStringList *list = new TStringList;	// declare the list

	    try {
		connection->GetTableNames(list, false);
		if (list->IndexOf(_toAnsiString(tableName)) > -1) {
		    return true;
		} else {
		    return false;
		}
	    }
	    __finally {
		delete list;	// destroy the list object
	    }
	    return false;

	};

	string_vector_ptr ExcelFileDB::select(const std::string & keyField, const int keyValue) {
	    return select0(keyField, _toString(keyValue), false);
	};

	string_vector_ptr ExcelFileDB::select(const int keyValue) {
	    return select0(getKeyField(), _toString(keyValue), false);
	};
	string_vector_ptr ExcelFileDB::select(const std::string & keyField,
					      const std::string & keyValue) {
	    return select0(keyField, keyValue, true);
	};
	string_vector_ptr ExcelFileDB::select(const std::string & keyValue) {
	    return select0(getKeyField(), keyValue, true);
	};

	bptr < DBQuery > ExcelFileDB::selectAll() {
	    string select = "SELECT * FROM [" + getTableName() + "$]";
	    bptr < TADODataSet > dataSet = selectDataSet(select);
	    if (null != dataSet) {
		bptr < DBQuery > query(new DBQuery(dataSet));
		return query;
	    } else {
		return bptr < DBQuery > ((DBQuery *) null);
	    }
	};

	void ExcelFileDB::close() {
	    if (null != connection && true == connection->Connected) {
		connection->Close();
		CoUninitialize();
	    }
	};


	void ExcelFileDB::setKeyField(const std::string & keyField) {
	    this->keyField = keyField;
	};
	void ExcelFileDB::setCacheMode(bool caching) {
	    this->caching = caching;
	};
	void ExcelFileDB::excuteCache() {
	    int size = cachesql.size();
	    if (size != 0) {
		cachesql.erase(size - 1, size);
		//cachesql += ";";
		execute(cachesql);
		cachesql.clear();
	    }
	};
	//======================================================================

	//======================================================================
	//
	//======================================================================
      DBQuery::DBQuery(bptr < TADODataSet > dataSet):dataSet(dataSet) {
	};

	string_vector_ptr DBQuery::nextResult() {
	    if (!hasNext()) {
		throw IllegalStateException("!hasNext()");
	    }
	    string_vector_ptr result = ExcelFileDB::getResult(dataSet);
	    dataSet->Next();
	    return result;
	};
	double_vector_ptr DBQuery::toDoubleVector(string_vector_ptr result) {
	    int size = result->size();
	    double_vector_ptr doublevec(new double_vector(size));
	    for (int x = 0; x != size; x++) {
		try {
		    string str = (*result)[x];
		    if (0 == str.size()) {
			(*doublevec)[x] = -1;
		    } else {
			(*doublevec)[x] = _toDouble((*result)[x]);
		    }
		}
		catch(boost::bad_lexical_cast e) {
		    (*doublevec)[x] = -1;
		}
	    }

	    return doublevec;
	};
	bool DBQuery::hasNext() {
	    return !dataSet->Eof;
	};

	const string_ptr DBQuery::get(int row, int column) {
	    dataSet->First();
	    for (int x = 0; x < row; x++) {
		dataSet->Next();
	    };
	    string_vector_ptr result = nextResult();
	    string_ptr str(new string((*result)[column]));
	    return str;
	};
	//======================================================================



	//======================================================================
	// ExcelAccessBase
	//======================================================================
	const string & ExcelAccessBase::DeltaData = "Delta_Data";
	const string & ExcelAccessBase::GammaTable = "Gamma_Table";
	const string & ExcelAccessBase::OldGammaTable = "Gamma Table";
	const std::string & ExcelAccessBase::Sheet1 = "Sheet1";
	const string & ExcelAccessBase::Measure = "Measure";
	string_vector_ptr ExcelAccessBase::getHeaderNames(const std::string & sheetname) {
	    return headerNamesMap[sheetname];
	};
	const int ExcelAccessBase::getHeaderCount(const std::string & sheetname) {
	    return headerNamesMap[sheetname]->size();
	};
	void ExcelAccessBase::initSheet(const std::string & sheetname, int headerCount, ...) {
	    string_vector_ptr headers(new string_vector());
	    va_list num_list;
	    va_start(num_list, headerCount);

	    for (int i = 0; i < headerCount; i++) {
		const char *c = va_arg(num_list, const char *);
		string str(c);
		headers->push_back(str);
	    } va_end(num_list);

            initSheet(sheetname, headers);
	};
	void ExcelAccessBase::initSheet(const std::string & sheetname,
					string_vector_ptr headerNames) {
	    if (db->isTableExist(sheetname)) {
		return;
	    }
	    headerNamesMap.insert(make_pair(sheetname, headerNames));
	    if (Create == mode) {
		db->createTable(sheetname, headerNames);
	    } else {
		throw IllegalStateException("");
	    }

	};
	void ExcelAccessBase::initSheet(const std::string & sheetname,
					string_vector_ptr headerNames,
					string_vector_ptr fieldTypes) {
	    if (db->isTableExist(sheetname)) {
		return;
	    }
	    headerNamesMap.insert(make_pair(sheetname, headerNames));
	    if (Create == mode) {
		db->createTable(sheetname, headerNames, fieldTypes);
	    } else {
		throw IllegalStateException("");
	    }

	};
	void ExcelAccessBase::initPropertySheet() {
	    if (db->isTableExist(Properties)) {
		return;
	    }
	    string_vector_ptr headerNames = StringVector::fromCString(2, "Key", "Value");
	    string_vector_ptr fieldType = StringVector::fromCString(2, "Text", "Text");
	    headerNamesMap.insert(make_pair(Properties, headerNames));
	    if (Create == mode) {
		db->createTable(Properties, headerNames, fieldType);
	    } else {
		throw IllegalStateException("");
	    }
	};
	void
	 ExcelAccessBase::initBegin() {
	    if (Create == mode && FileExists(filename.c_str())) {
		throw IllegalStateException("File " + filename + " exists.");
	    }
	    db = bptr < ExcelFileDB > (new ExcelFileDB(filename, mode));
	};
	void ExcelAccessBase::insertData(const std::string & sheetname,
					 string_vector_ptr values, bool text) {
	    string_vector_ptr headerNames = getHeaderNames(sheetname);
	    db->setTableName(sheetname);
	    db->insert(headerNames, values, text);
	};

	ExcelAccessBase::ExcelAccessBase(const std::string & filename, Mode mode):filename(filename), mode(mode) {	/*, lazyMode(LAZY_EXCEL) */
	    initBegin();
	    /*initSheet(Measure, 12, "id", "R", "G", "B", "X", "Y (nit)", "Z", "_x", "_y",
	       "R12", "G12", "B12"); */
	    measureID = 1;
	};
	void
	 ExcelAccessBase::addProperty(const
				      string & key, const
				      string & value) {
	    string_vector_ptr values = StringVector::fromString(2, key, value);
	    db->setCacheMode(false);
	    this->insertData(Properties, values, true);

	};
	void
	 ExcelAccessBase::addProperty(const std::string & key, const double value) {
	    addProperty(key, _toString(value));
	};

	const string & ExcelAccessBase::Properties = "Properties";
	bptr < DBQuery > ExcelAccessBase::retrieve(const std::string & sheetname) {
	    db->setTableName(sheetname);
	    return db->selectAll();
	};

	void ExcelAccessBase::setDeltaData(Patch_vector_ptr patchVector) {
	    using namespace cms::lcd::calibrate;
	    int size = patchVector->size();
	    Component_vector_ptr componentVector(new Component_vector(size));
	    for (int x = 0; x < size; x++) {
		Patch_ptr p = (*patchVector)[x];
		//p->getRGB()
		Component_ptr c(new Component(p));
		(*componentVector)[x] = c;
	    }
	    setDeltaData(componentVector);
	}

	void ExcelAccessBase::setDeltaData(Component_vector_ptr componentVector) {
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    const int headerCount = 8;
	    initSheet(DeltaData, headerCount, "Gray Level", "W_x", "W_y", "Y (nit)", "dx", "dy",
		      "ave_x", "ave_y");

	    int size = componentVector->size();
	    string_vector_ptr values(new string_vector(headerCount));
	    //==================================================================

	    xyY_ptr xyY0(new CIExyY((*componentVector)[0]->XYZ));
	    xyY_ptr xyY1(new CIExyY((*componentVector)[size - 1]->XYZ));
	    string ave_x = _toString((xyY0->x - xyY1->x) / size);
	    string ave_y = _toString((xyY0->y - xyY1->y) / size);

	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {
		Component_ptr c = (*componentVector)[x];
		int w = static_cast < int >(c->rgb->getValue(Channel::W));
		(*values)[0] = _toString(w);
		xyY_ptr xyY(new CIExyY(c->XYZ));


		//xyY_ptr xyY(new CIExyY(c->XYZ));
		(*values)
		    [1] = _toString(xyY->x);
		(*values)
		    [2] = _toString(xyY->y);
		(*values)
		    [3] = _toString(xyY->Y);

		(*values)
		    [6] = ave_x;
		(*values)
		    [7] = ave_y;

		if (x < (size - 1)) {
		    //dx dy只算到倒數第二個
		    Component_ptr c2 = (*componentVector)[x + 1];
		    xyY_ptr xyY2(new CIExyY(c2->XYZ));
		    (*values)
			[4] = _toString(xyY->x - xyY2->x);
		    (*values)
			[5] = _toString(xyY->y - xyY2->y);
		} else {
		    StringVector::setContent(values, "-1", 2, 4, 5);
		}

		this->insertData(DeltaData, values, false);
	    }
	};


	void ExcelAccessBase::setGammaTable(RGB_vector_ptr dglut) {
	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    int size = dglut->size();
	    string_vector_ptr values(new string_vector(4));
	    initSheet(GammaTable, 4, "Gray Level", "Gamma R", "Gamma G", "Gamma B");
	    //==================================================================
	    //==================================================================
	    // 迴圈處理
	    //==================================================================
	    for (int x = 0; x != size; x++) {

		RGB_ptr rgb = (*dglut)[x];
		(*values)[0] = _toString(x);
		(*values)
		    [1] = _toString(rgb->R);
		(*values)
		    [2] = _toString(rgb->G);
		(*values)
		    [3] = _toString(rgb->B);
		this->insertData(GammaTable, values, false);
	    }

	    //==================================================================
	};

	RGB_vector_ptr ExcelAccessBase::getGammaTable(const Dep::MaxValue & maxValue) {
	    if (db->isTableExist(GammaTable)) {
		db->setTableName(GammaTable);
	    } else if (db->isTableExist(OldGammaTable)) {
		db->setTableName(OldGammaTable);
	    } else {
		db->setTableName(Sheet1);
	    }

	    RGB_vector_ptr vector(new RGB_vector());
	    bptr < DBQuery > query = db->selectAll();
	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		if (result->size() > 3 && (*result)[1].size() != 0) {
		    double R = _toDouble((*result)[1]);
		    double G = _toDouble((*result)[2]);
		    double B = _toDouble((*result)[3]);
		    RGB_ptr rgb(new RGBColor(R, G, B, maxValue));
		    vector->push_back(rgb);
		} else {
		    break;
		}
	    };
	    return vector;
	};


	bool ExcelAccessBase::isMeasurePatchVectorAvailable() {
	    return db->isTableExist(Measure);
	};
	Patch_vector_ptr ExcelAccessBase::getMeasurePatchVector() {

	    if (!db->isTableExist(Measure)) {
		return nil_Patch_vector_ptr;
	    }

	    db->setTableName(Measure);
	    bptr < DBQuery > query = db->selectAll();
	    //int index = 0;
	    Patch_vector_ptr patchVector(new Patch_vector());

	    while (query->hasNext()) {
		string_vector_ptr result = query->nextResult();
		string id = (*result)[0];
		string_ptr name(new string(id));
		double R = _toDouble((*result)[1]);
		double G = _toDouble((*result)[2]);
		double B = _toDouble((*result)[3]);

		double X = _toDouble((*result)[4]);
		double Y = _toDouble((*result)[5]);
		double Z = _toDouble((*result)[6]);

		double intensityR = _toDouble((*result)[9]);
		double intensityG = _toDouble((*result)[10]);
		double intensityB = _toDouble((*result)[11]);

		RGB_ptr rgb(new RGBColor(R, G, B));
		XYZ_ptr XYZ(new CIEXYZ(X, Y, Z));
		RGB_ptr intensity(new RGBColor(intensityR, intensityG, intensityB));
		Patch_ptr p(new Patch(name, XYZ, nil_XYZ_ptr, rgb, intensity));
		patchVector->push_back(p);
	    };
	    return patchVector;

	};

	void ExcelAccessBase::addMeasure(Patch_ptr p) {
	    const int headerCount = 15;
	    if (!isMeasurePatchVectorAvailable()) {
		initSheet(Measure, headerCount, "id", "R", "G", "B", "X", "Y (nit)", "Z", "_x",
			  "_y", "W_R", "W_G", "W_B", "R12", "G12", "B12");
	    }
	    //==================================================================
	    // 初始資料設定
	    //==================================================================

	    string_vector_ptr values(new string_vector(headerCount));


	    (*values)[0] = _toString(measureID++);

	    double r = -1, g = -1, b = -1;
	    RGB_ptr rgb = p->getRGB();
	    if (null != rgb) {
		r = rgb->getValue(Channel::R, MaxValue::Double255);
		g = rgb->getValue(Channel::G, MaxValue::Double255);
		b = rgb->getValue(Channel::B, MaxValue::Double255);
	    }
	    (*values)[1] = _toString(r);
	    (*values)[2] = _toString(g);
	    (*values)[3] = _toString(b);

	    XYZ_ptr XYZ = p->getXYZ();
	    (*values)[4] = _toString(XYZ->X);
	    (*values)[5] = _toString(XYZ->Y);
	    (*values)[6] = _toString(XYZ->Z);

	    xyY_ptr xyY(new CIExyY(XYZ));
	    (*values)[7] = _toString(xyY->x);
	    (*values)[8] = _toString(xyY->y);

	    //intensity
	    RGB_ptr intensity = p->getIntensity();
	    if (null != intensity) {
		(*values)[9] = _toString(intensity->R);
		(*values)[10] = _toString(intensity->G);
		(*values)[11] = _toString(intensity->B);
	    } else {
		(*values)[9] = "-1";
		(*values)[10] = "-1";
		(*values)[11] = "-1";
	    }

	    double r12 = -1, g12 = -1, b12 = -1;
	    if (null != rgb) {
		r12 = rgb->getValue(Channel::R, MaxValue::Int12Bit);
		g12 = rgb->getValue(Channel::G, MaxValue::Int12Bit);
		b12 = rgb->getValue(Channel::B, MaxValue::Int12Bit);
	    }
	    (*values)[12] = _toString(r12);
	    (*values)[13] = _toString(g12);
	    (*values)[14] = _toString(b12);

	    this->insertData(Measure, values, false);
	}


	void ExcelAccessBase::setMeasure(Patch_vector_ptr patchList) {

	    //==================================================================
	    // 初始資料設定
	    //==================================================================
	    //const int headerCount = 12;
	    //string_vector_ptr values(new string_vector(headerCount));
	    //int size = patchList->size();
	    //==================================================================

	    foreach(Patch_ptr p, *patchList) {
		addMeasure(p);
	    }

	};
	//======================================================================

	//======================================================================
	// SimpleExcelAccess
	//======================================================================

	SimpleExcelAccess::SimpleExcelAccess(const std::string & filename,
					     Mode mode):ExcelAccessBase(filename, mode) {
	    /*, headerNames(headerNames) */

	};
	SimpleExcelAccess::SimpleExcelAccess(const std::string & filename, Mode mode, string_vector_ptr headerNames):ExcelAccessBase(filename, mode) {	/*, headerNames(headerNames) */
	    initSheet(Sheet1, headerNames);
	};
	SimpleExcelAccess::SimpleExcelAccess(const std::string & filename, Mode mode, string_vector_ptr headerNames, string_vector_ptr fieldTypes):ExcelAccessBase(filename, mode) {	/*, headerNames(headerNames) */
	    initSheet(Sheet1, headerNames, fieldTypes);
	};
	SimpleExcelAccess::SimpleExcelAccess(const std::
					     string &
					     filename):ExcelAccessBase(filename, ReadOnly) {
	    //initSheet(Sheet1, headerNames);
	};

	bptr < DBQuery > SimpleExcelAccess::retrieve() {
	    return ExcelAccessBase::retrieve(Sheet1);
	};
	void SimpleExcelAccess::insert(string_vector_ptr values) {
	    insertData(Sheet1, values, false);
	};
	/*void SimpleExcelAccess::insert(const std::string & sheetname,
	   string_vector_ptr values) {
	   insertData(sheetname, values, false);
	   }; */
	bptr < SimpleExcelAccess >
	    SimpleExcelAccess::getValueStoreInstance(const std::string & filename) {
	    string_vector_ptr fieldNames = StringVector::fromCString(1,
								     "value");
	    bptr < SimpleExcelAccess > access(new SimpleExcelAccess(filename, Create, fieldNames));
	    return access;
	};

	bptr < SimpleExcelAccess >
	    SimpleExcelAccess::getCustomPatternInstance(const std::string & filename) {
	    string_vector_ptr fieldNames = StringVector::fromCString(4,
								     "Num", "R", "G", "B");
	    bptr < SimpleExcelAccess >
		access(new SimpleExcelAccess(filename, ReadOnly, fieldNames));
	    return access;
	};
	//======================================================================
    };
};

