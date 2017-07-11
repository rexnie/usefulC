CFLAGS += -DTEST=1
bitcount.out : bitcount.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
