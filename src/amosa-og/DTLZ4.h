#include<math.h>

void DTLZ4(double *s)
 {
   int i;
   int mul;
  double f1;
  double f2;
  double g;
  double f3;
  double sum;


  g=0;
  
  for(i=2;i<12;i++)
  {
    g=g+pow((s[i]-0.5),2);
   } 
    
  f1 = (1+g)*cos(PI*pow(s[0],100)*0.5)*cos(PI*pow(s[1],100)*0.5);
  f2 = (1+g)*cos(PI*pow(s[0],100)*0.5)*sin(PI*pow(s[1],100)*0.5);
  f3=(1+g)*sin(0.5*pow(s[0],100)*PI);
  d_eval[0]=f1;
  d_eval[1]=f2;
  d_eval[2]=f3;
  return ;
 }  
