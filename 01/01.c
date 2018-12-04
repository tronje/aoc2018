#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "dynamic_array.h"
#include "../util.h"

static int parse(char *input, unsigned short len)
{
	if (len <= 0)
		return 0;

	bool sign;

	if (input[0] == '+')
		sign = true;
	else if (input[0] == '-')
		sign = false;
	else
		return 0;

	int result = atoi(input + 1);

	if (sign)
		return result;
	else
		return -result;
}

static void part1()
{
	char c;
	bool sign;
	unsigned short counter = 0;
	int sum = 0;

	FILE *in = fopen("input", "r");
	CHECK_FILE(in);

	char *buf = calloc(16, sizeof(char));
	CHECK_ALLOC(buf);

	while ((c = fgetc(in)) != EOF) {
		if (c == '\n') {
			sum += parse(buf, counter);
			for (int i = 0; i < counter; i++)
				buf[i] = '\0';
			counter = 0;
		} else {
			buf[counter] = c;
			counter ++;
		}
	}

	printf("%d\n", sum);

	free(buf);
	fclose(in);
}

static void part2()
{
	char c;
	bool sign;
	bool solved = false;
	unsigned short counter = 0;
	int sum = 0;
	struct Array *sums = Array_new(1000);

	FILE *in = fopen("input", "r");
	CHECK_FILE(in);

	char *buf = calloc(16, sizeof(char));
	CHECK_ALLOC(buf);

	while (!solved) {
		while ((c = fgetc(in)) != EOF) {
			if (c == '\n') {
				sum += parse(buf, counter);

				if (Array_contains(sums, sum)) {
					solved = true;
					break;
				} else {
					Array_append(sums, sum);
				}

				for (int i = 0; i < counter; i++)
					buf[i] = '\0';
				counter = 0;
			} else {
				buf[counter] = c;
				counter ++;
			}
		}

		rewind(in);
	}

	printf("%d\n", sum);

	Array_free(sums);
	free(buf);
	fclose(in);
}

int main(void)
{
	part1();
	part2();

	return 0;
}
