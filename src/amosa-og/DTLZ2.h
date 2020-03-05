#include<malloc.h>
#include<math.h>

 void DTLZ2(double *s)
 {
   int i;
   double *var=(double *)malloc(sizeof(double)*i_totalno_var);

  
  double f1;
  double f2;
  double g;
  double f3;

 //set paramaters to zero
  for (i = 0; i < i_totalno_var; i++)
    var[i] = s[i];
  g=0;
  for(i=2;i<12;i++)
    g=g+pow((var[i]-0.5),2);
     
  f1 = (1+g)*cos(PI*var[0]*0.5)*cos(PI*var[1]*0.5);
  f2 = (1+g)*cos(PI*var[0]*0.5)*sin(PI*var[1]*0.5);
  f3=(1+g)*sin(0.5*var[0]*PI);
  d_eval[0]=f1;
  d_eval[1]=f2;
  d_eval[2]=f3;
  return ;
 } 
 
