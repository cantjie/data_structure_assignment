// expVal.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>

double RPolishExpVal() {
	char str[50];
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

int main()
{
	//�沨�����ʽ��ֵReverse Polish expression
	printf("%f\n", RPolishExpVal());
	return 0;
}

