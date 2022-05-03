#include "mfunc.h"

extern void read_data(char *L1B_in, float *data, char *sds_name);
extern void write_data(char *L1B_out,float *data, char *sds_name);
extern void destripe(float x[], char* bname,unsigned int cmask[], char *hdfname);
extern void inv_water_mask(float nir[],unsigned int mask[]);
