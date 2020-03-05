#include<math.h>


void ZDT3(double *s)
 {
  int i, j;
  int mul;
  double sum = 0;
  double f1, f2, g, h;
  f1 = s[0];
  for (i = 1; i < i_totalno_var; i++)
	sum += s[i];
  g = 1 + (9*sum)/29.0;
  h = 1 - sqrt(f1/g)-(f1/g)*(sin(10*3.14*f1));
  f2 = g*h;
  d_eval[0]=f1;
  d_eval[1]=f2;
  return;
} 
