#include "huffman.h"
#include <stdlib.h>

/**
 * huffman_tree - builds a Huffman tree from given data and frequencies
 * @data: array of characters
 * @freq: array of corresponding frequencies
 * @size: size of both arrays
 *
 * Return: pointer to root node of Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *q;
	node_t *left, *right, *parent;

	if (!data || !freq || size == 0)
		return (NULL);

	q = huffman_priority_queue(data, freq, size);
	if (!q)
		return (NULL);

	/* Extract two smallest nodes and combine until only one node remains */
	while (q->size > 1)
		huffman_extract_and_insert(q);

	/* Get the root of Huffman tree */
	if (!q->root)
	{
		free(q);
		return (NULL);
	}

	parent = q->root->data;
	free(q->root);
	free(q);

	return (parent);
}
