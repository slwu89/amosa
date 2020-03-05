#include<math.h>

void DTLZ3(double *s)
 {
   int i;
   int mul;
   double f1;
   double f2;
   double g;
   double f3;
   

    
  for(i=2;i<12;i++)
  {
    g=g+pow((s[i]-0.5),2)-cos(20*PI*(s[i]-0.5));
   } 
  g=100*(10+g);    

  f1 = (1+g)*cos(PI*s[0]*0.5)*cos(PI*s[1]*0.5);
  f2 = (1+g)*cos(PI*s[0]*0.5)*sin(PI*s[1]*0.5);
  f3=(1+g)*sin(0.5*s[0]*PI);
  d_eval[0]=f1;
  d_eval[1]=f2;
  d_eval[2]=f3;
  for(i=0;i<i_no_offunc;i++)
    {
     if(d_eval[i]<0)
     {
       printf("\n d_eval=%lf",d_eval[i]);
       getchar();
      } 
    } 
  return ;
 } 
