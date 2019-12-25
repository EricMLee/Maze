#include <stdio.h>
#include <stdlib.h>
#include "List.h"
typedef struct NodeObj {
	int element;
	struct NodeObj* next;
	struct NodeObj* prev;
}NodeObj;

typedef struct ListObj {
	int manyNodes;
	Node* head_ptr;
	Node* tail_ptr;
	Node* cursor;
}ListObj;

Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->element = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}
int index(List L) {
	if (L == NULL) {
		return -1;
	}
	if (L->cursor == NULL) {
		return -1;
	}
	Node reader = L->head_ptr;
	int counter = 0;
	while (reader != L->cursor) {
		reader = reader->next;
		counter++;
	}
	return counter;
}
int isEmpty(List L) {
	if (L == NULL) {
		exit(1);
	}
	return (L->manyNodes == 0);
}

void Dequeue(List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(L)) {
		printf("Queue Error: calling Dequeue on an empty Queue\n");
		exit(1);
	}
	N = L->head_ptr;
	Node temp;
	if (L->manyNodes > 1) {
		temp = L->head_ptr;
		L->head_ptr = temp->next;
	}
	else {
		L->head_ptr = L->tail_ptr = NULL;
	}
	L->manyNodes--;
	freeNode(&N);
}

void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->cursor = NULL;
	L->tail_ptr = NULL;
	L->head_ptr = NULL;
	L->manyNodes = 0;
	return(L);
}
int length(List L) {
	return L->manyNodes;
}
int front(List L) {
	if (L->manyNodes > 0) {
		Node n = L->head_ptr;
		return n->element;
	}
	return -1;
}
int back(List L) {
	if (L->manyNodes <= 0) {
		return -1;
	}
	Node n = L->tail_ptr;
	int nodeElement = n->element;
	return nodeElement;
}
int get(List L) {
	if (L->cursor == NULL || L == NULL)
		return -1;
	Node n = L->cursor;
	int nodeElement = n->element;
	return nodeElement;
}

void clear(List L) {
	while (L->manyNodes != 0) {
		deleteFront(L);
		//L->manyNodes--;
	}
	L->head_ptr = NULL;
	L->cursor = NULL;
	//L->manyNodes = 0;
	L->tail_ptr = NULL;
}
void moveFront(List L) {
	L->cursor = L->head_ptr;
}
void moveBack(List L) {
	L->cursor = L->tail_ptr;
}
void moveNext(List L) {
	if (L == NULL)
		return -1;
	Node nextNode = L->cursor;
	L->cursor = nextNode->next;
}
void movePrev(List L) {
	if (L == NULL)
		return -1;
	Node prevNode = L->cursor;
	L->cursor = prevNode->prev;
}

