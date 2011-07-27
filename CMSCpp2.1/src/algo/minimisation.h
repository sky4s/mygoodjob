#ifndef MINIMISATIONH
#define MINIMISATIONH

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

//本項目內gui頭文件




#define mObject_ptr bptr < mObject >
#define Integer_ptr bptr < Integer >
#define Double_ptr bptr < Double >
namespace algo {

    class MinimisationFunction {
      public:
	virtual double function(double_vector_ptr param) = 0;
    };

    class mObject {
      protected:
	virtual ~ mObject() {
	};
    };

    /*class Integer:public mObject {
       public:
       int value;
       public:
       Integer(int val);

       };
       class Double:public mObject {
       public:
       double value;
       public:
       Double(double val);

       };

       class Minimisation {
       protected:
       int nParam;              // number of unknown parameters to be estimated
       double_vector_ptr paramValue;    // function parameter values (returned at function minimum)
       double functValue;       // current value of the function to be minimised
       double lastFunctValNoCnstrnt;    // Last function value with no constraint penalty
       double minimum;          // value of the function to be minimised at the minimum
       bool convStatus; // Status of minimisation on exiting minimisation method
       int scaleOpt;            // if = 0; no scaling of initial estimates
       //  if = 1; initial simplex estimates scaled to unity
       //  if = 2; initial estimates scaled by user provided values in scale[]
       //  (default = 0)
       double_vector_ptr scale; // values to scale initial estimate (see scaleOpt above)
       bool penalty;            // true if single parameter penalty function is included
       bool sumPenalty; // true if multiple parameter penalty function is included
       int nConstraints;        // number of single parameter constraints
       int nSumConstraints;     // number of multiple parameter constraints
       int maxConstraintIndex;  // maximum index of constrained parameter/s
       //        ArrayList < Object > penalties = new ArrayList < Object > ();  // method index,
       vector < mObject_ptr > penalties;
       // number of single parameter constraints,
       // then repeated for each constraint:
       //  penalty parameter index,
       //  below or above constraint flag,
       //  constraint boundary value
       //        ArrayList < Object > sumPenalties = new ArrayList < Object > ();       // constraint method index,
       vector < mObject_ptr > sumPenalties;
       // number of multiple parameter constraints,
       // then repeated for each constraint:
       //  number of parameters in summation
       //  penalty parameter indices,
       //  summation signs
       //  below or above constraint flag,
       //  constraint boundary value
       int_vector_ptr penaltyCheck;     // = -1 values below the single constraint boundary not allowed
       // = +1 values above the single constraint boundary not allowed
       int_vector_ptr sumPenaltyCheck;  // = -1 values below the multiple constraint boundary not allowed
       // = +1 values above the multiple constraint boundary not allowed
       double penaltyWeight;    // weight for the penalty functions
       int_vector_ptr penaltyParam;     // indices of paramaters subject to single parameter constraint
       int2D_ptr sumPenaltyParam;       // indices of paramaters subject to multiple parameter constraint
       double2D_ptr sumPlusOrMinus;     // value before each parameter in multiple parameter summation
       int_vector_ptr sumPenaltyNumber; // number of paramaters in each multiple parameter constraint

       double_vector_ptr constraints;   // single parameter constraint values
       double constraintTolerance;      // tolerance in constraining parameter/s to a fixed value
       double_vector_ptr sumConstraints;        // multiple parameter constraint values
       int constraintMethod;    // constraint method number
       //  =0: cliff to the power two (only method at present)
       int nMax;                //  Nelder and Mead simplex maximum number of iterations
       int nIter;               //  Nelder and Mead simplex number of iterations performed
       int konvge;              //  Nelder and Mead simplex number of restarts allowed
       int kRestart;            //  Nelder and Mead simplex number of restarts taken
       double fTol;             //  Nelder and Mead simplex convergence tolerance
       double rCoeff;           //  Nelder and Mead simplex reflection coefficient
       double eCoeff;           //  Nelder and Mead simplex extension coefficient
       double cCoeff;           //  Nelder and Mead simplex contraction coefficient
       double_vector_ptr startH;        //  Nelder and Mead simplex initial estimates
       double_vector_ptr step;  //  Nelder and Mead simplex step values
       double dStep;            //  Nelder and Mead simplex default step value
       int minTest;             //  Nelder and Mead minimum test
       //      = 0; tests simplex sd < fTol
       //  allows options for further tests to be added later
       double simplexSd;        //  simplex standard deviation

       //Constructor
       public:
       Minimisation();
       void addConstraint(int paramIndex, int conDir, double constraint);
       double getMinimum();
       double_vector_ptr getParamValues();
       void nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
       double_vector_ptr step);
       void nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
       double_vector_ptr step, double fTol, int nMax);
       void nelderMead(mObject_ptr g, double_vector_ptr start, double_vector_ptr step, double fTol,
       int nMax);
       }; */
    double minimisationFunction(double x[]);


    /*class MinimisationFunction {
       public:
       virtual double function(double_vector_ptr param) = 0;
       }; */

    Enumeration(Error) NoErrors, IllegalValue, IterationTerminate, Unknow EnumerationEnd();

    class Minimisation {
      private:
	int icount, numres, ifault;
	int n;
	double ynewlo;
	int konvge, kcount;
	double_vector_ptr paramValues;
      public:
	 Minimisation();
	void nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
			double_vector_ptr step, double ftol, int nmax);
	void nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
			double_vector_ptr step);
	int getNiter();
	int getNmax();
	double getMinimum();
	void setNrestartsMax(int nrm);
	int getNrestartMax();

	double_vector_ptr getParamValues();
	Error getError();
	static int minimisation_n;
	static bptr < MinimisationFunction > mf_ptr;
    };
};
#endif

