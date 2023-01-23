#include <cstdio>
#include <chrono>

/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////


// You are NOT ALLOWED to add any header file

class Queue {
private:
	const int max = 100000000;
	int *q = new int[max];
	int index_front;
	int index_rear;

public:
	Queue() {
		index_front = 0;
		index_rear = 0;
	}
	bool empty() {
		return index_front == index_rear;
	}
	void push(int x) {
		index_rear = (index_rear + 1) % max;
		q[index_rear] = x;
	}
	void pop() {
		index_front = (index_front + 1) % max;
	}
	int front() {
		return q[(index_front + 1) % max];
	}
};

int get_min(int N, int *data) {

	int min = 0;

	for (int i = 0; i < N; i++) {
		if (min > data[i]) {
			min = data[i];
		}
	}

	return min;
}

int get_max(int N, int *data) {

	int max = 0;

	for (int i = 0; i < N; i++) {
		if (max < data[i]) {
			max = data[i];
		}
	}

	return max;
}

void counting_sort(int N, int *data) {

	int *sorted_arr = new int[N];
	int max = get_max(N, data);

	for (int i = 0; i < N; i++) {
		sorted_arr[i] = 0;
	}

	int *count = new int[max + 1];

	for (int i = 0; i < max + 1; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		count[data[i]]++;
	}

	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	for (int i = 1; i <= max; i++) {
		for (int j = count[i - 1]; j < count[i]; j++) {
			sorted_arr[j] = i;
		}
	}

	for (int i = 0; i < N; i++) {
		data[i] = sorted_arr[i];
	}

	delete[] sorted_arr;
	delete[] count;
}

int get_radix(int N, int *data) {

	int max = get_max(N, data);
	int radix = 1;

	while (max / 10 > 0) {
		max /= 10;
		radix *= 10;
	}

	return radix;
}

void radix_sort(int N, int *data) {

	int radix = get_radix(N, data);
	Queue Q[10];

	for (int i = 1; i <= radix; i *= 10) {
		for (int j = 0; j < N; j++) {
			int k = 0;

			if (data[j] >= i) {
				k = (data[j] / i) % 10;
			}

			Q[k].push(data[j]);
		}

		int index = 0;

		for (int j = 0; j < 10; j++) {

			while (!Q[j].empty()) {

				data[index] = Q[j].front();
				Q[j].pop();

				index++;
			}
		}
	}
}

void Find_K_Smallest(int N, int *data, int K, int *result)
{
	int min = get_min(N, data);
	int max = get_max(N, data);
	int m = max - min;

	if (N >= m) {
		if (m <= 10) {
			radix_sort(N, data);
		}
		else {
			counting_sort(N, data);
		}
	}

	else {
		if (m < 10000000) {
			if ((int)(m / N) > 5) {
				radix_sort(N, data);
			}
			else {
				counting_sort(N, data);
			}
		}
		else {
			if ((int)(m / N) > 6) {
				radix_sort(N, data);
			}
			else {
				counting_sort(N, data);
			}
		}
	}

	for(int i = 0;i < K;i++) {
		result[i] = data[i];
	}
}


/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
	}

	// Get input from a binary file whose name is provided from the command line
	int N, K, * data, * result;
	FILE* input = fopen(argv[1], "rb");
	int e = fread(&N, sizeof(int), 1, input);
	e = fread(&K, sizeof(int), 1, input);
	data = new int[N];
	e = fread(data, sizeof(int), N, input);
	fclose(input);

	result = new int[K];

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	// Call your function
	Find_K_Smallest(N, data, K, result);

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	// Write the results
	FILE* output = fopen(argv[2], "w");
	fprintf(output, "%d\n", K);
	for (int i = 0; i < K; i++)
	{
		fprintf(output, "%d ", result[i]);
	}
	fprintf(output, "\n%d\n", (int)res_time);
	fclose(output);

	delete[] data;
	delete[] result;

	return 1;
}