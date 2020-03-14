/* --------------------------------------------------------------------------------
#
#   single linkage clustering
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
-------------------------------------------------------------------------------- */

#ifndef AMOSA_CLUSTER
#define AMOSA_CLUSTER

#include <stdlib.h>

#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "amosa-problems.h"


/* --------------------------------------------------------------------------------
#   If the size of the archive is greater than Soft Limit (SL) then the clustering process is
#   done to reduce the size of the archive to Hard Limit (HL).
#   The function clustering clusters by "Single Linkage Clustering" mechanism
-------------------------------------------------------------------------------- */

void clustering(AMOSAType* amosa);

#endif
