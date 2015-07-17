#ifndef IMG_IO_H
#define IMG_IO_H

#include "img_std.h"
#define HEADER_SIZE		54
#define WIDTH_OFFSET	18 
#define HEIGHT_OFFSET	22
#define BITCOUNT_OFFSET 28	

/**************************************************
 *
 * is_a_bmp(...
 *
 * This function looks at a file to see if it
 * is a bmp file. First look ar the file 
 * extension. Next look at the first two 
 * characters of the header to check if it reads
 * "BM"
 *
 * ************************************************/
bool is_a_bmp(unsigned char *raw_header);

/**************************************************
 *
 * calculate_pad(...
 *
 * This function calculates the pad needed at the 
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
int calculate_pad(int width);

/**************************************************
 *
 * construct_header(...
 *
 * This function extracts basic information of the
 * given BMP image from the raw header string
 *
 * ************************************************/
BMP_FILE_HEADER* construct_header(BMP_FILE_HEADER *header, unsigned char *raw_header);

/**************************************************
 *
 * read_raw_header(...
 *
 * This function calculates the pad needed at the 
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
void read_raw_header(FILE *fp, unsigned char *raw_header);

/**************************************************
 *
 * read_bmp_image(...
 *
 * This function calculates the pad needed at the 
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
RGB** read_bmp_image(FILE *fp, BMP_FILE_HEADER *header);

/**************************************************
 *
 * write_bmp_image(...
 *
 * This function calculates the pad needed at the 
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
void write_bmp_image(RGB **img, BMP_FILE_HEADER header);

/**************************************************
 *
 * free_image(...
 *
 * This function calculates the pad needed at the 
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
RGB** free_image(RGB** img, BMP_FILE_HEADER header);

#endif /* IMGIO_H */
