# include <stdint.h>
# include <stdio.h>

# include <unistd.h>
#include <sys/stat.h>

# include <fcntl.h>
# include <ctype.h>
# include "huffman.h"
# include "code.h"
# include "stack.h"

# ifndef NIL
# define NIL ( void *) 0
# endif

treeNode *newNode(uint8_t s, bool l, uint64_t c)
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
	if (t != NIL)
	{
		delTree(t->left);
		delTree(t->right);
		delNode(t);
	}
	return NIL;
}

void dumpTree(treeNode *t, int file)
{	
	if (t -> leaf)
	{
		write(file, "L", 1);
		write(file, &t -> symbol, 1);
	}
	else
	{
		dumpTree(t -> left, file);
		dumpTree(t -> right, file);
		write(file, "I", 1);
	}
	return;
}


// writes representaition of tree to file
// postorder traversal  if called on a leaf write l write I when called on 

treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	stack *s = newStack();
	treeNode *root;
	for (uint16_t i = 0; i < treeBytes; i++)
	{
		if (savedTree[i] == 'L')
		{
			i++;
			treeNode *node = newNode(savedTree[i], true, 0);
			push(s, node);
		}
		else if(savedTree[i] == 'I')
		{	
			treeNode *a = pop(s);
			treeNode *b = pop(s);
			root = join(b, a);
			push(s, root);	
		}
	}
	delStack(s);
	return root;	
}


int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	//pass pointer points to callers local var treenode* update local variable with new treenode value either left or right child of the root you pass in
	//if code is zero go left code 1 right
	//return if could stepTreetreeNode **t
	uint8_t sym;
	if (code)
	{
		*t = (*t) -> right;
	}
	else if (code == 0)
	{
		*t = (*t) -> left;
	}
	if ((*t) -> leaf)
        {
                sym = (*t) -> symbol;
                *t = root;
                return sym;
        }
	return -1;
}

void buildCode(treeNode *t, code s, code table[256])
{
	uint32_t temp;
	if (t -> leaf)
	{
		table[t -> symbol] = s;
	}
	else
	{
		pushCode(&s, 0);
		buildCode(t -> left, s, table);
 		popCode(&s, &temp);
		pushCode(&s, 1);
		buildCode(t -> right, s, table);
		popCode(&s, &temp);
		
	}
	return;
	
}

treeNode *join(treeNode *l, treeNode *r)
{
	uint64_t newCount = (l -> count) + (r -> count);
	treeNode *node = newNode('$',0, newCount);
	node->left = l;
	node->right = r;
	return node;
}

static inline void spaces(int c) { for (int i = 0; i < c; i += 1) { putchar(' '); } return; }
/*
void printTree(treeNode *t, int depth)
{
        if (t && t->leaf)
        {
                if (isalnum(t->symbol))
                {
                        spaces(4 * depth); 
			printf("%c (%lu)\n", t->symbol, t->count);
                }
                else
                {
                        spaces(4 * depth); 
			printf("%X (%lu)\n", t->symbol, t->count);
                }
        }
        else if (t)
        {
                spaces(4 * depth); 
		printf("$ (%lu)\n", t->count);
                printTree(t->left, depth + 1);
                printTree(t->right, depth + 1);
        }
        return;
}
*/

void printTree(treeNode *t, int depth)
{
	if (t) 
	{
		printTree(t->left, depth + 1);

		if (t->leaf)
		{
			if (isalnum(t->symbol) || ispunct(t -> symbol))
			{
				spaces(4 * depth); printf("'%c' (%lu)\n", t->symbol, t->count);
			}
			else
			{
				spaces(4 * depth); printf("0x%X (%lu)\n", t->symbol, t->count);
			}
		}
		else
		{
			spaces(4 * depth); printf("$ (%lu)\n", t->count);
		}

		printTree(t->right, depth + 1); 
	}

	return;
}

/*
int main(void)
{
	//int fd = open("sample.txt", O_WRONLY);

	treeNode *a = newNode('A', 1, 2);
	treeNode *b = newNode('V', 1, 9);
	treeNode *rootA = join(a, b);
	treeNode *c = newNode('h', 1, 14);
	treeNode *d = newNode('f', 1, 12);
	treeNode *rootB = join(c, d);
	treeNode *root = join(rootA, rootB);
	dumpTree(root, 1);
	
	uint8_t savedTree[8] = {"LALBLCII"};
	static code s, array[256];
	buildCode(root, s, array); 
	treeNode *FATHER = loadTree(savedTree, 8);
	printTree(FATHER, 5);
	printTree(root, 1);
	delTree(FATHER);
	delTree(root);	
}
*/

// int main(void)
// {
// 	//int fd = open("sample.txt", O_WRONLY);
// 
// 	treeNode *a = newNode('A', 1, 2);
// 	treeNode *b = newNode('V', 1, 9);
// 	treeNode *rootA = join(a, b);
// 	treeNode *c = newNode('h', 1, 14);
// 	treeNode *d = newNode('f', 1, 12);
// 	treeNode *rootB = join(c, d);
// 	treeNode *root = join(rootA, rootB);
// 	dumpTree(root, 1);
// 	
// 	uint8_t savedTree[8] = {"LALBLCII"};
// 	static code s, array[256];
// 	buildCode(root, s, array); 
// 	treeNode *FATHER = loadTree(savedTree, 8);
// 	printTree(FATHER, 5);
// 	printTree(root, 1);
// 	delTree(FATHER);
// 	delTree(root);	
// }

