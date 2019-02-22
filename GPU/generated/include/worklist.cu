__global__ void __worklist_initialize__(int size, int count, int *arr) {
	int id = threadIdx.x * blockDim.y + threadIdx.y;
	if(id < size) {
		int n = max((id+1)*count, size);
		for(int i=id*count; i<n; ++i) {
			arr[i] = i;
		}
	}
}


class Worklist
{
private:
	int *in, *out;
	int inSize;
	int outSize;
	int arrSize;

	__host__ bool allocate(int sz) {
		arrSize = sz;
		if(cudaMalloc((void**)&in, sizeof(int)*sz) != cudaSuccess) {
			return false;
		}
		return cudaMalloc((void**)&out, sizeof(int)*sz) == cudaSuccess;
	}

	__host__ void initialize(int size) {
		// launch kernel
		cudaDeviceSynchronize();
		inSize = size;
		outSize = 0;
	}

public:
	__host__ Worklist(int npoints, int nedges) {
		if(!allocate(nedges)) {
			fprintf(stderr, "ERROR: %s\n", "Memory allocation error @Worklist");
		}
		initialize(npoints);
		insize = npoints
	}

	__device__ void push(int val) {
		int i = atomicAdd(&outSize, 1);
		out[i] = val;
	}

	__device__ int get(int pos) {
		return in[pos];
	}

	__device__ int get() {
		int i = atomicAdd(&inSize, 1);
		return in[i];
	}

	__host__ void swap() {
		// launch compute kernel
		inSize = outSize;
		outSize = 0;
		int *temp = in;
		in = out;
		out = temp;
	}

	~Worklist() {
	#ifndef __CUDA_ARCH__
		cudaFree(in);
		cudaFree(out);
	#endif
	}
};