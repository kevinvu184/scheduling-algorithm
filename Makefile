OBJS	 = FCFS.o RR.o SJF.o
SOURCE	 = FCFS.c RR.c SJF.c
OUT	     = Sched
CC	     = g++
FLAGS	 = -g -c -Wall -Werror

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

FCFS.o: FCFS.c
	$(CC) $(FLAGS) FCFS.c -std=c++14

RR.o: RR.c
	$(CC) $(FLAGS) RR.c -std=c++14

SJF.o: SJF.c
	$(CC) $(FLAGS) SJF.c -std=c++14


clean:
	rm -f $(OBJS) $(OUT)
