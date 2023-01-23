#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

template<typename WT>
class Graph {

public:
	int **p;
	int nV, nE;
	vector < pair<int, WT > > *edges;

	Graph() {}
	Graph(int n = 0) {

		FILE *input = fopen("info.txt", "r");
		fscanf(input, " %d %d\n", &nV, &nE);
		fclose(input);

		p = new int *[nV];
		for (int i = 0; i < nV; i++) {
			p[i] = new int[2];
		}

		input = fopen("V.txt", "r");
		for (int i = 0; i < nV; i++) {
			fscanf(input, " %d %d\n", &p[i][0], &p[i][1]);
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

int Generate_Map(const char *file) {

	int nE = 0;
	int nV, G, x, y;

	FILE *input = fopen(file, "r");
	fscanf(input, " %d %d\n", &nV, &G);

	pair<int, int> *p = new pair<int, int>[nV + 1];
	p[0] = make_pair((int)0, (int)0);

	for (int i = 1; i < nV + 1; i++) {
		fscanf(input, " %d %d\n", &x, &y);
		p[i] = make_pair(x, y);
	}
	fclose(input);

	FILE *output = fopen("V.txt", "w");
	for (int i = 0; i < nV + 1; i++) {
		fprintf(output, "%d %d\n", p[i].first, p[i].second);
	}
	fclose(output);

	pair<double, int> *d = new pair<double, int>[nV + 1];

	output = fopen("E.txt", "w");
	for (int i = 0; i < nV + 1; i++) {
		for (int j = 0; j < nV + 1; j++) {
			if ((abs(p[i].first - p[j].first) <= 2) && (abs(p[i].second - p[j].second) <= 2) && (i != j)) {
				d[j].first = (p[i].first - p[j].first) * (p[i].first - p[j].first);
				d[j].first += (p[i].second - p[j].second) * (p[i].second - p[j].second);
				d[j].first = sqrt(d[j].first);
				d[j].second = j;
				nE++;

				fprintf(output, "%d %d %lf\n", i, d[j].second, d[j].first);
			}
		}
	}
	fclose(output);

	output = fopen("info.txt", "w");
	fprintf(output, "%d %d\n", nV + 1, nE);
	fclose(output);

	return G;
}

template<typename WT>
void AStar(const char *file, Graph<WT> &g, int start, int y_dest) {
	
	FILE *output = fopen(file, "w");
	
	double distance = numeric_limits<WT>::max() / (WT)2;

	for (int i = 0; i < g.nV; i++) {
		if (g.p[i][1] >= y_dest) {
			bool *visit = new bool[g.nV];
			WT *dist = new WT[g.nV];
			WT *w = new WT[g.nV];
			WT *h = new WT[g.nV];

			h[0] = (g.p[0][0] - g.p[i][0]) * (g.p[0][0] - g.p[0][0]);
			h[0] += (g.p[0][1] - g.p[i][1]) * (g.p[0][1] - g.p[i][1]);
			h[0] = sqrt(h[0]);

			if (h[0] >= distance) {
				continue;
			}

			for (int j = 0; j < g.nV; j++) {
				visit[j] = false;
				dist[j] = numeric_limits<WT>::max() / (WT)2;
				w[j] = numeric_limits<WT>::max() / (WT)2;

				h[j] = (g.p[j][0] - g.p[i][0]) * (g.p[j][0] - g.p[i][0]);
				h[j] += (g.p[j][1] - g.p[i][1]) * (g.p[j][1] - g.p[i][1]);
				h[j] = sqrt(h[j]);
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

				if (x.second == i) {
					break;
				}

				for (int i = 0; i < g.edges[x.second].size(); i++) {

					int idx = g.edges[x.second][i].first;
					WT edge_weight = g.edges[x.second][i].second;

					if (!visit[idx] && w[idx] > dist[x.second] + edge_weight + h[idx]) {
						dist[idx] = dist[x.second] + edge_weight;
						w[idx] = dist[x.second] + edge_weight + h[idx];
						pq.push(make_pair(w[idx], idx));
					}
				}
			}
			
			if (dist[i] < distance) {
				distance = dist[i];
			}

			delete[] visit;
			delete[] dist;
			delete[] w;
			delete[] h;
		}
	}

	int round_distance = round(distance);

	fprintf(output, "%d\n", round_distance);
	fclose(output);
}

int main(int argc, char** argv) {

	int y_goal = Generate_Map(argv[1]);
	
	Graph<double> g(0);

	AStar<double>(argv[2], g, 0, y_goal);

	return 1;
}