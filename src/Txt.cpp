#include "Txt.h"
#include "ScopeGuard.h"

/// convert char to char point
/// char to char*
const char * char2p(char c)
{
	return CPLSPrintf("%c", c);
}

FILE * OpenTxt(const char * fileName)
{
	return VSIFOpen(fileName, "r");
}

Txt::Txt(const char * fileName, Option opt)
{
	fp = OpenTxt(fileName);

	if (fp != nullptr)
	{
		const char * first = CPLReadLine(fp);
		seperator = CSVDetectSeperator(first);
		fields = CSLTokenizeString2(first, char2p(seperator), CSLT_HONOURSTRINGS);
        // auto detect x,y index
		x = CSLFindString(fields,"x");
		y = CSLFindString(fields,"y");
	}
}

Point * Txt::ReadOnePoint()
{
	char ** values = CSVReadParseLine2(fp, seperator);
	ON_SCOPE_EXIT([&]{CSLDestroy(values); });

	if (values == nullptr)
	{
		return nullptr;
	}

	return new Point(CPLAtof(values[x]), CPLAtof(values[y]));
}

std::list<Point> Txt::getRing()
{
	std::list<Point> ring;

	for (;;)
	{
		Point * point = ReadOnePoint();
		ON_SCOPE_EXIT([&]{delete point; });

		if (point == nullptr)
		{
			break;
		}

		ring.push_back(*point);
	}

	return ring;
}

Txt::~Txt()
{
	if (fp != nullptr)
	{
		VSIFClose(fp);
	}

	CSLDestroy(fields);
}
