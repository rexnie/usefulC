WKDIR 	:= $(CURDIR)
CC 	:= gcc
AR 	:= ar
RANLIB 	:= ranlib
LDLIBS 	:= -lds -lrt
LDFLAGS := -L.
DEFINES :=
INCLUDE := -I../include/
CFLAGS 	:= -g -O3 $(DEFINES) $(INCLUDE)
INC_DIR := ../include

OBJS_LIB:= time_measure.o num_seq.o binary_search.o shell_sort.o misc.o linked_list.o \
	stack_array.o getch.o queue.o binary_search_tree.o
SRCS 	:=

TARGET_LIB := libds.a

TIME_MEASURE_TEST := time_measure_test.out
NUM_SEQ_TEST := num_seq_test.out
TARGET_BIN := $(TIME_MEASURE_TEST) $(NUM_SEQ_TEST)

all : $(TARGET_LIB) $(TARGET_BIN)

$(TARGET_LIB) : $(OBJS_LIB)
	$(AR) rv $@ $?
	$(RANLIB) $@

$(TIME_MEASURE_TEST) : time_measure_test.o $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(NUM_SEQ_TEST) : num_seq_test.o $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

*.o : $(INC_DIR)/ds.h

time_measure.o : $(INC_DIR)/time_measure.h
num_seq.o : $(INC_DIR)/num_seq.h
binary_search.o : $(INC_DIR)/binary_search.h
shell_sort.o : $(INC_DIR)/shell_sort.h
misc.o : $(INC_DIR)/misc.h
linked_list.o : $(INC_DIR)/linked_list.h
stack_array.o : $(INC_DIR)/stack_array.h
getch.o : $(INC_DIR)/getch.h
queue.o : $(INC_DIR)/queue.h
binary_search_tree.o : $(INC_DIR)/binary_search_tree.h

.PHONY : clean db
clean :
	$(RM) *.o *.out *.so *.a tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
