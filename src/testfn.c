/* --------------------------------------------------------------------------------
#
#   Test functions from AMOSA
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

// testing calling the R function from C
SEXP call_DTLZ1_from_c(SEXP sR){
  SEXP R_fun, sym_fun, out;
  PROTECT(sym_fun = install("DTLZ1"));
  R_fun = PROTECT(LCONS(sym_fun,LCONS(sR,R_NilValue)));
  PROTECT(out = Rf_eval(R_fun,R_GlobalEnv));
  UNPROTECT(3);
  return out;
};
