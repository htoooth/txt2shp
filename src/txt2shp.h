#ifndef TXT2SHP_H_INCLUDE

#define TXT2SHP_H_INCLUDE

#include "common.h"

struct Options{
	int x_column;
	int y_column;

	Options(int x, int y) :x_column(x), y_column(y){

	}
};

CPLErr BatchTxt(char * idir, char * odir, Options opt);

#endif