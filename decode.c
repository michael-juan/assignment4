# include <fcntl.h>
# include <stdio.h>
# include "huffman.h"
# include "code.h"
# include <stdint.h>
# include <unistd.h>

int main(void)
{
	uint8_t magicNum[14];
	uint16_t treeSize = 0;
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

	for (int8_t i = 13; i > 11; i--)
        {
		treeSize = 10 * treeSize + magicNum[i];
                printf("%d", magicNum[i]);
        }

        printf("\n");
	printf("%X\n", treeSize);
	return 0;
}
