#ifndef IMG_TREE_H
#define IMG_TREE_H

#include "img_std.h"

/*
typedef enum { NO_NODE, LR_NODE, UD_NODE, ALL_NODE } node_status;

typedef struct _node
{
	node_status stat;
	int r,c;
	int h,w;
	union _u
	{
		struct _node* child;
		RGB color;
	} u;
} node;
*/
int ds_cmp(node tree, int depth);

int tree_progress(bool init, int pixels);

void free_tree(node tree);

void tree_to_array(RGB** img, node tree);

node make_tree(RGB** img, int r, int c, int h, int w);

node rgb_ratio(node tree, float r_weight, float g_weight, float b_weight);

node rgb_relation(node tree, int r_relation[256], int g_relation[256], int b_relation[256]);

void make_hist(node tree, int hr[256], int hg[256], int hb[256]);

node hist_eq(node tree);

#endif 
