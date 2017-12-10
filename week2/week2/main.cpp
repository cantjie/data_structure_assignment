#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
template <class T> class List {
private:
	int maxSize;
	int listSize;
	int curr;
	T *head;
public:
	//���캯��������һ������
	List(int size = 1000) {
		maxSize = size;
		listSize = curr = 0;
		head = new T[maxSize];
	}
	//����������ɾ������Ŀռ�
	~List()
	{
		delete[] head;
	}
	void Init() { curr = 0; }
	void Empty() { listSize = curr = 0; }
	int GetMaxSize() { return maxSize; }
	T GetCurrValue() { return head[curr]; }
	int GetCurrIndex() { return curr; }
	int GetListSize() { return listSize; }

	void SetMaxSize(int max_size) { maxSize = max_size; }
	void SetCurrValue(T value) { head[curr] = value; }
	void SetCurrIndex(int idx) { curr = idx }
	void SetListSize(int list_size) { listSize = list_size; }

	void Prev() { curr < 0 ? curr : curr--; }
	void Next() { curr > listSize ? curr : curr++; }

	bool Insert(T value, int index = -1 );
	int RemoveByValue(T value);
	bool RemoveByIndex(int index = -1);
	int Find(T value);
	List<T>* Merge(List<T>*, int size);
	void Sort();
	List<T>* Split(int index = -1);

};

/*ָ��λ�û����ڵ�ǰλ�ò���һ�����ݣ����ز���ɹ����*/
template <class T>
bool List<T>::Insert(T value, int index) {
	index = index == -1 ? curr : index;
	if (listSize >= maxSize - 1) {
		return false;
	}
	if (index<0 || index > listSize ) {
		return false;
	}
	for (int i = listSize; i >= index; i--) {
		head[i] = head[i - 1];
	}
	listSize++;
	head[index] = value;
	return true;
}

/*ͨ��ֵɾ��һ��Ԫ�أ�����ж��Ԫ��ֵ��ͬ����ȫ��ɾ��������ɾ��Ԫ�صĸ���*/
template <class T>
int List<T>::RemoveByValue(T value) {
	count = 0;
	for (int i = 0; i < listSize; i++) {
		if (head[i] == value) {
			listSize--; count++;
			for (int j = i; j < listSize; j++) {
				head[j] = head[j + 1];
			}
		}
	}
	curr = curr > listSize ? listSize : curr;
	return count;
}

/*ͨ��λ��ɾ��һ��Ԫ�أ���δָ���ض�λ�ã���ɾ��ָ�뵱ǰλ��Ԫ��*/
template <class T>
bool List<T>::RemoveByIndex(int index ) {
	index = index == -1 ? curr : index;
	if (index < 0 || index > listSize - 1) { return false; }
	for (int i = index; i < listSize; i++) {
		head[i] = head[i + 1];
	}
	listSize--;
	curr = curr > listSize ? listSize : curr;
	return true;
}

/*����ĳ��ֵ��������ֵ�λ�ã�������ֶ�Σ�ֻ���ص�һ�����ֵ�λ��*/
template <class T>
int List<T>::Find(T value) {
	for (int i = 0; i < listSize; i++) {
		if (head[i] == value) {
			return i;
		}
	}
}
/*�ϲ�����List�࣬ȡmaxSize�ĺ���Ϊ�µ�maxSize*/
template<class T>
List<T>* List<T>::Merge(List<T>* another_list, int size) {
	/*new_max_size = maxSize + another_list.G*/
	int new_max_size = maxSize + another_list->GetMaxSize();
	int new_list_size = listSize + another_list->GetListSize();
	another_list->Init();
	List<T>* A = new List<T>(new_max_size);
	for (int i = 0; i < new_list_size; i++) {
		if (i < listSize) {
			A->SetCurrValue(head[i]);
		}
		else {
			A->SetCurrValue(another_list->GetCurrValue());
			another_list->Next();
		}
		A->Next();
	}
	A->SetListSize(new_list_size);

	return A;
}

/*����*/
template<class T>
void List<T>::Sort() {
	for (int i = 0; i < listSize; i++) {
		for (int j = 0; j < listSize - i - 1; j++) {
			if (head[j] < head[j + 1]) {
				temp = head[j];
				head[j] = head[j + 1];
				head[j + 1] = temp;
			}
		}
	}
}

/*��index��λ�÷ֿ�������������*/
template<class T>
List<T>* List<T>::Split(int index = -1) {
	index = index == -1 ? curr : index;
	List<T>* A = new List<T>(maxSize);
	for (int i = index; i < listSize ; i++){
		A->SetCurrValue(head[i]);
		A->Next();
	}
	A->SetListSize(listSize - index);
	listSize = index;
	return A;
}
int main() {
	List<int>* A;
	List<int>* B;
	List<int>* C;
	A = new List<int>(100);
	A->Insert(100);
	A->Insert(200);
	A->Insert(300);
	B = new List<int>(200);
	/*B->Insert(200);
	C = A->Merge(B, B->GetListSize());
	B->Init();
	C->Init();
	*/
	B = A->Split(1);
	B->Init();
	A->Init();
	A->Next();
	A->Next();
	printf("A%d\n", A->GetCurrIndex());
	printf("A%d\n", A->GetCurrValue());
	printf("B%d\n", B->GetCurrIndex());
	printf("B%d\n", B->GetCurrValue());
	//printf("%d\n", C->GetCurrIndex());
	//printf("%d\n", C->GetCurrValue());

	return 0;
}