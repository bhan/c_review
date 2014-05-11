#include "llist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct llist *
llist_create() {
    struct llist *ll = (struct llist *)malloc(sizeof(struct llist));
    if (ll == NULL)
        return NULL;
    ll->hd = NULL;
    ll->tl = NULL;
    ll->len = 0;
    return ll;
}
void
llist_destroy(struct llist *ll) {
    assert(ll != NULL);
    assert(ll->hd == NULL);
    assert(ll->tl == NULL);
    assert(ll->len == 0);
    free(ll);
}

struct node *
llist_add(struct llist *ll, void *data) {
    assert(ll != NULL);
    assert(data != NULL);
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (n == NULL)
        return NULL;
    n->data = data;

    /* empty linked list */
    if (ll->hd == NULL) {
        assert(ll->tl == NULL);
        assert(ll->len == 0);
        n->p = NULL;
        n->n = NULL;
        ll->hd = n;
        ll->tl = n;
        ++ll->len;
        return n;
    }

    /* linked list with at least one node, insert at end (arbitrary choice) */
    assert(ll->tl->n == NULL);
    ll->tl->n = n; //make current tail's next point to new node
    n->p = ll->tl; //make new node's prev point to current tail
    ll->tl = n; // make current tail the new node to reflect reality
    ++ll->len;
    return n;
}

void
llist_remove(struct llist *ll, struct node *n) {
    assert(ll != NULL);
    assert(n != NULL);

    int found = 0;
    for (struct node *cur = ll->hd; cur != NULL; cur = cur->n) {
        if (cur == n) {
            found = 1;
            break;
        }
    }
    assert(found);

    if (n == ll->hd) {
        // make the head's next node to the head
        ll->hd = ll->hd->n;
    }
    if (n == ll->tl) {
        // make the tail's prev node to the tail
        ll->tl = ll->tl->p;
    }

    if (n->p != NULL) {
        // make node's prev's next the node's next
        n->p->n = n->n;
    }
    if (n->n != NULL) {
        // make node's next's prev the node's prev
        n->n->p = n->p;
    }
    free(n);
    --ll->len;
}

struct node*
llist_find(struct llist *ll, struct node *n,
           int (*eq)(struct node *a, struct node *b)) {
    D printf("ENTER llist_find ll:%p, n:%p, eq:%p\n", ll, n, eq);
    assert(ll != NULL);
    assert(n != NULL);

    if (eq == NULL) {
        D printf("llist_find: no eq function provided, comparing pointers\n");
        for (struct node *cur = ll->hd; cur != NULL; cur = cur->n) {
            if (cur == n)
                return cur;
        }
        return NULL;
    }

    D printf("llist_find: using provided eq function\n");
    for (struct node *cur = ll->hd; cur != NULL; cur = cur->n) {
        if (eq(cur, n))
            return cur;
    }
    return NULL;
}
