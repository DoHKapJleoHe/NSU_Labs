#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <malloc.h>
#include <math.h>
typedef struct node node;
struct node
{
	node* to1;
	node* to0;
	int freq;
	char symb;
};
typedef struct Position Position;
struct Position
{
	unsigned int bit_pos;
	unsigned int byte_pos;
};
int qSort(node** mas, int left, int right);
int partition(node** mas, int left, int right)
{
	int piv = mas[(left + right) / 2]->freq;
	int left_1 = left,
		right_1 = right;
	while (left_1 <= right_1)
	{
		while (mas[left_1]->freq < piv)
		{
			left_1++;
		}
		while (mas[right_1]->freq > piv)
		{
			right_1--;
		}
		if (left_1 >= right_1)
			break;
		int temp = mas[left_1]->freq;
		mas[left_1]->freq = mas[right_1]->freq;
		mas[right_1]->freq = temp;

		left_1++;
		right_1--;
	}
	return right_1;
}

int qSort(node** mas, int left, int right)
{
	if (left < right)
	{
		int q = partition(mas, left, right);
		qSort(mas, left, q);
		qSort(mas, q + 1, right);
	}
}

node* build_tree(node** mas, int mas_size)
{
	 // i take two symbols with the lowest freq and make of them 
	 // a node with freq equal to sum of their freqs
	 while (mas_size > 1)
	 {
		 // ПЕРЕДЕЛАТЬ КВИКСОРТ НА СОРТИРОВКУ ПО УБЫВАНИЮ!!!!!!!!
		 qSort(mas, 0, mas_size - 1);  // sorting array of nodes
		 node* min1 = mas[mas_size - 1];
		 node* min2 = mas[mas_size - 2];

		 node* new_node = (node*)malloc(sizeof(node));
		 new_node->freq = min1->freq + min2->freq;
		 new_node->to0 = min1;
		 new_node->to1 = min2;

		 mas[mas_size - 2] = new_node;
		 mas_size--;
	 }
	 return mas[0]; // возвращаем mas[0], т.к. в него будет сложен весь массив и, соответсвенно, он будет корнем
}

void make_code(node* root, char** code, char *path, int length_of_path)
{
	if (root != NULL)
	{
		if (root->to0) 
		{
			path[length_of_path] = '0';
			make_code(root->to0, code, path, length_of_path + 1);
			path[length_of_path] = '1';
			make_code(root->to1, code, path, length_of_path + 1);
		}
		else
		{
			path[length_of_path] = 0;
			code[root->symb] = (char*)memcpy(malloc(length_of_path + 1), path, length_of_path + 1);
		}
	}
}
void write_tree(node* root, unsigned char* bit_mas, Position* pos)
{
	if (root->to0)
	{
		pos->bit_pos++;
		if (8 == pos->bit_pos)
		{
			pos->bit_pos = 0;
			pos->byte_pos++;
		}

		write_tree(root->to0, bit_mas, pos);
		write_tree(root->to1, bit_mas, pos);
	}
	else
	{
		bit_mas[pos->byte_pos] |= 128u >> pos->bit_pos;
		pos->bit_pos++;
		if (8 == pos->bit_pos)
		{
			pos->bit_pos = 0;
			pos->byte_pos++;
		}
		if (0 == pos->bit_pos)
		{
			bit_mas[pos->byte_pos] |= root->symb >> pos->bit_pos;
			bit_mas[pos->byte_pos] |= root->symb << (8 - pos->bit_pos);
		}
		pos->byte_pos++;
	}
}

