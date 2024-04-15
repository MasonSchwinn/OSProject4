#!/bin/bash

cat <<EOF > job_script.sh
#!/bin/sh
hostname
./MPI
EOF

chmod u+x job_script.sh

sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=1 --ntasks=1 --nodes=1 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=2 --ntasks=1 --nodes=1 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=4 --ntasks=1 --nodes=1 job_script.sh