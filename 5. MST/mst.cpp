#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

template<typename WT>
class Graph {

public:
	int n, m;

	vector < pair<int, WT > > *edges;

	Graph() {}
	Graph(const char *file) {

		FILE *input = fopen(file, "r");
		fscanf(input, "%d %d", &n, &m);

		edges = new vector<pair<int, WT>>[n];

		for (int i = 0; i < m; i++) {
			int a, b;
			double c;

			fscanf(input, "%d %d %lf", &a, &b, &c);
			a--; b--;

			edges[a].push_back(make_pair(b, (WT)c));
			edges[b].push_back(make_pair(a, (WT)c));
		}

		fclose(input);
	}
};

template<typename WT>
WT Prim(Graph<WT> &g) {
	bool *visit = new bool[g.n];
	int *parent = new int[g.n];

	WT *dist = new WT[g.n];

	for (int i = 0; i < g.n; i++) {
		visit[i] = false;
		parent[i] = -1;
		dist[i] = numeric_limits<WT>::max() / (WT)2;
	}

	WT ret = (WT)0;
	int rootidx = 0;

	dist[rootidx] = (WT)0;
	parent[rootidx] = 0;

	priority_queue < pair<WT, int>, vector<pair<WT, int>>, greater<pair<WT, int>>> pq;
	pq.push(make_pair((WT)0, rootidx));

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
		ret += x.first;

		for (int i = 0; i < g.edges[x.second].size(); i++) {
			int idx = g.edges[x.second][i].first;
			WT w = g.edges[x.second][i].second;
			if (!visit[idx] && w < dist[idx]) {
				pq.push(make_pair(w, idx));
				parent[idx] = x.second;
				dist[idx] = w;
			}
		}
	}

	delete[] visit;
	delete[] parent;
	delete[] dist;

	return ret;
}

class Disjoint_Set {
public:
	int *parent;
	int *height;

	Disjoint_Set() {}
	Disjoint_Set(int n) {

		parent = new int[n];
		height = new int[n];

		for (int i = 0; i < n; i++) {
			parent[i] = i;
			height[i] = 0;
		}
	}
	~Disjoint_Set() { delete[] parent; delete[] height; }

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
			if (height[a] == height[b]) {
				parent[b] = a;
				height[a]++;
			}
			else if (height[a] > height[b]) {
				parent[b] = a;
			}
			else {
				parent[b] = a;
			}
		}
	}
};

template<typename WT>
WT Kruskal(Graph<WT> &g) {
	vector < pair<WT, pair<int, int>>> d;

	for (int i = 0; i < g.n; i++) {
		for (int j = 0; j < g.edges[i].size(); j++) {
			if (i < g.edges[i][j].first) {
				d.push_back(make_pair(g.edges[i][j].second, make_pair(i, g.edges[i][j].first)));
			}
		}
	}

	sort(d.begin(), d.end());

	Disjoint_Set s(g.n);
	WT ret = (WT)0;

	for (int i = 0; i < d.size(); i++) {
		int x = d[i].second.first;
		int y = d[i].second.second;
		WT w = d[i].first;

		if (s.Find_Set(x) != s.Find_Set(y)) {
			ret += w;
			s.Union_Set(x, y);
		}
	}

	return ret;
}


int main(int argc, char** argv) {

	long long int cost;
	Graph<long long int> g(argv[1]);

	FILE *output = fopen(argv[2], "w");

	if (g.n < g.m) {
		cost = Prim<long long int>(g);
	}
	else {
		cost = Kruskal<long long int>(g);
	}

	fprintf(output, "%lld\n", cost);
	fclose(output);
	
	return 1;
}