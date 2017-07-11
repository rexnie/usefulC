CFLAGS += -DTEST=1
LDLIBS += -lm
atof.out : atof.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
