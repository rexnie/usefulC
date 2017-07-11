CFLAGS += -DTEST=1
binsearch.out : binsearch.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
