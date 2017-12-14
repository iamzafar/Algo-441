#!/bin/bash
#SBATCH --job-name=lcs_length
#SBATCH --output slurm.out
#SBATCH --error slurm.err
#SBATCH --partition=batch
#SBATCH --qos=short
#SBATCH --constraint=hpcf2013
#SBATCH --exclusive
#SBATCH --cpus-per-task=16
#SBATCH --ntasks=1

export KMP_AFFINITY="verbose,compact"


echo "2 threads 40000 X 30000"
export OMP_NUM_THREADS=2
srun ./lcs_length test1.txt 40000 test2.txt 30000

echo "4 threads 40000 X 30000"
export OMP_NUM_THREADS=4
srun ./lcs_length test1.txt 40000 test2.txt 30000

echo "8 threads 40000 X 30000"
export OMP_NUM_THREADS=8
srun ./lcs_length test1.txt 40000 test2.txt 30000

echo "16 threads 40000 X 30000"
export OMP_NUM_THREADS=16
srun ./lcs_length test1.txt 40000 test2.txt 30000