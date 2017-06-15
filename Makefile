#cd /home/saurabh/myprogs/myrepo/mysources/mylib
#gcc -c -g -Wall -Werror -fpic *.c
#gcc -shared -g -o libmyutils.so *.o
#cd /home/saurabh/myprogs/myrepo/mysources
#gcc -o bstops -g BST_ops.c -I/home/saurabh/myprogs/myrepo/mysources/mylib -L/home/saurabh/myprogs/myrepo/mysources/mylib -lmyutils

CFLAGS= -g -Wall -Werror
OUT_CBSTEXE= bstops
OUT_BSTEXE= bsttrav
OUT_BIGINTEXE= bigint_test
OUT_DIGRAPHEXE= graph_test
OUT_PQTEXE= pqueue_test
CC= gcc
CPPC= g++
INCLUDES= $(CURDIR)/mylib
LIBDIRS= $(CURDIR)/mylib
LIBS= -lmyutils
SHELL=/bin/bash
BST_CSOURCES=BST_ops.c
BST_CPPSOURCES=BST_traversal.cpp
BIGINT_SOURCES=bigint_use.cpp
DIGRAPH_SOURCES=digraph.cpp
PQ_SOURCES=PQtest.cpp

SUBDIRS := $(wildcard */.)

.PHONY : $(SUBDIRS)
all : $(SUBDIRS) $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUT_CBSTEXE) $(BST_CSOURCES) -I$(INCLUDES) -L$(LIBDIRS) $(LIBS)
	$(CPPC) $(CFLAGS) -o $(OUT_BSTEXE) $(BST_CPPSOURCES) -I$(INCLUDES) -L$(LIBDIRS) $(LIBS)
	$(CPPC) $(CFLAGS) -o $(OUT_BIGINTEXE) $(BIGINT_SOURCES) -I$(INCLUDES) -L$(LIBDIRS) $(LIBS)
	$(CPPC) $(CFLAGS) -o $(OUT_DIGRAPHEXE) $(DIGRAPH_SOURCES) -I$(INCLUDES)
	$(CPPC) $(CFLAGS) -o $(OUT_PQTEXE) $(PQ_SOURCES) -I$(INCLUDES) -L$(LIBDIRS) $(LIBS)

$(SUBDIRS) :
	$(MAKE) -C $@ all

SUBDIR_ROOTS := mylib
DIRS := . $(shell find $(SUBDIR_ROOTS) -type d)
GARBAGE_PATTERNS := *.o *~ core .depend .*.cmd *.so *.mod.c
GARBAGE := $(foreach DIR,$(DIRS),$(addprefix $(DIR)/,$(GARBAGE_PATTERNS)))
clean :
	\rm -rf $(GARBAGE) $(OUT_CBSTEXE) $(OUT_BSTEXE) $(OUT_BIGINTEXE) $(OUT_DIGRAPHEXE) $(OUT_PQTEXE)

clobber : clean all
#clean :
#	\rm -f cscope.* *.o $(OUT_CBSTEXE) $(OUT_BSTEXE) $(OUT_BIGINTEXE)
