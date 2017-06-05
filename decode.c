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

	printf("Magic No: %X\n", magicNum);
	
	if (magicNum != 0xdeadd00d)
	{
		printf("Invalid File: Magic Number does not match.\n");
		return 0;
	}	
	printf("File Size: %lu\n", fileSize);
	
	printf("Tree Size: %d\n", treeSize);
	
	uint8_t *savedTree = malloc(sizeof(uint8_t)*treeSize);	
	read(fd, savedTree, treeSize);
	
	treeNode *tree = loadTree(savedTree, treeSize);
	printTree(tree, 1);
	
//	treeNode **t = &(tree);
		
	uint64_t bytesDecoded = 0;
	uint8_t *buf = malloc(sizeof(uint8_t)*fileSize);
	read(fd, buf, fileSize);
	bitV *bits = newVec(fileSize*8);
        bits -> v = buf;
/*
	for (uint32_t i = 0; i < bits -> l; i++)
        {
     		printf("%d", valBit(bits, i));
        }
	printf("\n");
*/	
	treeNode *t = tree;
	while (bytesDecoded <= fileSize)
	{
		for (uint32_t i = 0; i < bits -> l; i++)
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
                }
	}

/*		
	do
	{
		n = read(fd, buf, 4096);	
		bitV *bits = newVec(n*8);
		bits -> v = buf;
		
		for (uint32_t i = 0; i < bits -> l; i++)
		{
			int32_t symbol = stepTree(tree, t, bits -> v[i]);
			if (symbol != -1)
			{
				write(1, &symbol, 1);
			}
			if(++bytesDecoded >= fileSize)
			{
				return 0;
			}
		}
	}
	while (n != 4096);
*/
	delVec(bits);
	//free(buf);
	free(savedTree);
	delTree(tree);















	return 0;
}
