#ifndef MINIMISATIONH
#define MINIMISATIONH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>

//�����ؤ�gui�Y���






namespace algo {
    double minimisationFunction(double x[]);


    class MinimisationFunction {
      public:
	virtual double function(double_vector_ptr param) = 0;
    };

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

