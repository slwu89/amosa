

void ZDT1(double *s)
 {
   int i;
   double sum = 0;
   double f1, f2, g, h;
   f1 = s[0];
   for (i = 1; i < i_totalno_var ; i++)
	sum += s[i];
   g = 1 + (9*sum)/29.0;
   h = 1 - sqrt(f1/g);
   f2 = g*h;
   d_eval[0]=f1;
   d_eval[1]=f2;
   return ;
 }
