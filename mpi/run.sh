file_path=collectives
target_name=case4
file_name=${target_name}.cpp
mpicxx -o ${file_path}/${target_name}.exe ${file_path}/${file_name}

sbatch ./run_mpi.sh