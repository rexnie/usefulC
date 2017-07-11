CFLAGS += -DTEST=1

itob.out : itob.o stack.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

stack.o : stack.h
itob.o : stack.h

.PHONY : clean
clean :
	$(RM) *.o *.out
