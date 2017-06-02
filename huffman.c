# include <stdint.h>
# include <stdio.h>
# include <ctype.h>
# include "huffman.h"

# ifndef NIL
# define NIL ( void *) 0
# endif

void *delTree(treeNode *t)
{
	if (t != NIL)
	{
		delTree(t->left);
		delTree(t->right);
		delNode(t);
	}
	return NIL;
}


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
