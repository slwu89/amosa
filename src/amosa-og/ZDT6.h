#include<math.h>


void ZDT6(double *s)
{
  int i;
  double sum = 0;
  double f1, f2, g, h;

  f1 =  1-exp(-4*s[0])*pow(sin((6*22*s[0])/7),6);
  for (i = 1; i < i_totalno_var; i++)
	sum += s[i];
  g = 1 + (9*pow((sum/9),0.25));
  h = 1 - pow((f1/g),2);
  f2 = g*h;
  d_eval[0]=f1;
  d_eval[1]=f2;
  return; 
}
