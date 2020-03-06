/* --------------------------------------------------------------------------------
#
#   initializes the soft limit number of initial solutions
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-initsoln.h"


/* --------------------------------------------------------------------------------
#   The following function initializes the softl number of solutions
-------------------------------------------------------------------------------- */

void initialize_sol(AMOSAType* amosa){

  // local variables we need
  int i,j,f, ii;
  int i_count;
  double *d_xnew;
  double *d_area1,*d_area2;
  d_area1 = (double*)malloc(amosa->i_no_offunc*sizeof(double));
  d_area2 = (double*)malloc(amosa->i_no_offunc*sizeof(double));

  /* Randomly initializing softl number of solutions */
  for(i=0; i<amosa->i_softl; i++){
    for(j=0; j<amosa->i_totalno_var; j++){
      amosa->d_solution[i][j] = runif(amosa->d_min_real_var[j],amosa->d_max_real_var[j]);
    }
  }

  d_xnew = (double*)malloc(amosa->i_totalno_var*sizeof(double));

  /* Performing some hill-climbing operation on solutions of the archive */
  for(ii=0; ii<amosa->i_softl; ii++){
    for(j=0;j<amosa->i_hillclimb_no;j++){

      /* This function calls different evaluation functions */
      evaluate(amosa->d_solution[ii], amosa);

      for(i=0;i<amosa->i_no_offunc;i++){
        d_area1[i]=amosa->d_eval[i];
      }

      for(f=0;f<amosa->i_totalno_var;f++){
        d_xnew[f]=amosa->d_solution[ii][f];
      }

      /* Function performing mutation on individual string */
      real_mutate_ind(d_xnew, amosa);

      /* This function calls different evaluation functions */
      evaluate(d_xnew, amosa);

      for(i=0;i<amosa->i_no_offunc;i++){
        d_area2[i]=amosa->d_eval[i];
      }

      i_count=0;
      for(i=0;i<amosa->i_no_offunc;i++){
        if(d_area1[i]>=d_area2[i]){
          i_count++;
        }
      }

      if(i_count==amosa->i_no_offunc){
        for(f=0;f<amosa->i_totalno_var;f++){
          amosa->d_solution[ii][f]=d_xnew[f];
        }
      }

    }
  }

  // free memory
  free(d_area1);
  free(d_area2);
  free(d_xnew);
};
