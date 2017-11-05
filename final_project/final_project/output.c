#include "header.h"

typedef struct FIFO_queue {
	huffmanNode* pNode;
	struct FIFO_queue* next;
}queue;

typedef struct FIFO_queueHead {
	queue* next;
	queue* tail;
}queueHead;

queue* popQueue(queueHead* queue_head);

void appendQueue(queueHead* head, huffmanNode* pNode);

queueHead* createQueue(void);

void print_data(listHead *head) {
	listData *data;
	printf("�ַ�\t\tƵ��\tƵ��\t\n");
	while (data = foreach(head)) {
		if (data->ch[0] < 0) {
			printf("%c%c\t\t", data->ch[0], data->ch[1]);
		}
		else {
			if ((data->ch[0] <= 31 && data->ch[0] >= 0) || 127 == data->ch[0]) {
				printf("(ASCII:%d)\t", data->ch[0]);
			}
			else {
				printf("%c(ASCII:%d)\t", data->ch[0], data->ch[0]);
			}

		}
		printf("%d\t%lf\t\n", data->cnt, data->freq);
	}
	printf("����%d����ͬ�ַ�������%d���ַ�\n", head->length, head->cnt);
}

void print_huffman_tree(huffmanNode* head) {
	//  ���������ʵ���е����
	queueHead* queue_head;
	queue* p_queue;
	huffmanNode sep_node, *p_sep_node;  //���separator
	sep_node.lChild = sep_node.rChild = NULL;
	p_sep_node = &sep_node;
	queue_head = createQueue();
	appendQueue(queue_head, head);
	appendQueue(queue_head, p_sep_node);
	p_queue = popQueue(queue_head);
	while (p_queue)
	{
		if (p_queue->pNode == p_sep_node) {
			if(queue_head->next && queue_head->next->next){
				appendQueue(queue_head, p_sep_node);
			}
			p_queue = popQueue(queue_head);
			printf("\n");
			continue;
		}
		printf("%3d ", p_queue->pNode->val);
		if (NULL != p_queue->pNode->lChild && NULL != p_queue->pNode->rChild) {
			appendQueue(queue_head, p_queue->pNode->lChild);
			appendQueue(queue_head, p_queue->pNode->rChild);
		}
		p_queue = popQueue(queue_head);
	}
}

//��FIFO�����е���һ��Ԫ��
//@param queueHead* head FIFO����ͷ
//@return huffmanNode;
queue* popQueue(queueHead* queue_head) {
	queue* first;
	first = queue_head->next;
	if (NULL != first) {
		queue_head->next = queue_head->next->next;
	}
	else {
		queue_head = NULL;
	}
	return first;
}

//��һ�����������������
//@param queueHead* head FIFO����ͷ
//@param huffmanNode* pNode
void appendQueue(queueHead* head, huffmanNode* pNode) {
	queue* p_queue;
	p_queue = (queue*)malloc(sizeof(queue));
	if (!p_queue) {
		printf("���п��ٿռ�ʧ��");
		exit(0);
	}

	p_queue->pNode = pNode;
	p_queue->next = NULL;
	if (NULL == head->next) {
		head->next = p_queue;
		head->tail = p_queue;
	}
	else {
		head->tail->next = p_queue;
		head->tail = p_queue;
	}
}

//����һ��FIFO���У�����ͷ���
//@return queueHead*
queueHead* createQueue(void) {
	queueHead* queue_head;
	queue_head = (queueHead*)malloc(sizeof(queueHead));
	if (!queue_head) {
		printf("���ٶ���ͷ�Ŀռ�ʧ��");
		exit(0);
	}
	queue_head->next = NULL;
	queue_head->tail = NULL;
	return queue_head;
}