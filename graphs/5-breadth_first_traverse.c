#include <stdlib.h>
#include <stdio.h>   /* only if using perror/debug — can remove */
#include "graphs.h"

/**
 * queue_push - Enqueue a vertex with its depth
 * @queue: Double pointer to queue head
 * @vertex: Vertex to enqueue
 * @depth: Depth of this vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int queue_push(vertex_t **queue, vertex_t *vertex, size_t depth)
{
	vertex_t *new_node = malloc(sizeof(vertex_t));

	if (!new_node)
		return (0);

	new_node->content = (char *)(uintptr_t)depth;  /* abuse content as depth holder */
	new_node->index   = vertex->index;             /* optional, for debug */
	new_node->next    = NULL;
	new_node->edges   = (edge_t *)vertex;          /* store real vertex pointer here */

	if (*queue == NULL)
	{
		*queue = new_node;
	}
	else
	{
		vertex_t *tmp = *queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (1);
}

/**
 * queue_pop - Dequeue and return the stored vertex + depth
 * @queue: Double pointer to queue head
 * @vertex: Where to store the real vertex pointer
 * @depth: Where to store the depth
 *
 * Return: 1 if dequeued, 0 if empty
 */
static int queue_pop(vertex_t **queue, vertex_t **vertex, size_t *depth)
{
	vertex_t *front;

	if (*queue == NULL)
		return (0);

	front = *queue;
	*vertex = (vertex_t *)front->edges;
	*depth  = (size_t)(uintptr_t)front->content;

	*queue = front->next;
	free(front);
	return (1);
}

/**
 * is_visited - Check if vertex index is already visited
 * @visited: Array of visited flags
 * @index: Vertex index to check
 * @size: Size of visited array
 *
 * Return: 1 if visited, 0 otherwise
 */
static int is_visited(char *visited, size_t index, size_t size)
{
	if (index >= size)
		return (0);
	return (visited[index]);
}

/**
 * mark_visited - Mark vertex as visited
 * @visited: Array of visited flags
 * @index: Vertex index
 * @size: Size of array
 */
static void mark_visited(char *visited, size_t index, size_t size)
{
	if (index < size)
		visited[index] = 1;
}

/**
 * breadth_first_traverse - Performs BFS traversal from first vertex
 * @graph: Pointer to the graph
 * @action: Function to call on each visited vertex
 *
 * Return: Maximum depth reached, or 0 on failure / empty graph
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *, size_t))
{
	vertex_t *start, *current, *neighbor;
	vertex_t *queue = NULL;
	char *visited = NULL;
	size_t max_depth = 0;
	size_t depth, i;

	if (!graph || !graph->vertices || !action)
		return (0);

	start = graph->vertices;
	if (!start)
		return (0);

	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
		return (0);

	/* Enqueue start vertex at depth 0 */
	if (!queue_push(&queue, start, 0))
	{
		free(visited);
		return (0);
	}

	mark_visited(visited, start->index, graph->nb_vertices);

	if (action)
		action(start, 0);

	while (queue_pop(&queue, &current, &depth))
	{
		if (depth > max_depth)
			max_depth = depth;

		/* Visit all neighbors */
		for (edge_t *edge = current->edges; edge; edge = edge->next)
		{
			neighbor = edge->dest;
			if (!is_visited(visited, neighbor->index, graph->nb_vertices))
			{
				mark_visited(visited, neighbor->index, graph->nb_vertices);

				if (!queue_push(&queue, neighbor, depth + 1))
				{
					/* On failure: clean up and return what we have */
					while (queue_pop(&queue, &current, &depth))
						;
					free(visited);
					return (max_depth);
				}

				if (action)
					action(neighbor, depth + 1);
			}
		}
	}

	free(visited);
	return (max_depth);
}
