#!/bin/bash

#MSUB -l partition=catalyst
#MSUB -l nodes=49
#MSUB -l walltime=5:00
#MSUB -l gres=ignore
#MSUB -q pbatch
#MSUB -j oe

#MSUB -N synth

srun -N49 /g/g19/lavin2/synth/synth -p 1 -t 1000 -s 2097152
##srun -o /g/g19/lavin2/synth/benchmarks/squeue/$SLURM_JOB_ID.out -N4 /g/g19/lavin2/synth/synth -p 1 -t 1000 -s 1048576
##srun -n8 /g/g19/lavin2/multicram/bin/hello
##mpirun -n 4 /g/g19/lavin2/multicram/bin/hello : -n 4 /g/g19/lavin2/multicram/bin/hello2