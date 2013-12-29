#ifndef OPTION_H_INCLUDE

#define OPTION_H_INCLUDE

struct Option
{
	int x_column;
	int y_column;
	int geoType;
	const char * format;

	Option(int x = 0, int y = 1, int type = 3, char * fmt = "ESRI Shapefile")
		: x_column(x)
		, y_column(y)
		, geoType(type)
		, format(fmt) {}
};


#endif