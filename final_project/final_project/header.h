#pragma once
#ifndef HEADER_H

#define HEADER_H

#define MAX_CODE_LEN 3

//在这里引用标准头文件
#include<stdio.h>
#include <string.h>  //memcpy
#include<stdlib.h>
#include<stdbool.h>

#endif

//数据结构定义部分

//链表结点内的数据的定义
typedef struct listData
{
	char ch[2];
	int cnt;		//频数
	double freq;	// 频率
}listData;

//链表结点的定义、单向链表
typedef struct listNode
{
	listData data;
	struct listNode *next;
}listNode;

//链表头，不包含数据，只用来包含链表信息
typedef struct listHead
{
	int length;  //除头结点外结点个数，也就是不同字符的个数
	int cnt;   //字符数，即所有结点的cnt的和，也就是文件长度
	bool traverseTag;  //判断是否在遍历的过程中
	listNode *next;
	listNode *curr;
	listNode *tail;
}listHead;

typedef struct tfListData
{
	char ch[2];
	unsigned char valid_len;
	unsigned char code[MAX_CODE_LEN];
}tfListData;

typedef struct tfListNode
{
	tfListData data;
	struct tfListNode *next;
}tfListNode;

typedef struct tfListHead
{
	tfListNode *next;
	tfListNode *curr;
	tfListNode *tail;
}tfListHead;


//哈夫曼树的结点
typedef struct huffmanNode
{
	int val;
	//bool leafTag;
	struct huffmanNode *lChild;
	struct huffmanNode *rChild;
}huffmanNode;

//临时储存代码的数组
unsigned char G_code_array[MAX_CODE_LEN];


//函数声明部分

//main.c

//检查文件名是否合法
//@param char filename[]
//@return bool 是否合法
bool isFilenameLegal(char filename[]);

//检查文件名后缀
//@param char filename[]
//@param char suffix[] 
//@return bool 文件后缀为suffix，则返回true
bool filenameEndsWith(char filename[], char suffix[]);

//list.c

//创建一个新的空链表，返回链表头
listHead* create_null_list(void);
//从list创建一个tf_list
//@param listHead *list_head 排序好了的链表的头结点
//@param huffmanNode *huffman_head 哈夫曼根节点
tfListHead* create_tf_list(listHead *list_head, huffmanNode *huffman_head);

//向链表末尾增加一个结点，返回1表示成功，0表示未成功
//参数head为目标链表的头结点，参数ch为要插入的字符变量。
listNode* append_list(listHead *head, char ch[]);


//循环链表每一个结点，返回结点的data指针,循环完毕或长度为空时返回NULL
//注意如果在foreach的过程中break了，需要将head->traverseTag置为假
//参数head为目标链表的头结点。
listData* foreach_list(listHead *head);

//读取储存了list的文件并重新构建链表。
//@param listHead* list_head 旧的链表的头指针，主要用来释放旧的链表。nullable
//@param char list_filename[] list文件路径
//@param listHead* 返回链表头指针
listHead* create_list_from_file(listHead* list_head, char list_filename[]);

//查找一个字符对应的tf节点data数据
//@param tfListHead *tf_list_head
//@param char ch[] 
//@return tfListData
tfListData get_tf_node_data(tfListHead *tf_list_head, char ch[]);

//删除链表：删除除头结点外的其他节点，注意预防野指针
//@param listHead* list_head
void drop_list(listHead* list_head);

//删除链表：删除除头结点外的其他节点，注意预防野指针
void drop_tf_list(tfListHead * list_head);

//count.c

//用来统计频率，返回一个链表头
//@param filename string 文件名
//@return listHead* 链表头
listHead* count_from_file(char filename[]);

//将统计结果排序。
//@param listHead* head 目标链表头结点
//@param bool mode true表示增序，false表示降序
void sort_list(listHead* head, bool mode);


//output.c

//美观地输出频率频度
//@param listHead* head目标链表的头结点
void print_freq(listHead *head);

//美观地输出哈夫曼树
//@param huffmanNode* head目标哈夫曼树的根节点
void print_huffman_tree(huffmanNode* head);

//将二进制的码流转换成十进制方便输出码本的编码
//@param int len 二进制码流的位数
//@param char *code 用来储存转换后的十进制0、1的数组
//@param char *bi_code 储存二进制码流的数组
void code_bi_to_dec(int len, bool *code, char *bi_code);

//输出一个字符的编码
//@param huffmanNode *huffman_head 
//@param char ch[]，字符长度为2
void print_one_char_code(huffmanNode *huffman_head, char ch[]);

//打印码本
//@param huffmanNode *huffman_head
//@param listHead *list_head
void print_codebook(huffmanNode *huffman_head, listHead *list_head);

//保存节点信息，格式为每个单元6字节=char字符*2+int频数*1，无分隔符。
//@param listHead *list_head
//@param char codebook_filename[] 保存到文件的位置
void save_list(listHead *list_head, char list_filename[]);

//空间优先模式得到二进制码流并且将码流输出到文件中去。
//@param huffmanNode *huffman_head
//@param char output_filename[] 压缩后输出的文件的文件名
//@param char input_filename[] 要压缩的文件名
void encode_and_save(huffmanNode *huffman_head, char output_filename[], char input_filename[]);

//时间优先模式得到二进制码流并且将码流输出到文件中去。
//@param tfListHead *tf_list_head
//@param char output_filename[] 压缩后输出的文件的文件名
//@param char input_filename[] 要压缩的文件名
void encode_and_save_tf(tfListHead *tf_list_head, char output_filename[], char input_filename[]);

//检查两个文本文件是否完全相同
//@param char file1_name[]
//@param char file2_name[]
bool file_compare(char file1_name[], char file2_name[]);


//huffman.c

//由统计结果建立哈夫曼树
//@param listHead* head
//@return huffmanNode* 返回树根结点指针
huffmanNode* build_tree(listHead* head);

//删除一个哈夫曼树，将删掉所有节点，包括根节点.
//@param huffmanNode* huffman_head
void drop_huffman_tree(huffmanNode* huffman_head);

//给一个字符，得到该字符对应编码数组的前几位。
//@param huffmanNode* huffman_head 根节点
//@param char ch[] char的长度固定为2
//@return int 返回该编码长度。
int get_char_code_len(huffmanNode* huffman_head, char ch[]);

//将压缩后的文件解码，并输出到文件中去。
//@param huffmanNode *huffman_head
//@param char encoded_filename[] 压缩文件，储存二进制码流的文件
//@param char decoded_filename[] 输出的文件名
void decode_from_file(huffmanNode* huffman_head, char encoded_filename[], char decoded_filename[]);

