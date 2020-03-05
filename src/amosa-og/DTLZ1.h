#include<math.h>
#include<malloc.h>

void DTLZ1(double *s)
 {
   int i;
   int k;
   int mul;
   double *var=(double *)malloc(sizeof(double)*i_totalno_var);

  double sum = 0;
 
  double g;
 

 //set paramaters to zero
  for (i = 0; i <i_totalno_var ; i++)
    var[i] = s[i];
  
      for(k=2;k<i_totalno_var;k++)
        {
	  sum=sum+pow((var[k]-0.5),2)-cos(20*PI*(var[k]-0.5));
	}
      g=100*(5+sum);
      d_eval[0]=0.5*var[0]*var[1]*(1+g);
      d_eval[1]=0.5*var[0]*(1-var[1])*(1+g);
      d_eval[2]=0.5*(1-var[0])*(1+g);	 
 
  return ;
 } 
