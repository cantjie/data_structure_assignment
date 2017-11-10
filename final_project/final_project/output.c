#include "header.h"

//用来辅助做二进制运算
unsigned char bi_array[8] = { 1,128,64,32,16,8,4,2 };

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
	printf("字符\t\t频数\t频率\t\n");
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
	printf("共计%d个不同字符，共计%d个字符\n", head->length, head->cnt);
}

void print_huffman_tree(huffmanNode* head) {
	//  这里的命名实在有点糟糕
	queueHead* queue_head;
	queue* p_queue;
	huffmanNode sep_node, *p_sep_node;  //层次separator
	sep_node.lChild = sep_node.rChild = NULL;
	p_sep_node = &sep_node;
	queue_head = createQueue();
	appendQueue(queue_head, head);
	appendQueue(queue_head, p_sep_node);
	p_queue = popQueue(queue_head);
	while (p_queue)
	{
		if (p_queue->pNode == p_sep_node) {
			if (queue_head->next && queue_head->next->next) {
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

void code_bi_to_dec(int len, bool * code)
{
	int i = 0;
	for (i = 0; i < len; i++) {
		code[i] = bi_array[(i + 1) % 8] & G_code_array[(i - 1) / 8];
	}
}

void print_one_char_code(huffmanNode *huffman_head, char ch[]) {
	bool code[MAX_CODE_LEN * 8];
	int len;
	int i;
	len = get_char_code(huffman_head, ch);
	code_bi_to_dec(len, code);
	printf("%c%c编码有%d位:", ch[0], ch[1], len);
	for (i = 0; i < len; i++) {
		printf("%d", code[i]);
	}
	printf("\n");
}

void print_codebook(huffmanNode * huffman_head, listHead *list_head)
{
	bool code[MAX_CODE_LEN * 8];
	int len;
	int i;
	listNode *list_node;
	list_node = list_head->next;
	printf("字符\t\t位数\t编码\n");
	while (list_node) {
		len = get_char_code(huffman_head, list_node->data.ch);
		code_bi_to_dec(len, code);
		if (list_node->data.ch[0] < 0) {
			printf("%c%c\t\t", list_node->data.ch[0], list_node->data.ch[1]);
		}
		else {
			if ((list_node->data.ch[0] <= 31 && list_node->data.ch[0] >= 0) || 127 == list_node->data.ch[0]) {
				printf("(ASCII:%d)\t", list_node->data.ch[0]);
			}
			else {
				printf("%c(ASCII:%d)\t", list_node->data.ch[0], list_node->data.ch[0]);
			}

		}
		printf("%d\t:", len);
		for (i = 0; i < len; i++) {
			printf("%d", code[i]);
		}
		printf("\n");
		list_node = list_node->next;
	}
}

//从FIFO队列中弹出一个元素
//@param queueHead* head FIFO队列头
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

//将一个哈夫曼结点加入队列
//@param queueHead* head FIFO队列头
//@param huffmanNode* pNode
void appendQueue(queueHead* head, huffmanNode* pNode) {
	queue* p_queue;
	p_queue = (queue*)malloc(sizeof(queue));
	if (!p_queue) {
		printf("队列开辟空间失败");
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

//创建一个FIFO队列，返回头结点
//@return queueHead*
queueHead* createQueue(void) {
	queueHead* queue_head;
	queue_head = (queueHead*)malloc(sizeof(queueHead));
	if (!queue_head) {
		printf("开辟队列头的空间失败");
		exit(0);
	}
	queue_head->next = NULL;
	queue_head->tail = NULL;
	return queue_head;
}