prefix=/usr/local

all:
	gcc -Os obpipec.c -o obpipec

install: obpipec
	install -m 0755 obpipec $(prefix)/bin

.PHONY: install
