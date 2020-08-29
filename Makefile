all: FCFS SJF RR

FCFS: FCFS.o
	gcc -g -Wall -Werror -O -o FCFS FCFS.c
	./FCFS

SJF: SJF.o
	gcc -g -Wall -Werror -O -o SJF SJF.c
	./SJF

RR: RR.o
	gcc -g -Wall -Werror -O -o RR RR.c -lm
	./RR
	
clean:
	rm -f FCFS RR SJF *.o *.out *.txt
