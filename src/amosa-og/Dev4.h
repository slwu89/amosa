#include<math.h>

void Dev4(double *s)
{
  
  int i;
  double sum = 0;
  double f1;
  double f2;
  double g;
  double h;

  f1 =s[0];
  g=1+10*s[1];
  h=1-pow((f1/g),2)-(f1/g)*sin(2*3.14*4*f1);
  f2=g*h;
  d_eval[0]=f1;
  d_eval[1]=f2;
  return;

}
