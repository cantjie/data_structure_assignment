#pragma once
#ifndef HEADER_H

#define HEADER_H
//在这里引用标准头文件
#include<stdio.h>
#include<malloc.h>

#define FILE_NAME "test.txt"

#endif

//数据结构定义部分

//链表节点内的数据的定义
typedef struct linkData
{
	//这里要考虑如何储存汉字、特殊字符等,于是这里考虑每个节点储存一个utf-8字符
	char ch;
	int cnt;
	double freq;
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
	int length;//除头节点外节点个数
	int cnt;   //字符数，即所有节点的cnt的和
	linkNode *next;
	linkNode *curr;
	linkNode *tail;
}linkHead;


//函数声明部分

//创建一个新的链表，返回链表头
linkHead* create_link(void);

//向链表末尾增加一个节点，返回1表示成功，0表示未成功
//参数head为目标链表的头结点，参数ch为要插入的字符变量
int append(linkHead *head,char ch);