!/bin/bash -l
SBATCH --job-name=pthreads

SBATCH --mem-per-cpu=4G   # Memory per core, use --mem= for memory per node
SBATCH --time=4-04:00:00   # Use the form DD-HH:MM:SS
SBATCH --nodes=20
SBATCH --ntasks-per-node=4
SBATCH --constraint=moles

SBATCH --mail-user=mschwinn@ksu.edu
SBATCH --mail-type=ALL   # same as =BEGIN,FAIL,END

mpirun -np $SLURM_NPROCS NPmpi -o np.out