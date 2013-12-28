#include "txt2shp.h"
#include "Txt.h"
#include "Shp.h"

bool CheckForDir(const char * file){
	if (EQUAL(file, ".") || EQUAL(file, "..")){
		return true;
	}
	return false;
}

char ** GetFilesName(char * dir){
	char ** file = VSIReadDir(dir);
	char ** result = NULL;
	for (int i = 0; i < CSLCount(file); i++){
		if (!CheckForDir(file[i])){
			result = CSLAddString(result, file[i]);
		}
	}
	return result;
}

const char * GetAbsPath(char * dir, char * fileName){
	const char * absPath = CPLFormFilename(dir, fileName, NULL);
	return absPath;
}

char ** GetFilesPath(char * dir, char ** files){
	char ** paths = NULL;
	for (int i = 0; i < CSLCount(files); i++){
	    paths = CSLAddString(paths,GetAbsPath(dir,files[i]));
	}
	return paths;
}

char ** GetFiles(char * dir){
	char ** files = GetFilesName(dir);
	char ** result = GetFilesPath(dir, files);

	CSLDestroy(files);
	return result;
}

char ** GetBaseFiles(char ** files){
	char ** result = NULL;
	for (int i = 0; i < CSLCount(files); i++){
		result = CSLAddString(result, CPLGetBasename(files[i]));
	}
	return result;
}

char ** GetSources(char * dir,char * idir){
	char ** files = GetFilesName(idir);
	char ** baseFiles = GetBaseFiles(files);
	char ** sources = GetFilesPath(dir, baseFiles);

	CSLDestroy(files);
	CSLDestroy(baseFiles);
	return sources;
}

OGRGeometry * GeometryFromRing(std::list<Point> & ring){
	OGRLinearRing * poOGRRing = new OGRLinearRing();
	OGRGeometry * poOGRGeometry = NULL;
	OGRPolygon * polygon = new OGRPolygon();
	std::list<Point>::iterator first = ring.begin();
	for (std::list<Point>::iterator it = ring.begin(); it != ring.end(); it++){
		poOGRRing->addPoint(it->x, it->y);
	}

	poOGRRing->addPoint(first->x, first->y);

	polygon->addRingDirectly(poOGRRing);
	poOGRGeometry = polygon;
	return poOGRGeometry;
}


CPLErr Txt2Shp(const char * txt, const char * shp, Options opt){
	Txt txtfile(txt, opt.x_column, opt.y_column);
	std::list<Point> ring = txtfile.getRing();

	OGRGeometry * geo = GeometryFromRing(ring);

	Shp shpfile(shp);
	shpfile.AddGeometry(geo);
	
	return CE_None;
}

CPLErr BatchTxt(char *idir, char * odir,Options opt){
	char ** files = GetFiles(idir);
	char ** shps = GetSources(odir,idir);

	CSLPrint(files, NULL);
	CSLPrint(shps, NULL);

	OGRRegisterAll();

	CPLErr err = CE_None;

	for (int i = 0; i < CSLCount(files); i++){
		err = Txt2Shp(files[i], shps[i],opt);
		if (err != CE_None){
			break;
		}
	}

	CSLDestroy(files);
	CSLDestroy(shps);
	return err;
}
