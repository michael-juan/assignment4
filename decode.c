# include <fcntl.h>
# include <stdio.h>
# include "huffman.h"
# include "code.h"
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <ctype.h>
# include "bv.h"


int main(int argc, char **argv)
{
	int c, fd = 0;
	bool verbose = false, showTree = false;

	while ((c = getopt(argc, argv, "i:o:vp")) != -1)
	{
		switch (c)
		{
			case 'i':
			{
				fd = open(optarg, O_RDONLY);
				if (fd == 0)
				{
					printf("Please specify an input file");
					return 0;
				}
				break;
			}
			case 'v':
			{
				verbose = true;
				break;
			}
			case 'p':
			{
				showTree = true;
				break;
			}
			default:
			{
				break;
			}
			
		}
	} 

	
	uint32_t magicNum = 0;

	read(fd, &magicNum, 4);
	
	if (magicNum != 0xdeadd00d)
	{
		printf("Not a compressed file\n");
		return 0;
	}	
	
	uint16_t treeSize = 0;
        uint64_t fileSize = 0;

	read(fd, &fileSize, 8);
        read(fd, &treeSize, 2);
	
	uint8_t *savedTree = malloc(sizeof(uint8_t)*treeSize);	
	read(fd, savedTree, treeSize);
	
	treeNode *tree = loadTree(savedTree, treeSize);
			
	treeNode *t = tree;
	
	uint8_t *buf = malloc(sizeof(uint8_t)*fileSize);
	uint64_t bytesDecoded = 0;
	
	while (bytesDecoded < fileSize)
	{
		bitV *bits = newVec(4096);
		read(fd, bits->v, 512);
		
		for (uint32_t i = 0; i < bits->l; i++)
                {
                        if (valBit(bits, i) == 0)
			{
				t = t -> left;
			}
			else
			{
				t = t -> right;
			}
			if (t -> leaf)
			{
				buf[bytesDecoded] = t -> symbol;
				t = tree;
				bytesDecoded++;
			}
			if (bytesDecoded == fileSize)
			{
				break;
			}
                }
		delVec(bits);
	}
	
	if (verbose)
	{
		printf("Original %lu bits: tree (%u)\n", fileSize*8, treeSize);
	}
	
	write(1, buf, bytesDecoded);
	
	if (showTree)
	{
		printTree(tree, 1);
	} 

	free(buf);
	close(fd);
	free(savedTree);
	delTree(tree);


	return 0;
}
