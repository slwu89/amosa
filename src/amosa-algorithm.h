/* --------------------------------------------------------------------------------
#
#   The main AMOSA process
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_ALGORITHM
#define AMOSA_ALGORITHM

#include <stdlib.h>
#include <time.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <Rmath.h>

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#   main AMOSA process
-------------------------------------------------------------------------------- */

void RunAMOSA(AMOSAType* amosa);

#endif
