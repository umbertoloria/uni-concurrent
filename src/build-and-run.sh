cd /volume/e3

mpicc main-gather.c -o app.o
mpirun --allow-run-as-root --oversubscribe -np 13 app.o

rm app.o
