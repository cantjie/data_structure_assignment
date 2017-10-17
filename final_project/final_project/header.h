#pragma once
#ifndef HEADER_H

#define HEADER_H
//���������ñ�׼ͷ�ļ�
#include<stdio.h>
#include<malloc.h>

#define FILE_NAME "test.txt"

#endif

//���ݽṹ���岿��

//����ڵ��ڵ����ݵĶ���
typedef struct linkData
{
	//����Ҫ������δ��溺�֡������ַ���,�������￼��ÿ���ڵ㴢��һ��utf-8�ַ�
	char ch;
	int cnt;
	double freq;
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
	int length;//��ͷ�ڵ���ڵ����
	int cnt;   //�ַ����������нڵ��cnt�ĺ�
	linkNode *next;
	linkNode *curr;
	linkNode *tail;
}linkHead;


//������������

//����һ���µ�������������ͷ
linkHead* create_link(void);

//������ĩβ����һ���ڵ㣬����1��ʾ�ɹ���0��ʾδ�ɹ�
//����headΪĿ�������ͷ��㣬����chΪҪ������ַ�����
int append(linkHead *head,char ch);