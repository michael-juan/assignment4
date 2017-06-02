# include <stdint.h>
# include <stdio.h>

# include <unistd.h>
#include <sys/stat.h>

# include <fcntl.h>
# include <ctype.h>
# include "huffman.h"

# ifndef NIL
# define NIL ( void *) 0
# endif

treeNode * newNode( uint8_t s, bool l, uint64_t c)
{
	treeNode *node = malloc(sizeof(treeNode));
	node->symbol = s;
	node->leaf = l;
	node->count = c;
	node->left = NIL;
	node->right = NIL;
	return node;
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
void dumpTree(treeNode *t, int file)
{
	//file = open("",O_CREAT | O_TRUNC | O_WRONLY,0644);
	
	//close(file);
	struct stat fileStat;
	uint64_t sFileSize; 
	write( file,"\xde\xad\xd0\x0d",4);	// writes magic number
	
	return;
}
// writes representaition of tree to file
// postorder traversal  if called on a leaf write l write I when called on 
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes);

int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	//pass pointer points to callers local var treenode* update local variable with new treenode value either left or right child of the root you pass in
	//if code is zero go left code 1 right
	//return if could stepTree
	return -1;
}

treeNode * join (treeNode *l, treeNode *r);
static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }
void printTree(treeNode *t, int depth)
{
        if (t && t->leaf)
        {
                if (isalnum(t->symbol))
                {
                        spaces(4 * depth); printf("%c (%lu)\n", t->symbol, t->count);
                }
                else
                {
                        spaces(4 * depth); printf("%X (%lu)\n", t->symbol, t->count);
                }
        }
        else if (t)
        {
                spaces(4 * depth); printf("$ (%lu)\n", t->count);
                printTree(t->left, depth + 1);
                printTree(t->right, depth + 1);
        }
        return;
}
