#pragma once

#include "mem.h"

struct mem_t* mlist_get_free(struct mem_t *list, size_t request);
struct mem_t* mlist_get_last(struct mem_t *list);
struct mem_t* mlist_get_block(struct mem_t *list, char *ptr);
struct mem_t* mlist_get_prev(struct mem_t *list, struct mem_t *blk);