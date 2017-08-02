WKDIR 	:= $(CURDIR)
CC 	:= gcc
AR 	:= ar
RANLIB 	:= ranlib
LDLIBS 	:= -lds -lrt
LDFLAGS := -L.
DEFINES :=
INCLUDE := -I../include/
CFLAGS 	:= -g -O3 $(DEFINES) $(INCLUDE)

OBJS_LIB:= time_measure.o
SRCS 	:=

TARGET_LIB := libds.a

TIME_MEASURE_TEST := time_measure_test
TARGET_BIN := $(TIME_MEASURE_TEST)

all : $(TARGET_LIB) $(TARGET_BIN)

$(TARGET_LIB) : $(OBJS_LIB)
	$(AR) rv $@ $?
	$(RANLIB) $@

$(TIME_MEASURE_TEST) : time_measure_test.o $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

*.o : ../include/ds.h

.PHONY : clean db
clean :
	$(RM) *.o *.out *.so *.a tags filenametags
	$(RM) $(TARGET_BIN)

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb