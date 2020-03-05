# a classic tau-leaping method with a fixed (non-adaptive) tau

StepPTS <- function(N,dt=0.01)
{
  # if the stochiometry matrices are sparse, use the Matrix version of transpose
  if(attr(class(N$Post),"package") == "Matrix"){
    S <- Matrix::t(N$Post-N$Pre)
  } else {
    S <- t(N$Post-N$Pre)
  }
  v = ncol(S)
  return(
         function(x0,t0,deltat,...)
         {
           x = x0
           t = t0
           termt = t0+deltat
           repeat {
             h = N$h(x, t, ...)
             if(any(h > 1e6)){
               stop("warning: hazard too large, terminating simulation; try reducing dt")
             }
             r = rpois(v,h*dt)
             x = x+as.vector(S %*% r)
             x[x<0] <- 0 # absorption at zero
             t = t+dt
             if (t > termt)
               return(x)
           }
         }
         )
}
