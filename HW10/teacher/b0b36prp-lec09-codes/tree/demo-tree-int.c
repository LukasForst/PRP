#include "tree-int.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

   node_t *root = NULL;

   int values1[] = { 5, 3, 7, 2, 4, 6, 8 };
   int values2[] = { 5, 4, 6, 3, 7, 2, 8 };
   const int n = sizeof(values1) / sizeof(int);
   int *values;

   if (argc > 1 && strcmp(argv[1], "values1") == 0) {
      printf("Insert values1 to make balanced tree\n");
      values = values1;
   } else {
      printf("Insert values2 that will result in none balanced tree\n");
      values = values2;
   }
   for (int i = 0; i < n; ++i) {
      printf("Insert value %i\n", values[i]);
      if (root == NULL) {
         root = tree_insert(values[i], NULL);
      } else {
         tree_insert(values[i], root);
      }
   }
   printf("No. of tree nodes is %i\n", tree_size(root));

   printf("Print tree: ");
   tree_print(root);
   printf("\n");

   printf("Max tree depth: %i\n", tree_max_depth(root));

   printf("Tree is binary seach tree (BST): %s\n", tree_is_bst(root) ? "yes" : "no");

   printf("Print tree by depth row\n");
   tree_print_layers(root);

   tree_free(&root);
   printf("After tree_free() root is %p\n", root);
   return 0;
}
