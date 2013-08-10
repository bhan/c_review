struct bst;

struct bst* bst_create();
void bst_destroy(struct bst *tree);

// returns 1 on error, 0 on success
int bst_insert(struct bst *tree, int data);
// returns 1 if in bst, 0 if not
int bst_search(struct bst *tree, int data);
// returns 1 if removed, 0 if not in tree
int bst_remove(struct bst *tree, int data);
