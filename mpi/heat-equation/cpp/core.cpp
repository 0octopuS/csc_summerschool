// Main solver routines for heat equation solver

#include <mpi.h>

#include "heat.hpp"

// Exchange the boundary values
void exchange(Field& field, const ParallelData parallel)
{

    double* sbuf = field.temperature.data(1, 0);
    double* rbuf = field.temperature.data(field.nx + 1, 0);
    // TODO start: implement halo exchange
    // You can utilize the data() method of the Matrix class to obtain pointer
    // to element, e.g. field.temperature.data(i, j)
    MPI_Request request[4];
    MPI_Status status[4];
    // Send to up, receive from down
    MPI_Isend( sbuf , field.ny + 2 , MPI_DOUBLE , parallel.nup , parallel.nup + 100, MPI_COMM_WORLD, & request[0]);
    MPI_Irecv( rbuf , field.ny + 2 , MPI_DOUBLE , parallel.ndown , parallel.rank + 100, MPI_COMM_WORLD,& request[1]);


    // MPI_Isend( sbuf , MPI_Count count , MPI_Datatype datatype , int dest , int tag , MPI_Comm comm , MPI_Request* request);
    // MPI_Isendrecv( sbuf , field.ny + 2 , MPI_DOUBLE ,parallel.nup  , parallel.nup + 100, rbuf , field.ny + 2, MPI_DOUBLE ,parallel.ndown , parallel.rank + 100 , MPI_COMM_WORLD, &request[0]);

    // Send to down, receive from up
    sbuf = field.temperature.data(field.nx, 0);
    rbuf = field.temperature.data();
    MPI_Isend( sbuf , field.ny +2 , MPI_DOUBLE , parallel.ndown , parallel.ndown + 200, MPI_COMM_WORLD,& request[2]);
    MPI_Irecv( rbuf , field.ny + 2 , MPI_DOUBLE , parallel.nup , parallel.rank + 200, MPI_COMM_WORLD, & request[3]);

    // MPI_Isendrecv( sbuf , field.ny + 2 , MPI_DOUBLE ,parallel.ndown  , parallel.ndown + 200, rbuf , field.ny + 2, MPI_DOUBLE ,parallel.nup , parallel.rank + 200 , MPI_COMM_WORLD,&request[1]);

    MPI_Waitall( 4 , request , status);
    // TODO end
}

// Update the temperature values using five-point stencil */
void evolve(Field& curr, const Field& prev, const double a, const double dt)
{

  // Compilers do not necessarily optimize division to multiplication, so make it explicit
  auto inv_dx2 = 1.0 / (prev.dx * prev.dx);
  auto inv_dy2 = 1.0 / (prev.dy * prev.dy);

  // Determine the temperature field at next time step
  // As we have fixed boundary conditions, the outermost gridpoints
  // are not updated.
  for (int i = 1; i < curr.nx + 1; i++) {
    for (int j = 1; j < curr.ny + 1; j++) {
            curr(i, j) = prev(i, j) + a * dt * (
	       ( prev(i + 1, j) - 2.0 * prev(i, j) + prev(i - 1, j) ) * inv_dx2 +
	       ( prev(i, j + 1) - 2.0 * prev(i, j) + prev(i, j - 1) ) * inv_dy2
               );
    }
  }

}
