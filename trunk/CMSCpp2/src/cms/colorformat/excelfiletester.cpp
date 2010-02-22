#include "excelfiletester.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace colorformat {
	ExcelFileTester::ExcelFileTester(string_ptr filename) {
	    CoInitialize(null);
	    ADOConnection1 = new TADOConnection(null);

	    WideString connection;
	     connection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=";
	     connection += filename->c_str();
	     connection +=
		";Mode=ReadWrite;Extended Properties=Excel 8.0;Persist Security Info=False";

	    /*ADOConnection1->ConnectionString =
	       "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" +
	       *filename +
	       ";Mode=ReadWrite;Extended Properties=Excel 8.0;Persist Security Info=False"; */
	     ADOConnection1->ConnectionString = connection;
	     ADOConnection1->Provider = "Microsoft.Jet.OLEDB.4.0";

	     ADOConnection1->Open();
	    WideString sql =
		"CREATE TABLE tblCustomers (CustomerID INTEGER, [Last Name] TEXT(50), [First Name] TEXT(50), Phone TEXT(10), Email TEXT(50))";
	    WideString sql2 =
		"CREATE TABLE aa (CustomerID INTEGER, [Last Name] TEXT(50), [First Name] TEXT(50), Phone TEXT(10), Email TEXT(50))";
	     ADOConnection1->Execute(sql, TCommandType(),
				     TExecuteOptions());
	     ADOConnection1->Execute(sql2, TCommandType(),
				     TExecuteOptions());
	     ADOConnection1->Close();
	};


        
    };
};

