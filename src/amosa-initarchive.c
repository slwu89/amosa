/* --------------------------------------------------------------------------------
#
#   creates the archive
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-initarchive.h"
#include "amosa-problems.h"
#include "amosa-evaluate.h"


/* --------------------------------------------------------------------------------
#   Function creating the archive
-------------------------------------------------------------------------------- */

void creating_archive(AMOSAType* amosa){

  // local variables
  int i,j,h;
  int g=0;
  int count,count1;
  int* i_flag;
  double** d_area;

  // alloc memory
  i_flag = (int*)malloc(amosa->i_softl * sizeof(int));

  d_area = (double**)malloc(amosa->i_softl*sizeof(double*));
  for(i=0; i<amosa->i_softl; i++){
    d_area[i] = (double*)malloc(amosa->i_no_offunc*sizeof(double));
  }

  for(i=0; i<amosa->i_softl; i++){

    evaluate(amosa->d_solution[i],amosa);

    for(j=0; j<amosa->i_no_offunc; j++){
      d_area[i][j] = amosa->d_eval[j];
    }
    
    i_flag[i] = 1;
  }

  for(j=0; j<amosa->i_softl-1; j++){

    if(i_flag[j] == 1){

      for(i=j+1; i<amosa->i_softl && i_flag[j]==1; i++){

        if(i_flag[i] == 1){

          count=0;
          count1=0;
          for(h=0; h<amosa->i_no_offunc; h++){
            if(d_area[j][h]>=d_area[i][h]){
              count++;
            } else if(d_area[j][h]<=d_area[i][h]){
              count1++;
            }
          }  //end of 4th inner for loop
          if(count==amosa->i_no_offunc){
            i_flag[j]=0;
          } else if(count1==amosa->i_no_offunc){
            i_flag[i]=0;
          }

        }
      }
    }
  }

  // FIX: iterate to i_softl-1
  for(i=0; i<amosa->i_softl-1; i++){
    if(i_flag[i] == 1){

      for(h=0; h<amosa->i_totalno_var; h++){
        amosa->d_archive[g][h]=amosa->d_solution[i][h];
      }

      for(h=0; h<amosa->i_no_offunc; h++){
        amosa->d_func_archive[g][h]=d_area[i][h];
      }

      g++;
    }
  }

  amosa->i_archivesize=g;
  // end generating archive

  // free allocated memory
  free(i_flag);
  for(i=0; i<amosa->i_softl; i++){
    free(d_area[i]);
  }
  free(d_area);
};
