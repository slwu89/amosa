/* --------------------------------------------------------------------------------
#
#   initializes the soft limit number of initial solutions
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_INITSOLN
#define AMOSA_INITSOLN

#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <Rmath.h>

#include "amosa-problems.h"
#include "amosa-evaluate.h"
#include "amosa-mutate.h"


/* --------------------------------------------------------------------------------
#   The following function initializes the softl number of solutions
-------------------------------------------------------------------------------- */

void initialize_sol(AMOSAType* amosa);


#endif
