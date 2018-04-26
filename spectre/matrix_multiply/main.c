#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
// functions for using perf or direct pmu system calls
#include "../spectre_pre_data/pmu.h"
// simulating matix multiply
#include "simulated_work.h"

#define LOG_FILE "log/log.csv"
#define ITERATIONS 100

int main(){
	srand(0);
	initialize_matrices();

	// PMU
	enable_pmu();
	start_pmu();	
	
	// MATRIX MULTIPLICATION / TRAMSPOSE
	for(int i=0;i<ITERATIONS;++i){
		reset_pmu();

		multiply();
		transpose();	

		read_pmu();
	}

	// PMU
	stop_pmu();
	disable_pmu();
	
	log_pmu(LOG_FILE);	

	return 0;
}
