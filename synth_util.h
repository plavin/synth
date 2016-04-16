#ifndef SYNTH_UTIL_H
#define SYNTH_UTIL_H
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

void nearest_neighbor_1d();
void nearest_neighbor_2d();
void nearest_neighbor_3d();
void nearest_neighbor_4d();
void one_to_all();
void all_to_all();

#endif
