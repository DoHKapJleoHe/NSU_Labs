#define CRT_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SHABLON_LENGTH 20
#define TEXT_LENGTH 4096

int Hash(char* shablon, int shablon_length)
{
	int i = 0;
	int hash = 0;
	while (i < shablon_length)
	{
		hash += (unsigned long)(((unsigned char)shablon[i] % 3) * pow(3, i)); // что-то надо сделать
		i++;
	}
	return hash;
}

void proverka (char* shablon, char* text, int shablon_length, int index)
{
	int j = 0;
	while (j <= shablon_length)
	{
		printf("%d\n", j + index);
		if (shablon[j] != text[j])
			break;
		j++;
	}
	
}

void Rabin_Karp (char* shablon, char* text, int shablon_length, int shablon_hash, int index, int read_text)
{
	shablon_length -= 1;
	int text_hash = Hash(text, shablon_length);
	int stepen = (unsigned long)pow(3, shablon_length);
	int konec = read_text - shablon_length,
		i = 0;
    //printf("%d\n", shablon_hash);
	while (i < konec)
	{
		text_hash = (unsigned long)(text_hash + ((unsigned char)(text[i + shablon_length]) % 3) * stepen);
		if (shablon_hash == text_hash)
		{
			proverka(shablon, text + i, shablon_length, index + i);
		}
		text_hash = (text_hash - ((unsigned char)(text[i]) % 3)) / 3;
		i++;
	}
	
}

int main(void)
{
	char shablon[SHABLON_LENGTH];
	char text[TEXT_LENGTH];
	if (NULL == fgets(shablon, SHABLON_LENGTH, stdin))
	{
		printf("Bad input!");
		return 0;
	}
	unsigned int shablon_length = strlen(shablon) - 1;
	int shablon_hash = Hash(shablon, shablon_length);
	unsigned int read_text = 0,
		offset = 0,
		index = 1;
    read_text = (unsigned int)fread(text + offset, 1, TEXT_LENGTH - offset, stdin);
	if (read_text == 0)
	{
		printf("%d", 0);
		return 0;
	}
	printf("%d\n", shablon_hash);
	while (read_text > 0)
	{
			printf("\n");
			read_text += offset;
			if (shablon_length <= read_text)
			{
				Rabin_Karp(shablon, text, shablon_length, shablon_hash, index, read_text);
			}
			offset = shablon_length - 1;
			index = index + read_text - offset;
			if (read_text > offset)
			{
				memcpy(text, text + TEXT_LENGTH - offset, offset);
			}
			read_text = (unsigned int)fread(text + offset, 1, TEXT_LENGTH - offset, stdin);
	}
	return 0;
}
