#LDLIBS += -lm
binary_search.out : binary_search.o
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $@

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
