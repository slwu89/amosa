/* --------------------------------------------------------------------------------
#
#   struct to contain AMOSA optimization fn parameters
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_PROBLEMS
#define AMOSA_PROBLEMS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>


/* --------------------------------------------------------------------------------
#	Generic AMOSA problem struct
-------------------------------------------------------------------------------- */

typedef struct AMOSAType
{
	int i_hardl;				/* Hardlimit of the archive */
	int i_softl;				/* Softlimit of the archive */
	int i_no_ofiter;			/* Number of iteration per temperature */
	int i_hillclimb_no;			/* Total number of hill_climbing number */
	int i_totalno_var;			/* Total number of variable of the functions */
	int i_archivesize;			/* Stores the archive size */
	int i_no_offunc;			/* Number of function */

	double d_tmax;				/* maximum temperature */
	double d_tmin;				/* minimum temperature */
	double d_alpha;				/* cooling rate */
	double** d_solution;		/* data structure corresponding to binary strings */
	double** d_archive;			/* archive */
	double** d_func_archive;	/* variable to store the functional values of the archive solutions */
	double* d_eval; 			/* objectives function values*/
	double* d_func_range;		/* range of the functions */
	double* d_min_real_var;		/* Store minimum value of the real variables */
 	double* d_max_real_var;		/* Store maximum value of the real variables */
} AMOSAType;


/* --------------------------------------------------------------------------------
#		DTLZ1 type
-------------------------------------------------------------------------------- */

// initializes an amosa type
void init_AMOSAType_DTLZ1(AMOSAType* amosa);

// frees the memory
void free_AMOSAType_DTLZ1(AMOSAType* amosa);

// evaluates the type at a point in paramter space
void evaluate_DTLZ1(double* s, AMOSAType* amosa);


# endif
