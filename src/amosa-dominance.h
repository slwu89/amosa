/* --------------------------------------------------------------------------------
#
#   check if solutions dominate each other
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_DOMINANCE
#define AMOSA_DOMINANCE

#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <Rmath.h>

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#   The Following function checks whether the solution vector func1 dominates the solution vector func2
-------------------------------------------------------------------------------- */

int is_dominated(double* func1, double* func2, AMOSAType* amosa);


/* --------------------------------------------------------------------------------
#   The Following function calculates the unsigned amount of domination between two solution vectors func1 and func2
-------------------------------------------------------------------------------- */

double find_unsign_dom(double* func1, double* func2, AMOSAType* amosa);


/* --------------------------------------------------------------------------------
#   The Following function calculates the signed amount of domination between two solution vectors func1 and func2
-------------------------------------------------------------------------------- */

double find_sign_dom(double* func1, double* func2, AMOSAType* amosa);


#endif
