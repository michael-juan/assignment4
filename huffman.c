# include <stdint.h>
# include <stdio.h>

# include <unistd.h>

# include <fcntl.h>
# include <ctype.h>
# include "huffman.h"
# include "code.h"
# include "stack.h"

# ifndef NIL
# define NIL ( void *) 0
# endif

/* For this Huffman Tree implementation, many of the functions were influence by Arjun Govindjee at his office hours on Friday June 2nd. */
/* He discussed various functions and I asked him for help on dumpTree and buildCode, since I was having trouble with these functions. */
/* Arjun discussed and went over pseudocode for these functions, and I implemented them according to what he explained */

treeNode *newNode(uint8_t s, bool l, uint64_t c)  /* creates a new tree node */
{
	treeNode *node = malloc(sizeof(treeNode));  /* first I allocate memory for the struct itself */
	node->symbol = s;	/* symbol is set according to the parameter which is passed in */
	node->leaf = l;		/* boolean variable for determining whether or not it is a leaf */
	node->count = c;	/* frequency of the symbol according to the histogram */
	node->left = NIL;	/* left and right pointers are initially set to NIL */
	node->right = NIL;	
	return node;
}
	
void *delTree(treeNode *t) /* delTree function to delete an entire tree */
{
/* We saw this function on Piazza Post @1092, where Professor Long showed his implementation of the delTree function */
	if (t != NIL)
	{
		delTree(t->left); 	/* recursive calls on the left and right children */
		delTree(t->right);
		delNode(t);
	}
	return NIL;
}

/* For the following function, I received help from Arjun, as I stated above. I implemented this function according to the pseudo code which he went over on Friday June 2nd */
void dumpTree(treeNode *t, int file)
{	
	if (t -> leaf)	/* if we are at a leaf, the 'L' character is written followed by the symbol itself */
	{
		write(file, "L", 1);
		write(file, &t -> symbol, 1); 
	}
	else	/* if we are not at a leaf, the following happens */
	{
		dumpTree(t -> left, file);  /* recursive call on the left child */
		dumpTree(t -> right, file);	/* recursive call on the right child */
		write(file, "I", 1); 	/* 'I' is printed, to denote that we are at an interior node */
	}
	return;
}

treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)  /* This function loads a new tree based upon the output of dump tree */
{
	stack *s = newStack();	/* a new stack is created */
	treeNode *root;		/* root of the tree */
	for (uint16_t i = 0; i < treeBytes; i++)	/* for loop to traverse through the tree using the treeBytes variable */
	{
		if (savedTree[i] == 'L')	/* if we encounter an L */
		{
			i++;		/* add to the index variable so that we can record the symbol within the tree */
			treeNode *node = newNode(savedTree[i], true, 0);	/* new leaf node is created with this symbol */
			push(s, node);	/* this node is then pushed onto the stack */
		}
		else if (savedTree[i] == 'I')	/* if we encounter an Interior Node (I) */
		{	
			treeNode *a = pop(s);	/* pop one node from the stack */
			treeNode *b = pop(s);	/* pop another node from the stack */
			root = join(b, a);	/* join these two nodes */
			push(s, root);		/* push this node back onto the stack */
		}
	}
	delStack(s);	/* free the stack */
	return root;	/* return the root of the tree */
}

/* For the following function, I received help from Arjun, as I stated above. I implemented this function according to the pseudo code which he went over on Friday June 2nd */
void buildCode(treeNode *t, code s, code table[256])
{
/* this function creates and records the code for each symbol in the Huffman tree, and I got help from Arjun */
	uint32_t temp; 	/* temporary uint32_t holder */
	if (t -> leaf)	/* if we encounter a leaf */
	{	
		table[t -> symbol] = s;   /* the symbol's code is recorded into the array */
	}
	else	/* if we are not at a leaf */
	{
		pushCode(&s, 0);	/* a zero is pushed, since we are going left */
		buildCode(t -> left, s, table);	/* recursive call on the left child */
 		popCode(&s, &temp);	/* the 0 is popped, since we now we want to go to the right of the node */
		pushCode(&s, 1);	/* a one is pushed, since we are now going to the left of the original node */
		buildCode(t -> right, s, table);	/* recursive call on the right child */
		popCode(&s, &temp);	/*  the one is popped, and we are back at the original node */
		
	}
	return;
	
}

treeNode *join(treeNode *l, treeNode *r)
{
/* this function joins to nodes */
	uint64_t newCount = (l -> count) + (r -> count); /* the new parent node must have a count equal to the sum of the two children nodes */
	treeNode *node = newNode('$',0, newCount);	/* new interior node with a dollar sign as a symbol */
	node->left = l;	/* left and right addreses are set */
	node->right = r;
	return node;	/* new interior node is returned */
}

/* Theses final two functions were given by Professor Long on Piazza Post @1063. These are used to print the tree for debugging purposes, as well as if the -p flag has been turned on */
static inline void spaces(int c) 
{ 
	for (int i = 0; i < c; i += 1) 
	{ 
		putchar(' '); 
	} 
	return; 
}

void printTree(treeNode *t, int depth)
{
	if (t) 
	{
		printTree(t->left, depth + 1);

		if (t->leaf)
		{
			if (isalnum(t->symbol) || ispunct(t -> symbol))
			{
				spaces(4 * depth); 
				printf("'%c' (%lu)\n", t->symbol, t->count);
			}
			else
			{
				spaces(4 * depth); 
				printf("0x%X (%lu)\n", t->symbol, t->count);
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
