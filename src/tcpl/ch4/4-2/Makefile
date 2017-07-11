CFLAGS += -DTEST=1 -l m
LDFLAGS += -l m
#LDLIBS += m
atof.out : atof.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
