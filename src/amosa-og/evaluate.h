/*This function calls different evaluation functions */

#include <stdlib.h>
#include<stdio.h>

void evaluate(double *s)
   {  
  	if (!strcmp(c_problem, "ZDT1"))
    		ZDT1(s);    // this is a function described in 
                	   // Diss. ETH No. 13398 (Eckart Zitzler's PhD Thesis) 
                          // available from http://www.tik.ee.ethz.ch/~zitzler/
    	else if(!strcmp(c_problem,"ZDT2"))
	        ZDT2(s);
    	else if(!strcmp(c_problem,"ZDT3"))
   		ZDT3(s);
    	else if(!strcmp(c_problem,"ZDT6"))
   		ZDT6(s);
    	else if(!strcmp(c_problem,"SCH1"))
   		SCH1(s);
    	else if(!strcmp(c_problem,"SCH2"))
   		SCH2(s);
    	else if(!strcmp(c_problem,"Dev1"))
    		Dev1(s);
    	else if(!strcmp(c_problem,"Dev2")) 
    		Dev2(s);
    	else if(!strcmp(c_problem,"Dev3")) 
    		Dev3(s);
    	else if(!strcmp(c_problem,"Dev4")) 
    		Dev4(s);
    	else if(!strcmp(c_problem,"DTLZ1"))
    		DTLZ1(s);
    	else if(!strcmp(c_problem,"DTLZ2"))
    		DTLZ2(s);
    	else if(!strcmp(c_problem,"DTLZ3"))
    		DTLZ3(s);
    	else if(!strcmp(c_problem,"DTLZ4"))
    		DTLZ4(s);
    	else if(!strcmp(c_problem,"DTLZ24"))
    		DTLZ24(s);
    	else if(!strcmp(c_problem,"DTLZ5"))
    		DTLZ5(s);
    	else if(!strcmp(c_problem,"DTLZ7"))
    		DTLZ7(s);
    	else if (!strcmp(c_problem,"DTLZ15"))
     		DTLZ15(s);
     	else if (!strcmp(c_problem,"DTLZ110"))
     		DTLZ110(s);
     	else if (!strcmp(c_problem,"DTLZ115"))
     		DTLZ115(s);
     	else
    		{
      		printf("Invalid argument for test c_problem given. Exiting.\n");
      		exit(-1);
      		}
    
   }
