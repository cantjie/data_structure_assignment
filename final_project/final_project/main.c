#include "header.h"

void print_data(linkHead *head) {
	linkData *data;
	printf("×Ö·û\tÆµÊý\tÆµÂÊ\t\n");
	while (data = foreach(head)) {
		if (data->ch[0] < 0) {
			printf("%c%c\t", data->ch[0], data->ch[1]);
		}
		else
		{
			printf("%c\t", data->ch[0]);
		}
		printf("%d\t%lf\t\n", data->cnt, data->freq);
	}
}

int main() {
	linkHead *head;
	FILE *fp;
	linkData *data;
	linkNode *p;

	fp = fopen(FILE_NAME, "r");
	head = count(fp);
	print_data(head);

}
