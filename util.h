#pragma once

#include <stdio.h>

#define CHECK_ALLOC(ptr) \
	if ((ptr) == NULL) { \
		fprintf( \
			stderr, \
			"memory allocation failure in %s, line %d!\n", \
			__FILE__, __LINE__ \
		); \
		exit(EXIT_FAILURE); \
	}

#define CHECK_FILE(f) \
	if ((f) == NULL) { \
		fprintf( \
			stderr, \
			"failed to open file in %s, line %d!\n", \
			__FILE__, __LINE__ \
		); \
		exit(EXIT_FAILURE); \
	}
