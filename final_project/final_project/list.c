#include "header.h"

listNode* append_list(listHead *head, char ch[]) {
	listNode* p;
	p = (listNode*)malloc(sizeof(listNode));
	if (NULL == p) {
		return NULL;
	}

	if (head->tail) {  //ԭ�ȵ����һ�����ָ���½��
		head->tail->next = p;
	}
	else
	{//���tailΪ�գ�˵��length=0
		head->next = p;
	}

	head->tail = p;  //����ͷ����Ϣ
	head->length++;

	p->next = NULL;  //��ʼ���ý����Ϣ
	memcpy(p->data.ch, ch, 2);
	//strcpy(p->data.ch, ch);
	p->data.cnt = 0;
	p->data.freq = 0;

	return p;  //�ɹ��򷵻ظý��ָ��
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
	//�������Ϊ�㣬���ؿ�
	if (!head->length) {
		return NULL;
	}

	//�ж��Ƿ���ѭ�������С�
	listData *p;
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
	else {
		head->traverseTag = true;
		head->curr = head->next;
		return foreach(head);
	}
}