#include "header.h"
#include<stdio.h>
#include<wchar.h>
//#include<string.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "chs");
	wchar_t str[] = L"cantjie��������";
	printf("%ls\n", str);
	wchar_t wc = L'��';
	printf("%lc\n", wc);
}
