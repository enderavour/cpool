#include <stdio.h>
#include "mempool.h"
#include <stdlib.h>
#include <string.h>

main()
{
    mempool_ctx ctx = {
        .partition_size = 8,
        .memory_block = malloc(161),
        .block_size = 161
    };

    mempool *pool;
    uint32_t err = mempool_init(&pool, &ctx);
    if (err == MEMPOOL_OK)
    {
        uint8_t *mem = (uint8_t*)mempool_alloc(&pool);
        strcpy(mem, "Hello!");
        mem[6] = 0;

        printf("%s\n", mem);
        mempool_free(&pool, mem);
        free(ctx.memory_block);
    }
    else
    {
       free(ctx.memory_block);
       printf("Allocation error!\n");
    }
    return 0;
}