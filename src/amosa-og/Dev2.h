#include<malloc.h>

void Dev2(double *s)
{
  int i;
  int total_sub=4;
  int *length;
  int j;
  int *val;
  int count=0;
  int *fung;
  int sum;
  double f1;
  double f2;
  length=(int *)malloc(total_sub*sizeof(int));
  length[0]=10;
  length[1]=5;
  length[2]=5;
  length[3]=5;
  val=(int *)malloc(total_sub*sizeof(int));
  fung=(int *)malloc((total_sub-1)*sizeof(int));
  for(i=0;i<total_sub;i++)
   {
    val[i]=0;
   }
  for(i=0;i<(total_sub-1);i++)
   {
    fung[i]=0;
   }
  for(i=0;i<total_sub;i++)
   {
    if(i!=0)
     { 
       sum=0;
       for(j=0;j<i;j++)
        {
          sum=sum+length[j];
         }
      }
     else sum=0;
     for(j=0;j<length[i];j++)
      {
       if(s[sum+j]==1) 
	val[i]++;
      }
   }
  sum=0;
  for(i=1;i<total_sub;i++)
   {
     if(val[i]<length[i])
       {
         fung[i-1]=2+val[i];
       }
     else if(val[i]=length[i])
            fung[i-1]=1;
     sum=sum+fung[i-1];
   }
  f1=1+val[0];
  f2=(sum/f1);
  d_eval[0]=f1;
  d_eval[1]=f2;
  return;
  
 }   
