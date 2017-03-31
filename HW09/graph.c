#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "graph.h"

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */
// - function -----------------------------------------------------------------

static void enlarge_graph(graph_t *graph) 
{
	graph->capacity = graph->capacity * 2;

	edge_t *e = realloc(graph->edges, graph->capacity * sizeof(edge_t));	
	if(!e) exit(111);	

	graph->edges = e;

}
// - function -----------------------------------------------------------------
graph_t* allocate_graph(void) 
{
	graph_t *g = (graph_t*) malloc(sizeof(graph_t));
	g->num_edges = 0;
	g->capacity = 100;
	
	edge_t *e = (edge_t*)malloc(g->capacity * sizeof(edge_t));
	if(!e) exit(111);

	g->edges = e;
	return g;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t **graph)
{
	if ((*graph)->capacity > 0) {
		free((*graph)->edges);
	}
	free(*graph);
	*graph = NULL;
}

static int fast_read(FILE *f) {
	char number[10];
	char didget;
	didget = fgetc(f);

	int idx = -1;

	while(didget != ' ' ) {
		idx++;
		number[idx] = didget;
		didget = fgetc(f);

		if(didget == EOF) return -1;
		
		if(didget == 10 || didget == -1) break;
	}

	number[idx + 1] = '\0';

	char * str = number;

	int final_number = 0;

	while( *str ) {
		final_number = final_number*10 + (*str++ - '0');
	}

	return final_number;
}
// - function faster reading input
void load_txt(const char *fname, graph_t *graph)
{
	FILE *f = fopen(fname, "r");

	if(!f){
		fprintf(stderr, "WRONG FILE\n");
		free_graph(&graph);
		exit(111);
	}

	int exit = 0;
   	while (!feof(f) && !exit) {
      	
      	if (graph->num_edges == graph->capacity) {
         	enlarge_graph(graph);
      	}

      	edge_t *e = graph->edges + graph->num_edges;

      	int from = 0;
      	int to = 0;
      	int cost = 0;
      	while (!feof(f) && graph->num_edges < graph->capacity) {

         	//int r = fscanf(f, "%d %d %d\n", &(e->from), &(e->to), &(e->cost));
      		from = fast_read(f);
      		to = fast_read(f);
      		cost = fast_read(f);

      		if(from < 0 || to < 0 || cost < 0){
      			exit = 1;
      			break;
      		}

      		e->from = from;
      		e->to = to;
      		e->cost = cost;

      		graph->num_edges += 1;
            e += 1;
      	}
   	}
   	fclose(f);

}


// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
	FILE *f = fopen(fname, "rb");

	if(!f){
		fprintf(stderr, "WRONG FILE\n");
		free_graph(&graph);
		exit(111);
	}

	if (graph->num_edges == graph->capacity) {
		enlarge_graph(graph);
	}

	while(!feof(f)) {

		edge_t *e = graph->edges + graph->num_edges;

		if(graph->num_edges < graph->capacity) {
			
			if(fread(e, sizeof(edge_t), 1, f) != 1) break;

			graph->num_edges += 1;
			e++;

		} else {
			enlarge_graph(graph);
		}
	}

   	fclose(f);
}

static void iprint(int n, FILE *f)
{ 
	if( n > 9 ){ 
		int a = n / 10;
		n -= 10 * a;
		iprint(a, f);
	}
	fputc('0'+n, f);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname)
{
	FILE *f = fopen(fname, "w");

	edge_t *e = graph->edges;
   	for (int i = 0; i < graph->num_edges; ++i, ++e) {
		//fprintf(f, "%d %d %d\n", e->from, e->to, e->cost);
		iprint(e->from, f);
		fputc(' ', f);
		iprint(e->to, f);
		fputc(' ', f);
		iprint(e->cost, f);
		fputc('\n', f);
	}
   	fclose(f);   	
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
	FILE *f = fopen(fname, "wb");
	edge_t *e = graph->edges;

   	for (int i = 0; i < graph->num_edges; ++i, ++e) {
		fwrite(&e->from, sizeof(e->from), 1, f);
		fwrite(&e->to, sizeof(e->to), 1, f);
		fwrite(&e->cost, sizeof(e->cost), 1, f);
	}

   	fclose(f);
}

