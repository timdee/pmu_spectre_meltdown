CFLAGS = -std=c99 -ggdb

PROGRAM = main.out
SOURCE  = main.c simulated_work.c ../spectre_pre_data/pmu.c


all: $(PROGRAM) 
     
$(PROGRAM): $(SOURCE) simulated_work.h ../spectre_pre_data/pmu.h
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCE)

clean: ; rm -f $(PROGRAM)
