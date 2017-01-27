#include "mlist.h"

struct mem_t* mlist_get_free(struct mem_t *list, size_t request)
{
	for (; list; list = list->next)
		if (list->is_free == 1 && list->capacity >= request) return list;
	return NULL;
}

struct mem_t* mlist_get_last(struct mem_t *list){
	for (; list->next; list = list->next){;}
	return list;
}

struct mem_t* mlist_get_block(struct mem_t *list, char *mem){
	for (; list; list = list->next)
		if (list == (struct mem_t*)(mem - sizeof(struct mem_t))) return list;
	return NULL;
}

struct mem_t* mlist_get_prev(struct mem_t *list, struct mem_t *blk){
	for (; list; list = list->next)
		if (list->next == blk) return list;
	return NULL;
}