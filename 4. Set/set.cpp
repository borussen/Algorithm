#include <cstdio>

class Disjoint_Set {
public:
	int *parent;

	Disjoint_Set() {}
	Disjoint_Set(int n) {
		
		parent = new int[n + 1];

		for (int i = 0; i < n + 1; i++) {
			parent[i] = i;
		}
	}
	~Disjoint_Set() { delete[] parent; }

	int Find_Set(int x) {
		while (parent[x] != x) {
			x = parent[x];
		}
		return x;
	}

	void Union_Set(int a, int b) {
		a = Find_Set(a);
		b = Find_Set(b);

		if (a != b) {
			parent[b] = a;
		}
	}

};

int main(int argc, char** argv) {

	int n, m;

	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");
	
	fscanf(input, "%d %d", &n, &m);
	Disjoint_Set s(n);

	for (int i = 0; i < m; i++) {
		
		int check, a, b;
		fscanf(input, "%d %d %d", &check, &a, &b);
		
		if (check == 0) {
			s.Union_Set(a, b);
		}

		else if (check == 1) {
			if (s.Find_Set(a) == s.Find_Set(b)) {
				fprintf(output, "Y\n");
			}
			else {
				fprintf(output, "N\n");
			}
		}

		else {
			fprintf(stderr, "Error!\n");
		}

	}

	fclose(input);
	fclose(output);

	return 1;
}