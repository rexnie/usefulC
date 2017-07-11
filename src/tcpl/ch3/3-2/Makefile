CFLAGS += -DTEST=1
escape.out : escape.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
