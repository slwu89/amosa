#include <math.h>
#include <stdlib.h>


void DTLZ15(double *s)
 {
   int i, k;
   double *var=(double *)malloc(sizeof(double)*i_totalno_var);

   double sum = 0;
   double f1, f2, g, h,f3;

   //set paramaters to zero
   for (i = 0; i < i_totalno_var; i++)
      var[i] = s[i];
   sum=0;
   for(k=4;k<9;k++)
      sum=sum+pow((var[k]-0.5),2)-cos(20*PI*(var[k]-0.5));
	
   g=100.0*(5.0+sum);
   d_eval[0]=0.5*var[0]*var[1]*var[2]*var[3]*(1+g);
   d_eval[1]=0.5*var[0]*var[1]*var[2]*(1-var[3])*(1+g);
   d_eval[2]=0.5*var[0]*var[1]*(1-var[2])*(1+g);
   d_eval[3]=0.5*var[0]*(1-var[1])*(1+g);	 
   d_eval[4]=0.5*(1-var[0])*(1+g);
   return ;
 } 
