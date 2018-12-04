#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../util.h"

#define INPUT_LENGTH 1233

struct Rectangle {
	int id;
	int margin_left;
	int margin_top;
	int width;
	int height;
};

static void clear_buf(char *buf, size_t size)
{
	for (size_t s = 0; s < size; s++)
		buf[s] = 0;
}

/* parse a claim into a rectangle
 *
 * A claim looks like this:
 *
 *  #123 @ 4,5: 6x7
 *  |      |    |
 *  id     |    width and height
 *         |
 *         margins left and right
 */
static struct Rectangle parse_claim(char *claim)
{
	struct Rectangle r;

	int idx;
	char c;
	char *buf = calloc(8, sizeof(char));
	CHECK_ALLOC(buf);

	/* seek beginning of id */
	while ((c = *(claim++)) != '#');

	/* read and parse id */
	idx = 0;
	while ((c = *claim) != ' ') {
		buf[idx] = c;
		idx++;
		claim++;
	}

	r.id = atoi(buf);
	clear_buf(buf, 8);

	/* seek to right after '@' marker */
	while ((c = *claim++) != '@');

	/* read and parse margins */
	idx = 0;
	while ((c = *claim) != ',') {
		buf[idx] = c;
		idx++;
		claim++;
	}

	r.margin_left = atoi(buf);
	clear_buf(buf, 8);

	claim++;

	idx = 0;
	while ((c = *claim) != ':') {
		buf[idx] = c;
		idx++;
		claim++;
	}

	r.margin_top = atoi(buf);
	clear_buf(buf, 8);

	claim++;

	/* finally, read and parse width and height */
	idx = 0;
	while ((c = *claim) != 'x') {
		buf[idx] = c;
		idx++;
		claim++;
	}

	r.width = atoi(buf);
	clear_buf(buf, 8);

	claim++;

	idx = 0;
	while ((c = *claim) != '\0') {
		buf[idx] = c;
		idx++;
		claim++;
	}

	r.height = atoi(buf);
	free(buf);

	return r;
}

static struct Rectangle *read_rectangles()
{
	struct Rectangle *rects =
		malloc(INPUT_LENGTH * sizeof(struct Rectangle));
	CHECK_ALLOC(rects);

	FILE *in = fopen("input", "r");
	CHECK_FILE(in);

	int idx = 0;
	size_t len = 0;
	char *line = NULL;
	while (getline(&line, &len, in) != -1) {
		rects[idx] = parse_claim(line);
		idx++;
	}

	if (idx > 0)
		free(line);
	fclose(in);

	return rects;
}

static void part1and2(struct Rectangle *rectangles)
{
	/* calculate width and height of master rectangle */
	unsigned width = 0;
	unsigned height = 0;
	for (int i = 0; i < INPUT_LENGTH; i++) {
		struct Rectangle temp = rectangles[i];
		unsigned temp_width = temp.margin_left + temp.width;
		unsigned temp_height = temp.margin_top + temp.height;

		if (temp_width > width)
			width = temp_width;

		if (temp_height > height)
			height = temp_height;
	}

	/* create a master rectangle to keep track of which square inches
	   are part of how many rectangles */
	int **master_rectangle = calloc(width, sizeof(int*));
	CHECK_ALLOC(master_rectangle);

	for (int i = 0; i < width; i++) {
		master_rectangle[i] = calloc(height, sizeof(int));
		CHECK_ALLOC(master_rectangle[i]);
	}

	/* for each rectangle, increment the value of each contained square
	   inch in the master rectangle */
	for (int i = 0; i < INPUT_LENGTH; i++) {
		struct Rectangle r = rectangles[i];
		int left = r.margin_left;
		int top = r.margin_top;
		int width = r.width;
		int height = r.height;

		for (int x = left; x < left + width; x++) {
			for (int y = top; y < top + height; y++) {
				master_rectangle[x][y]++;
			}
		}
	}

	/* get the count of square inches that are part of at least 2
	   rectangles (i.e. their value in the master rectangle is >= 2) */
	unsigned count = 0;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (master_rectangle[x][y] >= 2)
				count++;

	printf("%u\n", count);

	/* part 2 */
	for (int i = 0; i < INPUT_LENGTH; i++) {
		struct Rectangle r = rectangles[i];
		int left = r.margin_left;
		int top = r.margin_top;
		int width = r.width;
		int height = r.height;

		bool no_overlaps = true;

		for (int x = left; x < left + width; x++) {
			if (!no_overlaps)
				break;

			for (int y = top; y < top + height; y++) {
				if (master_rectangle[x][y] > 1) {
					no_overlaps = false;
					break;
				}
			}
		}

		if (no_overlaps)
			printf("no overlaps: #%d\n", r.id);
	}

	for (int x = 0; x < width; x++)
		free(master_rectangle[x]);
	free(master_rectangle);
}

int main(void)
{
	struct Rectangle *rectangles = read_rectangles();

	part1and2(rectangles);

	free(rectangles);

	return 0;
}
