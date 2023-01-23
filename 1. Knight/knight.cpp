#include <cstdio>
#include <vector>
#include <queue>

typedef std::pair<int, int> Pair;
typedef std::pair<int, Pair> PPair;

int BFS(int N, int s_y, int s_x, int e_y, int e_x) {

	const int mvY[] = { 2, 2, 1, -1, -2, -2, -1, 1 };
	const int mvX[] = { 1, -1, -2, -2, -1, 1, 2, 2 };

	int ans = 0;

	std::queue<PPair> Q;
	std::vector<std::vector<bool>> visit;
	visit.resize(N + 1);

	for (int i = 0; i < N; i++)
		visit[i].resize(N, false);

	Q.push({ 0, {s_y, s_x} });
	while (!Q.empty()) {
		int cnt = Q.front().first;
		int now_y = Q.front().second.first;
		int now_x = Q.front().second.second;
		Q.pop();

		if (now_y == e_y && now_x == e_x) {
			ans = cnt;
			return ans;
		}

		for (int i = 0 ; i < 8 ; i++) {
			int next_y = now_y + mvY[i];
			int next_x = now_x + mvX[i];

			if (next_y < 0 || next_x < 0 || next_y >= N || next_x >= N) {
				continue;
			}

			if (visit[next_y][next_x]) {
				continue;
			}

			visit[next_y][next_x] = true;
			Q.push({ cnt + 1, {next_y, next_x} });
		}
	}
	return -1;
}

int main(int argc, char** argv) {
	int N, s_y, s_x, e_y, e_x;

	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	fscanf(input, "%d%d%d%d%d", &N, &s_y, &s_x, &e_y, &e_x); 
	fprintf(output, "%d", BFS(N, s_y, s_x, e_y, e_x));

	fclose(input);
	fclose(output);

	return 0;
}