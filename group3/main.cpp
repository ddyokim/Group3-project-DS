#include "img_io.h"
#include "img_ui.h"
#include "img_hist.h"
#include "img_tree.h"
#include "img_filter.h"

int read_command(char *cin);
void get_mode(char *cin);
void case_convert(char *cin);
char* read_file_name(void);
void select_filter(char *cin);
void select_hist(char *cin);
void select_rgb(char *cin);

int main(void)
{
	BMP_FILE_HEADER header = {0,0,0};
	RGB **img_arr = NULL;
	FILE *img_ori;
	char mode, cin;
	int exit_flag = 0;
	float degree;
	
	node img_tree;
	int flag = 0; /* flag == 0 use array	flag == 1 use tree */

	float r_weight, g_weight, b_weight;

	do
	{
		print_main_menu();
		get_mode(&mode);

		switch(mode)
		{
			case 'I':
				if(img_ori)
				{	
					print_import_menu();
					gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
					printf("Image Already exists ");
					gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
					printf("Current File Will be Deleted. Overwrite  (y / n) ? ");
					read_command(&cin);
					if(cin == 'R')
						continue;
					if(cin == 'Y')
					{
						flag = 0;
						fclose(img_ori);
						free(header.input_name);						
						img_arr = free_image(img_arr, header);
						img_ori = NULL;
						img_arr = NULL;
						header.input_name = NULL;
						free_tree(img_tree);	
					}
					else
						break;
				}
				print_import_menu();
				header.input_name = read_file_name();
				gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
				if(!header.input_name)
					printf("Error : File Must Be of Extension .bmp ");
				else
				{
					img_ori = fopen(header.input_name, "rb");
					if(!img_ori)
						printf("Error : File Does Not Exist ");
					else
					{
						img_arr = read_bmp_image(img_ori, &header);
						if(img_arr == NULL)
						{
							printf("Error : File is Not in bmp Format ");
							continue;
						}
						img_tree = make_tree(img_arr, 0, 0, header.height, header.width);
						if(ds_cmp(img_tree, 1) > 0)
						{
							flag = 1;
							printf("    use tree ");
						}
						else
							printf("    use array");
					}	
				} 	
				break;
			case 'E':
				print_export_menu();
				if(!img_ori)
				{
					gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
					printf("Error : No Image to Export ");
					gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
					printf("Import Image First ");
					break;
				}
				header.output_name = read_file_name();
				if(!header.output_name)
				{
					gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
					printf("Error : File Must Be of Extension .bmp ");
				}
				else
				{
					if(flag == 1)
						tree_to_array(img_arr, img_tree);
					write_bmp_image(img_arr, header);
					free(header.output_name);
					header.output_name = NULL;
				}
				break;
			case 'A':
				if(!img_ori)
				{	
					print_title();
					print_filter_box();
					print_message_box();
					gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
					printf("Error : No Image to Apply Filter ");
					gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
					printf("Import Image First ");
					break;
				}
				else
				{
					print_filter_menu();
					select_filter(&cin);
					if(cin == 'R')
						continue;
					print_title();
					print_filter_box();
					if(cin == 'T')
					{
						if(flag == 0)
						{
						print_message_box2();
						gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
						printf("[R]ed, [G]reen, [B]lue ");
						gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
						printf("[R, G, B] ? ");
						select_rgb(&cin);
						gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
						printf("                                                                            ");
						gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
						printf("Choose Intensity Between [0 ~ 10] ? ");
						scanf("%f", &degree);
						while(getchar()!='\n');
						intensify_element(img_arr, header, cin, degree);
						}
						else
						{
							print_message_box2();
							gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
							printf("Input Ratio Values for R, G, B ");
							scanf("%f %f %f", &r_weight, &g_weight, &b_weight);
							while(getchar()!='\n');
							gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
							tree_progress(true,header.width*header.height);
							img_tree = rgb_ratio(img_tree, r_weight, g_weight, b_weight);
							printf("    %%100    complete ");
						}
					}
					else
					{
						print_message_box();
						gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
						if(flag == 1)
						{
							tree_to_array(img_arr, img_tree);
							free_tree(img_tree);
						}
						apply_filter(img_arr, header, cin, flag, img_tree);
						if(flag == 1)
							make_tree(img_arr, 0, 0, header.height, header.width);
					}
				}
				break;
			case 'H':
				if(!img_ori)
				{	
					print_title();
					print_filter_box();
					print_message_box();
					gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
					printf("Error : No Image to Make Histogram ");
					gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
					printf("Import Image First ");
					break;
				}
				else
				{
					print_title();
					print_hist_box();
					print_message_box();
					gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
					printf("[S]how Histogram [H]istogram Equalization ");
					gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
					printf("[S, H, R] ? ");
					select_hist(&cin);
					if(cin == 'R')
						continue;
					print_title();
					print_hist_box();
					if(cin == 'S')
					{
						print_large_box();
						gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
						printf("from the left are histograms of each R, G, B in grayscale from [0 ~ 255] ");
						if(flag == 1)
							tree_to_array(img_arr, img_tree);	
						show_hist(img_arr, header);
					}
					else if(cin == 'H')
					{
						print_message_box();
						if(flag == 1)
						{
							gotoxy(MENU_BOX_X_OFFSET, MENU_BOX_Y_OFFSET);
							printf("Equalizing Histogram ");
							gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
							tree_progress(true,header.width*header.height);
							img_tree = hist_eq(img_tree);
							printf("    %%100    complete ");
						}
						else
							hist_equal(img_arr, header);
					}
				}
				break;
			case 'Q': exit_flag = 1;	break;
			default : continue;
		}
		if(exit_flag == 0)
			while(getchar()!='\n');
	} while(exit_flag == 0);

	if(img_arr)
		free_image(img_arr, header);
	if(header.input_name)
		free(header.input_name);
	if(header.output_name)
		free(header.output_name);
	if(img_ori)
		fclose(img_ori);

	return 0;
}

