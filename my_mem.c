#include "my_mem.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

#define BLOCK_SIZE sizeof(Block)

void* memory_start;
Block* free_list;

void init_memory_manager(size_t size) {
    memory_start = (void*)sbrk(size);
    free_list = (Block*)memory_start;
    free_list->size = size - BLOCK_SIZE;
    free_list->free = 1;
    free_list->next = NULL;
    printf("Memory manager initialized with %zu bytes\n", size);
}

void* my_malloc(size_t size) {
    Block* current = free_list;
    while (current != NULL) {
        printf("Checking block at %p size=%zu, free=%d\n", (void*)current, current->size, current->free);
        if (current->free && current->size >= size) {
            if (current->size >= size + BLOCK_SIZE + 1) {
                Block* new_block = (Block*)((char*)current + BLOCK_SIZE + size);
                new_block->size = current->size - size - BLOCK_SIZE;
                new_block->free = 1;
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }
            current->free = 0;
            printf("Allocated %zu bytes at %p\n", size, (void*)(current + 1));
            return (void*)(current + 1);
        }
        current = current->next;
    }
    printf("malloc failed: no suitable block found\n");
    return NULL; // No suitable block found
}

void my_free(void* ptr) {
    if (ptr == NULL) return;
    Block* block = (Block*)ptr - 1;
    block->free = 1;
    printf("Freed block at %p\n", ptr);

    Block* current = free_list;
    while (current != NULL) {
        if (current->free && current->next && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

void* my_realloc(void* ptr, size_t size) {
    if (ptr == NULL) return my_malloc(size);
    Block* block = (Block*)ptr - 1;
    if (block->size >= size) return ptr;
    void* new_ptr = my_malloc(size);
    if (new_ptr == NULL) return NULL;
    memcpy(new_ptr, ptr, block->size);
    my_free(ptr);
    return new_ptr;
}

__attribute__((constructor))
void initilize_memory() {
    init_memory_manager(1024 * 1024);
}