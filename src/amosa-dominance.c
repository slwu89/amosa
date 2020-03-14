/* --------------------------------------------------------------------------------
#
#   check if solutions dominate each other
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-dominance.h"

#include <float.h>


/* --------------------------------------------------------------------------------
#   The Following function checks whether the solution vector func1 dominates the solution vector func2
-------------------------------------------------------------------------------- */

int is_dominated(double* func1, double* func2, AMOSAType* amosa){

	int i;
	int i_count_less = 0;
  int i_count_equal = 0;
	double ff;

	for(i=0;i<amosa->i_no_offunc;i++){

		ff = (func1[i]-func2[i]);
		if(func1[i]<func2[i]){
      i_count_less++;
    } else if(func1[i]==func2[i]) {
      i_count_equal++;
    }
	}

  int ret;

	if(((i_count_less+i_count_equal)==amosa->i_no_offunc) && i_count_less>0){
    ret = 1;
  } else {
    ret = 0;
  }

  return ret;
}


/* --------------------------------------------------------------------------------
#   The Following function calculates the unsigned amount of domination between two solution vectors func1 and func2
-------------------------------------------------------------------------------- */

double find_unsign_dom(double* func1, double* func2, AMOSAType* amosa){

	int i;
	double d_dominance = 1.;

	for(i=0;i<amosa->i_no_offunc;i++){

    if( fabs(func1[i] - func2[i]) > DBL_EPSILON){
      d_dominance = d_dominance * fabs(func1[i] - func2[i]) / amosa->d_func_range[i];
    }

		// if((func1[i]-func2[i])!=0.0){
    //   d_dominance=d_dominance*fabs(func1[i]-func2[i])/amosa->d_func_range[i];
    // }

	}

	return d_dominance;
}


/* --------------------------------------------------------------------------------
#   The Following function calculates the signed amount of domination between two solution vectors func1 and func2
-------------------------------------------------------------------------------- */

double find_sign_dom(double* func1, double* func2, AMOSAType* amosa){

	int i;
	double d_dominance = 1.;

	for(i=0;i<amosa->i_no_offunc;i++){

    if( fabs(func1[i] - func2[i]) > DBL_EPSILON){
      d_dominance = d_dominance * (func1[i]-func2[i]) / amosa->d_func_range[i];
    }

		// if(fabs(func1[i]-func2[i])!=0)
		// 	d_dominance=d_dominance*(func1[i]-func2[i])/amosaParams->d_func_range[i];
	}
  
	return d_dominance;
}
