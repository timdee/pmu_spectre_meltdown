#! /bin/bash


# GATHER BTB-related PMU events for
# front end
# back end
# victim
# USING perf command line


# USEFUL PERF FLAGS
# -I msecs, --interval-print msecs
#	Print count deltas every N milliseconds (minimum: 100ms) example: perf stat -I 1000 -e cycles -a sleep 5
#
# -o file, --output file
#	Print the output into the designated file.
#
# -r, --repeat=<n>
#	repeat command and print average + stddev (max: 100). 0 means forever.

# perf -e counters
#TODO make these BTB-related (all 5 counters)
COUNTERS="-e branch-misses"
FLAGS="-d -d -d"

#TODO how to run them simultaneously?
perf stat $FLAGS $COUNTERS ./front_end.out
perf stat $FLAGS $COUNTERS ./back_end.out
perf stat $FLAGS $COUNTERS ./victim.out
