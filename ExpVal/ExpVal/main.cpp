
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<string>
using namespace std;

double RPolishExpVal() {
	char str[20];
	scanf("%s", str);
	switch (str[0])
	{
	case '*': {return(RPolishExpVal() * RPolishExpVal()); break; }
	case '+': {return(RPolishExpVal() + RPolishExpVal()); break; }
	case '-': {return(RPolishExpVal() - RPolishExpVal()); break; }
	case '/': {return(RPolishExpVal() / RPolishExpVal()); break; }
	default:return atof(str);
	}
}


/*中缀表达式*/

double cal(char opt, double num1, double num2) {
	switch (opt)
	{
	case '+':
		return num1 + num2;
		break;
	case '-':
		return num1 - num2;
		break;
	case '*':
		return num1*num2;
		break;
	case '/':
		return num1 / num2;
		break;
	default:
		return 0;
		break;
	}
}

int getPriority(char opt) {
	{
		int priority;
		if (opt == ')')
			priority = 3;
		else if (opt == '*' || opt == '/')
			priority = 2;
		else if (opt == '+' || opt == '-')
			priority = 1;
		else if (opt == '(')
			priority = 0;
		return priority;
	}
}

float NormExpVal() {
	char exp[300];
	bool num_tag = 0;
	int curr = 0;
	int priority = 0;
	double result;
	double temp;
	double num1, num2;
	char opt;
	stack <double>NumStack;
	stack <char>OptStack;
	scanf("%s", exp);

	while (exp[curr] != '\0') {
		if ((exp[curr] >= 48 && exp[curr] <= 57) || exp[curr] == '.') {
			if (num_tag == 0) {
				temp = atof(exp + curr);
				num_tag = 1;
				NumStack.push(temp);
			}
		}
		else {
			if (getPriority(exp[curr]) == 3) {
				opt = OptStack.top();
				OptStack.pop();
				while (getPriority(opt) != 0) {
					num2 = NumStack.top();
					NumStack.pop();
					num1 = NumStack.top();
					NumStack.pop();
					temp = cal(opt, num1, num2);
					NumStack.push(temp);

					opt = OptStack.top();
					OptStack.pop();
				}
			}
			else {
				//getPriority(exp[curr]) == 0 
				if (!OptStack.empty()) {
					if (getPriority(exp[curr]) > getPriority(OptStack.top()) || exp[curr] == '(') {
						OptStack.push(exp[curr]);

					}
					else {
						opt = OptStack.top();
						OptStack.pop();
						num2 = NumStack.top();
						NumStack.pop();
						num1 = NumStack.top();
						NumStack.pop();
						temp = cal(opt, num1, num2);
						NumStack.push(temp);
						if (getPriority(exp[curr]) <= getPriority(OptStack.top())) {
							opt = OptStack.top();
							OptStack.pop();
							num2 = NumStack.top();
							NumStack.pop();
							num1 = NumStack.top();
							NumStack.pop();
							temp = cal(opt, num1, num2);
							NumStack.push(temp);
						}
						OptStack.push(exp[curr]);
					}
				}
				else {
					OptStack.push(exp[curr]);
				}
			}
			num_tag = 0;
		}
		curr++;
	}
	while (!OptStack.empty()) {
		opt = OptStack.top();
		OptStack.pop();
		num2 = NumStack.top();
		NumStack.pop();
		num1 = NumStack.top();
		NumStack.pop();
		temp = cal(opt, num1, num2);
		NumStack.push(temp);
	}
	return NumStack.top();

}


int main()
{
	//逆波兰表达式求值Reverse Polish expression

	//printf("%f\n", RPolishExpVal());

	//中缀表达式求值
	//http://bailian.openjudge.cn/practice/4132/
	double result;
	result = NormExpVal();
	printf("%.2lf", result);

	return 0;
}

