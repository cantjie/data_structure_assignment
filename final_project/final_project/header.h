#pragma once
#ifndef HEADER_H

#define HEADER_H

//在这里引用标准头文件
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>


#define FILE_NAME "test.txt"

#endif

//数据结构定义部分

//链表节点内的数据的定义
typedef struct linkData
{
	//这里要考虑如何储存汉字、特殊字符等,为了避免汉字造成内存溢出，这里设计成一个ch[2]
	char ch[2];
	int cnt;		//频数
	double freq;	// 频率
}linkData;

//链表节点的定义、单向链表
typedef struct linkNode
{
	linkData data;
	struct linkNode *next;
}linkNode;

//链表头，不包含数据，只用来包含链表信息
typedef struct linkHead
{
	int length;  //除头节点外节点个数，也就是不同字符的个数
	int cnt;   //字符数，即所有节点的cnt的和，也就是文件长度
	bool traverseTag;  //判断是否在遍历的过程中
	linkNode *next;
	linkNode *curr;
	linkNode *tail;
}linkHead;


//函数声明部分

//link.c

//创建一个新的链表，返回链表头
linkHead* create_link(void);

//向链表末尾增加一个节点，返回1表示成功，0表示未成功
//参数head为目标链表的头结点，参数ch为要插入的字符变量。
linkNode* append(linkHead *head,char ch[]);

//循环链表每一个节点，返回节点的data指针
//循环完毕或长度为空时返回NULL
//参数head为目标链表的头结点。
linkData* foreach(linkHead *head);


//count.c

//用来统计频率，返回一个链表头
linkHead* count_from_file(FILE* fp);


//main.c

//美观的输出频率频度
//参数head为目标头结点指针
void print_data(linkHead *head);