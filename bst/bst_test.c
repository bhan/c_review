#include "bst.h"
#include "common.h"
#include <assert.h>
#include <stdio.h>

int main() {
  struct bst *tree = bst_create();
  assert(bst_is_valid(tree));

  int values[] = {10, 5, 0, 8, 20, 15, 25};
  int len_values = sizeof(values)/sizeof(values[0]);

  int notvalues[] = {-1, 50, 100};
  int len_notvalues = sizeof(notvalues)/sizeof(notvalues);

  for (int i = 0; i < len_values; ++i) {
      bst_insert(tree, values[i]);
      assert(bst_is_valid(tree));
  }
  bst_print(tree);

  for (int i = 0; i < len_values; ++i)
      assert(bst_search(tree, values[i]));

  for (int i = 0; i < len_notvalues; ++i)
      assert(bst_search(tree, notvalues[i]) == 0);

  for (int i = 0; i < len_values; ++i) {
      assert(bst_remove(tree, values[i]));
      assert(bst_is_valid(tree));
  }

  for (int i = 0; i < len_notvalues; ++i) {
      assert(bst_remove(tree, notvalues[i]) == 0);
      assert(bst_is_valid(tree));
  }

  bst_destroy(tree);

  printf("No assertion failures. All tests pass!\n");
  return 0;
}
