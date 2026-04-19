main:main.c scan.c expr.c interp.c tree.c
	cc -o main -g expr.c interp.c main.c scan.c tree.c

clean:
	rm -f main *.o