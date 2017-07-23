#LDLIBS += -lm
#CFLAGS += -DTEST=1
test.out : test.o my_malloc.o
	$(CC) $^ $(LDLIBS) -o $@

test.o my_malloc.o : my_malloc.h

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
