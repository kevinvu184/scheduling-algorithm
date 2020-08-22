OBJS	 = FCFS.o RR.o SJF.o
SOURCE	 = FCFS.c RR.c SJF.c
OUT	     = Sched
CC	     = gcc
FLAGS	 = -g -c -Wall -Werror

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

FCFS.o: FCFS.c
	$(CC) $(FLAGS) FCFS.c

RR.o: RR.c
	$(CC) $(FLAGS) RR.c

SJF.o: SJF.c
	$(CC) $(FLAGS) SJF.c


clean:
	rm -f $(OBJS) $(OUT)
