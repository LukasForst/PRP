#ifndef __TREE_H__
#define __TREE_H__

typedef struct node {
   int value;
   struct node *left;
   struct node *right;
} node_t;

node_t* tree_insert(int value, node_t *tree);

void tree_free(node_t **tree);

/*
 * count number of tree nodes
 */
int tree_size(const node_t *const tree);

void tree_print(const node_t *const node);

/*
 * Check if the tree is the binary search tree (bst)
 */ 
_Bool tree_is_bst(const node_t *const node);

int tree_max_depth(const node_t *const node);
void tree_print_layers(const node_t *const node);

#endif 
