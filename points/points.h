#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>

inline int positive_modulo(int i, int n);

struct loc2d{
  int x;
  int y;
};

struct loc2d getloc2d(int rank, int dim_len);

void printloc2d(struct loc2d pt);

int getrank2d(struct loc2d pt, int dim_len);

void getNeighbors2d(int rank, int dim_len, int * neighbor);

struct loc3d{
  int x;
  int y;
  int z;
};

struct loc3d getloc3d(int rank, int dim_len);

void printloc3d(struct loc3d pt);

int getrank3d(struct loc3d pt, int dim_len);

void getNeighbors3d(int rank, int dim_len, int * neighbor);

struct loc4d{
  int x;
  int y;
  int z;
  int a;
};

struct loc4d getloc4d(int rank, int dim_len);

void printloc4d(struct loc4d pt);

int getrank4d(struct loc4d, int dim_len);

void getNeighbors4d(int rank, int dim_len, int * neighbor);

#endif
