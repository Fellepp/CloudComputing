seq: matrixMul_seq.cu matrix_common.cu matrix_common.h
	nvcc -o matrixMul_seq matrixMul_seq.cu matrix_common.cu

global: matrixMul_glo.cu matrix_common.cu matrix_common.h
	nvcc -o matrixMul_glo matrixMul_glo.cu matrix_common.cu

shared: matrixMul_shr.cu matrix_common.cu matrix_common.h
	nvcc -o matrixMul_shr matrixMul_shr.cu matrix_common.cu

all: shared global

clean:
	rm -f matrixMul_shr matrixMul_seq matrixMul_glo matrixMul.o* matrixMul.e*

