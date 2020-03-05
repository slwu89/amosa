
void SCH2(double *s)
 {
   double value;
   double func1,func2;
   value=s[0];
   if (value <= 1.0)
        func1 = -value;
   else if ((value>1.0)&&(value<=3.0))
       func1 = -2.0+value;
   else if ((value>3.0)&&(value<=4.0))
        func1 = 4.0-value;
   else
        func1 = -4.0+value;
   func2= (value-5.0)*(value-5.0);
   d_eval[0]=func1;
   d_eval[1]=func2;
   return;
 }  
