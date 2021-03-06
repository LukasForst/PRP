#include <stdio.h>

#include "graph_utils.h"


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
int load_graph_simple(const char *fname, graph_t *graph)
{
   FILE *f = fopen(fname, "r");

   if(!f){
      fprintf(stderr, "WRONG FILE\n");
      free_graph(&graph);
   }

   int c = 0;
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
         c += 1;
         graph->num_edges += 1;
         e += 1;
      }
   }
   fclose(f);
   return c;
}
