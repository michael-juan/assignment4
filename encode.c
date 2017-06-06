# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "huffman.h"
# include "queue.h"
# include "bv.h"
# include "code.h"

void append(bitV *vec, code s)
{
	uint32_t originalLength = vec -> l;
	vec -> l = s.l + vec->l;
        vec ->v = realloc(vec ->v, sizeof(uint8_t)*((vec->l/8)+1));
	uint32_t counter = 32;

	for (uint32_t i = originalLength; i < vec -> l; i++) 
	{
		setBit(vec, i)s.bits[counter];
		counter--; 
	}

//	(vec -> v) |= (0x0 | s.bits);
}

int main(void)
{
	int inputFile = open("badspeak.txt",O_RDONLY);
	static uint32_t histogram[256];
	histogram[0] = 0x01;
	histogram[255] = 0x01;
	uint64_t numBytes = 0;
	uint8_t temp;
	
	while (read(inputFile, &temp, 1))
	{
		histogram[temp]++;
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
//	printTree(itemA,10);
	code s = newCode();
	code codeTable[256];
	buildCode(itemA, s, codeTable);
	printCode(&codeTable[122]);
	printTree(itemA,1);
	//uint8_t inputFile
	//uint8_t buffer[8192];
	bitV *test = newVec(5);
	for (uint32_t i = 0; i < test -> l; i++)
	{
		printf("%u", valBit(test,i));
	}
	printf("\n");
	printCode(&codeTable[122]);
	append(test, codeTable[122]);
	
	for (uint32_t i = 0; i < test -> l; i++)
        {
                printf("%u", valBit(test,i));
        }
        printf("\n");
	//code t = newCode();
	//t -> bits = {0,0,1};
	//t.l = 3;
	//test->l = t.l+test->l;
	//test ->v =realloc(test ->v, sizeof(uint8_t)*((test->l/8)+1));
	for(uint32_t i = 0; i < numBytes; i++ )
	{
		
	}
	
	
	
	int file = open("testoutput",O_CREAT | O_TRUNC | O_WRONLY,0644);
	write(file, "\xAD\xDE\x0D\xD0", 4);
	write(file, &numBytes, sizeof(uint64_t));
	
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
