#include <stdlib.h>
#include <stdio.h> 
#include "mfunc.h"
#include <string.h>

extern int row, col;

void destripe(float x[], char* bname, unsigned int mask[], char* hdfname)
{	int c,p,r;
	int ind;
	float *px,*py,*g,*gf;
	char* fname;
	FILE *fp;
	int hdflen;
	unsigned int count;
	
	if ( (fname = (char *)calloc(25,sizeof(char))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to FNAME"ANSI_COLOR_RESET);
				exit(1);
			}
	
	hdflen=strlen(hdfname);
			
	strncpy(fname, hdfname + (hdflen-4-12), (hdflen-4) - (hdflen-4-12));
			
	strcat(fname,bname);	
	strcat(fname,".dat");	
	
	printf("\n");
	
	if ( (g = (float *)calloc(col*row,sizeof(float))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to G"ANSI_COLOR_RESET);
				exit(1);
			}
	if ( (px = (float *)calloc(col,sizeof(float))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to PX"ANSI_COLOR_RESET);
				exit(1);
			}
			
	for(r=0;r<row;r++)
	{	count=0;
		for(c=0;c<col;c++)
		{	p=r*col+c;
			if(mask[p]==0)
			{	px[c]=x[p];
				count++;
			}
			else
				px[c]=0;
		}
		
		ifgauss(px,101);
										
		for(c=0;c<col;c++)
		{	p=r*col+c;
			if(mask[p]==0 && x[p]!=0)
				g[p]=((x[p]-px[c])/x[p]);
			else
				g[p]=0;
		}
		
		printf("\r\t\t... Processing Row Number: %4d of %d",r+1,row);
		fflush(stdout);
	}
	
	free(px);
	
	if ( (gf = (float *)calloc(col,sizeof(float))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to GF"ANSI_COLOR_RESET);
				exit(1);
			}

	fp= fopen(fname, "w"); // write only	
	fprintf(fp,"%s\t%s\n","Column","Gain");	

	for(c=0;c<col;c++)
	{	ind=0;
		
		for(r=0;r<row;r++)
		{	p=r*col+c;
			if(mask[p]==0)
				ind++;
		}
		
		if ( (py = (float *)calloc(ind,sizeof(float))) == NULL) 
		{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to PY"ANSI_COLOR_RESET);
			exit(1);
		}
				
		if(ind!=0)
		{	ind=0;
		
			for(r=0;r<row;r++)
			{	p=r*col+c;
				if(mask[p]==0 && g[p]!=0)
				{	py[ind]=g[p];
					ind++;
				}
			}
			
			gf[c]=median(py,ind);
							
			free(py);									
		}
		else
			gf[c]=0;
				
		fprintf(fp,"%d\t%f\n",c+1,gf[c]);
	}
	free(fname);
	fclose(fp);

	for(r=0;r<row;r++)   //row
		for(c=0;c<col;c++)	//col
		{	p = r*col + c;	//pixel
			x[p]=x[p]-x[p]*gf[c];	
		}
		
free(g);
free(gf);

printf("\n");
}
