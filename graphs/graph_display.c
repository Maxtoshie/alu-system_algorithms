#include <stdio.h>
#include "graphs.h"

/**
 * graph_display - Displays the graph's vertices
 * @graph: Pointer to the graph
 */
void graph_display(const graph_t *graph)
{
	const vertex_t *vertex;

	if (graph == NULL)
	{
		printf("Graph: (null)\n");
		return;
	}

	printf("Number of vertices: %zu\n", graph->nb_vertices);

	for (vertex = graph->vertices; vertex != NULL; vertex = vertex->next)
	{
		printf("[%zu] %s\n", vertex->index, vertex->content);
	}
}
