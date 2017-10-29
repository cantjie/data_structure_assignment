#include "header.h"

int main(int argc, char *argv[]) {
	linkHead *head;

	//linkData *data;
	//linkNode *p;

	head = count_from_file("test.txt");
	sort_link(head, 0);
	print_data(head);
	build_tree(head);
}
