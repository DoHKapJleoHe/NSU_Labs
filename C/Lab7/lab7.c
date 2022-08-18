#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

void topological_sort(char* graph, int number_of_vertices, int byts_for_matrix, int current_position, char* visited_vertices, int** stack_pointer)
{
	visited_vertices[current_position] = 1;

	for (int i = 0; i < number_of_vertices; i++)
	{
		if (graph[current_position * byts_for_matrix + i / 8] & (128 >> (i % 8))) // типо если в этой позиции не ноль, то действуем? попросить объяснить!!!
		{
			if (visited_vertices[i] == 1)
			{
				printf("Impossible to sort");
				exit(0);
			}

			if (!visited_vertices[i])
			{
				topological_sort(graph, number_of_vertices, byts_for_matrix, i, visited_vertices, stack_pointer);
			}
		}
	}
	visited_vertices[current_position] = 2;
	*(*stack_pointer) = current_position + 1;
	(*stack_pointer)++;
}

int main(void)
{
	int number_of_vertices,
		number_of_edges;
	if (scanf("%d", &number_of_vertices) != 1)
	{
		printf("bad number of verices\n"); // ?
		return 0;
	}
	if (number_of_vertices < 0 || number_of_vertices > 2000)
	{
		printf("bad number of vertices\n");
		return 0;
	}
	if (scanf("%d", &number_of_edges) != 1)
	{
		printf("bad number of edges");
	}
	if (number_of_edges < 0 || number_of_edges > number_of_vertices * (number_of_vertices + 1) / 2)
	{
		printf("bad number of edges");
		return 0;
	}

	// Для чего нужна эта штука? Тут я узнаю сколько чаров(8 бит) мне нужно для построения матрицы смежности, а именно 
    // строчки: если допустим пришло 4 вершины, то 1 байта будет достаточно, чтобы записать туда верншины(1 чар = 8 бит) --->  00000000   - чар
	// если этого недостаточно, то нужно уже 2 байта. Например, если вершин не 4, а 10. Тогда потребутся 2 байта
	int byts_for_matrix = (number_of_vertices + 7) / 8;  
	char* graph = (char*)malloc(sizeof(char) * byts_for_matrix * number_of_vertices);
	if (graph == NULL)
	{
		printf("Couldn't allocate memory for graph");
		return 0;
	}

	memset(graph, 0, number_of_vertices * byts_for_matrix);

	int start,
		end;
	for (int i = 0; i < number_of_edges; i++)
	{
		if (scanf("%d %d", &start, &end) != 2)
		{
			printf("bad number of lines");
			free(graph);
			return 0;
		}
		if (start < 1 || start > number_of_vertices || end < 1 || end > number_of_vertices)
		{
			printf("bad vertex");
			free(graph);
			return 0;
		}
		// как работает строчка ниже? Я смотрю в какую ячейку матрицы смежности нужно положить 1. Это зависит от того, какие start и end придут.
		// допустим пришли start = 1, end = 3 и 4 вершины. Теперь считаем: graph[ (0) * 1 + (2 / 8 = 0) ] = graph[0] т.е. еденичку мы должны 
		// будем положить в нулевом байте. Дальше я делаю побитовое ИЛИ: беру 128(это 10000000 в двоичной системе) и сдвигаю еденичку на (end - 1) бит.
		graph[(start - 1) * byts_for_matrix + (end - 1)/8] |= 128 >> (end - 1) % 8;
	}

	int* sorted_vertices = (int*)malloc(sizeof(int) * number_of_vertices);
	if (sorted_vertices == NULL)
	{
		printf("Couldn't allocate memory for the sorted vertices");
		free(graph);
		return 0;
	}
	int* stack = sorted_vertices; // тут храним текущее значение массива sorted_vertices
	int** stack_pointer = &stack; // тут лежит адрес стека

	char* visited_vertices = (char*)malloc(sizeof(char) * number_of_vertices);
	if (visited_vertices == NULL)
	{
		printf("Couldn't allocate memory for array of visited vertices");
		free(sorted_vertices);
		free(graph);
		return 0;
	}
	
	memset(visited_vertices, 0, number_of_vertices);

	for (int i = 0; i < number_of_vertices; i++)
	{
		if (!visited_vertices[i])
			topological_sort(graph, number_of_vertices, byts_for_matrix, i, visited_vertices, stack_pointer);
	}
	
	while (stack != sorted_vertices)
	{
		stack--;
		printf("%hd ", *stack);
	}

	free(visited_vertices);
	free(graph);
	free(sorted_vertices);

	return 0;
}
