#include "header.h"

void print_data(linkHead *head) {
	linkData *data;
	printf("字符\t\t频数\t频率\t\n");
	while (data = foreach(head)) {
		if (data->ch[0] < 0) {
			printf("%c%c\t\t", data->ch[0], data->ch[1]);
		}
		else {
			if ((data->ch[0] <= 31 && data->ch[0] >= 0) || 127 == data->ch[0]) {
				printf("(ASCII:%d)\t", data->ch[0]);
			}
			else {
				printf("%c(ASCII:%d)\t", data->ch[0], data->ch[0]);
			}

		}
		printf("%d\t%lf\t\n", data->cnt, data->freq);
	}
	printf("共计%d个不同字符，共计%d个字符\n", head->length, head->cnt);
}