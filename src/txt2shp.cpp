#include "txt2shp.h"
#include "Txt.h"
#include "Any.h"
#include "ogrformat.h"
#include "ScopeGuard.h"

bool CheckForFile(const char * file)
{
	if (EQUAL(file, ".") || EQUAL(file, ".."))
	{
		return false;
	}

	return true;
}

bool CheckForExtension(const char * file, const char * ext)
{
	if (EQUAL(CPLGetExtension(file), "") || !EQUAL(CPLGetExtension(file), ext))
	{
		return false;
	}

	return true;
}

char ** GetFilesName(char * dir)
{
	char ** file = VSIReadDir(dir);
	ON_SCOPE_EXIT([&]{CSLDestroy(file); });

	char ** result = nullptr;

	for (int i = 0; i < CSLCount(file); i++)
	{
		if (CheckForFile(file[i]) && CheckForExtension(file[i], "txt"))
		{
			result = CSLAddString(result, file[i]);
		}
	}

	return result;
}

const char * GetAbsPath(char * dir, char * fileName)
{
	const char * absPath = CPLFormFilename(dir, fileName, nullptr);
	return absPath;
}

char ** GetFilesPath(char * dir, char ** files)
{
	char ** paths = nullptr;

	for (int i = 0; i < CSLCount(files); i++)
	{
		paths = CSLAddString(paths, GetAbsPath(dir, files[i]));
	}

	return paths;
}

char ** GetFiles(char * dir)
{
	char ** files = GetFilesName(dir);
	ON_SCOPE_EXIT([&]{CSLDestroy(files); });

	char ** result = GetFilesPath(dir, files);

	return result;
}

char ** GetBaseFiles(char ** files)
{
	char ** result = nullptr;

	for (int i = 0; i < CSLCount(files); i++)
	{
		result = CSLAddString(result, CPLGetBasename(files[i]));
	}

	return result;
}

char ** GetSources(char * dir, char ** files)
{
	char ** baseFiles = GetBaseFiles(files);
	ON_SCOPE_EXIT([&]{CSLDestroy(baseFiles); });

	char ** sources = GetFilesPath(dir, baseFiles);

	return sources;
}

OGRGeometry * GeometryFromRing(std::list<Point> & ring)
{
	auto ogrRing = new OGRLinearRing();
	auto ogrPolygon = new OGRPolygon();

	std::for_each(std::begin(ring), std::end(ring),
		[&](Point it){ogrRing->addPoint(it->getX(), it->getY()); });

	ogrPolygon->addRingDirectly(ogrRing);

	return ogrPolygon;
}

CPLErr Txt2Any(const char * txt, const char * shp, Option opt)
{
	Txt txtfile(txt, opt);
	std::list<Point> ring = txtfile.getRing();

	auto geo = GeometryFromRing(ring);

	Any shpfile(shp, opt);
	shpfile.AddGeometry(geo);

	return CE_None;
}

CPLErr BatchTxt(char * idir, char * odir, Option opt)
{
	char ** files = GetFiles(idir);
	ON_SCOPE_EXIT([&]{CSLDestroy(files); });

	char ** shps = GetSources(odir, files);
	ON_SCOPE_EXIT([&]{CSLDestroy(shps); });

	CPLErr err = CE_None;

	for (int i = 0; i < CSLCount(files); i++)
	{
		err = Txt2Any(files[i], shps[i], opt);

		if (err != CE_None)
		{
			break;
		}
	}

	printf("OK");

	return err;
}
