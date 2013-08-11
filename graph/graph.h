#ifdef DEBUG
#define D
#else
#define D for (;0;)
#endif

struct vertex;
struct graph;

struct graph *graph_create();
void graph_destroy(struct graph *g);
void graph_print(struct graph *g);

// adds a vertex of the given value to the graph
struct vertex *graph_vertex_add(struct graph *g, int data);
// removes given vertex from graph
void graph_vertex_remove(struct graph *g, struct vertex *v);
int graph_vertex_num(struct graph *g);

struct edge *graph_edge_add(struct graph *g, struct vertex *from,
                            struct vertex *to, int weight);
void graph_edge_remove(struct graph *g, struct vertex *from,
                       struct vertex *to);
int graph_edge_num(struct graph *g);
