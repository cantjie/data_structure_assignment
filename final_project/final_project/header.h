#pragma once
#ifndef HEADER_H

#define HEADER_H

#define MAX_CODE_LEN 250

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
	//这里要考虑如何储存汉字、特殊字符等,为了避免汉字造成内存溢出，这里设计成一个ch[2]
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

//list.c

//创建一个新的空链表，返回链表头
listHead* create_list(void);

//向链表末尾增加一个结点，返回1表示成功，0表示未成功
//参数head为目标链表的头结点，参数ch为要插入的字符变量。
listNode* append_list(listHead *head, char ch[]);

//循环链表每一个结点，返回结点的data指针,循环完毕或长度为空时返回NULL
//注意如果在foreach的过程中break了，需要将head->traverseTag置为假
//参数head为目标链表的头结点。
listData* foreach(listHead *head);


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
void print_data(listHead *head);

//美观地输出哈夫曼树
//@param huffmanNode* head目标哈夫曼树的根节点
void print_huffman_tree(huffmanNode* head);


//huffman.c

//由统计结果建立哈夫曼树
//@param listHead* head
//@return huffmanNode* 返回树根结点指针
huffmanNode* build_tree(listHead* head);

//给一个字符，得到该字符对应编码数组的前几位。
//@param huffmanNode* huffman_head 根节点
//@param char ch[] char的长度固定为2
//@return int 返回该编码长度。
int get_char_code(huffmanNode* huffman_head, char ch[]);