all:
	gcc -g -pthread flamegraph_demo.c -o flamegraph_demo.bin
	gcc -g gdb_demo.c -o gdb_demo.bin
	gcc -g gdb_demo_var.c -o gdb_demo_var.bin

install:

clean:
	rm -rf *.bin *.o
	rm -rf out.perf-folded perf.data perf-kernel.svg

