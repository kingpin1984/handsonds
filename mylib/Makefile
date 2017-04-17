#cd /home/saurabh/myprogs/myrepo/mysources/mylib
#gcc -c -g -Wall -Werror -fpic *.c
#gcc -shared -g -o libmyutils.so *.o
#cd /home/saurabh/myprogs/myrepo/mysources
#gcc -o bstops -g BST_ops.c -I/home/saurabh/myprogs/myrepo/mysources/mylib -L/home/saurabh/myprogs/myrepo/mysources/mylib -lmyutils

CFLAGS= -c -g -Wall -Werror -fpic
LFLAGS= -shared -g
OUT_EXE= libmyutils.so
CC= gcc
CPPC=g++
CFILES= BST.c LinkList.c heapsort.c quicksort.c Utils.c
CPPFILES= BSTNode.cpp mergesort.cpp BigInteger.cpp

OBJECTS:= BST.o LinkList.o heapsort.o quicksort.o Utils.o
CPPOBJS:=BSTNode.o mergesort.o BigInteger.o

all: $(OBJECTS) $(CPPOBJS)
	$(CPPC) $(LFLAGS) -o $(OUT_EXE) $(OBJECTS) $(CPPOBJS)

$(OBJECTS): $(CFILES)
	$(CC) $(CFLAGS) $(CFILES)

$(CPPOBJS): $(CPPFILES)
	$(CPPC) $(CFLAGS) $(CPPFILES)

clean:
	\rm -f *.o *.so

clobber: clean all
