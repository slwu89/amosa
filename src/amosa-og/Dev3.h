#include<math.h>

void Dev3(double *s)
{
  
  int i;
  double *var;
  double sum = 0;
  double f1; 
  double f2;
  double g;
  double h;
  double alpha;

 f1 =4*s[0];
 if(var[1]<0.4)
   {
    g=4-3*exp(pow((-(s[1]-0.2)/0.02),2));
   }
  else 
   {
    g=4-2*exp(pow((-(s[1]-0.7)/0.2),2));
   }
  alpha=0.25+3.75*(g-1)/(2-1);
  if(f1<=g) 
  h=1-pow((f1/g),alpha);
  else h=0;
  f2=g*h;
  d_eval[0]=f1;
  d_eval[1]=f2;
  return;

}
