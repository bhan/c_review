#include "llist.h"
#include <assert.h>
#include <stdio.h>

int
main() {
    struct llist *ll = llist_create();
    if (ll == NULL) {
        printf("Could not create linked list\n");
        return 1;
    }
    assert(ll->len == 0);

    int data[] = {0, 1, 2, 3, 4, 5};

    struct node *a = llist_add(ll, &data[0]);
    assert(ll->len == 1);
    assert(llist_find(ll, a, NULL) == a);

    struct node *b = llist_add(ll, &data[1]);
    assert(ll->len == 2);
    assert(llist_find(ll, a, NULL) == a);
    assert(llist_find(ll, b, NULL) == b);

    llist_remove(ll, a);
    assert(ll->len == 1);
    assert(llist_find(ll, a, NULL) == NULL);
    assert(llist_find(ll, b, NULL) == b);

    llist_remove(ll, b);
    assert(ll->len == 0);
    assert(llist_find(ll, a, NULL) == NULL);
    assert(llist_find(ll, b, NULL) == NULL);

    llist_destroy(ll);

    return 0;
}
