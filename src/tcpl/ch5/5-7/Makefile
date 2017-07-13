
CFLAGS += -g
all : str_sort_malloc.out str_sort_array.out
.PHONY : all

str_sort_malloc.out : str_sort_malloc.o
	$(CC) $(CFLAGS) $^ -o $@

str_sort_array.out : str_sort_array.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY : clean
clean :
	$(RM) *.o *.out
