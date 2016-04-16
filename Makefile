compile: synth.c
	mpicc synth.c synth_util.c points/points.c -o synth -lm

compile-mpi: synth.c
	mpicc synth.c points/points.c -o synth ../multicram/lib/libsplitwrap.a -lm -lstdc++
run:
	./synth
asm: synth.c
	mpicc synth.c -S
test: test.c points/points.c
	mpicc test.c points/points.c -o test -lm