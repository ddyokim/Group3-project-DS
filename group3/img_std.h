#ifndef IMG_STD_H
#define IMG_STD_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>

using namespace std;

typedef struct
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGB;

typedef struct
{
	int width;
	int height;
	int pad;
	char *input_name;
	char *output_name;
} BMP_FILE_HEADER;

typedef enum {NO_NODE, LR_NODE, UD_NODE, ALL_NODE} node_status;

typedef struct _node
{
	node_status stat;
	int r, c;
	int h, w;
	union _u
	{
		struct _node* child;
		RGB color;
	} u;
} node;

#endif /* IMG_STD_H */
