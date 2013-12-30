#ifndef OPTION_H_INCLUDE

#define OPTION_H_INCLUDE

struct Option
{
	int geoType;
	const char * format;

	Option(int type = 3, char * fmt = "ESRI Shapefile")
		: geoType(type)
		, format(fmt) {}
};


#endif