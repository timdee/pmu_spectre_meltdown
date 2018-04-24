#ifndef PMU_H
#define PMU_H

#define _GNU_SOURCE

#include <stdio.h>

// added for perf
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>


// INCLUDES FOR THIS
#include <sys/types.h>
#include <sys/syscall.h>


// true => perf
// false => direct PMU access
#define USE_PERF 1

#if USE_PERF
#else
//TODO type definitions conflict with PattYehPredictor
// included from track_pid/pmu-module/
#include "pmu-device2.h"
#include "pmc.h"
#include "pmuctl.h"
#endif

// included from patt_yeh_predictor/src/
//#include "PattYehPredictor.h"

// filename of kernel module character device
#define KERNEL_MODULE_DEVICE "../track_pid/pmu-module/PMU_DEVICE2_SWAMY"

// file descriptor for character device
// this device is used to read, configure pmu
static int file_desc;
static char *msg = "Message passed by ioctl\n";
static int read_buffer_size;

// read buffer used with perf (FOR TESTING)
#define READ_BUFFER_SIZE_MAX 10000
#define N_COUNTER 8 
static long long read_buffer[N_COUNTER][READ_BUFFER_SIZE_MAX];

// define methods to use pmu
// perf and direct access approaches will implement these methods
//
// enable the pmu
void enable_pmu();
// disable the pmu
void disable_pmu();
// start counters
void start_pmu();
// reset counters
void reset_pmu();
// stop counters
void stop_pmu();
// read counters -- the data is stored until log is called
void read_pmu();
// log the data which has been read
void log_pmu(char* file_name);

#endif
