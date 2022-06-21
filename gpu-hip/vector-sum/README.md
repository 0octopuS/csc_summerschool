# Vector sum on two GPUs without MPI

Calculate the vector sum of two vectors (C = A + B) using two GPUs.

Decompose the vectors into equal halves, copy data from host to device memory
and launch a GPU kernel on each part asynchronously using streams. Copy the
results back to the host to check for correctness. Add timing events to
measure the time of execution.

A skeleton code is provided in [vector-sum.cpp](vector-sum.cpp).