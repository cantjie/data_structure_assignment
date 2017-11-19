#include "header.h"

listNode* getMiddle(listNode* p);

listNode* mergelist(listNode* p1, listNode* p2, bool mode);

listNode* sortlist(listNode* p, bool mode);

listHead* count_from_file(char filename[]) {
	listHead *head;
	listData *data;
	FILE *fp;
	bool duplicate_tag;  //���ж��ظ���ʱ����
	char ch[2];
	listNode *p;

	fp = fopen(filename, "r");
	if (NULL == fp) {
		return NULL;
	}
	head = create_null_list();
	while ((*ch = fgetc(fp)) != EOF) {
		//ch[0]<0��˵���Ǻ��֣����ٶ�ȡһ���ַ���
		if (ch[0] < 0) {
			ch[1] = fgetc(fp);
		}
		else {
			ch[1] = '\0';
		}
		duplicate_tag = false;
		//�ж��Ƿ��ظ�
		while (data = foreach_list(head)) {
			//������ַ�����ȣ�˵���ظ��ˣ���Ƶ��+1
			//ע�����ﲻ����strcmp��strcmp��Ƚ�ֱ��'\0'
			//if (0 == strcmp(data->ch, ch)) {
			if (0 == memcmp(data->ch, ch, 2)) {
				data->cnt++;
				duplicate_tag = true;
				head->traverseTag = false;
				break;
			}
		}
		//�������ַ�֮ǰ��û�г��ֹ�����append_list
		if (!duplicate_tag) {
			if (!(p = append_list(head, ch))) {
				//���ʧ�ܾ���ʾ���˳�����
				printf("ͳ�ƹ��̳��ִ�������������");
				exit(0);
			}
			else {
				p->data.cnt++;
			}
		}
		head->cnt++;
	}
	fclose(fp);

	//�������һ����ʾ�������ַ�
	ch[0] = '\0'; ch[1] = '\0';
	if (!(p = append_list(head, ch))) {
		printf("ͳ�ƹ��̳��ִ�������������");
		exit(0);
	}
	p->data.cnt = 0;
	head->length -= 1;

	//���ѭ������һ��Ƶ��
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

//���ظ�������м��㣬�����ż������㣬�����м�ƫ��Ľ��
//@param listNode p �������һ����ͷ��㡣
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

//�ϲ���������õ��������غϲ��������ĵ�һ�����
//@param listNode p1
//@param listNode p2
//@param bool mode true��ʾ����false��ʾ����
//@return listNode*
listNode* mergelist(listNode * p1, listNode * p2, bool mode)
{
	if (NULL == p1) return p2;
	if (NULL == p2) return p1;

	listNode* p;
	listNode* head;

	// �����������ж�дҲ���ԣ�������̫���ˡ�
	//������������ȱ���ǲ������ȶ��ԣ����ù��̶������ȶ�����Ҫ��
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

//�鲢���򣬷�������õ�����ĵ�һ�����
//@param listNode p �����һ����ͷ���
//@param bool mode true��ʾ����false��ʾ����
//@return listNode* 
listNode* sortlist(listNode * p, bool mode)
{
	if (!(p && p->next)) return p;  // ���ؿջ������Ψһ�Ľ��

	listNode* middle = getMiddle(p);
	listNode* latter_part;
	if (middle) {
		latter_part = middle->next;
		middle->next = NULL;
	}
	return mergelist(sortlist(p, mode), sortlist(latter_part, mode), mode);
}
