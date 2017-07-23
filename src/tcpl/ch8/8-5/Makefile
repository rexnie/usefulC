#LDLIBS += -lm
#CFLAGS += -DTEST=1
fsize.out : fsize.o
	$(CC) $^ $(LDLIBS) -o $@

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
