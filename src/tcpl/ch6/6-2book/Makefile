#LDLIBS += -lm
main.out : main.o getword.o getch.o node.o
	$(CC) $^ $(LDLIBS) -o $@

node.o main.o : node.h

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
