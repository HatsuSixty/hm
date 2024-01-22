CFLAGS=-Wall -Wextra -std=c11 -pedantic -ggdb

all: hasm hm

# Build hasm
hasm: src/hasm.o src/vm.o src/util.o
	$(CC) $(CFLAGS) -o hasm src/hasm.o src/vm.o src/util.o $(LIBS)

src/hasm.o: src/hasm.c
	$(CC) $(CFLAGS) -o src/hasm.o -c src/hasm.c $(LIBS)

# Build hm
hm: src/hm.o src/vm.o src/util.o
	$(CC) $(CFLAGS) -o hm src/hm.o src/vm.o src/util.o $(LIBS)

src/hm.o: src/hm.c
	$(CC) $(CFLAGS) -o src/hm.o -c src/hm.c $(LIBS)

# Build depedencies
src/vm.o: src/vm.c
	$(CC) $(CFLAGS) -o src/vm.o -c src/vm.c $(LIBS)

src/util.o: src/util.c
	$(CC) $(CFLAGS) -o src/util.o -c src/util.c $(LIBS)
