all: FCFS RR SJF

FCFS:
	gcc -g -Wall -Werror -o FCFS FCFS.c

RR:
	gcc -g -Wall -Werror -o RR RR.c

SJF:
	gcc -g -Wall -Werror -o SJF SJF.c

clean:
	rm FCFS RR SJF
