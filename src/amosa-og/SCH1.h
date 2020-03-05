
void SCH1(double *s)
 {
    double value;
	
	double func1,func2;
   
    value=s[0];
    func1=value*value;
    func2= (value-2.0)*(value-2.0);
    d_eval[0]=func1;
    d_eval[1]=func2;
    return;
 } 