void prepend(List L, int data) {
	Node new_node = newNode(data);
	if (L->manyNodes == 0) {
		L->head_ptr = new_node;
		L->tail_ptr = new_node;
		L->manyNodes = 1;
	}
	else {
		Node oldHead = L->head_ptr;
		oldHead->prev = new_node;
		new_node->next = oldHead;
		L->head_ptr = new_node;
		L->manyNodes++;
	}
}
void append(List L, int data) {
	if (L == NULL) {
		exit(1);
	}
	Node new_node = newNode(data);
	if (L->manyNodes == 0) {
		L->head_ptr = new_node;
		L->tail_ptr = new_node;
		L->manyNodes = 1;
	}
	else {
		Node prevTail = L->tail_ptr;
		prevTail->next = new_node;
		new_node->prev = L->tail_ptr;
		L->tail_ptr = new_node;
		L->manyNodes++;
	}
}
void insertBefore(List L, int data) {
	Node new_node = newNode(data);
	if (L->cursor == L->head_ptr) {
		Node head_node = L->head_ptr;
		new_node->next = L->head_ptr;
		head_node->prev = new_node;
		L->head_ptr = new_node;
		L->manyNodes++;
	}
	else {
		Node cursorNode = L->cursor;
		Node preNode = cursorNode->prev;
		preNode->next = new_node;
		new_node->next = cursorNode;
		cursorNode->prev = new_node;
		new_node->prev = preNode;
		L->manyNodes++;
	}
}
void insertAfter(List L, int data) {
	if (L->tail_ptr == L->cursor) {
		Node cursor_node = L->cursor;
		Node new_node = newNode(data);
		new_node->next = cursor_node->next;
		new_node->prev = cursor_node;
		L->tail_ptr = new_node;
		cursor_node->next = new_node;
		L->manyNodes++;
	}
	else {
		Node cursor_node = L->cursor;
		Node new_node = newNode(data);
		new_node->next = cursor_node->next;
		new_node->prev = cursor_node;
		cursor_node->next = new_node;
		L->manyNodes++;
	}
}
void delete(List L) {
	Node n = L->cursor;
	if (L == NULL) {
		printf("Queue Error: calling Dequeue() on NULL Queue reference\n");
		exit(1);
	}
	if (isEmpty(L)) {
		printf("Queue Error: calling Dequeue on an empty Queue\n");
		exit(1);
	}
	if (L->manyNodes == 1) {
		freeNode(&n);
		L->head_ptr = NULL;
		L->tail_ptr = NULL;
		L->cursor = NULL;
	}
	else if (n == L->head_ptr) {
		L->head_ptr = n->next;
		L->cursor = NULL;
		freeNode(&n);
	}
	else if (n == L->tail_ptr) {
		L->tail_ptr = n->prev;
		L->cursor = NULL;
		freeNode(&n);
	}
	else {
		Node prevN = n->prev;
		Node nextN = n->next;
		prevN->next = nextN;
		nextN->prev = prevN;
		L->cursor = NULL;
		freeNode(&n);
	}

	L->manyNodes--;

}
void deleteFront(List L) {
	if (L->manyNodes == 0 || L == NULL) {

	}
	else if (L->manyNodes == 1) {
		freeNode(&L->head_ptr);
		L->head_ptr = NULL;
		L->tail_ptr = NULL;
		L->cursor = NULL;
		L->manyNodes = 0;
	}
	else {
		Node head = L->head_ptr;
		Node nextHead = head->next;
		nextHead->prev = NULL;
		head = NULL;
		if (L->cursor == L->head_ptr)
			L->cursor = NULL;
		freeNode(&L->head_ptr);
		L->head_ptr = nextHead;
		L->manyNodes--;
	}
}
void deleteBack(List L) {
	Node tail = L->tail_ptr;
	L->tail_ptr = tail->prev;
	if (L->cursor == tail) {
		L->cursor = NULL;
	}
	freeNode(&tail);
	L->manyNodes--;
}
void printList(FILE* out, List L) {
	Node N = NULL;

	if (L == NULL) {
		printf("Queue Error: calling printQueue() on NULL Queue reference\n");
		exit(1);
	}
	N = L->head_ptr;
	for (int i = 0; i < L->manyNodes - 1; i++) {
		fprintf(out, "%d ", N->element);
		fflush(out);
		N = N->next;
	}
	fprintf(out, "%d ", N->element);
	fflush(out);
	fprintf(out, "\n");
	fflush(out);
}

int equals(List A, List B) {
	if (A->manyNodes != B->manyNodes) {
		return 0;
	}
	Node a_node = A->head_ptr;
	Node b_node = B->head_ptr;
	for (int i = 0; i < A->manyNodes; i++) {
		if (a_node->element != b_node->element) {
			return 0;
		}
	}
	return 1;
}

List copyList(List L) {
	List copy = newList();
	if (L->manyNodes == 0) {
		return copy;
	}
	Node readNode = L->head_ptr;
	Node copyNode = newNode(readNode->element);
	copy->head_ptr = copyNode;
	copy->manyNodes = 1;
	if (L->manyNodes == 1) {
		copy->tail_ptr = copyNode;
		return copy;
	}
	Node prevNode;
	while (copy->manyNodes != L->manyNodes) {
		readNode = readNode->next;
		prevNode = copyNode;
		copyNode = newNode(readNode->element);
		copyNode->prev = prevNode;
		prevNode->next = copyNode;
		copy->manyNodes++;
	}
	copy->tail_ptr = copyNode;
	return copy;
}
