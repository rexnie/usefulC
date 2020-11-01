all:
	gcc nice_test.c -o nice_test.bin
	gcc getpriority_test.c -o getpriority_test.bin
	gcc sched_get_priority_min_test.c -o sched_get_priority_min_test.bin
	gcc sched_getscheduler_test.c -o sched_getscheduler_test.bin
	#gcc sched_getattr_test.c -o sched_getattr_test.bin
	gcc sched_deadline_test.c -o sched_deadline_test.bin -lpthread
	gcc sched_getattr_self_contain_test.c -o sched_getattr_self_contain_test.bin
	gcc nice_to_weight.c -o nice_to_weight.bin -lm

install:
	install ftrace ${HOME}/bin/

clean:
	rm -rf *.bin *.o

