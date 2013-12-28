#include "txt2shp.h"

void Usage(){
	printf(
		"Usage: txt2shp -i <input directory>\n"
		"               -o <output directory>\n"
		"               -x <the column index of x coordination >\n"
		"               -y <the column index of y coordination >\n"
		"\nNote:\n"
		"The column index start 0, so if the x coordination column number is 3 and y is 5,\n"
		"you will set x with 2 and y is 4.\n "
		"\nExample:\n "
		"txt2shp -i you_dir -o you_dir -x 2 -y 4 \n "
		);

	exit(1);
}

int main(int argc,char ** argv){
	char * iDir = NULL;
	char * oDir = NULL;
	Options opt(1,2);
	for (int i = 1; i < argc; ++i) {
		if (EQUAL(argv[i],"-i")) {
			iDir = argv[++i];
		}
		else if(EQUAL(argv[i],"-o")){
			oDir = argv[++i];
		}
		else if (EQUAL(argv[i], "-x")){
			opt.x_column = atoi(argv[++i]);
		}
		else if (EQUAL(argv[i], "-y")){
			opt.y_column = atoi(argv[++i]);
		}
		else {
			Usage();
		}
	}

	if( iDir == NULL || oDir == NULL 
	|| strcmp(iDir,oDir) == 0){
		Usage();
	}

	CPLErr err = BatchTxt(iDir, oDir,opt);

	return err;
}