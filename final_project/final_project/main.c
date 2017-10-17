#include "header.h"
#include<stdio.h>
#include<wchar.h>
//#include<string.h>
#include <locale.h>
int main() {
	setlocale(LC_ALL, "chs");
	wchar_t str[] = L"cantjie中文中文";
	printf("%ls\n", str);
	wchar_t wc = L'中';
	printf("%lc\n", wc);
}
