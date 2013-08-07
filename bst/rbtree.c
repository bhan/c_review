#include "bst.h"
#include <assert.h>
#include <stdlib.h>

enum node_color {
  BLACK,
  RED
};

struct node {
  int data;
  enum node_color color;
  struct node *left;
  struct node *right;
};

struct bst {
  struct node *root;
  int size;
};

static struct node* bst_node_create(int data, enum node_color color) {
  struct node *bst_node = (struct node*)malloc(sizeof(struct node));
  if (bst_node == NULL)
    return NULL;
  bst_node->data = data;
  bst_node->color = color;
  bst_node->left = NULL;
  bst_node->right = NULL;
  return bst_node;
}

struct bst* bst_create() {
  struct bst *tree = (struct bst*)malloc(sizeof(struct bst));
  if (tree == NULL)
    return NULL;
  tree->root = NULL;
  tree->size = 0;
  return tree;
}

void bst_destroy(struct bst* tree) {
  assert(tree != NULL);
  assert(tree->root == NULL);
  assert(tree->size == 0);
  free(tree);
}

int bst_add(struct bst* tree, int data) {
  assert(tree != NULL);
  // add root
  if (tree->size == 0) {
    struct node *bst_node = bst_node_create(data, BLACK);
    if (bst_node == NULL)
      return -1;
    return 0;
  }

  return 0;
}
