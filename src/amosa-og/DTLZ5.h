#include <math.h>
#include <stdlib.h>


void DTLZ5(double *s)
 {
   int i;
   int mul;
   double *var=(double *)malloc(sizeof(double)*i_totalno_var);
   double *theta=(double *)malloc(i_totalno_var*sizeof(double));
  
  double f1, f2, g, h,f3;

  //set paramaters to zero
  for (i = 0; i < i_totalno_var; i++)
   {
    var[i] = s[i];
    theta[i]=0;
    }

  
  g=0;
  for(i=2;i<12;i++)
    g=g+pow((var[i]-0.5),2);
  
  theta[1]=(PI*(1+2*g*var[1]))/(4*(1+g));
  theta[0]=var[0];
        
  f1 = (1+g)*cos(PI*theta[0]*0.5)*cos(theta[1]);
  f2 = (1+g)*cos(PI*theta[0]*0.5)*sin(theta[1]);
  f3=(1+g)*sin(0.5*theta[0]*PI);
  d_eval[0]=f1;
  d_eval[1]=f2;
  d_eval[2]=f3;
  return ;
 }  
