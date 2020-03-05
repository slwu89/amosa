//Declaring User Defined Header Files.


/*The following function initializes the softl number of solutions*/
   void initialize_sol()
    {

// variable declaration
//------------------------------------------------------------------------------------------------------
	FILE *fp;      
      int i,j,f,ii;
      int i_count;
      double *d_xnew;
      double *d_area1,*d_area2;
      d_area1=(double *)malloc(i_no_offunc*sizeof(double));
      d_area2=(double *)malloc(i_no_offunc*sizeof(double));

//--------------------------------------------------------------------------------------------------------
        

// Body of the intialize_sol function	

//---------------------------------------------------------------------------------------------------------
      /*Randomly initializing softl number of solutions */
      for(i=0;i<i_softl;i++)	//???????????????????????????????????????????????//
        {
	    for(j=0;j<i_totalno_var;j++)
	      {
		d_solution[i][j]=(rand()/(RAND_MAX+1.0))*(d_max_real_var[j]-d_min_real_var[j])+d_min_real_var[j]; 
		printf("\n after initialization-->> %lf",d_solution[i][j]);
	//getchar();


		}  //end of inner for loop
	     
	  }   //end of outer for loop	  
      printf("\n IN Initialize "); 
      d_xnew=(double *) malloc(i_totalno_var *sizeof(double));  

      /* Performing some hill-climbing operation on solutions of the archive */  
      for(ii=0;ii<i_softl;ii++)
       {
         for(j=0;j<i_hillclimb_no;j++)
          {
             evaluate(d_solution[ii]);     /*This function calls different evaluation functions */

             for(i=0;i<i_no_offunc;i++)
                 d_area1[i]=d_eval[i];
                
             for(f=0;f<i_totalno_var;f++)
                 d_xnew[f]=d_solution[ii][f];
                
	     real_mutate_ind(d_xnew);  	 /*Function performimg mutation on individual string */
             evaluate(d_xnew);          /*This function calls different evaluation functions */
             for(i=0;i<i_no_offunc;i++)
                 d_area2[i]=d_eval[i];
                
             i_count=0;
             for(i=0;i<i_no_offunc;i++)
               {
                  if(d_area1[i]>=d_area2[i])
                    i_count++;
                }  //end of 2nd inner for loop
             if(i_count==i_no_offunc)
               {
                   for(f=0;f<i_totalno_var;f++)
                      d_solution[ii][f]=d_xnew[f]; 
                }  //end of 2nd inner if loop
           }  //end of inner for loop
        }   //end of outer for loop
      printf("\n At the end of initialize solution\n\n");
     
    }

//------------------------------------------------------------------------------------------------------------------------
    // End of initialie_sol function
//---------------------------------------------------------------------------------------------------------------------
