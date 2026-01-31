#include "ft_malloc.h"

int main() {
    char *string = ft_malloc(15);
    string = "Hello, World!\n";
    ft_printf("%s", string);
    ft_free(string);
    return 0;
}
