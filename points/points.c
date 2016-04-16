#include "points.h"

inline int positive_modulo(int i, int n) {
  return (i % n + n) % n;
}

struct loc2d getloc2d(int rank, int dim_len){
  struct loc2d pt;
  pt.y = rank % dim_len;
  pt.x = (rank / dim_len) % dim_len;
  return pt;
}

void printloc2d(struct loc2d pt){
  printf("(%d,%d)\n", pt.x, pt.y);
}

int getrank2d(struct loc2d pt, int dim_len){
  int sum = 0;
  sum += pt.y;
  sum += pt.x * dim_len;
  return sum;
}

void getNeighbors2d(int rank, int dim_len, int * neighbor){
  struct loc2d cur = getloc2d(rank, dim_len);
  cur.x = positive_modulo(cur.x-1, dim_len);
  neighbor[0] = getrank2d(cur, dim_len);
  //  printloc2d(cur);
  cur.x = positive_modulo(cur.x+2, dim_len);
  neighbor[1] = getrank2d(cur, dim_len);
  //  printloc2d(cur);
  cur.x = positive_modulo(cur.x-1, dim_len);
  cur.y = positive_modulo(cur.y-1, dim_len);
  neighbor[2] = getrank2d(cur, dim_len);
  //  pintloc2d(cur);
  cur.y = positive_modulo(cur.y+2, dim_len);
  neighbor[3] = getrank2d(cur, dim_len);
  //  printloc2d(cur);
  return;
}

struct loc3d getloc3d(int rank, int dim_len){
  struct loc3d pt;
  pt.z = rank % dim_len;
  pt.y = (rank / dim_len) % dim_len;
  pt.x = (rank / (dim_len * dim_len)) % dim_len;
  return pt;
}

void printloc3d(struct loc3d pt){
  printf("(%d,%d,%d)\n", pt.x, pt.y, pt.z);
}

int getrank3d(struct loc3d pt, int dim_len){
  int sum = 0;
  sum += pt.z;
  sum += pt.y * dim_len;
  sum += pt.x * dim_len * dim_len;
  return sum;
}

void getNeighbors3d(int rank, int dim_len, int * neighbor){
  struct loc3d cur = getloc3d(rank, dim_len);
  cur.x = positive_modulo(cur.x-1, dim_len);
  neighbor[0] = getrank3d(cur, dim_len);

  cur.x = positive_modulo(cur.x+2, dim_len);
  neighbor[1] = getrank3d(cur, dim_len);

  cur.x = positive_modulo(cur.x-1, dim_len);
  cur.y = positive_modulo(cur.y-1, dim_len);
  neighbor[2] = getrank3d(cur, dim_len);

  cur.y = positive_modulo(cur.y+2, dim_len);
  neighbor[3] = getrank3d(cur, dim_len);

  cur.y = positive_modulo(cur.y-1, dim_len);
  cur.z = positive_modulo(cur.z-1, dim_len);
  neighbor[4] = getrank3d(cur, dim_len);

  cur.z = positive_modulo(cur.z+2, dim_len);
  neighbor[5] = getrank3d(cur, dim_len);

  return;
}

struct loc4d getloc4d(int rank, int dim_len){
  struct loc4d pt;
  pt.a = rank % dim_len;
  pt.z = (rank / dim_len) % dim_len;
  pt.y= (rank / (dim_len * dim_len)) % dim_len;
  pt.x = (rank / (dim_len * dim_len * dim_len)) % dim_len;
  return pt;
}

void printloc4d(struct loc4d pt){
  printf("(%d,%d,%d,%d)\n", pt.x, pt.y, pt.z, pt.a);
}

int getrank4d(struct loc4d pt, int dim_len){
  int sum = 0;
  sum += pt.a;
  sum += pt.z * dim_len;
  sum += pt.y * dim_len * dim_len;
  sum += pt.x * dim_len * dim_len * dim_len;
  return sum;
}

void getNeighbors4d(int rank, int dim_len, int * neighbor){
  struct loc4d cur = getloc4d(rank, dim_len);
  cur.x = positive_modulo(cur.x-1, dim_len);
  neighbor[0] = getrank4d(cur, dim_len);

  cur.x = positive_modulo(cur.x+2, dim_len);
  neighbor[1] = getrank4d(cur, dim_len);

  cur.x = positive_modulo(cur.x-1, dim_len);
  cur.y = positive_modulo(cur.y-1, dim_len);
  neighbor[2] = getrank4d(cur, dim_len);

  cur.y = positive_modulo(cur.y+2, dim_len);
  neighbor[3] = getrank4d(cur, dim_len);

  cur.y = positive_modulo(cur.y-1, dim_len);
  cur.z = positive_modulo(cur.z-1, dim_len);
  neighbor[4] = getrank4d(cur, dim_len);

  cur.z = positive_modulo(cur.z+2, dim_len);
  neighbor[5] = getrank4d(cur, dim_len);

  cur.z = positive_modulo(cur.z-1, dim_len);
  cur.a = positive_modulo(cur.a-1, dim_len);
  neighbor[6] = getrank4d(cur, dim_len);

  cur.a = positive_modulo(cur.a+2, dim_len);
  neighbor[7] = getrank4d(cur, dim_len);

  return;
}
/*
int main(){
  int i, dim=3;
  for(i = 0; i < dim*dim*dim*dim; i++){
    //   printloc4d(getloc4d(i, dim));
  }

  i = 0;
  struct loc4d a = getloc4d(i, dim);
  int ranks[6];
  getNeighbors4d(i, dim, ranks);
  int j;
  for(j = 0; j < 8; j++){
    printloc4d(getloc4d(ranks[j], dim));
  }
	   
 
}
*/
