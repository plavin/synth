#include "synth_util.h"


extern int rank, num_ranks;
extern int c;
extern int waittime, size, pattern;
extern unsigned char * m, *recv1, *recv2;
extern int dim_len;


void nearest_neighbor_1d(){
  MPI_Request req1, req2;

  int next_rank = positive_modulo(rank + 1, num_ranks);
  int prev_rank = positive_modulo(rank - 1, num_ranks);

  MPI_Isend(m, size, MPI_UNSIGNED_CHAR, next_rank, 0, MPI_COMM_WORLD, &req1);
  MPI_Isend(m, size, MPI_UNSIGNED_CHAR, prev_rank, 0, MPI_COMM_WORLD, &req2);

  MPI_Recv(recv1, size, MPI_UNSIGNED_CHAR, next_rank, 0, MPI_COMM_WORLD, NULL);
  MPI_Recv(recv2, size, MPI_UNSIGNED_CHAR, prev_rank, 0, MPI_COMM_WORLD, NULL);

  MPI_Wait(&req1, NULL);
  MPI_Wait(&req2, NULL);
  MPI_Barrier(MPI_COMM_WORLD);
}

void nearest_neighbor_2d(){
  MPI_Request req[4];
  int neighbor[4];
  
  unsigned char recv[size * 4];

  getNeighbors2d(rank, dim_len, neighbor);
  
  int i;
  for(i = 0; i < 4; i++){
    MPI_Isend(m, size, MPI_UNSIGNED_CHAR, neighbor[i], 0, MPI_COMM_WORLD, &(req[i]));
  }

  for(i = 0; i < 4; i++){
    MPI_Recv(&(recv[(size*i)]), size, MPI_UNSIGNED_CHAR, neighbor[i], 0, MPI_COMM_WORLD, NULL);
  }
  
  for(i = 0; i< 4; i++){
    MPI_Wait(&(req[i]), NULL);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  
}
void nearest_neighbor_3d(){ 
  MPI_Request req[6];
  int neighbor[6];
  
  unsigned char recv[size * 6];

  getNeighbors3d(rank, dim_len, neighbor);
  
  int i;
  for(i = 0; i < 6; i++){
    MPI_Isend(m, size, MPI_UNSIGNED_CHAR, neighbor[i], 0, MPI_COMM_WORLD, &(req[i]));
  }

  for(i = 0; i < 6; i++){
    MPI_Recv(&(recv[(size*i)]), size, MPI_UNSIGNED_CHAR, neighbor[i], 0, MPI_COMM_WORLD, NULL);
  }
  
  for(i = 0; i< 6; i++){
    MPI_Wait(&(req[i]), NULL);
  }
  MPI_Barrier(MPI_COMM_WORLD);
}

void nearest_neighbor_4d(){
  MPI_Request req[8];
  int neighbor[8];
  
  unsigned char recv[size * 8];

  getNeighbors4d(rank, dim_len, neighbor);
  
  int i;
  for(i = 0; i < 8; i++){
    MPI_Isend(m, size, MPI_UNSIGNED_CHAR, neighbor[i], 0, MPI_COMM_WORLD, &(req[i]));
  }

  for(i = 0; i < 8; i++){
    MPI_Recv(&(recv[(size*i)]), size, MPI_UNSIGNED_CHAR, neighbor[i], 0, MPI_COMM_WORLD, NULL);
  }
  
  for(i = 0; i< 8; i++){
    MPI_Wait(&(req[i]), NULL);
  }
  MPI_Barrier(MPI_COMM_WORLD);
}

void one_to_all(){
  MPI_Bcast(m, size, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
}
void all_to_all(){
  MPI_Alltoall(m, size, MPI_UNSIGNED_CHAR, recv1, size, MPI_UNSIGNED_CHAR, MPI_COMM_WORLD);
}
