PATH_DSAA := ../dsaa

CC 	:= gcc
AR 	:= ar
RANLIB 	:= ranlib
LDLIBS 	:= -lds -lrt -lm
LDFLAGS := -L$(PATH_DSAA)/lib/
DEFINES :=
INC_DIR := $(PATH_DSAA)/include
INCLUDE := -I$(INC_DIR)
CFLAGS 	:= -ansi -g -O3 $(DEFINES) $(INCLUDE)
OBJS 	:=
SRCS 	:=
DEP_LIB := $(PATH_DSAA)/lib/libds.a

BIN_GETOPT := getopt_demo.out

all : mylibs $(BIN_GETOPT) my_memcpy.bin

$(BIN_GETOPT) : getopt_demo.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

my_memcpy.bin: my_memcpy.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

.PHONY : clean db mylibs

mylibs :
	$(MAKE) -C $(PATH_DSAA)/lib

clean :
	$(RM) *.o *.out *.so *.a tags filenametags *.bin

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
