#include "pmu.h"

void log_pmu(char* file_name){
	FILE *file;
	int first;
	//pmc_value_t pmc;

	file=fopen(file_name,"w");

	// read counters by reading device
	// 	this retrieves the counter values stored in the kernel
	// 	they are retrieved in order
	for(int i=0; i<read_buffer_size; i++){
		first=1;
		for(int j=0; j<N_COUNTER; j++){
#if USE_PERF
			// print ,'s correctly
			if(first==1){
				first=0;
			}else{	
				fprintf(file,",");
			}
			// print the pmu counter values to the log file
			fprintf(file,"%lld",read_buffer[j][i]);
#else
		//fprintf(file,"%lld\n",read_buffer[i]);
		
		//TODO figure out why reading them all at the end doesn't work
		//	it works in other programs
		//	mabe kernel memory is getting cleared by something else?
		//	BUT that wouldn't explain why it works in PIN tool
		//read(file_desc, &pmc, sizeof(pmc_value_t));
		//print_pmc_file(stdout,&pmc);
		//print_pmc_file(file,&pmc);
#endif
		}
		fprintf(file,"\n");
	}

	fclose(file);
}

#if USE_PERF

// use perf to start,stop,read pmu
	
struct perf_event_attr pe;
int fd[N_COUNTER];

static long perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
		int cpu, int group_fd, unsigned long flags)
{
	int ret;

	ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
			group_fd, flags);
	return ret;
}

// CONFIGURATION REFERENCE
// http://man7.org/linux/man-pages/man2/perf_event_open.2.html
void enable_pmu(){
	// set all bytes of struct to 0
	memset(&pe, 0, sizeof(struct perf_event_attr));
	pe.size = sizeof(struct perf_event_attr);
	pe.disabled = 1;
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;
	

	// COUNTERS
	int c=0;
	
	// branches and instructions
	pe.type = PERF_TYPE_HARDWARE;
	pe.config = PERF_COUNT_HW_INSTRUCTIONS;
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	pe.type = PERF_TYPE_HARDWARE;
	pe.config = PERF_COUNT_HW_BRANCH_INSTRUCTIONS;
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	pe.type = PERF_TYPE_HARDWARE;
	pe.config = PERF_COUNT_HW_BRANCH_MISSES;
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);


	// cache
	pe.type = PERF_TYPE_HARDWARE;
	pe.config = PERF_COUNT_HW_CACHE_REFERENCES;
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);

	pe.type = PERF_TYPE_HARDWARE;
	pe.config = PERF_COUNT_HW_CACHE_MISSES;
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	// perhaps a simultaneous miss in all levels of cache
	// will tell us a flush is happening?
	/*
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_L1D | 
		(PERF_COUNT_HW_CACHE_OP_READ << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_L1D | 
		(PERF_COUNT_HW_CACHE_OP_READ << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_LL | 
		(PERF_COUNT_HW_CACHE_OP_READ << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_LL | 
		(PERF_COUNT_HW_CACHE_OP_READ << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	*/
	

	// timer
	pe.type = PERF_TYPE_SOFTWARE;
	pe.config = PERF_COUNT_SW_CPU_CLOCK;
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);


	// read, write, prefetch ACCESS
	/* NOT WORKING
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_BPU | 
		(PERF_COUNT_HW_CACHE_OP_WRITE << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	*/
	
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_BPU | 
		(PERF_COUNT_HW_CACHE_OP_READ << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	
	/* NOT WORKING
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_BPU | 
		(PERF_COUNT_HW_CACHE_OP_PREFETCH << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	*/
	

	// read, write, prefetch MISS
	/* NOT WORKING
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_BPU | 
		(PERF_COUNT_HW_CACHE_OP_WRITE << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	*/
	
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_BPU | 
		(PERF_COUNT_HW_CACHE_OP_READ << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);

	/* NOT WORKING
	pe.type = PERF_TYPE_HW_CACHE;
	pe.config = PERF_COUNT_HW_CACHE_BPU | 
		(PERF_COUNT_HW_CACHE_OP_PREFETCH << 8) | 
		(PERF_COUNT_HW_CACHE_RESULT_MISS << 16);
	fd[c++] = perf_event_open(&pe, 0, -1, -1, 0);
	*/
	
	for(int i=0; i<N_COUNTER; i++)
		if (fd[i] == -1) {
			fprintf(stderr, "Error opening leader %llx\n", pe.config);
			//exit(EXIT_FAILURE);
		}else{
			fprintf(stderr, "open success: %d\n", i);
		}
}
void disable_pmu(){
	for(int i=0; i<N_COUNTER; i++){
		if(fd[i]==-1) continue;
		close(fd[i]);	
	}
}
void start_pmu(){
	for(int i=0; i<N_COUNTER; i++){
		if(fd[i]==-1) continue;
		ioctl(fd[i], PERF_EVENT_IOC_RESET, 0);
		ioctl(fd[i], PERF_EVENT_IOC_ENABLE, 0);
	}
}
void reset_pmu(){
	for(int i=0; i<N_COUNTER; i++){
		if(fd[i]==-1) continue;
		ioctl(fd[i], PERF_EVENT_IOC_RESET, 0);
	}
}
void stop_pmu(){
	for(int i=0; i<N_COUNTER; i++){
		if(fd[i]==-1) continue;
		ioctl(fd[i], PERF_EVENT_IOC_DISABLE, 0);
	}
}
void read_pmu(){
	//TODO where to store the value of the read?
	//	the eventual logging will need to take place.
	//
	// Thinking ahead, the pyp will be trained upon a read
	// 	it doesn't make sence to spend a bunch of time on a complexe storage system
	// 	a staticly sized buffer may do the trick
	for(int i=0; i<N_COUNTER; i++){
		if(fd[i]==-1) *(read_buffer[i]+read_buffer_size)=0;
		else read(fd[i], read_buffer[i]+read_buffer_size, sizeof(long long));
	}
	//printf("%lld\n", read_buffer[read_buffer_size]);
	read_buffer_size++;
}



#else

// direct PMU access

void enable_pmu(){
}
void disable_pmu(){
}
void start_pmu(){
	file_desc = open(KERNEL_MODULE_DEVICE, 0);
	if (file_desc < 0) {
		printf("Can't open device file: %s\n", KERNEL_MODULE_DEVICE);
		exit(-1);
	}
	ioctl_start_counters(file_desc, msg);
	
	//printf("fd: %d\n",file_desc);
}
void stop_pmu(){
	ioctl_stop_counters(file_desc, msg);
	ioctl_stop_counters(file_desc, msg);
	close(file_desc);
}
void read_pmu(){
	// read the counters
	// the kernel will store the values
	ioctl_read_counters(file_desc, msg);
	
	// TODO figure out why
	// for some reason reading the coutners at the end doesn't work
	// 	but reading them immediatly does
	pmc_value_t pmc;
	read(file_desc, &pmc, sizeof(pmc_value_t));
	read_buffer[read_buffer_size]=pmc.fc0;	
	read_buffer_size++;
	
	// DEBUG
	//print_pmc_file(file,&pmc);
	//printf("%d\n",file_desc);
}

#endif


