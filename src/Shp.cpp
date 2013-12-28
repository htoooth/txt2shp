#include "Shp.h"
#include "ogrformat.h"

Shp::Shp(const char * fileName) {
	ds = VectorCreate("ESRI Shapefile", fileName);
    layer = ds->CreateLayer(CPLGetBasename(fileName), NULL, wkbPolygon);
	DefaultDefn();
}

Shp::~Shp() {
    if (ds != NULL) {
        VectorClose(ds);
    }
}

void Shp::AddGeometry(OGRGeometry * geo){
	OGRFeature * feat = new OGRFeature(defn);
	feat->SetGeometryDirectly(geo);
	layer->CreateFeature(feat);
}

void Shp::DefaultDefn(){
	defn = new OGRFeatureDefn("default");
}