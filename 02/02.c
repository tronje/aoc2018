#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../util.h"
#include "dynamic_array.h"

#define CHAR_OFFSET 97

static bool contains_n(int n, char *string)
{
	char counts[26] = { 0 };
	char *p = string;

	while (*p != '\0') {
		counts[(int) *p - CHAR_OFFSET] += 1;
		p++;
	}

	for (int i = 0; i < 26; i++) {
		if (counts[i] == n) {
			return true;
		}
	}

	return false;
}

static bool close_match(char *a, char *b)
{
	if (strlen(a) != strlen(b))
		return false;

	int num_differences = 0;
	for (int i = 0; i < strlen(a); i++)
		if (a[i] != b[i])
			num_differences++;

	return num_differences == 1;
}

static void common(char *a, char *b)
{
	for (int i = 0; i < strlen(a); i++)
		if (a[i] == b[i])
			printf("%c", a[i]);
	printf("\n");
}

static void part1()
{
	char c;
	unsigned counter = 0;
	unsigned two_count = 0;
	unsigned three_count = 0;

	FILE *in = fopen("input", "r");
	CHECK_FILE(in);

	char *buf = calloc(30, sizeof(char));
	CHECK_ALLOC(buf);

	while ((c = fgetc(in)) != EOF) {
		if (c == '\n') {
			if (contains_n(2, buf))
				two_count++;
			if (contains_n(3, buf))
				three_count++;

			counter = 0;
		} else {
			buf[counter] = c;
			counter ++;
		}
	}

	printf("%d\n", two_count * three_count);

	free(buf);
	fclose(in);
}

static void part2()
{
	char c;
	unsigned counter = 0;

	FILE *in = fopen("input", "r");
	CHECK_FILE(in);

	char *buf = calloc(30, sizeof(char));
	CHECK_ALLOC(buf);

	struct Array *strings = Array_new(250);

	while ((c = fgetc(in)) != EOF) {
		if (c == '\n') {
			Array_append(strings, buf);
			counter = 0;

			buf = calloc(30, sizeof(char));
			CHECK_ALLOC(buf);
		} else {
			buf[counter] = c;
			counter ++;
		}
	}

	char *a;
	char *b;

	for (size_t i = 0; i < Array_len(strings); i++) {
		a = Array_get(strings, i);

		for (size_t j = 0; j < Array_len(strings); j++) {
			b = Array_get(strings, j);
			if (close_match(a, b)) {
				printf("%s\n%s\n", a, b);
				goto done;
			}
		}
	}

done:
	common(a, b);
	Array_free(strings);
	free(buf);
	fclose(in);
}

int main(void)
{
	part1();
	part2();

	return 0;
}
