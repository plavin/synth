# Synth 
Simple synthetic MPI benchmarks

## Purpose
This program is a configurable MPI sythetic benchark. It's purpose is to run very simple communication patterns, so that one can measure the contention caused by such a pattern. 

## Options

-v Verbose: print SQUEUE output to squeue/$JOBID-squeue.out

-s Size: message size (bytes)

-p Pattern: an integer in [0,5] specifying the communication pattern to use. The supported patterns are:

   0: Nearest Neighbor 1D
   1: Nearest Neighbor 2D 
   2: Nearest Neighbor 3D
   3: Nearest Neighbor 4D
   4: One to All
   5: All to All

-i Iterations: number of times the comm phase will be run

-t Timing: milliseconds between comm phases

## Usage

A sample usage case might be: `srun -N8 /g/g19/lavin2/synth/synth -p 1 -t 1000 -s 1048576` as is provided in `moab.sh`.

# Compiling

`make` 

# Examples 

Simply look at the `moab.sh` file

# Warning
 
I have learned a lot about software development in C since I wrote this. I could probably point out a dozen problems with this. Regardless, I believe the code should be fine if you want to use it without modification. I would not recommend extending it. If there is interest, I would be happy to impelement a newer version with more modern practices and a larger list of communication patterns. 
