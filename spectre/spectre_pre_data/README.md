GOAL: 
1. separate the front and back end of spectre attack
2. run front end and back end in different processes
3. write a script to
3.1 run each process
3.2 measure the perf output of each process
4. collect BTB-related counters
5. perform PCA to determine important events
5.1 R script?


ATTACK
VICTIM
ATTACK


NOTE:
another approach might be to
fork {front_end, victim, back_end} 
from the same program.
Perf can then follow each of them.
OR perf system calls might be used.


IDEA:
- put all variables into shared memory.
