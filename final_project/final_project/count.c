#include "header.h"

linkHead* count_from_file(FILE* fp) {
	linkHead *head;
	linkData *data;
	bool duplicate_tag;  //在判断重复的时候用
	char ch[2];
	linkNode *p;
	head = create_link();
	while ((*ch = fgetc(fp)) != EOF)
	{
		//ch[0]<0就说明是汉字，就再读取一个字符。
		if (ch[0] < 0) {
			ch[1] = fgetc(fp);
		}
		else
		{
			ch[1] = '\0';
		}
		duplicate_tag = false;
		//判断是否重复
		while (data = foreach(head)) {
			//如果两字符串相等，说明重复了，则频数+1
			//注意这里不能用strcmp，strcmp会比较直到'\0'
			//if (0 == strcmp(data->ch, ch)) {
			if (0 == memcmp(data->ch,ch,2)) {
				data->cnt++;
				duplicate_tag = true;
				head->traverseTag = false;
				break;
			}
		}
		//如果这个字符之前还没有出现过，就append
		if (!duplicate_tag) {
			if (!(p = append(head, ch))) {
				//如果失败就提示并退出程序
				printf("统计过程出现错误，请重新运行");
				exit(0);
			}
			else {
				p->data.cnt++;
			}
		}
		head->cnt++;
	}

	//最后循环，改一下频率
	while (data = foreach(head)) {
		data->freq = (double)data->cnt / head->cnt;
	}

	return head;
}

void sort_link(linkHead* head) {

}