#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

template<typename WT>
class Graph {

public:
	int nV, nE;
	
	vector < pair<int, WT > > *edges;

	Graph() {}
	
	Graph(const char *_filename, int _type = 0) {

		if (_type == 0) {

			FILE* input = fopen(_filename, "r");
			fscanf(input, "%d", &nV);
			fscanf(input, "%d", &nE);
			edges = new vector<pair<int, WT>>[nV];

			for (int i = 0; i < nE; i++) {

				int vA, vB;
				double weight;

				fscanf(input, "%d %d %lf", &vA, &vB, &weight);
				vA--; vB--;

				edges[vA].push_back(make_pair(vB, (WT)weight));
				edges[vB].push_back(make_pair(vA, (WT)weight));
			}

			fclose(input);
		}

		else if (_type == 1) {
			
			FILE* input = fopen(_filename, "r");
			fscanf(input, "%d", &nV);
			fscanf(input, "%d", &nE);
			edges = new vector<pair<int, WT>>[nV];

			for (int i = 0; i < nE; i++) {

				char a, b;
				int vA = 0, vB = 0;
				double weight;

				fscanf(input, " %c %c %lf", &a, &b, &weight);
				vA = a - 'A';
				vB = b - 'A';

				edges[vA].push_back(make_pair(vB, (WT)weight));
				edges[vB].push_back(make_pair(vA, (WT)weight));
			}

			fclose(input);
		}
	}
};

template<typename WT>
void Dijkstra(Graph<WT>& _g, int start) {
	
	bool *visit = new bool[_g.nV];
	int *prev = new int[_g.nV];
	WT *dist = new WT[_g.nV];

	for (int i = 0; i < _g.nV; i++) {
		visit[i] = false;
		prev[i] = -1;
		dist[i] = numeric_limits<WT>::max() / (WT)2;
	}

	dist[start] = (WT)0;
	prev[start] = start;

	priority_queue < pair<WT, int>, vector<pair<WT, int>>, greater<pair<WT, int>>> pq;
	pq.push(make_pair((WT)0, start));

	for (;;) {
		if (pq.empty()) {
			break;
		}

		pair<WT, int> x = pq.top();
		pq.pop();

		if (visit[x.second]) {
			continue;
		}

		visit[x.second] = true;

		for (int i = 0; i < _g.edges[x.second].size(); i++) {
			
			int idx = _g.edges[x.second][i].first;
			WT w = _g.edges[x.second][i].second;

			if (!visit[idx] && dist[idx] > (dist[x.second] + w)) {
				pq.push(make_pair(dist[x.second] + w, idx));
				prev[idx] = x.second;
				dist[idx] = dist[x.second] + w;
			}
		}
	}

	printf("Idx\tv\tDist\tPrev\n");
	for (int i = 0; i < _g.nV; i++) {
		printf("%c\t%d\t%.2lf\t%c\n", i + 'A', (int)visit[i], (double)dist[i], prev[i] + 'A');
	}

	for (int i = 0; i < _g.nV; i++) {
		vector<int> p;
		p.push_back(i);
		while (true) {
			if (p[p.size() - 1] == start) {
				break;
			}
			p.push_back(prev[p[p.size() - 1]]);
		}
		printf("Path from %c to %c: ", start + 'A', i + 'A');
		for (int j = p.size() - 1; j >= 0; j--) {
			printf(" %c ", 'A' + p[j]);
		}
		printf("\n");
	}

	delete[] visit;
	delete[] prev;
	delete[] dist;
}



int main(int argc, char **argv) {

	Graph<int> g(argv[1], 1);

	Dijkstra<int>(g, 'K' - 'A');

	return 1;
}