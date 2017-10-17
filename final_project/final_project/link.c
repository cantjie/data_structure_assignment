#include "header.h"

int append(linkHead *head, char ch){
	linkNode* p;
	p = (linkNode*)malloc(sizeof(linkNode));
	if (p == NULL) {
		return 0;
	}
	
	if (head->tail) {  //ԭ�ȵ����һ���ڵ�ָ���½ڵ�
		head->tail->next = p;
	}
	
	head->tail = p;  //����ͷ����Ϣ
	head->length++;

	p->next = NULL;  //��ʼ���ýڵ���Ϣ
	p->data.ch = ch;
	p->data.cnt = 0;
	p->data.freq = 0;

	return 1;  //����1��ʾ�ɹ�
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