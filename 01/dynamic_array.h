#pragma once

struct Array;

struct Array *Array_new(size_t capacity);
void Array_append(struct Array *array, int item);
bool Array_contains(struct Array *array, int item);
void Array_free(struct Array *array);
