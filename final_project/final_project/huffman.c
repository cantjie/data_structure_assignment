#include "header.h"

//��¼ÿ�����ָ���ɭ�ֽ��
typedef struct forestNode
{
	huffmanNode* pNode;
	struct forestNode* next;
}forestNode;

forestNode* preBuildTree(listHead* head);

huffmanNode* createHuffmanNode(forestNode* p1, forestNode* p2);

forestNode* createForestNode(huffmanNode* p_huffman);

void deleteLastTwoForestNode(forestNode* prev, forestNode* p1);

forestNode* insertForestNode(forestNode* head, forestNode* p);

huffmanNode* build_tree(listHead* head) {
	if (NULL == head->next || NULL == head->next->next) {
		printf("���ļ�����һ���ַ���û���ַ����ܾ���������������\n");
		exit(0);
	}

	//p1,p2��Ȩ����С��������㣬p���½�㡣prev_p1��p1��ǰ��
	forestNode *p1_forest, *p2_forest, *p_forest, *prev_p1_forest;
	forestNode *p_forest_head;
	huffmanNode *p_huffman;

	p_forest_head = preBuildTree(head);

	//�����ɭ����Ӧ��ֻ��һ�����
	while (p_forest_head->next) {
		p1_forest = p_forest_head;
		p2_forest = p_forest_head->next;
		prev_p1_forest = NULL;

		//��Ȩ����С��������㣬��Ϊ�Ѿ�����ã�����ֻ��Ҫ�����������㼴��
		while (p2_forest->next) {
			if (NULL == p2_forest->next->next) {
				prev_p1_forest = p1_forest;
			}
			p1_forest = p1_forest->next;
			p2_forest = p2_forest->next;
		}

		p_huffman = createHuffmanNode(p1_forest, p2_forest);
		p_forest = createForestNode(p_huffman);
		deleteLastTwoForestNode(prev_p1_forest, p1_forest);
		if (NULL == prev_p1_forest) {
			p_forest_head = NULL;
		}
		p_forest_head = insertForestNode(p_forest_head, p_forest);
	}
	return p_forest_head->pNode;
}

int get_one_code(char ch[])
{
	int tail = -1;
	//TODO
		
}

//��headָ������ɭ���в���һ��pָ��ָ��Ľڵ�,����
//@param forestNode* head
//@param forestNode* p
//@return forestNode* �����Ľڵ��ͷ
forestNode* insertForestNode(forestNode* head, forestNode* p) {
	if (head == NULL) {
		return p;
	}
	forestNode* prev;
	forestNode* curr;
	prev = head;
	curr = head;
	while (NULL != curr && curr->pNode->val > p->pNode->val) {
		prev = curr;
		curr = curr->next;
	}

	//���prev��curr��ͬ����˵��p�ڵ�Ӧ�ò���ͷ���ǰ��
	if (prev == curr) {
		head = p;
	}
	else {
		prev->next = p;
	}
	p->next = curr;
	return head;
}

//����һ��ָ���huffman����ɭ�ֽ��
//@param huffmanNode* p_huffman 
//@return forestNode* 
forestNode* createForestNode(huffmanNode* p_huffman) {
	forestNode *p_forest;
	p_forest = (forestNode*)malloc(sizeof(forestNode));
	if (!p_forest) {
		printf("���������������з�����ʱ�ڴ�ʧ��");
		exit(0);
	}
	p_forest->pNode = p_huffman;
	p_forest->next = NULL;
	return p_forest;
}

//ɾ��prev�������forest�Ľڵ㡣
//@param forestNode* pre Ҫɾ���������ڵ��ǰ��һ��
//@param forestNode* p1 Ҫɾ���ĵ�һ���ڵ�
void deleteLastTwoForestNode(forestNode* prev, forestNode* p1) {
	if (NULL != prev) {
		prev->next = NULL;
	}
	free(p1->next);
	free(p1);
}

//������ɭ�ֽ�㴴��һ���µ�huffman��㣬Ӧ����p2��Ӧ��valС�ڵ���p1��Ӧ��val
//@param forestNode p1
//@param forestNode p2
//@return huffmanNode* 
huffmanNode* createHuffmanNode(forestNode * p1, forestNode * p2)
{
	huffmanNode* p_huffman;

	p_huffman = (huffmanNode*)malloc(sizeof(huffmanNode));
	if (!p_huffman) {
		printf("���������������з�����ʱ�ڴ�ʧ��");
		exit(0);
	}
	p_huffman->lChild = p1->pNode;
	p_huffman->rChild = p2->pNode;
	//p_huffman->leafTag = false;
	p_huffman->val = p1->pNode->val + p2->pNode->val;
	return p_huffman;
}

//��ԭ�����listNode�����huffmanNode���ɵ�ɭ�ֵ�
//@param listNode* head
//@return forestNode* 
forestNode* preBuildTree(listHead * head)
{
	listNode *p = head->next;
	forestNode *p_forest_head;
	forestNode *p_forest;
	huffmanNode *p_huffman;
	p_forest = (forestNode*)malloc(sizeof(forestNode));
	p_forest_head = p_forest;
	while (p)
	{
		p_huffman = (huffmanNode*)malloc(sizeof(huffmanNode));
		if (!p_forest || !p_huffman) {
			printf("���������������з�����ʱ�ڴ�ʧ��");
			exit(0);
		}

		//��ʼ��huffman���
		p_huffman->rChild = NULL;
		p_huffman->lChild = p;  //����p��lChildָ�����ݵ����Ͳ���һ�£���ָ�뱾�ʶ���һ��int��ʹ����ʱ�ٽ���һ��ǿ��ת�����ɡ�
		//p_huffman->leafTag = true;  ͨ���ж��ҽڵ��Ƿ�Ϊ�ռ��ɵ�֪���ǲ���Ҷ�ӽ��
		p_huffman->val = p->data.cnt;

		//��ʼ��forest���
		p_forest->pNode = p_huffman;
		p_forest->next = NULL;

		if (p->next) {
			p_forest->next = (forestNode*)malloc(sizeof(forestNode));
		}
		p_forest = p_forest->next;
		p = p->next;
	}
	return p_forest_head;
}