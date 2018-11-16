all: prog4

prog4: prog4.o Allocation.o Allocator.o
	gcc -g -Wall -Werror -o prog4 prog4.o Allocation.o Allocator.o

prog4.o: Allocation.h Allocator.h

Allocation.o: Allocation.h Allocation.c
	gcc -g -Wall -Werror -c Allocation.c

Allocator.o: Allocator.h Allocator.c Allocation.h
	gcc -g -Wall -Werror -c Allocator.c

clean:
	rm -rf Allocation.o Allocator.o prog4.o prog4

