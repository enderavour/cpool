#include "mempool.h"

struct _mempool
{
    struct _mempool *next;
};

static void *mempool_align(void *addr, size_t alignment)
{
    uintptr_t mem = (uintptr_t)addr;
    uintptr_t aligned = ((mem + (alignment - 1)) & ~(alignment - 1));
    return (void*)aligned;
}

uint32_t mempool_init(mempool **pool, mempool_ctx *ctx)
{  
    size_t chunk_size = sizeof(mempool) + ctx->partition_size;
    if (ctx->block_size < chunk_size || chunk_size == 0)
        return MEMPOOL_SIZE_MISMATCH;
    
    void *aligned_block = mempool_align(ctx->memory_block, chunk_size);

    uintptr_t offset = (uintptr_t)aligned_block - (uintptr_t)ctx->memory_block;
    if (offset >= ctx->block_size)
        return MEMPOOL_SIZE_MISMATCH; 

    size_t available_size = ctx->block_size - offset;
    size_t chunks_count = available_size / chunk_size;

    if (chunks_count == 0)
        return MEMPOOL_SIZE_MISMATCH;

    mempool *head = (mempool*)aligned_block;
    head->next = NULL;

    mempool *current = head;
    for (int32_t i = 1; i < chunks_count; ++i)
    {
        current->next = (mempool*)((uint8_t*)aligned_block + i * chunk_size);
        current = current->next;
    }
    current->next = NULL;

    *pool = aligned_block;
    return MEMPOOL_OK;
}

void *mempool_alloc(mempool **pool)
{
    if (!pool || !*pool)
        return NULL;
    
    mempool *block = *pool;
    *pool = block->next;
    return (void*)((uint8_t*)block + sizeof(mempool));
}

void mempool_free(mempool **pool, void *mem)
{
    if (!pool || !mem)
        return;

    mempool *begin = (mempool*)((uint8_t*)mem - sizeof(mempool));
    begin->next = *pool;
    *pool = begin;
}