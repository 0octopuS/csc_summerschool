#include <cstdio>
#include <cmath>
#include <mpi.h>
constexpr int n = 840;

int main(int argc, char** argv)
{

  MPI_Init(&argc, &argv);
  MPI_Status status;
  int myid, istart, istop;
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  printf("Computing approximation to pi with N=%d\n", n);

  istart = myid == 0 ? 1: n/2+1;
  istop = myid == 0? n/2: n;

  double pi = 0.0;
  for (int i=istart; i <= istop; i++) {
    double x = (i - 0.5) / n;
    pi += 1.0 / (1.0 + x*x);
  }
  pi *= 4.0 / n;
  
  if(myid == 1){
    MPI_Send( &pi, 1, MPI_DOUBLE, 0 , 1, MPI_COMM_WORLD);
  } else{
    double pi_other;
    MPI_Recv( &pi_other , 1, MPI_DOUBLE ,1 , 1 , MPI_COMM_WORLD , &status);
    pi += pi_other;
    printf("Approximate pi=%18.16f (exact pi=%10.8f)\n", pi, M_PI);
  }
}
