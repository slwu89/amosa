/* --------------------------------------------------------------------------------
#
#   generic interface to evaluate various multi-objective problems
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_EVALUATE
#define AMOSA_EVALUATE

#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#   Main interface function
-------------------------------------------------------------------------------- */

void evaluate(double* s, AMOSAType* amosa);


#endif
