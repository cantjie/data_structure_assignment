#include "header.h"

//���ظ�������м�ڵ㣬�����ż�����ڵ㣬�����м�ƫ��Ľڵ�
//@param linkNode p �������һ����ͷ�ڵ㡣
//@return linkNode
linkNode* getMiddle(linkNode* p);

//�ϲ���������õ��������غϲ��������ĵ�һ���ڵ�
//@param linkNode p1
//@param linkNode p2
//@param bool mode true��ʾ����false��ʾ����
//@return linkNode*
linkNode* mergeLink(linkNode* p1, linkNode* p2, bool mode);

//�鲢���򣬷�������õ�����ĵ�һ���ڵ�
//@param linkNode p �����һ����ͷ�ڵ�
//@param bool mode true��ʾ����false��ʾ����
//@return linkNode* 
linkNode* sortLink(linkNode* p, bool mode);

linkHead* count_from_file(char filename[]) {
	linkHead *head;
	linkData *data;
	FILE *fp;
	bool duplicate_tag;  //���ж��ظ���ʱ����
	char ch[2];
	linkNode *p;

	fp = fopen(filename, "r");
	head = create_link();
	while ((*ch = fgetc(fp)) != EOF)
	{
		//ch[0]<0��˵���Ǻ��֣����ٶ�ȡһ���ַ���
		if (ch[0] < 0) {
			ch[1] = fgetc(fp);
		}
		else
		{
			ch[1] = '\0';
		}
		duplicate_tag = false;
		//�ж��Ƿ��ظ�
		while (data = foreach(head)) {
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
		//�������ַ�֮ǰ��û�г��ֹ�����append
		if (!duplicate_tag) {
			if (!(p = append(head, ch))) {
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

	//���ѭ������һ��Ƶ��
	while (data = foreach(head)) {
		data->freq = (double)data->cnt / head->cnt;
	}

	return head;
}

void sort_link(linkHead* head, bool mode) {
	head->next = sortLink(head->next, mode);
}

linkNode* getMiddle(linkNode* p) {
	if (!(p && p->next)) return p;

	linkNode *fast;
	linkNode *slow;
	slow = p;
	fast = p->next;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

linkNode* mergeLink(linkNode * p1, linkNode * p2, bool mode)
{
	if (NULL == p1) return p2;
	if (NULL == p2) return p1;

	linkNode* p;
	linkNode* head;

	// �����������ж�дҲ���ԣ�������̫���ˡ�������������ȱ���ǲ������ȶ��ԣ����ù��̶������ȶ�����Ҫ��
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

linkNode* sortLink(linkNode * p, bool mode)
{
	if (!(p && p->next)) return p;  // ���ؿջ������Ψһ�Ľڵ�

	linkNode* middle = getMiddle(p);
	linkNode* latter_part;
	if (middle) {
		latter_part = middle->next;
		middle->next = NULL;
	}
	return mergeLink(sortLink(p, mode), sortLink(latter_part, mode), mode);
}
