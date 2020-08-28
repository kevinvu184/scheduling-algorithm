all: FCFS RR SJF

FCFS: FCFS.o
	gcc -g -Wall -Werror -O -o FCFS FCFS.c

SJF: SJF.o
	gcc -g -Wall -Werror -O -o SJF SJF.c

RR: RR.o
	gcc -g -Wall -Werror -O -o RR RR.c -lm
	
clean:
	rm -f FCFS RR SJF *.o *.out *.txt
