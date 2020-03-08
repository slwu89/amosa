/* --------------------------------------------------------------------------------
#
#   mutation for individual string
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-mutate.h"
#include "amosa-problems.h"


void real_mutate_ind(double* s, AMOSAType* amosa){

  // local variables
  int i, j;
  int i_count;
  int i_rnd1;
  double d_rnd;
  double d_rnd2;
  double b;
  double y;
  double d_rand_lap;

  // pick variable to mutate
  d_rnd2 = floor(unif_rand() * amosa->i_totalno_var);
  i_rnd1 = (int)d_rnd2;
  y = s[i_rnd1];

  b = 0.25;
  d_rnd = unif_rand();
  d_rnd = d_rnd-0.5;

  if(d_rnd < 0.){
    d_rand_lap = b * log(1-2*fabs(d_rnd));
  } else {
    d_rand_lap = -b * log(1-2*fabs(d_rnd));
  }

  y += d_rand_lap;
  i_count = 0;

  while ((y<amosa->d_min_real_var[i_rnd1] || y>amosa->d_max_real_var[i_rnd1]) && (i_count<20)){

    y = s[i_rnd1];
    d_rnd = unif_rand();
    d_rnd = d_rnd-0.5;

    if(d_rnd < 0.){
      d_rand_lap = b * log(1-2*fabs(d_rnd));
    } else {
      d_rand_lap = -b * log(1-2*fabs(d_rnd));
    }

    y += d_rand_lap;
    i_count++;
  }

  s[i_rnd1] = y;

  if(i_count == 20){
    if(s[i_rnd1]<amosa->d_min_real_var[i_rnd1]){
      s[i_rnd1]=amosa->d_min_real_var[i_rnd1];
    } else if (s[i_rnd1]>amosa->d_max_real_var[i_rnd1]){
      s[i_rnd1]=amosa->d_max_real_var[i_rnd1];
    }
  }

};
