#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 * @graph: Pointer to the graph
 * @str: String to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *tmp;
	char *copy;

	if (!graph || !str)
		return (NULL);

	/* Check for duplicate vertex */
	for (tmp = graph->vertices; tmp; tmp = tmp->next)
	{
		if (strcmp(tmp->content, str) == 0)
			return (NULL);
	}

	copy = strdup(str);
	if (!copy)
		return (NULL);

	vertex = calloc(1, sizeof(vertex_t));
	if (!vertex)
	{
		free(copy);
		return (NULL);
	}

	vertex->content = copy;
	vertex->index = graph->nb_vertices;
	vertex->next = graph->vertices;

	graph->vertices = vertex;
	graph->nb_vertices++;

	return (vertex);
}
