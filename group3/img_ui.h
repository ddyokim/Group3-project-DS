#ifndef IMG_UI_H
#define IMG_UI_H
#include "img_std.h"

#define MSG_BOX_X_OFFSET 3
#define MSG_BOX_Y_OFFSET 32
#define MENU_BOX_X_OFFSET 3
#define MENU_BOX_Y_OFFSET 26


/**************************************************
 *
 * print_menu(...
 *
 * This function calculates the pad needed at the
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
void print_title(void);

/**************************************************
 *
 * print_continue_msg(...
 *
 * This function calculates the pad needed at the
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
void print_continue_msg(void);

/**************************************************
 *
 * print_continue_msg(...
 *
 * This function calculates the pad needed at the
 * end of each row of pixels in a bmp image
 *
 * ************************************************/
char select_menu(void);

void print_main_menu(void);

void print_import_menu(void);

void print_export_menu(void);

void print_filter_menu(void);

void print_message_box(void);

void print_message_box2(void);

void print_large_box(void);

void print_menu_box(void);

void print_import_box(void);

void print_export_box(void);

void print_filter_box(void);

void print_hist_box(void);

void gotoxy(int x, int y);

#endif /* IMG_UI_H */
