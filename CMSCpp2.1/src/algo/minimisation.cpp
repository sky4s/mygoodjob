#include <includeall.h>
#pragma hdrstop
#include "minimisation.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件
#include "asa047.H"
//本項目內頭文件

//本項目內gui頭文件

namespace algo {
    using namespace java::lang;
    using namespace math;



    double minimisationFunction(double x[]) {
	double_vector_ptr params = DoubleArray::toDoubleVector(x, Minimisation::minimisation_n);
	 bptr < MinimisationFunction > mf = Minimisation::mf_ptr;
	 return mf->function(params);
    };
  Minimisation::Minimisation():konvge(3) {
    };
    void Minimisation::nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
				  double_vector_ptr step) {
	nelderMead(mf, start, step, 1e-13, 3000);
    }

    void Minimisation::nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
				  double_vector_ptr step, double ftol, int nmax) {
	if (start->size() != step->size()) {
	    throw IllegalArgumentException("start->size() != step->size()");
	}
	mf_ptr = mf;

	if (this->n != (int) start->size()) {
	    if (xmin != null) {
		delete[]xmin;
		delete[]cstep;
		delete[]cstart;
	    }
	    cstart = new double[n];
	    cstep = new double[n];
	    xmin = new double[n];
	}

	this->n = start->size();
	minimisation_n = start->size();
	this->kcount = nmax;

	DoubleArray::toCDoubleArray(start, cstart);
	DoubleArray::toCDoubleArray(step, cstep);

	nelmin(minimisationFunction, n, cstart, xmin, &ynewlo, ftol, cstep, konvge, kcount,
	       &icount, &numres, &ifault);

	paramValues = DoubleArray::toDoubleVector(xmin, n);

    };
    int Minimisation::getNiter() {
	return icount;
    };
    int Minimisation::getNmax() {
	return numres;
    };
    double Minimisation::getMinimum() {
	return ynewlo;
    };
    void Minimisation::setNrestartsMax(int nrm) {
	this->konvge = nrm;
    };
    int Minimisation::getNrestartMax() {
	return konvge;
    };
    double_vector_ptr Minimisation::getParamValues() {
	return paramValues;
    };
    Error Minimisation::getError() {
	switch (ifault) {
	case 0:
	    return Error::NoErrors;
	case 1:
	    return Error::IllegalValue;
	case 2:
	    return Error::IterationTerminate;
	default:
	    return Error::Unknow;

	}
    };

    int Minimisation::minimisation_n;
    bptr < MinimisationFunction > Minimisation::mf_ptr;

    /*Integer::Integer(int val) {
       this->value = val;
       };
       Double::Double(double val) {
       this->value = val;
       };
       Minimisation::Minimisation() {

       nParam = 0;             // number of unknown parameters to be estimated
       //double[] paramValue = null;   // function parameter values (returned at function minimum)
       functValue = 0.0;       // current value of the function to be minimised
       lastFunctValNoCnstrnt = 0.0;    // Last function value with no constraint penalty
       minimum = 0.0;          // value of the function to be minimised at the minimum
       convStatus = false;     // Status of minimisation on exiting minimisation method
       scaleOpt = 0;           // if = 0; no scaling of initial estimates
       //double[] scale = null;        // values to scale initial estimate (see scaleOpt above)
       penalty = false;        // true if single parameter penalty function is included
       sumPenalty = false;     // true if multiple parameter penalty function is included
       nConstraints = 0;       // number of single parameter constraints
       nSumConstraints = 0;    // number of multiple parameter constraints
       maxConstraintIndex = -1;        // maximum index of constrained parameter/s
       //ArrayList < Object > penalties = new ArrayList < Object > ();        // method index,
       //ArrayList < Object > sumPenalties = new ArrayList < Object > ();     // constraint method index,
       //int[] penaltyCheck = null;    // = -1 values below the single constraint boundary not allowed
       //int[] sumPenaltyCheck = null; // = -1 values below the multiple constraint boundary not allowed
       penaltyWeight = 1.0e30; // weight for the penalty functions
       //int[] penaltyParam = null;    // indices of paramaters subject to single parameter constraint
       //int[][] sumPenaltyParam = null;       // indices of paramaters subject to multiple parameter constraint
       //double[][] sumPlusOrMinus = null;     // value before each parameter in multiple parameter summation
       //int[] sumPenaltyNumber = null;        // number of paramaters in each multiple parameter constraint

       //double[] constraints = null;  // single parameter constraint values
       constraintTolerance = 1e-4;     // tolerance in constraining parameter/s to a fixed value
       //double[] sumConstraints = null;       // multiple parameter constraint values
       constraintMethod = 0;   // constraint method number
       nMax = 3000;            //  Nelder and Mead simplex maximum number of iterations
       nIter = 0;              //  Nelder and Mead simplex number of iterations performed
       konvge = 3;             //  Nelder and Mead simplex number of restarts allowed
       kRestart = 0;           //  Nelder and Mead simplex number of restarts taken
       fTol = 1e-13;           //  Nelder and Mead simplex convergence tolerance
       rCoeff = 1.0;           //  Nelder and Mead simplex reflection coefficient
       eCoeff = 2.0;           //  Nelder and Mead simplex extension coefficient
       cCoeff = 0.5;           //  Nelder and Mead simplex contraction coefficient
       //uble[] startH = null; //  Nelder and Mead simplex initial estimates
       //uble[] step = null;   //  Nelder and Mead simplex step values
       dStep = 0.5;            //  Nelder and Mead simplex default step value
       minTest = 0;            //  Nelder and Mead minimum test
       simplexSd = 0.0;        //  simplex standard deviation


       };
       void Minimisation::addConstraint(int paramIndex, int conDir, double constraint) {
       penalty = true;
       // First element reserved for method number if other methods than 'cliff' are added later
       if (penalties.empty()) {
       bptr < Integer > integer(new Integer(constraintMethod));
       penalties.push_back(integer);
       }
       // add constraint

       if (penalties.size() == 1) {
       bptr < Integer > integer(new Integer(1));
       penalties.push_back(integer);
       } else {
       bptr < Integer > i = boost::dynamic_pointer_cast < Integer > (penalties[1]);
       int nPC = i->value;
       nPC++;
       bptr < Integer > integer(new Integer(nPC));
       penalties[1] = integer;
       }

       bptr < Integer > i1(new Integer(paramIndex));
       bptr < Integer > i2(new Integer(conDir));
       bptr < Integer > i3(new Integer(constraint));
       penalties.push_back(i1);
       penalties.push_back(i2);
       penalties.push_back(i3);

       if (paramIndex > maxConstraintIndex) {
       maxConstraintIndex = paramIndex;
       }
       };
       double_vector_ptr Minimisation::getParamValues() {
       return paramValue;
       };
       double Minimisation::getMinimum() {
       return minimum;
       };

       void Minimisation::nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
       double_vector_ptr step) {
       double fToll = fTol;
       int nMaxx = nMax;
       nelderMead(mf, start, step, fToll, nMaxx);
       };
       void Minimisation::nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
       double_vector_ptr step, double fTol, int nMax) {

       mObject_ptr g = boost::dynamic_pointer_cast < mObject > (mf);
       nelderMead(g, start, step, fTol, nMax);
       };
       void Minimisation::nelderMead(mObject_ptr g, double_vector_ptr start,
       double_vector_ptr step, double fTol, int nMax) {
       int np = start->size(); // number of unknown parameters;
       if (maxConstraintIndex >= np) {
       //throw IllegalArgumentException("You have entered more constrained parameters (" +
       //                                   maxConstraintIndex +
       //                         ") than minimisation parameters (" + np + ")");

       throw IllegalArgumentException("");
       }
       nParam = np;
       convStatus = true;
       int nnp = np + 1;       // Number of simplex apices
       lastFunctValNoCnstrnt = 0.0;

       if (scaleOpt < 2) {
       //scale = new double[np];
       scale = double_vector_ptr(new double_vector());
       }
       if (scaleOpt == 2 && scale->size() != start->size()) {
       throw
       IllegalArgumentException
       ("scale array and initial estimate array are of different lengths");
       }
       if (step->size() != start->size()) {
       throw IllegalArgumentException("");
       //throw IllegalArgumentException("step array length " + step->size() +
       //                                   " and initial estimate array length " +
       //                         start->size() + " are of different");
       }
       // check for zero step sizes
       for (int i = 0; i < np; i++) {
       if ((*step)[i] == 0.0) {
       if ((*start)[i] != 0.0) {
       (*step)[i] = (*start)[i] * 0.1;
       } else {
       (*step)[i] = 1.0;
       //System.out.
       //println
       //("As no step size has been entered for an itial estimate of zero an initial step size of unity has been used");
       //System.out.
       //println
       //("You are advised to repeat the minimization using one of the methods allowing the setting of an appropriate non-zero initial step size"); 
       }
       }
       }

       // set up arrays
       paramValue = double_vector_ptr(new double_vector(np));
       startH = double_vector_ptr(new double_vector(np));
       step = double_vector_ptr(new double_vector(np));
       double_vector_ptr pmin(new double_vector(np));  //Nelder and Mead Pmin


       //double[][] pp = new double[nnp][nnp]; //Nelder and Mead P
       double2D_ptr pp(new double2D(nnp, nnp));        //Nelder and Mead P
       double_vector_ptr yy(new double_vector(nnp));   //Nelder and Mead y
       double_vector_ptr pbar(new double_vector(nnp)); //Nelder and Mead P with bar superscript
       double_vector_ptr pstar(new double_vector(nnp));        //Nelder and Mead P*
       double_vector_ptr p2star(new double_vector(nnp));       //Nelder and Mead P**

       // Set any single parameter constraint parameters
       if (penalty) {

       bptr < Integer > itemp = boost::dynamic_pointer_cast < Integer > (penalties[1]);

       nConstraints = itemp->value;

       penaltyParam = int_vector_ptr(new int_vector(nConstraints));
       penaltyCheck = int_vector_ptr(new int_vector(nConstraints));
       constraints = int_vector_ptr(new int_vector(nConstraints));
       bptr < Double > dtemp;
       int j = 2;
       for (int i = 0; i < nConstraints; i++) {
       itemp = boost::dynamic_pointer_cast < Integer > (penalties[j]);
       (*penaltyParam)[i] = itemp->value;
       j++;
       itemp = boost::dynamic_pointer_cast < Integer > (penalties[j]);
       (*penaltyCheck)[i] = itemp->value;
       j++;
       dtemp = boost::dynamic_pointer_cast < Double > (penalties[j]);
       (*constraints)[i] = dtemp->value;
       j++;
       }
       }
       // Set any multiple parameter constraint parameters
       if (sumPenalty) {

       bptr < Integer > itemp = boost::dynamic_pointer_cast < Integer > (sumPenalties[1]);
       nSumConstraints = itemp->value;

       sumPenaltyParam = int_vector_ptr(new int_vector(nSumConstraints));
       sumPlusOrMinus = double_vector_ptr(new double_vector(nSumConstraints));
       sumPenaltyCheck = int_vector_ptr(new int_vector(nSumConstraints));
       sumPenaltyNumber = int_vector_ptr(new int_vector(nSumConstraints));
       sumConstraints = double_vector_ptr(new double_vector(nSumConstraints));
       int_vector_ptr itempArray;
       double_vector_ptr dtempArray;
       bptr < Double > dtemp;
       int j = 2;
       for (int i = 0; i < this.nSumConstraints; i++) {
       itemp = (Integer) this.sumPenalties.get(j);
       this.sumPenaltyNumber[i] = itemp.intValue();
       j++;
       itempArray = (int[]) this.sumPenalties.get(j);
       this.sumPenaltyParam[i] = itempArray;
       j++;
       dtempArray = (double[]) this.sumPenalties.get(j);
       this.sumPlusOrMinus[i] = dtempArray;
       j++;
       itemp = (Integer) this.sumPenalties.get(j);
       this.sumPenaltyCheck[i] = itemp.intValue();
       j++;
       dtemp = (Double) this.sumPenalties.get(j);
       this.sumConstraints[i] = dtemp.doubleValue();
       j++;
       }
       }
       // Store unscaled start values
       for (int i = 0; i < np; i++) {
       this.startH[i] = start[i];
       }

       // scale initial estimates and step sizes
       if (this.scaleOpt > 0) {
       boolean testzero = false;
       for (int i = 0; i < np; i++) {
       if (start[i] == 0.0 D) {
       testzero = true;
       }
       }
       if (testzero) {
       System.out.
       println("Neler and Mead Simplex: a start value of zero precludes scaling");
       System.out.println("Regression performed without scaling");
       this.scaleOpt = 0;
       }
       }
       switch (this.scaleOpt) {
       case 0:
       for (int i = 0; i < np; i++) {
       scale[i] = 1.0 D;
       }
       break;
       case 1:
       for (int i = 0; i < np; i++) {
       scale[i] = 1.0 / start[i];
       step[i] = step[i] / start[i];
       start[i] = 1.0 D;
       }
       break;
       case 2:
       for (int i = 0; i < np; i++) {
       step[i] *= scale[i];
       start[i] *= scale[i];
       }
       break;
       }

       // set class member values
       this.fTol = fTol;
       this.nMax = nMax;
       this.nIter = 0;
       for (int i = 0; i < np; i++) {
       this.step[i] = step[i];
       this.scale[i] = scale[i];
       }

       // initial simplex
       double sho = 0.0 D;
       for (int i = 0; i < np; ++i) {
       sho = start[i];
       pstar[i] = sho;
       p2star[i] = sho;
       pmin[i] = sho;
       }

       int jcount = this.konvge;       // count of number of restarts still available

       for (int i = 0; i < np; ++i) {
       pp[i][nnp - 1] = start[i];
       }
       yy[nnp - 1] = this.functionValue(g, start);
       for (int j = 0; j < np; ++j) {
       start[j] = start[j] + step[j];

       for (int i = 0; i < np; ++i) {
       pp[i][j] = start[i];
       }
       yy[j] = this.functionValue(g, start);
       start[j] = start[j] - step[j];
       }

       // loop over allowed iterations
       double ynewlo = 0.0 D;  // current value lowest y
       double ystar = 0.0 D;   // Nelder and Mead y*
       double y2star = 0.0 D;  // Nelder and Mead y**
       double ylo = 0.0 D;     // Nelder and Mead y(low)
       double fMin;            // function value at minimum
       // variables used in calculating the variance of the simplex at a putative minimum
       double curMin = 00 D, sumnm = 0.0 D, summnm = 0.0 D, zn = 0.0 D;
       int ilo = 0;            // index of low apex
       int ihi = 0;            // index of high apex
       int ln = 0;             // counter for a check on low and high apices
       boolean test = true;    // test becomes false on reaching minimum

       while (test) {
       // Determine h
       ylo = yy[0];
       ynewlo = ylo;
       ilo = 0;
       ihi = 0;
       for (int i = 1; i < nnp; ++i) {
       if (yy[i] < ylo) {
       ylo = yy[i];
       ilo = i;
       }
       if (yy[i] > ynewlo) {
       ynewlo = yy[i];
       ihi = i;
       }
       }
       // Calculate pbar
       for (int i = 0; i < np; ++i) {
       zn = 0.0 D;
       for (int j = 0; j < nnp; ++j) {
       zn += pp[i][j];
       }
       zn -= pp[i][ihi];
       pbar[i] = zn / np;
       }

       // Calculate p=(1+alpha).pbar-alpha.ph {Reflection}
       for (int i = 0; i < np; ++i) {
       pstar[i] = (1.0 + this.rCoeff) * pbar[i] - this.rCoeff * pp[i][ihi];
       }

       // Calculate y*
       ystar = this.functionValue(g, pstar);

       ++this.nIter;

       // check for y*<yi
       if (ystar < ylo) {
       // Form p**=(1+gamma).p*-gamma.pbar {Extension}
       for (int i = 0; i < np; ++i) {
       p2star[i] = pstar[i] * (1.0 D + this.eCoeff) - this.eCoeff * pbar[i];
       }
       // Calculate y**
       y2star = this.functionValue(g, p2star);
       ++this.nIter;
       if (y2star < ylo) {
       // Replace ph by p**
       for (int i = 0; i < np; ++i) {
       pp[i][ihi] = p2star[i];
       }
       yy[ihi] = y2star;
       } else {
       //Replace ph by p*
       for (int i = 0; i < np; ++i) {
       pp[i][ihi] = pstar[i];
       }
       yy[ihi] = ystar;
       }
       } else {
       // Check y*>yi, i!=h
       ln = 0;
       for (int i = 0; i < nnp; ++i) {
       if (i != ihi && ystar > yy[i]) {
       ++ln;
       }
       }
       if (ln == np) {
       // y*>= all yi; Check if y*>yh
       if (ystar <= yy[ihi]) {
       // Replace ph by p*
       for (int i = 0; i < np; ++i) {
       pp[i][ihi] = pstar[i];
       }
       yy[ihi] = ystar;
       }
       // Calculate p** =beta.ph+(1-beta)pbar  {Contraction}
       for (int i = 0; i < np; ++i) {
       p2star[i] = this.cCoeff * pp[i][ihi] + (1.0 - this.cCoeff) * pbar[i];
       }
       // Calculate y**
       y2star = this.functionValue(g, p2star);
       ++this.nIter;
       // Check if y**>yh
       if (y2star > yy[ihi]) {
       //Replace all pi by (pi+pl)/2

       for (int j = 0; j < nnp; ++j) {
       for (int i = 0; i < np; ++i) {
       pp[i][j] = 0.5 * (pp[i][j] + pp[i][ilo]);
       pmin[i] = pp[i][j];
       }
       yy[j] = this.functionValue(g, pmin);
       }
       this.nIter += nnp;
       } else {
       // Replace ph by p**
       for (int i = 0; i < np; ++i) {
       pp[i][ihi] = p2star[i];
       }
       yy[ihi] = y2star;
       }
       } else {
       // replace ph by p*
       for (int i = 0; i < np; ++i) {
       pp[i][ihi] = pstar[i];
       }
       yy[ihi] = ystar;
       }
       }

       // test for convergence
       // calculte sd of simplex and minimum point
       sumnm = 0.0;
       ynewlo = yy[0];
       ilo = 0;
       for (int i = 0; i < nnp; ++i) {
       sumnm += yy[i];
       if (ynewlo > yy[i]) {
       ynewlo = yy[i];
       ilo = i;
       }
       }
       sumnm /= (double) (nnp);
       summnm = 0.0;
       for (int i = 0; i < nnp; ++i) {
       zn = yy[i] - sumnm;
       summnm += zn * zn;
       }
       curMin = Math.sqrt(summnm / np);

       // test simplex sd
       switch (this.minTest) {
       case 0:
       if (curMin < fTol) {
       test = false;
       }
       break;
       }
       this.minimum = ynewlo;
       if (!test) {
       // store parameter values
       for (int i = 0; i < np; ++i) {
       pmin[i] = pp[i][ilo];
       }
       yy[nnp - 1] = ynewlo;
       // store simplex sd
       this.simplexSd = curMin;
       // test for restart
       --jcount;
       if (jcount > 0) {
       test = true;
       for (int j = 0; j < np; ++j) {
       pmin[j] = pmin[j] + step[j];
       for (int i = 0; i < np; ++i) {
       pp[i][j] = pmin[i];
       }
       yy[j] = this.functionValue(g, pmin);
       pmin[j] = pmin[j] - step[j];
       }
       }
       }

       if (test && this.nIter > this.nMax) {
       this.convStatus = false;
       // store current estimates
       for (int i = 0; i < np; ++i) {
       pmin[i] = pp[i][ilo];
       }
       yy[nnp - 1] = ynewlo;
       test = false;
       }
       }

       for (int i = 0; i < np; ++i) {
       pmin[i] = pp[i][ilo];
       paramValue[i] = pmin[i] / this.scale[i];
       }
       this.minimum = ynewlo;
       this.kRestart = this.konvge - jcount;
       }; */
};

