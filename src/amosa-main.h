/* --------------------------------------------------------------------------------
#
#   The R interface
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_MAIN
#define AMOSA_MAIN

#include <stdlib.h>
#include <time.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include <Rmath.h>


/* --------------------------------------------------------------------------------
#   run amosa
-------------------------------------------------------------------------------- */

SEXP AMOSA_C(SEXP verboseR);

#endif
