#ifndef HEAP_H
#define HEAP_H

void InitHeap(void* base, int size);
void* Allocate(int size);
void Free(void* ptr);

#endif
