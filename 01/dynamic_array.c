#include <stdlib.h>
#include <stdbool.h>

#include "dynamic_array.h"
#include "../util.h"

#define GROW_BY 500

struct Array {
	size_t capacity;
	size_t length;
	int *inner;
};

struct Array *Array_new(size_t capacity)
{
	struct Array *a = malloc(sizeof(struct Array));
	CHECK_ALLOC(a);

	a->capacity = capacity;
	a->length = 0;

	a->inner = malloc(sizeof(int) * capacity);
	CHECK_ALLOC(a->inner);

	return a;
}

void Array_grow(struct Array *array)
{
	array->inner = realloc(array->inner,
				(array->capacity + GROW_BY) * sizeof(int));
	CHECK_ALLOC(array->inner);

	array->capacity += GROW_BY;
}

void Array_append(struct Array *array, int item)
{
	if (array->length == array->capacity)
		Array_grow(array);

	array->inner[array->length] = item;
	array->length++;
}

bool Array_contains(struct Array *array, int item)
{
	for (size_t i = 0; i < array->length; i++)
		if (array->inner[i] == item)
			return true;

	return false;
}

void Array_free(struct Array *array)
{
	if (array) {
		if (array->inner)
			free(array->inner);
		free(array);
	}
}
