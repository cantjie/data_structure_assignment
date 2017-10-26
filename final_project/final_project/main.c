#include "header.h"

void print_data(linkHead *head) {
	linkData *data;
	printf("×Ö·û\t\tÆµÊý\tÆµÂÊ\t");
	while (data = foreach(head)) {
		if (data->ch[0] < 0) {
			printf("%c%c\t\t", data->ch[0], data->ch[1]);
		}
		else
		{
			printf("%c(ASCII:%d)\t", data->ch[0], data->ch[0]);
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
	head = count_from_file(fp);
	fclose(fp);
	print_data(head);

}
