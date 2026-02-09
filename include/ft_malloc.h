#include <sys/mman.h>
#include "../libft/include/libft.h"

#define MINALLOC 1024

typedef int32_t t_word;
typedef struct s_header t_header;
typedef struct s_block t_block;

struct s_header {
    t_word size;
    t_block *next; 
};

struct s_block {
    t_header header;
    // memory blocks...
};

void *ft_malloc(size_t bytes);
void *ft_realloc(size_t bytes, void *ptr);
void ft_free(void *ptr);
