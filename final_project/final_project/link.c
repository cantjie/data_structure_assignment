#include "header.h"

int append(linkHead *head, char ch){
	linkNode* p;
	p = (linkNode*)malloc(sizeof(linkNode));
	if (p == NULL) {
		return 0;
	}
	
	if (head->tail) {  //原先的最后一个节点指向新节点
		head->tail->next = p;
	}
	
	head->tail = p;  //更改头部信息
	head->length++;

	p->next = NULL;  //初始化该节点信息
	p->data.ch = ch;
	p->data.cnt = 0;
	p->data.freq = 0;

	return 1;  //返回1表示成功
}

linkHead* create_link(void) {
	linkHead *head;
	head = (linkHead*)malloc(sizeof(linkHead));
	head->next = NULL;
	head->cnt = 0;
	head->curr = NULL;
	head->tail = NULL;
	head->length = 0;
	return head;
}