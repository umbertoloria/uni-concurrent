cd /volume/e3

mpicc main-scatter.c -o app.o
mpirun --allow-run-as-root --oversubscribe -np 6 app.o

rm app.o
