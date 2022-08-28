#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int add(unsigned int a, unsigned int b)
{
	if (a > (unsigned int)INT_MAX || b > (unsigned int)INT_MAX || a+b > (unsigned int)INT_MAX)
		return (unsigned int)INT_MAX + 1;
	else
		return a+b;
}

void dijkstra(short int start, unsigned int* graph, int number_of_vertices, unsigned int* dlina, short int* parent, short int finish, int* perepolnenie)
{
	char* visited = (char*)malloc(number_of_vertices * sizeof(char));
	if (!visited)
	{
		printf("Couldn't allocate space for visited");
		free(graph);
		free(dlina);
		free(parent);
		exit(1);
	}
	memset(visited, 0, number_of_vertices);

	for (int i = 0; i < number_of_vertices; i++)
	{
		if (graph[start * number_of_vertices + i] == UINT_MAX)
			parent[i] = i;
		else
			parent[i] = start;
		dlina[i] = graph[start * number_of_vertices + i];
	}
	dlina[start] = 0;

	short int new_vertex = start;
	for (int i = 0; i < number_of_vertices; i++)
	{
		visited[new_vertex] = 1;
		for (short int j = 0; j < number_of_vertices; j++)
		{
			unsigned int newvertex_to_vertex = graph[new_vertex * number_of_vertices + j];
			if (newvertex_to_vertex != UINT_MAX && ((newvertex_to_vertex = add(newvertex_to_vertex, dlina[new_vertex])) <= dlina[j] || dlina[j] == UINT_MAX))
			{
				dlina[j] = newvertex_to_vertex;
				parent[j] = new_vertex;
				if (j == finish && dlina[j] > (unsigned int)INT_MAX)
					(*perepolnenie)++;
			}
		}
		unsigned int min_dlina = UINT_MAX;
		for (short int j = 0; j < number_of_vertices; j++)
		{
			if (!visited[j])
			{
				if ((dlina[j] < min_dlina || min_dlina == UINT_MAX) && dlina[j] != UINT_MAX)
				{
					min_dlina = dlina[j];
					new_vertex = j;
				}
			}
		}
		if (min_dlina == UINT_MAX)
		{
			break;
		}
	}
	free(visited);
}

int main(void)
{
	int number_of_vertices,
		number_of_edges;
	short int start,
		finish;

	if (scanf("%d\n", &number_of_vertices) != 1)
	{
		printf("bad number of lines\n");
		return 0;
	}
	if ((number_of_vertices > 5000) || (number_of_vertices < 0))
	{
		printf("bad number of vertices\n");
		return 0;
	}
	if (scanf("%hd %hd\n", &start, &finish) != 2)
	{
		printf("bad number of lines\n");
		return 0;
	}
	if ((start > number_of_vertices) || (start < 1) || (finish < 1) || (finish > number_of_vertices))
	{
		printf("bad vertex\n");
		return 0;
	}
	start--;
	finish--;

	if (scanf("%d\n", &number_of_edges) != 1)
	{
		printf("bad number of lines\n");
		return 0;
	}
	if ((number_of_edges > number_of_vertices * (number_of_vertices - 1) / 2) || (number_of_edges < 0))
	{
		printf("bad number of edges\n");
		return 0;
	}

	unsigned int* graph = (unsigned int*)malloc(number_of_vertices * number_of_vertices * sizeof(unsigned int));
	if (graph == NULL)
	{
		printf("Couldn't allocate space for graph");
		return 1;
	}
	for (int i = 0; i < number_of_vertices * number_of_vertices; i++)
	{
		graph[i] = UINT_MAX;
	}

	short int start1, end;
	long int edge_length;
	for (int i = 0; i < number_of_edges; i++) 
	{
		if (scanf("%hd %hd %ld\n", &start1, &end, &edge_length) != 3)
		{
			printf("bad number of lines\n");
			free(graph);
			return 0;
		}
		if (start1 < 1 || start1 > number_of_vertices || end < 1 || end > number_of_vertices)
		{
			printf("bad vertex\n");
			free(graph);
			return 0;
		}
		if (edge_length < 0 || edge_length > INT_MAX) {
			printf("bad length\n");
			free(graph);
			return 0;
		}

		graph[(start - 1) * number_of_vertices + (end - 1)] = (unsigned int)edge_length;
		graph[(end - 1) * number_of_vertices + (start - 1)] = (unsigned int)edge_length;
	}

	unsigned int* dlina = (unsigned int*)malloc(number_of_vertices * sizeof(unsigned int));
	if (!dlina)
	{
		printf("Couldn't allocate space for dlina");
		free(graph);
		return 1;
	}

	short int* parent = (short int*)malloc(number_of_vertices * sizeof(short int));
	if (!parent)
	{
		printf("Couldn't allocate for parent");
		free(graph);
		free(dlina);
		return 1;
	}

	int perepolnenie = 0;
	dijkstra(start, graph, number_of_vertices, dlina, parent, finish, &perepolnenie);

	for (int i = 0; i < number_of_vertices; i++)
	{
		if (parent[i] == i && i != start)
		{
			printf("oo ");
		}
		else {
			if (dlina[i] > (unsigned int)INT_MAX)
				printf("INT_MAX+ ");
			else
				printf("%u ", dlina[i]);
		}
	}
	printf("\n");
	if (dlina[finish] == UINT_MAX)
		printf("no path\n");
	else
	{
		if (perepolnenie >= 2)
			printf("overflow\n");
		else
		{
			while (finish != start)
			{
				printf("%d ", finish + 1);
				finish = parent[finish];
			}
			printf("%d\n", finish + 1);
		}
	}

	free(graph);
	free(dlina);
	free(parent);

	return 0;
}
