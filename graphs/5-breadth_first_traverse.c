#include <stdlib.h>
#include "graphs.h"

/**
 * breadth_first_traverse - Traverses a graph using breadth-first search
 * @graph: Pointer to the graph to traverse
 * @action: Function to call on each visited vertex
 *
 * Return: Maximum depth reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	vertex_t **queue;
	size_t *depths;
	int *visited;
	size_t front = 0, rear = 0, max_depth = 0;
	vertex_t *v;
	edge_t *edge;
	size_t depth;

	if (!graph || !graph->vertices || !action)
		return (0);

	queue = calloc(graph->nb_vertices, sizeof(vertex_t *));
	depths = calloc(graph->nb_vertices, sizeof(size_t));
	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!queue || !depths || !visited)
		goto fail;

	/* Start from the first vertex */
	queue[rear] = graph->vertices;
	depths[rear++] = 0;
	visited[graph->vertices->index] = 1;

	while (front < rear)
	{
		v = queue[front];
		depth = depths[front++];
		action(v, depth);

		if (depth > max_depth)
			max_depth = depth;

		for (edge = v->edges; edge; edge = edge->next)
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				queue[rear] = edge->dest;
				depths[rear++] = depth + 1;
			}
		}
	}

	free(queue);
	free(depths);
	free(visited);
	return (max_depth);

fail:
	free(queue);
	free(depths);
	free(visited);
	return (0);
}
