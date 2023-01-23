#include <cstdio>
#include <vector>
#include <stack>

struct Op {
	int lev;
	char oper;
};

void Calc(std::stack<double>* numSt, std::stack<Op>* opSt) {
	double a = -1, b = -1, res = 0;
	char oper = 0;

	a = numSt->top();
	numSt->pop();
	
	b = numSt->top();
	numSt->pop();
	
	oper = opSt->top().oper;
	opSt->pop();
	
	if (oper == '*')
		res = b * a;
	else if (oper == '/')
		res = b / a;
	else if (oper == '+')
		res = b + a;
	else if (oper == '-')
		res = b - a;
	numSt->push(res);
}

int main(int argc, char** argv) {
	const int MAX = 105;

	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

	char expr[MAX];
	std::stack<double>* numSt = new std::stack<double>;
	std::stack<Op>* opSt = new std::stack<Op>;
	int tmp = -1;
	
	fscanf(input, "%s", expr);

	for (int i = 0 ; expr[i] ; i++) {
		if (tmp != -1 && !('0' <= expr[i] && expr[i] <= '9')) {
			numSt->push(tmp);
			tmp = -1;
		}

		if (expr[i] == '(') {
			opSt->push({ 0, '(' });
		}

		else if (expr[i] == ')') {
			while (!opSt->empty() && opSt->top().lev != 0)
				Calc(numSt, opSt);
			opSt->pop();
		}

		else if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '-') {
			int lev;

			if (expr[i] == '*' || expr[i] == '/') {
				lev = 2;
			}
			else {
				lev = 1;
			}

			while (!opSt->empty() && lev <= opSt->top().lev) {
				Calc(numSt, opSt);
			}

			opSt->push({ lev, expr[i] });
		}

		else {
			if (tmp == -1) {
				tmp = 0;
			}

			tmp = tmp * 10 + (expr[i] - '0');
			
			if (!expr[i + 1]) {
				numSt->push(tmp);
			}
		}
	}
	
	while (!opSt->empty()) {
		Calc(numSt, opSt);
	}

	fprintf(output, "%.2f\n", numSt->top());

	fclose(input);
	fclose(output);

	return 0;
}