char* read_file_name(void)
{
	int cin, idx = 0;
	char *file_extension;
	char *file_name;

	file_name = (char*)malloc(sizeof(char));
	do
	{
		cin = getchar();
		file_name = (char*)realloc(file_name, (idx+1) * sizeof(char));
		if(cin == '\n')
			cin = '\0';
		file_name[idx++] = cin;
	} while(cin != '\0');


	file_extension = strstr(file_name, ".bmp");
	if(file_extension == NULL)
	{
		free(file_name);
		return NULL;
	}

	return file_name;
}

void select_rgb(char *cin)
{
	int flag = read_command(cin)>1 ? 1:0;

	if (*cin!='R'&&*cin!='G'&&*cin!='B')
		flag = 1;

	if(flag)
	{
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);	
		printf("Invalid Input. Please Type Again. ");
		while(getchar() != '\n');
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("[R, G, B] ? ");
		select_rgb(cin);
	}
}

void select_hist(char *cin)
{
	int flag = read_command(cin)>1 ? 1:0;

//	case_convert(cin);

	if (*cin!='S'&&*cin!='H'&&*cin!='R')
		flag = 1;

	if(flag)
	{
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);	
		printf("Invalid Input. Please Type Again. ");
		while(getchar() != '\n');
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("[S, H, R] ? ");
		select_hist(cin);
	}
}

void select_filter(char *cin)
{
	int flag = read_command(cin)>1 ? 1:0;

//	case_convert(cin);

	if (*cin!='I'&&*cin!='B'&&*cin!='V'&&*cin!='T'&&*cin!='R')
		flag = 1;

	if(flag)
	{
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);	
		printf("Invalid Input. Please Type Again. ");
		while(getchar() != '\n');
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("[I, B, V, T, R] ? ");
		select_filter(cin);
	}
}

void get_mode(char *cin)
{
	int flag = read_command(cin)>1 ? 1:0;

//	case_convert(cin);

	if (*cin!='I'&&*cin!='E'&&*cin!='A'&&*cin!='H'&&*cin!='Q')
		flag = 1;

	if(flag)
	{
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);	
		printf("Invalid Input. Please Type Again. ");
		while(getchar() != '\n');
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("                                                                            ");
		gotoxy(MSG_BOX_X_OFFSET, MSG_BOX_Y_OFFSET);
		printf("[I, E, A, H, Q] ? ");
		get_mode(cin);
	}
}

int read_command(char *cin)
{
	int idx = 0;
	char *command;

	command = (char*)malloc(sizeof(char));
	do
	{
		*cin = getchar();
		if(*cin == ' ')
			continue;
		command = (char*)realloc(command, (idx+1) * sizeof(char));
		if(*cin == '\n')
			*cin = '\0';
		command[idx++] = *cin;	
	} while(*cin != '\0');

	idx = strlen(command);

	*cin = command[0];
	case_convert(cin);

	free(command);

	return idx;
}

void case_convert(char *cin)
{
	if(*cin >= 'a' && *cin <= 'z')
		*cin += 'A'-'a';
}



