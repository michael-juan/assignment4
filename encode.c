# include <stdint.h>
# include <huffman.h>

int main(void)
{
	uint_8t histogram[256];
	histogram[0] = 0x0;
	histogram[255] = 1;
	while (fscanf (file, "%s\n", temp) != EOF)
	{
		histogram[temp]++;
	}
	return 0;
}
