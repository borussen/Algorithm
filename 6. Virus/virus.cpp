#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

template<typename WT>
class Graph {

public:
	
	int n, m, s;
	vector < pair<int, WT > > *edges;

	Graph() {}
	Graph(const char *file) {

		FILE *input = fopen(file, "r");

		fscanf(input, "%d %d %d", &n, &m, &s);
		s--;

		edges = new vector<pair<int, WT>>[n];

		for (int i = 0; i < m; i++) {
			
			int x, y;
			double t;

			fscanf(input, "%d %d %lf", &x, &y, &t);
			x--; y--;

			edges[y].push_back(make_pair(x, (WT)t));
		}

		fclose(input);
	}
};

template<typename WT>
void Dijkstra(Graph<WT> &g, int origin, const char *file) {
	
	bool *infected = new bool[g.n];
	WT *time = new WT[g.n];

	int n_infected = 0;
	int t_infected = 0;

	FILE *output = fopen(file, "w");

	for (int i = 0; i < g.n; i++) {
		infected[i] = false;
		time[i] = numeric_limits<WT>::max() / (WT)2;
	}

	time[origin] = (WT)0;

	priority_queue < pair<WT, int>, vector<pair<WT, int>>, greater<pair<WT, int>>> pq;
	pq.push(make_pair((WT)0, origin));

	for (;;) {
		if (pq.empty()) {
			break;
		}

		pair<WT, int> x = pq.top();
		pq.pop();

		if (infected[x.second]) {
			continue;
		}

		infected[x.second] = true;

		for (int i = 0; i < g.edges[x.second].size(); i++) {
			
			int idx = g.edges[x.second][i].first;
			WT w = g.edges[x.second][i].second;

			if (!infected[idx] && time[idx] > (time[x.second] + w)) {
				pq.push(make_pair(time[x.second] + w, idx));
				time[idx] = time[x.second] + w;
			}
		}
	}

	for (int i = 0; i < g.n; i++) {
		if (infected[i] == true) {
			n_infected++;
			if (t_infected < time[i]) {
				t_infected = time[i];
			}
		}
	}

	fprintf(output, "%d %d\n", n_infected, t_infected);
	fclose(output);

	delete[] infected;
	delete[] time;
}



int main(int argc, char **argv) {

	Graph<int> g(argv[1]);
	
	Dijkstra<int>(g, g.s, argv[2]);

	return 1;
}