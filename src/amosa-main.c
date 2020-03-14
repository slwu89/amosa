/* --------------------------------------------------------------------------------
#
#   The R interface
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */


#include "amosa-main.h"

#include "amosa-problems.h"
#include "amosa-initsoln.h"
#include "amosa-initarchive.h"
#include "amosa-burnin.h"
#include "amosa-algorithm.h"

/* --------------------------------------------------------------------------------
#   run amosa
-------------------------------------------------------------------------------- */

SEXP AMOSA_C(SEXP verboseR){

  GetRNGstate();

  int verbose = Rf_asLogical(verboseR);

  AMOSAType amosa;

  if(verbose){Rprintf(" --- INIT AMOSA TYPE --- \n");}
  init_AMOSAType_DTLZ1(&amosa,verbose);

  if(verbose){Rprintf(" --- INITIALIZE SOLUTIONS --- \n");}
  initialize_sol(&amosa);

  if(verbose){Rprintf(" --- CREATE ARCHIVE --- \n");}
  creating_archive(&amosa);

  if(verbose){Rprintf(" --- BURN IN TEMPERATURE --- \n");}
  burn_in_period(&amosa);

  if(verbose){Rprintf(" --- RUN AMOSA ALGORITHM --- \n");}
  RunAMOSA(&amosa);

  if(verbose){Rprintf(" --- FORMAT OUTPUT --- \n");}

  SEXP d_archive_2R = PROTECT(Rf_allocMatrix(INTSXP,amosa.i_archivesize,amosa.i_totalno_var));
  int* d_archive_2R_ptr = INTEGER(d_archive_2R);

  SEXP d_func_archive_2R = PROTECT(Rf_allocMatrix(REALSXP,amosa.i_archivesize,amosa.i_no_offunc));
  double* d_func_archive_2R_ptr = REAL(d_func_archive_2R);

  // gg iterates over "rows"
  if(amosa.i_archivesize > (amosa.i_softl+3)){
    Rprintf(" --- warning 'i_archivesize' (%d) is greater than '(i_softl+3)' (%d) --- \n",amosa.i_archivesize,(amosa.i_softl+3));
  }

  for(int gg=0; gg<amosa.i_archivesize; gg++){

    // fill d_archive_2R
    for(int hh=0; hh<amosa.i_totalno_var; hh++){
      d_archive_2R_ptr[gg + amosa.i_archivesize*hh] = amosa.d_archive[gg][hh];
    }

    // fill d_func_archive_2R
    for(int hh=0; hh<amosa.i_no_offunc; hh++){
      d_func_archive_2R_ptr[gg + amosa.i_archivesize*hh] = amosa.d_func_archive[gg][hh];
    }

  }

  // set up output for R
  SEXP out = PROTECT(Rf_allocVector(VECSXP,2));
  SET_VECTOR_ELT(out,0,d_archive_2R);
  SET_VECTOR_ELT(out,1,d_func_archive_2R);

  SEXP names = PROTECT(Rf_allocVector(STRSXP,2));
  SET_STRING_ELT(names,0,Rf_mkChar("d_archive"));
  SET_STRING_ELT(names,1,Rf_mkChar("d_func_archive"));

  Rf_namesgets(out,names);

  PutRNGstate();

  free_AMOSAType_DTLZ1(&amosa);

  UNPROTECT(4);

  return out;
};
