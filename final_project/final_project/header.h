#pragma once
#ifndef HEADER_H

#define HEADER_H

#define MAX_CODE_LEN 3

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

//main.c

//����ļ����Ƿ�Ϸ�
//@param char filename[]
//@return bool �Ƿ�Ϸ�
bool isFilenameLegal(char filename[]);

//����ļ�����׺
//@param char filename[]
//@param char suffix[] 
//@return bool �ļ���׺Ϊsuffix���򷵻�true
bool filenameEndsWith(char filename[], char suffix[]);

//list.c

//����һ���µĿ�������������ͷ
listHead* create_null_list(void);
//��list����һ��tf_list
//@param listHead *list_head ������˵������ͷ���
//@param huffmanNode *huffman_head ���������ڵ�
tfListHead* create_tf_list(listHead *list_head, huffmanNode *huffman_head);

//������ĩβ����һ����㣬����1��ʾ�ɹ���0��ʾδ�ɹ�
//����headΪĿ�������ͷ��㣬����chΪҪ������ַ�������
listNode* append_list(listHead *head, char ch[]);


//ѭ������ÿһ����㣬���ؽ���dataָ��,ѭ����ϻ򳤶�Ϊ��ʱ����NULL
//ע�������foreach�Ĺ�����break�ˣ���Ҫ��head->traverseTag��Ϊ��
//����headΪĿ�������ͷ��㡣
listData* foreach_list(listHead *head);

//��ȡ������list���ļ������¹�������
//@param listHead* list_head �ɵ������ͷָ�룬��Ҫ�����ͷžɵ�����nullable
//@param char list_filename[] list�ļ�·��
//@param listHead* ��������ͷָ��
listHead* create_list_from_file(listHead* list_head, char list_filename[]);

//����һ���ַ���Ӧ��tf�ڵ�data����
//@param tfListHead *tf_list_head
//@param char ch[] 
//@return tfListData
tfListData get_tf_node_data(tfListHead *tf_list_head, char ch[]);

//ɾ������ɾ����ͷ�����������ڵ㣬ע��Ԥ��Ұָ��
//@param listHead* list_head
void drop_list(listHead* list_head);

//ɾ������ɾ����ͷ�����������ڵ㣬ע��Ԥ��Ұָ��
void drop_tf_list(tfListHead * list_head);

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
void print_freq(listHead *head);

//���۵������������
//@param huffmanNode* headĿ����������ĸ��ڵ�
void print_huffman_tree(huffmanNode* head);

//�������Ƶ�����ת����ʮ���Ʒ�������뱾�ı���
//@param int len ������������λ��
//@param char *code ��������ת�����ʮ����0��1������
//@param char *bi_code �������������������
void code_bi_to_dec(int len, bool *code, char *bi_code);

//���һ���ַ��ı���
//@param huffmanNode *huffman_head 
//@param char ch[]���ַ�����Ϊ2
void print_one_char_code(huffmanNode *huffman_head, char ch[]);

//��ӡ�뱾
//@param huffmanNode *huffman_head
//@param listHead *list_head
void print_codebook(huffmanNode *huffman_head, listHead *list_head);

//����ڵ���Ϣ����ʽΪÿ����Ԫ6�ֽ�=char�ַ�*2+intƵ��*1���޷ָ�����
//@param listHead *list_head
//@param char codebook_filename[] ���浽�ļ���λ��
void save_list(listHead *list_head, char list_filename[]);

//�ռ�����ģʽ�õ��������������ҽ�����������ļ���ȥ��
//@param huffmanNode *huffman_head
//@param char output_filename[] ѹ����������ļ����ļ���
//@param char input_filename[] Ҫѹ�����ļ���
void encode_and_save(huffmanNode *huffman_head, char output_filename[], char input_filename[]);

//ʱ������ģʽ�õ��������������ҽ�����������ļ���ȥ��
//@param tfListHead *tf_list_head
//@param char output_filename[] ѹ����������ļ����ļ���
//@param char input_filename[] Ҫѹ�����ļ���
void encode_and_save_tf(tfListHead *tf_list_head, char output_filename[], char input_filename[]);

//��������ı��ļ��Ƿ���ȫ��ͬ
//@param char file1_name[]
//@param char file2_name[]
bool file_compare(char file1_name[], char file2_name[]);


//huffman.c

//��ͳ�ƽ��������������
//@param listHead* head
//@return huffmanNode* �����������ָ��
huffmanNode* build_tree(listHead* head);

//ɾ��һ��������������ɾ�����нڵ㣬�������ڵ�.
//@param huffmanNode* huffman_head
void drop_huffman_tree(huffmanNode* huffman_head);

//��һ���ַ����õ����ַ���Ӧ���������ǰ��λ��
//@param huffmanNode* huffman_head ���ڵ�
//@param char ch[] char�ĳ��ȹ̶�Ϊ2
//@return int ���ظñ��볤�ȡ�
int get_char_code_len(huffmanNode* huffman_head, char ch[]);

//��ѹ������ļ����룬��������ļ���ȥ��
//@param huffmanNode *huffman_head
//@param char encoded_filename[] ѹ���ļ�������������������ļ�
//@param char decoded_filename[] ������ļ���
void decode_from_file(huffmanNode* huffman_head, char encoded_filename[], char decoded_filename[]);

