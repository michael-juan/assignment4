# include <stdint.h>
# include <stdio.h>
//# include <huffman.h>

int main(void)
{
	FILE *fp = fopen("/home/michael/Documents/assignment4/file", "r");
	static uint32_t histogram[256];
	histogram[0] = 0x01;
	histogram[255] = 0x01;
	uint8_t temp;
	while (fscanf(fp, "%c", &temp) == 1)
	{
		histogram[temp]++;
	}
	fclose(fp);
	for(int i = 0; i < 256; i++)
	{
		printf("%x %u \n",i,histogram[i]);
	}
	return 0;
}
