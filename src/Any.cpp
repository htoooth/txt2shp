#include "Any.h"
#include "ogrformat.h"

Any::Any(const char * fileName, Option opt)
{
	ds = VectorCreate(opt.format, fileName);
	layer = ds->CreateLayer(CPLGetBasename(fileName), NULL, wkbUnknown);
	DefaultDefn();
}

Any::~Any()
{
	if (ds != NULL)
	{
		VectorClose(ds);
	}
}

void Any::AddGeometry(OGRGeometry * geo)
{
	OGRFeature * feat = new OGRFeature(defn);
	feat->SetGeometryDirectly(geo);
	layer->CreateFeature(feat);
}

void Any::DefaultDefn()
{
	defn = new OGRFeatureDefn("default");
}