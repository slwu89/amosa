/*This function finds the number of functions in each of the c_problem functions*/

#include <stdlib.h>

int number_of_functions()
     {
	int value;

   	if (!strcmp(c_problem, "ZDT1"))
    		value=2;
    	else if(!strcmp(c_problem,"ZDT2"))
   		value=2;
  	else if(!strcmp(c_problem,"ZDT3"))
 		value=2;
    	else if(!strcmp(c_problem,"ZDT6"))
   		value=2;
    	else if(!strcmp(c_problem,"SCH1"))
   		value=2;
    	else if(!strcmp(c_problem,"SCH2"))
   		value=2;
    	else if(!strcmp(c_problem,"Dev1"))
    		value=2;
    	else if(!strcmp(c_problem,"Dev2")) 
    		value=2;
    	else if(!strcmp(c_problem,"Dev3")) 
    		value=2;
    	else if(!strcmp(c_problem,"Dev4")) 
    		value=2;
    	else if(!strcmp(c_problem,"DTLZ1"))
    		value=3;
    	else if(!strcmp(c_problem,"DTLZ2"))
    		value=3;
    	else if(!strcmp(c_problem,"DTLZ3"))
    		value=3;
    	else if(!strcmp(c_problem,"DTLZ4"))
    		value=3;
    	else if(!strcmp(c_problem,"DTLZ24"))
    		value=4;
    	else if(!strcmp(c_problem,"DTLZ5"))
    		value=3;
    	else if(!strcmp(c_problem,"DTLZ7"))
    		value=3;
    	else if (!strcmp(c_problem,"DTLZ15"))
     		value=5;
     	else if (!strcmp(c_problem,"DTLZ110"))
     		value=10;
     	else if (!strcmp(c_problem,"DTLZ115"))
     		value=15;
     	else
    		{
      		printf("Invalid argument for test c_problem given. Exiting.\n");
      		exit(-1);
        	}
     return value;         
     }	
