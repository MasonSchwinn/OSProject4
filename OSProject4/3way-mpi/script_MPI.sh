#!/bin/bash

cat <<EOF > job_script.sh
#!/bin/sh
hostname
mpirun ./MPI
EOF

chmod u+x job_script.sh

#sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --ntasks-per-node=1 --nodes=1 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --ntasks-per-node=2 --nodes=1 job_script.sh
#sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --ntasks-per-node=4 --nodes=1 job_script.sh