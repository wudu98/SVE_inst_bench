.PHONY : all

# CC = fcc
CC = gcc
C_FLAGS = -O3
LD_FLAGS = -O3 -pthread

all: 
	$(CC) -c cpu_neon_fp64_add_lat.s -o cpu_neon_fp64_add_lat.o
	$(CC) -c cpu_fp_cpi_kernel_aarch64.s -o cpu_fp_cpi_kernel_aarch64.o
	$(CC) -c cpu_fp_lat_kernel_aarch64.s -o cpu_fp_lat_kernel_aarch64.o
	$(CC) $(C_FLAGS) -c cpufp_aarch64.c -o cpufp_aarch64.o
	$(CC) $(LD_FLAGS) -o cpufp cpufp_aarch64.o cpu_fp_cpi_kernel_aarch64.o cpu_fp_lat_kernel_aarch64.o

clean:
	rm -rf cpufp *.o