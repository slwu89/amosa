#include <math.h>
#include <stdlib.h>


void DTLZ24(double *s)
 {
   int i, j;
   int mul;
   double *var=(double *)malloc(sizeof(double)*i_totalno_var);

  
  double f1, f2, g, h,f3,f4;

 //set paramaters to zero
  for (i = 0; i < i_totalno_var; i++)
    var[i] = s[i];

 
  g=0;
  for(i=3;i<13;i++)
    g=g+pow((var[i]-0.5),2);
     
  f1 = (1+g)*cos(PI*var[0]*0.5)*cos(PI*var[1]*0.5)*cos(PI*var[2]*0.5);
  f2 = (1+g)*cos(PI*var[0]*0.5)*cos(PI*var[1]*0.5)*sin(PI*var[2]*0.5);
  f3=(1+g)*cos(PI*var[0]*0.5)*sin(PI*var[1]*0.5);
  f4=(1+g)*sin(0.5*var[0]*PI);
  d_eval[0]=f1;
  d_eval[1]=f2;
  d_eval[2]=f3;
  d_eval[3]=f4;
  return ;
 } 
