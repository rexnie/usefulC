LDLIBS += -lm
expr.out : expr.o stack.o
	$(CC) $^ $(LDLIBS) -o $@

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
