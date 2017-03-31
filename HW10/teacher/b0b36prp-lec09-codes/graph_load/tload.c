
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "graph.h"
#include "graph_utils.h"

#include "load_simple.h"

int main(int argc, char *argv[]) 
{
   int ret = 0;
   int print = 0;
   char *fname; 
   int c = 1;
   if (argc > 2 && strcmp(argv[c], "-p") == 0) {
      print = 1;
      c += 1;
   }
   fname = argc > 1 ? argv[c] : NULL;
   fprintf(stderr, "Load file '%s'\n", fname);

   graph_t *graph = allocate_graph();

   int e = load_graph_simple(fname, graph);

   fprintf(stderr, "Load %d edges\n", e);

   if (print) {
      print_graph(graph);
   }

   free_graph(&graph);
   return ret;
}
