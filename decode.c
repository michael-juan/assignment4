# include <fcntl.h>
# include <stdio.h>
# include "huffman.h"
# include "code.h"
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>

int main(void)
{
	uint8_t magicNum[14];
	uint16_t treeSize = 0x00;
	int fd = open("secret.zzZ", O_RDONLY);
	read(fd, magicNum, 14);
	for(int8_t i = 3; i > -1; i--)
	{
		printf("%X ", magicNum[i]);
	}
	printf("\n");
	for (uint8_t i = 11; i > 3 ; i--)
	{	
		printf("%x", magicNum[i]);
	}
	printf("\n");

	treeSize |= ((magicNum[13]) << 8); 
	treeSize |= (magicNum[12]);

        printf("\n");
	printf("%d\n", treeSize);
	
	uint8_t *savedTree = malloc(sizeof(uint8_t)*treeSize);	
	read(fd, savedTree, treeSize);
	
	treeNode *tree = loadTree(savedTree, treeSize);
	printTree(tree, 1);
	free(savedTree);
	delTree(tree);
	return 0;
}
