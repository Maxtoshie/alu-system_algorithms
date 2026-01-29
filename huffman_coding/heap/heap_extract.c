#include "heap.h"
#include <stdlib.h>

/* Helper: restore heap property from root downwards */
static void heapify(node_t *root, int (*data_cmp)(void *, void *))
{
	if (!root || !root->left || !data_cmp)
		return;

	if (root->right && data_cmp(root->left->data, root->right->data) > 0)
	{
		if (data_cmp(root->data, root->right->data) >= 0)
			DATASWAP(root, root->right);
		heapify(root->right, data_cmp);
	}
	else
	{
		if (data_cmp(root->data, root->left->data) >= 0)
			DATASWAP(root, root->left);
		heapify(root->left, data_cmp);
	}
}

/* Helper: convert heap tree to array (optional, can suppress unused warnings) */
static size_t heap_to_array(node_t **array, node_t *root, size_t i)
{
	if (!root || !array)
		return 0;

	array[i] = root;
	return 1 + heap_to_array(array, root->left, 2 * i + 1)
		+ heap_to_array(array, root->right, 2 * i + 2);
}

/**
 * heap_extract - extracts the root value of a Min Binary Heap
 * @heap: heap_t pointer
 * Return: generic pointer to data that was stored in heap's root, or NULL
 */
void *heap_extract(heap_t *heap)
{
	node_t *a[32], *last;
	void *data;

	if (!heap || !heap->root)
		return NULL;

	/* convert heap to array */
	if (heap->size != heap_to_array(a, heap->root, 0))
		return NULL;

	data = heap->root->data;
	last = a[heap->size - 1];

	if (heap->root == last)
	{
		heap->root = NULL;
	}
	else
	{
		heap->root->data = last->data;
		if (last->parent->left == last)
			last->parent->left = NULL;
		else
			last->parent->right = NULL;

		heapify(heap->root, heap->data_cmp);
	}

	free(last);
	heap->size--;

	return data;
}
