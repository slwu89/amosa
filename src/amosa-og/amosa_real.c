/*	AMOSA: archived Multi Objective Simulated Annealing 		*/




//Declaring Pre Defined Header Filuntitled folderes Of C Compiler.

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>

//Declaring Constants.

#define PI 3.1415927
#define TRUE 1
#define FALSE 0

//Declaring Global Variables.

int i_hardl,          /* Hardlimit of the archive */
    i_softl,	      /* Softlimit of the archive */
    i_no_ofiter,       /*Number of iteration per temperature */
    i_hillclimb_no,    /*Total number of hill_climbing number */
    i_maxno_bit,       /*maximum number of bits used to encode one variable */
    i_arrsize, 	      /*Total length of each string */
    i_totalno_var,     /*Total number of variable of the functions */
    i_archivesize,     /*Stores the archive size*/
    i_no_offunc;       /*Number of function */


long seed; 	      /*seed for random number generation */


char c_problem[50];  /*function name to be optimized */


double d_tmax=100,             /*maximum temperature */
       d_tmin,             /*minimum temperature*/
       d_alpha,            /*cooling rate*/
       **d_solution,       /*data structure corresponding to binary strings*/
       **d_archive,        /*archive */
       **d_func_archive,   /*variable to store the functional values of the archive solutions */
       *d_eval,		   /**/
       *d_func_range,      /*range of the functions */
       *d_min_real_var,    /*Store minimum value of the real variables*/
       *d_max_real_var;    /*Store maximum value of the real variables*/

//Declaring User Defined Header Files.

#include "ZDT1.h"
#include "ZDT2.h"
#include "ZDT3.h"
#include "ZDT6.h"
#include "SCH1.h"
#include "SCH2.h"
#include "Dev1.h"
#include "Dev2.h"
#include "Dev3.h"
#include "Dev4.h"
#include "DTLZ1.h"
#include "DTLZ2.h"
#include "DTLZ3.h"
#include "DTLZ4.h"
#include "DTLZ5.h"
#include "DTLZ7.h"
#include "DTLZ24.h"
#include "DTLZ15.h"
#include "DTLZ110.h"
#include "DTLZ115.h"

#include "number_of_variable.h"
#include "evaluate.h"
#include "number_of_functions.h"
#include "clustering.h"
#include "real_mutate_ind.h"
#include "init_sol.h"
#include "dominance.h" 
#include "main_process.h"
#include "creating_archive.h"
#include "burn_in_period.h" 



//If want to include some new function include its declaration here , call it from evaluate() and write its definition in the code*/

int main(int argc,char *argv[])
     {
	int i;
	time_t t1,t2;
	(void)time(&t1); /*time() gives the current time, in seconds, elapsed since 00:00:00 GMT, January
1, 1970. It stores that value in the location *t1, provided that t1 is
not a null pointer.*/
	if(argc!=2)	/*Checks whether the command given to run the program is wrong or not*/
	     {
	     printf("\n Wrong Usages");
	     printf("\n It should be ./amosa problem\n \n");
	     exit(1);
	     }
	sprintf(c_problem, "%s", argv[1]);
	printf("\n %s",c_problem);
	i_no_offunc=number_of_functions();
	printf("\nNumber of functions in %s is %d",c_problem,i_no_offunc);
	printf("\n Give me the values of Hard-limit and Soft-limit");
       	scanf("%d %d",&i_hardl,&i_softl);
       	printf("\n softl=%d",i_softl);
       	i_no_ofiter=500;  	/*number of iterations per temperature i sset to 100*/
       	d_tmin=0.0000025;		/*the minimum temperature is set to 0.0000025*/
       	d_func_range=(double *)malloc(i_no_offunc*sizeof(double));	    /*dynamically allocating memory to store the functional values of the archive solutions */
       	for(i=0;i<i_no_offunc;i++)
             {
	     printf("\n Enter range of %d th function",(i+1));
	     scanf("%lf",&d_func_range[i]);
	     }  
        printf("\n Enter the value of cooling rate");
       	scanf("%lf",&d_alpha);
	i_totalno_var=number_of_variable();       	
	printf("\n Total number of variables in %s is %d",c_problem,i_totalno_var);
	seed=67644288;
	srand(seed);
        i_hillclimb_no=20; 	/*setting hill climd number to 10*/
       	d_solution=(double **)malloc(i_softl*sizeof(double *));  /*memory allocation for storing solution in a variable named solution.*/
       	for(i=0;i<i_softl;i++)
	   d_solution[i]=(double *)malloc(i_totalno_var*sizeof(double));
       	d_archive=(double **)malloc((i_softl+3)*sizeof(double *)); /*memory allocation for archive */ 
       	for(i=0;i<(i_softl+3);i++)
             d_archive[i]=(double *)malloc(i_totalno_var*sizeof(double));
        d_min_real_var=(double *)malloc(i_totalno_var*sizeof(double));/*memory allocation to store the minimum value of real variables in the functions*/
       	if(d_min_real_var==NULL)	
             {	/*if there is any allocation error then report it and exit*/
             printf("\n Error in allocation");
	     exit(1);
	     }
	d_max_real_var=(double *)malloc(i_totalno_var*sizeof(double));/*memory allocation to store the maximum value of real variables in the functions*/
	if(d_max_real_var==NULL)
	     {/*if there is any allocation error then report it and exit*/
	     printf("\n Error in allocation");
	     exit(1);
	     }
	for(i=0;i<i_totalno_var;i++)
	     {
	     printf("\n Enter minimum value of real-variable %d\n",i);
	     scanf("%lf",&d_min_real_var[i]);
	     printf("\n Enter maximum value of real-variable %d\n",i);
	     scanf("%lf",&d_max_real_var[i]);
	   // d_min_real_var[i]=0;
	    //d_max_real_var[i]=1;
	     }  	   
       	d_func_archive=(double **) malloc((i_softl+3)*sizeof(double *));/*allocating memory for func_archive*/
      	for(i=0;i<(i_softl+3);i++)
            d_func_archive[i]=(double *)malloc(i_no_offunc*sizeof(double));
       	d_eval=(double *)malloc(i_no_offunc*sizeof(double));
	initialize_sol(); /*Initializing the archive by calling this function */
       	creating_archive();  /*Creation the archive*/
//	burn_in_period();   /* Computing maximum temperature(declared as d_tmax) using burn in period */
	
       	mainprocess();	/*calling mainprocess() which runs the main algorithm proposed in AMOSA*/
	(void)time(&t2);    /*time() gives the current time, in seconds, elapsed since 00:00:00 GMT, January
1, 1970. It stores that value in the location *t2, provided that t2 is
not a null pointer.*/
	printf("\n Total time needed=%d",(int)(t2-t1));      /*Displaying the time taken to run the AMOSA process*/
	printf("\n Total processor time taken by a program is=%f",(float)(clock()/CLOCKS_PER_SEC)); 	/*Displaying the number of clock ticks since program start*/
return 0;
     }
