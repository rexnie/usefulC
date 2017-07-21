#LDLIBS += -lm
CFLAGS += -DTEST=1
minprintf.out : minprintf.o
	$(CC) $^ $(LDLIBS) -o $@

minprintf.o : minprintf.h

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
