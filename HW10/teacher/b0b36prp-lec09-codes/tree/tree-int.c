#include "tree-int.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// - local helper function ---------------------------------------------------
static node_t* newNode(int value)
{
   node_t *node= (node_t*)malloc(sizeof(node_t));
   node->value = value;
   node->left = node->right = NULL;
   return node;
}

// - function ----------------------------------------------------------------
node_t* tree_insert(int value, node_t *node) 
{
   if (node == NULL) {
      return newNode(value); 
   } else {
      if (value <= node->value) {
         //insert into left subtree
         node->left = tree_insert(value, node->left);
      } else {
         //insert into right subtree
         node->right = tree_insert(value, node->right);
      }
      return node; // return the given node
   }
}

// - function ----------------------------------------------------------------
void tree_free(node_t **tree)
{
   if (tree && *tree) {
      node_t * node = *tree;
      if ( node->left ) {
         tree_free(&(node->left));
      }
      if ( node->right ) {
         tree_free(&(node->right));
      }
      free(*tree);
      *tree = NULL; // fill the tree variable of tha calling function to NULL
   }
}

// - function ----------------------------------------------------------------
int tree_size(const node_t *const node) 
{
   return node == NULL ? 0 : tree_size(node->left) + 1 + tree_size(node->right);
}

// - function ----------------------------------------------------------------
int tree_max_depth(const node_t *const node) 
{
   if (node) {
      const int left_depth = tree_max_depth(node->left);
      const int right_depth = tree_max_depth(node->right);
      return left_depth > right_depth ? left_depth + 1 : right_depth + 1;
   } else { 
      return 0;
   }
}

// - function ----------------------------------------------------------------
void tree_print(const node_t *const node) 
{
   if (node) {
      tree_print(node->left);
      printf("%d ", node->value); 
      tree_print(node->right);
   }
}

// - local helper function ---------------------------------------------------
static int getMaxValue(const node_t *const node)
{
   const node_t *cur = node;
   while (cur->right) {
      cur = cur->right;
   } 
   return cur->value;
}

// - local helper function ---------------------------------------------------
static int getMinValue(const node_t *const node)
{

   const node_t *cur = node;
   while (cur->left) {
      cur = cur->left;
   } 
   return cur->value;
}

// - function ----------------------------------------------------------------
_Bool tree_is_bst(const node_t *const node) 
{
   _Bool ret = true;
   if (node != NULL) {
      if (node->left && getMaxValue(node->left) > node->value) {
         ret = false;
      }
      if (ret && node->right && getMinValue(node->right) <= node->value) {
         ret = false;
      }
      if (ret 
            && (
               !tree_is_bst(node->left) 
               || !tree_is_bst(node->right)
               )
         ) {
         ret = false;
      }
   } 
   return ret;
}

// - local helper function ---------------------------------------------------
static void printDepth(int depth, int cur_depth, const node_t *const node)
{
   if (depth == cur_depth) {
      if (node) {
         printf("%2d ", node->value);
      } else {
         printf(" - ");
      }
   } else if (node) {
      printDepth(depth, cur_depth + 1, node->left);
      printDepth(depth, cur_depth + 1, node->right);
   }
}

// - local helper function ---------------------------------------------------
void tree_print_layers(const node_t *const node)
{
   const int depth = tree_max_depth(node);
   for (int i = 0; i <= depth; ++i) {
      printDepth(i, 0, node);
      printf("\n");
   }
}
