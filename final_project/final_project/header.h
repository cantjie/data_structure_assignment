#pragma once
#ifndef HEADER_H

#define HEADER_H

#define MAX_CODE_LEN 250

//���������ñ�׼ͷ�ļ�
#include<stdio.h>
#include <string.h>  //memcpy
#include<stdlib.h>
#include<stdbool.h>

#endif

//���ݽṹ���岿��

//�������ڵ����ݵĶ���
typedef struct listData
{
	//����Ҫ������δ��溺�֡������ַ���,Ϊ�˱��⺺������ڴ������������Ƴ�һ��ch[2]
	char ch[2];
	int cnt;		//Ƶ��
	double freq;	// Ƶ��
}listData;

//������Ķ��塢��������
typedef struct listNode
{
	listData data;
	struct listNode *next;
}listNode;

//����ͷ�����������ݣ�ֻ��������������Ϣ
typedef struct listHead
{
	int length;  //��ͷ������������Ҳ���ǲ�ͬ�ַ��ĸ���
	int cnt;   //�ַ����������н���cnt�ĺͣ�Ҳ�����ļ�����
	bool traverseTag;  //�ж��Ƿ��ڱ����Ĺ�����
	listNode *next;
	listNode *curr;
	listNode *tail;
}listHead;

//���������Ľ��
typedef struct huffmanNode
{
	int val;
	//bool leafTag;
	struct huffmanNode *lChild;
	struct huffmanNode *rChild;
}huffmanNode;

//��ʱ������������
unsigned char G_code_array[MAX_CODE_LEN];

//������������

//list.c

//����һ���µĿ�������������ͷ
listHead* create_list(void);

//������ĩβ����һ����㣬����1��ʾ�ɹ���0��ʾδ�ɹ�
//����headΪĿ�������ͷ��㣬����chΪҪ������ַ�������
listNode* append_list(listHead *head, char ch[]);

//ѭ������ÿһ����㣬���ؽ���dataָ��,ѭ����ϻ򳤶�Ϊ��ʱ����NULL
//ע�������foreach�Ĺ�����break�ˣ���Ҫ��head->traverseTag��Ϊ��
//����headΪĿ�������ͷ��㡣
listData* foreach(listHead *head);


//count.c

//����ͳ��Ƶ�ʣ�����һ������ͷ
//@param filename string �ļ���
//@return listHead* ����ͷ
listHead* count_from_file(char filename[]);

//��ͳ�ƽ������
//@param listHead* head Ŀ������ͷ���
//@param bool mode true��ʾ����false��ʾ����
void sort_list(listHead* head, bool mode);


//output.c

//���۵����Ƶ��Ƶ��
//@param listHead* headĿ�������ͷ���
void print_data(listHead *head);

//���۵������������
//@param huffmanNode* headĿ����������ĸ��ڵ�
void print_huffman_tree(huffmanNode* head);


//huffman.c

//��ͳ�ƽ��������������
//@param listHead* head
//@return huffmanNode* �����������ָ��
huffmanNode* build_tree(listHead* head);

//��һ���ַ����õ����ַ���Ӧ���������ǰ��λ��
//@param huffmanNode* huffman_head ���ڵ�
//@param char ch[] char�ĳ��ȹ̶�Ϊ2
//@return int ���ظñ��볤�ȡ�
int get_char_code(huffmanNode* huffman_head, char ch[]);