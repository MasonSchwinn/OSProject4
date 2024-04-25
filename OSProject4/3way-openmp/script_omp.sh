#!/bin/bash

cat <<EOF > job_script.sh
#!/bin/sh
hostname
./OPENMP
EOF

chmod u+x job_script.sh

sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=1 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=2 job_script.sh
sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=4 job_script.sh