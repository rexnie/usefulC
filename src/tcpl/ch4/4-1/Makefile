CFLAGS += -DTEST=1
strrindex.out : strrindex.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
