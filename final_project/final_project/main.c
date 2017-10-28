#include "header.h"

int main(int argc, char *argv[]) {
	linkHead *head;

	//linkData *data;
	//linkNode *p;

	head = count_from_file("test.txt");
	sort_link(head, true);
	print_data(head);
}
