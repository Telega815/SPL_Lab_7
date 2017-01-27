
#include "mem.h"
#include "mlist.h"

struct mem_t* head;

static size_t correct_size(size_t sz){
	if(sz % 4096 == 0) return sz;
	else return sz + 4096 - sz % 4096;
}

static int near_fwd(struct mem_t *parent, struct mem_t *child)
{
	return ((char*) parent + sizeof(struct mem_t) + parent->capacity == (char*) child) ? 1 : 0;
}


static void cat(struct mem_t *blk){
	struct mem_t *prev;
	if(blk->next && blk->next->is_free == 1 && near_fwd(blk, blk->next) == 1){
			blk->capacity += blk->next->capacity + sizeof(struct mem_t);
			blk->next = blk->next->next;
		}

	prev = mlist_get_prev(head, blk);
	if(prev && prev->is_free == 1 && near_fwd(prev, blk) == 1){
		prev->capacity += blk->capacity + sizeof(struct mem_t);
		prev->next = blk->next;
	}
}

static void divide(struct mem_t *new, size_t sz)
{		
	struct mem_t *free = NULL;
	free = (struct mem_t*) ((char*) new + sizeof(struct mem_t) + sz);
	free->next = new->next;
	free->capacity = new->capacity - sz - sizeof(struct mem_t);
	free->is_free = 1;

	new->next = free;
	new->capacity = sz;		
}

static void* expand_heap(size_t sz){
	struct mem_t *new;

	new = (struct mem_t*) VirtualAlloc(NULL, sz + sizeof(struct mem_t), MEM_COMMIT, PAGE_READWRITE);

	new->next = NULL;
	new->capacity = correct_size(sz + sizeof(struct mem_t)) - sizeof(struct mem_t);
	new->is_free = 1;
	
	mlist_get_last(head)->next = new;


	return new;
}

void* heap_init(size_t initial_size){
	head = (struct mem_t*) VirtualAlloc(NULL, initial_size, MEM_COMMIT, PAGE_READWRITE);

	head->next = NULL;
	head->capacity = correct_size(initial_size) - sizeof(struct mem_t);
	head->is_free = 1;

	return head;
}



void* _malloc(size_t query)
{
	struct mem_t* new;
	
	if (!head)
		heap_init(query);

	if (query == 0)
		return NULL;

	new =  mlist_get_free(head, query);

	//In case if there's no free list or not enough capacity, we geting new page
	if (!new)
		new = expand_heap(query);
	//-----------

	if (new->capacity - query > sizeof(struct mem_t) + 1)
			divide(new, query);
	
	new->is_free = 0;
	return (char*)new + sizeof(struct mem_t);
}



void _free(void *mem){

	if (!head || !mem)
		return;

	struct mem_t *blk;

	blk = mlist_get_block(head, mem);

	if(blk){
		blk->is_free = 1;

		cat(blk);
	}
	else printf("%s\n", "WRONG!!!");
}

