#!/bin/bash

if [ $# -lt 4 ]
then
    echo Too few arguments!
else

#MSUB -l walltime=5:00
#MSUB -l gres=ignore
#MSUB -q pbatch
#MSUB -j oe

#MSUB -N synth

srun -N$1 /g/g19/lavin2/synth/synth -p $2 -t $3 -s $4
##srun -o /g/g19/lavin2/synth/benchmarks/squeue/$SLURM_JOB_ID.out -N4 /g/g19/lavin2/synth/synth -p 1 -t 1000 -s 1048576
##srun -n8 /g/g19/lavin2/multicram/bin/hello
##mpirun -n 4 /g/g19/lavin2/multicram/bin/hello : -n 4 /g/g19/lavin2/multicram/bin/hello2

fi