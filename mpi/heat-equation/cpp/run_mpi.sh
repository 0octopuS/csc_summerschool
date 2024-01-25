#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2009502
#SBATCH --partition=small
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --cpus-per-task=1  

file_path=heat-equation/cpp
target_name=heat_mpi
srun -o ${target_name}-1.out ${target_name}
srun -o ${target_name}-2.out ${target_name} bottle.dat
srun -o ${target_name}-3.out ${target_name} bottle.dat 1000
srun -o ${target_name}-4.out ${target_name} 4000 8000 1000