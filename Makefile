main:main.c scan.c expr.c interp.c tree.c cg.c gen.c
	cc -o main -g expr.c interp.c main.c scan.c tree.c cg.c gen.c

clean:
	rm -f main *.o