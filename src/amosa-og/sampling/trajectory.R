# simulate a trajectory

# helper function to check 0s
fequal <- function(x,y,tol=.Machine$double.eps^0.5){
  abs(x-y) <= tol
}

# want a way to record only every dt steps
sim_trajectory <- function(x0, t0=0, tt=100, dt=1, stepFun, events = NULL, pb = FALSE, ...){

  # number of steps we need to take
  n = (tt-t0) %/% dt + 1
  times <- seq(from=t0,to=tt,by=dt)

  if(length(times) != n){
    stop("error in sequence of times; make sure tt is evenly divisible by dt")
  }

  u = length(x0)
  names = names(x0)

  x = x0
  t = t0

  # output matrix
  mat = matrix(data=0,nrow=length(times),ncol=u+1,dimnames=list(NULL,c("time",names)))
  mat[,1] <- times
  mat[1,-1] = x

  # make sure events occur at times that will actually be sampled
  if(any(events$time %% dt != 0)){
    cat("warning: event times do not correspond to a multiple of dt; event times will be rounded up to the nearest time-step!\n")
    events$time <- events$time + (events$time %% dt)
  }

  # progress bar
  if(pb){pbar <- txtProgressBar(min = 1,max = n,style = 3)}
  cat(" --- begin simulation --- \n")

  # main simulation loop
  for (i in 2:n) {

    # iterate the step function until this delta t is over
    t = times[i]
    x = stepFun(x,t,dt,...)

    if(all(fequal(x,0))){
      if(pb){close(pbar)}
      cat(" --- marking of net is zero; terminating simulation early --- \n")
      return(mat)
    }

    # add the event to the state vector
    if(!is.null(events)){
      while(nrow(events) > 0 & fequal(events[1,"time"],t)){
        # browser()
        x[events[1,"var"]] <- x[events[1,"var"]] + events[1,"value"]
        events <- events[-1,]
      }
    }

    # record output
    mat[i,-1] <- x

    # progress bar
    if(pb){setTxtProgressBar(pb = pbar,value = i)}
  }

  if(pb){close(pbar)}
  cat(" --- end simulation --- \n")

  return(mat)
}
