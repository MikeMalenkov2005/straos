#ifndef STRUCTS
#define STRUCTS

struct Node {
	void* val;
	struct Node* next;
}__attribute__((packed));

struct List {
	struct Node* head;
	struct Node* tail;
	int size;
}__attribute__((packed));

struct List* NewList();
int GetListSize(struct List list);
void AddToList(struct List* list, void* val);
bool InsertToList(struct Lisr* list, void* val, int index);
bool RemoveFromList(struct List* list, int index);
bool RemoveFromList(struct List* list, void* val);
bool ForEachInList(void (*action)(int));

#endif
