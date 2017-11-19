#include "header.h"

listNode* getMiddle(listNode* p);

listNode* mergelist(listNode* p1, listNode* p2, bool mode);

listNode* sortlist(listNode* p, bool mode);

listHead* count_from_file(char filename[]) {
	listHead *head;
	listData *data;
	FILE *fp;
	bool duplicate_tag;  //在判断重复的时候用
	char ch[2];
	listNode *p;

	fp = fopen(filename, "r");
	if (NULL == fp) {
		return NULL;
	}
	head = create_null_list();
	while ((*ch = fgetc(fp)) != EOF) {
		//ch[0]<0就说明是汉字，就再读取一个字符。
		if (ch[0] < 0) {
			ch[1] = fgetc(fp);
		}
		else {
			ch[1] = '\0';
		}
		duplicate_tag = false;
		//判断是否重复
		while (data = foreach_list(head)) {
			//如果两字符串相等，说明重复了，则频数+1
			//注意这里不能用strcmp，strcmp会比较直到'\0'
			//if (0 == strcmp(data->ch, ch)) {
			if (0 == memcmp(data->ch, ch, 2)) {
				data->cnt++;
				duplicate_tag = true;
				head->traverseTag = false;
				break;
			}
		}
		//如果这个字符之前还没有出现过，就append_list
		if (!duplicate_tag) {
			if (!(p = append_list(head, ch))) {
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
	fclose(fp);

	//最后增加一个表示结束的字符
	ch[0] = '\0'; ch[1] = '\0';
	if (!(p = append_list(head, ch))) {
		printf("统计过程出现错误，请重新运行");
		exit(0);
	}
	p->data.cnt = 0;
	head->length -= 1;

	//最后循环，改一下频率
	while (data = foreach_list(head)) {
		data->freq = (double)data->cnt / head->cnt;
	}

	return head;
}

void sort_list(listHead* head, bool mode) {
	head->next = sortlist(head->next, mode);
	while (head->tail->next)
	{
		head->tail = head->tail->next;
	}
}

//返回该链表的中间结点，如果是偶数个结点，返回中间偏左的结点
//@param listNode p 该链表第一个非头结点。
//@return listNode
listNode* getMiddle(listNode* p) {
	if (!(p && p->next)) return p;

	listNode *fast;
	listNode *slow;
	slow = p;
	fast = p->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

//合并两个排序好的链表，返回合并后的链表的第一个结点
//@param listNode p1
//@param listNode p2
//@param bool mode true表示增序，false表示降序
//@return listNode*
listNode* mergelist(listNode * p1, listNode * p2, bool mode)
{
	if (NULL == p1) return p2;
	if (NULL == p2) return p1;

	listNode* p;
	listNode* head;

	// 这里用两层判断写也可以，但看着太乱了。
	//现在这样做的缺点是不具有稳定性，但该工程对排序稳定性无要求
	if (p1->data.cnt < p2->data.cnt) {
		head = mode ? p1 : p2;
		mode ? (p1 = p1->next) : (p2 = p2->next);
	}
	else
	{
		head = mode ? p2 : p1;
		mode ? (p2 = p2->next) : (p1 = p1->next);
	}
	p = head;
	while (p1 && p2) {
		if (p1->data.cnt < p2->data.cnt) {
			p->next = mode ? p1 : p2;
			mode ? (p1 = p1->next) : (p2 = p2->next);
		}
		else {
			p->next = mode ? p2 : p1;
			mode ? (p2 = p2->next) : (p1 = p1->next);
		}
		p = p->next;
	}
	while (p2) {
		p->next = p2;
		p = p->next;
		p2 = p2->next;
	}
	while (p1) {
		p->next = p1;
		p = p->next;
		p1 = p1->next;
	}
	return head;
}

//归并排序，返回排序好的链表的第一个结点
//@param listNode p 链表第一个非头结点
//@param bool mode true表示增序，false表示降序
//@return listNode* 
listNode* sortlist(listNode * p, bool mode)
{
	if (!(p && p->next)) return p;  // 返回空或者这个唯一的结点

	listNode* middle = getMiddle(p);
	listNode* latter_part;
	if (middle) {
		latter_part = middle->next;
		middle->next = NULL;
	}
	return mergelist(sortlist(p, mode), sortlist(latter_part, mode), mode);
}
