#ifndef MEMPOOL_ALLOC_IMPL
#define MEMPOOL_ALLOC_IMPL

#include <stdint.h>

#define MEMPOOL_OK 0
#define MEMPOOL_SIZE_MISMATCH 1
#define MEMPOOL_ALLOC_FAILED 2 // not used yet
#define MEMPOOL_ALIGNMENT_MISMATCH 3 // not used yet

typedef struct _mempoolctx
{
    void *memory_block;
    size_t block_size;
    size_t partition_size;
} mempool_ctx;


typedef struct _mempool mempool;

uint32_t mempool_init(mempool **pool, mempool_ctx *ctx);
void *mempool_alloc(mempool **pool);
void mempool_free(mempool **pool, void *mem);

#endif
