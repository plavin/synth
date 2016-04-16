#!/bin/bash

sizes=(512 2048 8192 32768 131072 524288)
numnodes=(4 9 16 25 36)
for i in `seq 1 20`
do
    for j in "${sizes[@]}"
    do
	for k in "${numnodes[@]}"
	do
	    msub -l partition=cab,nodes=$k moab-gen.sh $k 1 100 $j
	    sleep 10m
	done
    done
done