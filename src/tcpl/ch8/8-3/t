#LDLIBS += -lm
#CFLAGS += -DTEST=1
stdio_.out : stdio_.o
	$(CC) $^ $(LDLIBS) -o $@

stdio_.o : stdio_.h

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
