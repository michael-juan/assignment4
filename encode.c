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

// void append(bitV *vecOne, bitV *vecTwo)
// {
// 	uint32_t originalLength = vecOne -> l;
// 	vecOne -> l = vecOne -> l + vecTwo -> l;
// 	vecOne ->v = realloc(vecOne ->v, sizeof(uint8_t)*((vecOne->l/4)+1));
// 	uint32_t counter = 0;
// 
// 	for (uint32_t i = originalLength; i < vecOne -> l; i++) 
// 	{
// 		vecOne -> v[i] = vecTwo -> v[counter];
// 		counter++;
// 	}
// 	
// 	delVec(vecTwo);
// }

int main(void)
{
	int inputFile = open("badspeak.txt",O_RDONLY);
	
	struct stat fileStat;	//http://codewiki.wikidot.com/c:system-calls:fstat
	if(fstat(inputFile,&fileStat) < 0)  
	{
		return 1;
	}
	
	static uint32_t histogram[256];
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
//	uint8_t *outputBuffer = calloc(fileStat.st_size,sizeof(uint8_t));
	bitV *outputBuffer = newVec(fileStat.st_size*8);
	uint32_t index = 0;
	//memcpy(outputBuffer,codeTable[inputBuffer[0]].bits,(codeTable[inputBuffer[0]].l+7)>>3);
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
	
//	printf("%ld",  index);
//	printf("\t%ld",  (index+7)>>3);

	//printTree(itemA,1);
	//uint8_t inputFile
	//uint8_t buffer[8192];
/*
	bitV *vec = newVec(codeTable[112].l);
	vec -> v = codeTable[112].bits;	
	bitV *testVec = newVec(codeTable[102].l);
	testVec -> v = codeTable[102].bits;
	
	for (uint32_t i = 0; i < vec -> l; i++)
        {
                printf("%u", valBit(vec,i));
        }
	printf("\n");
	for (uint32_t i = 0; i < testVec -> l; i++)
        {
                printf("%u", valBit(testVec,i));
        }
        printf("\n");	
//	append(vec, testVec);
	for (uint32_t i = 0; i < vec -> l; i++)
        {
                printf("%u", valBit(vec,i));
        }	
	*/

	
	int file = open("testoutput",O_CREAT | O_TRUNC | O_WRONLY,0644);
	write(file, "\x0D\xD0\xAD\xDE", 4);	//magic number
	write(file, &numBytes, sizeof(uint64_t));	//file size
	uint16_t huffmanTreeSize =0;
	for (int i = 0; i < 256;i++)
	{
		if(histogram[i])
		{
			 huffmanTreeSize++;
		}
	}
	write(file, &huffmanTreeSize, sizeof(uint16_t));
	dumpTree(itemA, file);
	write(file, outputBuffer->v, (index+7)/8);
	free(inputBuffer);
	close(inputFile);
	close(file);
	return 0;
}
// void shiftl(void *object, size_t size)
// {
//    unsigned char *byte;
//    for ( byte = object; size--; ++byte )
//    {
//       unsigned char bit = 0;
//       if ( size )
//       {
//          bit = byte[1] & (1 << (CHAR_BIT - 1)) ? 1 : 0;
//       }
//       *byte <<= 1;
//       *byte  |= bit;
//    }
// }
//magic number number of bytes size of tree
//while bytes written < total bytes continue looping
//deadD00d total bytes size of tree tree encoded file trailing zeros

//step 1 histogram thing you see most
//priority queue make nodes

//histogram pop pop join push pop pop join push
//priority queue based on count
//professor did preorder traversal
//postorder left right nodes

//do full postorder traversal
// put into stack
// push push push unti its leaf nodes
// set the table to c0de
// move through huffman tree post order using stack and then 
// code table ['s'] = stack;
