# include <fcntl.h>
# include <stdio.h>
# include "huffman.h"
# include "code.h"
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include "bv.h"

/* DONT FORGET TO CHECK THE MAGIC NUMBER!!!!*/

int main(void)
{
	uint32_t magicNum = 0;
	uint16_t treeSize = 0;
	uint64_t fileSize = 0;
	int fd = open("secret.zzZ", O_RDONLY);
	read(fd, &magicNum, 4);
	read(fd, &fileSize, 8);
	read(fd, &treeSize, 2);

//	printf("Magic No: %X\n", magicNum);
	
	if (magicNum != 0xdeadd00d)
	{
		printf("Invalid File: Magic Number does not match.\n");
		return 0;
	}	
//	printf("File Size: %lu\n", fileSize);
	
//	printf("Tree Size: %d\n", treeSize);
	
	uint8_t *savedTree = malloc(sizeof(uint8_t)*treeSize);	
	read(fd, savedTree, treeSize);
	
	treeNode *tree = loadTree(savedTree, treeSize);
//	printTree(tree, 1);
			
	uint64_t bytesDecoded = 0;
	
	treeNode *t = tree;
	while (bytesDecoded < fileSize)
	{
		bitV *bits = newVec(8);
		read(fd, bits->v, 1);
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
				write(1, &t -> symbol, 1);
				t = tree;
				bytesDecoded++;
			}
			if(bytesDecoded == fileSize)
			{
				break;
			}
                }
		delVec(bits);
	}


	close(fd);
	free(savedTree);
	delTree(tree);


	return 0;
}
