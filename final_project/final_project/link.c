#include "header.h"

linkNode* append(linkHead *head, char ch[]){
	linkNode* p;
	p = (linkNode*)malloc(sizeof(linkNode));
	if (NULL == p) {
		return NULL;
	}
	
	if (head->tail) {  //ԭ�ȵ����һ���ڵ�ָ���½ڵ�
		head->tail->next = p;
	}
	else
	{//���tailΪ�գ�˵��length=0
		head->next = p;
	}

	head->tail = p;  //����ͷ����Ϣ
	head->length++;

	p->next = NULL;  //��ʼ���ýڵ���Ϣ
	strcpy(p->data.ch, ch);
	p->data.cnt = 0;
	p->data.freq = 0;

	return p;  //�ɹ��򷵻ظýڵ�ָ��
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
	//�������Ϊ�㣬���ؿ�
	if (!head->length) {
		return NULL;
	}

	//�ж��Ƿ���ѭ�������С�
	linkData *p;
	if (head->traverseTag) {
		//���p�ǿյ�˵��ѭ�����
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