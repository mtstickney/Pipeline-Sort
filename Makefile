all: sort normalize bubble pack
sort: bubble pipe_util.o sort.o
	gcc -o sort sort.o pipe_util.o djb/alloc/alloc.a djb/unix/unix.a djb/byte/byte.a
bubble: bubble.c
	gcc -o bubble bubble.c
normalize: normalize.c
	gcc -o normalize normalize.c
pack: pack.c
	gcc -o pack pack.c -lm
%.o: %.c
	gcc -c -Wall $^ -I djb/alloc/
.PHONY: all
