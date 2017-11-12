#include "header.h"

int main(int argc, char *argv[]) {
	listHead *list_head;
	listNode *list_node;
	huffmanNode *huffman_head;
	int len;  //��ǰ���볤�ȣ�λ����
	bool code[2000];  //��������ʮ���Ƶ�0��1
	int i, j, k;
	char input_filename[50] = "test.txt";
	char output_filename[50] = "output.dat";
	
	list_head = count_from_file(input_filename);

	sort_list(list_head, 0);

	print_data(list_head);

	huffman_head = build_tree(list_head);

	print_huffman_tree(huffman_head);

	//print_one_char_code(huffman_head, "��");

	print_codebook(huffman_head, list_head);


	file_put_stream(huffman_head, output_filename, input_filename);
	
	return 0;
}


