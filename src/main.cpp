#include "txt2shp.h"

void Usage(){
	OGRSFDriverRegistrar *poR = OGRSFDriverRegistrar::GetRegistrar();
	printf(
		"Usage: txt2shp -i <input directory>\n"
		"               -o <output directory>\n"
		"               -x <the column index of x coordination >\n"
		"               -y <the column index of y coordination >\n"
		"               -f <output file format_name>\n\n"

		"Note :\n"
		" The column index start 0, so if the x coordination column number is 3 and y is 5,"
		" you will set x with 2 and y is 4.\n\n"

		"** Very Important ** :\n"
		" You can not put any file except you data files in the input directory."
		" And the output directory must be empty directory.\n\n"
	);

	printf("Advanced options :\n");
	printf(" -f format_name: output file format name, possible values are:\n");

	for (int iDriver = 0; iDriver < poR->GetDriverCount(); iDriver++) {
		OGRSFDriver *poDriver = poR->GetDriver(iDriver);

		if (poDriver->TestCapability(ODrCCreateDataSource))
			printf("     -f \"%s\"\n", poDriver->GetName());
	}

	printf(
		"\nExample :\n"
		" txt2shp -i you_dir -o you_dir -x 2 -y 4 -f \"ESRI Shapefile\"\n\n"
		);
	exit(1);
}

int main(int argc,char ** argv){
	char * iDir = NULL;
	char * oDir = NULL;
	Option opt(1,2);

	RegisterVector();

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
		else if (EQUAL(argv[i], "-f")){
			opt.format = argv[++i];
		}
		else if (EQUAL(argv[i], "-g")){
			opt.geoType = atoi(argv[++i]);
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
    
	VectorClean();

	return err;
}