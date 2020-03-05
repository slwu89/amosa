# -------------------------------------------------------------------------------- #
#
#   Test functions from AMOSA
#   Sean Wu (slwu89@berkeley.edu)
#   March 2020
#
# -------------------------------------------------------------------------------- #

#' DTLZ1
#'
#' One of the test functions from the \url{https://github.com/amirmasoudabdol/amosa}{AMOSA} package.
#' It is a 7 dimensional continuous optimization problem with 3 objectives and can be found in the paper:
#' * Deb, Kalyanmoy, et al. "Scalable multi-objective optimization test problems." Proceedings of the 2002 Congress on Evolutionary Computation. CEC'02 (Cat. No. 02TH8600). Vol. 1. IEEE, 2002.
#'
#' @param s a numeric vector of length 7 (all parameters must be bounded by [0,1])
#'
#' @return a numeric vector of length 3
#' @export
DTLZ1 <- function(s){
  stopifnot(length(s)==7)
  stopifnot(all(s >= 0),all(s <= 1))
  s <- as.numeric(s)
  f <- rep(0,3)

  g <- 100 * (5 + sum( ((s[3:7] - 0.5)^2) - cos(20*pi*(s[3:7] - 0.5)) ))
  f[1] <- 0.5*s[1]*s[2]*(1+g)
  f[2] <- 0.5*s[1]*(1-s[2])*(1+g)
  f[3] <- 0.5*(1-s[1])*(1+g)

  return(f)
}


#' Call DTLZ1 from C
#'
#' See \code{\link[amosa]{DTLZ1}} for details.
#'
#' @param s a numeric vector of length 7 (all parameters must be bounded by [0,1])
#'
#' @return a numeric vector of length 3
#' @useDynLib amosa call_DTLZ1_from_c
#' @export
DTLZ1_fromC <- function(s){
  .Call(call_DTLZ1_from_c,as.numeric(s),new.env())
}
