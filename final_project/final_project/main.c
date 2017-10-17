#include "header.h"

//#include <locale.h>

int main() {
	linkHead *head;
	head = create_link();

	FILE *fp;
	fp = fopen(FILE_NAME, "r");
	char ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		printf("%c", ch);
		if (!append(head, ch)) {
			printf("Ê§°Ü£¡");
		}
	}
}