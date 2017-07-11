CFLAGS += -DTEST=1
setbits.out : setbits.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
