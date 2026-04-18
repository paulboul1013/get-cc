main:main.c scan.c
	cc -o main main.c scan.c

clean:
	rm -f main *.o