cd /volume/e3

mpicc main-broadcast.c -o app.o
mpirun --allow-run-as-root --oversubscribe -np 13 app.o

rm app.o
