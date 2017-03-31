#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "graph.h"

#ifndef INIT_SIZE 
#define INIT_SIZE 10
#endif

graph_t* allocate_graph(void) 
{
   graph_t *g = (graph_t*) malloc(sizeof(graph_t));
   assert(g != NULL);
   g->edges = NULL;
   g->num_edges = 0;
   g->capacity = 0;
   /* or we can call calloc */
   return g;
}

void free_graph(graph_t **g) 
{
   assert(g != NULL && *g != NULL);
   if ((*g)->capacity > 0) {
      free((*g)->edges);
   }
   free(*g);
   *g = NULL;
}

graph_t* enlarge_graph(graph_t *g) 
{
   assert(g != NULL);
   int n = g->capacity == 0 ? INIT_SIZE : g->capacity * 2; /* double the memory */

   edge_t *e = (edge_t*)malloc(n * sizeof(edge_t));
   assert(e != NULL);
   memcpy(e, g->edges, g->num_edges * sizeof(edge_t));
   free(g->edges);
   g->edges = e;
   g->capacity = n;
   return g;
}

void print_graph(graph_t *g) 
{
   assert(g != NULL);
   fprintf(stderr, "Graph has %d edges and %d edges are allocated\n", g->num_edges, g->capacity);
   edge_t *e = g->edges;
   for (int i = 0; i < g->num_edges; ++i, ++e) {
      printf("%d %d %d\n", e->from, e->to, e->cost);
   }
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

//NETWORK ORDER IS BIG ENDIAN
static int load_big_endian(FILE *f) {
   uint32_t a;

   if( fread(&a, sizeof(uint32_t), 1, f) != 1 ) return -1;

   return ntohl(a);

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
         int from = load_big_endian(f);
         int to = load_big_endian(f);
         int cost = load_big_endian(f);

         if(from < 0 || to < 0 || cost < 0) break;

         e->from = from;
         e->to = to;
         e->cost = cost;

         graph->num_edges += 1;
         e++;

      } else {
         enlarge_graph(graph);
      }
   }

      fclose(f);
}

static void save_big_endian(int a, FILE *f)
{

   int *p1 = &a;
   char *p2 = (char *)p1; 
   char byte1 = *(p2); 
   char byte2 = *(p2+1);
   char byte3 = *(p2+2);
   char byte4 = *(p2+3);

   fputc(byte4,f);
   fputc(byte3,f);
   fputc(byte2,f);
   fputc(byte1,f);
}
// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
   FILE *f = fopen(fname, "wb");
   edge_t *e = graph->edges;

      for (int i = 0; i < graph->num_edges; ++i, ++e) {
         
      
         save_big_endian(e->from ,f);
         save_big_endian(e->to ,f);
         save_big_endian(e->cost ,f);
      

         /*
         save_little_endian(e->from, f);
         save_little_endian(e->to, f);
         save_little_endian(e->cost, f);
      */

      /*
      uint32_t from = htonl(e->from);
      uint32_t to = htonl(e->to);
      uint32_t cost = htonl(e->cost);
      
      fwrite(&from, sizeof(from), 1, f);
      fwrite(&to, sizeof(to), 1, f);
      fwrite(&cost, sizeof(cost), 1, f);

      */
         /*
      fwrite(&e->from , sizeof(e->from), 1, f);
      fwrite(&e->to, sizeof(e->to), 1, f);
      fwrite(&e->cost, sizeof(e->cost), 1, f);
      */
   }

      fclose(f);
}

