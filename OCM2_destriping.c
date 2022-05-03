#include <stdlib.h>
#include <stdio.h>      
#include <libgen.h>
#include <time.h>
#include "mainf.h"
#include "mfhdf.h"

int row, col;
char *band_name[8]={"L_412","L_443","L_490","L_510","L_555","L_620","L_740","L_865"};

int main( int argc,char *argv[]) 
{   
	float *data,*nir;
	unsigned int *mask;
	int i;
	time_t start, stop, now, bnow;
	unsigned int min, sec;
	int32 fileid, bid, bindex, rank, data_type, n_attrs,istat;
	int32 dim_sizes[2];
	int32 st[2],ed[2],str[2];
	char bname[6]={"L_865"};
	char *cpy,*dfile;	

	if(argc!=2)
	{	printf(ANSI_COLOR_RED"\n\n\tERROR:\n\tThe usage for this program is : \n\t\t%s <OCM2 L1B input file>\n\n"ANSI_COLOR_RESET,argv[0]);
		exit(1);
	}
	if ( (cpy = (char *)calloc(512,sizeof(char))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to COMMAND"ANSI_COLOR_RESET);
				exit(1);
			}
	if ( (dfile = (char *)calloc(64,sizeof(char))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to OUTPUT FILENAME"ANSI_COLOR_RESET);
				exit(1);
			}
				
	strcpy(dfile,"DESTRIPED_");
	strcat(dfile,basename(argv[1]));
	strcpy(cpy,"/bin/cp  ");
	strcat(cpy,argv[1]);
	strcat(cpy,"  ");
	strcat(cpy,dfile);
	
	
	if(system(cpy)<0)
	{	printf(ANSI_COLOR_RED"\n\n\tERROR:\n\tCANNOT CREATE OUTPUT FILE\n\n"ANSI_COLOR_RESET,argv[0]);
		exit(1);
	}
	
	free(cpy);
	
	start=time(NULL);
	printf(ANSI_COLOR_GREEN"\n\tINTIATING DESTRIPING PROCESS FOR %s on %s\n\n"ANSI_COLOR_RESET,argv[1],ctime(&start));
		
	/* Open the file */
	fileid = SDstart (argv[1], DFACC_READ);
	
	if (fileid == FAIL)
	{	printf (ANSI_COLOR_RED"\n\t-E- : OCM - 2 L1B FILE NOT FOUND: %s\n"ANSI_COLOR_RESET,argv[1]);
			exit(15);
	}
	
	/* Get the index of the given data set SDS_NAME */
	bindex = SDnametoindex(fileid, bname);
	
	bid = SDselect (fileid, bindex);

	/* Get the name, rank, dimension sizes, data type and number of attributes for a data set  */
	SDgetinfo(bid, bname, &rank, dim_sizes, &data_type, &n_attrs);
	row = dim_sizes[0];
	col = dim_sizes[1];
	
	
	printf(ANSI_COLOR_BLUE"\n\t\t... Creating Mask for INVALID OCEAN PIXELS\n"ANSI_COLOR_RESET);
	
	if ( (nir = (float *)calloc(col*row,sizeof(float))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory for NIR"ANSI_COLOR_RESET);
				exit(1);
			}
	
	if ( (mask = (unsigned int *)calloc(row*col,sizeof(unsigned int))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory to MASK"ANSI_COLOR_RESET);
				exit(1);
			}
	
	st[0] = 0;  /* index of first row to read */
	st[1] = 0;  /* index of first column to read */
	ed[0] = row;    /* the number of rows to read */
	ed[1] = col;    /* the number of cols to read */
	str[0] = 1;
	str[1] = 1;
	
	istat = SDreaddata (bid, st, str, ed, (VOIDP) nir);
	
	/* Terminate access to the data set. */
	istat=SDendaccess (bid);
 
	/* Terminate access to the SD interface and close the file. */
	istat=SDend (fileid);
	
	inv_water_mask(nir,mask);
	
	free(nir);
	
	if (istat != FAIL)
	{ 
		printf(ANSI_COLOR_BLUE"\n\t\t... Mask Created\n"ANSI_COLOR_RESET);
	}
	else
	{	printf(ANSI_COLOR_RED"\n\t\t-E- : ERROR closing L1B file %s. \n\t\t... Masking Failed. \n\t\t... Exiting\n"ANSI_COLOR_RESET, argv[1]);
		exit(1);
	}
		
	printf(ANSI_COLOR_MAGENTA"\n\n\tStarted processing OCM 2 L1B file"ANSI_COLOR_LMAGENTA" (%d x %d)"ANSI_COLOR_MAGENTA": %s\n\n"ANSI_COLOR_RESET,col,row,argv[1]);
	
		
	for(i=0;i<8;i++)
	{	bnow=(unsigned)time(NULL);
		
		if ( (data = (float *)calloc(col*row,sizeof(float))) == NULL) 
			{	printf(ANSI_COLOR_RED"\n\t\t-E- : Error allocating memory for DATA"ANSI_COLOR_RESET);
				exit(1);
			}
		
		read_data(argv[1],data,band_name[i]);		
	
		printf(ANSI_COLOR_LMAGENTA"\n\t\t... Started DESTRIPING %s of %s\n"ANSI_COLOR_RESET,band_name[i],argv[1]);	
		
		destripe(data,band_name[i],mask,argv[1]);

		printf(ANSI_COLOR_LMAGENTA"\n\t\t... DESTRIPING %s of %s COMPLETED\n"ANSI_COLOR_RESET,band_name[i],argv[1]);
	
		write_data(dfile,data,band_name[i]);
		
		free(data);
		
		now=time(NULL);
		
		min=(now-bnow)/60;
		sec=(now-bnow)%60;
			
		printf(ANSI_COLOR_GOLDEN"\n\n\tDESTRIPING %s of OCM2 L1B file %s is COMPLETE after"ANSI_COLOR_BLUE" %d minutes and %d seconds"ANSI_COLOR_GOLDEN".\n\n"ANSI_COLOR_RESET,band_name[i],argv[1],min,sec);
	}
	
	free(dfile);
	free(mask);
	
	stop=time(NULL);
	
	min=(stop-start)/60;
	sec=(stop-start)%60;
		
	printf(ANSI_COLOR_GOLDEN"\n\n\tDESTRIPING process for OCM2 L1B file %s is COMPLETE on %s (after"ANSI_COLOR_BLUE" %d minutes and %d seconds"ANSI_COLOR_GOLDEN").\n\n"ANSI_COLOR_RESET,argv[1],ctime(&stop),min,sec);
			
	return 0;
		
}

	
