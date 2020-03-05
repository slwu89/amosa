#include <math.h>
#include <stdlib.h>


void DTLZ7(double *s)
 {
   int i;
   double  *func,g, h,f3,sum;

   func=(double *)malloc(i_no_offunc*sizeof(double));   
 
   for(i=0;i<(i_no_offunc-1);i++)
     func[i]=s[i];
        
   sum=0;
   for(i=2;i<22;i++)
      sum=sum+s[i];
   g=(9.0*sum)/20.0;
   sum=0;
   for(i=0;i<(i_no_offunc-1);i++)
     sum=sum+ (func[i]*(1+sin(3*PI*func[i])))/(1+g);
   h=i_no_offunc-sum;  
   func[2]=(1+g)*h;
   d_eval[0]=func[0];
   d_eval[1]=func[1];
   d_eval[2]=func[2];
   return ;
 }  
