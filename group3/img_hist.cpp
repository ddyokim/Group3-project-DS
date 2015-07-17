#include "img_std.h"

void show_hist(RGB **img, BMP_FILE_HEADER header)
{
	int hr[256] = {0,};
	int hb[256] = {0,};
	int hg[256] = {0,};
	
	int mod_hr[9] = {0,};
	int mod_hb[9] = {0,};
	int mod_hg[9] = {0,};

	float r_total = 0;
	float b_total = 0;
	float g_total = 0;

	float rgb_total = 0;

	int i, j;

	for(i=0;i<header.height;++i)
		for(j=0;j<header.width;++j)
		{
			hr[img[i][j].r]++;
			hb[img[i][j].b]++;
			hg[img[i][j].g]++;
		}
	
	for(i=1;i<256;++i)
	{
		mod_hr[i/32] += hr[i]; r_total += hr[i];
		mod_hb[i/32] += hb[i]; b_total += hb[i];
		mod_hg[i/32] += hg[i]; g_total += hg[i];	
	}

	for(i=0;i<9;++i)
	{
		rgb_total += mod_hr[i];
		rgb_total += mod_hg[i];
		rgb_total += mod_hb[i];
	}

	/* ===== calculating histogram ===== */

	for(i=0;i<8;++i)
	{
		printf("%c[%d;%df",0x1B,32+i,4);
		printf("║ ");
		for(j=0;j<(int)((float)(mod_hr[i])/r_total*100)/5 && j<8;++j)
			printf("██");	
		printf("%c[%d;%df",0x1B,32+i,24);
		printf("%0.1lf%%", r_total==0?0:(float)mod_hr[i]/r_total*100);
	}
	for(i=0;i<8;++i)
	{
		printf("%c[%d;%df",0x1B,32+i,29);
		printf("║ ");
		for(j=0;j<(int)((float)(mod_hg[i])/g_total*100)/5 && j<8;++j)
			printf("██");
		printf("%c[%d;%df",0x1B,32+i,49);	
		printf("%0.1lf%%", g_total==0?0:(float)mod_hg[i]/g_total*100);
	}
	for(i=0;i<8;++i)
	{
		printf("%c[%d;%df",0x1B,32+i,54);
		printf("║ ");
		for(j=0;j<(int)((float)(mod_hb[i])/b_total*100)/5 && j<8;++j)
			printf("██");
		printf("%c[%d;%df",0x1B,32+i,74);	
		printf("%0.1lf%%", b_total==0?0:(float)mod_hb[i]/b_total*100);
	}

	printf("%c[%d;%df",0x1B,41,4);
	printf("relative ratio of each color : red=%.2lf%%     green=%.2lf%%     blue=%.2lf%% \n", 
			r_total/rgb_total*100, g_total/rgb_total*100, b_total/rgb_total*100);
}



void hist_equal(RGB **img, BMP_FILE_HEADER header) 
{
	// histogram equalization
	int hr[256] = {0,};
	int hb[256] = {0,};
	int hg[256] = {0,};
	int cr[256] = {0,};
	int cb[256] = {0,};
	int cg[256] = {0,};
	int i,j;
	int offset_cnt = 0, per = 0;

	printf("%c[%d;%df",0x1B,26,3);
	printf("Equalizing Histogram ");

	for(i=0;i<header.height;++i)
		for(j=0;j<header.width;++j)
		{
			hr[img[i][j].r]++;
			hb[img[i][j].b]++;
			hg[img[i][j].g]++;
		}

	// smooth histogram (optional)
	hr[0] = (hr[0]+hr[1])/2;
	hr[255] = (hr[254]+hr[255])/2;
	for(i=1;i<255;++i) hr[i] = (hr[i-1]+hr[i]+hr[i+1])/3;
	hg[0] = (hg[0]+hg[1])/2;
	hg[255] = (hg[254]+hg[255])/2;
	for(i=1;i<255;++i) hg[i] = (hg[i-1]+hg[i]+hg[i+1])/3;
	hb[0] = (hb[0]+hb[1])/2;
	hb[255] = (hb[254]+hb[255])/2;
	for(i=1;i<255;++i) hb[i] = (hb[i-1]+hb[i]+hb[i+1])/3;

	cr[0] = hr[0];
	cb[0] = hb[0];
	cg[0] = hg[0];
	for(i=1;i<256;++i)
	{
		cr[i] += cr[i-1]+hr[i];
		cg[i] += cg[i-1]+hg[i];
		cb[i] += cb[i-1]+hb[i];
	}
	for(i=0;i<header.height;++i)
	{
		for(j=0;j<header.width;++j)
		{
			int r = cr[img[i][j].r]*256/(header.width*header.height);
			int g = cg[img[i][j].g]*256/(header.width*header.height);
			int b = cb[img[i][j].b]*256/(header.width*header.height);
			if(r>255) r = 255;
			if(g>255) g = 255;
			if(b>255) b = 255;
			img[i][j].r = r;
			img[i][j].g = g;
			img[i][j].b = b;
		}
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
}


