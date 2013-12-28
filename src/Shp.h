#ifndef SHP_H_INCLUDE

#define SHP_H_INCLUDE

#include "common.h"

class Shp
{
public:
	Shp(const char * name);
	~Shp();

	void AddGeometry(OGRGeometry * geo);

private:
	void DefaultDefn();

	OGRDataSource * ds;
	OGRLayer * layer;
	OGRFeatureDefn * defn;
};

#endif
