#include "bst.h"

int main() {
  struct bst *tree = bst_create();
  bst_destroy(tree);

  return 0;
}
