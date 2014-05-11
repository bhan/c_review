struct bst;

// return 1 if bst valid, 0 if not
int bst_is_valid(struct bst *tree);
// return value of rightmost node
int bst_rmost(struct bst *tree);
// return value of leftmost node
int bst_lmost(struct bst *tree);
void bst_print(struct bst *tree);
