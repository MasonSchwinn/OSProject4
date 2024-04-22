#!/bin/bash

# Make executable
make clean
make

# Submit jobs using sbatch
for i in 1 2 4
do
    
    cat <<EOF > job_script_$i.sh
#!/bin/sh
mpirun -c $i ./MPI

EOF

    # Make the batch script executable
    chmod u+x job_script_$i.sh

    # Submit the batch script using sbatch
    sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=1G --cpus-per-task=1 --ntasks-per-node=$i --nodes=1 ./job_script_$i.sh
done