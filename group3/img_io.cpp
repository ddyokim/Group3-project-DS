#include "img_io.h"

bool is_a_bmp(unsigned char *raw_header)
{	
	if(raw_header[0] != 'B' || raw_header[1] != 'M')
	{
		printf("Error : File Must Be Of Type BMP\n");
		return false;
	}

	if(*(short*)&raw_header[BITCOUNT_OFFSET] != 24)
	{
		printf("ERROR : BITCOUNT MUST BE 24\n");
		return false;
	}
	return true;
}

int calculate_pad(int width)
{
	int pad; 

	for(pad=0;(width*3+pad)%4;++pad);
	return pad;
}

BMP_FILE_HEADER* construct_header(BMP_FILE_HEADER *header, unsigned char *raw_header) 
{
	header->width = *(int*)&raw_header[WIDTH_OFFSET];
	header->height = *(int*)&raw_header[HEIGHT_OFFSET];
	header->pad = calculate_pad(header->width);

	return header;
}

void read_raw_header(FILE *fp, unsigned char *raw_header)
{
	fread(raw_header, sizeof(unsigned char), HEADER_SIZE, fp);
	//return raw_header;
}

RGB** read_bmp_image(FILE *fp, BMP_FILE_HEADER *header)
{
	int i, j;
	int offset_cnt = 0;
	int per = 0;
	RGB **img;
	unsigned char raw_header[HEADER_SIZE];
	unsigned char *raw_data;

	read_raw_header(fp, raw_header);
	if(!is_a_bmp(raw_header))
		return NULL;
	
	construct_header(header, raw_header);
	raw_data = (unsigned char*)malloc(sizeof(unsigned char)*((header->width*3)+header->pad));
	img = (RGB**)malloc(sizeof(RGB*)*header->height);

	for(i=0;i<header->height;++i)
		img[i] = (RGB*)malloc(sizeof(RGB)*header->width);
	/* ======== end of initialization ======== */


	for(i=0;i<header->height;++i)
	{
		fread(raw_data,sizeof(unsigned char),header->width*3+header->pad,fp);
		for(j=0;j<header->width*3;j+=3)
		{
			img[header->height-i-1][j/3].b = raw_data[j];
			img[header->height-i-1][j/3].g = raw_data[j+1];
			img[header->height-i-1][j/3].r = raw_data[j+2];
		}
		if(i % (header->height/20) == 0)
		{
			printf("%c[%d;%df",0x1B,32,3+offset_cnt);
			offset_cnt += 2;
			printf("██");
			printf("%c[%d;%df",0x1B,32,50);
			printf("%3d%%", per);
			per += 5;
		}
	}

//	printf("    complete ");

	return img;
}

void write_bmp_image(RGB **img, BMP_FILE_HEADER header)
{
	int i, j;
	int offset_cnt = 0, per = 0;
	unsigned char raw_header[HEADER_SIZE];
	unsigned char *raw_data;
	FILE *fp;

	raw_data = (unsigned char*)malloc(sizeof(unsigned char)*((header.width*3)+header.pad));
	
	fp = fopen(header.input_name, "rb");
	fread(raw_header, sizeof(unsigned char), HEADER_SIZE, fp);
	fclose(fp);

	fp = fopen(header.output_name, "wb");
	fwrite(raw_header, sizeof(unsigned char), HEADER_SIZE, fp);

	for(i=0;i<header.height;++i)
	{
		memset(raw_data, 0, ((header.width*3)+header.pad)*sizeof(unsigned char));
		for(j=0;j<header.width*3;j+=3)
		{
			raw_data[j]   = img[header.height-i-1][j/3].b;		
			raw_data[j+1] = img[header.height-i-1][j/3].g;
			raw_data[j+2] = img[header.height-i-1][j/3].r;
		}
		fwrite(raw_data, sizeof(unsigned char), header.width*3+header.pad, fp);	
		if(i % (header.height/20) == 0)
		{
			printf("%c[%d;%df",0x1B,32,3+offset_cnt);
			offset_cnt += 2;
			printf("██");
			printf("%c[%d;%df",0x1B,32,50);
			printf("%3d%%", per);
			per += 5;
		}
	}
	
	printf("    complete ");

	free(raw_data);
	fclose(fp);
}

RGB** free_image(RGB** img, BMP_FILE_HEADER header)
{
	int i;

	if(!img)
	{
		for(i=0;i<header.height;++i)
			free(img[i]);
		free(img);
	}
	return  NULL;
}

