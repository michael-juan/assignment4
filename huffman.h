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
	treeNode -> symbol = s;
	treeNode -> leaf = l;
	treeNode -> count = c;
	treeNode -> left = NIL;
	treeNode -> right = NIL;
	return newNode;
}


// Dump a Huffman tree onto a file
void dumpTree(treeNode *t, int file);

// Build a tree from the saved tree
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

// Step through a tree following the code
static inline int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	if()
	{
	
	}
	return -1;	// when its an interior node;
}

// Parse a Huffman tree to build codes
void buildCode(treeNode *t, code s, code table[256])
{
	table[0] = 1;
	table[255] = 1;
	return
}

// Delete a tree
static inline void * delTree (treeNode *t)
{
	if (t != NIL)
	{
		delTree(t -> left);
		delTree(t -> right);
		delNode(t);
	}
	return;
}

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

// if code is 1 or 0 1 is left 0 is right other is the thingy
// test code from piazza professor

static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }

void printTree(treeNode *t, int depth)
{
        if (t && t->leaf)
        {
                if (isalnum(t->symbol))
                {
                        spaces(4 * depth); printf("%c (%llu)\n", t->symbol, t->count);
                }
                else
                {
                        spaces(4 * depth); printf("%X (%llu)\n", t->symbol, t->count);
                }
        }
        else if (t)
        {
                spaces(4 * depth); printf("$ (%llu)\n", t->count);
                printTree(t->left, depth + 1);
                printTree(t->right, depth + 1);
        }
        return;
}

# endif
