sig.o: \
compile sig.c sig.h
	./compile sig.c

sig_block.o: \
compile sig_block.c sig.h hassgprm.h
	./compile sig_block.c

sig_catch.o: \
compile sig_catch.c sig.h hassgact.h
	./compile sig_catch.c

sig_pause.o: \
compile sig_pause.c sig.h hassgprm.h
	./compile sig_pause.c

sig.a: \
makelib sig.o sig_block.o sig_catch.o sig_pause.o
	./makelib sig.a sig.o sig_block.o sig_catch.o sig_pause.o

hassgact.h: \
choose compile load trysgact.c hassgact.h1 hassgact.h2
	./choose cl trysgact hassgact.h1 hassgact.h2 > hassgact.h

hassgprm.h: \
choose compile load trysgprm.c hassgprm.h1 hassgprm.h2
	./choose cl trysgprm hassgprm.h1 hassgprm.h2 > hassgprm.h
