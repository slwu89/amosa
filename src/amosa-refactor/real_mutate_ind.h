// Declaring Pre Defined Header Files Of C Compiler.
#include <stdlib.h>
#include <math.h>

#include "amosa.h"

/* Function performimg mutation on individual string */

void real_mutate_ind(double *s, AMOSAType *amosaParams)
{

// variable declaration
//------------------------------------------------------------------------------------------------------
	int i, j ;
	int i_count ;
	int i_rnd1 ;
	double d_rnd ;
	double d_rnd2 ;
	double b ;
	double y ;
	double d_rand_lap ;
//--------------------------------------------------------------------------------------------------------


// Body of the real_mutate_ind function

//---------------------------------------------------------------------------------------------------------

	d_rnd2=(rand()%amosaParams->i_totalno_var);
	i_rnd1=(int) d_rnd2;
	y = s[i_rnd1];

        /* if(y==0.0)
      {
        for(i=0;i<amosaParams->i_totalno_var;i++)
                 printf("\n s[%d]=%lf",i,s[i]);
           // getchar();
        }  //end of if loop
*/
        b=0.25;
        d_rnd=(rand()/(RAND_MAX+1.0));

        while(d_rnd==0)
        	d_rnd=(rand()/(RAND_MAX+1.0));
        d_rnd=d_rnd-0.5;


        if(d_rnd<0)
        	d_rand_lap= b * log(1-2*fabs(d_rnd));
        else
        	d_rand_lap= -b * log(1-2*fabs(d_rnd));

        y=y+d_rand_lap;
        i_count=0;

        while ((y<amosaParams->d_min_real_var[i_rnd1] || y>amosaParams->d_max_real_var[i_rnd1]) && (i_count<20))
        {
        	y = s[i_rnd1];
        	d_rnd=(rand()/(RAND_MAX+1.0));

        	while(d_rnd==0)
        		d_rnd=(rand()/(RAND_MAX+1.0));

        	d_rnd=d_rnd-0.5;

        	if(d_rnd<0)
        		d_rand_lap=b*log(1-2*fabs(d_rnd));
        	else
        		d_rand_lap= -b*log(1-2*fabs(d_rnd));
        	y=y+d_rand_lap;
        	i_count++;
           }  //end of while loop
           s[i_rnd1]=y;
           if(i_count==20)
           {
           	if (s[i_rnd1]<amosaParams->d_min_real_var[i_rnd1])
           		s[i_rnd1]=amosaParams->d_min_real_var[i_rnd1];
           	else if (s[i_rnd1]>amosaParams->d_max_real_var[i_rnd1])
           		s[i_rnd1]=amosaParams->d_max_real_var[i_rnd1];
        }  //end of if loop


        return;
    }


//------------------------------------------------------------------------------------------------------------------------
   // End of real_mutate_ind function
//---------------------------------------------------------------------------------------------------------------------
