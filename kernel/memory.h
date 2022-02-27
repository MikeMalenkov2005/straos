#ifndef HEAP_H
#define HEAP_H

void InitHeap(void* base, int32_t size);
void* Allocate(int32_t size);
void Free(void* ptr);

#endif
