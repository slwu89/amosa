/* --------------------------------------------------------------------------------
#
#   The main AMOSA process
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */


#include "amosa-algorithm.h"

#include "amosa-mutate.h"
#include "amosa-evaluate.h"
#include "amosa-cluster.h"
#include "amosa-dominance.h"


/* --------------------------------------------------------------------------------
#   main AMOSA process
-------------------------------------------------------------------------------- */

void RunAMOSA(AMOSAType *amosa){

  // Variable declaration
  int    r;
  int    i;
  int    j;
  int    h;
  int    k;
  int    l;
  int    flag;
  int    pos;
  int    f;
  int    n;
  int    m;
  int    p1;
  int    p2;
  double ran2;
  double p;
  double deldom;
  double amount;
  // float  ran1;
  int    count;
  int    duplicate;
  int    count1;
  int    count2;
  double **archive1;
  int    isdom;
  double *current;
  double *newsol;
  double t;
  double*func_new;
  double *func_current;
  double **area2;

  // memory allocation
  p2 = amosa->i_softl+3;
  p1 = amosa->i_archivesize-1;

  duplicate = 0;

  area2 = (double**) malloc(sizeof(double *)*(p2));
  for(i=0;i<(p2);i++){
    area2[i] = (double *)malloc(amosa->i_no_offunc*sizeof(double));
  }

  archive1 = (double**) malloc(sizeof(double *)*(p2-1));
  for(i=0;i<(p2-1);i++){
    archive1[i] = (double *)malloc(amosa->i_totalno_var*sizeof(double));
  }

  current = (double*) malloc(sizeof(double)*amosa->i_totalno_var);
  newsol = (double*) malloc(sizeof(double)*amosa->i_totalno_var);

  func_new = (double*) malloc(amosa->i_no_offunc*sizeof(double));
  func_current = (double*) malloc(amosa->i_no_offunc*sizeof(double));

  if(p1 > 0){
    r = (int)floor(runif(0.,p1));
  } else {
    r = 0;
  }

  for(i=0;i<amosa->i_totalno_var;i++){
    current[i] = amosa->d_archive[r][i];
  }

  flag = 1;
  pos = r;

  for(i=0;i<amosa->i_no_offunc;i++){
    func_current[i]=amosa->d_func_archive[r][i];
  }

  // MAIN LOOP
  if(amosa->verbose){
    Rprintf(" --- BEGIN AMOSA ALGORITHM --- \n");
  }
  int iter = 0;
  for(t=amosa->d_tmax;t>=amosa->d_tmin;t=t*amosa->d_alpha){
    iter++;
    if(amosa->verbose){
      Rprintf(" *** iteration %d, current temperature: %f *** \n",iter,t);
    }

  for(j=1;j<=amosa->i_no_ofiter;j++){

    if(amosa->verbose){
      Rprintf(" *** inner iteration: %d ***\n",j);
    }

    duplicate = 0;

    for(h=0;h<amosa->i_totalno_var;h++){
          newsol[h] = current[h];
	  }

    real_mutate_ind(newsol, amosa);
    evaluate(newsol, amosa);

    for(h=0;h<amosa->i_no_offunc;h++){
      func_new[h] = amosa->d_eval[h];
    }

    count2 = 0;
    count1 = 0;

    for(h=0;h<amosa->i_no_offunc;h++){
      if(func_current[h]<=func_new[h]){
        count1++;
      }
      if(func_new[h]<=func_current[h]){
        count2++;
      }
    }

    // Case1:if current dominates new
    if(count1==amosa->i_no_offunc){

      if(amosa->verbose){
        Rprintf(" *** current solution dominates new solution ***\n",j);
      }

      deldom = 0.0;
      amount = find_unsign_dom(func_current,func_new, amosa);

      deldom = deldom + amount;

      for(i=0;i<amosa->i_archivesize;i++){
        count = 1;
        if(flag==0 || i!=r){
          isdom = is_dominated(amosa->d_func_archive[i],func_new, amosa);

          if(isdom==1){
            count = count + 1;
            amount = find_unsign_dom(amosa->d_func_archive[i],func_new, amosa);
            deldom = deldom + amount;
          }
        }
      }

      // The probability of Case 1
      p= 1./(1.+exp(deldom/(t)));

      ran2 = unif_rand();

      if(p >= ran2){
        for(f=0;f<amosa->i_totalno_var;f++){
          current[f]=newsol[f];
        }
        for(h=0;h<amosa->i_no_offunc;h++){
          func_current[h]=func_new[h];
        }
        flag = 0;
      }
      // End of Case1
    } else if(count2==amosa->i_no_offunc) {

      //Case 3: if new sol dominates the current solution
      k=0;
      count=0;
      deldom=1000000;

      if(amosa->verbose){
        Rprintf(" *** new solution dominates current solution ***\n",j);
      }

      for(i=0;i<amosa->i_archivesize;i++){
        isdom = is_dominated(amosa->d_func_archive[i],func_new, amosa);
        if(isdom==1){
          count=count+1;
          amount=find_unsign_dom(amosa->d_func_archive[i],func_new, amosa);
          if(amount<deldom){
           deldom=amount;
           k=i;
          }
        }
      }

      // Case3(a):If new point is dominated by k(k>=1) solutions in the archive
      if(count>0){

        // The probability of case 3(a)
        p=1.0/(1.0+exp(-deldom));
        ran2 = unif_rand();

        //Case3(a)1:Set point of the archive corresponds to deldom as current point with probability=p
        if(p>=ran2){

          for(h=0;h<amosa->i_totalno_var;h++){
            current[h]=amosa->d_archive[k][h];
      		}

          for(h=0;h<amosa->i_no_offunc;h++){
            func_current[h]=amosa->d_func_archive[k][h];
       		}

          flag=1;
          pos=k;

          //End of case3(a)1:
        } else {
          //Case3(a)2: Set new point as current point
          for(f=0;f<amosa->i_totalno_var;f++){
            current[f]=newsol[f];
          }
          for(h=0;h<amosa->i_no_offunc;h++){
            func_current[h]=func_new[h];
          }
          flag=0;

          //End of case3(a)2:
        }

        //End of case3(a):
      } else if(count==0 && duplicate==0){  /* no sol in archive dominates current*/
        // Case3(b): New point is non-dominating with respect to the point in the archive

         /* if current resides in archivehieve then remove that point */
        if(flag==1){

          for(i=pos;i<amosa->i_archivesize-1;i++){
            for(h=0;h<amosa->i_no_offunc;h++){
              amosa->d_func_archive[i][h]=amosa->d_func_archive[i+1][h];
            }
            for(h=0;h<amosa->i_totalno_var;h++){
              amosa->d_archive[i][h]=amosa->d_archive[i+1][h];
            }
          }

          amosa->i_archivesize=amosa->i_archivesize-1;
        }

        for(i=0;i<amosa->i_archivesize;i++){
          for(h=0;h<amosa->i_no_offunc;h++){
            area2[i][h]=amosa->d_func_archive[i][h];
          }
          for(h=0;h<amosa->i_totalno_var;h++){
            archive1[i][h]=amosa->d_archive[i][h];
          }
        }

        /* if newsol dominates some other sols in archivehieve then remove all those*/
        k=0;
        h=0;

        for(i=0;i<amosa->i_archivesize;i++){
          isdom=is_dominated(func_new,area2[i], amosa);
          if(isdom==1){
            k++;
          } else {

            for(n=0;n<amosa->i_no_offunc;n++){
              amosa->d_func_archive[h][n]=area2[i][n];
            }

            for(n=0;n<amosa->i_totalno_var;n++){
              amosa->d_archive[h][n]=archive1[i][n];
            }
            h++;
          }
        }

        if(k>0){
          amosa->i_archivesize=h;
        }

        amosa->i_archivesize++;

        m = amosa->i_archivesize-1;

        for(l=0;l<amosa->i_totalno_var;l++){
          amosa->d_archive[m][l]=newsol[l];
        }
        for(l=0;l<amosa->i_no_offunc;l++){
          amosa->d_func_archive[m][l]=func_new[l];
        }

        /* If archive size exceeds soft limit then clustering is needed*/
        if(amosa->i_archivesize>amosa->i_softl){
          clustering(amosa);
        }

        for(f=0;f<amosa->i_totalno_var;f++){
          current[f]=newsol[f];
        }

        for(f=0;f<amosa->i_no_offunc;f++){
          func_current[f]=func_new[f];
        }

        flag = 1;
        pos = m;
        // End of case3(b)
      }

      //End of case3
    } else {
      //Case 2: Current point and new point are non-dominating to each-other

      if(amosa->verbose){
        Rprintf(" *** current solution and new solution are nondominating to each other ***\n",j);
      }

      count=0;
      deldom=0.0;

      for(i=0;i<amosa->i_archivesize;i++){

        /* count total no of solution that dominates new sol*/
        isdom=is_dominated(amosa->d_func_archive[i],func_new, amosa);
        if(isdom==1){
          count= count+1;
          amount=find_unsign_dom(amosa->d_func_archive[i],func_new, amosa);
          deldom=deldom+amount;
        }
      }

      //Case 2(a): New point is dominated by k(k>=1) point in the archive
      if(count>0){

        // The probability of case 2(a)
        p=1.0/(1.0+exp(deldom/(t)));
        ran2=unif_rand();

        if(p>=ran2){
          for(f=0;f<amosa->i_totalno_var;f++){
            current[f]=newsol[f];
          }
          for(f=0;f<amosa->i_no_offunc;f++){
            func_current[f]=func_new[f];
          }
          flag=0;
        }
        // End of case 2(a):
      } else if(count==0 ){

        // Case 2(b):New point is non-dominating with respect to all the points in the archive

        for(i=0;i<amosa->i_archivesize;i++){
          for(h=0;h<amosa->i_no_offunc;h++){
            area2[i][h]=amosa->d_func_archive[i][h];
          }
          for(h=0;h<amosa->i_totalno_var;h++){
            archive1[i][h]=amosa->d_archive[i][h];
          }
        }

        k=0;
        h=0;

        for(i=0;i<amosa->i_archivesize;i++){
          isdom=is_dominated(func_new,area2[i], amosa);
          if(isdom==1){
            k++;
          } else {
            for(n=0;n<amosa->i_no_offunc;n++){
              amosa->d_func_archive[h][n]=area2[i][n];
            }
            for(n=0;n<amosa->i_totalno_var;n++){
              amosa->d_archive[h][n]=archive1[i][n];
            }
            h++;
          }
        }

        if(k>0){
          amosa->i_archivesize=h;
        }

        amosa->i_archivesize++;
        m=amosa->i_archivesize-1;

        for(l=0;l<amosa->i_totalno_var;l++){
          amosa->d_archive[m][l]=newsol[l];
        }
        for(l=0;l<amosa->i_no_offunc;l++){
          amosa->d_func_archive[m][l]=func_new[l];
        }

        if(amosa->verbose){
          Rprintf(" *** amosa->i_archivesize is: %d ***\n",amosa->i_archivesize);
        }

        // If amosa->i_archivesize increases from soft limit clustering is required
        if(amosa->i_archivesize>amosa->i_softl){
          clustering(amosa);
          if(amosa->verbose){
            Rprintf(" *** finish clustering, new archive size, amosa->i_archivesize is: %d ***\n",amosa->i_archivesize);
          }
        }

        for(f=0;f<amosa->i_totalno_var;f++){
          current[f]=newsol[f];
        }
        for(f=0;f<amosa->i_no_offunc;f++){
          func_current[f]=func_new[f];
        }

        flag=1;
        pos=m;
        // End of case 2(b):
      }
      // End of case 2:
    }

    // End of for loop :for(i=0;i<amosa->i_no_ofiter;i++)
  }

  // End of for loop :for(temp=amosa->d_tmax,;temp>amosa->d_tmin;temp*=amosa->d_alpha)
  }

  // free memory
  for(i=0;i<(p2);i++){
    free(area2[i]);
  }
  free(area2);

  for(i=0;i<(p2-1);i++){
    free(archive1[i]);
  }
  free(archive1);

  free(current);
  free(newsol);

  free(func_new);
  free(func_current);

}
