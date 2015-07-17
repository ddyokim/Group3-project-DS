#include "img_ui.h"

void print_title(void)
{
	system("clear");
	puts("██╗███╗   ███╗ █████╗  ██████╗ ███████╗                                        ");
	puts("██║████╗ ████║██╔══██╗██╔════╝ ██╔════╝                                        ");
	puts("██║██╔████╔██║███████║██║  ███╗█████╗                                          ");
	puts("██║██║╚██╔╝██║██╔══██║██║   ██║██╔══╝                                          ");
	puts("██║██║ ╚═╝ ██║██║  ██║╚██████╔╝███████╗                                        ");
	puts("╚═╝╚═╝     ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝                                        ");
	puts("                                                                               ");
	puts("██████╗ ██████╗  ██████╗  ██████╗███████╗███████╗███████╗██╗███╗   ██╗ ██████╗ ");
	puts("██╔══██╗██╔══██╗██╔═══██╗██╔════╝██╔════╝██╔════╝██╔════╝██║████╗  ██║██╔════╝ ");
	puts("██████╔╝██████╔╝██║   ██║██║     █████╗  ███████╗███████╗██║██╔██╗ ██║██║  ███╗");
	puts("██╔═══╝ ██╔══██╗██║   ██║██║     ██╔══╝  ╚════██║╚════██║██║██║╚██╗██║██║   ██║");
	puts("██║     ██║  ██║╚██████╔╝╚██████╗███████╗███████║███████║██║██║ ╚████║╚██████╔╝");
	puts("╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝╚══════╝╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝ ");
	puts("                                                                               ");
	puts("██╗███╗   ██╗     ██████╗                                                      ");
	puts("██║████╗  ██║    ██╔════╝                                                      ");
	puts("██║██╔██╗ ██║    ██║                                                           ");
	puts("██║██║╚██╗██║    ██║                                                           ");
	puts("██║██║ ╚████║    ╚██████╗                                                      ");
	puts("╚═╝╚═╝  ╚═══╝     ╚═════╝                                                    \n");

	puts("═══════════════════════════════════Developed by K.H. Choi, D.H. Kim, Y.J. Chung"); 
}

void print_continue_msg(void)
{
	printf("Press Any Key to Continue ... ");
	getchar();
} 

void print_main_menu(void)
{
	print_title();
	print_menu_box();
	print_message_box();
	gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
	printf("[I]mport Image [E]xport Image [A]pply Filters [H]istogram [Q]uit");
	gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
	printf("[I, E, A, H, Q] ? ");
}

void print_import_menu(void)
{
	print_title();
	print_import_box();
	print_message_box();
	gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
	printf("Input File Name : " );
}

void print_export_menu(void)
{
	print_title();
	print_export_box();
	print_message_box();
	gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
	printf("Output File Name : ");
}

void print_filter_menu(void)
{
	print_title();
	print_filter_box();
	print_message_box();
	gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
	printf("[I]Identity Filter [B]lur Filter [V]Invertion Filter [T]Intensity Filter ");
	gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
	printf("[I, B, V, T, R] ? ");
}

void print_import_box(void)
{
	printf("\n");
	puts("╔════════════Import Image══════════════════════════════════════════════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_export_box(void)
{
	printf("\n");
	puts("╔════════════Export Image══════════════════════════════════════════════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_filter_box(void)
{
	printf("\n");
	puts("╔════════════Select Filter═════════════════════════════════════════════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_hist_box(void)
{
	printf("\n");
	puts("╔════════════Histogram═════════════════════════════════════════════════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_menu_box(void)
{
	printf("\n");
	puts("╔════════════Select Menu═══════════════════════════════════════════════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_message_box(void)
{
	puts("╔════════════Message Box═══════════════════════════[R]eturn to Menu════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_message_box2(void)
{
	puts("╔════════════Message Box═══════════════════════════════════════════════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}

void print_large_box(void)
{
	puts("╔════════════R, G, B pixel values [0 ~ 255]════════[R]eturn to Menu════════════╗");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("║                                                                              ║");
	puts("╚══════════════════════════════════════════════════════════════════════════════╝");
	printf("\n");
}


void gotoxy(int x, int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}
 
