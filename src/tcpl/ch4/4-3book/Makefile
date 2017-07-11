CFLAGS += -DTEST=1
LDLIBS += -lm
OBJS = stack.o getch.o getop.o main.o
calc.out : $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJS) : calc.h
.PHONY : clean
clean :
	$(RM) *.o *.out
