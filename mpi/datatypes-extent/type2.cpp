#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int array[8][6];

    // Declare a variable storing the MPI datatype
    // TODO
    MPI_Datatype columns,rows;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays
    if (rank == 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                array[i][j] = (i + 1) * 10 + j + 1;
            }
        }
    } else {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                array[i][j] = 0;
            }
        }
    }

    // Print data on rank 0
    if (rank == 0) {
        printf("Data on rank %d\n", rank);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    // Create datatype
    // TODO
    MPI_Type_vector( 8 , 1 , 6 , MPI_INT , &columns); // a column
    MPI_Type_vector( 6 , 1 , 1 , MPI_INT , &rows);
    MPI_Type_commit( &columns);
    MPI_Type_commit( &rows);

    // Send data from rank 0 to rank 1
    // TODO
    if(0 == rank){
        MPI_Send(&array[0][0], 1, columns, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&array[4][0], 1, rows, 1, 2, MPI_COMM_WORLD);
    } else{
        MPI_Recv(&array[0][0], 1, columns, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&array[4][0], 1, rows, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Free datatype
    // TODO
     MPI_Type_free(&rows);
     MPI_Type_free(&columns);
    // Print received data
    if (rank == 1) {
        printf("Received data on rank %d\n", rank);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}
