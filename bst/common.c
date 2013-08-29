#include "common.h"
#include "../utils/utils.h"
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXLEN 255

// every bst will have data, left, right in same place
struct node {
    int data;
    struct node *l;
    struct node *r;
};

// every bst is a pointer to the root node
struct bst {
    struct node *root;
};

static int bst_is_valid_helper(struct node *cur, int min, int max) {
    if (cur == NULL)
        return 1;
    else if (cur->data < min || cur->data > max)
        return 0;
    return bst_is_valid_helper(cur->l, min, cur->data) ||
        bst_is_valid_helper(cur->r, cur->data, max);
}

int bst_is_valid(struct bst *tree) {
    assert(tree != NULL);
    return bst_is_valid_helper(tree->root, INT_MIN, INT_MAX);
}

int bst_rmost(struct bst *tree) {
    assert(tree != NULL);
    struct node *cur;
    for (cur = tree->root; cur->r != NULL; cur = cur->r);
    return cur->data;
}

int bst_lmost(struct bst *tree) {
    assert(tree != NULL);
    struct node *cur;
    for (cur = tree->root; cur->l != NULL; cur = cur->l);
    return cur->data;
}

static void
bst_print_helper(struct node *cur, int level, int max_places) {
    if (cur == NULL)
        return;
    for (int i = 0; i < level; ++i) {
        for (int j = 0; j < max_places-1; ++j)
            printf(" ");
        // hopefully the compiler optimizes this for us
        if (i < level-1)
            printf("| ");
        else printf("|-");
    }
    int places = utils_get_places(cur->data);
    // pad unused places with '-'
    for (int i = 0; i < max_places-places; ++i)
        printf("-");
    printf("%d\n", cur->data);
    bst_print_helper(cur->l, level+1, max_places);
    bst_print_helper(cur->r, level+1, max_places);
}

void bst_print(struct bst *tree) {
    assert(tree != NULL);
    int max_places = utils_get_places(bst_rmost(tree));
    bst_print_helper(tree->root, 0, max_places);
}
