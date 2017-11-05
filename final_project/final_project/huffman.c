#include "header.h"

//记录每个结点指针的森林结点
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
		printf("该文件仅有一种字符或没有字符，拒绝建立哈夫曼编码\n");
		exit(0);
	}

	//p1,p2找权重最小的两个结点，p存新结点。prev_p1存p1的前驱
	forestNode *p1_forest, *p2_forest, *p_forest, *prev_p1_forest;
	forestNode *p_forest_head;
	huffmanNode *p_huffman;

	p_forest_head = preBuildTree(head);

	//到最后森林里应该只有一个结点
	while (p_forest_head->next) {
		p1_forest = p_forest_head;
		p2_forest = p_forest_head->next;
		prev_p1_forest = NULL;

		//找权重最小的两个结点，因为已经排序好，所以只需要找最后两个结点即可
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

//向head指向的这个森林中插入一个p指针指向的节点,降序
//@param forestNode* head
//@param forestNode* p
//@return forestNode* 插入后的节点的头
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

	//如果prev和curr相同。就说明p节点应该插在头结点前面
	if (prev == curr) {
		head = p;
	}
	else {
		prev->next = p;
	}
	p->next = curr;
	return head;
}

//创建一个指向该huffman结点的森林结点
//@param huffmanNode* p_huffman 
//@return forestNode* 
forestNode* createForestNode(huffmanNode* p_huffman) {
	forestNode *p_forest;
	p_forest = (forestNode*)malloc(sizeof(forestNode));
	if (!p_forest) {
		printf("建立哈夫曼过程中分配临时内存失败");
		exit(0);
	}
	p_forest->pNode = p_huffman;
	p_forest->next = NULL;
	return p_forest;
}

//删除prev后的两个forest的节点。
//@param forestNode* pre 要删除的两个节点的前面一个
//@param forestNode* p1 要删除的第一个节点
void deleteLastTwoForestNode(forestNode* prev, forestNode* p1) {
	if (NULL != prev) {
		prev->next = NULL;
	}
	free(p1->next);
	free(p1);
}

//由两个森林结点创建一个新的huffman结点，应满足p2对应的val小于等于p1对应的val
//@param forestNode p1
//@param forestNode p2
//@return huffmanNode* 
huffmanNode* createHuffmanNode(forestNode * p1, forestNode * p2)
{
	huffmanNode* p_huffman;

	p_huffman = (huffmanNode*)malloc(sizeof(huffmanNode));
	if (!p_huffman) {
		printf("建立哈夫曼过程中分配临时内存失败");
		exit(0);
	}
	p_huffman->lChild = p1->pNode;
	p_huffman->rChild = p2->pNode;
	//p_huffman->leafTag = false;
	p_huffman->val = p1->pNode->val + p2->pNode->val;
	return p_huffman;
}

//将原链表的listNode结点变成huffmanNode构成的森林的
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
			printf("建立哈夫曼过程中分配临时内存失败");
			exit(0);
		}

		//初始化huffman结点
		p_huffman->rChild = NULL;
		p_huffman->lChild = p;  //这里p和lChild指向数据的类型并不一致，但指针本质都是一个int，使用它时再进行一下强制转换即可。
		//p_huffman->leafTag = true;  通过判断右节点是否为空即可得知它是不是叶子结点
		p_huffman->val = p->data.cnt;

		//初始化forest结点
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