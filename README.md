# OSProject4
Project 4 in operating systems for Mason, Nate, and Keenan

Once you have logged in to Beocat with this project, you will want to cd into one of the three
sub-folders: 3way-mpi, 3way-openmp, or 3way-pthread. Once done, enter 'make' into the terminal 
to make said program. To schedule and run on Beocat after making, 

type 'sbatch script_pthreads.sh' for 3way-pthread. 
type 'sbatch script_MPI.sh' for 3way-mpi.
type 'sbatch script_omp.sh' for 3way-openmp.

This will submit the job to Beocat. Depending on whether the process is queued, 
the time can take between 30 seconds to couple hours. The python script
for graphing time and memory will take an additional 60-90 seconds to gather
the data for the graph. If the pending process takes too long, the graphs will
not be made.