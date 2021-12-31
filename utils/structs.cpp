struct List* NewList()
{
	struct List list = {.head = NULL, .tail = NULL, .size = 0};
	return *list;
}

void AddToList(struct List* list, void* val)
{
	struct Node node = {.val = val, .next = NULL}
	if(list.size == 0)
	{
		list.head = &node;
		list.tail = &node;
	}
	else
	{
		(*list.tail).next = &node;
		tail = &node
	}
}
