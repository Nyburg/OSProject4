all: lswc redirout

lswc: lswc.c
	gcc -o lswc lswc.c

redirout: redirout.c
	gcc -o redirout redirout.c

clean:
	rm -f lswc redirout