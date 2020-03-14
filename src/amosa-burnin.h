/* --------------------------------------------------------------------------------
#
#   burnin temperature
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_BURN
#define AMOSA_BURN

#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <Rmath.h>

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#   Function to initialize Tmax which is the maximum temperature
-------------------------------------------------------------------------------- */

void burn_in_period(AMOSAType* amosa);

#endif
