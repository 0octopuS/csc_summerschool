#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2009502
#SBATCH --partition=small
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1  

file_path=datatypes-extent
target_name=type1
srun -o ${file_path}/${target_name}.out ${file_path}/${target_name}.exe