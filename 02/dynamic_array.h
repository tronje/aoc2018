#pragma once

struct Array;

struct Array *Array_new(size_t capacity);
size_t Array_len(struct Array *array);
void Array_append(struct Array *array, char *item);
char *Array_get(struct Array *array, size_t idx);
bool Array_contains(struct Array *array, char *item);
void Array_free(struct Array *array);
