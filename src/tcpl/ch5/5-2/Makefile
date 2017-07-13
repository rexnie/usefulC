LDLIBS += -lm
getfloat.out : getfloat.o getch.o
	$(CC) $^ $(LDLIBS) -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
