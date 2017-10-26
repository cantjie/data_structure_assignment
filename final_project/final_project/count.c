#include "header.h"

linkHead* count_from_file(FILE* fp) {
	linkHead *head;
	linkData *data;
	bool duplicate_tag;  //���ж��ظ���ʱ����
	char ch[2];
	linkNode *p;
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
			if (0 == memcmp(data->ch,ch,2)) {
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

	//���ѭ������һ��Ƶ��
	while (data = foreach(head)) {
		data->freq = (double)data->cnt / head->cnt;
	}

	return head;
}

void sort_link(linkHead* head) {

}