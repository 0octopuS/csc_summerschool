file_path=datatypes-extent
target_name=type1
file_name=${target_name}.cpp
mpicxx -o ${file_path}/${target_name}.exe ${file_path}/${file_name}

sbatch ./run_mpi.sh