/* --------------------------------------------------------------------------------
#
#   struct to contain AMOSA optimization fn parameters
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_TYPE
#define AMOSA_TYPE

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct AMOSAType
{
	int i_hardl;				/* Hardlimit of the archive */
	int i_softl;				/* Softlimit of the archive */
	int i_no_ofiter;			/* Number of iteration per temperature */
	int i_hillclimb_no;			/* Total number of hill_climbing number */
	int i_totalno_var;			/* Total number of variable of the functions */
	int i_archivesize;			/* Stores the archive size */
	int i_no_offunc;			/* Number of function */

	char c_problem[50];			/* function name to be optimized */

	double d_tmax;				/* maximum temperature */
	double d_tmin;				/* minimum temperature */
	double d_alpha;				/* cooling rate */
	double **d_solution;		/* data structure corresponding to binary strings */
	double **d_archive;			/* archive */
	double **d_func_archive;	/* variable to store the functional values of the archive solutions */
	double *d_eval; 			/* objectives function values*/
	double *d_func_range;		/* range of the functions */
	double *d_min_real_var;		/* Store minimum value of the real variables */
 	double *d_max_real_var;		/* Store maximum value of the real variables */
} AMOSAType;


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

	amosa->i_archivesize = amosa->i_softl + 3;

	amosa->d_min_real_var = (double*)malloc(amosa->i_totalno_var * sizeof(double));	/* memory allocation to store the minimum value of real variables in the functions */
	amosa->d_max_real_var = (double*)malloc(amosa->i_totalno_var * sizeof(double));	/* memory allocation to store the maximum value of real variables in the functions */

	for(int i=0; i<amosa->i_totalno_var; i++){
		amosa->d_min_real_var[i] = 0.;
		amosa->d_max_real_var[i] = 1.;
	}


	// amosaParams->d_func_archive = (double **) malloc ((amosaParams->i_softl + 3) * sizeof (double *));	/* allocating memory for func_archive */
	// for (i = 0; i < (amosaParams->i_softl + 3); i++)
	// 	amosaParams->d_func_archive[i] = (double *) malloc (amosaParams->i_no_offunc * sizeof (double));
	// amosaParams->d_eval = (double *) malloc (amosaParams->i_no_offunc * sizeof (double));


};



# endif
