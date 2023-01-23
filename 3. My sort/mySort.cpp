#include <cstdio>
#include <chrono>


/////////////////////////////////////////////////
//////////////// YOUR PLAYGROUND ////////////////
/////////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <queue>

int get_min(int n, int* d) {

	int min = 0;
	
	for (int i = 0; i < n; i++) {
		if (min > d[i]) {
			min = d[i];
		}
	}

	return min;
}

int get_max(int n, int* d) {

	int max = 0;

	for (int i = 0; i < n; i++) {
		if (max < d[i]) {
			max = d[i];
		}
	}

	return max;
}


void merge(int* d, int _first, int _middle, int _last) {

	int n = _middle - _first + 1;
	int m = _last - _middle;
	int* L = new int[n];
	int* R = new int[m];

	for (int i = 0; i < n; i++) {
		L[i] = d[_first + i];
	}

	for (int j = 0; j < m; j++) {
		R[j] = d[_middle + 1 + j];
	}

	int i = 0;
	int j = 0;
	int k = _first;

	while (i < n && j < m) {
		if (L[i] <= R[j]) {
			d[k] = L[i];
			i++;
		}
		else {
			d[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n) {
		d[k] = L[i];
		i++;
		k++;
	}

	while (j < m) {
		d[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void merge_sort(int* d, int _first, int _last) {

	if (_first >= _last) {
		return;
	}

	int middle = _first + (_last - _first) / 2;

	merge_sort(d, _first, middle);
	merge_sort(d, middle + 1, _last);
	merge(d, _first, middle, _last);
}


int partition(int* d, int _first, int _last) {

	int index = d[_last];
	int i = (_first - 1);

	for (int j = _first; j <= _last - 1; j++) {

		if (d[j] < index) {
			i++;
			std::swap(d[i], d[j]);
		}

	}

	std::swap(d[i + 1], d[_last]);

	return (i + 1);
}

void quick_sort(int* d, int _first, int _last) {

	if (_first < _last)
	{
		int pivot = partition(d, _first, _last);

		quick_sort(d, _first, pivot - 1);
		quick_sort(d, pivot + 1, _last);
	}
}


void counting_sort(int n, int* d) {

	int* sorted_arr = new int[n];
	memset(sorted_arr, 0, sizeof(sorted_arr));

	int min = get_min(n, d);
	int max = 0;

	for (int i = 0; i < n; i++) {
		d[i] = d[i] - min;
	}

	for (int j = 0; j < n; j++) {
		if (max < d[j]) {
			max = d[j];
		}
	}

	int* count = new int[max + 1];
	memset(count, 0, sizeof(count));

	for (int i = 0; i < n; i++) {
		count[d[i]]++;
	}

	for (int i = 1; i <= max; i++) {
		count[i] += count[i - 1];
	}

	for (int i = 1; i <= max; i++) {
		for (int j = count[i - 1]; j < count[i]; j++) {
			sorted_arr[j] = i;
		}
	}

	for (int i = 0; i < n; i++) {
		d[i] = sorted_arr[i] + min;
	}

	delete[] sorted_arr;
	delete[] count;
}


int get_radix(int n, int* d) {

	int min = get_min(n, d);
	int max = 0;
	int radix = 1;

	for (int i = 0; i < n; i++) {
		d[i] = d[i] - min;
	}

	for (int j = 0; j < n; j++) {
		if (max < d[j]) {
			max = d[j];
		}
	}

	while (max / 10 > 0) {
		max /= 10;
		radix *= 10;
	}

	return radix;
}

void radix_sort(int n, int* d) {

	int radix = get_radix(n, d);
	int min = get_min(n, d);

	std::queue<int> Q[10];

	for (int i = 0; i < n; i++) {
		d[i] = d[i] - min;
	}

	for (int i = 1; i <= radix; i *= 10) {
		for (int j = 0; j < n; j++) {
			int k = 0;

			if (d[j] >= i) {
				k = (d[j] / i) % 10;
			}

			Q[k].push(d[j] + min);
		}

		int index = 0;

		for (int j = 0; j < 10; j++) {

			while (!Q[j].empty()) {

				d[index] = Q[j].front();
				Q[j].pop();

				index++;
			}
		}
	}
}


void MyVeryFastSort(int n, int* d) {

	int min = 0;
	int cnt = 0;
	int max = get_max(n, d);

	for (int i = 0; i < n; i++) {
		if (min > d[i]) {
			min = d[i];
			cnt++;
		}
	}

	int m = max - min;

	if (n >= m) {
		if (n * (int)log10(m) < (n + m)) {
			radix_sort(n, d);
		}
		else {
			counting_sort(n, d);
		}
	}

	else {
		if ((int)log10(m) <= (int)log2(n)) {
			if (n * (int)log10(m) < (n + m)) {
				radix_sort(n, d);
			}
			else {
				counting_sort(n, d);
			}
		}
		else {
			if (n * (int)log2(n) < (n + m)) {
				if (cnt > (int)(4 * n / 5)) {
					merge_sort(d, 0, n - 1);
				}
				else {
					quick_sort(d, 0, n - 1);
				}
			}
			else {
				counting_sort(n, d);
			}
		}
	}
}


/////////////////////////////////////////////////
/////////////////////////////////////////////////
/////////////////////////////////////////////////

// Utilized to check the correctness
bool Validate(int n, int* d)
{
	for (int i = 1; i < n; i++)
	{
		if (d[i - 1] > d[i])
		{
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "USAGE:  EXECUTABLE   INPUT_FILE_NAME   OUTPUT_FILE_NAME\n");
		return 1;
	}

	// Get input from a binary file whose name is provided from the command line
	int n, * d;
	FILE* input = fopen(argv[1], "rb");
	int e = fread(&n, sizeof(int), 1, input);
	d = new int[n];
	e = fread(d, sizeof(int), n, input);
	fclose(input);

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	// Call your sorting algorithm
	MyVeryFastSort(n, d);

	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	double res_time = elapsed_time.count();

	bool res_validate = Validate(n, d);

	// Write the results (corretness and time)
	FILE* output = fopen(argv[2], "w");
	if (res_validate) { fprintf(output, "OKAY\n"); printf("OKAY\n"); }
	else { fprintf(output, "WRONG\n"); printf("WRONG\n"); }
	fprintf(output, "%d\n", (int)res_time);
	printf("%d\n", (int)res_time);
	fclose(output);

	delete[] d;

	return 1;
}