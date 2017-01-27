#include "mem.h"


int main(int argc, char **argv)
{
	
	void* abir = _malloc(4000);
	memalloc_debug_heap(stdout, abir - sizeof(struct mem_t));

	printf("\n%s\n", "After free:");
	_free(abir);
	memalloc_debug_heap(stdout, abir - sizeof(struct mem_t));

	printf("\n%s\n", "------------------------------------------");
	void *abr = _malloc(4200);
	memalloc_debug_heap(stdout, abir - sizeof(struct mem_t));
	//memalloc_debug_heap(stdout, abr - sizeof(struct mem_t));

	printf("\n%s\n", "After free:");
	_free(abr);
	memalloc_debug_heap(stdout, abir - sizeof(struct mem_t));

	return 0;
}