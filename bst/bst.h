struct bst;

struct bst* bst_create();
void bst_destroy(struct bst* tree);

int bst_add(struct bst* tree, int value);
