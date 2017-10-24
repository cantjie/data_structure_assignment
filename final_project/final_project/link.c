#include "header.h"

linkNode* append(linkHead *head, char ch[]){
	linkNode* p;
	p = (linkNode*)malloc(sizeof(linkNode));
	if (NULL == p) {
		return NULL;
	}
	
	if (head->tail) {  //原先的最后一个节点指向新节点
		head->tail->next = p;
	}
	else
	{//如果tail为空，说明length=0
		head->next = p;
	}

	head->tail = p;  //更改头部信息
	head->length++;

	p->next = NULL;  //初始化该节点信息
	strcpy(p->data.ch, ch);
	p->data.cnt = 0;
	p->data.freq = 0;

	return p;  //成功则返回该节点指针
}

linkHead* create_link(void) {
	linkHead *head;
	head = (linkHead*)malloc(sizeof(linkHead));
	head->next = NULL;
	head->cnt = 0;
	head->curr = NULL;
	head->tail = NULL;
	head->length = 0;
	head->traverseTag = false;
	return head;
}

linkData* foreach(linkHead *head) {
	//如果长度为零，返回空
	if (!head->length) {
		return NULL;
	}

	//判断是否在循环进程中。
	linkData *p;
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
	else{
		head->traverseTag = true;
		head->curr = head->next;
		return foreach(head);
	}
}