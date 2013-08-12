#ifdef DEBUG
#define D
#else
#define D for (;0;)
#endif

struct node {
    void *data;
    struct node *p;
    struct node *n;
};

struct llist {
    struct node *hd;
    struct node *tl;
    int len;
};

struct llist *
llist_create();
void
llist_destroy(struct llist *ll);

struct node *
llist_add(struct llist *ll, void *data);
void
llist_remove(struct llist *ll, struct node *n);
// find/return a node in the linkedlist, an equality function can be specified
struct node *
llist_find(struct llist *ll, struct node *n,
           int (*eq)(struct node *a, struct node *b));
