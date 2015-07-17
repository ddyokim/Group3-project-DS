#ifndef FILTER_H
#define FILTER_H
#include "img_std.h"

enum filter_type {IDENTITY, BLUR, QUICK};

/***************************
*
* Directions for the masks
* 3 2 1
* 4 x 0
* 5 6 7
*
****************************/

/*******************************************
*
* setup_filter(...
*
* This function filters an image by using
* a single 3x3 mask.
*
*******************************************/
float** setup_filter(enum filter_type type);


/*******************************************
*
* filter_image(...
*
* This function filters an image by using
* a single 3x3 mask.
*
*******************************************/
void apply_filter(RGB** img, BMP_FILE_HEADER header, char mode, int flag, node img_tree);


RGB** invert_filter(RGB** img, BMP_FILE_HEADER header);

void intensify_element(RGB **img, BMP_FILE_HEADER header, char mode, float degree);

void masktree(float** mask, RGB** img, node root);

#endif /* FILTER_H */
