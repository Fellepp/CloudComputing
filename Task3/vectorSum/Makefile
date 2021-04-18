cpu: vectorSum_cpu.cu
	nvcc -o vectorSum_cpu  vectorSum_cpu.cu

gpu: vectorSum_gpu.cu
	nvcc -o vectorSum_gpu vectorSum_gpu.cu

long: vectorSum_gpu_long.cu
	nvcc -o vectorSum_gpu_long vectorSum_gpu_long.cu

all: cpu gpu long

clean:
	rm -f vectorSum_cpu vectorSum_gpu vectorSum_gpu_long gpu_job.o* gpu_job.e*

