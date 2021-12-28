#include<stdio.h>
#include<stdlib.h>
#include<string.h>   
#define TEXT_LENGTH  100000

void make_ShiftTable(int shift[256], char* shablon, int shablon_length)
{
	for (int i = 0; i < 256; i++) // filling array with l_shablon 
	{
		shift[i] = shablon_length;
	}

	for (int i = 0; i < shablon_length - 1; i++)
	{
		int kod = (unsigned char)shablon[i]; // finding symbol's code
		shift[kod] = shablon_length - 1 - i;
	}
}

int Boyer_Moor(char* text, char* shablon, int text_length, int shablon_length, int* shift, int start_pos)
{
	//text_length -= 1;
	int pos = shablon_length - 1;
	while (pos < text_length)
	{
		int i = 0;
		while (i < shablon_length)
		{
			printf("%d ", start_pos + pos - i);
			if (text[pos - i] == shablon[shablon_length - 1 - i])
				i++;
			else
			{
				break;
			}
		}
		int kod = (unsigned char)(text[pos]);
		pos += shift[kod];
	}
	return shablon_length - (pos - text_length + 1);
}    

int main(void)
{
	char shablon[20], text[TEXT_LENGTH];
	int shift[256];
	int shablon_length, 
	    text_length,     
	    offset = 0, 
	    start_pos = 1;

	if (NULL == fgets(shablon, 20, stdin))
	{
		printf("bad input!");
		return 0;
	}
	shablon_length = strlen(shablon);
	if (shablon[shablon_length - 1] == '\n')
	{
		shablon[shablon_length - 1] = '\0';
		shablon_length -= 1;
	}
	make_ShiftTable(shift, shablon, shablon_length);
	while ((text_length = fread(text + offset, sizeof(char), TEXT_LENGTH - offset, stdin)) > 0)
	{
		text_length += offset;
		offset = Boyer_Moor(text, shablon, text_length, shablon_length, shift, start_pos);
		start_pos += text_length - offset;
		for (int i = 0; i < offset; i++)
		{
			text[i] = text[text_length - offset + 1 + i];
		}
	}
}  
