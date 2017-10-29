#include "header.h"

int main(int argc, char *argv[]) {
	listHead *list_head;
	huffmanNode *huffman_head;

	list_head = count_from_file("test.txt");

	sort_list(list_head, 0);

	print_data(list_head);

	huffman_head = build_tree(list_head);

	//print_huffman_tree(huffman_head);
}
