#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(void) {
	char in[] = "in";
	char out[] = "out";
	char bin[] = "bin";
	char bin2[] = "bin2";
	
	graph_t *g = allocate_graph();
	printf("Alocated.\n");
	
	load_txt(in, g);
	printf("Loaded\n");
	
	save_txt(g, out);
	printf("Saved.\n");

	save_bin(g, bin);
	printf("Saved bin.\n");


	graph_t *q = allocate_graph();
	printf("ALLOCATED\n");
	
	load_bin(bin, q);
	printf("Loaded bin.\n");

	save_txt(q, out);
	printf("Saved.\n");

	
	save_bin(q, bin2);
	printf("Saved 2nd bin.\n");

	free_graph(&q);
	free_graph(&g);
	printf("OK\n");
	return 0;
}