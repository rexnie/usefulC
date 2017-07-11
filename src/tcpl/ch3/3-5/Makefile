CFLAGS += -DTEST=1
itob.out : itob.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
