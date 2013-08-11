#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct edge {
    int weight;
    struct vertex *adj;
};

struct vertex {
    int data;
    struct edge **edges;
    int edges_num;
    int edges_capacity;
};

struct graph {
    struct vertex **vertices;
    int vertices_num;
    int vertices_capacity;
    int edges_num;
};

// returns index of vertex in graph's vertices field
static int graph_vertex_find(struct graph *g, struct vertex *v) {
    assert(g != NULL);
    assert(v != NULL);
    for (int pos = 0; pos < g->vertices_num; ++pos) {
        if (g->vertices[pos] == v)
            return pos;
    }
    return -1;
}

struct graph *graph_create() {
    D printf("ENTER graph_create\n");

    struct graph *g = (struct graph*)malloc(sizeof(struct graph));
    if (g == NULL)
        return NULL;
    g->vertices = NULL;
    g->vertices_num = 0;
    g->vertices_capacity = 0;
    g->edges_num = 0;

    D graph_print(g);
    D printf("EXIT graph_create return g:%p\n", g);
    return g;
}

void graph_destroy(struct graph *g) {
    D printf("ENTER graph_destroy\n");

    assert(g != NULL);
    assert(g->vertices == NULL);
    assert(g->vertices_num == 0);

    D graph_print(g);
    D printf("freeing %p\n", g);

    free(g);

    D printf("EXIT graph_destroy");
}

static void edge_print(struct edge *e) {
    assert(e != NULL);
    printf("\tEdge %p weight:%d adj:%p\n", e, e->weight, e->adj);
}

static void vertex_print(struct vertex *v) {
    assert(v != NULL);
    printf("Vertex %p data:%d edges_num:%d edges_capacity:%d\n", v, v->data,
           v->edges_num, v->edges_capacity);
    printf("\tEdges: {\n");
    for (int i = 0; i < v->edges_num; ++i) {
        printf("\t");
        edge_print(v->edges[i]);
    }
    printf("\t}\n");
}

void graph_print(struct graph *g) {
    assert(g != NULL);
    printf("g:%p, vertices_num:%d, vertices_capacity:%d, edges_num:%d\n",
           g, g->vertices_num, g->vertices_capacity, g->edges_num);
    printf("vertices:{\n");
    for (int i = 0; i < g->vertices_num; ++i) {
        printf("\t");
        vertex_print(g->vertices[i]);
    }
    printf("}\n");
}

struct vertex *graph_vertex_add(struct graph *g, int data) {
    assert(g != NULL);
    struct vertex *v = (struct vertex*)malloc(sizeof(struct vertex));
    if (v == NULL)
        return NULL;
    v->data = data;
    v->edges = NULL;
    v->edges_num = 0;
    v->edges_capacity = 0;

    // double capacity if at capacity
    if (g->vertices_num == g->vertices_capacity) {
        int new_capacity = 1;
        if (g->vertices_capacity > 0)
            new_capacity = 2*g->vertices_capacity;
        int new_size = new_capacity*sizeof(struct vertex*);
        struct vertex **new_vertices = (struct vertex**)realloc(g->vertices,
                                                                new_size);
        if (new_vertices == NULL) {
            free(v);
            return NULL;
        }
        g->vertices = new_vertices;
        g->vertices_capacity = new_capacity;
    }

    // add vertex to vertices
    g->vertices[g->vertices_num] = v;
    ++g->vertices_num;

    return v;
}

void vertex_destroy(struct vertex *v) {
    D printf("ENTER vertex_destroy v:%p\n", v);
    assert(v != NULL);
    if (v->edges_num > 0) {
        assert(v->edges != NULL);
        for (int i = 0; i < v->edges_num; ++i) {
            free(v->edges[i]);
        }
        free(v->edges);
    }
    D printf("vertex_destroy: freeing %p\n", v);
    free(v);
    D printf("EXIT vertex_destroy\n");
}

