all:
	gcc nice_test.c -o nice_test.bin
	gcc getpriority_test.c -o getpriority_test.bin
	gcc sched_get_priority_min_test.c -o sched_get_priority_min_test.bin
	gcc sched_getscheduler_test.c -o sched_getscheduler_test.bin
	#gcc sched_getattr_test.c -o sched_getattr_test.bin

install:
	install ftrace ${HOME}/bin/

clean:
	rm -rf *.bin *.o

