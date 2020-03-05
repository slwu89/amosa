/* --------------------------------------------------------------------------------
#
#
#
-------------------------------------------------------------------------------- */

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

SEXP call_DTLZ1_from_c(SEXP sR, SEXP rho){
  SEXP R_fun, sym_fun, out;
  PROTECT(sym_fun = install("DTLZ1"));
  R_fun = PROTECT(LCONS(sym_fun,LCONS(sR,R_NilValue)));
  PROTECT(out = Rf_eval(R_fun,rho));
  UNPROTECT(2);
  return out;
};
