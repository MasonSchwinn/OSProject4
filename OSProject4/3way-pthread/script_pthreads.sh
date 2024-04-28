#!/bin/bash

cat <<EOF > job_script.sh
#!/bin/sh
hostname
./PTHREADS
EOF

pip install scipy
pip install matplotlib


chmod u+x job_script.sh



job_id_1=$(sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=1 --ntasks=1 --nodes=1 --parsable job_script.sh)
job_id_2=$(sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=2 --ntasks=1 --nodes=1 --parsable job_script.sh)
job_id_3=$(sbatch --constraint=moles --time=24:00:00 --mem-per-cpu=4G --cpus-per-task=4 --ntasks=1 --nodes=1 --parsable job_script.sh)


python script_python.py $job_id_1 $job_id_2 $job_id_3