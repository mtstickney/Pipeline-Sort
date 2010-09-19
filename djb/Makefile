SHELL = /bin/sh

all: alloc/alloc.a buffer/buffer.a byte/byte.a dns/dns.a unix/unix.a \
tai/tai.a timeout/timeout.a sig/sig.a

alloc/alloc.a:
	cd alloc && $(MAKE) alloc.a

buffer/buffer.a:
	cd buffer && $(MAKE) buffer.a

byte/byte.a:
	cd byte && $(MAKE) byte.a

dns/dns.a:
	cd dns && $(MAKE) dns.a

unix/unix.a:
	cd unix && $(MAKE) unix.a

sig/sig.a:
	cd sig && $(MAKE) sig.a

tai/tai.a:
	cd tai && $(MAKE) tai.a

timeout/timeout.a:
	cd timeout && $(MAKE) timeout.a

clean:
	cd alloc && $(MAKE) clean
	cd buffer && $(MAKE) clean
	cd byte && $(MAKE) clean
	cd dns && $(MAKE) clean
	cd unix && $(MAKE) clean
	cd sig && $(MAKE) clean
	cd tai && $(MAKE) clean
	cd timeout && $(MAKE) clean

tar:
	cd .. && tar cf djb.tar.bz2 djb --use=bzip2
