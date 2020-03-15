/* --------------------------------------------------------------------------------
#
#   single linkage clustering
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#include "amosa-cluster.h"


/* --------------------------------------------------------------------------------
#   If the size of the archive is greater than Soft Limit (SL) then the clustering process is
#   done to reduce the size of the archive to Hard Limit (HL).
#   The function clustering clusters by "Single Linkage Clustering" mechanism
-------------------------------------------------------------------------------- */

void clustering(AMOSAType* amosa){

  // local variables
  int    i;
  int    j;
  int    k;
  // int    l;
  int    h;
  int    p;
  int    g2;
  int    g;
  int    pp;
  int    u = 0;
  int    v = 0;
  int    w;
  int    m;
  double min;
  int    no_clus;
  // allocated heap memory
  double**  area2;
  int*      point1;
  int*      point2;
  double*   dist;
  double**  distance;
  int*      flag;
  int*      cluster;
  double**  archive2;

  // memory allocation
  no_clus = amosa->i_archivesize;

  cluster = (int*)malloc((amosa->i_softl+1) * sizeof(int));

  archive2 = (double**)malloc((amosa->i_softl+2) * sizeof(double*));
  for(i=0; i<(amosa->i_softl+2); i++){
    archive2[i] = (double*)malloc(amosa->i_totalno_var * sizeof(double));
  }

  area2 = (double**)malloc((amosa->i_softl+2) * sizeof(double*));
  for(i=0; i<(amosa->i_softl+2); i++){
    area2[i] = (double*)malloc(amosa->i_no_offunc * sizeof(double));
  }

  point1 = (int*)malloc((amosa->i_softl+1) * sizeof(int));
  point2 = (int*)malloc((amosa->i_softl+1) * sizeof(int));
  dist = (double *)malloc(amosa->i_softl * sizeof(double));

  distance = (double**) malloc((amosa->i_softl+1)*sizeof(double *));
  for(i=0;i<(amosa->i_softl+1);i++){
    distance[i]=(double *)malloc((amosa->i_softl+1)*sizeof(double));
  }

  flag = (int*)malloc((amosa->i_softl+1) * sizeof(int));

  k = amosa->i_archivesize;

  // begin clustering
  for(i=0; i<amosa->i_archivesize; i++){
    cluster[i]=i;
  }

  for(i=0; i<k; i++){

    distance[i][i] = 2000000.;

    for(j=i+1; j<k; j++){

      distance[i][j] = 0.0;
      for(p=0; p<amosa->i_no_offunc; p++){
        distance[i][j] += pow((amosa->d_func_archive[i][p]-amosa->d_func_archive[j][p]),2);
      }
      distance[j][i] = sqrt(distance[i][j]);
    }

  }

  while(no_clus > amosa->i_hardl){

    min = 2000000.;
    for(i=0; i<amosa->i_archivesize; i++){
      flag[i]=0;
    }

    for(i=0; i<k; i++){
      for(j=0; j<k; j++){
        if(j != k){
          if(min > distance[i][j]){
            min = distance[i][j];
            u = i;
            v = j;
          }
        }
      }
    }

    if(cluster[u]==u && cluster[v]==v){
      cluster[u]=v;
      cluster[v]=u;
    } else if(cluster[u]==u) {
      j=cluster[v];
      while(cluster[j]!=v){
        j=cluster[j];
      }
      cluster[j]=u;
      cluster[u]=v;
    } else if(cluster[v]==v) {
      j=cluster[u];
      while(cluster[j]!=u){
        j=cluster[j];
      }
      cluster[j]=v;
      cluster[v]=u;
    } else {
      j=cluster[u];
      while(cluster[j]!=u){
        j=cluster[j];
      }
      cluster[j]=v;
      p=cluster[v];
      while(cluster[p]!=v){
        p=cluster[p];
      }
      cluster[p]=u;
    }

    no_clus=no_clus-1;
    g=0;
    point1[g]=u;
    j=cluster[u];

    while(j!=u){
      g++;
      point1[g]=j;
      j=cluster[j];
    }

    for(i=0;i<=g;i++){

      w=point1[i];
      flag[w]=1;

      for(j=i+1;j<=g;j++){
        m=point1[j];
        flag[m]=1;
        distance[m][w] = distance[w][m] = 2000000.;
      }
    }

    for(i=0; i<amosa->i_archivesize; i++){
      if(flag[i]==0){

        if(cluster[i]==i){
          w=point1[0];
          min=distance[w][i];

          for(j=1;j<=g;j++){

            m=point1[j];

            if(min>distance[m][i]){
              min=distance[m][i];
            }
          }

          for(j=0;j<=g;j++){
            m=point1[j];
            distance[m][i]=min;
          }
          flag[i]=1;

        } else {

          g2=0;
          point2[g2]=i;j=cluster[i];

          while(j!=i){
            g2++;
            point2[g2]=j;
            j=cluster[j];
          }

          w=point1[0];
          m=point2[0];
          min=distance[w][m];

          for(j=0;j<=g;j++){
            w=point1[j];
            for(p=0;p<=g2;p++){
              m=point2[p];

              if(min>distance[w][m]){
                min=distance[w][m];
              }
            }
          }

          for(j=0;j<=g;j++){
            for(p=0;p<=g2;p++){
              w=point1[j];
              m=point2[p];
              distance[m][w]=distance[w][m]=min;
              flag[m]=1;
            }
          }

        }
      }
    }
  }
  // end while loop

  for(i=0;i<amosa->i_archivesize;i++){
    for(h=0;h<amosa->i_totalno_var;h++){
      archive2[i][h]=amosa->d_archive[i][h];
    }
    for(h=0;h<amosa->i_no_offunc;h++){
      area2[i][h]=amosa->d_func_archive[i][h];
    }
  }

  for(i=0;i<amosa->i_archivesize;i++){
    flag[i]=0;
  }

  k=0;
  for(i=0;i<amosa->i_archivesize;i++){
    if(flag[i]==0){
      if(cluster[i]!=i){
        g=0;
        point1[g]=i;
        flag[i]=1;
        j=cluster[i];

        while(j!=i){
          g++;
          point1[g]=j;
          flag[j]=1;
          j=cluster[j];
        }

        for(j=0;j<=g;j++){
          dist[j]=0;
          w=point1[j];
          for(p=0;p<=g;p++){
            if(p!=j){
              m=point1[p];
              for(pp=0;pp<amosa->i_no_offunc;pp++){
                dist[j] += pow((amosa->d_func_archive[w][pp]-amosa->d_func_archive[m][pp]),2);
              }
              dist[j]=sqrt(dist[j]);
            }
          }
        }

        min=dist[0];
        w=point1[0];
        for(j=1;j<=g;j++){
          if(min>dist[j]){
            min=dist[j];
            w=point1[j];
          }
        }

        for(h=0;h<amosa->i_totalno_var;h++){
          amosa->d_archive[k][h] = archive2[w][h];
        }

        for(h=0;h<amosa->i_no_offunc;h++){
          amosa->d_func_archive[k][h]=area2[w][h];
        }

        k++;
      } else {

        for(h=0;h<amosa->i_no_offunc;h++){
          amosa->d_func_archive[k][h]=area2[i][h];
        }

        for(h=0;h<amosa->i_totalno_var;h++){
          amosa->d_archive[k][h]=archive2[i][h];
        }

        k++;

      }
    }
  }
  amosa->i_archivesize=k;

  // free memory
  for(i=0; i<amosa->i_no_offunc+2; i++){
    free(area2[i]);
  }
  free(area2);

  free(point1);
  free(point2);

  free(dist);

  for(i=0; i<amosa->i_softl+1; i++){
    free(distance[i]);
  }
  free(distance);

  free(flag);
  free(cluster);

  for(i=0; i<amosa->i_softl+2; i++){
    free(archive2[i]);
  }
  free(archive2);
};
