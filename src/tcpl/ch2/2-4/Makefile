CFLAGS += -DTEST=1
squeeze.out : squeeze.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
