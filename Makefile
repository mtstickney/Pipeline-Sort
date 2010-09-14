sort: bubble chan.o pipe_util.o sort.o
	tcc -o sort sort.o chan.o pipe_util.o
bubble:
	tcc -o bubble bubble.c
%.o: %.c
	tcc -c -Wall $^
