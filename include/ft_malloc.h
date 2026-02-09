#include "../libft/include/libft.h"

typedef int32_t t_word;

typedef struct s_header t_header;
typedef struct s_block t_block;

struct s_header {
    size_t size;
    t_block *next; 
};

struct s_block {
    t_header header;
    // memory
};

typedef struct s_heap {
    t_block *freep;
    int block_count;
}   t_heap;

const int word_size = sizeof(t_header);

void *ft_malloc(size_t bytes);
void *ft_realloc(size_t bytes, void *address);
void ft_free(void *address);
