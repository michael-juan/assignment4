# include <stdint.h>
# include <stdio.h>
# include <ctype.h>
# include "huffman.h"

# ifndef NIL
# define NIL ( void *) 0
# endif

treeNode * newNode( uint8_t s, bool l, uint64_t c)
{
	treeNode *newNode = malloc(sizeof(treeNode));
	newNode->symbol = s;
	newNode->leaf = l;
	newNode->count = c;
	newNode->left = NIL;
	newNode->right = NIL;
	return newNode;
}	
void *delTree(treeNode *t)
{
	if(t != NIL)
	{
		delTree(t->left);
		delTree(t->right);
		delNode(t);
	}
	return NIL;
}
void dumpTree(treeNode *t, int file);
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);
treeNode * newNode( uint8_t s, bool l, uint64_t c)
{
	treeNode *newNode = malloc(sizeof(treeNode));
	newNode->symbol = s;
	newNode->leaf = l;
	newNode->count = c;
	newNode->left = NIL;
	newNode->right = NIL;
	return newNode;
}	delTree(t->right);
		delNode(t);
	}
	return NIL;
}
treeNode * join (treeNode *l, treeNode *r);

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
