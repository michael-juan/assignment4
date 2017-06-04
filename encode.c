# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "huffman.h"
# include "queue.h"

int main(void)
{
	FILE *fp = fopen("sample.txt", "r");
	static uint32_t histogram[256];
	histogram[0] = 0x01;
	histogram[255] = 0x01;
	uint64_t numBytes = 0;
	uint8_t temp;
	
	while (fscanf(fp, "%c", &temp) == 1)
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
	printQueue(histogramQueue);
// 	treeNode *tempItemLeft *tempItemRight;
// 	while( empty(histogramQueue) != 0 )
// 	{
// 		dequeue(histogramQueue, tempItemLeft);
// 		dequeue(histogramQueue, tempItemLeft);
// // 		enqueue(histogramQueue, );
// 	}
// 	
	
	
	int file = open("fuckingfuck",O_CREAT | O_TRUNC | O_WRONLY,0644);
	write(file, "\xAD\xDE\x0D\xD0", 4);
	write(file, &numBytes, sizeof(uint64_t));
	
	close(file);
	fclose(fp);
// 	for(int i = 0; i < 256; i++)
// 	{
// 		printf("%x %u \n",i,histogram[i]);
// 	}
	return 0;
}
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
