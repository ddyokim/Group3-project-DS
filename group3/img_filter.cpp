#include "img_filter.h"
#include "img_tree.h"

/*
float motion_blur1[3][3] =
{
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
};

float motion_blur2[3][3] =
{
	{0.0, 0.0, 1.0},
	{0.0, 1.0, 0.0},
	{1.0, 0.0, 0.0},
};
*/

float quick_mask[3][3] =
{
	{-1.0, 0.0, -1.0},
	{ 0.0, 4.0, 0.0},
	{-1.0, 0.0, -1.0},
};

float identity_mask[3][3] =
{
	{-2.0, -1.0, 0.0},
	{-1.0, 1.0, 1.0},
	{0.0, 1.0, 2.0},
};

float blur_mask[3][3] =
{
	{0.11, 0.11, 0.11},
	{0.11, 0.11, 0.11},
	{0.11, 0.11, 0.11},
};



float** setup_filter(enum filter_type type)
{
	float **filter = (float**)malloc(sizeof(float*)*3);
	int i, j;

	for(i=0;i<3;++i)
		filter[i] = (float*)malloc(sizeof(float)*3);

	switch(type)
	{
		case IDENTITY :	for(i=0;i<3;++i){for(j=0;j<3;++j) filter[i][j] = identity_mask[i][j];}	break;
		case BLUR	  :	for(i=0;i<3;++i){for(j=0;j<3;++j) filter[i][j] = blur_mask[i][j];}		break;
		case QUICK	  : for(i=0;i<3;++i){for(j=0;j<3;++j) filter[i][j] = quick_mask[i][j];}		break;
	}
	
	return filter;
}

RGB** filter_image(RGB** img, BMP_FILE_HEADER header, enum filter_type type)
{
	int i, j,  r, g, b;
	int offset_cnt = 0, per = 0;
	float **filter;

	filter = setup_filter(type);

	for(i=0;i<header.height;++i)
	{
		for(j=0;j<header.width;++j)
		{
			r = 0;
			g = 0;
			b = 0;
			for(int m=-1;m<2;++m)
				for(int n=-1;n<2;++n)
					if((i+m)>=0&&(i+m)<header.height&&(j+n)>=0&&(j+n)<header.width)
					{
						r+=img[i+m][j+n].r * filter[n+1][m+1];
						g+=img[i+m][j+n].g * filter[n+1][m+1];
						b+=img[i+m][j+n].b * filter[n+1][m+1];
					}
			if(r > 255) r = 255; else if(r < 0) r = 0;
			if(g > 255) g = 255; else if(g < 0) g = 0;
			if(b > 255) b = 255; else if(b < 0) b = 0;
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

	return img;
}

RGB** invert_filter(RGB** img, BMP_FILE_HEADER header)
{
	int i, j;
	int offset_cnt = 0, per = 0;

	for(i=0;i<header.height;++i)
	{
		for(j=0;j<header.width;++j)
		{
			img[i][j].r = 255 - img[i][j].r;
			img[i][j].g = 255 - img[i][j].g;
			img[i][j].b = 255 - img[i][j].b;
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

	return img;
}

void intensify_element(RGB **img, BMP_FILE_HEADER header, char mode, float degree)
{
	int i, j, r, g, b;
	int offset_cnt = 0, per = 0;
	
	for(i=0;i<header.height;++i)
	{
		for(j=0;j<header.width;++j)
		{
			r = 0;
			g = 0;
			b = 0;
			if(mode == 'R')
			{
				r = img[i][j].r*degree;
				if(r>255) r = 255;
				img[i][j].r = r;
			}
			else if(mode == 'G')
			{
				g = img[i][j].g*degree;
				if(g>255) g = 255;
				img[i][j].g = g;
			}
			else if(mode == 'B')
			{
				b = img[i][j].b*degree;
				if(b>255) b = 255;
				img[i][j].b = b;
			}
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

void apply_filter(RGB** img, BMP_FILE_HEADER header, char mode, int flag, node img_tree)
{
	int i;
	float **filter = (float**)malloc(3*sizeof(float*));;

	for(i=0;i<3;++i)
		filter[i] = (float*)malloc(3*sizeof(float));

	switch(mode)
	{
		case 'I': 
			printf("Applying Identity Filter ");
			filter = setup_filter(IDENTITY);
			if(flag == 1)
				masktree(filter, img, img_tree);
			else
			{
				img = filter_image(img, header, IDENTITY);
				printf("    complete ");
			}	break;
		case 'B':
			filter = setup_filter(BLUR);
			printf("How Blurry ? [1 ~ 10] ");
			scanf("%d", &i);
			while(getchar()!='\n'); 
			while(i--)
			{
				if(flag == 1)
					masktree(filter, img, img_tree);
				else
					img = filter_image(img, header, BLUR);
			}
			if(flag == 0)
				printf("    complete ");	break;
		case 'V': 
			printf("Applying Invertion Filter ");
			img = invert_filter(img, header);
			printf("    complete "); break;
	}
}

void masktree(float** mask, RGB** img, node root)
{
    const int masksize = 3;
    int r, c, i, j, m, n;
    bool flag = false;
    node tree;
    RGB result;
    int *jumpsize = (int*)malloc(sizeof(int)*root.w);
    int *jumpcnt = (int*)malloc(sizeof(int)*root.w);
    RGB *jumpresult = (RGB*)malloc(sizeof(RGB)*root.w);
    
    
    for(r=0;r<root.h;++r)
    {
        for(c=0;c<root.w;++c)
        {
            if(jumpcnt[c]>0)
            {
                for(i=c;i<jumpsize[c]+c;++i)
                    img[r][i] = jumpresult[c];
                jumpcnt[c]--;
                c+=jumpsize[c]-1;
                continue;
            }
            
            tree = root;
            result.r = result.g = result.b = 0;
            flag = false;           // if false == not good else == good
            while(1)
            {
                if(tree.w-tree.c > masksize && tree.h-tree.r > masksize)
                {
                    if(tree.stat == NO_NODE) break;
                    if(r<tree.h/2+tree.r)
                    {
                        if(c<tree.w/2+tree.c && tree.c < c) tree = tree.u.child[0];
                        else tree = tree.u.child[1];
                    }
                    else
                    {
                        if(c<tree.w/2+tree.c && tree.c < c) tree = tree.u.child[2];
                        else tree = tree.u.child[3];
                    }
                }
                else
                {
                    flag=true;
                    break;
                }
            }
            
            for(i=-masksize/2, m=0;i<(masksize/2+masksize%2);++i, ++m)
                for(j=-masksize/2, n=0;j<(masksize/2+masksize%2);++j, ++n)
                    if((i+r)>=0&&(i+r)<root.h && (j+c)>=0&&(j+c)<root.w)
                    {
                        result.r += (int)img[i+r][j+c].r*mask[m][n];
                        result.g += (int)img[i+r][j+c].g*mask[m][n];
                        result.b += (int)img[i+r][j+c].b*mask[m][n];
                    }
            
            if(flag == false)
            {
                jumpcnt[c] = tree.h-1;
                jumpsize[c] = tree.w;
                jumpresult[c] = result;
                for(i=c;i<jumpsize[c]+c;++i)
                    img[r][i] = jumpresult[c];
                c+=jumpsize[c]-1;
            }
            else img[r][c] = result;
        }
    }
    free(jumpsize);
    free(jumpresult);
    free(jumpcnt);
}

