#include "common.h"
#include "limits.h"
#include <assert.h>
#include <stdlib.h>

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
