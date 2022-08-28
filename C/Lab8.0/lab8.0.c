#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge Edge;
struct Edge
{
	short int start;
	short int end;
	int edge_length;
};

int compare(const void* a1, const void* a2)
{
	return ((Edge*)a1)->edge_length - ((Edge*)a2)->edge_length;
}

short int seek(short int vertex, short int* parent)
{
	if (parent[vertex] == vertex)
		return vertex;
	return parent[vertex] = seek(parent[vertex], parent);
}

void merge(short int start, short int end, short int* parent, short int* tree_size)
{
	int start_pos = seek(start, parent);
	int end_pos = seek(end, parent);
	if (start_pos != end_pos)
	{
		if (tree_size[start_pos] > tree_size[end_pos]) {
			parent[end_pos] = start_pos;
			tree_size[start_pos] += tree_size[end_pos];
		}
		else
		{
			parent[start_pos] = end_pos;
			tree_size[end_pos] += tree_size[start_pos];
		}
	}
}

int build_tree(Edge* graph_edges, Edge* ostovnoe_derevo, int number_of_edges, int number_of_vertices)
{
	qsort(graph_edges, number_of_edges, sizeof(Edge), compare);
	short int* parent = (short int*)malloc(sizeof(short int) * number_of_vertices);
	if (parent == NULL) {
		printf("Couldn't allocate memory for parent");
		free(graph_edges);
		free(ostovnoe_derevo);
		return 0;
	}
	short int* tree_size = (short int*)malloc(sizeof(short int) * number_of_vertices);
	if (tree_size == NULL)
	{
		printf("Couldn't allocate space for tree_sizes");
		free(graph_edges);
		free(parent);
		free(ostovnoe_derevo);
		return 0;
	}
	for (int i = 0; i < number_of_vertices; i++)
	{
		parent[i] = i;
		tree_size[i] = i;
	}

	int count = 0;
	for (int i = 0; i < number_of_edges; i++)
	{
		if (seek(graph_edges[i].start - 1, parent) != seek(graph_edges[i].end - 1, parent))
		{
			merge(graph_edges[i].start - 1, graph_edges[i].end - 1, parent, tree_size);
			ostovnoe_derevo[count++] = graph_edges[i];
		}
	}
	if (tree_size[seek(0, parent)] != number_of_vertices)
	{
		printf("no spanning tree\n");
		free(graph_edges);
		free(ostovnoe_derevo);
		free(parent);
		free(tree_size);
		exit(0);
	}
	free(parent);
	free(tree_size);

	return count;
}

int main(void)
{
	int number_of_vertices,
		number_of_edges;
	if (scanf("%d", &number_of_vertices) != 1)
	{
		printf("bad number of lines\n");
		return 0;
	}
	if ((number_of_vertices > 5000) || (number_of_vertices < 0))
	{
		printf("bad number of vertices\n");
		return 0;
	}
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
	if (number_of_vertices == 0) {
		printf("no spanning tree\n");
		return 0;
	}

	Edge* graph_edges = (Edge*)malloc(sizeof(Edge) * number_of_edges); // this array will contain edges
	if (graph_edges == NULL)
	{
		printf("Couldn't allocate memory for graph_edges");
		return 0;
	}

	Edge* ostovnoe_derevo = (Edge*)malloc(sizeof(Edge) * number_of_edges);
	if (ostovnoe_derevo == NULL)
	{
		printf("Couldn't allocate memory for ostovnoe_derevo");
		free(graph_edges);
		return 0;
	}

	short int start, end;
	long int edge_length;
	for (int i = 0; i < number_of_edges; i++)
	{
		if (scanf("%hd %hd %ld\n", &start, &end, &edge_length) != 3)
		{
			printf("bad number of lines");
			free(graph_edges);
			free(ostovnoe_derevo);
			return 0;
		}
		if (start < 0 || start > number_of_vertices || end < 0 || end > number_of_vertices)
		{
			printf("bad vertex\n");
			free(graph_edges);
			free(ostovnoe_derevo);
			return 0;
		}
		if (edge_length < 0 || edge_length > INT_MAX) {
			printf("bad length\n");
			free(graph_edges);
			free(ostovnoe_derevo);
			return 0;
		}

		graph_edges[i].start = start;
		graph_edges[i].end = end;
		graph_edges[i].edge_length = (int)edge_length;
	}

	int ammount_of_edges = build_tree(graph_edges, ostovnoe_derevo, number_of_edges, number_of_vertices);
	for (int i = 0; i < ammount_of_edges; i++) {
		printf("%hd %hd\n", ostovnoe_derevo[i].start, ostovnoe_derevo[i].end);
	}

	free(ostovnoe_derevo);
	free(graph_edges);

	return 0;
}
