#!/bin/bash
#SBATCH --job-name=lcs_length
#SBATCH --output slurm.out
#SBATCH --error slurm.err
#SBATCH --partition=batch
#SBATCH --qos=short
#SBATCH --constraint=hpcf2010
#SBATCH --exclusive
#SBATCH --cpus-per-task=8
#SBATCH --ntasks=1

export KMP_AFFINITY="verbose,compact"

echo "2 threads 10000"
export OMP_NUM_THREADS=2
srun ./lcs_length test1.txt 10000 test2.txt 10000

echo "4 threads 10000"
export OMP_NUM_THREADS=4
srun ./lcs_length test1.txt 10000 test2.txt 10000

echo "8 threads 10000"
export OMP_NUM_THREADS=8
srun ./lcs_length test1.txt 10000 test2.txt 10000

echo "2 threads 20000"
export OMP_NUM_THREADS=2
srun ./lcs_length test1.txt 20000 test2.txt 20000

echo "4 threads 20000"
export OMP_NUM_THREADS=4
srun ./lcs_length test1.txt 20000 test2.txt 20000

echo "8 threads 20000"
export OMP_NUM_THREADS=8
srun ./lcs_length test1.txt 20000 test2.txt 20000