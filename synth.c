#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include "points/points.h"
#include <string.h>
#include "synth_util.h"

const char * config = "Configuration: Delay: %dms, Message Size: %d bytes, Pattern: %s\n";
const char * patterns[] = {"Nearest Neighbor 1D","Nearest Neighbor 2D","Nearest Neighbor 3D","Nearest Neighbor 4D","One to All", "All to All"};
const char * patterns_s[] = {"NN1D","NN2D","NN3D","NN4D","OtA", "AtA"};
int rank, num_ranks;
int c;
int waittime, size, pattern;
unsigned char * m, *recv1, *recv2;
int dim_len;

int main(int argc, char ** argv){

  int jobid;
  int reporting = 0;
  int iterations;
  MPI_Init(&argc, &argv);
  struct timeval begin, end, progbegin;

  FILE * manifest, * squeue_out;
  
  if(rank == 0){
    gettimeofday(&progbegin, NULL);
    if(reporting){
      FILE * JOBID = popen("echo $SLURM_JOB_ID","r");
      fscanf(JOBID,"%d",&jobid);
      
      struct stat st = {0};

      if (stat("squeue", &st) == -1) {
	mkdir("squeue", 0700);
      }

      char squeue_filename[100];
      sprintf(squeue_filename,"squeue/%d-1.out",jobid);
      
      FILE * squeue_out = fopen(squeue_filename,"w");
      
      FILE * squeue = popen("squeue","r");
      char buf[256];
      while(fscanf(squeue,"%255c", buf)>0){
	fprintf(squeue_out,"%s", buf);
	memset(buf, 0, 256);
      }
    }
  }

  while((c = getopt(argc,argv,"t:s:p:v")) != -1){
    switch(c){
    case 'v':
      reporting = 1;
    case 't':
      sscanf(optarg, "%d", &waittime);
      break;
    case 's':
      sscanf(optarg, "%d", &size);
      break;
    case 'i':
      sscanf(optarg, "%d", &iterations);
      break;
    case 'p':
      sscanf(optarg, "%d", &pattern);
      if(pattern > 5 || pattern < 0){
	printf("Invalid pattern\nExiting.\n");
	return 1;
      }
      break;
    default:
      printf("Unrecognized argument\n");
    }
  }

  MPI_Comm_size(MPI_COMM_WORLD, &num_ranks);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  struct timespec s;
  s.tv_nsec = waittime * 1000;
  s.tv_sec = 0;
  /*
  if(rank == 0){
    printf(config, waittime, size, patterns[pattern]);
    }*/
  int i;
  switch(pattern){
  case 0:  //nearest neighbor 1d
    m = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv1 = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv2 = (unsigned char *)malloc(size * sizeof(unsigned char));
    for(i = 0; i < size; i++){
      m[i] = random() % 256;
    }
    break;
  case 1:  //nearest neighbor 2d
    dim_len = (int)sqrt((double)num_ranks);
    if(dim_len*dim_len != num_ranks){
      printf("Error: num_ranks is not a square number: %d\n", num_ranks);
      return 1;
    }
    m = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv1 = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv2 = (unsigned char *)malloc(size * sizeof(unsigned char));
    for(i = 0; i < size; i++){
      m[i] = random() % 256;
    }
    break;
  case 2:  //nearest neighbor 3d
    dim_len = (int)pow((double)num_ranks, 1.0/3);
    if(dim_len*dim_len*dim_len != num_ranks){
      printf("Error: num_ranks is not a perfect cube: %d\n", num_ranks);
      return 1;
    }
    m = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv1 = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv2 = (unsigned char *)malloc(size * sizeof(unsigned char));
    for(i = 0; i < size; i++){
      m[i] = random() % 256;
    }
    break;
  case 3:  //nearest neighbor 4d
    dim_len = (int)pow((double)num_ranks, 1.0/4);
    if(dim_len*dim_len*dim_len*dim_len != num_ranks){
      printf("Error: num_ranks is not a perfect fourth power: %d\n", num_ranks);
      return 1;
    }
    m = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv1 = (unsigned char *)malloc(size * sizeof(unsigned char));
    recv2 = (unsigned char *)malloc(size * sizeof(unsigned char));
    for(i = 0; i < size; i++){
      m[i] = random() % 256;
    }
    break;
  case 4:  //one to all
    m = (unsigned char *)malloc(size * sizeof(unsigned char));
    for(i = 0; i < size; i++){
      m[i] = random() % 256;
    }
    break;
  case 5:  //all to all
    m = (unsigned char *)malloc(size * num_ranks * sizeof(unsigned char));
    recv1 = (unsigned char *)malloc(size * num_ranks * sizeof(unsigned char));
    for(i = 0; i < size * num_ranks; i++){
      m[i] = random() % 256;
    }
    break;
  }
  
  gettimeofday(&begin, NULL);
  PMPI_Barrier(MPI_COMM_WORLD);
  for(i = 0; i < iterations; i++){

    switch(pattern){
    case 0:
      nearest_neighbor_1d();
      break;
    case 1:
      nearest_neighbor_2d();
      break;
    case 2:
      nearest_neighbor_3d();
      break;
    case 3:
      nearest_neighbor_4d();
      break;
    case 4:
      one_to_all();
      break;
    case 5:
      all_to_all();
      break;
    } 
    nanosleep(&s, NULL);
  }
  gettimeofday(&end, NULL);
  double timeelapsed = ((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec)/1000000.0)/iterations;
  double progtime = ((end.tv_sec - progbegin.tv_sec) + (end.tv_usec - progbegin.tv_usec)/1000000.0);
  if(rank == 0){
    
    //print to manifest
    FILE * manifest = fopen("manifest.txt", "a");
    fprintf(manifest,"%d,%s,%d,%d,%lf,%lf,%d\n", num_ranks, patterns_s[pattern],waittime, size, timeelapsed, progtime,jobid);
    fclose(manifest);

    if(reporting){
      char squeue_filename[100];
      sprintf(squeue_filename,"squeue/%d-2.out",jobid);
      FILE * squeue_out = fopen(squeue_filename,"w");
      
      FILE * squeue = popen("squeue","r");
      
      char buf[256];
      while(fscanf(squeue,"%255c", buf)>0){
	fprintf(squeue_out,"%s", buf);
	memset(buf, 0, 256);
      }
    }
  }

  return 0;
}
