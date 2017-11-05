#include "header.h"

listNode* append_list(listHead *head, char ch[]) {
	listNode* p;
	p = (listNode*)malloc(sizeof(listNode));
	if (NULL == p) {
		return NULL;
	}

	if (head->tail) {  //原先的最后一个结点指向新结点
		head->tail->next = p;
	}
	else
	{//如果tail为空，说明length=0
		head->next = p;
	}

	head->tail = p;  //更改头部信息
	head->length++;

	p->next = NULL;  //初始化该结点信息
	memcpy(p->data.ch, ch, 2);
	//strcpy(p->data.ch, ch);
	p->data.cnt = 0;
	p->data.freq = 0;

	return p;  //成功则返回该结点指针
}

listHead* create_list(void) {
	listHead *head;
	head = (listHead*)malloc(sizeof(listHead));
	head->next = NULL;
	head->cnt = 0;
	head->curr = NULL;
	head->tail = NULL;
	head->length = 0;
	head->traverseTag = false;
	return head;
}

listData* foreach(listHead *head) {
	//如果长度为零，返回空
	if (!head->length) {
		return NULL;
	}

	//判断是否在循环进程中。
	listData *p;
	if (head->traverseTag) {
		//如果p是空的说明循环完毕
		if (NULL == head->curr) {
			head->traverseTag = false;
			head->curr = head->next;
			return NULL;
		}
		p = &(head->curr->data);
		head->curr = head->curr->next;
		return p;
	}
	else {
		head->traverseTag = true;
		head->curr = head->next;
		return foreach(head);
	}
}