node* read_tree(unsigned char* bit_buf, Position* pos)
{
	node* root = (node*)malloc(sizeof(node));
	if (8 == pos->bit_pos)
	{
		pos->bit_pos = 0;
		pos->byte_pos++;
	}
	int bit = bit_buf[pos->byte_pos] & (128u >> pos->byte_pos++);
	if (0 == bit)
	{
		root->to0 = read_tree(bit_buf, pos);
		root->to1 = read_tree(bit_buf, pos);
	}
	else
	{
		root->to1 = root->to0 = NULL;
		if (0 == pos->bit_pos)
		{
			root->symb = bit_buf[pos->byte_pos];
		}
		else
		{
			root->symb = (bit_buf[pos->byte_pos] << pos->bit_pos) | (bit_buf[pos->byte_pos] >> (8 - pos->bit_pos));
		}
		pos->byte_pos++;
	}
	return root;
}

int zip(FILE* fin, FILE* fout, FILE* log)
{
	int freq[256] = { 0 };

	unsigned char *text = (unsigned char*)malloc(sizeof(unsigned char)*100000);
	if (text == NULL)
	{
		fprintf(log, "memory error");
		exit(0);
	}
	int to_zip_size = 0;
	while (1)
	{
		int fsize = fread(text, sizeof(char), 100000, fin); // reading text by portions of BUF size
		if (fsize == 0)
			break;
		for (int i = 0; i < fsize; ++i)
		{
			freq[text[i]]++; // calculating frequensy of each symbol in the text
		}
	}
	
	node* nodes[256];  // array of nodes
	nodes[0] = NULL;
	int k = 0;
	for (int i = 0; i < 256; i++)
	{
		if (freq[i] != 0)
		{
			node* leaf;
			leaf = malloc(sizeof(node));
			leaf->to0 = NULL;
			leaf->to1 = NULL;
			leaf->freq = freq[i];
			leaf->symb = i;
			nodes[k++] = leaf;
		}
	}

	node* root = build_tree(nodes, k);
	char path[256]; // для левостороннего обхода дерева. массив размера 256 для самого плохого случая, т.е. когда дерево всё слева построеноа, а спрва ничего нет
	char* code[256];
	make_code(root, code, path, 0);

	unsigned char bit_mas[1024];
	Position* pos = (Position*)malloc(sizeof(Position));
	write_tree(root, bit_mas, pos);
	
}

void decode(unsigned char* bit_buf, Position* pos,node* root, unsigned int total_length, FILE* fin, FILE* fout)
{
	char* out_buf[1024];
	unsigned int out_pos = 0;
	unsigned int bit_pos = pos->bit_pos,
		         byte_pos = pos->byte_pos;
	while (total_length > 0)
	{
		node* cur = root;
		while (cur->to0 != NULL)
		{
			int bit;
			if (8 == bit_pos)
			{
				bit_pos = 0;
				byte_pos++;
				if (1024 == byte_pos)
				{
					fread(bit_buf, 1, byte_pos, fin);
					byte_pos = 0;
				}
			}
			bit = bit_buf[byte_pos] & (188u >> bit_pos++);
			cur = bit ? cur->to1 : cur->to0;
		}
		out_buf[out_pos++] = cur->symb;
		if (1024 == out_pos)
		{
			fwrite(out_buf, 1, out_pos, fout);
			out_pos = 0;
		}
		total_length--;
	}
	fwrite(out_buf, 1, out_pos, fout);
}

int unzip(FILE* fin, FILE* fout, FILE* log, unsigned int file_size)
{
	unsigned char bit_buf[1024];
	Position* pos = (Position*)malloc(sizeof(Position));
	read_tree(bit_buf, pos);
	decode(bit_buf, pos, 0, file_size, fin, fout);
}



int main()
{
	FILE* fin = fopen("in.txt", "wb");
	FILE* fout = fopen("out.txt", "rb");
	FILE* log = fopen("log.txt", "wb"); // maybe i have to write "w"

	fseek(fin, 0, SEEK_END);    // moves coursor to the end of the file
	int file_size = ftell(fin); // size of the file


	char vvod[4];
	fread(vvod, sizeof(char), 3, fin);

	if (vvod[0] == 'c')
		zip(fin, fout, log);
	if (vvod[0] == 'd')
		unzip(fin, fout, log, file_size);


	return 0;
}
