#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cpufp_kernel_aarch64.h"

#define FMLA_FP32_COMP (0x10000000L)
static long long CPUFREQ = 3e9;

typedef void (*task_func_t)(int);

static double get_time(struct timespec *start, struct timespec *end)
{
	return end->tv_sec - start->tv_sec + (end->tv_nsec - start->tv_nsec) * 1e-9;
}

static long long get_freq(void) {
	FILE *fp = NULL;
	char buff[255];
	fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
	fgets(buff, 255, (FILE*)fp);
	unsigned long long ret = 1e3 * atoll(buff);
	fclose(fp);
	return ret;
}

double task_wrapper(task_func_t func, const long int loop_num) {
	struct timespec start, end;
	// warm up(pre heat)
	int warmup_loop = 1000;
	func(warmup_loop);
	// evaluate
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	func(loop_num);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	return get_time(&start, &end);
}

void cpufp_aarch64_fmla(int num_threads)
{
	double perf, cpi, time_used, latency;

	time_used = task_wrapper(cpu_fp32_cpi_kernel_aarch64, FMLA_FP32_COMP);
	perf = 8 * 32 * FMLA_FP32_COMP * num_threads / time_used * 1e-9;
	cpi = CPUFREQ * time_used / (32 * FMLA_FP32_COMP);
	time_used = task_wrapper(cpu_fp32_lat_kernel_aarch64, FMLA_FP32_COMP);
	latency = CPUFREQ * time_used / (32 * FMLA_FP32_COMP);
	printf("fmla fp32 perf: %.4lf gflops. cpi : %.4lf. latency : %.4lf.\n", perf, cpi, latency);
}

int main(int argc, char *argv[])
{
	int num_threads = 1;

	CPUFREQ = get_freq();
	double cpu_freq_d = CPUFREQ * 1e-9;
	printf("Thread(s): %d cpufreq(GHz) : %.2lf\n", num_threads, cpu_freq_d);
	cpufp_aarch64_fmla(num_threads);
	return 0;
}

