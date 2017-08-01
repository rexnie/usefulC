CC 	:= gcc
AR 	:= ar
RANLIB 	:= ranlib
LDLIBS 	:= -lds -lrt
LDFLAGS := -L../lib
DEFINES :=
INCLUDE := -I../include/
CFLAGS 	:= -ansi -g -O3 $(DEFINES) $(INCLUDE)

OBJS 	:= permutation.o
SRCS 	:=
DEP_LIB := ../lib/libds.a

TARGET 	:= permutation

all : $(TARGET)

$(TARGET) : $(OBJS) $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

*.o : ../include/ds.h

.PHONY : clean db
clean :
	$(RM) *.o *.out *.so *.a tags filenametags
	$(RM) $(TARGET)

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