void graph_vertex_remove(struct graph *g, struct vertex *v) {
    D printf("ENTER graph_vertex_remove g:%p, v:%p\n", g, v);
    D graph_print(g);
    assert(g != NULL);
    assert(v != NULL);

    int pos = graph_vertex_find(g, v);
    assert(pos >= 0);
    D printf("graph_vertex_remove: pos:%d\n", pos);

    // free vertex, move last position vertex to this position
    int edges_num = g->vertices[pos]->edges_num;
    vertex_destroy(g->vertices[pos]);
    g->edges_num -= edges_num;
    g->vertices[pos] = g->vertices[g->vertices_num-1];
    --g->vertices_num;

    // halve capacity if size is half the capacity
    if (g->vertices_num == g->vertices_capacity/2) {
        int new_capacity = g->vertices_capacity/2;
        int new_size = new_capacity*sizeof(struct vertex*);
        g->vertices = (struct vertex**)realloc(g->vertices, new_size);
        g->vertices_capacity = new_capacity;
        if (new_capacity == 0)
            g->vertices = NULL;
    }
    D printf("EXIT graph_vertex_remove\n");
}

int graph_vertex_num(struct graph *g) {
    return g->vertices_num;
}

struct edge *graph_edge_add(struct graph *g, struct vertex *from,
                            struct vertex *to, int weight) {
    D printf("ENTER graph_edge_add g:%p, from:%p, to:%p, weight:%d\n",
             g, from, to, weight);
    assert(g != NULL);
    assert(from != NULL);
    assert(to != NULL);
    assert(graph_vertex_find(g, from) >= 0);
    assert(graph_vertex_find(g, to) >= 0);

    struct edge *e = (struct edge*)malloc(sizeof(struct edge));
    if (e == NULL)
        return NULL;
    e->weight = weight;
    e->adj = to;

    // double capacity if at capacity
    if (from->edges_num == from->edges_capacity) {
        int new_capacity = 1;
        if (from->edges_capacity > 0)
            new_capacity = 2*from->edges_capacity;
        int new_size = new_capacity*sizeof(struct edge*);
        struct edge **new_edges = (struct edge**)realloc(from->edges, new_size);
        if (new_edges == NULL) {
            free(e);
            return NULL;
        }
        from->edges = new_edges;
        from->edges_capacity = new_capacity;
    }

    from->edges[from->edges_num] = e;
    ++from->edges_num;
    ++g->edges_num;

    D printf("EXIT graph_edge_add\n");
}

void graph_edge_remove(struct graph *g, struct vertex *from,
                       struct vertex *to) {
    D printf("ENTER graph_edge_remove g:%p, from:%p, to:%p\n",
             g, from, to);
    assert(g != NULL);
    assert(from != NULL);
    assert(to != NULL);
    assert(graph_vertex_find(g, from) >= 0);
    assert(graph_vertex_find(g, to) >= 0);

    // find where to is in from's adjacency list
    int pos = -1;
    for (int i = 0; i < from->edges_num; ++i) {
        if (from->edges[i]->adj == to) {
            pos = i;
            break;
        }
    }
    assert(pos >= 0);

    // free edge, move the last edge into the freed edge's place
    free(from->edges[pos]);
    from->edges[pos] = from->edges[from->edges_num-1];
    --from->edges_num;
    --g->edges_num;

    // halve capacity if capacity at 1/2 num
    if (from->edges_num == from->edges_capacity/2) {
        int new_capacity = from->edges_capacity/2;
        int new_size = new_capacity*sizeof(struct edge*);
        from->edges = (struct edge**)realloc(from->edges, new_size);
        from->edges_capacity = new_capacity;
        if (new_capacity == 0)
            from->edges = NULL;
    }

    D printf("EXIT graph_edge_remove\n");
}

int graph_edge_num(struct graph *g) {
    assert(g != NULL);
    return g->edges_num;
}
