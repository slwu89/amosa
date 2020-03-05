/* --------------------------------------------------------------------------------
#
#   struct to contain AMOSA optimization fn parameters
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#		DTLZ1 type
-------------------------------------------------------------------------------- */

// initializes an amosa type
void init_AMOSAType_DTLZ1(AMOSAType* amosa){

	amosa->i_hardl = 40;
	amosa->i_softl = 20;
	amosa->i_no_ofiter = 500;
	amosa->i_hillclimb_no = 20;
	amosa->i_totalno_var = 7;
	// amosa->i_archivesize;
	amosa->i_no_offunc = 3;

	strncpy(amosa->c_problem, "DTLZ1", 50);

	amosa->d_tmax = 200.;
	amosa->d_tmin = 1E-7;
	amosa->d_alpha = 0.8;

	// allocate memory
	amosa->d_solution = (double**)malloc(amosa->i_softl * sizeof(double*));	/* memory allocation for storing solution in a variable named solution. */
	for(int i=0; i<amosa->i_softl; i++){
		amosa->d_solution[i] = (double*)malloc(amosa->i_totalno_var * sizeof(double));
	}

	amosa->d_archive = (double**)malloc((amosa->i_softl + 3) * sizeof(double*));	/* memory allocation for archive */
	for(int i=0; i<(amosa->i_softl + 3); i++){
		amosa->d_archive[i] = (double*)malloc(amosa->i_totalno_var * sizeof(double));
	}

	amosa->d_func_archive = (double**)malloc((amosa->i_softl + 3) * sizeof(double*));	/* memory allocation for archive */
	for(int i=0; i<(amosa->i_softl + 3); i++){
		amosa->d_func_archive[i] = (double*)malloc(amosa->i_totalno_var * sizeof(double));
	}

	amosa->d_eval = (double*)malloc(amosa->i_no_offunc*sizeof(double));
	amosa->i_archivesize = amosa->i_softl + 3;

	amosa->d_func_range = (double*)malloc(amosa->i_no_offunc * sizeof(double)); /* dynamically allocating memory to store the functional values of the archive solutions */
	for(int i=0; i<amosa->i_no_offunc; i++){
		amosa->d_func_range[i] = 500.;
	}

	amosa->d_min_real_var = (double*)malloc(amosa->i_totalno_var * sizeof(double));	/* memory allocation to store the minimum value of real variables in the functions */
	amosa->d_max_real_var = (double*)malloc(amosa->i_totalno_var * sizeof(double));	/* memory allocation to store the maximum value of real variables in the functions */

	for(int i=0; i<amosa->i_totalno_var; i++){
		amosa->d_min_real_var[i] = 0.;
		amosa->d_max_real_var[i] = 1.;
	}

};

// evaluates the type at a point in paramter space, using the R function in the package
void evaluate_DTLZ1(double* s, AMOSAType* amosa, SEXP rho){

  // s_sexp <- s
  SEXP s_sexp = PROTECT(Rf_allocVector(REALSXP,amosa->i_totalno_var));
  memcpy(REAL(s_sexp),s,sizeof(double)*amosa->i_totalno_var);

  SEXP R_fun, sym_fun, out;
  PROTECT(sym_fun = install("DTLZ1"));
  R_fun = PROTECT(LCONS(sym_fun,LCONS(s_sexp,R_NilValue)));
  PROTECT(out = Rf_eval(R_fun,rho));

  // amosa->d_eval <- out
  memcpy(amosa->d_eval,REAL(out),amosa->i_no_offunc*sizeof(double));
  UNPROTECT(4);
};