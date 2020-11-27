#!/bin/sh
# run with root

# git clone https://github.com/brendangregg/FlameGraph
TOOL=$HOME/work/tools/FlameGraph

perf record -F 99 -a -g -- sleep 60

perf script | $TOOL/stackcollapse-perf.pl > out.perf-folded

$TOOL/flamegraph.pl out.perf-folded > perf-kernel.svg
