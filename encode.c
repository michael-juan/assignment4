# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
# include "huffman.h"
# include "queue.h"
# include "bv.h"
# include "code.h"

int main(int argc, char **argv)
{

	int inputFile = 0;
	int outputFile = 1;
	int c = 0;
	while ((c = getopt(argc, argv, "i:o:vp")) != -1)	//reused structure from assignment3
	{
		switch (c)
		{
			case 'i':
			{
				inputFile = open(optarg, O_RDONLY);
				break;
			}
			case 'o':
			{
				outputFile = open(optarg,O_CREAT | O_TRUNC | O_WRONLY,0644);
				break;
			}
			case 'v':
			{
				break;
			}
			case 'p':
			{
				break;
			}
			default:
			{
				inputFile = 0;
				outputFile = 1;
				break;
			}
		}
	}
	
	struct stat fileStat;	//http://codewiki.wikidot.com/c:system-calls:fstat

	if(fstat(inputFile,&fileStat) < 0)  
	{
		return 1;
	}
	
	static uint32_t histogram[256];	//change to memset
	histogram[0] = 0x01;
	histogram[255] = 0x01;
	uint64_t numBytes = 0;
	uint8_t *inputBuffer = calloc(fileStat.st_size, sizeof(uint8_t));
	read(inputFile,inputBuffer, fileStat.st_size);
	for (int i = 0; i<fileStat.st_size; i++)
	{
		histogram[inputBuffer[i]]++;
		numBytes++;
		
	}
	
	queue *histogramQueue = newQueue(768);
	
	for (uint16_t i = 0; i < 256; i++)
	{
		if (histogram[i])
		{
			enqueue(histogramQueue, newNode(i, 1, histogram[i]));
		}
	}
	treeNode *itemA = newNode('$', 0, 0);
	treeNode *itemB = newNode('$', 0, 0);
	
	while(empty(histogramQueue) == 0 )
	{
		dequeue(histogramQueue, &itemA);
		if(empty(histogramQueue))
		{
			break;
		}
		dequeue(histogramQueue, &itemB);
		enqueue(histogramQueue,join(itemA, itemB));
	
	}

	code s = newCode();
	code codeTable[256];
	buildCode(itemA, s, codeTable);
	
	bitV *outputBuffer = newVec(fileStat.st_size*8);
	uint32_t index = 0;

	for(int i = 0; i < fileStat.st_size; i++)
	{
		for(uint32_t j = 0; j < codeTable[inputBuffer[i]].l;j++)
		{
			if((codeTable[inputBuffer[i]].bits[j>>3] >> (j%8)) & (0x1))
			{
				setBit(outputBuffer, index + j);
			}
		}
		index += codeTable[inputBuffer[i]].l;
	}
	
	
//	int file = open("testoutput",O_CREAT | O_TRUNC | O_WRONLY,0644);
	write(outputFile, "\x0D\xD0\xAD\xDE", 4);	//magic number
	write(outputFile, &numBytes, sizeof(uint64_t));	//file size
	uint16_t huffmanTreeSize = 0;
	for (int i = 0; i < 256;i++)
	{
		if (histogram[i])
		{
			 huffmanTreeSize++;
		}
	}

	huffmanTreeSize = (huffmanTreeSize*3) - 1;
	write(outputFile, &huffmanTreeSize, sizeof(uint16_t));
	dumpTree(itemA, outputFile);
	write(outputFile, outputBuffer->v, (index+7)/8);
	
	delQueue(histogramQueue);
	delTree(itemA);
	
	delVec(outputBuffer);
	free(inputBuffer);
	close(inputFile);
	close(outputFile);

	return 0;
}
