#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Edge
{
	int start;
	int end;
	int length;
}Edge;

int find_tree(int vertex, int* parent)
{
	if (vertex == parent[vertex])
		return vertex;
	return find_set(parent[vertex], parent);
}

int union_trees(int vertex1, int vertex2, int* parent, int* tree_size)
{
	vertex1 = find_set(vertex1, parent);
	vertex2 = find_set(vertex2, parent);
	if (vertex1 != vertex2)
	{
		if (tree_size[vertex1] < tree_size[vertex2])
		{
			int temp = vertex1;
			vertex1 = vertex2;
			vertex2 = temp;
		}
		parent[vertex2] = vertex1;
		tree_size[vertex1] += tree_size[vertex2];
	}
}

int Kruscal(Edge* graph, Edge* spanning_tree, int num_of_edges, int num_of_vertices)
{
	int* parent = (int*)malloc(sizeof(int));
	if (parent == NULL)
	{
		printf("Couldn't allocate mem for parent");
		free(graph);
		free(spanning_tree);
		return 0;
	}
	
	int* tree_size = (int*)malloc(num_of_edges * sizeof(int));
	if (tree_size == NULL)
	{
		printf("Couldn't allocate mem for tree_size");
		free(graph);
		free(spanning_tree);
		free(parent);
		return 0;
	}

	for (int i = 0; i < num_of_vertices; i++)
	{
		parent[i] = i;
		tree_size[i] = 1;
	}

	int edge_count = 0 ;
	for (int i = 0; i < num_of_edges; i++)
	{
		if (find_tree(graph->start - 1, parent) != find_tree(graph->end - 1, parent))
		{
			union_trees(graph->start - 1, graph->end - 1, parent, tree_size);
			spanning_tree[edge_count++] = graph[i];
		}
	}
	if (edge_count != num_of_edges)
	{
		printf("no spanning tree");
		free(graph);
		free(spanning_tree);
		free(parent);
		free(tree_size);
		exit(0);
	}

	return edge_count;
}

int main(void)
{
	int num_of_vertices,
		num_of_edges;
	if (scanf("%d", &num_of_vertices) != 1)
	{
		printf("bad lines");
		return 0;
	}
	if (num_of_vertices > 5000 || num_of_vertices < 0)
	{
		printf("bad number of vertices");
		return 0;
	}
	if (scanf("%d", &num_of_edges) == 0)
	{
		printf("");
		return 0;
	}
	if (num_of_edges < 0 || num_of_edges > (num_of_vertices * (num_of_vertices + 1) / 2))
	{
		printf("bad number of num_of_edges");
		return 0;
	}

	Edge* graph = (Edge*)malloc(sizeof(Edge));
	if (graph == NULL)
	{
		printf("Couldn't allocate mem for graph");
		free(graph);
		return 0;
	}
	Edge* spanning_tree = malloc(sizeof(Edge));
	if (spanning_tree == NULL)
	{
		printf("Couldn't allocate mem for spanning tree");
		free(graph);
		free(spanning_tree);
		return 0;
	}

	int nachalo, 
		konec, 
		dlina;
	for (int i = 0; i < num_of_edges; i++)
	{
		if (scanf("%d %d %d\n", &nachalo, &konec, &dlina) != 3)
		{
			printf("error");
			free(graph);
			free(spanning_tree);
			return 0;
		}
		if (dlina < 0 || dlina > INT_MAX)
		{
			printf("bad length");
			free(graph);
			free(spanning_tree);
			return 0;
		}
		graph[i].end = konec;
		graph[i].start = nachalo;
		graph[i].length = dlina;
	}

	int edge_count;
	edge_count = Kruscal(graph, spanning_tree, num_of_edges, num_of_vertices);
	for (int i = 0; i < edge_count; i++)
	{
		printf("%d %d\n", spanning_tree[i].start, spanning_tree[i].end);
	}
	free(graph);
	free(spanning_tree);
	return 0;
}
