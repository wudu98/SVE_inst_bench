#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cpufp_kernel_aarch64.h"

#define FMLA_FP32_COMP (0x40000000L)
static double CPUFREQ;

typedef void (*task_func_t)(int);

static double get_time(struct timespec *start, struct timespec *end)
{
	return end->tv_sec - start->tv_sec + (end->tv_nsec - start->tv_nsec) * 1e-9;
}

static double get_freq(void) {
	FILE *fp = NULL;
	char buff[255];
	fp = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");
	fgets(buff, 255, (FILE*)fp);
	double ret = 1e3 * atoll(buff);
	fclose(fp);
	return ret;
}

static long long measuring_freq(task_func_t func) {
	struct timespec start, end;
	double time_used, cpu_freq_m;

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	func(FMLA_FP32_COMP);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	time_used = get_time(&start, &end);
	cpu_freq_m = (32 * FMLA_FP32_COMP) / time_used;
	return (long long)cpu_freq_m;
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
	double perf, cpi, throughput, time_used, latency;

	time_used = task_wrapper(cpu_fp32_cpi_kernel_aarch64, FMLA_FP32_COMP);
	perf = 1.0 * 8 * 32 * FMLA_FP32_COMP * num_threads / time_used * 1e-9;
	cpi = CPUFREQ * time_used / (32 * FMLA_FP32_COMP);
	throughput = 1.0 / cpi;
	time_used = task_wrapper(cpu_fp32_lat_kernel_aarch64, FMLA_FP32_COMP);
	latency = CPUFREQ * time_used / (32 * FMLA_FP32_COMP);
	printf("fmla fp32 perf: %.4lf gflops. latency : %.4lf. cpi : %.4lf. throughput : %.4lf.\n", perf, latency, cpi, throughput);
}

int main(int argc, char *argv[])
{
	int num_threads = 1;

	CPUFREQ = measuring_freq(cpu_neon_int_add_lat);
	double cpu_freq_measure = CPUFREQ * 1e-9;
	double cpu_freq_max = get_freq() * 1e-9;
	
	printf("Thread(s): %d | measure cpufreq(GHz) : %.2lf | max cpufreq(GHz) : %.2lf\n", num_threads, cpu_freq_measure, cpu_freq_max);
	cpufp_aarch64_fmla(num_threads);
	return 0;
}

