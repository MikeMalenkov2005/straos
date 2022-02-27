#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "../drivers/vga_text.h"

struct HeapBlock
{
	struct HeapBlock* next;
	struct HeapBlock* prev;
	int32_t info;
}__attribute__((packed));

struct Heap
{
	struct HeapBlock* base;
	int32_t size;
}__attribute__((packed));

bool IsFree(struct HeapBlock* block)
{
	return block -> info > 0;
}

struct Heap HEAP = { NULL, 0 };

void InitHeap(void* base, int32_t size)
{
	HEAP.size = size & 0x7FFFFFFF;
	HEAP.base = (struct HeapBlock*) base;
	HEAP.base -> prev = NULL;
	HEAP.base -> next = NULL;
	HEAP.base -> info = HEAP.size - sizeof(struct HeapBlock);
	return;
}

void* Allocate(int32_t size)
{
	int32_t trueSize = size & 0x7FFFFFFF;
	if(HEAP.base == NULL || HEAP.size == 0)return NULL;
	struct HeapBlock* block = HEAP.base;
	struct HeapBlock* check = NULL;
	while(block != NULL)
	{
		if(IsFree(block) && block -> info >= trueSize && (check == NULL || block -> info < check -> info))check = block;
		block = block -> next;
	}
	if(check == NULL)return NULL;
	void* ptr = (void*) &(check[1]);
	if(check -> info > trueSize + sizeof(struct HeapBlock))
	{
		struct HeapBlock* newb = (struct HeapBlock*) (ptr + trueSize);
		newb -> info = check -> info - trueSize - sizeof(struct HeapBlock);
		if(check -> next != NULL)check -> next -> prev = newb;
		newb -> next = check -> next;
		check -> next = newb;
		newb -> prev = check;
		check -> info = trueSize | 0x80000000;
	}
	check -> info = check -> info | 0x80000000;
	return ptr;
}

void Free(void* ptr)
{
	struct HeapBlock* block = &(((struct HeapBlock*) ptr)[-1]);
	if((void*) block < (void*) HEAP.base || (void*) block >= (void*) HEAP.base + HEAP.size)return;
	block -> info = block -> info & 0x7FFFFFFF;
	struct HeapBlock* next = block -> next;
	struct HeapBlock* prev = block -> prev;
	if(next != NULL && IsFree(next))
	{
		block -> info = block -> info + next -> info + sizeof(struct HeapBlock);
		next = next -> next;
		block -> next = next;
		if(next != NULL)next -> next -> prev = block;
	}
	if(prev != NULL && IsFree(prev))
	{
		prev -> info = prev -> info + block -> info + sizeof(struct HeapBlock);
		next = block -> next;
		prev -> next = next;
		if(next != NULL)next -> prev = prev;
	}
	return;
}
