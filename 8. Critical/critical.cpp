#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char** argv) {
	
	int n, m, critical_time = 0;
	int *degree;
	int *t_task;
	int *t_critical;
	
	queue<int> Q;
	vector< vector<int> > v;

	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");

	fscanf(input, "%d %d", &n, &m);

	degree = new int[n];
	t_task = new int[n];
	t_critical = new int[n];

	memset(degree, 0, sizeof(degree));
	memset(t_critical, 0, sizeof(t_critical));

	for (int i = 0; i < n; i++) {
		int t;
		fscanf(input, "%d", &t);
		t_task[i] = t;

		v.push_back(vector<int>());
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		fscanf(input, "%d %d", &a, &b);
		a--; b--;

		v[a].push_back(b);
		degree[b]++;
	}

	for (int i = 0; i < n; i++) {
		if (degree[i] == 0) {
			Q.push(i);
		}
	}

	for (;;) {
		if (Q.empty()) {
			break;
		}

		int task = Q.front();
		Q.pop();

		t_critical[task] += t_task[task];

		if (critical_time < t_critical[task]) {
			critical_time = t_critical[task];
		}

		for (int i = 0; i < v[task].size(); i++) {
			degree[v[task][i]]--;
			m--;

			if (t_critical[v[task][i]] < t_critical[task]) {
				t_critical[v[task][i]] = t_critical[task];
			}
			if (degree[v[task][i]] == 0) {
				Q.push(v[task][i]);
			}
		}		
	}

	if (m != 0) {
		fprintf(output, "-1\n");
	}
	else {
		fprintf(output, "%d\n", critical_time);
	}
	
	delete[] degree;
	delete[] t_task;
	delete[] t_critical;

	fclose(input);
	fclose(output);

	return 1;
}