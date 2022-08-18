#include<stdio.h>
#include<stdlib.h>

int Diykstra(int otkuda, int kuda,int* dlina_puti, unsigned int* graph, int* parent, int number_of_vertices, int number_of_edges)
{
	int* posetil = (int*)malloc(number_of_vertices * sizeof(int));
	if (posetil == NULL)
	{
		printf("Couldn't allocate mem for posetil");
		free(graph);
		free(dlina_puti);
		return 0;
	}
	
	for (int vertex = 0; vertex < number_of_vertices; vertex ++)
	{
		if (graph[vertex + otkuda * number_of_vertices] == UINT_MAX)
			parent[vertex] = vertex;
		else
			parent[vertex] = otkuda;
		dlina_puti[vertex] = graph[vertex + number_of_vertices * otkuda];
	}

	dlina_puti[otkuda] = 0;

	int new_vertex = otkuda;
	for (int i = 0; i < number_of_vertices; i++)
	{


	}
}

int main(void)
{
	int num_of_vertices;
	if (scanf("%d\n", &num_of_vertices) != 1)
	{
		printf("bad number of lines"); // maybe "bad number of vertices" ?
		return 0;
	}
	if ( num_of_vertices > 5000 || num_of_vertices < 0)
	{
		printf("bad number of vertices");
		return 0;
	}

	int na4alo,
		konec;
	if (scanf("%d %d\n", &na4alo, &konec) != 2)
	{
		printf("bad number of lines");
		return 0;
	}
	if (na4alo > num_of_vertices || na4alo < 0 || konec > 5000 || konec < 0)
	{
		printf("bad number of lines");
		return 0;
	}

	int num_of_edges;
	if (scanf("%d", &num_of_edges) != 1)
	{
		printf("bad number of lines");
		return 0;
	}
	if (num_of_edges < 0 || num_of_edges > (num_of_vertices * (num_of_vertices - 1)) / 2)
	{
		printf("bd number of edges");
		return 0;
	}

	unsigned int* graph = (unsigned int*)malloc(num_of_vertices * num_of_vertices * sizeof(unsigned int));
	if (graph == NULL)
	{
		printf("Couldn't allocate memory for graph");
		free(graph);
		return 0;
	}
	for (int i = 0; i < num_of_vertices * num_of_vertices; i++)
	{
		graph[i] = UINT_MAX;
	}

	int na4alo_1,
		konec_1,
		length_1;
	for (int i = 0; i < num_of_edges; i++)
	{
		if (scanf("%d %d %d\n", &na4alo_1, &konec_1, &length_1) != 3)
		{
			printf("bad number of lines");
			free(graph);

		}
		if (na4alo_1 < 1 || na4alo_1 > num_of_vertices || konec_1 < 1 || konec_1 > num_of_vertices || length_1 < 0 || length_1 > INT_MAX)
		{
			printf("bad vertex");
			free(graph);
			return 0;
		}

		graph[(na4alo_1 - 1) + num_of_vertices * (konec_1 - 1)] = (unsigned int)length_1;
		graph[(konec_1 - 1) + num_of_vertices * (na4alo_1 - 1)] = (unsigned int)length_1;
	}


	int* dlina_puti = (int*)malloc(num_of_vertices * sizeof(int));
	if (dlina_puti == NULL)
	{
		printf("Couldn't allocate mem fo dlina_puti");
		free(graph);
		return 0;
	}
	int* parent = (int*)malloc(num_of_vertices * sizeof(int));

    Diykstra(na4alo, konec, dlina_puti, graph, parent, num_of_vertices, num_of_edges);

	return 0;
}
