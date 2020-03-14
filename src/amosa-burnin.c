/* --------------------------------------------------------------------------------
#
#   burnin temperature
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-burnin.h"

#include "amosa-mutate.h"
#include "amosa-evaluate.h"


/* --------------------------------------------------------------------------------
#   Function to initialize Tmax which is the maximum temperature
-------------------------------------------------------------------------------- */

void burn_in_period(AMOSAType* amosa){

  // variable declaration
  int r;
  int h;
  int i_count=0;
  double *d_newsol,d_energy,d_pos_energy=0;
  double *func,*func1;

  // Body of the burn_in_period function

  d_newsol = (double *)malloc(sizeof(double)*amosa->i_totalno_var);
  func = (double *)malloc(sizeof(double)*amosa->i_no_offunc);
  func1 = (double *)malloc(sizeof(double)*amosa->i_no_offunc);

  while(i_count<amosa->i_hillclimb_no){

    /* Finding a random number between 0 and archivesize*/
    r = (int)floor(runif(0.,(double)amosa->i_archivesize));

    for( h=0;h<amosa->i_no_offunc;h++ ){
      func1[h] = amosa->d_func_archive[r][h];
    }

    for(h=0;h<amosa->i_totalno_var;h++){
      d_newsol[h]=amosa->d_archive[r][h];
    }

    /* Function performimg mutation on individual string */
    real_mutate_ind(d_newsol, amosa);

    /* This function calls different evaluation functions*/
    evaluate(d_newsol, amosa);

    for(h=0;h<amosa->i_no_offunc;h++){
      func[h]=amosa->d_eval[h];
    }

    d_energy = find_sign_dom(func,func1, amosa);
    if(d_energy > 0.){
      d_pos_energy+=d_energy;
      i_count++;
    }  //end of inner if loop
  }   //end of outer while loop

  d_pos_energy = (d_pos_energy/i_count);
  amosa->d_tmax = (d_pos_energy/log(2.));
};
