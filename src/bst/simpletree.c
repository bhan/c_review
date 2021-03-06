#include <assert.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *l;
    struct node *r;
};

struct bst {
    struct node *root;
};

struct node *node_create(int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL)
        return NULL;
    new_node->data = data;
    new_node->l = NULL;
    new_node->r = NULL;
    return new_node;
}

struct bst *bst_create() {
    struct bst *tree = malloc(sizeof(struct bst));
    if (tree == NULL)
        return NULL;
    tree->root = NULL;
    return tree;
}

static void free_nodes(struct node *cur) {
    if (cur == NULL)
        return;
    free_nodes(cur->l);
    free_nodes(cur->r);
    free(cur);
}

void bst_destroy(struct bst *tree) {
    assert(tree != NULL);
    free_nodes(tree->root);
    free(tree);
}

int bst_insert(struct bst *tree, int data) {
    assert(tree != NULL);

    if (tree->root == NULL) {
        struct node *new_node = node_create(data);
        if (new_node == NULL)
            return 1;
        tree->root = new_node;
    }

    struct node **to_modify = NULL;
    struct node *cur = tree->root;
    while (cur != NULL) {
        if (cur->data > data) {
            // new node belongs to left subtree
            to_modify = &cur->l;
            cur = cur->l;
        } else if (cur->data < data) {
            // new node belongs to right subtree
            to_modify = &cur->r;
            cur = cur->r;
        } else {
            // element is already in the tree
            return 0;
        }
    }
    struct node *new_node = node_create(data);
    if (new_node == NULL)
        return 1;
    *to_modify = new_node;

    return 0;
}

int bst_search(struct bst *tree, int data) {
    assert(tree != NULL);

    struct node *cur = tree->root;
    while (cur != NULL) {
        if (cur->data > data) {
            cur = cur->l;
        } else if (cur->data < data) {
            cur = cur->r;
        } else
            return 1;
    }
    return 0;
}

int bst_remove(struct bst *tree, int data) {
    assert(tree != NULL);

    struct node **to_modify = &tree->root;
    struct node *cur = tree->root;
    while (cur != NULL) {
        if (cur->data > data) {
            to_modify = &cur->l;
            cur = cur->l;
        } else if (cur->data < data) {
            to_modify = &cur->r;
            cur = cur->r;
        } else {
            if (cur->l == NULL && cur->r == NULL) {
                // leaf node
                free(cur);
                *to_modify = NULL;
            } else if (cur->r == NULL) {
                // only left subtree
                *to_modify = cur->l;
                free(cur);
            } else {
                // right subtree exists
                /*                  10
                 *          05------||------20
                 *    00----||----08  15----||----25
                 *     |--03  06--|
                 */
                // replace with the closest value larger than the node removed
                // (arbitrary choice which one)
                to_modify = &cur->r;
                struct node* replace = cur->r;
                // traverse to leftmost child
                while (replace->l != NULL) {
                    to_modify = &replace->l;
                    replace = replace->l;
                }

                // replace cur's value with that of replace
                cur->data = replace->data;

                // free replace and update the pointer to it to NULL
                free(replace);
                *to_modify = NULL;
            }
            return 1;
        }
    }
    return 0;
}
