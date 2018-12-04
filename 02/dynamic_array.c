#include <stdlib.h>
#include <stdbool.h>

#include "dynamic_array.h"
#include "../util.h"

#define GROW_BY 500

struct Array {
	size_t capacity;
	size_t length;
	char **inner;
};

struct Array *Array_new(size_t capacity)
{
	struct Array *a = malloc(sizeof(struct Array));
	CHECK_ALLOC(a);

	a->capacity = capacity;
	a->length = 0;

	a->inner = malloc(sizeof(char *) * capacity);
	CHECK_ALLOC(a->inner);

	return a;
}

size_t Array_len(struct Array *array)
{
	return array->length;
}

void Array_grow(struct Array *array)
{
	array->inner = realloc(array->inner,
				(array->capacity + GROW_BY) * sizeof(int));
	CHECK_ALLOC(array->inner);

	array->capacity += GROW_BY;
}

void Array_append(struct Array *array, char *item)
{
	if (array->length == array->capacity)
		Array_grow(array);

	array->inner[array->length] = item;
	array->length++;
}

char *Array_get(struct Array *array, size_t idx)
{
	return array->inner[idx];
}

bool Array_contains(struct Array *array, char *item)
{
	for (size_t i = 0; i < array->length; i++)
		if (array->inner[i] == item)
			return true;

	return false;
}

void Array_free(struct Array *array)
{
	if (array) {
		if (array->inner) {
			for (int i = 0; i < array->length; i++)
				free(array->inner[i]);
			free(array->inner);
		}
		free(array);
	}
}
