#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 * @graph: Pointer to the graph to add the vertex to
 * @str:   String to store in the new vertex (will be duplicated)
 *
 * Description: Creates a new vertex with a copy of the given string.
 *              Checks for duplicate content (case-sensitive).
 *              Inserts the vertex at the end of the list so that
 *              vertices appear in the order they were added.
 *
 * Return: Pointer to the created vertex, or NULL on failure
 *         (invalid input, allocation failure, or duplicate content)
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_v;
	vertex_t *current;
	char *content_copy;

	if (graph == NULL || str == NULL)
		return (NULL);

	/* Reject duplicates — content must be unique */
	current = graph->vertices;
	while (current != NULL)
	{
		if (strcmp(current->content, str) == 0)
			return (NULL);
		current = current->next;
	}

	content_copy = strdup(str);
	if (content_copy == NULL)
		return (NULL);

	new_v = calloc(1, sizeof(vertex_t));
	if (new_v == NULL)
	{
		free(content_copy);
		return (NULL);
	}

	new_v->content = content_copy;
	new_v->index   = graph->nb_vertices;
	new_v->nb_edges = 0;
	new_v->edges   = NULL;
	new_v->next    = NULL;

	/* Insert at tail (preserves chronological order) */
	if (graph->vertices == NULL)
	{
		graph->vertices = new_v;
	}
	else
	{
		current = graph->vertices;
		while (current->next != NULL)
			current = current->next;
		current->next = new_v;
	}

	graph->nb_vertices++;

	return (new_v);
}
