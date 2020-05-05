CC 	:= gcc
AR 	:= ar
RANLIB 	:= ranlib
LDLIBS 	:=
LDFLAGS :=
DEFINES :=
INC_DIR := .
INCLUDE := -I$(INC_DIR)
CFLAGS 	:= -ansi -g $(DEFINES) $(INCLUDE)
OBJS 	:=
SRCS 	:=
DEP_LIB :=

BIN_HELLO := hello.out
BIN_STRING_TABLE := string_table.out
BIN_STATIC_A := static_a.out
BIN_NO_SYMTAB := no_symtab.out
BIN_BSS_DEMO := bss_demo.out
BIN_REL := rel.bin
BIN_STATIC := static_bin.out
BIN_GEN_COREDUMP := gen_coredump.out

all : $(BIN_HELLO) $(BIN_STRING_TABLE) $(BIN_STATIC_A) $(BIN_NO_SYMTAB) \
	$(BIN_BSS_DEMO) $(BIN_REL) $(BIN_STATIC) $(BIN_GEN_COREDUMP)

$(BIN_HELLO) : hello.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN_STRING_TABLE) : string_table.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN_STATIC_A) : static_a.c b.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN_NO_SYMTAB) : no_symtab.c $(DEP_LIB)
	$(CC) -nostdlib $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	strip $@ -o $@.stripped

$(BIN_BSS_DEMO) : bss_demo.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN_REL) : obj1.c obj2.c $(DEP_LIB)
	$(CC) $(CFLAGS) -c $^ $(LDFLAGS) $(LDLIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	objdump -d obj1.o >obj1.o.dis
	objdump -d obj2.o >obj2.o.dis
	readelf -r obj1.o > obj1.o.rel
	readelf -r obj2.o > obj2.o.rel
	readelf -r $@ > $@.rel

$(BIN_STATIC) : static_bin.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BIN_GEN_COREDUMP) : gen_coredump.c $(DEP_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

.PHONY : clean

clean :
	$(RM) *.o *.out *.so *.a tags filenametags
