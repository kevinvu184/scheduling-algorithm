all: FCFS SJF RR

FCFS: FCFS.o
	gcc -g -Wall -Werror -O -o FCFS FCFS.c

SJF: SJF.o
	gcc -g -Wall -Werror -O -o SJF SJF.c

RR: RR.o
	gcc -g -Wall -Werror -O -o RR RR.c

run:
	./FCFS
	./SJF
	./RR

valgrind:
	valgrind ./FCFS
	valgrind ./SJF
	valgrind ./RR
	
clean:
	rm -f FCFS RR SJF *.o *.out *.txt
