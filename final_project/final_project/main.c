#include "header.h"

int main(int argc, char *argv[]) {
	listHead *list_head;
	listNode *list_node;
	huffmanNode *huffman_head;
	int len;  //当前编码长度（位数）
	int i, j, k;
	char input_filename[50] = "test.txt";
	char output_filename[50] = "compressed.dat";
	
	list_head = count_from_file(input_filename);

	sort_list(list_head, 0);

	//print_data(list_head);

	huffman_head = build_tree(list_head);

	//print_huffman_tree(huffman_head);

	//print_one_char_code(huffman_head, "中");

	//print_codebook(huffman_head, list_head);

	file_put_stream(huffman_head, output_filename, input_filename);

	system("pause");
	decode_from_file(huffman_head, output_filename, "uncompressed.txt");

	return 0;
}


