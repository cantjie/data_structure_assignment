#pragma once
#ifndef HEADER_H

#define HEADER_H

//���������ñ�׼ͷ�ļ�
#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>


#define FILE_NAME "test.txt"

#endif

//���ݽṹ���岿��

//����ڵ��ڵ����ݵĶ���
typedef struct linkData
{
	//����Ҫ������δ��溺�֡������ַ���,Ϊ�˱��⺺������ڴ������������Ƴ�һ��ch[2]
	char ch[2];
	int cnt;		//Ƶ��
	double freq;	// Ƶ��
}linkData;

//����ڵ�Ķ��塢��������
typedef struct linkNode
{
	linkData data;
	struct linkNode *next;
}linkNode;

//����ͷ�����������ݣ�ֻ��������������Ϣ
typedef struct linkHead
{
	int length;  //��ͷ�ڵ���ڵ������Ҳ���ǲ�ͬ�ַ��ĸ���
	int cnt;   //�ַ����������нڵ��cnt�ĺͣ�Ҳ�����ļ�����
	bool traverseTag;  //�ж��Ƿ��ڱ����Ĺ�����
	linkNode *next;
	linkNode *curr;
	linkNode *tail;
}linkHead;


//������������

//link.c

//����һ���µ�������������ͷ
linkHead* create_link(void);

//������ĩβ����һ���ڵ㣬����1��ʾ�ɹ���0��ʾδ�ɹ�
//����headΪĿ�������ͷ��㣬����chΪҪ������ַ�������
linkNode* append(linkHead *head,char ch[]);

//ѭ������ÿһ���ڵ㣬���ؽڵ��dataָ��
//ѭ����ϻ򳤶�Ϊ��ʱ����NULL
//����headΪĿ�������ͷ��㡣
linkData* foreach(linkHead *head);


//count.c

//����ͳ��Ƶ�ʣ�����һ������ͷ
linkHead* count_from_file(FILE* fp);


//main.c

//���۵����Ƶ��Ƶ��
//����headΪĿ��ͷ���ָ��
void print_data(linkHead *head);