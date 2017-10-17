#pragma once
#ifndef HEADER_H

#define HEADER_H
//在这里引用标准头文件

#endif


//链表节点内的数据的定义
typedef struct linkData
{
	//这里要考虑如何储存汉字、特殊字符等,于是这里考虑每个节点储存一个utf-8字符
	int a;
}linkData;

//链表节点的定义
typedef struct linkNode
{
	linkData data;
	struct linkNode *prev;
	struct linkNode *next;
}linkNode;

//链表头，不包含数据，只用来包含链表信息
typedef struct linkHead
{
	int sum;
	linkNode *next;
}linkHead;
