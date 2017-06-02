# ifndef _HUFFMAN_H
# define _HUFFMAN_H
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include "code.h"

# ifndef NIL
# define NIL ( void *) 0
# endif

typedef struct DAH treeNode;

struct DAH
{
	uint8_t symbol;
	uint64_t count;
	bool leaf;
	treeNode *left, *right;
};

// New node , with symbols , leaf or not , a count associated with it
static inline treeNode * newNode( uint8_t s, bool l, uint64_t c)
{
	treeNode *newNode = malloc(sizeof(treeNode));
	newNode->symbol = s;
	newNode->leaf = l;
	newNode->count = c;
	newNode->left = NIL;
	newNode->right = NIL;
	return newNode;
}


// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file);

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

// Step through a tree following the code
static inline int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	return -1;	// when its an interior node;
}

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, code s, code table[256]);
// Delete a tree
void *delTree(treeNode *t);

static inline void delNode(treeNode *h) 
{
	if (h != NIL)
	{
		free (h);
		h = NIL;
	}
	return;
}

static inline int8_t compare (treeNode *l, treeNode *r)
{
	return l -> count - r -> count; // l < r if negative , l = r if 0 , ...
}

treeNode * join (treeNode *l, treeNode *r); // Join two subtrees



void printTree(treeNode *t, int depth);

# endif

//notes 
// if code is 1 or 0 1 is left 0 is right other is the thingy
// test code from piazza professor
