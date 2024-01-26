#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int array[8][8];

    // Declare a variable storing the MPI datatype
    // TODO
    MPI_Datatype new_type;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays
    if (rank == 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                array[i][j] = (i + 1) * 10 + j + 1;
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                array[i][j] = 0;
            }
        }
    }

    // Print data on rank 0
    if (rank == 0) {
        printf("Data on rank %d\n", rank);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    // Create datatype
    // TODO
    int array_of_blocklengths[4] = {1,2,3,4};
    int array_of_displacements[4] = {0,17,17,17};
    for(int i = 1; i < 4; i++) array_of_displacements[i] += array_of_displacements[i-1];
    MPI_Type_indexed( 4 ,  array_of_blocklengths , array_of_displacements , MPI_INT, &new_type);
    // MPI_Type_vector( 8 , 1 , 1 , MPI_INT , &new_type);
    MPI_Type_commit( &new_type);

    // Send data from rank 0 to rank 1
    // TODO
    if(0 == rank){
        MPI_Send(&array[0][0], 1, new_type, 1, 1, MPI_COMM_WORLD);
    } else{
        MPI_Recv(&array[0][0], 1, new_type, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Free datatype
    // TODO
     MPI_Type_free(&new_type);

    // Print received data
    if (rank == 1) {
        printf("Received data on rank %d\n", rank);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}
