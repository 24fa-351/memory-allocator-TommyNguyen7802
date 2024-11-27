#ifndef MEMORY_ALLOCATOR_H
#define MEMORY_ALLOCATOR_H

#include <stddef.h>

void* my_malloc(size_t size);
void my_free(void* ptr);
void* my_realloc(void* ptr, size_t size);

#define xmalloc my_malloc
#define xfree my_free

#endif // MEMORY_ALLOCATOR_H
