/* --------------------------------------------------------------------------------
#
#   mutation for individual string
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_MUTATE
#define AMOSA_MUTATE

#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#   Function performimg mutation on individual string
-------------------------------------------------------------------------------- */

void real_mutate_ind(double* s, AMOSAType* amosa);

#endif
