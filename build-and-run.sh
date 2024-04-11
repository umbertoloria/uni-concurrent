mpicc eserc1.c -o hello
mpirun --allow-run-as-root -np 2 ./hello
