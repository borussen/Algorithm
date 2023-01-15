#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

class Tree {
public :
	int n;  // # of nodes
	std::vector<int> *c; // store the indized of child nodes by vector
	 
	void Init(const char *_fileName) { //read tree from the input file
		FILE *input = fopen(_fileName, "r");
		fscanf(input, "%d", &n); // initialize the # of nodes
		c = new std::vector<int> [n]; // initialize allocate the memory for c
		for (int i = 0; i < n; i++) {  // iterate each line
			int tmp;
			while (true) {
				fscanf(input, "%d", &tmp);
				if (tmp == -1) {
					break;
				}
				c[i].push_back(tmp); // add child node
			}
		}
		fclose(input);
	}
};

void DFS(Tree &_t) {  // &_ is reference in cpp
	std::stack<int> s;  // define the stack
	s.push(0);  // push root index
	while (!s.empty()) {  // repeat until stack is not empty. If stack is empty, traversing is finished.
		int x = s.top(); // get the top of stack
		s.pop();  // remove the element of top
		printf("%d ", x);
		for (int i = _t.c[x].size() -1 ; i >= 0 ; i--) {
			s.push(_t.c[x][i]);
		}
	}
}
void BFS(Tree &_t) {
	std::queue<int> q;  // define the queue
	q.push(0);
	while (!q.empty()) {
		int x = q.front();  
		q.pop();
		printf("%d", x);
		for (int i = 0; i < (_t.c[x]).size(); i++) {
			q.push(_t.c[x][i]);
		}
	}
}

int main(int argc, char **argv) {
	
	Tree t;
	t.Init(argv[1]); // Tree initailized by file name from the command line
	printf("DFS Order:\n");
	DFS(t); 
	printf("BFS Order:\n");
	BFS(t);

	return 1;
}