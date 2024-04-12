cd /volume/e2

mpicc main.c -o app.o
mpirun --allow-run-as-root -np 6 app.o

rm app.o
