struct bst;

struct bst* bst_create();
void bst_destroy(struct bst *tree);

int bst_insert(struct bst *tree, int data);
// returns 1 if in bst, 0 if not
int bst_search(struct bst *tree, int data);
