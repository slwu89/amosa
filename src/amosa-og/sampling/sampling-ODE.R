################################################################################
#
#   MGDrivE-2: ODE numerical integrator
#   Marshall Lab
#   slwu89@berkeley.edu
#   October 2019
#
################################################################################

#' Make Mean-field Approximation (ODE) Numerical Integrator for a SPN Model
#'
#' Make a function closure to implement a first order mean-field ODE approximation for a SPN.
#' This method is equivalent to considering the ODEs describing the time evolution of the mean trajectory (first moment)
#' and setting all higher order moments which appear on the right hand side to zero. The returned closure is to be used by \code{\link{sim_trajectory}}.
#'
# #' @param N a list representing the SPN; must have named elements \code{S} (stoichiometry matrix) and \code{h} (vector of hazard functions).
#' @param S a stoichiometry \code{\link[Matrix]{Matrix-class}} object
#' @param haz a vector of hazard functions
#' @param method a character giving the type of numerical integrator used (see \code{\link[deSolve]{ode}} for complete options); the default
#'        is "lsoda", for inhomogeneous systems consider using "rk4" to avoid excessively long integration times
#'
#' @details
#' Note that the function \code{h} in the list \code{N} does not return the vector of hazards but rather the vector of derivatives of state variables as required
#' by the numerical integrators provided by \code{deSolve}. An example of the proper function is provided below:
#'
# #' @examples
# #' \dontrun{
# #' N$h <- function(t,state,par=NULL){
# #'  dM <- N$S %*% vapply(X = hazards,FUN = function(h){h(t=t,M=state)},FUN.VALUE = numeric(1),USE.NAMES = FALSE)
# #'  list(dM[,1])
# #' }
# #' }
#'
#' @export
StepODE <- function(S,haz,method="lsoda")
{

  if(attr(class(S),"package") != "Matrix"){
    cat("warning: the stoichiometry 'S' matrix is not sparse; significant speed issues possible\n")
  }

  # assign to local environment
  S <- S
  haz <- haz
  method <- method

  dxdt <- function(t,state,par=NULL){
    dM <- S %*% vapply(X = haz,FUN = function(h){h(t=t,M=state)},FUN.VALUE = numeric(1),USE.NAMES = FALSE)
    list(dM[,1])
  }

  return(
         function(x0, t0, deltat,...){

           # initial state in step
           x = x0
           t = t0
           termt = t0+deltat

           # solve ODEs over the step
           X <- deSolve::ode(y = M0,times = c(t,termt),func = dxdt,parms = NULL,method=method)
           return(X[2,-1])
         }
       )
}
