# chemical langevin approximation

# based on fokker-planck approximation to master equations: get the mean/variances right
# higher order moments will be off

# SDE system driven by independent Brownian motion (wiener processes); scale by step size and hazard for proper variances

StepCLE <- function(N,dt=0.01)
{
  # if the stochiometry matrices are sparse, use the Matrix version of transpose
  if(attr(class(N$Post),"package") == "Matrix"){
    S <- Matrix::t(N$Post-N$Pre)
  } else {
    S <- t(N$Post-N$Pre)
  }
  v = ncol(S)
  sdt = sqrt(dt)
  return(
         function(x0, t0, deltat,...)
         {
           x = x0
           t = t0
           termt = t0+deltat
           repeat {
             h = N$h(x, t, ...)
             if(any(h > 1e6)){
               stop("warning: hazard too large, terminating simulation; try reducing dt")
             }
             dw = rnorm(v,0,sdt)
             dx = S %*% (h*dt + sqrt(h)*dw)
             x = x + as.vector(dx)
             # x[x<0] = -x[x<0] # reflection hack
             x[x<0] <- 0 # "absorption" at 0; not a hack? check smfsb
             t = t+dt
             if (t > termt)
               return(x)
           }
         }
         )
}
