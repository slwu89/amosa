# amosa

## src

Contains **C** source code for the *AMOSA* algorithm.

  * `amosa-problems.h`: contains definition of the `AMOSAType` struct which contains parameters for the algorithm as well as problem-specific parameters. It also contains the initialization, free, and evaluate functions for each problem. The list of parameters in `AMOSAType` are listed below:
    * `int i_hardl`: Hardlimit of the archive
    *	`int i_softl`: Softlimit of the archive
    *	`int i_no_ofiter`: Number of iteration per temperature
    *	`int i_hillclimb_no`: Total number of hill_climbing number
    *	`int i_totalno_var`: Total number of variable of the functions
    *	`int i_archivesize`: Stores the archive size
    *	`int i_no_offunc`: Number of function
    *	`char c_problem[50]`: function name to be optimized
    *	`double d_tmax`: maximum temperature
    *	`double d_tmin`: minimum temperature
    *	`double d_alpha`: cooling rate
    *	`double** d_solution`:  data structure corresponding to binary strings
    *	`double** d_archive`:  archive
    *	`double** d_func_archive`:  variable to store the functional values of the archive solutions
    *	`double* d_eval`: objectives function values
    *	`double* d_func_range`:	range of the functions
    *	`double* d_min_real_var`:	Store minimum value of the real variables
    *	`double* d_max_real_var`:	Store maximum value of the real variables
  * `amosa-evaluate.h`: the generic form of evaluate which is seen by the rest of the program.
  * `amosa-mutate.h`: mutates a solution
  * `amosa-initsoln.h`: initializes the soft limit number of random initial "solutions"
  * `amosa-initarchive.h`: initializes the archive
