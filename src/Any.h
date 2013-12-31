#ifndef SHP_H_INCLUDE

#define SHP_H_INCLUDE

#include "common.h"

class Any
{
public:
	Any(const char * name, Option opt);
	~Any();

	void AddGeometry(OGRGeometry * geo);

private:
	void DefaultDefn();

	OGRDataSource * ds;
	OGRLayer * layer;
	OGRFeatureDefn * defn;
	char * format;
};

#endif
