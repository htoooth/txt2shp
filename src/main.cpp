#include <cpl_string.h>
#include "txt2shp.h"

void Usage(){
	printf(
		"Usage: txt2gdal [-h]\n"
		"                 -i <input directory>\n"
		"                 -o <output directory>"
		);

	exit(1);
}

int main(int argc,char ** argv){
	char * iDir = NULL;
	char * oDir = NULL;
	for (int i = 1; i < argc; ++i) {
		if (EQUAL(argv[i],"-i")) {
			iDir = argv[++i];
		}
		else if(EQUAL(argv[i],"-o")){
			oDir = argv[++i];
		}
		else {
			Usage();
		}
	}

	if( iDir == NULL || oDir == NULL 
	|| strcmp(iDir,oDir) == 0){
		Usage();
	}

	int err = Txt2Shp(iDir, oDir);

	return err;
}