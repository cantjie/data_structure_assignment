#pragma once
#ifndef HEADER_H

#define HEADER_H
//���������ñ�׼ͷ�ļ�

#endif


//����ڵ��ڵ����ݵĶ���
typedef struct linkData
{
	//����Ҫ������δ��溺�֡������ַ���,�������￼��ÿ���ڵ㴢��һ��utf-8�ַ�
	int a;
}linkData;

//����ڵ�Ķ���
typedef struct linkNode
{
	linkData data;
	struct linkNode *prev;
	struct linkNode *next;
}linkNode;

//����ͷ�����������ݣ�ֻ��������������Ϣ
typedef struct linkHead
{
	int sum;
	linkNode *next;
}linkHead;
