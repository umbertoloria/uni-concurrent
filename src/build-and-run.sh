cd /volume/e1

mpicc main.c -o app.o
mpirun --allow-run-as-root -np 2 app.o

rm app.o
