#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

#ifndef INIT_SIZE
#define INIT_SIZE 10
#endif

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */


graph_t* enlarge_graph(graph_t *g){
    int n = g->capacity == 0 ? INIT_SIZE : g->capacity * 2;
    /* double the memory */
    edge_t *e = (edge_t*)malloc(n * sizeof(edge_t));
    memcpy(e, g->edges, g->num_edges * sizeof(edge_t));
    free(g->edges);
    g->edges = e;
    g->capacity = n;
    return g;
}
// - function -----------------------------------------------------------------
graph_t* allocate_graph() 
{
    graph_t *g = (graph_t*) malloc(sizeof(graph_t));
    g->edges = NULL;
    g->num_edges = 0;
    g->capacity = 0;
    return g;
    //return NULL;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t **graph)
{
    if((*graph)->capacity > 0){
        free((*graph)->edges);
    }
    free(*graph);
    *graph = NULL;
}

// - function -----------------------------------------------------------------
void load_txt(const char *fname, graph_t *graph)
{
    FILE *fp = fopen(fname, "r");
    
    int from;
    int to;
    int cost;
    while (fscanf(fp, "%d %d %d", &from, &to, &cost) == 3){
        if (graph->capacity <= graph->num_edges){
            enlarge_graph(graph);
        }
        
        (graph->edges + graph->num_edges)->from = from;
        (graph->edges + graph->num_edges)->to = to;
        (graph->edges + graph->num_edges)->cost = cost;
        
        /*
         * graph->edges[graph->num_edges]->to = to;
         * graph->edges[graph->num_edges]->cost = cost;
        */
        
        ++graph->num_edges;
    }
    fclose(fp);
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
    FILE *fp = fopen(fname, "r");
    
    
    enlarge_graph(graph);

    

    while(!feof(fp)){
    	edge_t *e = graph->edges + graph->num_edges;

		if(graph->num_edges < graph->capacity) {
			
			if(fread(e, sizeof(edge_t), 1, fp) != 1) break;

			graph->num_edges += 1;
			++e;

		} else {
			enlarge_graph(graph);
		}
    }
    fclose(fp);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname)
{
    FILE *fp = fopen(fname, "w");
    int from, to, cost;
    for (int i = 0; i < graph->num_edges; i++){
        
        from = (graph->edges + i)->from;
        to = (graph->edges + i)->to;
        cost = (graph->edges + i)->cost;
        fprintf(fp, "%d %d %d\n", from, to, cost);
    }
    fclose(fp);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
    FILE *fp = fopen(fname, "w");
    for (int i = 0; i < graph->num_edges; i++){
        fwrite(&graph->edges[i], sizeof(edge_t), 1, fp);
    }
    fclose(fp);
}

