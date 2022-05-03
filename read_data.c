#include <stdio.h>
#include "mfhdf.h"
#include "hdf.h"
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"                  
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_LMAGENTA   "\033[01;35m"
#define ANSI_COLOR_GOLDEN	"\033[22;33m"

extern int row, col;

void read_data(char *L1B_in, float *data, char *sds_name)
{	int32 sd_id, sds_id, istat,sds_index;
	int32 start[2],edges[2],stride[2];
	
	
	start[0] = 0;  /* index of first row to read */
	start[1] = 0;  /* index of first column to read */
	edges[0] = row;    /* the number of rows to read */
	edges[1] = col;    /* the number of cols to read */
	stride[0] = 1;
	stride[1] = 1;
	
	
	/* Open the file */
	
	sd_id = SDstart(L1B_in, DFACC_READ);
	
	if (sd_id != FAIL)
	{ 	printf (ANSI_COLOR_MAGENTA"\n\t\t... %s opened to READ\n"ANSI_COLOR_RESET,L1B_in);
	}
	else
		{	printf (ANSI_COLOR_MAGENTA"\n\t\t... access to READ %s FAILED\n"ANSI_COLOR_RESET,L1B_in);
			exit(15);
		}
	sds_index = SDnametoindex(sd_id, sds_name);	
	sds_id = SDselect (sd_id, sds_index);
	
	printf (ANSI_COLOR_MAGENTA"\n\t\t... Reading %s \n"ANSI_COLOR_RESET,sds_name);
  	
  	istat = SDreaddata (sds_id, start, stride, edges, (VOIDP) data);

	/* Terminate access to the array. */
	istat = SDendaccess(sds_id);



	/* Terminate access to the SD interface and close the file. */
	istat = SDend(sd_id);
	if (istat != FAIL)
	{ 
		printf(ANSI_COLOR_MAGENTA"\n\t\t... Reading %s from L1B file %s is COMPLETE\n"ANSI_COLOR_RESET,sds_name, L1B_in);
	}
	else
	{	printf(ANSI_COLOR_MAGENTA"\n\t\t... ERROR closing L1B file %s after reading %s data\n"ANSI_COLOR_RESET, L1B_in,sds_name);
		exit(1);
	}
		printf (ANSI_COLOR_MAGENTA"\n\t\t... CLOSED L1B file %s\n"ANSI_COLOR_RESET,L1B_in);
}

#undef ANSI_COLOR_RED     
#undef ANSI_COLOR_GREEN  
#undef ANSI_COLOR_YELLOW  
#undef ANSI_COLOR_BLUE                    
#undef ANSI_COLOR_MAGENTA 
#undef ANSI_COLOR_CYAN    
#undef ANSI_COLOR_RESET  
#undef ANSI_COLOR_LMAGENTA   
#undef ANSI_COLOR_GOLDEN	
