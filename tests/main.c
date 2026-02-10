#include "ft_malloc.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdalign.h>
#include <cstddef>

static void test_basic_alloc_free(void) {
    char *p = ft_malloc(16);
    assert(p != NULL);
    strcpy(p, "hello");
    assert(strcmp(p, "hello") == 0);
    ft_free(p);
}

static void test_multiple_alloc_free(void) {
    void *ptrs[128];
    for (int i = 0; i < 128; i++) {
        ptrs[i] = ft_malloc((size_t)(i + 1) * 8);
        assert(ptrs[i] != NULL);
        memset(ptrs[i], 0xA5, (size_t)(i + 1) * 8);
    }
    for (int i = 127; i >= 0; i--) {
        ft_free(ptrs[i]);
    }
}

static void test_realloc_grow_shrink(void) {
    char *p = ft_malloc(8);
    assert(p != NULL);
    memcpy(p, "abc", 4);

    p = ft_realloc(p, 64);
    assert(p != NULL);
    assert(strcmp(p, "abc") == 0);

    p = ft_realloc(p, 4);
    assert(p != NULL);
    assert(strcmp(p, "abc") == 0);

    ft_free(p);
}

static void test_edge_sizes(void) {
    void *p0 = ft_malloc(0);
    if (p0) {
        ft_free(p0);
    }

    void *p1 = ft_malloc(1);
    assert(p1 != NULL);
    ft_free(p1);

    void *p_big = ft_malloc(1024 * 1024);
    assert(p_big != NULL);
    ft_free(p_big);
}

static void test_alignment(void) {
    void *p = ft_malloc(sizeof(max_align_t));
    assert(p != NULL);
    assert(((uintptr_t)p % alignof(max_align_t)) == 0);
    ft_free(p);
}

static void test_reuse(void) {
    void *p1 = ft_malloc(64);
    assert(p1 != NULL);
    ft_free(p1);

    void *p2 = ft_malloc(64);
    assert(p2 != NULL);
    ft_free(p2);
}

static void stress_test(void) {
    const int N = 10000;
    void *ptrs[N];

    for (int i = 0; i < N; i++) {
        size_t sz = (size_t)((i % 256) + 1);
        ptrs[i] = ft_malloc(sz);
        assert(ptrs[i] != NULL);
        memset(ptrs[i], (int)(i & 0xFF), sz);
    }
    for (int i = 0; i < N; i += 2) {
        ft_free(ptrs[i]);
        ptrs[i] = NULL;
    }
    for (int i = 0; i < N; i += 2) {
        size_t sz = (size_t)(((i + 3) % 256) + 1);
        ptrs[i] = ft_malloc(sz);
        assert(ptrs[i] != NULL);
    }
    for (int i = 0; i < N; i++) {
        if (ptrs[i]) ft_free(ptrs[i]);
    }
}

int main(void) {
    test_basic_alloc_free();
    test_multiple_alloc_free();
    test_realloc_grow_shrink();
    test_edge_sizes();
    test_alignment();
    test_reuse();
    stress_test();

    return 0;
}
