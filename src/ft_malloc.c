#include "ft_malloc.h"

static void init_heap() {
    t_block dummy;
    dummy.header.size = 0;
    dummy.header.next = &dummy;
}

void *ft_malloc(size_t bytes) {
    
}

void *ft_realloc(size_t bytes, void *address) {

}

void ft_free(void *address) {

}
