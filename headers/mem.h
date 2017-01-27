#pragma once

#define _DEFAULT_SOURCE

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

//#include <sys/mman.h>

struct mem_t;

#pragma pack(push, 1)
struct mem_t 
{
	struct mem_t *next;
	size_t capacity;
	int is_free;
};
#pragma pack(pop)

void* _malloc(size_t query);
void _free(void *mem);
void* heap_init(size_t initial_size);

#define DEBUG_FIRST_BYTES 4

void memalloc_debug_struct_info(FILE *f, struct mem_t const* const address);

void memalloc_debug_heap(FILE *f, struct mem_t const* ptr);