all: sort normalize bubble pack
clean:
	rm *.o
	rm sort
	rm normalize
	rm bubble
	rm pack
nuke: clean
	cd djb && make clean
sort: bubble pipe_util.o sort.o djb
	gcc -o sort sort.o pipe_util.o djb/alloc/alloc.a djb/unix/unix.a djb/byte/byte.a
bubble: bubble.c
	gcc -o bubble bubble.c
normalize: normalize.c
	gcc -o normalize normalize.c
pack: pack.c
	gcc -o pack pack.c -lm
djb:
	cd djb && make
%.o: %.c
	gcc -c -Wall $^ -I djb/alloc/
.PHONY: all clean nuke djb
