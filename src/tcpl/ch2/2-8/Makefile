CFLAGS += -DTEST=1
rightrot.out : rightrot.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
