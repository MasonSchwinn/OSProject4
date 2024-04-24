#!/bin/bash

cat <<EOF > job_script.sh
#!/bin/sh
hostname
/homes/nlillich/hw4/OSProject4/3way-omp/omp.o
EOF

chmod u+x job_script.sh

sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=1  --nodes=1 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=2  --nodes=2 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=4  --nodes=4 job_script.sh