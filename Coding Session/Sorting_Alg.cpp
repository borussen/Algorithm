#include <cstdio>
#include <cstdlib>
#include <random>
#include <chrono> // allow us to measure the execution time
#include <algorithm>

# define NUM_THRESHOLD 6

// a.exe #-of-elements  sort-method  (recieve two additional parameters)

template <typename Type>
void Insertion_Sort(Type* _array, int _n)
{
	for (int i = 1; i < _n; i++)
	{
		for (int j = i; j > 0; j‐‐)
		{
			if (_array[j‐1] > _array[j])
			{
				std::swap(_array[j‐1], _array[j]);
			}
			else
			{
				break;
			}
		}
	}
}

template <typename Type>
void Insertion_Sort_without_Swap(Type* _array, int _n)
{
	for (int i = 1; i < _n; i++)
	{
		Type tmp = _array[i];
		for (int j = i; j > 0; j‐‐)
		{
			if (_array[j‐1] > tmp)
			{
				_array[j] = _array[j ‐ 1];
			}
			else
			{
				_array[j] = tmp;
				break;
			}
		}
		if (_array[0] > tmp)
		{
			_array[0] = tmp;
		}
	}
}

template <typename Type>
bool Is_Sorted(Type* _array, int _n) {
	for (int i = 1; i < _n; i++) {
		if (_array[i - 1] > _array[i]) {
			return false;
		}
	}
	return true;
}

template<typename Type>
void Merge(Type* _arrayA, Type* _arrayB, int _nA, int _nB, Type* _arrayOut)
{
	int posA = 0, posB = 0, k = 0;
	while (posA < _nA && posB < _nB)
	{
		if (_arrayA[posA] < _arrayB[posB])
		{
			_arrayOut[k] = _arrayA[posA];
			posA++;
		}
		else
		{
			_arrayOut[k] = _arrayB[posB];
			posB++;
		}
		k++;
	}
	for (; posA < _nA; posA++)
	{
		_arrayOut[k] = _arrayA[posA];
		k++;
	}
	for (; posB < _nB; posB++)
	{
		_arrayOut[k] = _arrayB[posB];
		k++;
	}
}

template<typename Type>
void Merge_Sort(Type* _array, int _first, int _last)
{
	if ( _last ‐ _first <= NUM_THRESHOLD)
	{
		//Insertion_Sort_without_Swap<Type>(_array, _first, _last);
		Insertion_Sort_without_Swap<Type>(&_array[_first], _last - _first);
	}
	else
	{
		int midpoint = (_first + _last) / 2;
		Merge_Sort<Type>(_array, _first, midpoint);
		Merge_Sort<Type>(_array, midpoint, _last);
		//Merge(_array, _first, midpoint, _last);
		Merge<Type>(&_array[_first], &_array[midpoint], midpoint - _first, _last - midpoint, tmp);
		for (int i = 0; i < _last - _first; i++) {
			_array[_first + i] = tmp[i];
		}
		delete[] tmp;
	}
}

int main(int argc, char **argv) {

	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<int> dist(0, 10 * 1000 * 1000);

	int N = atoi( argv[1] ); 
	printf("N = %d\n", N);
	int *data = new int[N];// define data as array size N based on dynamic memory allocation
	
	//printf("Data\n");
	for (int i = 0; i < N; i++) {
		data[i] = dist(gen);
		//printf("%10d\n", data[i]);
	}

	std::chrono::time_point<std::chrono::system_clock> stTime = std::chrono::system_clock::now();

	if (strcmp(argv[2], "insertion") == 0) {
		Insertion_Sort<int>(data, N);
	}
	else if (strcmp(argv[2], "insertion_without_swap") == 0) {
		Insertion_Sort_without_Swap<int>(data, N);
	}
	else if (strcmp(argv[2], "std") == 0) {
		std::sort(&(data[0]), &(data[N]));
	}
	else {}
	
	std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();
	std::chrono::milliseconds timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - stTime);

	bool isCorrect = Is_Sorted<int>(data, N);
	if (isCorrect) {
		printf("Correct!\n");
	}
	else {
		printf("Wrong!\n");
	}

	double T = timeDiff.count();
	printf("Runtime = %d ms\n", (int)T);




	//printf("Sorted\n");
	//for (int i = 0; i < N; i++) {
		//printf("%10d\n", data[i]);
	//}
	return 1;
	
}