#include "header.h"

int main(int argc, char *argv[]) {
	listHead *list_head;
	listNode *list_node;
	huffmanNode *huffman_head;
	int len; //当前编码长度（位数）
	bool code[2000];  //用来储存十进制的0、1
	int i, j, k;

	list_head = count_from_file("test.txt");

	sort_list(list_head, 0);

	print_data(list_head);

	huffman_head = build_tree(list_head);

	//print_huffman_tree(huffman_head);

	//print_one_char_code(huffman_head, "残");

	print_codebook(huffman_head, list_head);
	return 0;
}


