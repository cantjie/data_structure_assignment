#include "header.h"

int main(int argc, char *argv[]) {
	listHead *list_head;
	huffmanNode *huffman_head;

	list_head = count_from_file("test.txt");

	sort_list(list_head, 0);

	print_data(list_head);

	huffman_head = build_tree(list_head);

	print_huffman_tree(huffman_head);

	//unsigned char bi_array[9] = { 0,1,2,4,8,16,32,64,128 };
	//unsigned char a;
	//a = 'c';//0110 0011
	//printf("%d", (bi_array[6] & a)>>5);
	char a[2];
	a[0] = 'a';
	a[1] = '\n';
	get_char_code(huffman_head,a);
	return 0;
}


