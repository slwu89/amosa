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
void init_AMOSAType_DTLZ1(AMOSAType* amosa, const int verbose){

	amosa->i_hardl = 40;
	amosa->i_softl = 20;
	amosa->i_no_ofiter = 500;
	amosa->i_hillclimb_no = 20;
	amosa->i_totalno_var = 7;
	amosa->i_archivesize = 0;
	amosa->i_no_offunc = 3;

	if(verbose > 1 || verbose < 0){
		error("verbose must be an int (boolean)");
	}

	amosa->verbose = verbose;

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


// free the memory
void free_AMOSAType_DTLZ1(AMOSAType* amosa){

	for(int i=0; i<amosa->i_softl; i++){
		free(amosa->d_solution[i]);
	}
	free(amosa->d_solution);

	for(int i=0; i<(amosa->i_softl + 3); i++){
		free(amosa->d_archive[i]);
		free(amosa->d_func_archive[i]);
	}
	free(amosa->d_archive);
	free(amosa->d_func_archive);

	free(amosa->d_eval);

	free(amosa->d_func_range);

	free(amosa->d_min_real_var);
	free(amosa->d_max_real_var);

};

// evaluates the type at a point in paramter space, using the R function in the package
void evaluate_DTLZ1(double* s, AMOSAType* amosa){

  // s_sexp <- s
  SEXP s_sexp = PROTECT(Rf_allocVector(REALSXP,amosa->i_totalno_var));
  memmove(REAL(s_sexp),s,sizeof(double)*amosa->i_totalno_var);

  SEXP R_fun, sym_fun, out;
  PROTECT(sym_fun = install("DTLZ1"));
  R_fun = PROTECT(LCONS(sym_fun,LCONS(s_sexp,R_NilValue)));
  PROTECT(out = Rf_eval(R_fun,R_GlobalEnv));

  // amosa->d_eval <- out
  memmove(amosa->d_eval,REAL(out),amosa->i_no_offunc*sizeof(double));
  UNPROTECT(4);
};
