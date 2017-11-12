CC 	:= gcc
AR 	:= ar
RANLIB 	:= ranlib
LDLIBS 	:= -lds -lrt -lm
LDFLAGS := -L../lib
DEFINES :=
INC_DIR := ../include
INCLUDE := -I$(INC_DIR)
CFLAGS 	:= -ansi -g -O3 $(DEFINES) $(INCLUDE)

OBJS 	:= main.o
SRCS 	:=
DEP_LIB := ../lib/libds.a

TARGET 	:= a.out

all : $(TARGET)

$(TARGET) : $(OBJS) $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

*.o : $(INC_DIR)/ds.h

.PHONY : clean db
clean :
	$(RM) *.o *.out *.so *.a tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
