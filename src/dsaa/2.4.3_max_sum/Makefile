#LDLIBS += -lm

# 定义其中一个宏选择测试算法
#CFLAGS += -DCubicAlgorithm
CFLAGS += -DQuadraticAlgorithm
#CFLAGS += -DNlogNAlgorithm
#CFLAGS += -DLinearAlgorithm
max_sum.out : max_sum.o
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $@

.PHONY : clean db
clean :
	$(RM) *.o *.out tags filenametags

db :
	./mk_ctags.sh
	./mk_tags4_lookupfile.sh
	cscope -Rqb
