#include "graph.h"
#include <assert.h>
#include <stdio.h>

int main() {
    struct graph *g = graph_create();
    if (g == NULL) {
        printf("malloc error\n");
        return 1;
    }
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(values)/sizeof(values[0]);
    struct vertex *vertices[len];
    for (int i = 0; i < len; ++i) {
        vertices[i] = graph_vertex_add(g, values[i]);
        assert(vertices[i]);
        printf("Added vertex %p\n", vertices[i]);
    }
    graph_edge_add(g, vertices[0], vertices[7], 7);
    graph_edge_add(g, vertices[0], vertices[5], 5);
    graph_edge_add(g, vertices[0], vertices[3], 3);
    graph_edge_add(g, vertices[2], vertices[6], 8);
    graph_edge_add(g, vertices[5], vertices[4], 9);
    graph_edge_remove(g, vertices[0], vertices[7]);
    graph_edge_remove(g, vertices[0], vertices[5]);
    graph_edge_remove(g, vertices[2], vertices[6]);
    graph_edge_remove(g, vertices[5], vertices[4]);
    graph_edge_add(g, vertices[0], vertices[7], 7);
    graph_vertex_remove(g, vertices[0]);
    graph_print(g);

    graph_vertex_remove(g, vertices[1]);
    graph_vertex_remove(g, vertices[2]);
    graph_vertex_remove(g, vertices[3]);
    graph_vertex_remove(g, vertices[4]);
    graph_vertex_remove(g, vertices[5]);
    graph_vertex_remove(g, vertices[6]);
    graph_vertex_remove(g, vertices[7]);

    assert(graph_vertex_num(g) == 0);

    graph_destroy(g);

    return 0;
}
