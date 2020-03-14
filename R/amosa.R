################################################################################
#
#   AMOSA algorithm from R
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
################################################################################


#' Call AMOSA algorithm
#'
#'
#' @param verbose print detailed information?
#'
#' @useDynLib amosa AMOSA_C
#' @export
AMOSA <- function(verbose){
  .Call(AMOSA_C,as.logical(verbose))
}
