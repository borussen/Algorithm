#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>
#include <random>

using namespace std;

template<typename WT>
class Graph {

public:

	double **p;

	int nV, nE;

	vector < pair<int, WT > > *edges;

	Graph() {}

	Graph(int n) {

		nV = 1000;
		nE = 10000;

		p = new double *[nV];
		for (int i = 0; i < nV; i++) {
			p[i] = new double[2];
		}

		FILE* input = fopen("V.txt", "r");

		for (int i = 0; i < nV; i++) {
			fscanf(input, " %lf %lf\n", &p[i][0], &p[i][1]);
		}
		fclose(input);

		edges = new vector<pair<int, WT>>[nV];

		input = fopen("E.txt", "r");
		for (int i = 0; i < nE; i++) {
			int vA, vB;
			double dist;

			fscanf(input, " %d %d %lf\n", &vA, &vB, &dist);
			edges[vA].push_back(make_pair(vB, (WT)dist));
		}
		fclose(input);

	}
};

template<typename WT>
void Dijkstra(Graph<WT> &_g, int start = 0, int dest = 1) {
	FILE* output = fopen("edges_dijkstra.txt", "w");

	bool* visit = new bool[_g.nV];
	int* prev = new int[_g.nV];
	WT* dist = new WT[_g.nV];

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

		if (x.second == dest) {
			break;
		}

		for (int i = 0; i < _g.edges[x.second].size(); i++) {

			
			int idx = _g.edges[x.second][i].first;
			WT w = _g.edges[x.second][i].second;
			fprintf(output, "%d %d\n", x.second, idx);

			if (!visit[idx] && dist[idx] > (dist[x.second] + w)) {
				pq.push(make_pair(dist[x.second] + w, idx));
				prev[idx] = x.second;
				dist[idx] = dist[x.second] + w;
			}
		}
	}

	printf("Dist from (%lf,%lf) to (%lf,%lf) = %lf\n", _g.p[start][0], _g.p[start][1], _g.p[dest][0], _g.p[dest][1], dist[dest]);
	fclose(output);

	delete[] visit;
	delete[] prev;
	delete[] dist;
}

template<typename WT>
void AStar(Graph<WT> &_g, int start = 0, int dest = 1) {
	FILE* output = fopen("edges_astra.txt", "w");

	bool* visit = new bool[_g.nV];
	WT* dist = new WT[_g.nV];
	WT* w = new WT[_g.nV];
	WT* h = new WT[_g.nV];

	for (int i = 0; i < _g.nV; i++) {
		visit[i] = false;
		dist[i] = numeric_limits<WT>::max() / (WT)2;
		w[i] = numeric_limits<WT>::max() / (WT)2;
		
		h[i] = (_g.p[i][0] - _g.p[dest][0]) * (_g.p[i][0] - _g.p[dest][0]);
		h[i] += (_g.p[i][1] - _g.p[dest][1]) * (_g.p[i][1] - _g.p[dest][1]);
		h[i] = sqrt(h[i]);

	}

	dist[start] = (WT)0;
	w[start] = (WT)0;

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

		if (x.second == dest) {
			break;
		}

		for (int i = 0; i < _g.edges[x.second].size(); i++) {

			int idx = _g.edges[x.second][i].first;
			WT edge_weight = _g.edges[x.second][i].second;
			fprintf(output, "%d %d\n", x.second, idx);

			if (!visit[idx] && w[idx] > dist[x.second] + edge_weight +h[idx]) {
				dist[idx] = dist[x.second] + edge_weight;
				w[idx] = dist[x.second] + edge_weight + h[idx];
				pq.push(make_pair(w[idx], idx));
			}
		}
	}

	printf("Dist from (%lf,%lf) to (%lf,%lf) = %lf\n", _g.p[start][0], _g.p[start][1], _g.p[dest][0], _g.p[dest][1], dist[dest]);
	fclose(output);

	delete[] visit;
	delete[] dist;
}

void Generate_Map() {

	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<double> dist((double)0, (double)1);

	int nV = 1000;
	int nE = 10 * nV;

	pair<double, double>* p = new pair<double, double>[nV];
	p[0] = make_pair((double)0, (double)0);
	p[1] = make_pair((double)1, (double)1);

	for (int i = 2; i < nV; i++) {
		p[i] = make_pair(dist(gen), dist(gen));
	}

	FILE* output = fopen("V.txt", "w");
	for (int i = 0; i < nV; i++) {
		fprintf(output, "%lf\t%lf\n", p[i].first, p[i].second);
	}
	fclose(output);

	pair<double, int>* d = new pair<double, int>[nV];

	output = fopen("E.txt", "w");

	for (int i = 0; i < nV; i++) {
		for (int j = 0; j < nV; j++) {
			d[j].first = (p[i].first - p[j].first) * (p[i].first - p[j].first);
			d[j].first += (p[i].second - p[j].second) * (p[i].second - p[j].second);
			d[j].first = sqrt(d[j].first);
			d[j].second = j;
		}
		sort(&d[0], &d[nV]);
		for (int j = 1; j < 11; j++) {
			fprintf(output, "%d %d %lf\n", i, d[j].second, d[j].first);
			//if (i == 1) {
			//	fprintf(output, "%d %d %lf\n", d[j].second, i, d[j].first);
			//}
		}
	}
	fclose(output);
}

int main(int argc, char** argv) {

	Generate_Map();
	Graph<double> g(2);

	Dijkstra<double>(g);
	printf("\n");
	AStar<double>(g);

	return 1;
}