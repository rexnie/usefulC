#LDLIBS += -lm
main.out : main.o binsearch.o getword.o getch.o keytab.h
	$(CC) $^ $(LDLIBS) -o $@

binsearch.o main.o : keytab.h

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
