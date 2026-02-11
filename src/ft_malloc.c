#include "ft_malloc.h"

static t_block base;
static t_block *freep;

static void init_heap() {
    base.header.size = 0;
    base.header.next = &base;
    freep = &base;
}

static t_word btow(size_t bytes) {
    return (bytes + sizeof(t_header) - 1 / sizeof(t_header) - 1);
}

static t_block *getmem(t_word words) {
    size_t size;
    t_block *block;

    if (words < MINALLOC)
        words = MINALLOC;
    size = words * sizeof(t_header);
    block = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
    if (block == MAP_FAILED)
        return NULL;
    block->header.size = words;
    ft_free((void *)(block + 1));

    return freep;
}

void *ft_malloc(size_t bytes) {
    t_block *prev;
    t_block *curr;
    t_word words;

    if (freep == NULL)
        init_heap();
    words = btow(bytes);
    prev = freep;
    curr = prev->header.next;
    while (prev = curr) {
        if (curr->header.size >= words) {
            if (curr->header.size == words)
                prev->header.next = curr->header.next;
            else {
                curr->header.size -= words;
                curr += curr->header.size;
                curr->header.size = words;
            }
            freep = prev;
            return (void *)(curr + 1);
        }
        if (curr == freep) {
            curr = getmem(words);
            if (curr == NULL)
                return NULL;
        }
        curr = curr->header.next;
    }
}

void ft_free(void *ptr) {
    t_block *block;
    t_block *curr;

    if (ptr == NULL)
        return;
    block = (t_block *)ptr - 1;
    curr = freep;
    while (!(block > curr && block < curr->header.next)) {
        if (curr >= curr->header.next && (block > curr || block < curr->header.next))
            break;
        curr = curr->header.next;
    }
    if (block + block->header.size == curr->header.next) {
        block->header.size += curr->header.next->header.size;
        block->header.next = curr->header.next->header.next;
    } else
        block->header.next = curr->header.next;
    if (curr + curr->header.size == block) {
        curr->header.size += block->header.size;
        curr->header.next = block->header.next;
    } else
        curr->header.next = block;

    freep = curr;
}

// void *ft_realloc(size_t bytes, void *ptr) {
//     // TODO: Implement lmao
// }
