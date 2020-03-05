#include<math.h>

void Dev1(double *s)
 {
     double func2,func1;
     func1=s[0];
     func2=2.0-exp(-pow(((s[1]-0.2)/0.004),2))-0.8*exp(-pow(((s[1]-0.6)/0.4),2));
     func2=func2/s[0];
     d_eval[0]=func1;
     d_eval[1]=func2;
     return;
   }  
 
     
