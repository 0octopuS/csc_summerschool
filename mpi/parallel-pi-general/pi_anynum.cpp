#include <cstdio>
#include <cmath>
#include <mpi.h>
constexpr int n = 843;

int main(int argc, char** argv)
{

  MPI_Init(&argc, &argv);
  MPI_Status status;
  int myid, istart, istop, size;
  MPI_Comm_size( MPI_COMM_WORLD , &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  int num_per_node = n/size;
  int remainder = n % size;



//   version 1: last node deals all remainder
//   istart = myid * num_per_node + 1;
//   istop = (myid  + 1)* num_per_node;
//   if(myid == size -1){
//     istop = n;
//   }

  // version 2: equally assign them to each node
  istart =  myid * num_per_node + 1 +
  ((myid < remainder)? myid: remainder);

  istop = (myid  + 1)* num_per_node + ((myid < remainder)? myid + 1: remainder);

  double pi = 0.0;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi += 1.0 / (1.0 + x*x);
  }
  
  
  printf("Node %d compute for %d-%d.\n", myid, istart, istop);
  if(myid != 0){
    MPI_Send( &pi, 1, MPI_DOUBLE, 0 , 0, MPI_COMM_WORLD);
  } 
  
  if(myid == 0)
  {
    for(int i = 1; i < size; i++){
      double pi_other;
      MPI_Recv( &pi_other , 1, MPI_DOUBLE , MPI_ANY_SOURCE , 0 , MPI_COMM_WORLD , &status);
      pi += pi_other;
    }
    pi *= 4.0 / n;
    printf("Computing approximation to pi with N=%d\n", n);
    printf("Each one is responsible for %d elements.\n", num_per_node);
    printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  }
  MPI_Finalize();
}
